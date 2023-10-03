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
}


//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}


//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// Create your scene here :)
	// Create entities
	Entity* ogreHead1 = mSceneMgr->createEntity("Head1", "ogrehead.mesh");
	Entity* ogreHead2 = mSceneMgr->createEntity("Head2", "ogrehead.mesh");

	// Create SceneNodes and attach the entities to them
	SceneNode* headNode1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode1");
	SceneNode* headNode2 = headNode1->createChildSceneNode("HeadNode2");
	headNode1->attachObject(ogreHead1);
	headNode2->attachObject(ogreHead2);

	// Set transformations
	headNode1->scale(Vector3(1, 0.5, 1));
	headNode1->rotate(Vector3(0, 1, 0), Degree(-90));
	headNode1->translate(Vector3(20, 0, -20));

	headNode2->scale(Vector3(1, 1, 0.5));
	headNode2->rotate(Vector3(0, 1, 0), Degree(90));
	headNode2->translate(Vector3(-10, 0, 10));

	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

	// Create a light and set its position
	Light* light = mSceneMgr->createLight("MainLight");
	SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightNode");
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
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
