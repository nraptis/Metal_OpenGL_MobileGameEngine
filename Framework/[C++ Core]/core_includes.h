

#ifndef CORE_INC_H
#define CORE_INC_H

#define ENV_WIN32 1
#define ENV_MAC 2
#define ENV_IOS 3
#define ENV_ANDROID 4

#define GL_SILENCE_DEPRECATION 1

#ifndef _max
#define _max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef _min
#define _min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef _abs
#define _abs(x) ((x) > 0) ? (x) : -(x)
#endif

#define LANDSCAPE_MODE 1
//#undef LANDSCAPE_MODE

//#include "os_core_includes.h"
//#include "app_global.h"

#include "os_core_includes.h"
#include "os_core_outlets.h"
#include "os_core_sound.h"
#include "os_core_music.h"

#include "os_core_graphics.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <unordered_set>
#include <unordered_map>
#include <set>


#ifndef WIN_32_ENV
#include <strings.h>
#endif

#include <stdint.h>
#include <math.h>
#include <unistd.h>

#include "FTouchManager.hpp"
#include "FRandomizer.hpp"
#include "FImage.hpp"
#include "FRect.hpp"
#include "FSprite.hpp"
#include "FSpriteSequence.h"
#include "FString.hpp"
#include "FVec2.hpp"
#include "FVec3.hpp"
#include "FVec2.hpp"
#include "FCanvas.hpp"
#include "FWindow.hpp"
#include "FTexture.hpp"
#include "FTextureCache.hpp"
#include "FBufferCache.hpp"

#include "FButton.hpp"
#include "FMatrix.hpp"
#include "FMath.hpp"
#include "FColor.hpp"
#include "FList.hpp"
#include "FFile.hpp"
#include "FObject.hpp"
#include "FUniforms.hpp"
#include "FSound.hpp"
#include "FResource.hpp"
#include "FHashMap.hpp"
#include "FNotificationCenter.hpp"

extern float gAppWidth;
extern float gAppHeight;

extern float gAppWidth2;
extern float gAppHeight2;

extern float gVirtualDevX;
extern float gVirtualDevY;
extern float gVirtualDevWidth;
extern float gVirtualDevHeight;

extern float gDeviceWidth;
extern float gDeviceHeight;
extern float gDeviceWidth2;
extern float gDeviceHeight2;

extern float gSafeAreaInsetTop;
extern float gSafeAreaInsetRight;
extern float gSafeAreaInsetBottom;
extern float gSafeAreaInsetLeft;

extern bool gAdBannerVisible;

extern bool gSoundEnabled;
extern float gSoundVolume;

extern bool gMusicEnabled;
extern float gMusicVolume;

extern float gOSVersion;

extern int gEnvironment;

extern int gImageResolutionScale;
extern float gSpriteDrawScale;

extern FString gDirDocuments;
extern FString gDirBundle;
extern FString gDirExport;

extern FRandomizer gRand;

extern FTouchManager gTouch;
extern FTextureCache gTextureCache;
extern FBufferCache gBufferCache;

extern FNotificationCenter gNotify;

static FList sSoundList;
static FList sSoundInstanceList;
static FList sSpriteList;

#define SQRT_EPSILON 0.005f
#define FLOAT_EPSILON 0.0001f

#define DEGREES_TO_RADIANS(value) ((value) * 0.01745329251994329576923690768488)
#define RADIANS_TO_DEGREES(value) ((value) * 57.2957795130823208767981548141052)

#define __KEY__ESCAPE          0x01
#define __KEY__1               0x02
#define __KEY__2               0x03
#define __KEY__3               0x04
#define __KEY__4               0x05
#define __KEY__5               0x06
#define __KEY__6               0x07
#define __KEY__7               0x08
#define __KEY__8               0x09
#define __KEY__9               0x0A
#define __KEY__0               0x0B

