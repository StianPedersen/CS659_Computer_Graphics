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
	// Position
	pos_x = 200;
	pos_y = 200;
	pos_z = 0;
	position_flag = true; // Initial change always on position

	// Direction
	dir_x = -1;
	dir_y = -1;
	dir_z = 0;
	direction_flag = false;

	// Diffusion
	diff_red = 1.0;
	diff_green = 1.0;
	diff_blue = 1.0;
	diffusion_flag = false;

	// Specular
	spec_red = 0;
	spec_green = 0;
	spec_blue = 1.0;
	specular_flag = false;

	// Range
	inner_angle = 60;
	outer_angle = 14;
	range_flag = false;

	// First, second, third values
	change_first = true; // Initial change always on first
	change_second = false;
	change_third = false;
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

	case 'p': // 1
		position_flag = true;
		direction_flag = false;
		range_flag = false;
		specular_flag = false;
		diffusion_flag = false;
		break;

	case 'o': // 2
		direction_flag = true;
		position_flag = false;
		range_flag = false;
		specular_flag = false;
		diffusion_flag = false;
		break;

	case 'i': // 3
		range_flag = true;
		position_flag = false;
		direction_flag = false;
		specular_flag = false;
		diffusion_flag = false;
		break;

	case 'l': // 4
		specular_flag = true;
		position_flag = false;
		direction_flag = false;
		range_flag = false;
		diffusion_flag = false;

		break;
	case 'k': // 5
		diffusion_flag = true;
		position_flag = false;
		direction_flag = false;
		range_flag = false;
		specular_flag = false;
		break;

	case 'x':
		change_first = true;
		change_second = false;
		change_third = false;
		break;
	case 'y':
		change_first = false;
		change_second = true;
		change_third = false;
		break;

	case 'z':
		change_first = false;
		change_second = false;
		change_third = true;
		break;

	case '2':
		if (position_flag)
		{
			if (change_first)
			{
				pos_x = pos_x + 0.1;
				std::cout << "Position X increased: " << pos_x << std::endl;
			}
			else if (change_second)
			{
				pos_y = pos_y + 0.1;
				std::cout << "Position Y increas: " << pos_y << std::endl;
			}
			else if (change_third)
			{
				pos_z = pos_z + 0.1;
				std::cout << "Position Z increas: " << pos_z << std::endl;
			}
			lightNode->setPosition(pos_x, pos_y, pos_z);
		}
		else if (direction_flag)
		{
			if (change_first)
			{
				dir_x = dir_x + 0.1;
				std::cout << "Direction X increased: " << dir_x << std::endl;
			}
			else if (change_second)
			{
				dir_y = dir_y + 0.1;
				std::cout << "Direction Y increased: " << dir_y << std::endl;
			}
			else if (change_third)
			{
				dir_z = dir_z + 0.1;
				std::cout << "Direction Z increased: " << dir_z << std::endl;
			}
			lightNode->setDirection(dir_x, dir_y, dir_z);
		}
		else if (diffusion_flag)
		{
			if (change_first)
			{
				diff_red = diff_red + 0.1;
				std::cout << "Diffuse red increased: " << diff_red << std::endl;
			}
			else if (change_second)
			{
				diff_green = diff_green + 0.1;
				std::cout << "Diffuse green increased: " << diff_green << std::endl;
			}
			else if (change_third)
			{
				diff_blue = diff_blue + 0.1;
				std::cout << "Diffuse blue increased: " << diff_blue << std::endl;
			}
			light->setDiffuseColour(diff_red, diff_green, diff_blue);
		}
		else if (specular_flag)
		{
			if (change_first)
			{
				spec_red = spec_red + 0.1;
				std::cout << "Specular red increased: " << spec_red << std::endl;
			}
			else if (change_second)
			{
				spec_green = spec_green + 0.1;
				std::cout << "Specular green increased: " << spec_green << std::endl;
			}
			else if (change_third)
			{
				spec_blue = spec_blue + 0.1;
				std::cout << "Specular blue increased: " << spec_blue << std::endl;
			}
			light->setSpecularColour(spec_red, spec_green, spec_blue); // 4
		}
		else if (range_flag)
		{
			if (change_first)
			{
				inner_angle = inner_angle + 0.1;
				std::cout << "Inner angle range increased: " << inner_angle << std::endl;
			}
			else if (change_second)
			{
				outer_angle = outer_angle + 0.1;
				std::cout << "Outer angle range increased: " << inner_angle << std::endl;
			}
			else if (change_third)
			{
				inner_angle = inner_angle + 0.1;
				outer_angle = outer_angle + 0.1;
				std::cout << "Outer and Inner angle range increased: " << inner_angle << " " << outer_angle << std::endl;
			}
			light->setSpotlightRange(Degree(inner_angle), Degree(outer_angle)); // 3
		}
		break;

	case '1':
		if (position_flag)
		{
			if (change_first)
			{
				pos_x = pos_x - 0.1;
				std::cout << "Position X decreased: " << pos_x << std::endl;
			}
			else if (change_second)
			{
				pos_y = pos_y - 0.1;
				std::cout << "Position Y decreased: " << pos_y << std::endl;
			}
			else if (change_third)
			{
				pos_z = pos_z - 0.1;
				std::cout << "Position Z decreased: " << pos_z << std::endl;
			}
			lightNode->setPosition(pos_x, pos_y, pos_z);
		}
		else if (direction_flag)
		{
			if (change_first)
			{
				dir_x = dir_x - 0.1;
				std::cout << "Direction X decreased: " << dir_x << std::endl;
			}
			else if (change_second)
			{
				dir_y = dir_y - 0.1;
				std::cout << "Direction Y decreased: " << dir_y << std::endl;
			}
			else if (change_third)
			{
				dir_z = dir_z - 0.1;
				std::cout << "Direction Z decreased: " << dir_z << std::endl;
			}
			lightNode->setDirection(dir_x, dir_y, dir_z);
		}
		else if (diffusion_flag)
		{
			if (change_first)
			{
				diff_red = diff_red - 0.1;
				std::cout << "Diffuse red decreased: " << diff_red << std::endl;
			}
			else if (change_second)
			{
				diff_green = diff_green - 0.1;
				std::cout << "Diffuse green decreased: " << diff_green << std::endl;
			}
			else if (change_third)
			{
				diff_blue = diff_blue - 0.1;
				std::cout << "Diffuse blue decreased: " << diff_blue << std::endl;
			}
			light->setDiffuseColour(diff_red, diff_green, diff_blue);
		}
		else if (specular_flag)
		{
			if (change_first)
			{
				spec_red = spec_red - 0.1;
				std::cout << "Specular red decreased: " << spec_red << std::endl;
			}
			else if (change_second)
			{
				spec_green = spec_green - 0.1;
				std::cout << "Specular green decreased: " << spec_green << std::endl;
			}
			else if (change_third)
			{
				spec_blue = spec_blue - 0.1;
				std::cout << "Specular blue decreased: " << spec_blue << std::endl;
			}
			light->setSpecularColour(spec_red, spec_green, spec_blue); // 4
		}
		else if (range_flag)
		{
			if (change_first)
			{
				inner_angle = inner_angle - 0.1;
				std::cout << "Inner angle range decreased: " << inner_angle << std::endl;
			}
			else if (change_second)
			{
				outer_angle = outer_angle - 0.1;
				std::cout << "Outer angle range decreased: " << inner_angle << std::endl;
			}
			else if (change_third)
			{
				inner_angle = inner_angle - 0.1;
				outer_angle = outer_angle - 0.1;
				std::cout << "Outer and Inner angle range decreased: " << inner_angle << " " << outer_angle << std::endl;
			}
			light->setSpotlightRange(Degree(inner_angle), Degree(outer_angle)); // 3
		}
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
	head_nodes[0]->translate(Vector3(0, 0, 0));

	change_current_mesh();

	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

	// Create a light and set its position
	light = mSceneMgr->createLight("MainLight");

	light->setDiffuseColour(diff_red, diff_green, diff_blue);  // 5
	light->setSpecularColour(spec_red, spec_green, spec_blue); // 4
	light->setType(Light::LT_SPOTLIGHT);

	light->setSpotlightRange(Degree(inner_angle), Degree(outer_angle)); // 3

	lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightNode");

	lightNode->attachObject(light);
	lightNode->setPosition(pos_x, pos_y, pos_z);  // 1
	lightNode->setDirection(dir_x, dir_y, dir_z); // 2
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
