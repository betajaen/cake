/*
 * Ogrelicious
 * 
 * File:    Ogrelicious.h
 * Version: 0.0.91
 * 
 * Copyright (c) 2008-2009 Robin "betajaen" Southern.
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

#ifndef Ogrelicious_0_0_91_H
#define Ogrelicious_0_0_91_H

                                                                                       

#include "OgrePrerequisites.h"
#include "OgreMath.h"
#include "OgreSharedPtr.h"
#include "OgreSingleton.h"
#include "OgreFrameListener.h"
#include "OgreWindowEventUtilities.h"
#include "OgreMaterial.h"
#include "OgreResourceGroupManager.h"
#include "OgreFont.h"
#include "OgreOverlayElement.h"
#include "OgreTextAreaOverlayElement.h"

                                                                                       

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
# define WIN32_LEAN_AND_MEAN
# include "windows.h"
#endif

#ifdef OGRELICIOUS_LOVES_OIS
# include "ois/ois.h"
#endif

                                                                                       

#define OGRELICIOUS_MOUSE_POINTER_IMAGE "OgreliciousMousePointer"

//! Ogrelicious, Yummy.
namespace Ogrelicious
{
  namespace Colours
  {
   enum WebColours
   {
    AliceBlue=0xf0f8ff,       Gainsboro=0xdcdcdc,             MistyRose=0xffe4e1,
    AntiqueWhite=0xfaebd7,    GhostWhite=0xf8f8ff,            Moccasin=0xffe4b5,
    Aqua=0x00ffff,            Gold=0xffd700,                  NavajoWhite=0xffdead,
    Aquamarine=0x7fffd4,      Goldenrod=0xdaa520,             Navy=0x000080,
    Azure=0xf0ffff,           Gray=0x808080,                  OldLace=0xfdf5e6,
    Beige=0xf5f5dc,           Green=0x008000,                 Olive=0x808000,
    Bisque=0xffe4c4,          GreenYellow=0xadff2f,           OliveDrab=0x6b8e23,
    Black=0x000000,           Grey=0x808080,                  Orange=0xffa500,
    BlanchedAlmond=0xffebcd,  Honeydew=0xf0fff0,              OrangeRed=0xff4500,
    Blue=0x0000ff,            HotPink=0xff69b4,               Orchid=0xda70d6,
    BlueViolet=0x8a2be2,      IndianRed=0xcd5c5c,             PaleGoldenrod=0xeee8aa,
    Brown=0xa52a2a,           Indigo=0x4b0082,                PaleGreen=0x98fb98,
    Burlywood=0xdeb887,       Ivory=0xfffff0,                 PaleTurquoise=0xafeeee,
    CadetBlue=0x5f9ea0,       Khaki=0xf0e68c,                 PaleVioletRed=0xdb7093,
    Chartreuse=0x7fff00,      Lavender=0xe6e6fa,              PapayaWhip=0xffefd5,
    Chocolate=0xd2691e,       LavenderBlush=0xfff0f5,         PeachPuff=0xffdab9,
    Coral=0xff7f50,           LawnGreen=0x7cfc00,             Peru=0xcd853f,
    CornflowerBlue=0x6495ed,  LemonChiffon=0xfffacd,          Pink=0xffc0cb,
    Cornsilk=0xfff8dc,        LightBlue=0xadd8e6,             Plum=0xdda0dd,
    Crimson=0xdc143c,         LightCoral=0xf08080,            PowderBlue=0xb0e0e6,
    Cyan=0x00ffff,            LightCyan=0xe0ffff,             Purple=0x800080,
    DarkBlue=0x00008b,        LightGoldenrodyellow=0xfafad2,  Red=0xff0000,
    DarkCyan=0x008b8b,        LightGray=0xd3d3d3,             RosyBrown=0xbc8f8f,
    DarkGoldenrod=0xb8860b,   LightGreen=0x90ee90,            RoyalBlue=0x4169e1,
    DarkGray=0xa9a9a9,        LightGrey=0xd3d3d3,             SaddleBrown=0x8b4513,
    DarkGreen=0x006400,       LightPink=0xffb6c1,             Salmon=0xfa8072,
    DarkGrey=0xa9a9a9,        LightSalmon=0xffa07a,           SandyBrown=0xf4a460,
    DarkKhaki=0xbdb76b,       LightSeagreen=0x20b2aa,         SeaGreen=0x2e8b57,
    DarkMagenta=0x8b008b,     LightSkyblue=0x87cefa,          SeaShell=0xfff5ee,
    DarkOlivegreen=0x556b2f,  LightSlategray=0x778899,        Sienna=0xa0522d,
    DarkOrange=0xff8c00,      LightSlategrey=0x778899,        Silver=0xc0c0c0,
    DarkOrchid=0x9932cc,      LightSteelblue=0xb0c4de,        SkyBlue=0x87ceeb,
    DarkRed=0x8b0000,         LightYellow=0xffffe0,           SlateBlue=0x6a5acd,
    DarkSalmon=0xe9967a,      Lime=0x00ff00,                  SlateGray=0x708090,
    DarkSeagreen=0x8fbc8f,    LimeGreen=0x32cd32,             SlateGrey=0x708090,
    DarkSlateblue=0x483d8b,   Linen=0xfaf0e6,                 Snow=0xfffafa,
    DarkSlategray=0x2f4f4f,   Magenta=0xff00ff,               SpringGreen=0x00ff7f,
    DarkSlategrey=0x2f4f4f,   Maroon=0x800000,                SteelBlue=0x4682b4,
    DarkTurquoise=0x00ced1,   MediumAquamarine=0x66cdaa,      Tan=0xd2b48c,
    DarkViolet=0x9400d3,      MediumBlue=0x0000cd,            Teal=0x008080,
    DeepPink=0xff1493,        MediumOrchid=0xba55d3,          Thistle=0xd8bfd8,
    DeepSkyblue=0x00bfff,     MediumPurple=0x9370db,          Tomato=0xff6347,
    DimGray=0x696969,         MediumSeaGreen=0x3cb371,        Turquoise=0x40e0d0,
    DimGrey=0x696969,         MediumSlateBlue=0x7b68ee,       Violet=0xee82ee,
    DodgerBlue=0x1e90ff,      MediumSpringGreen=0x00fa9a,     Wheat=0xf5deb3,
    FireBrick=0xb22222,       MediumTurquoise=0x48d1cc,       White=0xffffff,
    FloralWhite=0xfffaf0,     MediumBioletRed=0xc71585,       WhiteSmoke=0xf5f5f5,
    ForestGreen=0x228b22,     MidnightBlue=0x191970,          Yellow=0xffff00,
    Fuchsia=0xff00ff,         MintCream=0xf5fffa,             YellowGreen=0x9acd32,
                                                              NumberOfColours
   }; // enum WebColours
  } // namespace
  enum
  {
   // Events                      // Selectors & Properties           // Internals                 
   _onDraw        = -1,            _None             = 0,              uint_max       = 0xffffFFFF, 
   _onLoad        = -2,            _First            = 1,              ushort_max     = 0xffFF,     
   _onUnload      = -3,            _Last             = 2,              uchar_max      = 0xff,       
   _onMove        = -4,            _Odd              = 3,              _NoChannel     = uint_max,   
   _onResize      = -5,            _Even             = 4,              _NoHandler     = uint_max,   
   _onFocus       = -6,            _Everything       = 5,              _TTF_Font      = Ogre::FT_TRUETYPE,
   _onClick       = -7,            _NoBorder         = 0,              _Bitmap_Font   = Ogre::FT_IMAGE,
   _onDblClick    = -8,            _FixedBorder      = 1,              
   _onBeginFrame  = -9,            _ResizableBorder  = 2,              
   _onEndFrame    = -10,           _NoAutoWindow     = 0,              
   _onKeyReleased = -11,           _AutoCreateWindow = 1,              
   _onKeyPressed  = -12,           _HorizontallyCenter = uint_max,     
   _onMouseMoved  = -13,           _VerticallyCenter   = uint_max,     
   _onMouseButtonPressed=-14,      _OperatingSystemMouse = 0,          
   _onMouseButtonReleased=-15,     _OgreOverlayMouse     = 1,          
  }; // enum

  class SmartCallback;            class SmartWindow;                  class SmartNodes;
  class SmartPlugin;              class SmartWindows;                 class EventSystem;
  class SmartPlugins;             class SmartCameras;                 class Core;
  class SmartRenderSystem;        class SmartCamera;                  class SmartMaterial;
  class SmartRenderSystems;       class SmartViewports;               class SmartMaterials;
  class SmartResourceGroup;       class SmartViewport;                struct KeyEvent;
  class SmartResourceGroups;      class SmartNode;                    struct MouseEvent;
  class SmartFont;                class SmartConfig;                  class SmartOverlay;

  typedef SmartPlugins _Plugins;                        typedef SmartRenderSystems _RenderSystems;
  typedef SmartPlugin  _Plugin;                         typedef SmartRenderSystem  _RenderSystem;
  typedef SmartResourceGroups _ResourceGroups;          typedef SmartWindows _Windows;
  typedef SmartResourceGroup _ResourceGroup;            typedef SmartWindow _Window;
  typedef SmartCallback _Callback;                      typedef SmartCameras _Cameras;
  typedef SmartNode _Node;                              typedef SmartCamera _Camera;
  typedef SmartNodes _Nodes;                            typedef SmartMaterial _Material;
  typedef SmartMaterials _Materials;                    typedef int SimpleAccessor;
  typedef int SingleAccessor;                           typedef int PluralAccessor;
  typedef int Colour;                                   typedef int EventType;
  typedef int WindowBorder;                             template<class RepresentativeT> class Many;
  typedef int MouseType;                                typedef SmartFont _Font;
  typedef SmartOverlay _Overlay;

  template<class OgreClassT> class Representative;      template<typename T> class FastConstIterator;
  template<typename T> class FastConstMapIterator;      typedef std::map<Ogre::String, Ogre::String> StringMap;
  //! Short cut to new Ogre() and initalises Ogrelicious instance. Not exactly required, but useful.
  Ogre::Root* startOgre(const std::string& log_name = "Ogre.log");
  //! Short cut to Ogre::getSingletonPtr()->init();
  void initialiseOgre(bool auto_create_window, const std::string& window_name = "Ogre Window");
  //! Short cut delete Ogre and kills the Ogrelicious instance (and those near it).
  void stopOgre();
  //! Converts a Colour enum to a Ogre Colour value
  Ogre::ColourValue ColourToRGBA(Colour, Ogre::Real Alpha = 1.0f);
  //! Shortcut to EventSystem::instance()
  EventSystem* _Events();
  //! Managed value.
  template <typename T> struct PossibleValue
  {
   T val;
   bool isNull;
   operator T()
   {
   return val;
   }
  };
  //! PossibleString.
  typedef PossibleValue<Ogre::String> PossibleString;
  //! Debug Function
  template <class ManyClass> void _OgreliciousDebugPrint(typename ManyClass::MapIt& iterator)
  {
   while(iterator.hasMoreElements())
   {
    iterator.next();
   }
  }
  //! Internal Helper function
  template <class ManyClass> void fill_all_ptr(ManyClass& many, FastConstIterator< std::vector<typename ManyClass::RepresentativeClass::OgreT*> >& iterator)
  {
   while(iterator.hasMoreElements())
   {
    many.add(ManyClass::RepresentativeClass(iterator.getValue()));
    iterator.next();
   }
  }
  //! Internal Helper function
  template <class ManyClass> void fill_all(ManyClass& many, FastConstIterator< std::vector<typename ManyClass::RepresentativeClass::OgreT> >& iterator)
  {
   while(iterator.hasMoreElements())
   {
    many.add(ManyClass::RepresentativeClass(iterator.getValue()));
    iterator.next();
   }
  }
  //! Internal Helper function
  template <class ManyClass> void fill_csa(const std::string& csa, ManyClass& many)
  {
   Ogre::StringVector strings = Ogre::StringUtil::split(csa, ",");
   for (Ogre::StringVector::iterator it = strings.begin(); it != strings.end();it++)
   {
    Ogre::StringUtil::trim((*it));
    many.add(ManyClass::RepresentativeClass((*it)));
   }
  }
  //! Internal Helper function
  template <class ManyClass, typename T> void fill_csa1(const std::string& csa, ManyClass& many, T t)
  {
   Ogre::StringVector strings = Ogre::StringUtil::split(csa, ",");
   for (Ogre::StringVector::iterator it = strings.begin(); it != strings.end();it++)
   {
    Ogre::StringUtil::trim((*it));
    many.add(ManyClass::RepresentativeClass((*it), t));
   }
  }
  //! Internal Helper function
  template <class ManyClass> void SAEach(SimpleAccessor accessor, typename ManyClass::MapIt& iterator, typename ManyClass::RepresentativeClass& (ManyClass::RepresentativeClass::*func)())
  {
   if (accessor == _None) return;
   if (accessor == _First)
   {
    (iterator.getValue().*func)();
    return;
   }
   if (accessor == _Last)
   {
    iterator.last();
    (iterator.getValue().*func)();
    return;
   }
   if (accessor == _Odd)
   {
    while(iterator.hasMoreElements())
    {
      (iterator.getNextValue().*func)();
      iterator.next();
    }
   }
   if (accessor == _Even)
   {
    iterator.next();
    while(iterator.hasMoreElements())
    {
     (iterator.getNextValue().*func)();
     iterator.next();
    }
   }
   while(iterator.hasMoreElements())
   {
    (iterator.getNextValue().*func)();
   }
  }
  //! Internal Helper function
  template <class ManyClass, typename T> void SAEach1(SimpleAccessor accessor, typename ManyClass::MapIt& iterator, typename ManyClass::RepresentativeClass& (ManyClass::RepresentativeClass::*func)(const T&), const T& t_val)
  {
   if (accessor == _None) return;
   if (accessor == _First)
   {
    (iterator.getValue().*func)(t_val);
    return;
   }
   if (accessor == _Last)
   {
    iterator.last();
    (iterator.getValue().*func)(t_val);
   return;
   }
   if (accessor == _Odd)
   {
    while(iterator.hasMoreElements())
    {
      (iterator.getNextValue().*func)(t_val);
      iterator.next();
    }
   }
   if (accessor == _Even)
   {
    iterator.next();
    while(iterator.hasMoreElements())
    {
     (iterator.getNextValue().*func)(t_val);
     iterator.next();
    }
   }
   while(iterator.hasMoreElements())
    (iterator.getNextValue().*func)(t_val);
  }
  //! Optional Singletons. Yeah, seriously.
  template<typename T> class OptionalSingleton
  {
   public:
    //! Create or Get
    static T* Instance()
    {
     if (sInstance == 0)
      sInstance = new T();
     return sInstance;
    }
    //! Kill
    static void KillInstance()
    {
     if (sInstance)
      delete sInstance;
     sInstance = 0;
    }
   protected:
    static T* sInstance;
  }; // class OptionalSingleton
  //! An Ogre-like iterator for the stl vector class.
  template <typename T> class FastConstIterator
  {
   public:
   typename T::iterator mBegin, mCurrent, mEnd;
   //! FastConstIterator constructor;  <code>FastConstIterator(vec.begin(), vec.end())</code>
   FastConstIterator(typename T::iterator start, typename T::iterator end) : mBegin(start), mCurrent(start), mEnd(end) {}
   //! Are we there yet?
   bool hasMoreElements() const
   {
    return mCurrent != mEnd;
   }
   //! Go to the first element in the iterator
   void first()
   {
    mCurrent = mBegin;
   }
   //! Go to the last element in the iterator
   void last()
   {
    mCurrent = mEnd;
   }
   //! Go to the next
   void next()
   {
    ++mCurrent;
   }
   //! Go to the previous
   void prev()
   {
    --mCurrent;
   }
   //! Get the current value of the iterator.
   typename T::value_type getValue(void)
   {
    return (*mCurrent);
   }
   //! Advance the iterator, then return that value.
   typename T::value_type getNextValue(void)
   {
    ++mCurrent;
    return (*mCurrent);
   }
   //! Copy constructor.
   FastConstIterator(const FastConstIterator<T>& other) : mBegin(other.mBegin), mCurrent(other.mCurrent), mEnd(other.mEnd) {}
   //! Assignment operator
   FastConstIterator<T>& operator=(FastConstIterator<T>& other)
   {
    mBegin = other.mBegin;mCurrent = other.mCurrent; mEnd = other.mEnd;
   }
  }; // FastConstIterator
  //! An Ogre-like iterator for the stl map class.
  template <typename T> class FastConstMapIterator
  {
   public:
   typename T::iterator mBegin, mCurrent, mEnd; bool mBlank;
   //! FastConstIterator constructor;  <code>FastConstIterator(map.begin(), map.end())</code> 
   FastConstMapIterator(typename T::iterator start, typename T::iterator end) : mBlank(false), mBegin(start), mCurrent(start), mEnd(end) {}
   //! Are we there yet?
   bool hasMoreElements() const
   {
    return !mBlank && mCurrent != mEnd;
   }
   //! Go to the first element in the iterator
   void first()
   {
    mCurrent = mBegin;
   }
   //! Go to the last element in the iterator
   void last()
   {
    mCurrent = mEnd; mCurrent--;
   }
   //! Go to the next
   void next()
   {
    ++mCurrent;
   }
   //! Go to the previous
   void prev()
   {
    --mCurrent;
   }
   //! Get the current key of the iterator.
   typename T::key_type getKey(void)
   {
    return mCurrent->first;
   }
   //! Get the current value of the iterator.
   typename T::mapped_type getValue(void)
   {
    return mCurrent->second;
   }
   //! Advance the iterator, then return that key.
   typename T::key_type getNextKey(void)
   {
    return (mCurrent++)->first;
   }
   //! Advance the iterator, then return that value.
   typename T::mapped_type getNextValue(void)
   {
    return (mCurrent++)->second;
   }
   //! Blank constructor.
   FastConstMapIterator() : mBlank(true) {}
   //! Copy constructor.
   FastConstMapIterator(const FastConstMapIterator& other) : mBlank(false), mBegin(other.mBegin), mCurrent(other.mCurrent), mEnd(other.mEnd) {}
   //! Assignment operator.
   FastConstMapIterator<T>& operator=(const FastConstMapIterator<T>& other)
   {
    mBegin = other.mBegin; mCurrent = other.mCurrent; mEnd = other.mEnd; mBlank = other.mBlank;
   }
   //! \internal Private constructor. Don't use.
   FastConstMapIterator(typename T& map) : mBegin(map.mBegin), mCurrent(map.mBegin), mEnd(map.mEnd) {}
  }; // class FastConstMapIterator
  //! Inherited by all SmartXXXs 
  template<class RepresentativeT> class Many
  {
   public:
    typedef RepresentativeT                         RepresentativeClass;
    typedef std::map<std::string, RepresentativeT>  MapT;
    typedef std::pair<std::string, RepresentativeT> PairT;
    typedef typename FastConstMapIterator<MapT>     MapIt;
    //! Normal constructor.
    Many() : mAssociates(new MapT()) {} 
    //! Copy constructor.
    Many(const Ogre::SharedPtr< MapT >& mapt) : mAssociates(mapt) {} 
    //! Required destructor.
    virtual ~Many() {}
    //! Add something to the list of Associates
    RepresentativeClass add(RepresentativeClass t) {mAssociates->insert(PairT(t.name(), t)); return t;} 
    //! Fetch something based on a SingleAccessor (_First or _Last) otherwise return the first.
    RepresentativeClass& operator[](SingleAccessor sa)
    {
     if(sa==_Last)  return mAssociates->end();
                    return mAssociates->begin();
    }
    //! Fetch something based on the name.
    RepresentativeClass& operator[](const Ogre::String& name) { return mAssociates->find(name); }
    //! Get a const iterator.
    MapIt getIterator() { return MapIt(mAssociates->begin(), mAssociates->end()); }
   protected:
    //! internal
    Ogre::SharedPtr< MapT > mAssociates;
  }; // class Many
  //! Ogrelicious is a yummy ice-cream flavour. It's made by hand from pack of wild Ogre's in the Swiss mountains.
  class Core : public Ogre::Singleton<::Ogrelicious::Core>
  {
    public:
     //! Shutdown Ogre via returning "false" via a framelistener in the next frame, in turn destroy the Ogrelicious instance, event system, callbacks, and so on.
     void SafeShutdown();
     //! Manually start up Ogrelicious, the Eventsystem and other complicated classes.
     static void init(bool init_event_system = true);
     //! Manually shutdown Ogrelicious
     static void uninit(void);
     //! Get the singleton as a reference
     static Core& getSingleton(void);
     //! Get the singleton as a pointer
     static Core* getSingletonPtr(void);
     //! Get the Screen Width
     static unsigned int getScreenWidth();
     //! Get the Screen Height
     static unsigned int getScreenHeight();
    protected:
     Core(bool init_event_system = true);
     ~Core(void);
  }; // class Ogrelicious
#if defined(OGRELICIOUS_LOVES_OIS) && !defined(OGRELICIOUS_HAS_SMARTINPUTSYSTEM)

  #define OGRELICIOUS_HAS_SMARTINPUTSYSTEM
  class OISInputSystem;
  typedef OISInputSystem     SmartInputSystem;
  typedef OIS::KeyCode       KeyCode;
  typedef OIS::MouseButtonID MouseButton;
  //! OISNullDevice
  class OISNullDevice : public OIS::Object
  {
   public:
    OISNullDevice() {mType = OIS::OISUnknown; mBuffered = false; mDevID = 0;}
    ~OISNullDevice() {}
    void setBuffered(bool buffered) {}
    void capture() {}
    OIS::Interface* queryInterface(OIS::Interface::IType) {return 0;}
    void _initialize() {}
  };
  //! OISInputSystem
  class OISInputSystem : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener, public OptionalSingleton<OISInputSystem>
  {
   friend class OptionalSingleton<EventSystem>;
   public:
    struct WindowBinding
    {
     OIS::InputManager*  mInputSystem;
     OIS::Object*        mDevices[3]; // 0 = Mouse, 1 = Keyboard, 2 = Joystick.
     Ogre::RenderWindow* mWindow;
     unsigned int        mHandle;
     struct HandleKeyPair
     {
      HandleKeyPair(int kc, int handle) : mKeyCode(kc), mHandle(handle) {}
      int mKeyCode, mHandle;
     };
     typedef std::vector<HandleKeyPair> HandleKeyT;
     typedef std::vector<HandleKeyPair>::iterator HandleKeyIterator;
     HandleKeyT mWatchedKeys;
    };
    typedef std::vector<WindowBinding*>  BindingsT;
    typedef BindingsT::iterator          BindingsIterator;
    //! OISInputSystem, constructor. Created by Core as SmartInputSystem
     OISInputSystem();
    //! OISInputSystem, destructor.
    ~OISInputSystem();
    //! Capture input, called by the EventSystem every frame.
    void capture();
    //! Add window, create an InputSystem for it; mouse, keyboard and joystick and create events.
    void addWindow(Ogre::RenderWindow*, unsigned int event_handle, bool exclusiveMouse);
    //! Remove a window, destroy the InputSystem for it, and stop generating events for it.
    void removeWindow(Ogre::RenderWindow*);
    //! Required by OIS::KeyListener
    bool keyPressed(const OIS::KeyEvent &arg);
    //! Required by OIS::KeyListener
    bool keyReleased(const OIS::KeyEvent &arg);
    //! Required by OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg);
    //! Required by OIS::MouseListener
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    //! Required by OIS::MouseListener
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    //! Required by OIS::MouseListener
    bool buttonPressed( const OIS::JoyStickEvent &arg, int button);
    //! Required by OIS::MouseListener
    bool buttonReleased( const OIS::JoyStickEvent &arg, int button);
    //! Required by OIS::MouseListener
    bool axisMoved( const OIS::JoyStickEvent &arg, int axis);
    //! Required by OIS::MouseListener
    bool sliderMoved( const OIS::JoyStickEvent &, int);
    //! Required by OIS::MouseListener
    bool povMoved( const OIS::JoyStickEvent &, int);
    //! Watch key. Fires an event when the key is down (OIS::Keyboard::isKeyDown) using a handle, and using the keycode as the channel id.
    void watchKey(Ogre::RenderWindow*, int handle, int keycode);
    //
    WindowBinding* getWindowBinding(Ogre::RenderWindow*);
    //
    bool keyDown(const OIS::KeyCode&) const;
   protected:
    BindingsT       mBindings;
    OISNullDevice*  mNullDevice;
    KeyEvent*       mKeyEvent;
    MouseEvent*     mMouseEvent;
  };
#endif

#ifndef OGRELICIOUS_HAS_SMARTINPUTSYSTEM
  #define OGRELICIOUS_HAS_SMARTINPUTSYSTEM
  typedef int                KeyCode;
  typedef int                MouseButton;
  //! This is the fallback SmartInputSystem. It *does not* monitor input.
  class SmartInputSystem : public OptionalSingleton<SmartInputSystem>
  {
   public: 
    void capture() {}
    void addWindow(Ogre::RenderWindow*, unsigned int, bool) {}
    void removeWindow(Ogre::RenderWindow*) {}
    bool watchKey(int handle, int keycode) {}
  };
#endif
  struct KeyEvent
  {
   KeyCode keyPressed;
   char    ascii;
   bool    isDown;
  };
  struct MouseEvent
  {
   struct
   {
    int position;
    int delta;
   } x;
   struct
   {
    int position;
    int delta;
   } y;
   struct
   {
    int position;
    int delta;
   } wheel;
   struct
   {
    bool Left : 1;    // 1
    bool Right : 1;   // 2
    bool Middle : 1;  // 3
    bool Fourth : 1;  // 4
    bool Fifth : 1;   // 5
    bool Sixth : 1;   // 6
    bool Seventh : 2; // 7
   } button;
  };
  //! SmartMousePointer
  class SmartMousePointer
  {
   public:
    //! SmartMousePointer using an RenderWindow to use with, Overlay is created or fetched, OverlayContainer is fetched/created.
    SmartMousePointer(SmartWindow&, const Ogre::String mouse_pointer_image = OGRELICIOUS_MOUSE_POINTER_IMAGE);
    //! SmartMousePointer destructor.
   ~SmartMousePointer();
    //! Set the horizontal coordinate of the mouse-pointer.
    void         x(unsigned int);
    //! Get the horizontal coordinate of the mouse-pointer.
    unsigned int x() const;
    //! Set the vertical coordinate of the mouse-pointer.
    void         y(unsigned int);
    //! Get the vertical coordinate of the mouse-pointer.
    unsigned int y() const;
    //! EventSystem binding to move the mouse when the Mouse has moved. It will pinch the window's onMouseMove event.
    void mouseMoved(MouseEvent*);
    Ogre::Overlay*          mOverlay;
    Ogre::OverlayContainer* mOverlayContainer;
  };
  //! Monitors the events on when Ogre starts and ends a frame, and creates Ogrelicious events for them.
  class FrameEventListener : public Ogre::FrameListener
  {
   typedef std::vector<Ogre::uint> VectorT;
   typedef VectorT::iterator       VectorIt;
   friend class EventSystem;
   friend class Ogre::SharedPtr<FrameEventListener>;
   public:
    //! Add a handle to raise events for.
    void addBegin(Ogre::uint handle);
    //! Add a handle to raise events for.
    void addEnd(Ogre::uint handle);
    //! Remove a handle from the current events.
    void remove(Ogre::uint handle);
    //! Sets the return boolean value for frameStarted/frameEnded functions.
    void setNextReturnValue(bool);
    //! Required by Ogre::FrameListener
    bool frameStarted(const Ogre::FrameEvent&);
    //! Required by Ogre::FrameListener
    bool frameEnded(const Ogre::FrameEvent&);
   protected:
    //! Internal constructor.
    FrameEventListener();
    //! Internal destructor.
   ~FrameEventListener();
    //! Current begin handles.
    VectorT mBeginEvents;
    //! Current end handles.
    VectorT mEndEvents;
    //! Next return value.
    bool    mNextReturnValue;
    //! Current timestep.
    Ogre::Real* mCurrentTimestep;
  };
  //! Monitors all events from all known Renderwindows and creates Ogrelicious events for them.
  class RenderWindowEventListener : public Ogre::WindowEventListener
  {
   typedef std::map<Ogre::RenderWindow*, Ogre::uint> MapT;
   typedef MapT::iterator MapIt;
   friend class EventSystem;
   friend class Ogre::SharedPtr<RenderWindowEventListener>;
   public:
    //! Add or set an handle to a renderwindow. All events to that RenderWindow will assume to be that handle calling.
    void set(Ogre::uint handle, Ogre::RenderWindow*);
    //! Remove a handle and renderwindow from the Events list.
    void remove(Ogre::uint handle);
    //! Required by WindowEventListener
    void windowMoved(Ogre::RenderWindow*);
    //! Required by WindowEventListener
    void windowResized(Ogre::RenderWindow*);
    //! Required by WindowEventListener
    void windowClosed(Ogre::RenderWindow*);
    //! Required by WindowEventListener
    void windowFocusChange(Ogre::RenderWindow*);
   protected:
    //! Internal constructor
    RenderWindowEventListener();
    //! Internal destructor
   ~RenderWindowEventListener();
    //! Current bound events.
    MapT mEvents;
  };
  //! Inherited by all functors
  class Functor
  {
  public:
    virtual void fire(void* = 0) = 0;
  };
  //! function with a no arguments and a void return type functor.
  template<class T> class VoidVoidFunctor : public Functor
  {
   public:
    //! VoidVoidFunctor constructor.
    VoidVoidFunctor(T* ptr, void (T::*func)(void)) : mPtr(ptr), mFunc(func) {}
    //! Required fire functor. Argument is ignored.
    void fire(void*) { (mPtr->*mFunc)(); }
    T*                  mPtr;
    void (T::*mFunc)(void);
  };
  //! function with a single Real argument and a void return type functor.
  template<class T> class VoidRealFunctor : public Functor
  {
   public:
    //! VoidRealFunctor constructor.
    VoidRealFunctor(T* ptr, void (T::*func)(const Ogre::Real&)) : mPtr(ptr), mFunc(func) {}
    //! Required fire functor. Argument isn't ignored.
    void fire(void* r)
    {
      Ogre::Real* rr = (Ogre::Real*) r;
      (mPtr->*mFunc)(*rr);
    }
    T*                  mPtr;
    void (T::*mFunc)(const Ogre::Real&);
  };
  //! Function with a KeyEvent* argument and a void return type functor.
  template<class T> class VoidKeyEventFunctor : public Functor
  {
   public:
    //! VoidKeyEvent constructor.
    VoidKeyEventFunctor(T* ptr, void(T::*func)(KeyEvent*)) : mPtr(ptr), mFunc(func) {}
    //! Required fire functor. Argument isn't ignored.
    void fire(void* r)
    {
     KeyEvent* e = (KeyEvent*) r;
     (mPtr->*mFunc)(e);
    }
    T*                  mPtr;
    void (T::*mFunc)(KeyEvent*);
  };
  //! Function with a MouseEvent* argument and a void return type functor.
  template<class T> class VoidMouseEventFunctor : public Functor
  {
   public:
    //! VoidMouseEvent constructor.
    VoidMouseEventFunctor(T* ptr, void(T::*func)(MouseEvent*)) : mPtr(ptr), mFunc(func) {}
    //! Required fire functor. Argument isn't ignored.
    void fire(void* r)
    {
     MouseEvent* e = (MouseEvent*) r;
     (mPtr->*mFunc)(e);
    }
    T*                  mPtr;
    void (T::*mFunc)(MouseEvent*);
  };
  //! Callbacks allow you to call backs.
  class SmartCallback
  {
   public:
    //! SmartCallback constructor for functions that are like  "void T::FunctionName()"
    template<class T>explicit SmartCallback(void (T::*void_T_function_void)(void), T* ptr):mFunctor(new VoidVoidFunctor<T>(ptr,void_T_function_void)){}
    //! Alternative SmartCallback constructor for functions that are like  "void T::FunctionName()"
    template<class T>explicit SmartCallback(T* ptr, void (T::*void_T_function_void)(void)):mFunctor(new VoidVoidFunctor<T>(ptr,void_T_function_void)){}
    //! SmartCallback constructor for functions that are like  "void T::FunctionName(const Real&)"
    template<class T>explicit SmartCallback(void (T::*rf)(const Ogre::Real&), T* ptr):mFunctor(new VoidRealFunctor<T>(ptr,rf)){}
    //! Alternative SmartCallback constructor for functions that are like  "void T::FunctionName(const Real&)"
    template<class T>explicit SmartCallback(T* ptr, void (T::*rf)(const Ogre::Real&)):mFunctor(new VoidRealFunctor<T>(ptr,rf)){}
    //! SmartCallback constructor for functions that are like  "void T::FunctionName(const Real&)"
    template<class T>explicit SmartCallback(void (T::*rf)(KeyEvent*), T* ptr):mFunctor(new VoidKeyEventFunctor<T>(ptr,rf)){}
    //! Alternative SmartCallback constructor for functions that are like  "void T::FunctionName(const Real&)"
    template<class T>explicit SmartCallback(T* ptr, void (T::*rf)(KeyEvent*)):mFunctor(new VoidKeyEventFunctor<T>(ptr,rf)){}
    //! SmartCallback constructor for functions that are like  "void T::FunctionName(const Real&)"
    template<class T>explicit SmartCallback(void (T::*rf)(MouseEvent*), T* ptr):mFunctor(new VoidMouseEventFunctor<T>(ptr,rf)){}
    //! Alternative SmartCallback constructor for functions that are like  "void T::FunctionName(const Real&)"
    template<class T>explicit SmartCallback(T* ptr, void (T::*rf)(MouseEvent*)):mFunctor(new VoidMouseEventFunctor<T>(ptr,rf)){}
    //! SmartCallback constructor for functions that use the Ogrelicious class. Pointers aren't required.
    SmartCallback(void(::Ogrelicious::Core::*_fp)()):mFunctor(new VoidVoidFunctor<::Ogrelicious::Core>(::Ogrelicious::Core::getSingletonPtr(), _fp)){}
    //! Blank SmartCallback constructor.
    SmartCallback() {}
    //! SmartCallback copy constructor.
    SmartCallback(const SmartCallback& other) : mFunctor(other.mFunctor) {}
    //! SmartCallback destructor.
    ~SmartCallback() {}
    //! Assignment operator. 
    SmartCallback& operator=(const SmartCallback& other) { mFunctor = other.mFunctor; }
    //! Local copy of the Functor, managed by a SharedPtr.
    Ogre::SharedPtr<Functor> mFunctor;
  };
  class SmartEvents
  {
   public:
    SmartEvents(unsigned int handle_id);
    void fire(unsigned int channel);
    void push(unsigned int channel, const Ogre::SharedPtr<Functor>& functor);
    unsigned int mHandle;
  };
  template<int ChannelT> class SmartEvent
  {
   public:
    void operator +=(const SmartCallback& callback) { _->push(ChannelT, callback.mFunctor); }
    void operator ()() { _->fire(ChannelT); }
    Ogre::SharedPtr<SmartEvents> _;
  };
  //! Centeralised event system which holds all functors and fires them when needed, managed by OptionalSingleton
  class EventSystem : public OptionalSingleton<EventSystem>
  {
   public:
    typedef std::vector< Ogre::SharedPtr<Functor> > Functors;
    typedef std::map<Ogre::uint, Functors> Channels;
    typedef std::map<Ogre::uint, Channels> Handles;
    friend class OptionalSingleton<EventSystem>;
    //! Add a functor.
    void addFunctor(Ogre::uint handle_id, Ogre::uint channel_id, const Ogre::SharedPtr<Functor>&);
    //! Remove an entire handle thus removing it's channels and functors.
    void removeHandle(Ogre::uint handle_id);
    //! Fire a functors based on the handle and channel it belongs to, with some optional data.
    void fire(Ogre::uint handle_id, Ogre::uint channel_id, void* data = 0);
    //! Fire all functors on a channel regardless of the handle, with some optional data.
    void fire(Ogre::uint channel_id, void* data =0);
    //! Get the FrameEventListener, managed by a SharedPtr
    Ogre::SharedPtr<FrameEventListener>& getFrameEventListener();
    //! Get the RenderWindowEventListener, managed by a SharedPtr
    Ogre::SharedPtr<RenderWindowEventListener>& getRenderWindowEventListener();
    //! SmartEvent for onBeginFrame
    SmartEvent<_onBeginFrame> onBeginFrame;
    //! SmartEvent for onEndFrame
    SmartEvent<_onEndFrame> onEndFrame;
   protected:
    //! Protected constructor. Use EventSystem::Instance()
    EventSystem();
    //! Protected destructor. Use EventSystem::KillInstance()
   ~EventSystem();
    //! Current handles, with Channels, with Functors.
    Handles mHandles;
    //! RenderWindowListener instance, managed by a SharedPtr
    Ogre::SharedPtr<RenderWindowEventListener> mRenderWindowEventListener;
    //! FrameEventListener instance, managed by a SharedPtr
    Ogre::SharedPtr<FrameEventListener>        mFrameEventListener;
    //! SmartEvents for onBeginFrame, onEndFrame event handlers.
    Ogre::SharedPtr<SmartEvents>               mSmartEvents;
  };
  //! Represents an Ogre Plugin with some fun helper functions.
  class SmartPlugin
  {
   public:
    typedef Ogre::Plugin OgreT;
    //! An Ogre plugin contains an Ogre plugin with meta-data about the Plugin.
    struct OgrePlugin
    {
     std::string   mName;
     std::string   mFilename;
     bool          mIsRenderSystem;
     bool          mIsLibrary;
     bool          mIsLoaded;
     Ogre::Plugin* mPlugin;
    };
    //! SmartPlugin constructor, with Plugin pointer as NULL. 
    SmartPlugin();
    //! SmartPlugin constructor, taking the name (trimmed) as the Plugin name.
    SmartPlugin(const std::string& name);
    //! SmartPlugin copy constructor.
    SmartPlugin(const SmartPlugin& other);
    //! SmartPlugin assignment operator.
    SmartPlugin& operator=(SmartPlugin&);
    //! SmartPlugin destructor
   ~SmartPlugin();
    //! -> operator to the actual Ogre Plugin
    OgrePlugin*  operator->();
    //! Load the plugin (if it has not been loaded) and is a library.
    SmartPlugin& load();
    //! Dump the plugin name and meta-data to the console.
    SmartPlugin& describe();
    //! Get the plugins name.
    std::string  name();
    //! Is a rendersystem
    bool isRenderSystem() const {return mPlugin->mIsRenderSystem;}
   protected:
    //! OgrePlugin instance, managed by a SharedPtr.
    Ogre::SharedPtr<OgrePlugin> mPlugin;
    //! OgrePlugin Scouting helper function
    void _scout();
  };
  //! SmartPlugins
  class SmartPlugins : public Many<SmartPlugin>
  {
   public:
    //! SmartPlugins constructor using a string as an commas seperated accessor; "RenderSystem: Direct3D9, RenderSystem_OpenGL.dll, Plugin_ParticleFX.dll"
    SmartPlugins(const std::string&);
    //! SmartPlugins copy constructor.
    SmartPlugins(const SmartPlugins&);
    //! Assignment operator.
    SmartPlugins& operator=(const SmartPlugins&);
    //! SmartPlugins destructor.
   ~SmartPlugins();
    //! Load all plugins based on the SimpleAccessor.
    SmartPlugins& load(SimpleAccessor = _Everything);
    //! Dump all plugins to the console based on the SimpleAccessor.
    SmartPlugins& describe(SimpleAccessor = _Everything);
  };
  //! Represents a single render system.
  class SmartRenderSystem
  {
   public:
    typedef Ogre::RenderSystem OgreT;
    //! An Ogre render system contains an Ogre plugin with meta-data about the RenderSystem.
    struct OgreRenderSystem
    {
      std::string   mName;
      std::string   mFilename;
      bool          mIsLoaded;
      bool          mIsNominated;
      Ogre::RenderSystem* mRenderSystem;
    };
    //! SmartRenderSystem, with no rendersystem
    SmartRenderSystem();
    //! SmartRenderSystem, with a RenderSystemp ptr
    SmartRenderSystem(Ogre::RenderSystem*);
    //! SmartRenderSystem, using the name (trimmed and lower-cased comparision) as a search identifier.
    SmartRenderSystem(const std::string& name);
    //! SmartRenderSystem copy constructor.
    SmartRenderSystem(const SmartRenderSystem& other);
    //! Assignment operator.
    SmartRenderSystem& operator=(SmartRenderSystem&);
    //! SmartRendersystem destructor.
   ~SmartRenderSystem();
    //! -> operator to the actual Ogre::RenderSystem
    Ogre::RenderSystem*  operator->();
    //! Nominate this RenderSystem that OGRE should use.
    SmartRenderSystem& nominate();
    //! Dump the RenderSystem name and meta-data to the console.
    SmartRenderSystem& describe();
    //! Get the name of the RenderSystem.
    std::string  name();
   protected:
    //! OgreRenderSystem instance, managed by a SharedPointer
    Ogre::SharedPtr<OgreRenderSystem> mRenderSystem;
    //! OgreRenderSystem scouting function
    void        _scout();
  }; // class SmartRenderSystem
  //! Represents many RenderSystems via SmartRenderSystem
  class SmartRenderSystems : public Many<SmartRenderSystem>
  {
   public:
    //! SmartRenderSystems constructor, using a comma seperated string to find loaded RenderSystem.
    SmartRenderSystems(const std::string&);
    //! SmartRenderSystems copy constructor.
    SmartRenderSystems(const SmartRenderSystems&);
    //! Assignment operator.
    SmartRenderSystems& operator=(const SmartRenderSystems&);
    //! SmartRenderSystems destructor.
   ~SmartRenderSystems();
    //! Nominate a rendersystem via the SingleAccessor. Multiple rendersystems cannot be nominated.
    SmartRenderSystems& nominate(SingleAccessor = _First);
    //! Dump the RenderSystems names and Meta-Data to the console, using SimpleAccessor.
    SmartRenderSystems& describe(SimpleAccessor = _Everything);
  }; // class SmartRenderSystems
  //! Represents an Ogre "Resource Group"
  class SmartResourceGroup
  {
   public:
    typedef Ogre::String  OgreT;
    //! Ogre doesn't really have a ResourceGroup class. It's basically a string.
    struct OgreResourceGroup
    {
      Ogre::String   mName;
    };
    //! SmartResourceGroup, with no ResourceGroup.
    SmartResourceGroup();
    //! SmartResourceGroup, using name as it's name. Case and Space sensitive.
    SmartResourceGroup(const std::string& name);
    //! SmartResourceGroup copy constructor.
    SmartResourceGroup(const SmartResourceGroup& other);
    //! Assignment operator.
    SmartResourceGroup& operator=(SmartResourceGroup&);
    //! SmartResourceGroup destructor.
   ~SmartResourceGroup();
    //! Add a comma seperated resource string to the Resource Group. i.e. "../media/#?" or "test.zip, /text, /media/#?".
    SmartResourceGroup& operator+=(const std::string& resource_string);
    //! Dump the SmartResourceGroup name and meta-data to the console.
    SmartResourceGroup& describe();
    //! Get the name of the ResourceGroup.
    std::string  name();
    //! Initialise the ResourceGroup.
    SmartResourceGroup& init();
   protected:
    //! OgreResourceGroup instance, managed by a SharedPtr.
    Ogre::SharedPtr<OgreResourceGroup> mResourceGroup;
  };
  // Represents many ResourceGroups via SmartResourceGroup
  class SmartResourceGroups : public Many<SmartResourceGroup>
  {
   public:
    //! SmartResourceGroups constructor, using a comma seperated string to find loaded RenderSystem.
    SmartResourceGroups(const std::string&);
    //! SmartResourceGroups copy constructor.
    SmartResourceGroups(const SmartResourceGroups&);
    //! Assignment operator
    SmartResourceGroups& operator=(const SmartResourceGroups&);
    //! SmartResourceGroups destructor
   ~SmartResourceGroups();
    //! Add a comma seperated resource string to the Resource Group. i.e. "../media/#?" or "test.zip, /text, /media/#?" to all ResourceGroups
    SmartResourceGroups& operator+=(const std::string& resource_string);
    //! Dump the RenderSystems names and Meta-Data to the console, using SimpleAccessor.
    SmartResourceGroups& describe(SimpleAccessor = _Everything);
    //! Initialise ResourceGroups based upon the SimpleAccessor.
    SmartResourceGroups& init(SimpleAccessor = _Everything);
  };
  //! Represents an Ogre Camera
  class SmartCamera
  {
   public:
    typedef Ogre::Camera  OgreT;
    //! An Ogre Camera and it's name.
    struct OgreCamera
    {
      Ogre::String mName;
      OgreT*       mCamera;
    };
    //! SmartCamera, with no Camera or name.
    SmartCamera();
    //! SmartCamera, using an Ogre Camera as it's Camera.
    SmartCamera(Ogre::Camera*);
    //! SmartCamera, using name as it's name. Camera will be created or fetched.
    SmartCamera(const std::string& name, Ogre::SceneManager*);
    //! SmartCamera copy constructor.
    SmartCamera(const SmartCamera& other);
    //! Assignment operator.
    SmartCamera& operator=(SmartCamera&);
    //! SmartCamera destructor.
   ~SmartCamera();
    //! Ogre::Camera -> operator
    OgreT*  operator->() {if (!mCamera.isNull())return mCamera->mCamera;return 0;}
    //! Ogre::Camera * operator
    OgreT*  operator*() {if (!mCamera.isNull())return mCamera->mCamera;return 0;}
    //! Print the Camera name and meta-data to the console
    SmartCamera& describe();
    //! Get the name of the Camera.
    std::string  name();
    //! Set the near clip distance of the Camera.
    SmartCamera& nearClip(const Ogre::Real&);
    //! Get the near clip distance of the Camera.
    Ogre::Real   nearClip() const;
    //! Set the far clip distance of the Camera.
    SmartCamera& farClip(const Ogre::Real&);
    //! Get the far clip distance of the Camera.
    Ogre::Real   farClip() const;
    //! Set the position of the camera, using seperate real components.
    SmartCamera& position(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z);
    //! Set the position of the camera using an Ogre Vector3.
    SmartCamera& position(const Ogre::Vector3&);
    //! Get the position of the camera as an Ogre Vector3.
    Ogre::Vector3 position() const; 
    //! Set the individual X position of the Camera.
    SmartCamera& x(const Ogre::Real& x);
    //! Set the individual Y position of the Camera.
    SmartCamera& y(const Ogre::Real& y);
    //! Set the individual Z position of the Camera.
    SmartCamera& z(const Ogre::Real& z);
    //! Get the individual X position of the Camera.
    Ogre::Real   x() const;
    //! Get the individual X position of the Camera.
    Ogre::Real   y() const;
    //! Get the individual X position of the Camera.
    Ogre::Real   z() const;
    //! Translate the camera in direction.
    SmartCamera& translate(const Ogre::Vector3& direction);
    //! Translate the camera in direction.
    SmartCamera& translate(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z);
    //! Set the direction of the camera so it's pointing at a position, using three seperate Real components.
    SmartCamera& look(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z);
    //! Set the direction of the camera so it's pointing at a position, using an Ogre Vector3.
    SmartCamera& look(const Ogre::Vector3&);
    //! Set the direction of the camera so it's pointing at a position, using another SceneNode's position.
    SmartCamera& look(Ogre::SceneNode*);
    //! Set the direction of the camera, using three seperate Real components.
    SmartCamera& direction(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z);
    //! Set the direction of the camera, using an Ogre Vector3.
    SmartCamera& direction(const Ogre::Vector3&);
    //! Get the direction of the camera, as an Ogre Vector3.
    Ogre::Vector3 direction() const;
  protected:
    //! Local OgreCamera instance, managed by a SharedPtr.
    Ogre::SharedPtr<OgreCamera> mCamera;
  };
  //! Represents many Cameras via SmartCameras.
  class SmartCameras : public Many<SmartCamera>
  {
   public:
    SmartCameras(Ogre::SceneManager*, const std::string&);
    SmartCameras(const SmartCameras&);
    SmartCameras& operator=(const SmartCameras&);
   ~SmartCameras();
    SmartCameras& describe(SimpleAccessor = _Everything);
  };
  //! Represents a single viewport.
  class SmartViewport
  {
   public:
    typedef Ogre::Viewport  OgreT;
    //! 
    struct OgreViewport
    {
      unsigned int        mID;
      OgreT*              mViewport;
      Ogre::Camera*       mCamera;
      Ogre::RenderWindow* mWindow;
    };
    //! Constructor with no viewport
    SmartViewport();
    //! Constructor with a new viewport.
    SmartViewport(Ogre::Camera*, Ogre::RenderWindow*);
    //! Alternate constructor with a new viewport.
    SmartViewport(SmartCamera&, SmartWindow&);
    //! Copy constructor.
    SmartViewport(const SmartViewport& other);
    //! Assignment operator.
    SmartViewport& operator=(SmartViewport&);
    //! SmartViewport destructor.
   ~SmartViewport();
    //! Ogre::Viewport* -> operator.
    OgreT*  operator->() {if (!mViewport.isNull())return mViewport->mViewport;return 0;}
    //! Ogre::Viewport* * operator.
    OgreT*  operator*() {if (!mViewport.isNull())return mViewport->mViewport;return 0;}
    //! The numerical identifier as a string.
    std::string name() const;
    //! Write the name and meta-data to the console.
    SmartViewport& describe();
    //! Set the background colour as an Ogre ColourValue.
    SmartViewport& background(const Ogre::ColourValue&);
    //! Set the background colour as an Colour enum.
    SmartViewport& background(Colour);
    //! Get the background colour as an Ogre ColourValue.
    Ogre::ColourValue background() const;
   protected:
    //! OgreViewport managed by a SharedPtr
    Ogre::SharedPtr<OgreViewport> mViewport;
  };
  //! Represents many Viewports as a SmartViewport
  class SmartViewports : public Many<SmartViewport>
  {
   public:
    //! SmartViewports constructor with no SmartViewports
    SmartViewports();
    //! SmartViewports copy constructor.
    SmartViewports(const SmartViewports&);
    //! Assignment operator.
    SmartViewports& operator=(const SmartViewports&);
    //! SmartViewports destructor
   ~SmartViewports();
    //! Print the viewports' ID and meta-data to the console, depending on the SimpleAccessor.
    SmartViewports& describe(SimpleAccessor = _Everything);
  };
  //! Represents an Ogre Window.
  class SmartWindow
  {
   public:
    typedef Ogre::RenderWindow  OgreT;
    //! Properties of a Window that hasn't been created yet.
    struct WindowDesigner
    {
      Ogre::String  mTitle;
      Ogre::uint    mLeft, mTop, mBorder;
      Ogre::ushort  mWidth, mHeight, mFrequency;
      Ogre::uchar   mDepth, mFSAA;
      bool          mIsFullScreen, mVSync;
      StringMap     mAttributes;
    };
    //! OgreWindow and/or WindowDesigner
    struct OgreWindow
    {
      Ogre::RenderWindow*  mWindow;
      Ogre::String         mName;
      WindowDesigner*      mProps;
    };
    //! SmartWindow with no name, no window and a default WindowDesigner.
    SmartWindow();
    //! SmartWindow with a name; either fetch the window, or create a WindowDesigner.
    SmartWindow(const std::string& name);
    //! SmartWindow copy constructor.
    SmartWindow(const SmartWindow& other);
    //! Assignment operator
    SmartWindow& operator=(SmartWindow&);
    //! SmartWindow destructor.
   ~SmartWindow();
    //! Return all the SmartViewports associated with this Window. Viewports created outside the SmartWindow aren't included.
    SmartViewports& viewports() { return mViewports; }
    //! Ogre::RenderWindow* -> operator
    OgreT*  operator->() {if (!mWindow.isNull())return mWindow->mWindow;return 0;}
    //! Ogre::Window* * operator
    OgreT*  operator*() {if (!mWindow.isNull())return mWindow->mWindow;return 0;}
    //! Write the name and meta-data to the console window. 
    SmartWindow& describe();
    //! Get the name of the WIndow
    std::string  name();
    //! Create the window using the WindowDesigner, otherwise if there is already a Window don't do anything.
    SmartWindow& create(MouseType = _OperatingSystemMouse);
    //! Destroy the window if there is a window, otherwise don't do anything.
    SmartWindow& destroy();
    //! Set the title of the window using OS functions.
    SmartWindow& title(const Ogre::String&);
    //! Get the title of the window using OS functions.
    std::string  title() const;
    //! Set the width and height of the window at once.
    SmartWindow& size(const Ogre::ushort& width, const Ogre::ushort& height);
    //! Set the width of the window.
    SmartWindow& width(const Ogre::ushort&);
    //! Get the width of the window.
    Ogre::ushort width() const;
    //! Set the height of the window.
    SmartWindow& height(const Ogre::ushort&);
    //! Get the height of the window.
    Ogre::ushort height() const;
    //! Set the depth of the window.
    SmartWindow& depth(const Ogre::uchar&);
    //! Get the depth of the window.
    Ogre::uchar  depth();
    //! Change to fullscreen or window.
    SmartWindow& fullscreen(const bool&);
    //! Is fullscreen?
    bool         fullscreen() const;
    //! Set the left and top position of the window at once.
    SmartWindow& position(const Ogre::ushort& left, const Ogre::ushort& top);
    //! Set the left position of the window.
    SmartWindow& left(const Ogre::uint&);
    //! Get the left position of the window.
    Ogre::uint   left() const;
    //! Set the top position of the window.
    SmartWindow& top(const Ogre::uint&);
    //! Get the top position of the window.
    Ogre::uint   top() const;
    //! Set a misc attribute of the window.
    SmartWindow& attribute(const Ogre::String&, const Ogre::String&);
    //! Get a misc attribute of the window.
    Ogre::String attribute(const Ogre::String&) const;
    //! Get all of the attributes as a StringMap Iterator.
    StringMap attributes() const;
    //! Set the FSAA of the window.
    SmartWindow& fsaa(const Ogre::uchar&);
    //! Get the FSAA of the window.
    Ogre::uint   fsaa() const;
    //! Set the frequency of the window.
    SmartWindow& frequency(const Ogre::ushort&);
    //! Get the frequency of the window.
    Ogre::ushort frequency() const;
    //! Set the window has vsync or not.
    SmartWindow& vsync(const bool&);
    //! Is prototype, is the window being designed or is it active?
    bool isPrototype() const;
    //! Get the vsync property of the window.
    bool vsync() const;
#ifdef OGRELICIOUS_LOVES_OIS
    OIS::InputManager* getOISManager();
#endif
    //! Create a viewport using a SmartCamera.
    SmartViewport add(SmartCamera&, unsigned int zOrder = 0, Ogre::Real left = 0, Ogre::Real top = 0, Ogre::Real width = 1, Ogre::Real height = 1); //!< Add a viewport and assign it to this camera.
    //! Alternate to onKeyPressed/onKeyReleased for when a specific key needs to be watched.
    SmartWindow&  watchKey(int keyCode, const _Callback&);
    //! Alternate to onKeyPressed/onKeyReleased for when a specific key needs to be watched.
    SmartWindow&  watchKeys(int keyCodeA, int keyCodeB, const _Callback&);
    //! Alternate to onKeyPressed/onKeyReleased for when a specific key needs to be watched.
    SmartWindow&  watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, const _Callback&);
    //! Alternate to onKeyPressed/onKeyReleased for when a specific key needs to be watched.
    SmartWindow&  watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, int keyCodeD, const _Callback&);
    //! Alternate to onKeyPressed/onKeyReleased for when a specific key needs to be watched.
    SmartWindow&  watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, int keyCodeD, int keyCodeE, const _Callback&);
    //! Alternate to onKeyPressed/onKeyReleased for when a specific key needs to be watched.
    SmartWindow&  watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, int keyCodeD, int keyCodeE, int keyCodeF, const _Callback&);
    //! Alternate to onKeyPressed/onKeyReleased for when a specific key needs to be watched.
    SmartWindow&  watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, int keyCodeD, int keyCodeE, int keyCodeF, int keyCodeG, const _Callback&);
    //! Alternate to onKeyPressed/onKeyReleased for when a specific key needs to be watched.
    SmartWindow&  watchKeys(int keyCodeA, int keyCodeB, int keyCodeC, int keyCodeD, int keyCodeE, int keyCodeF, int keyCodeG, int keyCodeI, const _Callback&);
    //! onLoad window property. Accessible before the window has been created.
    SmartEvent<_onLoad> onLoad;
    //! onUnload window property. Accessible after the window has been created.
    SmartEvent<_onUnload> onUnload;
    //! onDraw window property. Accessible after the window has been created.
    SmartEvent<_onDraw> onDraw;
    //! onMove window property. Accessible after the window has been created.
    SmartEvent<_onMove> onMove;
    //! onResize window property. Accessible after the window has been created.
    SmartEvent<_onResize> onResize;
    //! onFocus window property. Accessible after the window has been created.
    SmartEvent<_onFocus> onFocus;
    //! onKeyPressed window property. Accessible after the window has been created.
    SmartEvent<_onKeyPressed> onKeyPressed;
    //! onKeyReleased window property. Accessible after the window has been created.
    SmartEvent<_onKeyReleased> onKeyReleased;
    //! onMouseMoved window property. Accessible after the window has been created.
    SmartEvent<_onMouseMoved> onMouseMoved;
    //! onMouseButtonPressed window property. Accessible after the window has been created.
    SmartEvent<_onMouseButtonPressed> onMouseButtonPressed;
    //! onMouseButtonReleased window property. Accessible after the window has been created.
    SmartEvent<_onMouseButtonReleased> onMouseButtonReleased;
    //! Get mouse pointer or a null SharedPtr
    Ogre::SharedPtr<SmartMousePointer> getMousePointer();
   protected:
    //! Internal events binding function
    void _events(bool exclusiveMouse = false);
    //! Internal create WindowDesigner function.
    void _createProps();
    //! Local copy of the OgreWindow instance, managed by a SharedPtr
    Ogre::SharedPtr<OgreWindow>  mWindow;
    //! Local copy of the SmartsEvent instance, managed by a SharedPtr
    Ogre::SharedPtr<SmartEvents> mEvents;
    //
    unsigned int mKeyboardToken;
    //! SmartViewports instance.
    SmartViewports mViewports;
    //! MousePointer
    Ogre::SharedPtr<SmartMousePointer> mMousePointer;
  };
  //! Many Windows represented by a SmartWindow
  class SmartWindows : public Many<SmartWindow>
  {
   public:
    //! SmartWindows using a comma seperated accessor.
    SmartWindows(const std::string&);
    //! SmartWindows copy constructor.
    SmartWindows(const SmartWindows&);
    //! Assignment operator.
    SmartWindows& operator=(const SmartWindows&);
    //! SmartWindows destructor.
   ~SmartWindows();
    //! Describe a SmartWindow's name and meta-data, using a SimpleAccessor as a filter.
    SmartWindows& describe(SimpleAccessor = _Everything);
    //! Set the title of the window using OS functions.
    SmartWindows& title(const Ogre::String&, SimpleAccessor = _Everything);
    //! Set the width of the window.
    SmartWindows& width(const Ogre::ushort&, SimpleAccessor = _Everything);
    //! Set the height of the window.
    SmartWindows& height(const Ogre::ushort&, SimpleAccessor = _Everything);
    //! Set the depth of the window.
    SmartWindows& depth(const Ogre::uchar&, SimpleAccessor = _Everything);
    //! Change to fullscreen or window.
    SmartWindows& fullscreen(const bool&, SimpleAccessor = _Everything);
    //! Set the left position of the window.
    SmartWindows& left(const Ogre::uint&, SimpleAccessor = _Everything);
    //! Set the top position of the window.
    SmartWindows& top(const Ogre::uint&, SimpleAccessor = _Everything);
    //! Set a misc attribute of the window.
    SmartWindows& attribute(const Ogre::String&, const Ogre::String&, SimpleAccessor = _Everything);
    //! Set the FSAA of the window.
    SmartWindows& fsaa(const Ogre::uchar&, SimpleAccessor = _Everything);
    //! Set the frequency of the window.
    SmartWindows& frequency(const Ogre::ushort&, SimpleAccessor = _Everything);
    //! Set the window has vsync or not.
    SmartWindows& vsync(const bool&, SimpleAccessor = _Everything);
  };
  //! Represents an Ogre SceneNode
  class SmartNode
  {
   public:
    typedef Ogre::SceneNode  OgreT;
    //! An Ogre Camera and it's name.
    struct OgreSceneNode
    {
      OgreT*       mNode;
      Ogre::SceneManager* mSceneMgr;
    };
    //! SmartNode, with no Node or name.
    SmartNode();
    //! SmartNode, using an Ogre SceneNode.
    SmartNode(Ogre::SceneNode*);
    //! SmartNode, using name as it's name. SceneNode will be created or fetched.
    SmartNode(const std::string& name, Ogre::SceneManager*);
    //! SmartNode, using an unsigned integer (converted to a string) as it's name. SceneNode will be created or fetched.
    SmartNode(unsigned int, Ogre::SceneManager*);
    //! SmartNode copy constructor.
    SmartNode(const SmartNode& other);
    //! Assignment operator.
    SmartNode& operator=(SmartNode&);
    //! SmartNode destructor.
   ~SmartNode();
    //! Fetch or Create a SmartNode, and add it as a child to this one, using an integer(converted to a string) as a name.
    SmartNode add(const Ogre::String&);
    //! Fetch or Create a SmartNode, and add it as a child to this one, using an integer(converted to a string) as a name.
    SmartNode add(unsigned int);
    //! Ogre::Node -> operator
    OgreT*  operator->() {if (!mNode.isNull())return mNode->mNode;return 0;}
    //! Ogre::Node * operator
    OgreT*  operator*() {if (!mNode.isNull())return mNode->mNode;return 0;}
    //! Print the Node name and meta-data to the console
    SmartNode& describe();
    //! Get the name of the Node.
    std::string name();
    //! All children nodes as SmartNodes.
    SmartNodes nodes();
    //! An attached object, assumed to be an entity
    Ogre::Entity* entity(SingleAccessor);
    //! Create an entity, using name as a entity-name (leave blank for autogen)
    Ogre::Entity* entity(const Ogre::String& meshName, const Ogre::String& entityName = Ogre::StringUtil::BLANK);
    //! Add entity.
    SmartNode& operator +=(Ogre::Entity*);
    //! Add entity or mesh(created as entity). Meshes must end in ".mesh" otherwise it is treated as an entity
    SmartNode& operator +=(const Ogre::String&);
    //! Add mesh, converted into an entity. Using the Node's name as a prefix.
    SmartNode& operator +=(const Ogre::MeshPtr&);
    //! Add scenenode, and removing itself from it's parent.
    SmartNode& operator +=(Ogre::SceneNode*);
    //! Add scenenode via SmartNode, and removing itself from it's parent.
    SmartNode& operator +=(SmartNode&);
    //! Remove an entity from the node.
    SmartNode& operator -=(Ogre::Entity*);
    //! Set the position of the Node, using seperate real components.
    SmartNode& position(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z);
    //! Set the position of the Node using an Ogre Vector3.
    SmartNode& position(const Ogre::Vector3&);
    //! Get the position of the Node as an Ogre Vector3.
    Ogre::Vector3 position() const; 
    //! Set the individual X position of the Node.
    SmartNode& x(const Ogre::Real& x);
    //! Set the individual Y position of the Node.
    SmartNode& y(const Ogre::Real& y);
    //! Set the individual Z position of the Node.
    SmartNode& z(const Ogre::Real& z);
    //! Get the individual X position of the Node.
    Ogre::Real x() const;
    //! Get the individual X position of the Node.
    Ogre::Real y() const;
    //! Get the individual X position of the Node.
    Ogre::Real z() const;
    //! Set the direction of the Node, using an Ogre Vector3.
    SmartNode& orientation(const Ogre::Quaternion&);
    //! Get the direction of the Node, as an Ogre Vector3.
    Ogre::Quaternion orientation() const;
    //! Set the scale of the node, using three real components.
    SmartNode& scale(const Ogre::Real& x, const Ogre::Real& y, const Ogre::Real& z);
    //! Set the scale of the node using an Ogre Vector3
    SmartNode& scale(const Ogre::Vector3&);
    //! Get the scale of the node using an Ogre Vector3
    Ogre::Vector3 scale() const;
  protected:
    //! Local OgreNode instance, managed by a SharedPtr.
    Ogre::SharedPtr<OgreSceneNode> mNode;
  };
  //! Represents many Nodes via SmartNodes.
  class SmartNodes : public Many<SmartNode>
  {
   public:
    SmartNodes();
    SmartNodes(Ogre::SceneManager*, const std::string&);
    SmartNodes(const SmartNodes&);
    SmartNodes& operator=(const SmartNodes&);
   ~SmartNodes();
    SmartNodes& describe(SimpleAccessor = _Everything);
  };
  //! Represents an Ogre Material
  class SmartMaterial
  {
   public:
    //! SmartMaterial, with no Material or name.
    SmartMaterial();
    //! SmartMaterial, using an Ogre Material.
    SmartMaterial(const Ogre::MaterialPtr&);
    //! SmartMaterial, using name as it's name. Material will be created or fetched.
    SmartMaterial(const Ogre::String& name, const Ogre::String& group = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    //! SmartMaterial, using an unsigned integer (converted to a string) as it's name. Material will be created or fetched.
    SmartMaterial(unsigned int, const Ogre::String& group = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    //! SmartMaterial copy constructor.
    SmartMaterial(const SmartMaterial& other);
    //! Assignment operator.
    SmartMaterial& operator=(SmartMaterial&);
    //! SmartMaterial destructor.
   ~SmartMaterial();
    //! Write material name and meta-data to the console.
    SmartMaterial& describe();
    //! Get the name of the material.
    std::string name() const;
    //! Ogre::Material -> operator
    Ogre::Material*  operator->() {if (!mMaterial.isNull())return mMaterial.get();return 0;}
    //! Ogre::Material * operator
    Ogre::Material*  operator*() {if (!mMaterial.isNull())return mMaterial.get();return 0;}
    //! Set ambient colour to all passes in all techniques.
    SmartMaterial& ambient(const Ogre::ColourValue&);
    //! Set ambient colour to all passes in all techniques.
    SmartMaterial& ambient(const Colour&, Ogre::Real alpha = 1.0);
    //! Set diffuse colour to all passes in all techniques.
    SmartMaterial& diffuse(const Ogre::ColourValue&);
    //! Set diffuse colour to all passes in all techinques.
    SmartMaterial& diffuse(const Colour&, Ogre::Real alpha = 1.0);
    //! Set specular colour to all passes in all techniques.
    SmartMaterial& specular(const Ogre::ColourValue&);
    //! Set specular colour to all passes in all techinques.
    SmartMaterial& specular(const Colour&, Ogre::Real alpha = 1.0);
   protected:
    Ogre::MaterialPtr mMaterial;
  };
  //! Auto-Config. Loads and configures Ogre from a string or file.
  class SmartConfig
  {
   public:
    typedef StringMap Section;
    typedef std::map<Ogre::String, Section> Sections;
    typedef Section::iterator SectionIt;
    typedef Sections::iterator SectionsIt;
    struct Config
    {
     Sections mSections;
     Ogre::String mComment;
    };
    //! SmartConfig.
    SmartConfig();
    //! Parse a from configuation string or file. File is determined by the string ending in ".cfg"
    SmartConfig(const std::string& configuration_string);
    //! Create and fill SmartPlugins from the configuration.
    SmartPlugins toSmartPlugins(const Ogre::String& section_name = "Plugins");
    //! Create and design a Window from the configuration.
    SmartWindow toSmartWindow(const Ogre::String& window_name, const Ogre::String& section_name = "Window", const Ogre::String& attributes_section = "Window|Attributes");
    //! Serialise the SmartPlugins.
    SmartConfig& from(SmartPlugin&, const Ogre::String& = "Plugin");
    //! Serialise the names from a SmartPlugins.
    SmartConfig& from(SmartPlugins&, const Ogre::String& = "Plugins");
    //! Serialise the name and meta-data of a Window.
    SmartConfig& from(SmartWindow&, const Ogre::String& = "Window");
    //! Load from a file.
    SmartConfig& load(const Ogre::String& file_name);
    //! Save to a file.
    SmartConfig& save(const Ogre::String& file_name);
    //! Add/Set a value.
    SmartConfig& set(const Ogre::String& section, const Ogre::String& key, const Ogre::String& value);
    //! Set comment. Multiple lines are supported.
    SmartConfig& comment(const Ogre::String&);
    //! Get the comment.
    Ogre::String comment() const;
    //! Scribe the sections and comments to the console
    SmartConfig& scribe();
    //! Get a float from the configuration, otherwise return default_value.
    bool getAsBool(const Ogre::String& section, const Ogre::String& key, bool default_value = false) const;
    //! Get a string from a possible section and key, otherwise isNull in PossibleString is true.
    PossibleString get(const Ogre::String& section, const Ogre::String& key) const;
    //! Get a float from the configuration, otherwise return default_value.
    Ogre::String getAsString(const Ogre::String& section, const Ogre::String& key, Ogre::String default_value = Ogre::String()) const;
    //! Get a float from the configuration, otherwise return default_value.
    float getAsFloat(const Ogre::String& section, const Ogre::String& key, float default_value = 0.0f) const;
   protected:
    //! Lowercases a string and uppercases the first character
    void fixString(Ogre::String&);
    //! Config, managed by a SharedPtr.
    Ogre::SharedPtr<Config> mConfig;
  };
  //! Represents an Ogre Font
  class SmartFont
  {
   public:
    //! SmartFont, with no Font or name.
    SmartFont();
    //! SmartFont, using an Ogre Font.
    SmartFont(const Ogre::FontPtr&);
    //! SmartFont, using name as it's name. Font will be created or fetched.
    SmartFont(const Ogre::String& name, const Ogre::String& group = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    //! SmartFont copy constructor.
    SmartFont(const SmartFont& other);
    //! Assignment operator.
    SmartFont& operator=(SmartFont&);
    //! SmartFont destructor.
   ~SmartFont();
    //! Write material name and meta-data to the console.
    SmartFont& describe();
    //! Get the name of the material.
    std::string name() const;
    //! Ogre::Font -> operator
    Ogre::Font*  operator->() {if (!mFont.isNull())return mFont.get();return 0;}
    //! Ogre::Font * operator
    Ogre::Font*  operator*() {if (!mFont.isNull())return mFont.get();return 0;}
    //! Set source of the font to work with.
    SmartFont& source(const Ogre::String&);
    //! Set the type of font.
    SmartFont& type(Ogre::FontType);
    //! Set size of the TTF font.
    SmartFont& size(Ogre::Real);
    //! Set resolution of the TTF font.
    SmartFont& resolution(Ogre::uint);
    //! Add a codePoint range to the TTF font.
    SmartFont& pointRange(Ogre::uint lower, Ogre::uint higher);
   protected:
    Ogre::FontPtr mFont;
  };
  //! Represents an OverlayContainer.
  class SmartOverlay
  {
   public:
    struct OgreOverlay
    {
      void __create(const std::string& name, const std::string& caption, const std::string& font, unsigned int zOrder);
      Ogre::OverlayContainer*       mOverlayContainer;
      Ogre::TextAreaOverlayElement* mOverlayText;
      Ogre::Overlay*                mOverlay;
    };
    //! SmartOverlay, with no caption.
    SmartOverlay();
    //! SmartOverlay, with a caption. Ogre::Overlay will be fetched or created based on zOrder.
    SmartOverlay(const Ogre::String& caption, unsigned int zOrder = 100);
    //! SmartOverlay, with a caption, name and fontName Ogre::Overlay will be fetched or created based on zOrder.
    SmartOverlay(const Ogre::String& caption, const Ogre::String& name, const Ogre::String& font, unsigned int zOrder = 100);
    //! SmartOverlay copy constructor.
    SmartOverlay(const SmartOverlay& other);
    //! Assignment operator.
    SmartOverlay& operator=(SmartOverlay&);
    //! SmartOverlay destructor.
   ~SmartOverlay();
    //! Write material name and meta-data to the console.
    SmartOverlay& describe();
    //! Get the name of the material.
    std::string name() const;
    //! Ogre::Overlay -> operator
    Ogre::OverlayContainer* operator->() {if (!mOverlay.isNull())return mOverlay.get()->mOverlayContainer;return 0;}
    //! Ogre::Overlay * operator
    Ogre::OverlayContainer* operator*() {if (!mOverlay.isNull())return mOverlay.get()->mOverlayContainer;return 0;}
    //! Set Caption of the Overlay to work with.
    SmartOverlay& caption(const Ogre::String&);
    //! Set the type of Overlay.
    Ogre::String caption() const;
    //! Set position of the Overlay in relative coordinates OR pixels (if the vector magnitude is over 1)
    SmartOverlay& position(const Ogre::Vector2&);
    //! Get the position of Overlay.
    Ogre::Vector2 position() const;
    //! Set position of the Overlay in relative coordinates OR pixels (if the vector magnitude is over 1)
    SmartOverlay& size(const Ogre::Vector2&);
    //! Get the position of Overlay.
    Ogre::Vector2 size() const;
    //! Set left of the Overlay in relative coordinates
    SmartOverlay& left(const Ogre::Real&);
    //! Get the left position of Overlay in relative coordinates
    Ogre::Real left() const;
    //! Set top of the Overlay in relative coordinates
    SmartOverlay& top(const Ogre::Real&);
    //! Get the top position of Overlay in relative coordinates
    Ogre::Real top() const;
    //! Set the colour of the text.
    SmartOverlay& colour(::Ogrelicious::Colour);
    //! Set the colour of the text.
    SmartOverlay& colour(const Ogre::ColourValue&);
  protected:
    
    Ogre::SharedPtr<OgreOverlay> mOverlay;
  };
} // Ogrelicious namespace

//////////////////////////////////////////////////////////////////////////////
// End of Ogrelicious.h
//////////////////////////////////////////////////////////////////////////////
#endif
