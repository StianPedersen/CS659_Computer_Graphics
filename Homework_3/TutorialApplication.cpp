/*-------------------------------------------------------------------------
This source file is a part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/


Copyright (c) 2000-2013 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:


The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE
-------------------------------------------------------------------------*/

#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication() : mCurrSubMesh(0),
											 mCurrVertex(0)
{
	count = 1;
	selected_head = 0;
}

//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}
void TutorialApplication::change_current_mesh()
{
	std::cout << "Current selected head number: " << selected_head << std::endl;
	mMesh = ogre_heads[selected_head]->getMesh();
	int nSubMesh = mMesh->getNumSubMeshes();
	mVertexElePos.resize(nSubMesh, nullptr);
	for (int nMesh = 0; nMesh < nSubMesh; ++nMesh)
		mVertexElePos[nMesh] = mMesh->getSubMesh(nMesh)->vertexData->vertexDeclaration->findElementBySemantic(VES_POSITION);

	// Get vertex buffer for each sub-mesh
	mVertexBufPos.resize(nSubMesh, nullptr);
	for (int nMesh = 0; nMesh < nSubMesh; ++nMesh)
		mVertexBufPos[nMesh] = mMesh->getSubMesh(nMesh)->vertexData->vertexBufferBinding->getBuffer(mVertexElePos[nMesh]->getSource());
}

bool TutorialApplication::keyPressed(const KeyboardEvent &evt)
{
	uint8 *pVertexPtr = nullptr;
	float *pElePtr = nullptr;
	switch (evt.keysym.sym)
	{
	case 'm':
		// Increment current sub-mesh index
		if (mMesh)
		{
			int nSubMesh = mMesh->getNumSubMeshes();
			if (mCurrSubMesh < (nSubMesh - 1))
				++mCurrSubMesh;

			else
				mCurrSubMesh = 0;

			printf("The current sub-mesh index is \"%i\".\n", mCurrSubMesh);
		}
		break;
	case 'h':
		if (selected_head < (count - 1))
		{
			++selected_head;
			change_current_mesh();
		}
		else
		{
			selected_head = 0;
			change_current_mesh();
		}
		break;
	case 'v':
		++mCurrVertex;
		std::cout << "Changed to vertex number " << mCurrVertex << std::endl;
		break;

	case SDLK_F1:
		if (count <= 7)
		{
			head_nodes[count]->attachObject(ogre_heads[count]);
			head_nodes[count]->translate(Vector3(20 + (count * 10), 0, 0));
			++count;
		}
		else
		{
			std::cerr << "To many heads, only 8 on the same time" << std::endl;
		}
		break;
	case SDLK_F2:
		if (count > 1)
		{
			--count;
			head_nodes[count]->detachObject(ogre_heads[count]);
			if (selected_head > (count - 1))
			{
				selected_head = (count - 1);
				std::cerr << "Your currently selected OgreHead mesh is not visible, changing to head number " << selected_head << std::endl;
				change_current_mesh();
			}
		}
		else
		{
			std::cerr << "You must have 1 ogrehead" << std::endl;
		}
		break;

	case SDLK_INSERT:
		// Lock vertex buffer to get pointer of current vertex

		pVertexPtr = static_cast<uint8 *>(mVertexBufPos[mCurrSubMesh]->lock(HardwareBuffer::LockOptions::HBL_NORMAL));

		pVertexPtr += mCurrVertex * mVertexBufPos[mCurrSubMesh]->getVertexSize();
		mVertexElePos[mCurrSubMesh]->baseVertexPointerToElement(pVertexPtr, &pElePtr);

		// Increment x, y, z coordinates of current vertex
		pElePtr[0] += 1.0f;
		pElePtr[1] += 1.0f;
		pElePtr[2] += 1.0f;

		mVertexBufPos[mCurrSubMesh]->unlock();
		break;

	case SDLK_DELETE:
		// Lock vertex buffer to get pointer of current vertex
		pVertexPtr = static_cast<uint8 *>(mVertexBufPos[mCurrSubMesh]->lock(HardwareBuffer::LockOptions::HBL_NORMAL));
		pVertexPtr += mCurrVertex * mVertexBufPos[mCurrSubMesh]->getVertexSize();
		mVertexElePos[mCurrSubMesh]->baseVertexPointerToElement(pVertexPtr, &pElePtr);

		// Decrement x, y, z coordinates of current vertex
		pElePtr[0] -= 1.0f;
		pElePtr[1] -= 1.0f;
		pElePtr[2] -= 1.0f;

		mVertexBufPos[mCurrSubMesh]->unlock();
		break;
	}

	if (!BaseApplication::keyPressed(evt))
		return false;
}
//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// Create entities
	ogre_heads.push_back(mSceneMgr->createEntity("Head" + std::to_string(0), "ogrehead.mesh"));
	head_nodes.push_back(mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode" + std::to_string(0)));

	for (int i = 1; i <= 7; i++)
	{
		auto new_mesh = ogre_heads[0]->getMesh()->clone("Head_mesh_" + std::to_string(i));
		ogre_heads.push_back(mSceneMgr->createEntity("Head" + std::to_string(i), new_mesh));
		head_nodes.push_back(mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode" + std::to_string(i)));
	}

	head_nodes[0]->attachObject(ogre_heads[0]);
	head_nodes[0]->translate(Vector3(20, 0, 0));

	change_current_mesh();

	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

	// Create a light and set its position
	Light *light = mSceneMgr->createLight("MainLight");
	SceneNode *lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightNode");
	lightNode->attachObject(light);
	lightNode->setPosition(20, 80, 50);
}

//-------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	try
	{
		TutorialApplication app;
		app.initApp();
		app.go();
		app.closeApp();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}
