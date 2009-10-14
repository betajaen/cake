/** File: CakeCakeOGRE.cpp
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

#include "CakeOGRE.h"
#include "Ogrelicious.h"

using namespace Ogrelicious;
using namespace Ogre;

CakeOGRE* gCakeOGRE_Instance = 0;

int main(int argc, char **argv) 
{
 gCakeOGRE_Instance = new CakeOGRE();
 gCakeOGRE_Instance->start();
 delete gCakeOGRE_Instance;
}

CakeOGRE::CakeOGRE()
{
 doConfig();
}

CakeOGRE::~CakeOGRE()
{
}

void CakeOGRE::createRenderer()
{
 
 // Start Ogre and Ogrelicious.
 mRoot = startOgre();
 
#ifdef _DEBUG
 _Plugins("RenderSystem: Direct3D9, Plugin_CgProgramManager_d.dll").load(_Everything);
#else
 _Plugins("RenderSystem: Direct3D9, Plugin_CgProgramManager.dll").load(_Everything);
#endif

 _RenderSystems("all").nominate(_First);

 initialiseOgre(_NoAutoWindow);

 mWindow = _Window("Ogrelicious, yummy!")
               .left(_HorizontallyCenter)
               .top(_VerticallyCenter)
               .width(1024)
               .height(768)
               .depth(32)
               .fullscreen(false);

 
 // Initialise Ogre with no window.
 initialiseOgre(_NoAutoWindow);
 
 // Create the SceneManager
 mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "Cake");
 
 // Create, configure the window then create it.
 mWindow = mConfig
            .toSmartWindow("Cake")
            .title("CakeOGRE")
            .left(_HorizontallyCenter)
            .top(_VerticallyCenter)
            .width(Core::getScreenWidth() - 200)
            .height(Core::getScreenHeight() - 200)
            .vsync(true)
            .create(_OgreOverlayMouse);
 #ifdef WIN32
        HWND hwnd;
        mWindow->getCustomAttribute("WINDOW", &hwnd);
        HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL);
        SetClassLong (hwnd, GCL_HICON, 
               (LONG)LoadIcon (hInst, MAKEINTRESOURCE (100)));
 #endif

 NxOgre::RigidBodyDescription cameraActorDescription;
 cameraActorDescription.mMass = 1;                                              // 1 kilogram is enough.
 cameraActorDescription.mLinearDamping = 2.5f;                                  // Increase the damping factor for linear momentum.
 cameraActorDescription.mBodyFlags |= NxOgre::Enums::BodyFlags_DisableGravity;  // Disable gravity.
 cameraActorDescription.mBodyFlags |= NxOgre::Enums::BodyFlags_FreezeRotation;  // Disable all angular movement.
 
 mCameraActor = mScene->createActor(new NxOgre::Sphere(0.25f), NxOgre::Vec3(10,25,10), cameraActorDescription);
 
 mCamera = _Camera("Camera", mSceneMgr)
              .farClip(25000)
              .nearClip(0.05)
              .position(mCameraActor->getGlobalPosition().as<Ogre::Vector3>())
              .look(0,0,0);

 // Create the viewport and set the background to a very dark gray colour.
 mWindow.add(mCamera).background(Ogre::ColourValue(0.018,0.018,0.018));
 mCamera->setAspectRatio( float(mWindow.width()) / float(mWindow.height()) );
 
 // Load and initialise the resources.
 _ResourceGroup("General") += "media/";
 _ResourceGroups("all").init();
 
 // Lighting
 mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2137f,0.2137f,0.2137f,1));
 mLight = mSceneMgr->createLight("Light");
 mLight->setDiffuseColour(Ogre::ColourValue(1, 1, 1));
 mLight->setType(Light::LT_SPOTLIGHT);
 mLight->setSpotlightInnerAngle(Degree(25));
 mLight->setSpotlightOuterAngle(Degree(45));
 mLight->setAttenuation(75, 1, 1, 1);
 mLight->setDirection(0,0,-1);
 mLight->setCastShadows(true);
 Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightNode");
 lightNode->attachObject(mLight);
 lightNode->setPosition(Vector3(-10, 32, 32));
 mLight->setDirection(-lightNode->getPosition().normalisedCopy());
 
 // Shadows
 mSceneMgr->setShadowTextureSelfShadow(true);
 mSceneMgr->setShadowTextureCasterMaterial("shadow_caster");
#define BETAJAENS_HARDWARE
#ifdef BETAJAENS_HARDWARE
 mSceneMgr->setShadowTextureCount(6);
 mSceneMgr->setShadowTextureSize(2048);
#else
 mSceneMgr->setShadowTextureCount(4);
 mSceneMgr->setShadowTextureSize(512);
#endif
 mSceneMgr->setShadowTexturePixelFormat(PF_FLOAT16_RGB);
 mSceneMgr->setShadowCasterRenderBackFaces(false);
 mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);
 
 // Floor
 Ogre::Plane plane;
 plane.normal = Ogre::Vector3::UNIT_Y;
 plane.d = 0;
 Ogre::MeshManager::getSingleton().createPlane("SandBox-Floor.mesh",
                                               Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
                                               512, 512, 8, 8, true, 1, 128, 128, Ogre::Vector3::UNIT_Z);
 Entity* floorEntity = mSceneMgr->createEntity("SandBox-Floor", "SandBox-Floor.mesh" );
 floorEntity->setMaterialName("refPlane");
 mSceneMgr->getRootSceneNode()->attachObject(floorEntity);

 
 // Events
 mWindow.onUnload               += _Callback(&Core::SafeShutdown);
 mWindow.onKeyPressed           += _Callback(this, &CakeOGRE::onKeyEvent);
 mWindow.onMouseButtonPressed   += _Callback(this, &CakeOGRE::onMouseButtonPressed);
 mWindow.onMouseButtonReleased  += _Callback(this, &CakeOGRE::onMouseButtonReleased);
 mWindow.onMouseMoved           += _Callback(this, &CakeOGRE::onMouseEvent);
 mWindow.watchKeys(
                   mKeyConfig.CameraForward,
                   mKeyConfig.CameraBackward,
                   mKeyConfig.CameraLeft,
                   mKeyConfig.CameraRight,
                   mKeyConfig.CameraUp,
                   mKeyConfig.CameraDown,
                   OIS::KC_F10,
                   OIS::KC_F9,
                   OIS::KC_F8,
                   _Callback(this, &CakeOGRE::onCameraKeysDown)
                  );
 
 _Events()->onBeginFrame        += _Callback(this, &CakeOGRE::onFrameEvent);
 
 mRenderSystem = new OGRE3DRenderSystem(mScene, mSceneMgr);
}

void CakeOGRE::destroyRenderer()
{
 delete mRenderSystem;
 stopOgre();
}

void CakeOGRE::startRendering()
{
 mRoot->startRendering();
}

void CakeOGRE::onFrameEvent(const Ogre::Real& deltaTime)
{

 //for (unsigned int i=0; i < 16000000;i++); // Mr Sleep.

 std::stringstream ss;
 ss << "CakeOGRE - Gfx: " << mWindow->getAverageFPS() << "Hz, Acm: " << mScene->getTimeStep().getAccumulator() << "s, SST: " << mScene->getTimeStep().getSubSteps() << ", Mod:" << 1 / mScene->getTimeStep().getModified() << ", Alpha:" << mScene->getTimeStep().getAlpha();
 mWindow.title(ss.str());

 onFrame(deltaTime);
 frameStarted(deltaTime);
 mCamera->setPosition(mCameraActor->getGlobalPosition().as<Ogre::Vector3>());
 frameEnded();
}

void CakeOGRE::onKeyEvent(Ogrelicious::KeyEvent* keyEvent)
{
 if (keyEvent->keyPressed == OIS::KC_ESCAPE)
  Core::getSingletonPtr()->SafeShutdown();
 
 onKeyEvent(keyEvent->keyPressed);
}

void CakeOGRE::onMouseEvent(Ogrelicious::MouseEvent* mouseEvent)
{
 if (mouseEvent->button.Right)
 {
  if (mouseEvent->x.delta)
   mCamera->yaw(Ogre::Degree(mouseEvent->x.delta * -0.13f));
  if (mouseEvent->y.delta)
   mCamera->pitch(Ogre::Degree(mouseEvent->y.delta * -0.13f));
  return;
 }
}

void CakeOGRE::onMouseButtonPressed(Ogrelicious::MouseEvent* mouseEvent)
{
}

void CakeOGRE::onMouseButtonReleased(Ogrelicious::MouseEvent*)
{
}

void CakeOGRE::onCameraKeysDown(Ogrelicious::KeyEvent* keyEvent)
{
 
 static const float cameraDelta = 10.0f;
 
 // Our CameraActor has no direction, but the Camera does. So we use that.
 NxOgre::Quat quat(mCamera->getOrientation()); // Note: NxOgre's quaternion class will auto-convert any quaternion class that has public w,x,y,z variables.

 if (keyEvent->keyPressed == mKeyConfig.CameraForward)
  mCameraActor->addForce(NxOgre::Vec3(0,0,-cameraDelta) * quat);

 if (keyEvent->keyPressed == mKeyConfig.CameraBackward)
  mCameraActor->addForce(NxOgre::Vec3(0,0,cameraDelta) * quat);
 
 if (keyEvent->keyPressed == mKeyConfig.CameraLeft)
  mCameraActor->addForce(NxOgre::Vec3(-cameraDelta,0,0) * quat);
 
 if (keyEvent->keyPressed == mKeyConfig.CameraRight)
  mCameraActor->addForce(NxOgre::Vec3(cameraDelta,0,0) * quat);
 
 if (keyEvent->keyPressed == mKeyConfig.CameraUp)
  mCameraActor->addForce(NxOgre::Vec3(0,cameraDelta,0) * quat);
 
 if (keyEvent->keyPressed == mKeyConfig.CameraDown)
  mCameraActor->addForce(NxOgre::Vec3(0,-cameraDelta,0) * quat);
 
 if (keyEvent->keyPressed == OIS::KC_F10)
 {
  for(OGRE3DRenderSystem::BodyIterator body = mRenderSystem->getBodies(); body != body.end(); body++)
  {
   body->addForce(NxOgre::Vec3::random(-100, 100,  -100, 100,  -100, 100) * body->getMass());
  }
 }
 
 if (keyEvent->keyPressed == OIS::KC_F9)
 {
  int i=0;
  for(OGRE3DRenderSystem::BodyIterator body = mRenderSystem->getBodies(); body != body.end(); body++)
  {
   body->setGlobalPosition(NxOgre::Vec3(0, 0.5 + i, 0));
   i++;
  }
 }
 
 if (keyEvent->keyPressed == OIS::KC_F8)
 {
  mRenderSystem->createBody(new NxOgre::Box(1), NxOgre::Vec3(0, 9.5, 0), "cube.1m.mesh");
 }

}
