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

Fluid* fluid;
FluidEmitter* emitter;

Ogre::ParticleSystem* frank;

void CakeOGRE::createScene()
{
  
 Material* default_material = mScene->getMaterial(0);
 default_material->setStaticFriction(0.5f);
 default_material->setDynamicFriction(0.5f);
 
 //mRenderSystem->createBody(new Box(3), Vec3(0, 6, 0), "cube.1m.mesh")->getSceneNode()->setScale(3,3,3);
  
 NxOgre::FluidDescription desc;
 desc.mMaxParticles = 15000;
 desc.mKernelRadiusMultiplier = 2.0f;
 desc.mRestParticlesPerMetre = 7.0f;
 desc.mMotionLimitMultiplier = 3.0f;
 desc.mPacketSizeMultiplier = 8;
 desc.mCollisionDistanceMultiplier = 0.1f;
 desc.mStiffness = 50.0f;
 desc.mViscosity = 40.0f;
 desc.mRestDensity = 1000.0f;
 desc.mSimulationMethod = Enums::FluidSimulationMethod_SPH;
 desc.mFlags |= Enums::FluidFlags_Hardware;
 desc.mFlags |= Enums::FluidFlags_DisableGravity;
  
 fluid = mRenderSystem->createFluid(desc, "Gas", OGRE3DFluidType_OgreParticle);
 
 FluidEmitterDescription edesc;
 edesc.mPose.set(0, 2, 0);
 edesc.mParticleLifetime = 10.0;
 edesc.mRate = 300;
 edesc.mType = Enums::FluidEmitterType_Pressure;
 edesc.mRandomAngle = 4.5f;
 edesc.mRandomPosition.set(0.05f, 0.05f, 1.0f);
 edesc.mReplusionCoefficient = 0.8f;
 edesc.mDimensionX = 1.0f;
 edesc.mDimensionY = 1.0f;
 
 emitter = fluid->createEmitter(edesc);
 
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
 
 if (key == OIS::KC_8)
  frank->createParticle();
 
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