#define __KEY__MINUS           0x0C    /* - on main keyboard */
#define __KEY__EQUALS          0x0D
#define __KEY__BACK            0x0E    /* backspace */
#define __KEY__TAB             0x0F
#define __KEY__Q               0x10
#define __KEY__W               0x11
#define __KEY__E               0x12
#define __KEY__R               0x13
#define __KEY__T               0x14
#define __KEY__Y               0x15
#define __KEY__U               0x16
#define __KEY__I               0x17
#define __KEY__O               0x18
#define __KEY__P               0x19
#define __KEY__LBRACKET        0x1A
#define __KEY__RBRACKET        0x1B
#define __KEY__RETURN          0x1C    /* Enter on main keyboard */
#define __KEY__ENTER			0x1C    /* Enter on main keyboard */

#define __KEY__LCONTROL        0x1D
#define __KEY__A               0x1E
#define __KEY__S               0x1F
#define __KEY__D               0x20
#define __KEY__F               0x21
#define __KEY__G               0x22
#define __KEY__H               0x23
#define __KEY__J               0x24
#define __KEY__K               0x25
#define __KEY__L               0x26
#define __KEY__SEMICOLON       0x27
#define __KEY__APOSTROPHE      0x28
#define __KEY__GRAVE           0x29    /* accent grave */
#define __KEY__LSHIFT          0x2A
#define __KEY__BACKSLASH       0x2B
#define __KEY__Z               0x2C
#define __KEY__X               0x2D
#define __KEY__C               0x2E
#define __KEY__V               0x2F
#define __KEY__B               0x30
#define __KEY__N               0x31
#define __KEY__M               0x32
#define __KEY__COMMA           0x33
#define __KEY__PERIOD          0x34    /* . on main keyboard */
#define __KEY__SLASH           0x35    /* / on main keyboard */
#define __KEY__RSHIFT          0x36
#define __KEY__MULTIPLY        0x37    /* * on numeric keypad */
#define __KEY__LMENU           0x38    /* left Alt */
#define __KEY__SPACE           0x39
#define __KEY__CAPITAL         0x3A
#define __KEY__F1              0x3B
#define __KEY__F2              0x3C
#define __KEY__F3              0x3D
#define __KEY__F4              0x3E
#define __KEY__F5              0x3F
#define __KEY__F6              0x40
#define __KEY__F7              0x41
#define __KEY__F8              0x42
#define __KEY__F9              0x43
#define __KEY__F10             0x44
#define __KEY__NUMLOCK         0x45
#define __KEY__SCROLL          0x46    /* Scroll Lock */
#define __KEY__NUMPAD7         0x47
#define __KEY__NUMPAD8         0x48
#define __KEY__NUMPAD9         0x49
#define __KEY__SUBTRACT        0x4A    /* - on numeric keypad */
#define __KEY__NUMPAD4         0x4B
#define __KEY__NUMPAD5         0x4C
#define __KEY__NUMPAD6         0x4D
#define __KEY__ADD             0x4E    /* + on numeric keypad */
#define __KEY__NUMPAD1         0x4F
#define __KEY__NUMPAD2         0x50
#define __KEY__NUMPAD3         0x51
#define __KEY__NUMPAD0         0x52
#define __KEY__DECIMAL         0x53    /* . on numeric keypad */
#define __KEY__OEM_102         0x56    /* < > | on UK/Germany keyboards */
#define __KEY__F11             0x57
#define __KEY__F12             0x58


