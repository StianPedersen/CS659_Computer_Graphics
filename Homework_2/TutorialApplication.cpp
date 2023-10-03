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
TutorialApplication::TutorialApplication()
{
	count = 1;
}

//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

bool TutorialApplication::keyPressed(const KeyboardEvent &evt)
{
	if (evt.keysym.sym == SDLK_F1)
	{
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
	}
	if (evt.keysym.sym == SDLK_F2)
	{
		if (count > 1)
		{
			--count;
			head_nodes[count]->detachObject(ogre_heads[count]);
		}
		else
		{
			std::cerr << "You must haae 1 ogrehead" << std::endl;
		}
	}
	std::cout << "Count: " << count << std::endl;
	return true;
}
//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// Create entities

	for (int i = 0; i <= 7; i++)
	{
		ogre_heads.push_back(mSceneMgr->createEntity("Head" + std::to_string(i), "ogrehead.mesh"));
		head_nodes.push_back(mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode" + std::to_string(i)));
	}
	std::cout << ogre_heads.size() << std::endl;
	head_nodes[0]->attachObject(ogre_heads[0]);

	head_nodes[0]->translate(Vector3(20, 0, 0));

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
