/** File: CakeCakeOpenGL.cpp
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

#include "CakeOpenGL.h"

#include <windows.h>
#include <GL/glut.h>

CakeOpenGL*      gCakeOpenGL_Instance             = 0;
unsigned int gCakeOpenGL_LastMousePositionX   = 0;
unsigned int gCakeOpenGL_LastMousePositionY   = 0;
unsigned int gCakeOpenGL_LastMouseButton      = 0;
bool         gCakeOpenGL_MouseButtonDown      = false;
bool         gCakeOpenGL_MouseButtonJustDown  = false;

int main(int argc, char **argv) 
{
 gCakeOpenGL_Instance = new CakeOpenGL();
 gCakeOpenGL_Instance->start();
}

void CakeOpenGL_ExitCallback()
{
 delete gCakeOpenGL_Instance;
}

void CakeOpenGL_RenderCallback()
{
 gCakeOpenGL_Instance->renderFrame();
}

void CakeOpenGL_IdleCallback()
{
 glutPostRedisplay();
}

void CakeOpenGL_KeyboardCallback(unsigned char key, int x, int y)
{
 
 gCakeOpenGL_Instance->onKeyCallback(key);
 gCakeOpenGL_Instance->onKeyEvent(key);
 
}

void CakeOpenGL_MouseCallback(int button, int state, int x, int y)
{
 
 gCakeOpenGL_MouseButtonDown = (state == GLUT_DOWN);
 
 if (state == GLUT_DOWN)
 {
  gCakeOpenGL_LastMouseButton = button;
  gCakeOpenGL_LastMousePositionX = x;
  gCakeOpenGL_LastMousePositionY = y;
  gCakeOpenGL_MouseButtonJustDown = true;
  gCakeOpenGL_Instance->onMouseButtonEvent(gCakeOpenGL_LastMouseButton = button, x, y);
 }
 
}

void CakeOpenGL_MotionCallback(int x, int y)
{
 
 if (gCakeOpenGL_MouseButtonDown && gCakeOpenGL_MouseButtonJustDown)
 {
  gCakeOpenGL_MouseButtonJustDown = false;
  gCakeOpenGL_LastMousePositionX = x;
  gCakeOpenGL_LastMousePositionY = y;
 }
 
 if (gCakeOpenGL_MouseButtonDown)
 {
   
   int deltaX = gCakeOpenGL_LastMousePositionX - x;
   int deltaY = gCakeOpenGL_LastMousePositionY - y;
   
   gCakeOpenGL_Instance->onMouseDragEvent(gCakeOpenGL_LastMouseButton, deltaX, deltaY);
   
   gCakeOpenGL_LastMousePositionX = x;
   gCakeOpenGL_LastMousePositionY = y;
   
 }
 
}

void CakeOpenGL_PassiveMotionCallback(int x, int y)
{
 
 if (gCakeOpenGL_MouseButtonDown && gCakeOpenGL_MouseButtonJustDown)
 {
  gCakeOpenGL_MouseButtonJustDown = false;
  gCakeOpenGL_LastMousePositionX = x;
  gCakeOpenGL_LastMousePositionY = y;
 }
 
 if (gCakeOpenGL_MouseButtonDown)
 {
   
   int deltaX = gCakeOpenGL_LastMousePositionX - x;
   int deltaY = gCakeOpenGL_LastMousePositionY - y;
   
   gCakeOpenGL_Instance->onMouseDragEvent(gCakeOpenGL_LastMouseButton, deltaX, deltaY);
   
   gCakeOpenGL_LastMousePositionX = x;
   gCakeOpenGL_LastMousePositionY = y;
   
 }
 
}

CakeOpenGL::CakeOpenGL()
: mYaw(-0.785398163 * 2),
  mPitch(0.523598776),
  mDistance(12)
{
 gCakeOpenGL_Instance = this;
}

CakeOpenGL::~CakeOpenGL()
{
}

void CakeOpenGL::createRenderer()
{
 
 glutInitWindowSize(1024, 768);
 glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
 mWindowHandle = glutCreateWindow("Cake");
 glutSetWindow(mWindowHandle);
 glutDisplayFunc(CakeOpenGL_RenderCallback);
 glutIdleFunc(CakeOpenGL_IdleCallback);
 glutKeyboardFunc(CakeOpenGL_KeyboardCallback);
 glutMouseFunc(CakeOpenGL_MouseCallback);
 glutMotionFunc(CakeOpenGL_MotionCallback);
 glutPassiveMotionFunc(CakeOpenGL_PassiveMotionCallback);
 atexit(CakeOpenGL_ExitCallback);
 
 glClearColor(0.1337f, 0.1337f, 0.1337f, 0.1337f);
 glClearDepth(1.0f);

 glEnable(GL_DEPTH_TEST);
 glDepthFunc(GL_LEQUAL);

 glShadeModel(GL_SMOOTH);

 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

 // Enable light and set up 2 light sources (GL_LIGHT0 and GL_LIGHT1)
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);

 float ambientLight0[] = { 0.4f, 0.4f, 0.4f, 1.0f };
 float diffuseLight0[] = { 0.8f, 0.8f, 0.8f, 1.0f };
 float specularLight0[] = { 0.7f, 0.7f, 0.7f, 1.0f };
 float position0[] = { -25, 15, -25, 1.0f };	

 glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
 glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
 glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
 glLightfv(GL_LIGHT0, GL_POSITION, position0);

 orbitCamera(mYaw, mPitch, mDistance);
 
#ifdef _WIN32
 HWND wnd = WindowFromDC(wglGetCurrentDC());
 HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL);
 SetClassLong ( wnd , GCL_HICON, (LONG)LoadIcon (hInst, MAKEINTRESOURCE (100)));
#else
 // ...
#endif
 
}

void CakeOpenGL::destroyRenderer()
{
}

void CakeOpenGL::startRendering()
{
 gCakeOpenGL_Instance = this;
 glutMainLoop();
}

void CakeOpenGL::renderFrame()
{
 onFrame(1.0f/60.0f);
 frameStarted(1.0f/60.0f);
 
 ///////////////////
 
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(60.0f, (float)glutGet(GLUT_WINDOW_WIDTH)/(float)glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 1000.0f);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 
 gluLookAt(mCamera.x, mCamera.y, mCamera.z, mCameraTarget.x, mCameraTarget.y, mCameraTarget.z, 0.0f, 1.0f, 0.0f);
 
 glDisable(GL_LIGHTING);
 drawGrid();
 glEnable(GL_LIGHTING);

 drawBodies();
 
 drawUser();
 
 ///////////////////
 
 frameEnded();
 
 glutSwapBuffers();
}

void CakeOpenGL::drawGrid()
{
 glPushMatrix();
 glBegin(GL_LINES);
 
 for(int i=0;i<=50;i++)
 {
  
  if (i==25)
   glColor3f(.3,.3,.6);
  else
   glColor3f(.2,.2,.2);
  
  glVertex3f(-25 + i,0,-25);
  glVertex3f(-25 + i,0,25);
  
  if (i==25)
   glColor3f(.6,.3,.3);
  else
   glColor3f(.2,.2,.2);
  
  glVertex3f(-25,0,-25 + i);
  glVertex3f(25,0,-25 + i);
  
 }

 glColor3f(.3,.6,.3);
 glVertex3f(0,0,0);
 glColor3f(.3,.6,.3);
 glVertex3f(0,1,0);
 
 
 glEnd();
 glPopMatrix();
}

void CakeOpenGL::drawCube(const NxOgre::Vec3& size, NxOgre::Matrix44& matrix )
{
 
 glPushMatrix();
 
 float glMat[16];
 matrix.columnMajor(glMat);
 glMultMatrixf(glMat);
 glScalef(size.x, size.y, size.z);
 glutSolidCube(1);
 
 glPopMatrix();
 
}

void CakeOpenGL::onKeyEvent(char key)
{
 if (key == 27)
 {
  exit(0);
  return;
 }
 
 onKeyDown(key);
}

void CakeOpenGL::onMouseDragEvent(int ButtonID, int deltaX, int deltaY)
{
 if (ButtonID == GLUT_RIGHT_BUTTON)
 {
  mYaw   += (float(deltaX) * 0.0075f);
  mPitch -= (float(deltaY) * 0.0075f);
 }
 
 if (ButtonID == GLUT_MIDDLE_BUTTON)
 {
  mCameraTarget.x += deltaX * 0.0075f;
  mCameraTarget.z += deltaY * 0.0075f;

 }

 orbitCamera(mYaw, mPitch, mDistance);
 onMouseCallback(ButtonID, deltaX, deltaY);
 
}



void CakeOpenGL::onMouseButtonEvent(int ButtonID, int x, int y)
{
}

void CakeOpenGL::onKeyCallback(char key)
{
 onKeyDown(key);
}

void CakeOpenGL::orbitCamera(float& yaw, float& pitch, float& distance)
{
 if (yaw < -NxOgre::Math::Pi)
  yaw = NxOgre::Math::Pi;
 else if (yaw > NxOgre::Math::Pi)
  yaw = -NxOgre::Math::Pi;

 if (pitch < 0)
  pitch = 0;
 else if (pitch > 1.2f)
  pitch = 1.2f;

 mCamera.x = mCameraTarget.x + (sin(yaw) * distance);
 mCamera.y = tan(pitch) * distance;
 mCamera.z = mCameraTarget.z + (cos(yaw) * distance);
}