#define __KEY__KANA            0x70    /* (Japanese keyboard)            */
#define __KEY__ABNT_C1         0x73    /* / ? on Portugese (Brazilian) keyboards */
#define __KEY__CONVERT         0x79    /* (Japanese keyboard)            */
#define __KEY__NOCONVERT       0x7B    /* (Japanese keyboard)            */
#define __KEY__YEN             0x7D    /* (Japanese keyboard)            */
#define __KEY__ABNT_C2         0x7E    /* Numpad . on Portugese (Brazilian) keyboards */
#define __KEY__NUMPADEQUALS    0x8D    /* = on numeric keypad (NEC PC98) */
#define __KEY__PREVTRACK       0x90    /* Previous Track (__KEY__CIRCUMFLEX on Japanese keyboard) */
#define __KEY__AT              0x91    /*                     (NEC PC98) */
#define __KEY__COLON           0x92    /*                     (NEC PC98) */
#define __KEY__UNDERLINE       0x93    /*                     (NEC PC98) */
#define __KEY__KANJI           0x94    /* (Japanese keyboard)            */
#define __KEY__STOP            0x95    /*                     (NEC PC98) */
#define __KEY__AX              0x96    /*                     (Japan AX) */
#define __KEY__UNLABELED       0x97    /*                        (J3100) */
#define __KEY__NEXTTRACK       0x99    /* Next Track */
#define __KEY__NUMPADENTER     0x9C    /* Enter on numeric keypad */
#define __KEY__RCONTROL        0x9D
#define __KEY__MUTE            0xA0    /* Mute */
#define __KEY__CALCULATOR      0xA1    /* Calculator */
#define __KEY__PLAYPAUSE       0xA2    /* Play / Pause */
#define __KEY__MEDIASTOP       0xA4    /* Media Stop */
#define __KEY__VOLUMEDOWN      0xAE    /* Volume - */
#define __KEY__VOLUMEUP        0xB0    /* Volume + */
#define __KEY__WEBHOME         0xB2    /* Web home */
#define __KEY__NUMPADCOMMA     0xB3    /* , on numeric keypad (NEC PC98) */
#define __KEY__DIVIDE          0xB5    /* / on numeric keypad */
#define __KEY__SYSRQ           0xB7
#define __KEY__RMENU           0xB8    /* right Alt */
#define __KEY__PAUSE           0xC5    /* Pause */
#define __KEY__HOME            0xC7    /* Home on arrow keypad */
#define __KEY__UP              0xC8    /* UpArrow on arrow keypad */
#define __KEY__PRIOR           0xC9    /* PgUp on arrow keypad */
#define __KEY__LEFT            0xCB    /* LeftArrow on arrow keypad */
#define __KEY__RIGHT           0xCD    /* RightArrow on arrow keypad */
#define __KEY__END             0xCF    /* End on arrow keypad */
#define __KEY__DOWN            0xD0    /* DownArrow on arrow keypad */
#define __KEY__NEXT            0xD1    /* PgDn on arrow keypad */
#define __KEY__INSERT          0xD2    /* Insert on arrow keypad */
#define __KEY__DELETE          0xD3    /* Delete on arrow keypad */
#define __KEY__LWIN            0xDB    /* Left Windows key */
#define __KEY__RWIN            0xDC    /* Right Windows key */
#define __KEY__APPS            0xDD    /* AppMenu key */
#define __KEY__POWER           0xDE    /* System Power */
#define __KEY__SLEEP           0xDF    /* System Sleep */
#define __KEY__WAKE            0xE3    /* System Wake */
#define __KEY__WEBSEARCH       0xE5    /* Web Search */
#define __KEY__WEBFAVORITES    0xE6    /* Web Favorites */
#define __KEY__WEBREFRESH      0xE7    /* Web Refresh */
#define __KEY__WEBSTOP         0xE8    /* Web Stop */
#define __KEY__WEBFORWARD      0xE9    /* Web Forward */
#define __KEY__WEBBACK         0xEA    /* Web Back */
#define __KEY__MYCOMPUTER      0xEB    /* My Computer */
#define __KEY__MAIL            0xEC    /* Mail */
#define __KEY__MEDIASELECT     0xED    /* Media Select */

/*
*  Alternate names for keys, to facilitate transition from DOS.
*/
#define __KEY__BACKSPACE       __KEY__BACK            /* backspace */
#define __KEY__NUMPADSTAR      __KEY__MULTIPLY        /* * on numeric keypad */
#define __KEY__LALT            __KEY__LMENU           /* left Alt */
#define __KEY__CAPSLOCK        __KEY__CAPITAL         /* CapsLock */
#define __KEY__NUMPADMINUS     __KEY__SUBTRACT        /* - on numeric keypad */
#define __KEY__NUMPADPLUS      __KEY__ADD             /* + on numeric keypad */
#define __KEY__NUMPADPERIOD    __KEY__DECIMAL         /* . on numeric keypad */
#define __KEY__NUMPADSLASH     __KEY__DIVIDE          /* / on numeric keypad */
#define __KEY__RALT            __KEY__RMENU           /* right Alt */
#define __KEY__UPARROW         __KEY__UP              /* UpArrow on arrow keypad */
#define __KEY__PGUP            __KEY__PRIOR           /* PgUp on arrow keypad */
#define __KEY__LEFTARROW       __KEY__LEFT            /* LeftArrow on arrow keypad */
#define __KEY__RIGHTARROW      __KEY__RIGHT           /* RightArrow on arrow keypad */
#define __KEY__DOWNARROW       __KEY__DOWN            /* DownArrow on arrow keypad */
#define __KEY__PGDN            __KEY__NEXT            /* PgDn on arrow keypad */

