/** File: CakeOgreApp.cpp
    Created on: 06-Sept-09
    Author: Robin Southern "betajaen"

    Copyright (c) 2009 Robin Southern

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
    THE SOFTWARE.
*/

#include "Cake.h"
#include "CakeOGRE.h"

using namespace NxOgre;

void CakeOGRE::createScene()
{
 
 Material* default_material = mScene->getMaterial(0);
 default_material->setStaticFriction(0.5f);
 default_material->setDynamicFriction(0.5f);
 
 //mRenderSystem->createBody(new Box(3), Vec3(0, 6, 0), "cube.1m.mesh")->getSceneNode()->setScale(3,3,3);
 
 NxOgre::FluidDescription desc;
 desc.mSimulationMethod = Enums::FluidSimulationMethod_NoParticleInteraction;
 
 mRenderSystem->createFluid(desc);

}

void CakeOGRE::destroyScene()
{
}

void CakeOGRE::onFrame(float deltaTime)
{
}

void CakeOGRE::onKeyEvent(OIS::KeyCode key)
{
 if (key == OIS::KC_F1)
 {
  if (mRenderSystem->hasDebugVisualisation())
   mRenderSystem->setVisualisationMode(Enums::VisualDebugger_ShowNone);
  else
   mRenderSystem->setVisualisationMode(Enums::VisualDebugger_ShowAll);
 }
}

void CakeOGRE::doConfig()
{
 mKeyConfig.CameraForward  = OIS::KC_W;
 mKeyConfig.CameraBackward = OIS::KC_S;
 mKeyConfig.CameraLeft     = OIS::KC_A;
 mKeyConfig.CameraRight    = OIS::KC_D;
 mKeyConfig.CameraUp       = OIS::KC_Q;
 mKeyConfig.CameraDown     = OIS::KC_Z;
}