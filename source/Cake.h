/** File: Cake.h
    Created on: 18-Sept-09
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

#ifndef CAKE_H
#define CAKE_H

#include "NxOgre.h"

class Cake : public NxOgre::Callback
{
 public:
  
  Cake()
  {
  }
  
  
 ~Cake()
  {
   destroyScene();
   destroyRenderer();
   destroyNxOgre();
  }
  
  // Create NxOgre World and Scene and initialise PhysX.
  void createNxOgre()
  {
   
   mWorld = NxOgre::World::createWorld();
   mWorld->getRemoteDebugger()->connect();
   
   mTimeController = NxOgre::TimeController::getSingleton();

   NxOgre::SceneDescription scene_description;
   scene_description.mGravity.set(0,-9.8f,0);
   
   mScene = mWorld->createScene(scene_description);
   
   mScene->createSceneGeometry(new NxOgre::PlaneGeometry(0, NxOgre::Vec3(0, 1, 0)));
  
  }
  
  // Destroy NxOgre World and Scene and uninitialise PhysX.
  void destroyNxOgre()
  {
   NxOgre::World::destroyWorld(mWorld);
  }

  void start()
  {
   createNxOgre();
   createRenderer();
   createScene();
   
   startRendering();
  }
  
  // Frame started event.
  void frameStarted(float deltaTime)
  {
   mTimeController->advance(deltaTime);
  }
  
  // Frame ended event.
  void frameEnded()
  {
  }
  
  // User onSceneCreated function; implemented in Cake(RenderSystemName)App.cpp
  virtual void createScene() {}
  
  // User onSceneDestroyed function; implemented in Cake(RenderSystemName)App.cpp
  virtual void destroyScene() {}
  
  // user new frame function; implemented in Cake(RenderSystemName)App.cpp
  virtual void onFrame(float deltaTime) {}
  
  // Implemented by RenderSystem
  virtual void createRenderer() {}
  
  // Implemented by RenderSystem
  virtual void destroyRenderer() {}
  
  // Implemented by RenderSystem
  virtual void startRendering() {}

  // Helper functions.
  NxOgre::World*          getWorld()
  {
   return mWorld;
  }
  
  // Helper functions.
  NxOgre::Scene*          getScene()
  {
   return mScene;
  }
  
  // Helper functions.
  NxOgre::TimeController*   getTimeController()
  {
   return mTimeController;
  }
    
 protected:
  
  NxOgre::World*          mWorld;
  
  NxOgre::Scene*          mScene;
  
  NxOgre::TimeController* mTimeController;
  
};

#endif