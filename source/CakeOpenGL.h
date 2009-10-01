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

#ifndef CAKE_OPENGL_H
#define CAKE_OPENGL_H

#include "Cake.h"
#include "NxOgreGLUT.h"

class CakeOpenGL : public Cake, public GLUTRenderSystem
{
  
 public:
  
  CakeOpenGL();
  
 ~CakeOpenGL();
  
  void                createRenderer();
  
  void                destroyRenderer();
  
  void                startRendering();

  void                createScene();

  void                destroyScene();

  void                onFrame(float deltaTime);

  void                renderFrame();
  
  void                drawGrid();
  
  void                onKeyEvent(char key);
  
  void                onMouseDragEvent(int ButtonID, int deltaX, int deltaY);
  
  void                onMouseButtonEvent(int ButtonID, int x, int y);
  
  void                onKeyCallback(char key);
  
  void                onMouseCallback(int ButtonID, int deltaX, int deltaY);
  
  void                orbitCamera(float& yaw, float& pitch, float& distance);
  
  void                onKeyDown(char);
  
  void                drawCube(const NxOgre::Vec3& size, NxOgre::Matrix44& matrix);
  
  void                drawUser();
  
 protected:
  
  NxOgre::Vec3        mCamera;
  
  NxOgre::Vec3        mCameraTarget;
  
  int                 mWindowHandle;

  float               mYaw, mPitch, mDistance;
  
};


#endif