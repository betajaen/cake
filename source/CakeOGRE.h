/** File: FlourOpenGL.h
    Created on: 11-Sept-09
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

#ifndef CAKE_OGRE_H
#define CAKE_OGRE_H

#include "Cake.h"
#include "Ogrelicious.h"
#include "NxOgreOGRE3D.h"

class CakeOGRE : public Cake
{
  
 public:
  
  CakeOGRE();
  
 ~CakeOGRE();
  
  void                createRenderer();
  
  void                destroyRenderer();
  
  void                startRendering();
  
  void                createScene();
  
  void                destroyScene();
  
  void                onFrame(float deltaTime);
  
  void                onFrameEvent(const Ogre::Real&);
  
  void                onCameraKeysDown(Ogrelicious::KeyEvent*);
  
  void                onKeyEvent(Ogrelicious::KeyEvent*);
  
  void                onKeyEvent(OIS::KeyCode key);
  
  void                onMouseEvent(Ogrelicious::MouseEvent*);
  
  void                onMouseButtonPressed(Ogrelicious::MouseEvent*);
  
  void                onMouseButtonReleased(Ogrelicious::MouseEvent*);
  
  void                doConfig();
  
 protected:
  
  Ogre::Root*                     mRoot;
  Ogre::SceneManager*             mSceneMgr;
  Ogre::Light*                    mLight;
  
  Ogrelicious::SmartWindow        mWindow;
  Ogrelicious::SmartCamera        mCamera;
  Ogrelicious::SmartConfig        mConfig;
  
  OGRE3DRenderSystem*             mRenderSystem;
  
  NxOgre::Actor*                  mCameraActor;
  NxOgre::Ray                     mCameraRay;
  NxOgre::RaycastHit              mCameraHit;
  NxOgre::SimplePlane             mSimpleGroundPlane;
  
  struct
  {
   int CameraForward;
   int CameraBackward;
   int CameraLeft;
   int CameraRight;
   int CameraUp;
   int CameraDown;
  } mKeyConfig;
 
};


#endif