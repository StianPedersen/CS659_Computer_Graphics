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

    Light *light = mSceneMgr->createLight("MainLight");                           // Create a light
    SceneNode *lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(); // Create lightnode
    lightNode->attachObject(light);                                               // Attach light to lightnode
    lightNode->setPosition(20, 80, 50);                                           // Set the lights position

    // Entity 1
    Entity *ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");
    SceneNode *ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode->attachObject(ogreEntity);

    // Entity 2
    Entity *ogreEntity2 = mSceneMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode *ogreNode2 = ogreNode->createChildSceneNode(Ogre::Vector3(84, 48, 0)); // Attach another entity to the first ogre node
    ogreNode2->attachObject(ogreEntity2);

    // Entity 3
    Entity *ogreEntity3 = mSceneMgr->createEntity("ogrehead.mesh");
    SceneNode *ogreNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode3->setPosition(0, 104, 0);
    ogreNode3->setScale(2, 1.2, 1);
    ogreNode3->attachObject(ogreEntity3);

    // Entity 4
    Entity *ogreEntity4 = mSceneMgr->createEntity("ogrehead.mesh");
    SceneNode *ogreNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode4->setPosition(-84, 48, 0);
    ogreNode4->roll(Degree(-90));
    ogreNode4->attachObject(ogreEntity4);
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
