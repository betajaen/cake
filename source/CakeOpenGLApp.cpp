/** File: OpenGLApp.cpp
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
#include "CakeOpenGL.h"

using namespace NxOgre;

void CakeOpenGL::createScene()
{
 
 NxOgre::Mesh* cone = NxOgre::MeshManager::getSingleton()->load("file://cone.nxs");
 
 Material* default_material = mScene->getMaterial(0);
 default_material->setStaticFriction(0.5f);
 default_material->setDynamicFriction(0.5f);
 
}

void CakeOpenGL::destroyScene()
{
}

void CakeOpenGL::onFrame(float deltaTime)
{
}

void CakeOpenGL::onKeyDown(char key)
{
 if (key == 'p')
 {
  for(GLUTBodyIterator body = getBodies(); body != body.end(); ++body)
   body->addForce(Vec3::random(-70,70,  -70, 70, -70, 70));
 }
 else if (key == 'o')
 {
  float y = 0;
  for(GLUTBodyIterator body = getBodies(); body != body.end(); ++body)
  {
   body->setLinearMomentum(Vec3::ZERO);
   body->setAngularMomentum(Vec3::ZERO);
   body->setGlobalOrientation(Quat::IDENTITY);
   body->setGlobalPosition(Vec3(0, 3 + y, 0));
   y += 1.0f;
  }
 }
}

void CakeOpenGL::drawUser() {}
void CakeOpenGL::onMouseCallback(int,int,int) {}