#include "NxOgre.h"
#include <iostream>
#include <iomanip>

using namespace NxOgre;

World* gWorld;
TimeController* gTimeController;
Scene* gScene;
Actor* gActor;
Timer  gTimer;

void main()
{
 
 gWorld = World::createWorld();
 gTimeController = TimeController::getSingleton();
 
 SceneDescription scene_desc;
 scene_desc.mGravity.zero();
 
 gScene = gWorld->createScene(scene_desc);
 
 RigidBodyDescription desc;
 desc.mLinearDamping = 0.0f;
 
 gActor = gScene->createActor(new Box(1), Vec3::ZERO, desc);
 
 gTimer.reset();
 
 float time = 0;
 float nextSecond = 0;
 unsigned int currentSecond = 0;
 
 Vec3 direction(1, 0, 0);
 float walkSpeed = 1.0f;
 
 FixedTimeStep ts(gScene);
 
 Vec3 velocity = direction * walkSpeed;
 Real speed = velocity.magnitude();
 
 Timer delay;
 float realTime = 0;
 while(time < 10.0f)
 {
  
  while(delay.now() < 0.5);
   delay.reset(); // "Renderer pause".
   
  float dt = gTimer.nowReset(); // Get time passed and reset timer
  realTime += dt;
  
  const TimeStep& ts = gScene->getTimeStep();
  
  time += ts.getModified();       // Add it to time passed
  nextSecond += ts.getModified();   // + ts.getAccumulator();  // Add it to next second.
  
  gActor->setLinearVelocity(velocity);
  
  gTimeController->advance(dt);
 
  if (nextSecond >= 1.0f)
  {
   nextSecond = 0.0f;
   currentSecond++;
   std::cout << "* PhysX Time: " << time << ", Actual Time:" << realTime << ", Diff: " << realTime / time << "%" << std::endl;
   std::cout << "  Actual: " << gActor->getGlobalPosition().x << ", Calculated:" << (speed * time) << ", Diff: " <<  gActor->getGlobalPosition().x / (speed * time) << "%" << std::endl;
  }
  
 }
 
 
 World::destroyWorld();
}