/*
enum FKeys
{
	mKey0 = __KEY__0,
	m1 = __KEY__1,
	m2 = __KEY__2,
	m3 = __KEY__3,
	m4 = __KEY__4,
	m5 = __KEY__5,
	m6 = __KEY__6,
	m7 = __KEY__7,
	m8 = __KEY__8,
	m9 = __KEY__9,

	mA = __KEY__A,
	mB = __KEY__B,
	mC = __KEY__C,
	mD = __KEY__D,
	mE = __KEY__E,
	mF = __KEY__F,
	mG = __KEY__G,
	mH = __KEY__H,
	mI = __KEY__I,
	mJ = __KEY__J,
	mK = __KEY__K,
	mL = __KEY__L,
	mM = __KEY__M,
	mN = __KEY__N,
	mO = __KEY__O,
	mP = __KEY__P,
	mQ = __KEY__Q,
	mR = __KEY__R,
	mS = __KEY__S,
	mT = __KEY__T,
	mU = __KEY__U,
	mV = __KEY__V,
	mW = __KEY__W,
	mX = __KEY__X,
	mY = __KEY__Y,
	mZ = __KEY__Z,
	mLeftShift = __KEY__LSHIFT,
	mLShift = __KEY__LSHIFT,
	mRightShift = __KEY__RSHIFT,
	mRShift = __KEY__RSHIFT,
	mLeftControl = __KEY__LCONTROL,
	mRightControl = __KEY__RCONTROL,
	mLeftCTRL = __KEY__LCONTROL,
	mRightCTRL = __KEY__RCONTROL,
	mLControl = __KEY__LCONTROL,
	mRControl = __KEY__RCONTROL,
	mLCTRL = __KEY__LCONTROL,
	mRCTRL = __KEY__RCONTROL,
	mApostrophe = __KEY__APOSTROPHE,
	mApplication = __KEY__APPS,
	mBack = __KEY__BACK,
	mBackspace = __KEY__BACKSPACE,
	mBackSpace = __KEY__BACKSPACE,
	mBackSlash = __KEY__BACKSLASH,
	mBackslash = __KEY__BACKSLASH,
	mCalculator = __KEY__CALCULATOR,
	mCapsLock = __KEY__CAPITAL,
	mCapital = __KEY__CAPITAL,
	mComma = __KEY__COMMA,
	mDelete = __KEY__DELETE,
	mSlash_Keypad = __KEY__DIVIDE,
	mDivide_Keypad = __KEY__DIVIDE,
	mDown = __KEY__DOWN,
	mDownArrow = __KEY__DOWN,
	mUp = __KEY__UP,
	mUpArrow = __KEY__UP,
	mLeft = __KEY__LEFT,
	mLeftArrow = __KEY__LEFT,
	mRight = __KEY__RIGHT,
	mRightArrow = __KEY__RIGHT,
	mEnd = __KEY__END,
	mEquals = __KEY__EQUALS,
	mPlus = __KEY__EQUALS,
	mEqualSign = __KEY__EQUALS,
	mEsc = __KEY__ESCAPE,
	mEscape = __KEY__ESCAPE,
	mF1 = __KEY__F1,
	mF2 = __KEY__F2,
	mF3 = __KEY__F3,
	mF4 = __KEY__F4,
	mF5 = __KEY__F5,
	mF6 = __KEY__F6,
	mF7 = __KEY__F7,
	mF8 = __KEY__F8,
	mF9 = __KEY__F9,
	mF10 = __KEY__F10,
	mF11 = __KEY__F11,
	mF12 = __KEY__F12,
	mTilde = __KEY__GRAVE,
	mHome = __KEY__HOME,
	mInsert = __KEY__INSERT,
	mLeftAlt = __KEY__LALT,
	mLAlt = __KEY__LALT,
	mRightAlt = __KEY__RALT,
	mRAlt = __KEY__RALT,
	mLeftBracket = __KEY__LBRACKET,
	mLBracket = __KEY__LBRACKET,
	mRightBracket = __KEY__RBRACKET,
	mRBracket = __KEY__RBRACKET,
	mLeftWindows = __KEY__LWIN,
	mLWindows = __KEY__LWIN,
	mRightWindows = __KEY__RWIN,
	mRWindows = __KEY__RWIN,
	mMail = __KEY__MAIL,
	mMediaSelect = __KEY__MEDIASELECT,
	mMediaStop = __KEY__MEDIASTOP,
	mMinus = __KEY__MINUS,
	mUnderscore = __KEY__MINUS,
	mMultiply_Keypad = __KEY__MULTIPLY,
	mStar_Keypad = __KEY__MULTIPLY,
	mStar = __KEY__MULTIPLY,
	mAsterisk = __KEY__MULTIPLY,
	mMute = __KEY__MUTE,
	mMyComputer = __KEY__MYCOMPUTER,
	mNext = __KEY__NEXTTRACK,
	mNumLock = __KEY__NUMLOCK,
	m1_Keypad = __KEY__NUMPAD1,
	m2_Keypad = __KEY__NUMPAD2,
	m3_Keypad = __KEY__NUMPAD3,
	m4_Keypad = __KEY__NUMPAD4,
	m5_Keypad = __KEY__NUMPAD5,
	m6_Keypad = __KEY__NUMPAD6,
	m7_Keypad = __KEY__NUMPAD7,
	m8_Keypad = __KEY__NUMPAD8,
	m9_Keypad = __KEY__NUMPAD9,
	m0_Keypad = __KEY__NUMPAD0,
	mComma_Keypad = __KEY__NUMPADCOMMA,
	mEnter_Keypad = __KEY__NUMPADENTER,
	mEquals_Keypad = __KEY__NUMPADENTER,
	mMinus_Keypad = __KEY__NUMPADMINUS,
	mPeriod_Keypad = __KEY__DECIMAL,
	mPlus_Keypad = __KEY__NUMPADPLUS,
	mPeriod = __KEY__PERIOD,
	mPageDown = __KEY__PGDN,
	mPgDn = __KEY__PGDN,
	mPGDN = __KEY__PGDN,
	mPageUp = __KEY__PGUP,
	mPgUp = __KEY__PGUP,
	mPGUP = __KEY__PGUP,
	mPause = __KEY__PAUSE,
	mPlayPause = __KEY__PLAYPAUSE,
	mPower = __KEY__POWER,
	mPreviousTrack = __KEY__PREVTRACK,
	mEnter = __KEY__RETURN,
	mReturn = __KEY__RETURN,
	mScrollLock = __KEY__SCROLL,
	mSemiColor = __KEY__SEMICOLON,
	mSlash = __KEY__SLASH,
	mSleep = __KEY__SLEEP,
	mSpace = __KEY__SPACE,
	mTab = __KEY__TAB,
	mVolumeDown = __KEY__VOLUMEDOWN,
	mVolumeUp = __KEY__VOLUMEUP,
	mWake = __KEY__WAKE,
	mWebBack = __KEY__WEBBACK,
	mWebFavorites = __KEY__WEBFAVORITES,
	mWebForward = __KEY__WEBFORWARD,
	mWebHome = __KEY__WEBHOME,
	mWebRefresh = __KEY__WEBREFRESH,
	mWebSearch = __KEY__WEBSEARCH,
	mWebStop = __KEY__WEBSTOP,

	mNullKey
};
*/

extern const char           *gKeyName[256];
extern bool 				gKeyPressed[256];


extern bool gKeyDownCtrl;
extern bool gKeyDownShift;
extern bool gKeyDownAlt;


#endif
