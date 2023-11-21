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
TutorialApplication::TutorialApplication() : mSinbadNode(nullptr),
	mRunBaseState(nullptr),
	mRunTopState(nullptr)
{
}


//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
	mPressKeySet.clear();
}


//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// Create your scene here :)
	// Create an entity
	Entity* sinbad = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh"); 

	// Create SceneNode and attach the entity
	mSinbadNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("SinbadNode", Vector3(0, 0, 65)); 
	mSinbadNode->attachObject(sinbad); 

	// Set cumulative blending mode
	sinbad->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	// Set animation state properties ("RunBase")
	mRunBaseState = sinbad->getAnimationState("RunBase");
	mRunBaseState->setLoop(true);
	mRunBaseState->setEnabled(false);

	// Set animation state properties ("RunTop")
	mRunTopState = sinbad->getAnimationState("RunTop");
	mRunTopState->setLoop(true);
	mRunTopState->setEnabled(false);

	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

	// Create a Light and set its position
	Light* light = mSceneMgr->createLight("MainLight");
	SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightNode");
	lightNode->attachObject(light);
	lightNode->setPosition(200, 600, 500);
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const FrameEvent &evt)
{
	if (!BaseApplication::frameRenderingQueued(evt)) return false;

	// Check keyboard to determine running mode
	bool bRunning = false;
	if ((mPressKeySet.count('j') != 0) && (mPressKeySet.count('l') == 0))
	{
		// Turn left and run
		bRunning = true;
		mSinbadNode->translate(Vector3(-3, 0, 0) * evt.timeSinceLastFrame);
		mSinbadNode->resetOrientation();
		mSinbadNode->yaw(Radian(-Math::HALF_PI));
	}
	else if ((mPressKeySet.count('j') == 0) && (mPressKeySet.count('l') != 0))
	{
		// Turn right and run
		bRunning = true;
		mSinbadNode->translate(Vector3(3, 0, 0) * evt.timeSinceLastFrame);
		mSinbadNode->resetOrientation();
		mSinbadNode->yaw(Radian(Math::HALF_PI));
	}

	if(bRunning)
	{
		// Advance the animation
		mRunBaseState->setEnabled(true);
		mRunBaseState->addTime(evt.timeSinceLastFrame);

		mRunTopState->setEnabled(true);
		mRunTopState->addTime(evt.timeSinceLastFrame);
	}
	else
	{
		// Reset node orientation and time position
		mSinbadNode->resetOrientation();

		mRunBaseState->setEnabled(false);
		mRunBaseState->setTimePosition(0);

		mRunTopState->setEnabled(false);
		mRunTopState->setTimePosition(0);
	}

	return true;
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::keyPressed(const KeyboardEvent &evt)
{
	mPressKeySet.insert(evt.keysym.sym);
	return BaseApplication::keyPressed(evt);
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::keyReleased(const KeyboardEvent &evt)
{
	mPressKeySet.erase(evt.keysym.sym);
	return BaseApplication::keyReleased(evt);
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
