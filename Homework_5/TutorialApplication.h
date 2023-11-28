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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"

using namespace Ogre;
using namespace OgreBites;

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication();
    virtual ~TutorialApplication();
    bool keyPressed(const KeyboardEvent &evt);
    void change_current_mesh();

    int count, selected_head;
    // Position
    float pos_x, pos_y, pos_z;
    bool position_flag;

    // Direction
    float dir_x, dir_y, dir_z;
    bool direction_flag;

    // Diffusion
    float diff_red, diff_green, diff_blue;
    bool diffusion_flag;

    // Specular
    float spec_red, spec_green, spec_blue;
    bool specular_flag;

    // Range
    float inner_angle, outer_angle;
    bool range_flag;

    // First, second, third values
    bool change_first, change_second, change_third;

    std::vector<Entity *> ogre_heads;
    std::vector<SceneNode *> head_nodes;
    std::vector<MeshPtr *> mesh_list;

protected:
    virtual void createScene(void);
    int mCurrSubMesh, mCurrVertex;

    Light *light;
    SceneNode *lightNode;

    MeshPtr mMesh;
    std::vector<const VertexElement *> mVertexElePos;
    std::vector<HardwareVertexBufferSharedPtr> mVertexBufPos;
};

#endif // __TutorialApplication_h_