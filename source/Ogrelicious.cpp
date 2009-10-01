/*
 * Ogrelicious
 * 
 * File:    Ogrelicious.cpp
 * Version: 0.0.9
 *
 * Copyright (c) 2008 Robin "betajaen" Southern.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Ogrelicious.h"
#include "Ogre.h"
#include "OgrePlugin.h"
#include "OgreFileSystem.h"
#include "OgreFontManager.h"
#include <sstream>
#include <fstream>

#define _OgreliciousDebug(S) std::cout << "** Debug ** " << S << std::endl;
#define _OgreliciousToString(t) Ogre::StringConverter::toString(t)
static unsigned int _OgreliciousNextHandleID = 1;
static unsigned int _OgreliciousNextOverlayID = 1;
template<> ::Ogrelicious::Core* Ogre::Singleton<::Ogrelicious::Core>::ms_Singleton = 0;
template<> ::Ogrelicious::EventSystem* ::Ogrelicious::OptionalSingleton<::Ogrelicious::EventSystem>::sInstance = 0;
template<> ::Ogrelicious::SmartInputSystem* ::Ogrelicious::OptionalSingleton<::Ogrelicious::SmartInputSystem>::sInstance = 0;

struct __OgreliciousGC__
{
 ~__OgreliciousGC__()
 {
  if (::Ogrelicious::Core::getSingletonPtr())
   ::Ogrelicious::Core::uninit();
 }
} ___OgreliciousGC___;


static const unsigned char OgreliciousMouseGlyph[256] =
{
#define _ 0
#define C 1
#define O 2
//      |1|2|3|4|5|6|7|8|9|X|1|2|3|4|5|6
         3,O,_,_,_,_,_,_,_,_,_,_,_,_,_,_, // 1
         C,3,O,O,_,_,_,_,_,_,_,_,_,_,_,_, // 2
         _,C,3,3,O,O,_,_,_,_,_,_,_,_,_,_, // 3
         _,C,3,3,3,3,O,O,_,_,_,_,_,_,_,_, // 4
         _,_,C,3,3,3,3,3,O,O,_,_,_,_,_,_, // 5
         _,_,C,3,3,3,3,3,C,C,_,_,_,_,_,_, // 6
         _,_,_,C,3,3,3,O,_,_,_,_,_,_,_,_, // 7
         _,_,_,C,3,3,C,3,O,_,_,_,_,_,_,_, // 8
         _,_,_,_,C,3,_,C,3,O,_,_,_,_,_,_, // 9
         _,_,_,_,C,3,_,_,C,3,O,_,_,_,_,_, // X
         _,_,_,_,_,_,_,_,_,C,_,_,_,_,_,_, // 1
         _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_, // 2
         _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_, // 3
         _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_, // 4
         _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_, // 5
         _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_, // 6
#undef _
#undef C
#undef O
};
#define OgreliciousMouseGlyph0Colour(X) {(*X++)=0;(*X++)=0;(*X++)=0;(*X++)=0;}
#define OgreliciousMouseGlyph1Colour(X) {(*X++)=0;(*X++)=0;(*X++)=0;(*X++)=255;}
#define OgreliciousMouseGlyph2Colour(X) {(*X++)=255;(*X++)=255;(*X++)=255;(*X++)=255;}
#define OgreliciousMouseGlyph3Colour(X) {(*X++)=64;(*X++)=64;(*X++)=254;(*X++)=255;}

// FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS 
//FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS FUNCTIONS 

namespace Ogrelicious
{

Ogre::Root* startOgre(const std::string& log_name)
{
 Ogre::Root* root = Ogre::Root::getSingletonPtr();
 if (root == 0) root = new Ogre::Root("", "", log_name);
 Core::init();
 return root;
}

void stopOgre()
{
 Ogre::Root* root = Ogre::Root::getSingletonPtr();
 if (root != 0)
  delete root;
 Core::uninit();
}

void initialiseOgre(bool auto_create_window, const std::string& window_name)
{
 Ogre::Root* root = Ogre::Root::getSingletonPtr();
 if (root != 0)
  root->initialise(auto_create_window, window_name);
}


bool insCmp(const std::string& a, const std::string& b)
{
 static std::string sa, sb;
 sa = a;
 sb = b;
 Ogre::StringUtil::toLowerCase(sa);
 Ogre::StringUtil::toLowerCase(sb);
 return sa == sb;
}

bool insCmpS(const std::string& a, const std::string& b)
{
 static std::string sa, sb;
 sa = a;
 sb = b;
 Ogre::StringUtil::toLowerCase(sa);
 return sa == sb;
}

Ogre::StringVector csa_get(const Ogre::String& csa)
{
 Ogre::StringVector strings = Ogre::StringUtil::split(csa, ",");
 for (Ogre::StringVector::iterator it = strings.begin(); it != strings.end();it++)
  Ogre::StringUtil::trim((*it));
 return strings;
}

Ogre::ColourValue ColourToRGBA(Colour col, Ogre::Real Alpha)
{
 static int r, g, b;
 b =  col & 0xFF;
 g = (col >> 8) & 0xFF;
 r = (col >> 16) & 0xFF;
 return Ogre::ColourValue(r / 255.0f, g / 255.0f, b / 255.0f, Alpha);
}

}
// Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious 
//Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious Ogrelicious 

namespace Ogrelicious
{
  Core::Core(bool init_event_system)
  {
   if (init_event_system)
   {
    EventSystem::Instance();
    SmartInputSystem::Instance();
   }
  }
  
  Core::~Core(void)
  {
   EventSystem::KillInstance();
   SmartInputSystem::KillInstance();
  }
  
  Core* Core::getSingletonPtr(void)
  {
    return ms_Singleton;
  }
  
  Core& Core::getSingleton(void)
  {
    assert(ms_Singleton);
    return (*ms_Singleton);
  }
  
  void Core::init(bool init_event_system)
  {
   if (Core::ms_Singleton == 0)
    Core::ms_Singleton = new Core(init_event_system);
  }
  
  void Core::uninit()
  {
   delete Core::ms_Singleton;
   Core::ms_Singleton = 0;
  }
  
  void Core::SafeShutdown()
  {
   EventSystem::Instance()->getFrameEventListener()->setNextReturnValue(false);
  }

  unsigned int Core::getScreenWidth()
  {
   return GetSystemMetrics(SM_CXSCREEN);
  }
  
  unsigned int Core::getScreenHeight()
  {
   return GetSystemMetrics(SM_CYSCREEN);
  }

}

// EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS 
//EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS EVENTS 

namespace Ogrelicious
{

EventSystem::EventSystem()
: mFrameEventListener(new FrameEventListener()),
  mRenderWindowEventListener(new RenderWindowEventListener()),
  mSmartEvents(new SmartEvents(0))
{
 onBeginFrame._ = mSmartEvents;
 onEndFrame._ = mSmartEvents;
}

EventSystem::~EventSystem()
{
 // Everything else is managed by SharedPtrs. No cleanup!
}

void EventSystem::addFunctor(Ogre::uint handle_id, Ogre::uint channel_id, const Ogre::SharedPtr<Functor>& functor)
{
 if (channel_id == _onBeginFrame)
  mFrameEventListener->addBegin(handle_id);
 else if (channel_id == _onEndFrame)
  mFrameEventListener->addEnd(handle_id);
 mHandles[handle_id][channel_id].push_back(functor);
}

void EventSystem::removeHandle(Ogre::uint handle_id)
{
}

void EventSystem::fire(Ogre::uint handle_id, Ogre::uint channel_id, void* data)
{
 Handles::iterator handles_it = mHandles.find(handle_id);
 if (handles_it == mHandles.end())
  return;
 Channels::iterator channels_it = (*handles_it).second.find(channel_id);
 if (channels_it == (*handles_it).second.end())
  return;
 for (Functors::iterator functors_it = (*channels_it).second.begin(); functors_it != (*channels_it).second.end(); functors_it++)
  (*functors_it)->fire(data);
}


Ogre::SharedPtr<FrameEventListener>& EventSystem::getFrameEventListener()
{
 return mFrameEventListener;
}

Ogre::SharedPtr<RenderWindowEventListener>& EventSystem::getRenderWindowEventListener()
{
 return mRenderWindowEventListener;
}

RenderWindowEventListener::RenderWindowEventListener()
{
}

RenderWindowEventListener::~RenderWindowEventListener()
{
 for(MapIt it = mEvents.begin();it != mEvents.end();it++)
  ::Ogre::WindowEventUtilities::removeWindowEventListener((*it).first, this);
}

void RenderWindowEventListener::set(Ogre::uint handle, Ogre::RenderWindow* window)
{
 mEvents[window] = handle;
 Ogre::WindowEventUtilities::addWindowEventListener(window, this);
}

void RenderWindowEventListener::remove(Ogre::uint handle)
{
 for(MapIt it = mEvents.begin();it != mEvents.end();it++)
 {
  if ((*it).second == handle)
  {
   Ogre::WindowEventUtilities::removeWindowEventListener((*it).first, this);
   mEvents.erase(it);
   return;
  }
 }
}

void RenderWindowEventListener::windowMoved(Ogre::RenderWindow* window)
{
 MapIt it = mEvents.find(window);
 if (it != mEvents.end())
  EventSystem::Instance()->fire((*it).second, _onMove);
}

void RenderWindowEventListener::windowResized(Ogre::RenderWindow* window)
{
 MapIt it = mEvents.find(window);
 if (it != mEvents.end())
  EventSystem::Instance()->fire((*it).second, _onResize);
}

void RenderWindowEventListener::windowClosed(Ogre::RenderWindow* window)
{
 MapIt it = mEvents.find(window);
 if (it != mEvents.end())
  EventSystem::Instance()->fire((*it).second, _onUnload);
}

void RenderWindowEventListener::windowFocusChange(Ogre::RenderWindow* window)
{
 MapIt it = mEvents.find(window);
 if (it != mEvents.end())
  EventSystem::Instance()->fire((*it).second, _onFocus);
}

FrameEventListener::FrameEventListener() : mNextReturnValue(true)
{
 if (Ogre::Root::getSingletonPtr())
  Ogre::Root::getSingletonPtr()->addFrameListener(this);
 mCurrentTimestep = (Ogre::Real*) malloc(sizeof(Ogre::Real));
 (*mCurrentTimestep) = 0;
}

FrameEventListener::~FrameEventListener()
{
 if (Ogre::Root::getSingletonPtr())
  Ogre::Root::getSingletonPtr()->removeFrameListener(this);
 free(mCurrentTimestep);
}

void FrameEventListener::addBegin(Ogre::uint handle)
{
 mBeginEvents.push_back(handle);
}

void FrameEventListener::addEnd(Ogre::uint handle)
{
 mEndEvents.push_back(handle);
}
#if 0
void FrameEventListener::remove(Ogre::uint handle)
{
 for (VectorIt it = mEvents.begin(); it != mEvents.end();it++)
  if ((*it) == handle)
   mEvents.erase(it);
}
#endif
void FrameEventListener::setNextReturnValue(bool b)
{
 mNextReturnValue = b;
}

bool FrameEventListener::frameStarted(const Ogre::FrameEvent& evt)
{
 SmartInputSystem::Instance()->capture();
 static EventSystem* es = EventSystem::Instance();
 (*mCurrentTimestep) = evt.timeSinceLastFrame;
 for (VectorIt it = mBeginEvents.begin(); it != mBeginEvents.end();it++)
  es->fire( *it, ::Ogrelicious::_onBeginFrame, mCurrentTimestep);
 return mNextReturnValue;
}

bool FrameEventListener::frameEnded(const Ogre::FrameEvent& evt)
{
 static EventSystem* es = EventSystem::Instance();
 (*mCurrentTimestep) = evt.timeSinceLastFrame;
 for (VectorIt it = mEndEvents.begin(); it != mEndEvents.end();it++)
  es->fire( *it, ::Ogrelicious::_onEndFrame, mCurrentTimestep);
 return mNextReturnValue;
}

SmartEvents::SmartEvents(unsigned int handle_id) : mHandle(handle_id)
{
}

void SmartEvents::fire(unsigned int channel)
{
 EventSystem::Instance()->fire(mHandle, channel);
}

void SmartEvents::push(unsigned int channel, const Ogre::SharedPtr<Functor>& functor)
{
 EventSystem::Instance()->addFunctor(mHandle, channel, functor);
}

EventSystem* _Events()
{
 return EventSystem::Instance();
}

#ifdef OGRELICIOUS_LOVES_OIS

OISInputSystem::OISInputSystem()
{
 mNullDevice = new OISNullDevice();
 mMouseEvent = new MouseEvent();
 mKeyEvent = new KeyEvent();
}

OISInputSystem::~OISInputSystem()
{
 delete mNullDevice;
 delete mMouseEvent;
 delete mKeyEvent;
}

void OISInputSystem::capture()
{
 for (BindingsIterator it = mBindings.begin(); it != mBindings.end(); it++)
 {
  // Capture and fire all/any events for mouse, keyboard and joystick.
  for (unsigned int i=0;i < 3;i++)
    (*it)->mDevices[i]->capture();
  // Capture and fire specific key events.
  OIS::Keyboard* keyboard = static_cast<OIS::Keyboard*>((*it)->mDevices[0]);

  OIS::Mouse* mouse = static_cast<OIS::Mouse*>((*it)->mDevices[1]);
  

  if ((*it)->mWatchedKeys.size())
  {
   mKeyEvent->isDown = true;
   for (WindowBinding::HandleKeyIterator hkit = (*it)->mWatchedKeys.begin(); hkit != (*it)->mWatchedKeys.end(); hkit++)
   {
    if (keyboard->isKeyDown( OIS::KeyCode((*hkit).mKeyCode)))
    {
     mKeyEvent->keyPressed = Ogrelicious::KeyCode((*hkit).mKeyCode);
     mKeyEvent->ascii = (*hkit).mKeyCode;
     EventSystem::Instance()->fire( (*hkit).mHandle, (*hkit).mKeyCode, mKeyEvent); 
    }
   }
  }
 }
}

void OISInputSystem::addWindow(Ogre::RenderWindow* render_window, unsigned int event_handle, bool exclusiveMouse)
{
 if (render_window == 0)
  return;

 for (BindingsIterator it = mBindings.begin(); it != mBindings.end(); it++)
  if ((*it)->mWindow == render_window)
   return;

 WindowBinding* binding = new WindowBinding();
 binding->mHandle = event_handle;
 binding->mWindow = render_window;

 OIS::ParamList pl;
 size_t windowHnd = 0;
 std::ostringstream windowHndStr;
 render_window->getCustomAttribute("WINDOW", &windowHnd);
 windowHndStr << windowHnd;
 pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
if (exclusiveMouse)
{
#if defined OIS_WIN32_PLATFORM 
  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" ))); 
  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE"))); 
  pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND"))); 
  pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE"))); 
#elif defined OIS_LINUX_PLATFORM 
  pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false"))); 
  pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false"))); 
  pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false"))); 
  pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true"))); 
#endif
}

 binding->mInputSystem = OIS::InputManager::createInputSystem(pl);

 for (unsigned int i=0;i < 3;i++)
  binding->mDevices[i] = mNullDevice;

 if (binding->mInputSystem->numKeyboards() > 0)
 {
  OIS::Keyboard* keyboard = (OIS::Keyboard*) binding->mInputSystem->createInputObject(OIS::OISKeyboard, true);
  keyboard->setBuffered(true);
  keyboard->setEventCallback(this);
  binding->mDevices[0] = keyboard;
 }

 if (binding->mInputSystem->numMice() > 0)
 {
  OIS::Mouse* mouse = (OIS::Mouse*) binding->mInputSystem->createInputObject(OIS::OISMouse, true);
  mouse->setEventCallback(this);
  binding->mDevices[1] = mouse;
 }

 if (binding->mInputSystem->numJoySticks() > 0)
 {
  OIS::JoyStick* joystick = (OIS::JoyStick*) binding->mInputSystem->createInputObject(OIS::OISJoyStick, true);
  joystick->setBuffered(true);
  joystick->setEventCallback(this);
  binding->mDevices[2] = joystick;
 }

 mBindings.push_back(binding);

}

void OISInputSystem::removeWindow(Ogre::RenderWindow* window)
{
 // BLAHHARHARH!
}

bool OISInputSystem::keyDown(const OIS::KeyCode& kc) const
{
 return static_cast<OIS::Keyboard*>(mBindings[0]->mDevices[0])->isKeyDown(kc);
}

bool OISInputSystem::keyPressed(const OIS::KeyEvent &arg)
{
 mKeyEvent->keyPressed = arg.key;
 mKeyEvent->ascii = arg.text;
 mKeyEvent->isDown = true;
 for (BindingsIterator it = mBindings.begin(); it != mBindings.end(); it++)
  if (arg.device == (*it)->mDevices[0])
   EventSystem::Instance()->fire((*it)->mHandle, _onKeyPressed, mKeyEvent);
 return true;
}

bool OISInputSystem::keyReleased(const OIS::KeyEvent &arg)
{
 mKeyEvent->keyPressed = arg.key;
 mKeyEvent->ascii = arg.text;
 mKeyEvent->isDown = false;
 for (BindingsIterator it = mBindings.begin(); it != mBindings.end(); it++)
  if (arg.device == (*it)->mDevices[0])
   EventSystem::Instance()->fire((*it)->mHandle, _onKeyReleased, mKeyEvent);
 return true;
}

bool OISInputSystem::mouseMoved(const OIS::MouseEvent &arg)
{
 char b = (char) arg.state.buttons; memcpy(&mMouseEvent->button, &b, sizeof(char)); // Evil.
 mMouseEvent->x.position = arg.state.X.abs;
 mMouseEvent->x.delta = arg.state.X.rel;
 mMouseEvent->y.position = arg.state.Y.abs;
 mMouseEvent->y.delta = arg.state.Y.rel;
 mMouseEvent->wheel.position = arg.state.Z.abs;
 mMouseEvent->wheel.delta = arg.state.Z.rel;
 for (BindingsIterator it = mBindings.begin(); it != mBindings.end(); it++)
  if (arg.device == (*it)->mDevices[1])
   EventSystem::Instance()->fire((*it)->mHandle, _onMouseMoved, mMouseEvent);
 return true;
}

bool OISInputSystem::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
 char b =0; b |= (1 << unsigned int(id)); memcpy(&mMouseEvent->button, &b, sizeof(char)); // So Evil.
 mMouseEvent->x.position = arg.state.X.abs;
 mMouseEvent->x.delta = arg.state.X.rel;
 mMouseEvent->y.position = arg.state.Y.abs;
 mMouseEvent->y.delta = arg.state.Y.rel;
 mMouseEvent->wheel.position = arg.state.Z.abs;
 mMouseEvent->wheel.delta = arg.state.Z.rel;
 for (BindingsIterator it = mBindings.begin(); it != mBindings.end(); it++)
  if (arg.device == (*it)->mDevices[1])
   EventSystem::Instance()->fire((*it)->mHandle, _onMouseButtonPressed, mMouseEvent);
 return true;
}

bool OISInputSystem::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
 char b =0; b |= (1 << unsigned int(id)); memcpy(&mMouseEvent->button, &b, sizeof(char)); // So Evil.
 //char b = (char) arg.state.buttons; memcpy(&mMouseEvent->button, &id, sizeof(char)); // Evil.
 mMouseEvent->x.position = arg.state.X.abs;
 mMouseEvent->x.delta = arg.state.X.rel;
 mMouseEvent->y.position = arg.state.Y.abs;
 mMouseEvent->y.delta = arg.state.Y.rel;
 mMouseEvent->wheel.position = arg.state.Z.abs;
 mMouseEvent->wheel.delta = arg.state.Z.rel;
 for (BindingsIterator it = mBindings.begin(); it != mBindings.end(); it++)
  if (arg.device == (*it)->mDevices[1])
   EventSystem::Instance()->fire((*it)->mHandle, _onMouseButtonReleased, mMouseEvent);
 return true;
}

bool OISInputSystem::buttonPressed(const OIS::JoyStickEvent &arg, int button)
{
 return true;
}

bool OISInputSystem::buttonReleased(const OIS::JoyStickEvent &arg, int button)
{
 return true;
}

bool OISInputSystem::axisMoved(const OIS::JoyStickEvent &arg, int axis)
{
 return true;
}

bool OISInputSystem::sliderMoved(const OIS::JoyStickEvent &, int)
{
 return true;
}

bool OISInputSystem::povMoved(const OIS::JoyStickEvent &, int)
{
 return true;
}

void OISInputSystem::watchKey(Ogre::RenderWindow* render_window, int handle, int keycode)
{
 for (BindingsIterator it = mBindings.begin(); it != mBindings.end(); it++)
  if ((*it)->mWindow == render_window)
   (*it)->mWatchedKeys.push_back(WindowBinding::HandleKeyPair(keycode, handle));
}

OISInputSystem::WindowBinding* OISInputSystem::getWindowBinding(Ogre::RenderWindow* render_window)
{
 for (BindingsIterator it = mBindings.begin(); it != mBindings.end(); it++)
  if ((*it)->mWindow == render_window)
   return (*it);
 return 0;
}

#endif

SmartMousePointer::SmartMousePointer(SmartWindow& swindow, const Ogre::String mouse_pointer_image)
: mOverlay(0), mOverlayContainer(0)
{
 Ogre::RenderWindow* window = (*swindow);
 mOverlay = Ogre::OverlayManager::getSingletonPtr()->getByName("OgreliciousMouse");
 if (mOverlay == 0)
 {
  mOverlay = Ogre::OverlayManager::getSingletonPtr()->create("OgreliciousMouse");
  mOverlay->setZOrder(650);
  mOverlayContainer = (Ogre::OverlayContainer*) Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "OgreliciousMouseFor" + window->getName());
  mOverlay->add2D(mOverlayContainer);
  mOverlayContainer->show();
  mOverlay->show();
 }
 else
 {
  mOverlayContainer = mOverlay->getChild("OgreliciousMouseFor" + window->getName());
 }

 // Find material? No, create texture and material.
 if (Ogre::MaterialManager::getSingletonPtr()->getByName("OgreliciousMouseMaterial").isNull())
 {
  // Create the texture
  Ogre::TexturePtr texture = Ogre::TextureManager::getSingletonPtr()->createManual(
    "OgreliciousMouseTexture", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, 16, 16, 0, Ogre::PF_BYTE_BGRA, Ogre::TU_DEFAULT);
  Ogre::HardwarePixelBufferSharedPtr pixelBuffer = texture->getBuffer();
  pixelBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL); // for best performance use HBL_DISCARD!
  const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();
  unsigned char* pDest = static_cast<unsigned char*>(pixelBox.data);
  unsigned int p = 0, index = 0;
  for (size_t i = 0; i < 256;i++)
  {
   index = OgreliciousMouseGlyph[p++];
   if (index == 0)
    OgreliciousMouseGlyph0Colour(pDest)
   else if (index == 1)
    OgreliciousMouseGlyph1Colour(pDest)
   else if (index == 2)
    OgreliciousMouseGlyph2Colour(pDest)
   else if (index == 3)
    OgreliciousMouseGlyph3Colour(pDest)
  }
  // Unlock the pixel buffer
  pixelBuffer->unlock();

  Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("OgreliciousMouseMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  material->getTechnique(0)->getPass(0)->createTextureUnitState("OgreliciousMouseTexture");
  material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
  material->getTechnique(0)->getPass(0)->setTextureFiltering(Ogre::TFO_NONE);
 }

 // set overlaycontainer to 16x16, set it to the material, move to center of window.
 mOverlayContainer->setMetricsMode(Ogre::GMM_PIXELS);
 mOverlayContainer->setPosition((window->getWidth() / 2) - 8, (window->getHeight() / 2) - 8);
 mOverlayContainer->setDimensions(32, 32);
 mOverlayContainer->setMaterialName("OgreliciousMouseMaterial");

 swindow.onMouseMoved += SmartCallback(this, &SmartMousePointer::mouseMoved);
}

SmartMousePointer::~SmartMousePointer()
{
///// Ogre::OverlayManager::getSingletonPtr()->destroy(mOverlay);
}

void SmartMousePointer::mouseMoved(MouseEvent* _event)
{
 mOverlayContainer->setPosition(mOverlayContainer->getLeft() + _event->x.delta, mOverlayContainer->getTop() + _event->y.delta);
}

unsigned int SmartMousePointer::x() const
{
 return mOverlayContainer->getLeft();
}

unsigned int SmartMousePointer::y() const
{
 return mOverlayContainer->getTop();
}

} // namespace

// SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS 
//SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS SMARTPLUGINS 

namespace Ogrelicious
{

SmartPlugins::SmartPlugins(const std::string& csa)
: Many()
{
 fill_csa<SmartPlugins>(csa, *this);
}

SmartPlugins::SmartPlugins(const SmartPlugins& other)
: Many(other.mAssociates)
{
}

SmartPlugins& SmartPlugins::operator=(const SmartPlugins& other)
{
 mAssociates = other.mAssociates;
 return *this;
}

SmartPlugins::~SmartPlugins()
{
}

SmartPlugins& SmartPlugins::load(SimpleAccessor accessor)
{
 SAEach<SmartPlugins>(accessor, getIterator(), &SmartPlugin::load);
 return *this;
}

SmartPlugins& SmartPlugins::describe(SimpleAccessor accessor)
{
 std::cout << "Of SmartPlugins" << std::endl;
 SAEach<SmartPlugins>(accessor, getIterator(), &SmartPlugin::describe);
 return *this;
}

SmartPlugin::SmartPlugin()
: mPlugin(new OgrePlugin())
{
}

SmartPlugin::SmartPlugin(const std::string& name)
: mPlugin(new OgrePlugin())
{
 
 mPlugin->mName = name;
 mPlugin->mIsRenderSystem = false;
 mPlugin->mIsLibrary = false;
 mPlugin->mIsLoaded = false;
 mPlugin->mPlugin = 0;


 if (Ogre::StringUtil::endsWith(name, ".dll"))
 {
  mPlugin->mName = mPlugin->mName.substr(0, name.length() - 4);
  mPlugin->mIsLibrary = true;
  mPlugin->mFilename = name;
 }

 if (Ogre::StringUtil::endsWith(mPlugin->mName, "_d"))
  mPlugin->mName = mPlugin->mName.substr(0, name.length() - 2);

 if (Ogre::StringUtil::startsWith(mPlugin->mName, "rendersystem_"))
 {
  mPlugin->mName = mPlugin->mName.substr(13, name.length());
  mPlugin->mIsRenderSystem = true;
 }
 else if (Ogre::StringUtil::startsWith(mPlugin->mName, "rendersystem:"))
 {
  mPlugin->mName = mPlugin->mName.substr(13, name.length());
  mPlugin->mIsRenderSystem = true;
  mPlugin->mIsLibrary = true;
  Ogre::StringUtil::trim(mPlugin->mName);
#ifdef _DEBUG
  mPlugin->mFilename = "RenderSystem_" + mPlugin->mName + "_d.dll";
#else
  mPlugin->mFilename = "RenderSystem_" + mPlugin->mName + ".dll";
#endif
 }
 else if (Ogre::StringUtil::startsWith(mPlugin->mName, "plugin_"))
 {
  mPlugin->mName = mPlugin->mName.substr(7, name.length());
  mPlugin->mIsRenderSystem = false;
 }
 else if (Ogre::StringUtil::startsWith(mPlugin->mName, "plugin:"))
 {
  mPlugin->mName = mPlugin->mName.substr(7, name.length());
  mPlugin->mIsRenderSystem = false;
  mPlugin->mIsLibrary = true;
  Ogre::StringUtil::trim(mPlugin->mName);
#ifdef _DEBUG
  mPlugin->mFilename = "Plugin_" + mPlugin->mName + "_d.dll";
#else
  mPlugin->mFilename = "Plugin_" + mPlugin->mName + ".dll";
#endif
 }
 _scout();
}

SmartPlugin::SmartPlugin(const SmartPlugin& other)
{
 mPlugin = other.mPlugin;
}

SmartPlugin::~SmartPlugin()
{
}

SmartPlugin& SmartPlugin::operator=(SmartPlugin& other)
{
 mPlugin = other.mPlugin;
 return *this;
}

SmartPlugin& SmartPlugin::describe()
{
 std::cout << " - " << mPlugin->mName << " of " << mPlugin->mFilename << (mPlugin->mIsRenderSystem ? " (RenderSystem)" : " (Plugin)") << (mPlugin->mIsLoaded ? " (Loaded)" : "") << (mPlugin->mIsLibrary ? " (Library)" : "") << std::endl;
 return *this;
}

SmartPlugin& SmartPlugin::load()
{
  if (mPlugin->mIsLibrary && !mPlugin->mIsLoaded)
  {
  size_t nbPlugins = Ogre::Root::getSingletonPtr()->getInstalledPlugins().size();
  Ogre::Root::getSingletonPtr()->loadPlugin(mPlugin->mFilename);
  mPlugin->mIsLoaded = (nbPlugins < Ogre::Root::getSingletonPtr()->getInstalledPlugins().size());
  }

  _scout();

 return *this;
}

std::string SmartPlugin::name()
{
 return mPlugin->mName;
}

void SmartPlugin::_scout()
{
 Ogre::Root::PluginInstanceList plugins = Ogre::Root::getSingletonPtr()->getInstalledPlugins();
 for (unsigned int i=0;i < plugins.size(); i++)
 {
  if (plugins[i]->getName() == "D3D9 RenderSystem" && mPlugin->mName == "Direct3D9")
  {
   mPlugin->mPlugin = plugins[i];
   mPlugin->mName = plugins[i]->getName();
   mPlugin->mIsLoaded = true;
   break;
  }
  
  if (insCmp(plugins[i]->getName(), mPlugin->mName))
  {
   mPlugin->mPlugin = plugins[i];
   mPlugin->mIsLoaded = true;
   break;
  }

 }

}

}

// SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS 
//SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS SMARTRENDERSYSTEMS 

namespace Ogrelicious
{

SmartRenderSystems::SmartRenderSystems(const std::string& csa)
: Many()
{
 if (insCmpS(csa, "all"))
  fill_all_ptr<SmartRenderSystems>(*this, FastConstIterator<Ogre::RenderSystemList>(Ogre::Root::getSingletonPtr()->getAvailableRenderers()->begin(), Ogre::Root::getSingletonPtr()->getAvailableRenderers()->end()));
 else
  fill_csa<SmartRenderSystems>(csa, *this);
}

SmartRenderSystems::SmartRenderSystems(const SmartRenderSystems& other)
: Many(other.mAssociates)
{
}

SmartRenderSystems& SmartRenderSystems::operator=(const SmartRenderSystems& other)
{
 mAssociates = other.mAssociates;
 return *this;
}

SmartRenderSystems::~SmartRenderSystems()
{
}

SmartRenderSystems& SmartRenderSystems::nominate(SimpleAccessor accessor)
{
 SAEach<SmartRenderSystems>(accessor, getIterator(), &SmartRenderSystem::nominate);
 return *this;
}

SmartRenderSystems& SmartRenderSystems::describe(SimpleAccessor accessor)
{
 std::cout << "Of SmartRenderSystems" << std::endl;
 SAEach<SmartRenderSystems>(accessor, getIterator(), &SmartRenderSystem::describe);
 return *this;
}

SmartRenderSystem::SmartRenderSystem()
: mRenderSystem(new OgreRenderSystem())
{
}

SmartRenderSystem::SmartRenderSystem(Ogre::RenderSystem* rs)
: mRenderSystem(new OgreRenderSystem())
{
 mRenderSystem->mRenderSystem = rs;
 mRenderSystem->mIsLoaded = false;
 mRenderSystem->mIsNominated = false;
 _scout();
}

SmartRenderSystem::SmartRenderSystem(const std::string& name)
: mRenderSystem(new OgreRenderSystem())
{
 
 mRenderSystem->mName = name;
 mRenderSystem->mIsLoaded = false;
 mRenderSystem->mIsNominated = false;
 
 if (insCmpS(name, "d3d9") || insCmpS(name, "direct3d9") || insCmpS(name, "directx") ||  insCmpS(name, "dx9") || insCmpS(name, "dx"))
 {
  mRenderSystem->mRenderSystem = ::Ogre::Root::getSingletonPtr()->getRenderSystemByName("Direct3D9 Rendering Subsystem");
 }
// Uncomment when the name for OpenGL is found.
#if 0
  else if (insCmpS(name, "opengl") || insCmp(name, "gl"))
  {
    mRenderSystem->mRenderSystem = ::Ogre::Root::getRenderSystemByName("OpenGL RenderSystem");
  }
#endif
 else
 {
  mRenderSystem->mRenderSystem = ::Ogre::Root::getSingletonPtr()->getRenderSystemByName(name);
 }
 
 _scout();
 
}

SmartRenderSystem::SmartRenderSystem(const SmartRenderSystem& other)
{
 mRenderSystem = other.mRenderSystem;
}

SmartRenderSystem::~SmartRenderSystem()
{
}

SmartRenderSystem& SmartRenderSystem::operator=(SmartRenderSystem& other)
{
 mRenderSystem = other.mRenderSystem;
 return *this;
}

SmartRenderSystem& SmartRenderSystem::describe()
{
 std::cout << " - " << mRenderSystem->mName << (mRenderSystem->mIsLoaded ? " (Loaded)" : "") << (mRenderSystem->mIsNominated ? " (Nominated)" : "") << std::endl;
 return *this;
}

SmartRenderSystem& SmartRenderSystem::nominate()
{
 
 if (mRenderSystem->mRenderSystem && Ogre::Root::getSingletonPtr()->getRenderSystem() == NULL)
  Ogre::Root::getSingletonPtr()->setRenderSystem(mRenderSystem->mRenderSystem);
 
 _scout();
 
 return *this;
}

std::string SmartRenderSystem::name()
{
 return mRenderSystem->mName;
}
void SmartRenderSystem::_scout()
{
 
 if (mRenderSystem->mRenderSystem == NULL)
  return;
 
 mRenderSystem->mName = mRenderSystem->mRenderSystem->getName();
 mRenderSystem->mIsLoaded = true;
 mRenderSystem->mIsNominated = Ogre::Root::getSingletonPtr()->getRenderSystem() == mRenderSystem->mRenderSystem;
}



} // namespace

// SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS 
//SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS SMARTRESOURCEGROUPS 

namespace Ogrelicious
{

SmartResourceGroups::SmartResourceGroups(const std::string& csa)
: Many()
{
 if (insCmpS(csa, "all"))
 {
  Ogre::StringVector vec = Ogre::ResourceGroupManager::getSingletonPtr()->getResourceGroups();
  fill_all<SmartResourceGroups>(*this, FastConstIterator< Ogre::StringVector >(vec.begin(), vec.end()));
 }
 else
  fill_csa<SmartResourceGroups>(csa, *this);
}

SmartResourceGroups::SmartResourceGroups(const SmartResourceGroups& other)
: Many(other.mAssociates)
{
}

SmartResourceGroups& SmartResourceGroups::operator=(const SmartResourceGroups& other)
{
 mAssociates = other.mAssociates;
 return *this;
}


SmartResourceGroups::~SmartResourceGroups()
{
}

SmartResourceGroups& SmartResourceGroups::operator+=(const std::string& rs)
{
 SAEach1<SmartResourceGroups>(_Everything, getIterator(), &SmartResourceGroup::operator+=, rs);
 return *this;
}

SmartResourceGroups& SmartResourceGroups::init(SimpleAccessor accessor)
{
 SAEach<SmartResourceGroups>(accessor, getIterator(), &SmartResourceGroup::init);
 return *this;
}

SmartResourceGroups& SmartResourceGroups::describe(SimpleAccessor accessor)
{
 SAEach<SmartResourceGroups>(accessor, getIterator(), &SmartResourceGroup::describe);
 return *this;
}

SmartResourceGroup::SmartResourceGroup()
: mResourceGroup(new OgreResourceGroup())
{
}

SmartResourceGroup::SmartResourceGroup(const std::string& name)
: mResourceGroup(new OgreResourceGroup())
{
 mResourceGroup->mName = name;
}

SmartResourceGroup::SmartResourceGroup(const SmartResourceGroup& other)
{
 mResourceGroup = other.mResourceGroup;
}

SmartResourceGroup::~SmartResourceGroup()
{
}

SmartResourceGroup& SmartResourceGroup::operator=(SmartResourceGroup& other)
{
 mResourceGroup = other.mResourceGroup;
 return *this;
}

SmartResourceGroup& SmartResourceGroup::describe()
{
 std::cout << " - " << mResourceGroup->mName << std::endl;
 return *this;
}

SmartResourceGroup& SmartResourceGroup::init()
{
 _OgreliciousDebug("Initialising resource group " << mResourceGroup->mName); 
 Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup(mResourceGroup->mName);
 return *this;
}

SmartResourceGroup& SmartResourceGroup::operator+=(const std::string& rsa)
{
  Ogre::StringVector str_vector = csa_get(rsa);
  Ogre::ResourceGroupManager* rgm = Ogre::ResourceGroupManager::getSingletonPtr();
  
  for (Ogre::uint i=0;i < str_vector.size();i++)
  {

   if (Ogre::StringUtil::endsWith(str_vector[i], "/#?"))
   {
    Ogre::String baseDir = str_vector[i].substr(0, str_vector[i].size() - 2);
    Ogre::FileSystemArchive* arch = new Ogre::FileSystemArchive(baseDir, "FileSystem");
   
    Ogre::StringVectorPtr zip_files = arch->find("*.zip");
   
    for (Ogre::uint i=0;i < zip_files->size();i++)
     rgm->addResourceLocation(baseDir + zip_files->operator [](i), "Zip", mResourceGroup->mName, true);

    Ogre::StringVectorPtr directories = arch->find("*", false, true);
    for (Ogre::uint i=0;i < directories->size();i++)
    {
     Ogre::String str = directories->operator [](i);
     // Ignore all CVS directories.
     if (str == "CVS" || Ogre::StringUtil::endsWith(str, "/CVS", false))
      continue;
     rgm->addResourceLocation(baseDir + str, "FileSystem", mResourceGroup->mName, true);
    }
   
     delete arch;
   }
   else if (Ogre::StringUtil::endsWith(str_vector[i], ".zip"))
   {
    rgm->addResourceLocation(str_vector[i], "Zip", mResourceGroup->mName, true);
   }
   else
   {
    rgm->addResourceLocation(str_vector[i], "FileSystem", mResourceGroup->mName, true);
   }
  }
 return *this;
}

std::string SmartResourceGroup::name()
{
 return mResourceGroup->mName;
}


} // namespace


// SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS 
//SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS SMARTWINDOWS 

namespace Ogrelicious
{

SmartWindows::SmartWindows(const std::string& csa)
: Many()
{
 if (insCmpS(csa, "all"))
 {
  //Ogre::StringVector vec = Ogre::WindowManager::getSingletonPtr()->getWindows();
  //fill_all<SmartWindows>(*this, FastConstIterator< Ogre::StringVector >(vec.begin(), vec.end()));
 }
 else
  fill_csa<SmartWindows>(csa, *this);
}

SmartWindows::SmartWindows(const SmartWindows& other)
: Many(other.mAssociates)
{
}

SmartWindows& SmartWindows::operator=(const SmartWindows& other)
{
 mAssociates = other.mAssociates;
 return *this;
}

SmartWindows::~SmartWindows()
{
}

SmartWindows& SmartWindows::describe(SimpleAccessor accessor)
{
 SAEach<SmartWindows>(accessor, getIterator(), &SmartWindow::describe);
 return *this;
}

SmartWindows& SmartWindows::title(const std::string& t, SimpleAccessor a)
{
 SAEach1<SmartWindows>(a, getIterator(), &SmartWindow::title, t);
 return *this;
}

SmartWindows& SmartWindows::width(const Ogre::ushort& t, SimpleAccessor a)
{
 SAEach1<SmartWindows>(a, getIterator(), &SmartWindow::width, t);
 return *this;
}

SmartWindows& SmartWindows::height(const Ogre::ushort& t, SimpleAccessor a)
{
 SAEach1<SmartWindows>(a, getIterator(), &SmartWindow::height, t);
 return *this;
}

SmartWindows& SmartWindows::depth(const Ogre::uchar& t, SimpleAccessor a)
{
 SAEach1<SmartWindows>(a, getIterator(), &SmartWindow::depth, t);
 return *this;
}

SmartWindows& SmartWindows::fullscreen(const bool& t, SimpleAccessor a)
{
 SAEach1<SmartWindows>(a, getIterator(), &SmartWindow::fullscreen, t);
 return *this;
}

SmartWindows& SmartWindows::left(const Ogre::uint& t, SimpleAccessor a)
{
 SAEach1<SmartWindows>(a, getIterator(), &SmartWindow::left, t);
 return *this;
}

SmartWindows& SmartWindows::top(const Ogre::uint& t, SimpleAccessor a)
{
 SAEach1<SmartWindows>(a, getIterator(), &SmartWindow::top, t);
 return *this;
}

#if 0
SmartWindows& SmartWindows::fsaa(const Ogre::uchar& t, SimpleAccessor a)
{
 SAEach1<SmartWindows>(a, getIterator(), &SmartWindow::fsaa, t);
 return *this;
}

SmartWindows& SmartWindows::vsync(const bool& t, SimpleAccessor a)
{
 SAEach1<SmartWindows>(a, getIterator(), &SmartWindow::vsync, t);
 return *this;
}
#endif
SmartWindow::SmartWindow()
: mWindow(new OgreWindow()), mEvents(new SmartEvents(_OgreliciousNextHandleID++))
{

 mWindow->mWindow = 0;
 mWindow->mProps = 0;

 _events();
 _createProps();

}

SmartWindow::SmartWindow(const std::string& name)
: mWindow(new OgreWindow()), mEvents(new SmartEvents(_OgreliciousNextHandleID++))
{

 mWindow->mName = name;
 Ogre::StringUtil::trim(mWindow->mName);
 mWindow->mWindow = 0;
 mWindow->mProps = 0;

 _events();

 for (unsigned int i=0; i < Ogre::WindowEventUtilities::_msWindows.size();i++)
 {
  Ogre::RenderWindow* window = Ogre::WindowEventUtilities::_msWindows[i];
  if (window->getName() == mWindow->mName)
  {
   mWindow->mWindow = window;
   break;
  }
 }

 if (mWindow->mWindow == 0)
  _createProps();
 else
  EventSystem::Instance()->getRenderWindowEventListener()->set(mEvents->mHandle, mWindow->mWindow);

}

SmartWindow::SmartWindow(const SmartWindow& other)
: mWindow(other.mWindow),
  mEvents(other.mEvents),
  mViewports(other.mViewports),
  mMousePointer(other.mMousePointer)
{
 _events();
}

SmartWindow::~SmartWindow()
{
 if (mWindow.useCount() == 1)
  if (mWindow->mProps)
   delete mWindow->mProps;
}

SmartWindow& SmartWindow::operator=(SmartWindow& other)
{
 mWindow = other.mWindow;
 mEvents = other.mEvents;
 mViewports = other.mViewports;
 mMousePointer = other.mMousePointer;
 _events();
 return *this;
}

SmartWindow& SmartWindow::describe()
{
 return *this;
}

/// SmartWindow& SmartWindow::name(const Ogre::String& name)
/// {
/// }

std::string SmartWindow::name()
{
 return mWindow->mName;
}

SmartWindow& SmartWindow::create(MouseType mt)
{
 if (mWindow->mWindow != 0 || mWindow->mProps == 0)
  return *this;

 Ogre::NameValuePairList windowParams;
 windowParams["colorDepth"] = _OgreliciousToString(mWindow->mProps->mDepth);
 if (mWindow->mProps->mLeft != _HorizontallyCenter)
  windowParams["left"] = _OgreliciousToString(mWindow->mProps->mLeft);
 if (mWindow->mProps->mTop != _VerticallyCenter)
  windowParams["top"] = _OgreliciousToString(mWindow->mProps->mTop);
 windowParams["fsaa"] = _OgreliciousToString(mWindow->mProps->mFSAA);
 windowParams["displayFrequency"] = _OgreliciousToString(mWindow->mProps->mFrequency);

 switch(mWindow->mProps->mBorder)
 {
  case _NoBorder:
   windowParams["border"] = "none";
  break;
  case _FixedBorder:
   windowParams["border"] = "fixed";
  break;
  case _ResizableBorder:
   windowParams["border"] = "resize";
  break;
 }

 mWindow->mWindow = Ogre::Root::getSingletonPtr()->createRenderWindow(
  mWindow->mName, mWindow->mProps->mWidth, mWindow->mProps->mHeight, mWindow->mProps->mIsFullScreen, &windowParams);

 title(mWindow->mProps->mTitle);
 delete mWindow->mProps;
 mWindow->mProps = 0;

 _events(mt == _OperatingSystemMouse);
 if (mt == _OgreOverlayMouse && mMousePointer.isNull())
   mMousePointer.bind(new SmartMousePointer(*this));

 EventSystem::Instance()->getRenderWindowEventListener()->set(mEvents->mHandle, mWindow->mWindow);
 onLoad();

 return *this;
}

SmartWindow& SmartWindow::title(const Ogre::String& title)
{
 if (mWindow->mWindow)
 {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    HWND hWnd = 0;
    mWindow->mWindow->getCustomAttribute("WINDOW", &hWnd);
    SetWindowText(hWnd, title.c_str() );
#endif
 }
 else
  mWindow->mProps->mTitle = title;
 return *this;
}

Ogre::String SmartWindow::title() const
{
 if (mWindow->mWindow)
 {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    HWND hWnd = 0;
    mWindow->mWindow->getCustomAttribute("WINDOW", &hWnd);
    int str_length = GetWindowTextLength(hWnd);
    char* str = (char*) malloc(str_length + 1);
    GetWindowText(hWnd, str, str_length);
    std::string ret_title(str);
    free(str);
    return ret_title;
#endif
 }
 else
  return mWindow->mProps->mTitle;
}

SmartWindow& SmartWindow::width(const Ogre::ushort& width)
{
 if (mWindow->mWindow)
 {
  unsigned int h, x; int xx;
  mWindow->mWindow->getMetrics(x, h, x, xx, xx);
  mWindow->mWindow->resize(width, h);
 }
 else
  mWindow->mProps->mWidth = width;
 return *this;
}

SmartWindow& SmartWindow::size(const Ogre::ushort& width, const Ogre::ushort& height)
{
 if (mWindow->mWindow)
  mWindow->mWindow->resize(width, height);
 else
 {
  mWindow->mProps->mWidth = width;
  mWindow->mProps->mHeight = height;
 }
 return *this;
}

Ogre::ushort SmartWindow::width() const
{
 if (mWindow->mWindow)
 {
  unsigned int w, x; int xx;
  mWindow->mWindow->getMetrics(w, x, x, xx, xx);
  return w;
 }
 else
  return mWindow->mProps->mWidth;
}

SmartWindow& SmartWindow::height(const Ogre::ushort& height)
{
 if (mWindow->mWindow)
 {
  unsigned int w, x; int xx;
  mWindow->mWindow->getMetrics(w, x, x, xx, xx);
  mWindow->mWindow->resize(w, height);
 }
 else
  mWindow->mProps->mHeight = height;
 return *this;
}

Ogre::ushort SmartWindow::height() const
{
 if (mWindow->mWindow)
 {
  unsigned int h, x;  int xx;
  mWindow->mWindow->getMetrics(x, h, x, xx, xx);
  return h;
 }
 else
  return mWindow->mProps->mHeight;
}

SmartWindow& SmartWindow::depth(const Ogre::uchar& depth)
{
 if (mWindow->mWindow)
 {
  //< \todo Probably have to recreate the window. 
 }
 else
  mWindow->mProps->mDepth = depth;
 return *this;
}

Ogre::uchar  SmartWindow::depth()
{
 if (mWindow->mWindow)
 {
  unsigned int d, x;  int xx;
  mWindow->mWindow->getMetrics(x, x, d, xx, xx);
  return d;
 }
 else
  return mWindow->mProps->mDepth;
}

SmartWindow& SmartWindow::fullscreen(const bool& fs)
{
 if (mWindow->mWindow)
 {
  unsigned int w,h,x;  int xx;
  mWindow->mWindow->getMetrics(w, h, x, xx, xx);
  mWindow->mWindow->setFullscreen(fs, w, h);
 }
 else
  mWindow->mProps->mIsFullScreen = fs;
 return *this;
}

bool         SmartWindow::fullscreen() const
{
 if (mWindow->mWindow)
  return mWindow->mWindow->isFullScreen();
 else
  return mWindow->mProps->mIsFullScreen;
}

SmartWindow& SmartWindow::position(const Ogre::ushort& left, const Ogre::ushort& top)
{
 if (mWindow->mWindow)
  mWindow->mWindow->reposition(left, top);
 return *this;
}

SmartWindow& SmartWindow::left(const Ogre::uint& left)
{
 if (mWindow->mWindow)
 {
  int t, xx; unsigned int x;
  mWindow->mWindow->getMetrics(x, x, x, xx, t);
  mWindow->mWindow->reposition(left, t);
 }
 else
  mWindow->mProps->mLeft = left;
 return *this;
}

Ogre::uint   SmartWindow::left() const
{
 if (mWindow->mWindow)
 {
  int l, xx; unsigned int x;
  mWindow->mWindow->getMetrics(x, x, x, l, xx);
  return l;
 }
 else
  return mWindow->mProps->mLeft;
}

SmartWindow& SmartWindow::top(const Ogre::uint& top)
{
 if (mWindow->mWindow)
 {
  int l, xx; unsigned int x;
  mWindow->mWindow->getMetrics(x, x, x, l, xx);
  mWindow->mWindow->reposition(l, top);
 }
 else
  mWindow->mProps->mTop = top;
 return *this;
}

Ogre::uint   SmartWindow::top() const
{
 if (mWindow->mWindow)
 {
  unsigned int x; int t, xx;
  mWindow->mWindow->getMetrics(x, x, x, xx, t);
  return x;
 }
 else
  return mWindow->mProps->mTop;
}

Ogre::uint SmartWindow::fsaa() const
{
 if (mWindow->mWindow)
  return mWindow->mWindow->getFSAA();
 else
  return mWindow->mProps->mFSAA;
}

SmartWindow& SmartWindow::vsync(const bool &b)
{
 if (mWindow->mWindow)
 {
 }
 else
  mWindow->mProps->mVSync = b;
 return *this;
}

bool SmartWindow::vsync() const
{
 if (mWindow->mWindow)
 {
  return false;
 }
 return mWindow->mProps->mVSync;
}

SmartWindow& SmartWindow::frequency(const Ogre::ushort &freq)
{
 if (mWindow->mWindow)
 {
 }
 else
  mWindow->mProps->mFrequency = freq;
 return *this;
}

Ogre::ushort SmartWindow::frequency() const
{
 if (mWindow->mWindow)
 {
  return 0;
 }
 else
  return mWindow->mProps->mFrequency;
}

Ogre::String SmartWindow::attribute(const Ogre::String& key) const
{
 if (mWindow->mWindow)
 {
  return Ogre::StringUtil::BLANK;
 }
 else
 {
  StringMap::iterator it = mWindow->mProps->mAttributes.find(key);
  if (it == mWindow->mProps->mAttributes.end())
   return Ogre::StringUtil::BLANK;
  else
   return (*it).second;
 }
}

SmartWindow& SmartWindow::attribute(const Ogre::String& key, const Ogre::String& value)
{
 if (mWindow->mProps)
  mWindow->mProps->mAttributes[key] = value;
 return *this;
}

StringMap SmartWindow::attributes() const
{
 if (mWindow->mProps)
  return mWindow->mProps->mAttributes;
 return StringMap();
}

SmartWindow& SmartWindow::watchKey(int keyCode, const _Callback& callback)
{
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCode);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCode, callback.mFunctor);
 return *this;
}

SmartWindow& SmartWindow::watchKeys(int keyCodeA, int keyCodeB, const _Callback& callback)
{
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeA);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeA, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeB);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeB, callback.mFunctor);
 return *this;
}

SmartWindow& SmartWindow::watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, const _Callback& callback)
{
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeA);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeA, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeB);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeB, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeC);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeC, callback.mFunctor);
 return *this;
}

SmartWindow& SmartWindow::watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, int keyCodeD, const _Callback& callback)
{
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeA);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeA, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeB);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeB, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeC);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeC, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeD);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeD, callback.mFunctor);
 return *this;
}

SmartWindow& SmartWindow::watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, int keyCodeD, int keyCodeE, const _Callback& callback)
{
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeA);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeA, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeB);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeB, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeC);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeC, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeD);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeD, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeE);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeE, callback.mFunctor);
 return *this;
}

SmartWindow& SmartWindow::watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, int keyCodeD, int keyCodeE, int keyCodeF, const _Callback& callback)
{
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeA);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeA, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeB);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeB, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeC);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeC, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeD);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeD, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeE);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeE, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeF);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeF, callback.mFunctor);
 return *this;
}

SmartWindow& SmartWindow::watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, int keyCodeD, int keyCodeE, int keyCodeF, int keyCodeG, const _Callback& callback)
{
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeA);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeA, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeB);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeB, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeC);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeC, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeD);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeD, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeE);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeE, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeF);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeF, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeG);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeG, callback.mFunctor);
 return *this;
}

SmartWindow& SmartWindow::watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, int keyCodeD, int keyCodeE, int keyCodeF, int keyCodeG, int keyCodeI, const _Callback& callback)
{
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeA);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeA, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeB);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeB, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeC);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeC, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeD);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeD, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeE);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeE, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeF);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeF, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeG);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeG, callback.mFunctor);
 SmartInputSystem::Instance()->watchKey(mWindow->mWindow, mEvents->mHandle, keyCodeI);
 EventSystem::Instance()->addFunctor(mEvents->mHandle, keyCodeI, callback.mFunctor);
 return *this;
}

void SmartWindow::_events(bool exclusiveMouse)
{
 onDraw._   = mEvents;
 onFocus._  = mEvents;
 onLoad._   = mEvents;
 onMove._   = mEvents;
 onResize._ = mEvents;
 onUnload._ = mEvents;
 onKeyPressed._ = mEvents;
 onKeyReleased._= mEvents;
 onMouseMoved._ = mEvents;
 onMouseButtonPressed._ = mEvents;
 onMouseButtonReleased._ = mEvents;
 SmartInputSystem::Instance()->addWindow(mWindow->mWindow, mEvents->mHandle, exclusiveMouse);
}


void SmartWindow::_createProps()
{
 if (mWindow->mProps == 0)
  mWindow->mProps = new WindowDesigner();
 
 if (mWindow->mName.size())
  mWindow->mProps->mTitle = mWindow->mName;
 else
  mWindow->mProps->mTitle = "Ogrelicious Window";

 mWindow->mProps->mWidth = 600;
 mWindow->mProps->mHeight = 400;
 mWindow->mProps->mIsFullScreen = false;
 mWindow->mProps->mDepth = 32;
 mWindow->mProps->mBorder = _FixedBorder;
 mWindow->mProps->mFrequency = 60;
 mWindow->mProps->mFSAA = 0;
 mWindow->mProps->mLeft = 0;
 mWindow->mProps->mTop = 0;
 mWindow->mProps->mVSync = false;
}

SmartViewport SmartWindow::add(SmartCamera& cam, unsigned int zOrder, Ogre::Real left, Ogre::Real top, Ogre::Real width, Ogre::Real height)
{
 return mViewports.add(SmartViewport((*cam), mWindow->mWindow));
}

bool SmartWindow::isPrototype() const
{
 return (mWindow->mProps != 0);
}

Ogre::SharedPtr<SmartMousePointer> SmartWindow::getMousePointer()
{
 return mMousePointer;
}

#if OGRELICIOUS_LOVES_OIS
OIS::InputManager* SmartWindow::getOISManager()
{
 return SmartInputSystem::Instance()->getWindowBinding(mWindow->mWindow)->mInputSystem;
}
#endif


} // namespace



// SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS 
//SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS SMARTCAMERAS 

namespace Ogrelicious
{

SmartCameras::SmartCameras(Ogre::SceneManager* scene_mgr, const std::string& other)
: Many()
{
 
}

SmartCameras::SmartCameras(const SmartCameras& other)
: Many(other.mAssociates)
{
}

SmartCameras& SmartCameras::operator=(const SmartCameras& other)
{
 mAssociates = other.mAssociates;
 return *this;
}

SmartCameras::~SmartCameras()
{
}

SmartCamera::SmartCamera()
: mCamera(new OgreCamera())
{
 mCamera->mCamera = 0;
}

SmartCamera::SmartCamera(Ogre::Camera* cam)
: mCamera(new OgreCamera())
{
 mCamera->mCamera = cam;
 mCamera->mName = cam->getName();
}

SmartCamera::SmartCamera(const std::string& name, Ogre::SceneManager* scene_mgr)
: mCamera(new OgreCamera())
{

 mCamera->mName = name;
 Ogre::StringUtil::trim(mCamera->mName);

 if(scene_mgr->hasCamera(mCamera->mName))
  mCamera->mCamera = scene_mgr->getCamera(mCamera->mName);
 else
  mCamera->mCamera = scene_mgr->createCamera(mCamera->mName);

}


SmartCamera::SmartCamera(const SmartCamera& other)
{
 mCamera = other.mCamera;
}

SmartCamera::~SmartCamera()
{
}

SmartCamera& SmartCamera::operator=(SmartCamera& other)
{
 mCamera = other.mCamera;
 return *this;
}

SmartCamera& SmartCamera::describe()
{
 std::cout << " - " << mCamera->mName << std::endl;
 return *this;
}

std::string  SmartCamera::name()
{
 return mCamera->mName;
}

SmartCamera& SmartCamera::nearClip(const Ogre::Real& nearDist)
{
 mCamera->mCamera->setNearClipDistance(nearDist);
 return *this;
}

Ogre::Real   SmartCamera::nearClip() const
{
 return mCamera->mCamera->getNearClipDistance();
}

SmartCamera& SmartCamera::farClip(const Ogre::Real& farDist)
{
 mCamera->mCamera->setFarClipDistance(farDist);
 return *this;
}

Ogre::Real   SmartCamera::farClip() const
{
 return mCamera->mCamera->getFarClipDistance();
}

SmartCamera& SmartCamera::position(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z)
{
 mCamera->mCamera->setPosition(x, y, z);
 return *this;
}

SmartCamera& SmartCamera::position(const Ogre::Vector3& vec)
{
 mCamera->mCamera->setPosition(vec);
 return *this;
}

Ogre::Vector3 SmartCamera::position() const
{
 return mCamera->mCamera->getPosition();
}

SmartCamera& SmartCamera::x(const Ogre::Real& x)
{
 static Ogre::Vector3 pos = mCamera->mCamera->getPosition(); pos.x = x;
 mCamera->mCamera->setPosition(pos);
 return *this;
}

SmartCamera& SmartCamera::y(const Ogre::Real& y)
{
 static Ogre::Vector3 pos = mCamera->mCamera->getPosition(); pos.y = y;
 mCamera->mCamera->setPosition(pos);
 return *this;
}

SmartCamera& SmartCamera::z(const Ogre::Real& z)
{
 static Ogre::Vector3 pos = mCamera->mCamera->getPosition(); pos.z = z;
 mCamera->mCamera->setPosition(pos);
 return *this;
}

Ogre::Real   SmartCamera::x() const
{
 return mCamera->mCamera->getPosition().x;
}

Ogre::Real   SmartCamera::y() const
{
 return mCamera->mCamera->getPosition().y;
}

Ogre::Real   SmartCamera::z() const
{
 return mCamera->mCamera->getPosition().z;
}

SmartCamera& SmartCamera::translate(const Ogre::Vector3& direction)
{
 mCamera->mCamera->setPosition(mCamera->mCamera->getPosition() + direction);
 return *this;
}

SmartCamera& SmartCamera::translate(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z)
{
 mCamera->mCamera->setPosition(mCamera->mCamera->getPosition() + Ogre::Vector3(x, y, z));
 return *this;
}

SmartCamera& SmartCamera::look(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z)
{
 mCamera->mCamera->lookAt(Ogre::Vector3(x,y,z));
 return *this;
}

SmartCamera& SmartCamera::look(const Ogre::Vector3& vec)
{
 mCamera->mCamera->lookAt(vec);
 return *this;
}

SmartCamera& SmartCamera::look(Ogre::SceneNode* node)
{
 mCamera->mCamera->lookAt(node->getPosition());
 return *this;
}

SmartCamera& SmartCamera::direction(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z)
{
 mCamera->mCamera->setDirection(x, y, z);
 return *this;
}

SmartCamera& SmartCamera::direction(const Ogre::Vector3& vec)
{
 mCamera->mCamera->setDirection(vec);
 return *this;
}

Ogre::Vector3 SmartCamera::direction() const
{
 return mCamera->mCamera->getDirection();
}

}

// SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS 
//SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS SMARTVIEWPORTS 

namespace Ogrelicious
{

SmartViewports::SmartViewports()
: Many()
{
}

SmartViewports::SmartViewports(const SmartViewports& other)
: Many(other.mAssociates)
{
}

SmartViewports& SmartViewports::operator=(const SmartViewports& other)
{
 mAssociates = other.mAssociates;
 return *this;
}

SmartViewports::~SmartViewports()
{
}

SmartViewport::SmartViewport()
: mViewport(new OgreViewport())
{
 mViewport->mCamera = 0;
 mViewport->mViewport = 0;
 mViewport->mWindow = 0;
 mViewport->mID = 0;
}

SmartViewport::SmartViewport(Ogre::Camera* camera, Ogre::RenderWindow* win)
: mViewport(new OgreViewport())
{
 mViewport->mCamera = camera;
 mViewport->mViewport = 0;
 mViewport->mWindow = win;
 mViewport->mID = 0;
 
 if (camera != 0 && win != 0)
  mViewport->mViewport = win->addViewport(camera);

}

SmartViewport::SmartViewport(SmartCamera& camera, SmartWindow& win)
: mViewport(new OgreViewport())
{
 mViewport->mCamera = (*camera);
 mViewport->mViewport = 0;
 mViewport->mWindow = (*win);
 mViewport->mID = 0;

 mViewport->mViewport = mViewport->mWindow->addViewport(mViewport->mCamera);
}

SmartViewport::SmartViewport(const SmartViewport& other)
: mViewport(other.mViewport)
{
}

SmartViewport::~SmartViewport()
{
}

SmartViewport& SmartViewport::operator=(SmartViewport& other)
{
 mViewport = other.mViewport;
 return *this;
}

SmartViewport& SmartViewport::describe()
{
 std::cout << " - ?" << std::endl;
 return *this;
}

std::string SmartViewport::name() const
{
 return _OgreliciousToString(mViewport->mID);
}

SmartViewport& SmartViewport::background(const Ogre::ColourValue& colour)
{
 mViewport->mViewport->setBackgroundColour(colour);
 return *this;
}

SmartViewport& SmartViewport::background(Colour colour)
{
 mViewport->mViewport->setBackgroundColour(ColourToRGBA(colour));
 return *this;
}

Ogre::ColourValue SmartViewport::background() const
{
 return mViewport->mViewport->getBackgroundColour();
}

}


// SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES 
//SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES SMARTNODES 

namespace Ogrelicious
{


SmartNode::SmartNode()
: mNode(new OgreSceneNode())
{
}

SmartNode::SmartNode(Ogre::SceneNode* node)
: mNode(new OgreSceneNode())
{
 mNode->mNode = node;
 mNode->mSceneMgr = 0;
 //! \todo Loop through each scenemanger to see if this node is part of it. SLOW but useful.
}

SmartNode::SmartNode(const std::string& name, Ogre::SceneManager* scene_mgr)
: mNode(new OgreSceneNode())
{
 mNode->mSceneMgr = scene_mgr;

 if (insCmpS(name, "root"))
  mNode->mNode = mNode->mSceneMgr->getRootSceneNode();
 else if (mNode->mSceneMgr->hasSceneNode(name))
  mNode->mNode = mNode->mSceneMgr->getSceneNode(name);
 else
  mNode->mNode = mNode->mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
}

SmartNode::SmartNode(unsigned int integer_name, Ogre::SceneManager* scene_mgr)
: mNode(new OgreSceneNode())
{
 mNode->mSceneMgr = scene_mgr;

 static std::string name;
 name = _OgreliciousToString(integer_name);

 if (mNode->mSceneMgr->hasSceneNode(name))
  mNode->mNode = mNode->mSceneMgr->getSceneNode(name);
 else
  mNode->mNode = mNode->mSceneMgr->getRootSceneNode()->createChildSceneNode(name);
}

SmartNode::SmartNode(const SmartNode& other)
: mNode(other.mNode)
{
}

SmartNode& SmartNode::operator=(SmartNode& other)
{
 mNode = other.mNode;

 return *this;
}

SmartNode::~SmartNode()
{
}

SmartNode SmartNode::add(const Ogre::String& name)
{
 SmartNode node(name, mNode->mSceneMgr);
 if ((*node) == 0)
  return node;

 node->getParentSceneNode()->removeChild((*node));
 mNode->mNode->addChild((*node));
 return node;
}

SmartNode SmartNode::add(unsigned int int_val)
{
 SmartNode node(int_val, mNode->mSceneMgr);
 if ((*node) == 0)
  return node;

 node->getParentSceneNode()->removeChild((*node));
 mNode->mNode->addChild((*node));
 return node;
}

SmartNode& SmartNode::describe()
{
 if (mNode->mNode)
  std::cout << "Node " << mNode->mNode->getName() << std::endl;
 return *this;
}

std::string SmartNode::name()
{
 if (mNode->mNode)
  return mNode->mNode->getName();
 else
  return Ogre::StringUtil::BLANK;
}

SmartNodes SmartNode::nodes()
{
 SmartNodes nodes;
 if (mNode->mNode == 0)
  return nodes;

 Ogre::Node::ChildNodeIterator iterator = mNode->mNode->getChildIterator();
 while(iterator.hasMoreElements())
 {
  nodes.add(SmartNode((Ogre::SceneNode*)iterator.getNext()));
 }

 return nodes;
}
#if 0
Ogre::Entity* SmartNode::entity(SingleAccessor)
{
}
#endif

Ogre::Entity* SmartNode::entity(const Ogre::String& mesh_name, const Ogre::String& entity_name)
{

 if (mNode->mNode == 0 || mNode->mSceneMgr == 0 || mesh_name.size() == 0)
  return 0;
#if 0
 Ogre::SceneNode::ObjectIterator it = mNode->mNode->getAttachedObjectIterator();
 while(it.hasMoreElements())
 {
  Ogre::MovableObject* movable_object = it.getNext();
  if (movable_object->getName() ==  && movable_object->getMovableType() == "Entity")
   return (Ogre::Entity*) movable_object;
 }
#endif

 Ogre::Entity* entity = 0;
 if (entity_name.size() == 0)
 {
   static std::string name;
   name = mNode->mNode->getName() + "-" + _OgreliciousToString(mNode->mNode->numAttachedObjects());
   entity = mNode->mSceneMgr->createEntity(name, mesh_name);
 }
 else
  entity = mNode->mSceneMgr->createEntity(entity_name, mesh_name);

 mNode->mNode->attachObject(entity);

 return entity;
}

SmartNode& SmartNode::operator +=(Ogre::Entity* entity)
{
 if (mNode->mNode && entity)
 {
  if (entity->isAttached())
   entity->getParentSceneNode()->detachObject(entity);
  
  mNode->mNode->attachObject(entity);
 }
 return *this;
}

SmartNode& SmartNode::operator +=(const Ogre::String& str)
{

 if (mNode->mNode == 0 || mNode->mSceneMgr == 0 || str.size() == 0)
  return *this;

 if (Ogre::StringUtil::endsWith(str, ".mesh"))
 {
  static std::string name;
  name = mNode->mNode->getName() + "-" + _OgreliciousToString(mNode->mNode->numAttachedObjects());
  Ogre::Entity* entity = mNode->mSceneMgr->createEntity(name, str);
  mNode->mNode->attachObject(entity);
 }
 else
 {
  Ogre::Entity* entity = mNode->mSceneMgr->getEntity(str);
  if (entity->isAttached())
   entity->getParentSceneNode()->detachObject(entity);
  mNode->mNode->attachObject(entity);
 }
 return *this;
}

SmartNode& SmartNode::operator +=(const Ogre::MeshPtr& mesh)
{
 if (mNode->mNode == 0 || mNode->mSceneMgr == 0)
 {
  _OgreliciousDebug("No node or scenemanager in mNode");
  return *this;
 }

  _OgreliciousDebug("mNode += operator is fine.");
 static std::string name;
  _OgreliciousDebug("  Name is " << name);
 name = mNode->mNode->getName() + "-" + _OgreliciousToString(mNode->mNode->numAttachedObjects());
 Ogre::Entity* entity = mNode->mSceneMgr->createEntity(name, mesh->getName());

 return *this;
}

SmartNode& SmartNode::operator +=(Ogre::SceneNode* node)
{
 if (mNode->mNode == 0 || mNode->mSceneMgr == 0 || node == 0)
  return *this;
 
 if (node->getParent() != NULL)
  node->getParentSceneNode()->removeChild(node);
 
 mNode->mNode->addChild(node);
 return *this;
}

SmartNode& SmartNode::operator +=(SmartNode& node)
{

 if (mNode->mNode == 0 || mNode->mSceneMgr == 0 || (*node)  == 0)
  return *this;
 
 if ( (*node)->getParent() != NULL)
  (*node)->getParentSceneNode()->removeChild((*node));
 
 mNode->mNode->addChild((*node));
 return *this;
}

SmartNode& SmartNode::operator -=(Ogre::Entity* entity)
{
 if (mNode->mNode == 0 || entity == 0)
  return *this;
 
 if (mNode->mNode->getAttachedObject(entity->getName()) == NULL)
  return *this;

 mNode->mNode->detachObject(entity);
 return *this;
}

SmartNode& SmartNode::position(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z)
{
 if (mNode->mNode)
  mNode->mNode->setPosition(x, y, z);
 return *this;
}

SmartNode& SmartNode::position(const Ogre::Vector3& vec)
{
 if (mNode->mNode)
  mNode->mNode->setPosition(vec);
 return *this;
}

Ogre::Vector3 SmartNode::position() const
{
 if (mNode->mNode)
  mNode->mNode->getPosition();
 return Ogre::Vector3::ZERO;
}

SmartNode& SmartNode::x(const Ogre::Real& x)
{
 if (mNode->mNode)
 {
  static Ogre::Vector3 vec;
  vec = mNode->mNode->getPosition();
  mNode->mNode->setPosition(x, vec.y, vec.z);
 }
 return *this;
}

SmartNode& SmartNode::y(const Ogre::Real& y)
{
 if (mNode->mNode)
 {
  static Ogre::Vector3 vec;
  vec = mNode->mNode->getPosition();
  mNode->mNode->setPosition(vec.x, y, vec.z);
 }
 return *this;
}

SmartNode& SmartNode::z(const Ogre::Real& z)
{
 if (mNode->mNode)
 {
  static Ogre::Vector3 vec;
  vec = mNode->mNode->getPosition();
  mNode->mNode->setPosition(vec.x, vec.y, z);
 }
 return *this;
}

Ogre::Real SmartNode::x() const
{
 if (mNode->mNode)
  return mNode->mNode->getPosition().x;
 return 0;
}

Ogre::Real SmartNode::y() const
{
 if (mNode->mNode)
  return mNode->mNode->getPosition().y;
 return 0;
}

Ogre::Real SmartNode::z() const
{
 if (mNode->mNode)
  return mNode->mNode->getPosition().z;
 return 0;
}

SmartNode& SmartNode::orientation(const Ogre::Quaternion& orientation)
{
 if (mNode->mNode)
  mNode->mNode->setOrientation(orientation);
 return *this;
}

Ogre::Quaternion SmartNode::orientation() const
{
 if (mNode->mNode)
  return mNode->mNode->getOrientation();
 return Ogre::Quaternion::IDENTITY;
}

SmartNode& SmartNode::scale(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z)
{
 if (mNode->mNode)
  mNode->mNode->scale(x, y, z);
 return *this;
}

SmartNode& SmartNode::scale(const Ogre::Vector3& vec)
{
 if (mNode->mNode)
  mNode->mNode->scale(vec);
 return *this;
}

Ogre::Vector3 SmartNode::scale() const
{
 if (mNode->mNode)
  mNode->mNode->getScale();
 return Ogre::Vector3::ZERO;
}

SmartNodes::SmartNodes()
: Many()
{
}

SmartNodes::SmartNodes(Ogre::SceneManager* scene_mgr, const std::string& csa)
{
 fill_csa1<SmartNodes, Ogre::SceneManager*>(csa, *this, scene_mgr);
}

SmartNodes::SmartNodes(const SmartNodes& other)
: Many(other.mAssociates)
{
}

SmartNodes& SmartNodes::operator=(const SmartNodes& other)
{
 mAssociates = other.mAssociates;
 return *this;
}

SmartNodes::~SmartNodes()
{
}

SmartNodes& SmartNodes::describe(SimpleAccessor accessor)
{
 std::cout << "Of SmartNodes" << std::endl;
 SAEach<SmartNodes>(accessor, getIterator(), &SmartNode::describe);
 return *this;
}

}

// SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS 
//SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS SMARTMATERIALS 

namespace Ogrelicious
{
#if 0
SmartMaterials::SmartMaterials()
: Many()
{
}

SmartMaterials::SmartMaterials(const SmartMaterials& other)
: Many(other.mAssociates)
{
}

SmartMaterials& SmartMaterials::operator=(const SmartMaterials& other)
{
 mAssociates = other.mAssociates;
 return *this;
}

SmartMaterials::~SmartMaterials()
{
}
#endif

SmartMaterial::SmartMaterial(const Ogre::MaterialPtr& mat)
{
 mMaterial = mat;
}

SmartMaterial::SmartMaterial(const Ogre::String& name, const Ogre::String& group)
{
 mMaterial = Ogre::MaterialManager::getSingletonPtr()->getByName(name);
 if (mMaterial.isNull() == false)
  return;
 mMaterial = Ogre::MaterialManager::getSingletonPtr()->create(name, group);
}

SmartMaterial::SmartMaterial(unsigned int int_val, const Ogre::String& group)
{
 static Ogre::String name;
 name = _OgreliciousToString(int_val);
 mMaterial = Ogre::MaterialManager::getSingletonPtr()->getByName(name);
 if (mMaterial.isNull() == false)
  return;
 mMaterial = Ogre::MaterialManager::getSingletonPtr()->create(name, group);
}

SmartMaterial::SmartMaterial(const SmartMaterial& other)
: mMaterial(other.mMaterial)
{
}

SmartMaterial::~SmartMaterial()
{
}

SmartMaterial& SmartMaterial::operator=(SmartMaterial& other)
{
 mMaterial = other.mMaterial;
 return *this;
}

SmartMaterial& SmartMaterial::describe()
{
 std::cout << " - ?" << std::endl;
 return *this;
}

std::string SmartMaterial::name() const
{
 return mMaterial->getName();
}

SmartMaterial& SmartMaterial::ambient(const Ogre::ColourValue& colour)
{
 mMaterial->setAmbient(colour);
 return *this;
}

SmartMaterial& SmartMaterial::ambient(const Colour& colour, Ogre::Real alpha)
{
 mMaterial->setAmbient(ColourToRGBA(colour, alpha));
 return *this;
}

SmartMaterial& SmartMaterial::diffuse(const Ogre::ColourValue& colour)
{
 mMaterial->setDiffuse(colour);
 return *this;
}

SmartMaterial& SmartMaterial::diffuse(const Colour& colour, Ogre::Real alpha)
{
 mMaterial->setDiffuse(ColourToRGBA(colour, alpha));
 return *this;
}

SmartMaterial& SmartMaterial::specular(const Ogre::ColourValue& colour)
{
 mMaterial->setSpecular(colour);
 return *this;
}

SmartMaterial& SmartMaterial::specular(const Colour& colour, Ogre::Real alpha)
{
 mMaterial->setSpecular(ColourToRGBA(colour, alpha));
 return *this;
}

}

// SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG 
//SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG SMARTCONFIG 

namespace Ogrelicious
{

SmartConfig::SmartConfig()
: mConfig(new Config)
{
}

SmartConfig::SmartConfig(const std::string& configuration_string)
: mConfig(new Config)
{
}

SmartConfig& SmartConfig::load(const Ogre::String& file_name)
{
 std::ifstream file(file_name.c_str(), std::fstream::in | std::fstream::binary);
 
 Ogre::String section_name = "General";
 Ogre::DataStreamPtr stream(new Ogre::FileStreamDataStream(&file, false));
 Ogre::String line;
 mConfig->mComment = Ogre::String();
 while(!stream->eof())
 {
  line = stream->getLine();
  Ogre::StringUtil::trim(line);

  if (line.length() == 0)
   continue;

  if (line[0] == '#') // Comment
  {
   mConfig->mComment.append(line.substr(1, line.length() - 1));
   mConfig->mComment.append("\n");
   continue;
  }
  else if (line[0] == '[') // Section
  {
   if (Ogre::StringUtil::endsWith(line, "]", false))
    section_name = line.substr(1, line.length() - 2);
   else
    section_name = line.substr(1, line.length() - 1);
  }
  else
  {
   Ogre::StringVector strs = Ogre::StringUtil::split(line, "=:", 2);
   if (strs.size() == 2)
    mConfig->mSections[section_name][strs[0]] = strs[1];
   continue;
  }
 }

 file.close();

 return *this;
}

SmartConfig& SmartConfig::scribe()
{
 std::cout << "Of SmartConfig-" << std::endl;

 std::cout << "Comment" << std::endl << "{" << std::endl;
 Ogre::StringVector strs = Ogre::StringUtil::split(mConfig->mComment, "\n");
 for (Ogre::StringVector::iterator it = strs.begin(); it != strs.end(); it++)
  std::cout << "\t" << (*it) << std::endl;
 std::cout << "}" << std::endl;

 for(SectionsIt secs_it = mConfig->mSections.begin(); secs_it != mConfig->mSections.end();secs_it++)
 {
  std::cout << "Section '" << (*secs_it).first << "'" << std::endl << "{" << std::endl;
  for (SectionIt sec_it = (*secs_it).second.begin(); sec_it != (*secs_it).second.end();sec_it++)
   std::cout << "\t'" << (*sec_it).first << "' => '" << (*sec_it).second << "'" << std::endl;
  std::cout << "}" << std::endl;
 }
 return *this;
}

SmartConfig& SmartConfig::save(const Ogre::String& file_name)
{
 std::fstream file(file_name.c_str(), std::fstream::out);
 
 Ogre::StringVector strs = Ogre::StringUtil::split(mConfig->mComment, "\n");
 for (Ogre::StringVector::iterator it = strs.begin(); it != strs.end(); it++)
  file << "#" << (*it) << std::endl;

 for(SectionsIt secs_it = mConfig->mSections.begin(); secs_it != mConfig->mSections.end();secs_it++)
 {
  file << "[" << (*secs_it).first << "]" << std::endl;
  for (SectionIt sec_it = (*secs_it).second.begin(); sec_it != (*secs_it).second.end();sec_it++)
   file << (*sec_it).first << "=" << (*sec_it).second << std::endl;
 }
 file.close();
 return *this;
}

SmartConfig& SmartConfig::set(const Ogre::String& section, const Ogre::String& key, const Ogre::String& value)
{
 Ogre::String section_name = section;
 fixString(section_name);
 mConfig->mSections[section_name][key] = value;
 return *this;
}

SmartConfig& SmartConfig::from(SmartPlugins& plugins, const Ogre::String& key)
{
 SmartPlugins::MapIt iterator = plugins.getIterator();
 while(iterator.hasMoreElements())
  from(iterator.getNextValue(), key);
 return *this;
}

SmartConfig& SmartConfig::from(SmartPlugin& plugin, const Ogre::String& key)
{
 if (plugin.isRenderSystem())
  mConfig->mSections[key]["RenderSystems"].append(plugin.name() + " ");
 else
  mConfig->mSections[key]["Plugins"].append(plugin.name() + " ");
 return *this;
}

SmartConfig& SmartConfig::from(SmartWindow& window, const Ogre::String& key)
{
 mConfig->mSections[key]["Width"] = _OgreliciousToString(window.width());
 mConfig->mSections[key]["Height"] = _OgreliciousToString(window.height());
 mConfig->mSections[key]["Depth"] = _OgreliciousToString(window.depth());
 mConfig->mSections[key]["Fullscreen"] = _OgreliciousToString(window.fullscreen());
 mConfig->mSections[key]["Left"] = _OgreliciousToString(window.left());
 mConfig->mSections[key]["Top"] = _OgreliciousToString(window.top());
 mConfig->mSections[key]["FSAA"] = _OgreliciousToString(window.fsaa());
 mConfig->mSections[key]["Frequency"] = _OgreliciousToString(window.frequency());
 mConfig->mSections[key]["VSync"] = _OgreliciousToString(window.vsync());
 mConfig->mSections[key]["Title"] = window.title();
 //mConfig->mSections[key]["Border"] = _OgreliciousToString(window.border());

 StringMap attr = window.attributes();

 Ogre::String att_key = key;
 att_key.append("|Attributes");
 for (StringMap::iterator it = attr.begin(); it != attr.end(); it++)
  mConfig->mSections[att_key][(*it).first] = (*it).second;

 return *this;
}

#define PossibleToWindow(__String, __Then, __As) \
{PossibleString v=get(section_name,__String);if(!v.isNull)window.__Then(Ogre::StringConverter::__As(v.val));}
#define PossibleToWindow1(__String, __Then) \
{PossibleString v=get(section_name,__String);if(!v.isNull)window.__Then(v);}

SmartWindow SmartConfig::toSmartWindow(const Ogre::String& window_name, const Ogre::String& section_name, const Ogre::String& attributes_section)
{
 
 Sections::iterator secs_it = mConfig->mSections.find(section_name);
 if (secs_it == mConfig->mSections.end())
  return SmartWindow(window_name);
 
 SmartWindow window(window_name);

 PossibleToWindow("Width", width, parseUnsignedInt);
 PossibleToWindow("Height", height, parseUnsignedInt);
 PossibleToWindow("Depth", depth, parseUnsignedInt);
 PossibleToWindow("Fullscreen", fullscreen, parseBool);
 PossibleToWindow("Left", left, parseUnsignedInt);
 PossibleToWindow("Top", top, parseUnsignedInt);
 PossibleToWindow("FSAA", top, parseUnsignedInt);
 PossibleToWindow("Frequency", frequency, parseUnsignedInt);
 PossibleToWindow("VSync", vsync, parseBool);
 PossibleToWindow1("Title", title);

 return window;
}

#undef PossibleToWindow
#undef PossibleToWindow1

PossibleString SmartConfig::get(const Ogre::String& section, const Ogre::String& key) const
{
 PossibleString string;
 string.isNull = true;

 Sections::iterator secs_it = mConfig->mSections.find(section);
 if (secs_it == mConfig->mSections.end())
  return string;

 Section::iterator sec_it = (*secs_it).second.find(key);
 if (sec_it == (*secs_it).second.end())
   return string;

 string.val = (*sec_it).second;
 string.isNull = false;
 return string;
}

SmartPlugins SmartConfig::toSmartPlugins(const Ogre::String& section_name)
{

 Ogre::String plugins_string;
 
 PossibleString rss = get(section_name, "RenderSystems");
 if (!rss.isNull)
 {
  Ogre::StringVector rs_str = Ogre::StringUtil::split(rss);
  for (Ogre::StringVector::iterator it = rs_str.begin(); it != rs_str.end();it++)
   plugins_string.append("RenderSystem: ").append((*it)).append(", ");
 }
 
 PossibleString ps = get(section_name, "Plugins");
 if (!ps.isNull)
 {
  Ogre::StringVector ps_str = Ogre::StringUtil::split(ps);
  for (Ogre::StringVector::iterator it = ps_str.begin(); it != ps_str.end();it++)
   plugins_string.append("Plugin: ").append((*it)).append(", ");
 }

 if (plugins_string.length())
  plugins_string = plugins_string.substr(0, plugins_string.length() - 2);
 return SmartPlugins(plugins_string);
}

SmartConfig& SmartConfig::comment(const Ogre::String& comment)
{
 mConfig->mComment = comment;
 return *this;
}

Ogre::String SmartConfig::comment() const
{
 return mConfig->mComment;
}

void SmartConfig::fixString(Ogre::String& str)
{
 Ogre::StringUtil::toLowerCase(str);
 str[0] = toupper(str[0]);
}

bool SmartConfig::getAsBool(const Ogre::String& section, const Ogre::String& key, bool default_value) const
{
  Sections::iterator secs_it = mConfig->mSections.find(section);
 if (secs_it == mConfig->mSections.end())
  return default_value;

 Section::iterator sec_it = (*secs_it).second.find(key);
 if (sec_it == (*secs_it).second.end())
   return default_value;

 return Ogre::StringConverter::parseBool((*sec_it).second);
}

Ogre::String SmartConfig::getAsString(const Ogre::String& section, const Ogre::String& key, Ogre::String default_value) const
{
 Sections::iterator secs_it = mConfig->mSections.find(section);
 if (secs_it == mConfig->mSections.end())
  return default_value;

 Section::iterator sec_it = (*secs_it).second.find(key);
 if (sec_it == (*secs_it).second.end())
   return default_value;

 return (*sec_it).second;
}


float SmartConfig::getAsFloat(const Ogre::String& section, const Ogre::String& key, float default_value) const
{
 Sections::iterator secs_it = mConfig->mSections.find(section);
 if (secs_it == mConfig->mSections.end())
  return default_value;

 Section::iterator sec_it = (*secs_it).second.find(key);
 if (sec_it == (*secs_it).second.end())
   return default_value;

 return Ogre::StringConverter::parseReal((*sec_it).second);
}

} // namespace

// SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT 
//SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT SMARTFONT 

namespace Ogrelicious
{

SmartFont::SmartFont()
{
}

SmartFont::SmartFont(const Ogre::FontPtr& font) : mFont(font)
{
}

SmartFont::SmartFont(const Ogre::String& name, const Ogre::String& group)
{
 mFont = Ogre::FontManager::getSingletonPtr()->getByName(name);
 if (mFont.isNull())
 {
  mFont = Ogre::FontManager::getSingleton().create(name, group);
 }
}

SmartFont::SmartFont(const SmartFont& other) : mFont(other.mFont)
{
}

SmartFont& SmartFont::operator=(SmartFont& other)
{
 mFont = other.mFont;
 return *this;
}

SmartFont::~SmartFont()
{
}

SmartFont& SmartFont::describe()
{
 if (mFont.isNull() == false)
  std::cout << "Font " << mFont->getName() << std::endl;
 return *this;
}

std::string SmartFont::name() const
{
 if (mFont.isNull() == false)
  return mFont->getName();
 else
  return Ogre::StringUtil::BLANK;
}

SmartFont& SmartFont::source(const Ogre::String& filename)
{
 if (!mFont.isNull())
  mFont->setSource(filename);
 return *this;
}

SmartFont& SmartFont::type(Ogre::FontType ft)
{
 if (!mFont.isNull())
  mFont->setType(ft);
 return *this;
}

SmartFont& SmartFont::size(Ogre::Real size)
{
 if (!mFont.isNull())
  mFont->setTrueTypeSize(size);
 return *this;
}

SmartFont& SmartFont::resolution(Ogre::uint resolution)
{
 if (!mFont.isNull())
  mFont->setTrueTypeResolution(resolution);
 return *this;
}

SmartFont& SmartFont::pointRange(Ogre::uint lower, Ogre::uint higher)
{
 if (!mFont.isNull())
  mFont->addCodePointRange(Ogre::Font::CodePointRange(lower, higher));
 return *this;
}
 
SmartOverlay::SmartOverlay()
{
}
 
SmartOverlay::SmartOverlay(const Ogre::String& caption, unsigned int zOrder)
: mOverlay(new OgreOverlay())
{
 std::string name = "___" + Ogre::StringConverter::toString(_OgreliciousNextOverlayID++);
 Ogre::FontPtr font = Ogre::FontManager::getSingletonPtr()->getResourceIterator().getNext();
 mOverlay->__create(name, caption, font->getName(), zOrder);
}

SmartOverlay::SmartOverlay(const Ogre::String& caption, const Ogre::String& name, const Ogre::String& font, unsigned int zOrder)
: mOverlay(new OgreOverlay())
{
  mOverlay->__create(name, caption, font, zOrder);
}

void SmartOverlay::OgreOverlay::__create(const std::string& name, const std::string& caption, const std::string& font, unsigned int zOrder)
{
 std::string overlayName = "__" + Ogre::StringConverter::toString(zOrder);
 mOverlay = Ogre::OverlayManager::getSingletonPtr()->getByName(overlayName);
 if (mOverlay == 0)
 {
  mOverlay = Ogre::OverlayManager::getSingletonPtr()->create(overlayName);
  mOverlay->setZOrder(zOrder);
  mOverlay->show();
 }
 mOverlayContainer = static_cast<Ogre::OverlayContainer*>(
        Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", name + "Panel") 
                     );
 mOverlayContainer->setPosition(0,0);
 mOverlayContainer->setDimensions(0.1,0.1);
 
 mOverlayText = static_cast<Ogre::TextAreaOverlayElement*>(
        Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("TextArea", name + "Text")
                     );
 
 mOverlayText->setFontName(font);
 mOverlayText->setCharHeight(12);
 mOverlayText->setCaption(caption);
 mOverlayText->setPosition(0,0);
 mOverlay->add2D(mOverlayContainer);
 mOverlayContainer->addChild(mOverlayText);
}

SmartOverlay::SmartOverlay(const SmartOverlay& other)
: mOverlay(other.mOverlay)
{
}

SmartOverlay& SmartOverlay::operator=(SmartOverlay& other)
{
 mOverlay = other.mOverlay;
 return *this;
}

SmartOverlay::~SmartOverlay()
{
}

SmartOverlay& SmartOverlay::describe()
{
 std::cout << mOverlay->mOverlay->getName() << ":" << mOverlay->mOverlayContainer->getName();
 return *this;
}

std::string SmartOverlay::name() const
{
 return mOverlay->mOverlayContainer->getName();
}

SmartOverlay& SmartOverlay::caption(const Ogre::String& caption)
{
 mOverlay->mOverlayContainer->setCaption(caption);
 return *this;
}

Ogre::String SmartOverlay::caption() const
{
 return mOverlay->mOverlayContainer->getCaption();
}

SmartOverlay& SmartOverlay::position(const Ogre::Vector2& vec)
{
 Ogre::GuiMetricsMode originalMode = mOverlay->mOverlayContainer->getMetricsMode();

 if (vec.x > 1 || vec.y > 1)
 {
  mOverlay->mOverlayContainer->setMetricsMode(Ogre::GMM_PIXELS);
  mOverlay->mOverlayContainer->setPosition(vec.x, vec.y);
 }
 else
 {
  mOverlay->mOverlayContainer->setMetricsMode(Ogre::GMM_RELATIVE);
  mOverlay->mOverlayContainer->setPosition(vec.x, vec.y);
 }
 mOverlay->mOverlayContainer->setMetricsMode(originalMode);
 return *this;
}

Ogre::Vector2 SmartOverlay::position() const
{
 return Ogre::Vector2(mOverlay->mOverlayContainer->getLeft(), mOverlay->mOverlayContainer->getTop());
}

SmartOverlay& SmartOverlay::size(const Ogre::Vector2& vec)
{
 Ogre::GuiMetricsMode originalMode = mOverlay->mOverlayContainer->getMetricsMode();

 if (vec.x > 1 || vec.y > 1)
 {
  mOverlay->mOverlayContainer->setMetricsMode(Ogre::GMM_PIXELS);
  mOverlay->mOverlayContainer->setDimensions(vec.x, vec.y);
 }
 else
 {
  mOverlay->mOverlayContainer->setMetricsMode(Ogre::GMM_RELATIVE);
  mOverlay->mOverlayContainer->setDimensions(vec.x, vec.y);
 }
 mOverlay->mOverlayContainer->setMetricsMode(originalMode);
 return *this;
}

Ogre::Vector2 SmartOverlay::size() const
{
 return Ogre::Vector2(mOverlay->mOverlayContainer->getWidth(), mOverlay->mOverlayContainer->getHeight());
}

SmartOverlay& SmartOverlay::left(const Ogre::Real& l)
{
 mOverlay->mOverlayContainer->setLeft(l);
 return *this;
}

Ogre::Real SmartOverlay::left() const
{
 return mOverlay->mOverlayContainer->getLeft();
}

SmartOverlay& SmartOverlay::top(const Ogre::Real& t)
{
 mOverlay->mOverlayContainer->setTop(t);
 return *this;
}

Ogre::Real SmartOverlay::top() const
{
 return mOverlay->mOverlayContainer->getTop();
}

SmartOverlay& SmartOverlay::colour(::Ogrelicious::Colour colour)
{
 mOverlay->mOverlayContainer->setColour(ColourToRGBA(colour));
 return *this;
}

SmartOverlay& SmartOverlay::colour(const Ogre::ColourValue& colour)
{
 mOverlay->mOverlayContainer->setColour(colour);
 return *this;
}

} // Ogrelicious namespace

//////////////////////////////////////////////////////////////////////////////
// End of Ogrelicious.cpp
//////////////////////////////////////////////////////////////////////////////
