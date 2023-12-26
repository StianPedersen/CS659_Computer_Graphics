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
void TutorialApplication::createCamera(void)
{
	// Create the camera
	BaseApplication::createCamera();
	mCameraNode->setPosition(0, 0, 5000);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// Create your scene here :)
	Entity *ogreBall[9];
	SceneNode *ballNode[9];
	String ballString[9];

	for (int i = 0; i < 9; ++i)
	{
		StringStream ballSteam;
		ballSteam << (i + 1);
		ballString[i] = String("Ball") + ballSteam.str();

		// Create entities
		ogreBall[i] = mSceneMgr->createEntity(ballString[i], "ball.mesh");
		ogreBall[i]->setMaterialName(ballString[i]);

		// Create SceneNodes and attach the entities to them
		if (i == 0)
		{
			ballNode[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode(ballString[i]);
			ballNode[i]->rotate(Vector3(0, 0, 1), Degree(30));
			ballNode[i]->translate(Vector3(1000, -1500, 0));
		}
		else
		{
			ballNode[i] = ballNode[i - 1]->createChildSceneNode(ballString[i]);

			// Set transformations
			ballNode[i]->rotate(Vector3(0, 0, 1), Degree(30));
			ballNode[i]->translate(Vector3(500 + i * 100, 0, 0));
		}

		ballNode[i]->attachObject(ogreBall[i]);
	}

	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

	// Create a light and set its position
	Light *light = mSceneMgr->createLight("MainLight");
	light->setSpecularColour(ColourValue::White);
	light->setType(Light::LT_SPOTLIGHT);
	light->setSpotlightRange(Degree(90), Degree(30));

	SceneNode *lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightNode");
	lightNode->attachObject(light);
	lightNode->setPosition(1000, 4000, 2500);
	lightNode->setDirection(-1, -1, -1);
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
