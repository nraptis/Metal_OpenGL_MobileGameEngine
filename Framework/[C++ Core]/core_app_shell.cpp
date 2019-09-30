
#include "core_app_shell.hpp"
#include "os_core_graphics.h"
#include "os_core_social.h"
#include "os_core_sound.h"
#include "os_core_music.h"

#include "FApp.hpp"
#include "PlatformGraphicsInterface.hpp"

float gDeviceWidth = 1024.0f;
float gDeviceHeight = 768.0f;

float gDeviceWidth2 = (gDeviceWidth / 2.0f);
float gDeviceHeight2 = (gDeviceHeight / 2.0f);

float gVirtualDevX = 0.0f;
float gVirtualDevY = 0.0f;
float gVirtualDevWidth = 640.0f;
float gVirtualDevHeight = 700.0f;

float gAppWidth = 1024.0f;
float gAppHeight = 768.0f;
float gAppWidth2 = (gAppWidth / 2.0f);
float gAppHeight2 = (gAppHeight / 2.0f);

float gSafeAreaInsetTop = 0.0f;
float gSafeAreaInsetRight = 0.0f;
float gSafeAreaInsetBottom = 0.0f;
float gSafeAreaInsetLeft = 0.0f;

float gOSVersion = 1.0f;

float gSoundVolume = 1.0f;
float gMusicVolume = 1.0f;

bool gSoundEnabled = true;
bool gMusicEnabled = true;



bool gAdBannerVisible = false;

const char *gKeyName[256];
bool gKeyPressed[256];

FString gDirDocuments;
FString gDirBundle;
FString gDirExport;

FRandomizer gRand;
FTouchManager gTouch;
FNotificationCenter gNotify;
FTextureCache gTextureCache;
FBufferCache gBufferCache;

int gEnvironment = ENV_IOS;

int gImageResolutionScale = 1;
float gSpriteDrawScale = 1.0f;

bool gKeyDownCtrl = false;
bool gKeyDownShift = false;
bool gKeyDownAlt = false;



void AppShellInitialize(int pEnvironment) {
    gEnvironment = pEnvironment;
    
    //TODO: This is only for SCREEN FRAME UTIL on iPHONE...
    //AppShellSetVirtualFrame(gSafeAreaInsetLeft, gSafeAreaInsetTop, gDeviceWidth - (gSafeAreaInsetLeft + gSafeAreaInsetRight), gDeviceHeight - (gSafeAreaInsetTop + gSafeAreaInsetBottom));
    AppShellSetVirtualFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
	FList aResourceList;
    
	os_getAllResources(gDirBundle.c(), &aResourceList);
	os_getAllResources(gDirDocuments.c(), &aResourceList);

	EnumList(FString, aPath, aResourceList)gRes.AddResource(aPath->c());
	FreeList(FString, aResourceList);
    
    gGraphicsInterface = new PlatformGraphicsInterface();
    
    os_initialize_outlets();
    sound_initialize();
    music_initialize();
    social_Init();
    
    AppShellSetImageFileScale(gImageResolutionScale);
    
    //if(gAppBase)(gAppBase)->BaseInitialize();
    //gTouch.Initialize(pEnvironment);
    
    //sSoundList.mUnique = true;
    //sSoundInstanceList.mUnique = true;
    //sSpriteList.mUnique = true;
    
	for (int aCount = 0; aCount < 255; aCount++) {
		gKeyPressed[aCount] = false;
		gKeyName[aCount] = "???";
	}
    
	gKeyName[__KEY__0] = "0";
	gKeyName[__KEY__1] = "1";
	gKeyName[__KEY__2] = "2";
	gKeyName[__KEY__3] = "3";
	gKeyName[__KEY__4] = "4";
	gKeyName[__KEY__5] = "5";
	gKeyName[__KEY__6] = "6";
	gKeyName[__KEY__7] = "7";
	gKeyName[__KEY__8] = "8";
	gKeyName[__KEY__9] = "9";
	gKeyName[__KEY__A] = "A";
	gKeyName[__KEY__B] = "B";
	gKeyName[__KEY__C] = "C";
	gKeyName[__KEY__D] = "D";
	gKeyName[__KEY__E] = "E";
	gKeyName[__KEY__F] = "F";
	gKeyName[__KEY__G] = "G";
	gKeyName[__KEY__H] = "H";
	gKeyName[__KEY__I] = "I";
	gKeyName[__KEY__J] = "J";
	gKeyName[__KEY__K] = "K";
	gKeyName[__KEY__L] = "L";
	gKeyName[__KEY__M] = "M";
	gKeyName[__KEY__N] = "N";
	gKeyName[__KEY__O] = "O";
	gKeyName[__KEY__P] = "P";
	gKeyName[__KEY__Q] = "Q";
	gKeyName[__KEY__R] = "R";
	gKeyName[__KEY__S] = "S";
	gKeyName[__KEY__T] = "T";
	gKeyName[__KEY__U] = "U";
	gKeyName[__KEY__V] = "V";
	gKeyName[__KEY__W] = "W";
	gKeyName[__KEY__X] = "X";
	gKeyName[__KEY__Y] = "Y";
	gKeyName[__KEY__Z] = "Z";
	gKeyName[__KEY__APOSTROPHE] = "'";
	gKeyName[__KEY__APPS] = "APPLICATION";
	gKeyName[__KEY__BACK] = "BACKSPACE";
	gKeyName[__KEY__BACKSLASH] = "\\";
	gKeyName[__KEY__BACKSPACE] = "BACKSPACE";
	gKeyName[__KEY__CALCULATOR] = "CALCULATOR";
	gKeyName[__KEY__CAPITAL] = "CAPS LOCK";
	gKeyName[__KEY__COMMA] = ",";
	gKeyName[__KEY__DECIMAL] = ". (KEYPAD)";
	gKeyName[__KEY__DELETE] = "DELETE";
	gKeyName[__KEY__DIVIDE] = "/ (KEYPAD)";
	gKeyName[__KEY__DOWN] = "DOWN ARROW";
	gKeyName[__KEY__UP] = "UP ARROW";
	gKeyName[__KEY__LEFT] = "LEFT ARROW";
	gKeyName[__KEY__RIGHT] = "RIGHT ARROW";
	gKeyName[__KEY__END] = "END";
	gKeyName[__KEY__EQUALS] = "=";
	gKeyName[__KEY__ESCAPE] = "ESC";
	gKeyName[__KEY__F1] = "F1";
	gKeyName[__KEY__F2] = "F2";
	gKeyName[__KEY__F3] = "F3";
	gKeyName[__KEY__F4] = "F4";
	gKeyName[__KEY__F5] = "F5";
	gKeyName[__KEY__F6] = "F6";
	gKeyName[__KEY__F7] = "F7";
	gKeyName[__KEY__F8] = "F8";
	gKeyName[__KEY__F9] = "F9";
	gKeyName[__KEY__F10] = "F10";
	gKeyName[__KEY__F11] = "F11";
	gKeyName[__KEY__F12] = "F12";
	gKeyName[__KEY__GRAVE] = "`";
	gKeyName[__KEY__HOME] = "HOME";
	gKeyName[__KEY__INSERT] = "INSERT";
	gKeyName[__KEY__LALT] = "LEFT ALT";
	gKeyName[__KEY__RALT] = "RIGHT ALT";
	gKeyName[__KEY__LBRACKET] = "[";
	gKeyName[__KEY__RBRACKET] = "]";
	gKeyName[__KEY__LCONTROL] = "LEFT CTRL";
	gKeyName[__KEY__RCONTROL] = "RIGHT CTRL";
	gKeyName[__KEY__LSHIFT] = "LEFT SHIFT";
	gKeyName[__KEY__RSHIFT] = "RIGHT SHIFT";
	gKeyName[__KEY__LWIN] = "LEFT WIN";
	gKeyName[__KEY__RWIN] = "RIGHT WIN";
	gKeyName[__KEY__MAIL] = "MAIL";
	gKeyName[__KEY__MEDIASELECT] = "MEDIA SELECT";
	gKeyName[__KEY__MEDIASTOP] = "MEDIA STOP";
	gKeyName[__KEY__MINUS] = "-";
	gKeyName[__KEY__MULTIPLY] = "* (KEYPAD)";
	gKeyName[__KEY__MUTE] = "MUTE";
	gKeyName[__KEY__MYCOMPUTER] = "MY COMPUTER";
	gKeyName[__KEY__NEXTTRACK] = "NEXT TRACK";
	gKeyName[__KEY__NUMLOCK] = "NUMLOCK";
	gKeyName[__KEY__NUMPAD1] = "1 (KEYPAD)";
	gKeyName[__KEY__NUMPAD2] = "2 (KEYPAD)";
	gKeyName[__KEY__NUMPAD3] = "3 (KEYPAD)";
	gKeyName[__KEY__NUMPAD4] = "4 (KEYPAD)";
	gKeyName[__KEY__NUMPAD5] = "5 (KEYPAD)";
	gKeyName[__KEY__NUMPAD6] = "6 (KEYPAD)";
	gKeyName[__KEY__NUMPAD7] = "7 (KEYPAD)";
	gKeyName[__KEY__NUMPAD8] = "8 (KEYPAD)";
	gKeyName[__KEY__NUMPAD9] = "9 (KEYPAD)";
	gKeyName[__KEY__NUMPAD0] = "0 (KEYPAD)";
	gKeyName[__KEY__NUMPADCOMMA] = ", (KEYPAD)";
	gKeyName[__KEY__NUMPADENTER] = "ENTER (KEYPAD)";
	gKeyName[__KEY__NUMPADEQUALS] = "= (KEYPAD)";
	gKeyName[__KEY__NUMPADMINUS] = "- (KEYPAD)";
	gKeyName[__KEY__NUMPADPERIOD] = ". (KEYPAD)";
	gKeyName[__KEY__NUMPADPLUS] = "+ (KEYPAD)";
	gKeyName[__KEY__NUMPADSLASH] = "/ (KEYPAD)";
	gKeyName[__KEY__PAUSE] = "PAUSE";
	gKeyName[__KEY__PERIOD] = ".";
	gKeyName[__KEY__PGDN] = "PAGE DOWN";
	gKeyName[__KEY__PGUP] = "PAGE UP";
	gKeyName[__KEY__PLAYPAUSE] = "PAUSE";
	gKeyName[__KEY__POWER] = "POWER";
	gKeyName[__KEY__PREVTRACK] = "PREVIOUS";
	gKeyName[__KEY__RETURN] = "ENTER";
	gKeyName[__KEY__SCROLL] = "SCROLL LOCK";
	gKeyName[__KEY__SEMICOLON] = ";";
	gKeyName[__KEY__SLASH] = "/";
	gKeyName[__KEY__SLEEP] = "SLEEP";
	gKeyName[__KEY__SPACE] = "SPACE";
	gKeyName[__KEY__TAB] = "TAB";
	gKeyName[__KEY__VOLUMEDOWN] = "VOLUME DOWN";
	gKeyName[__KEY__VOLUMEUP] = "VOLUME UP";
	gKeyName[__KEY__WAKE] = "WAKE";
	gKeyName[__KEY__WEBBACK] = "WEB BACK";
	gKeyName[__KEY__WEBFAVORITES] = "FAVORITES";
	gKeyName[__KEY__WEBFORWARD] = "WEB FORWARD";
	gKeyName[__KEY__WEBHOME] = "WEB HOME";
	gKeyName[__KEY__WEBREFRESH] = "WEB REFRESH";
	gKeyName[__KEY__WEBSEARCH] = "WEB SEARCH";
	gKeyName[__KEY__WEBSTOP] = "WEB STOP";

}

void AppShellLoad() {
    if (gAppBase) {
        gAppBase->BaseLoad();
        gAppBase->BaseLoadComplete();
    }
}

void AppShellSetDeviceSize(int pWidth, int pHeight) {
    
    Log("Device Size Set: [%d x %d]\n", pWidth, pHeight);
    
	gDeviceWidth = (float)pWidth;
	gDeviceHeight = (float)pHeight;
	gDeviceWidth2 = (gDeviceWidth / 2.0f);
	gDeviceHeight2 = (gDeviceHeight / 2.0f);
    
    FApp *aApp = (gAppBase);
    if (aApp) {
		aApp->BaseSetDeviceSize(gDeviceWidth, gDeviceHeight);
        if ((gVirtualDevWidth > 0.0f) && (gVirtualDevHeight > 0.0f)) {

            //TODO: Toggle for crop tool...
            //aApp->BaseSetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
            
            float aAspectRatio = 768.0f / 1024.0f;
            
            
            /*
            if (false) {
                
                
                float aVirtualHeight = round(gDeviceHeight * 0.75f);
                float aVirtualWidth = round(aVirtualHeight * aAspectRatio);
                float aVirtualX = round(gDeviceWidth / 2.0f - (aVirtualWidth / 2.0f));
                float aVirtualY = gDeviceHeight - (5.0f + aVirtualHeight);
                
                
                
                //TODO:
                AppShellSetVirtualFrame(aVirtualX, aVirtualY, aVirtualWidth, aVirtualHeight);
                
            } else {
                float aPadding = 5.0f;
                float aVirtualHeight = round(gDeviceHeight - (aPadding * 2.0f));
                float aVirtualWidth = round(gDeviceHeight * aAspectRatio);
                float aVirtualX = round(gDeviceWidth / 2.0f - (aVirtualWidth / 2.0f));
                float aVirtualY = aPadding;
                
                
                
                //TODO:
                AppShellSetVirtualFrame(aVirtualX, aVirtualY, aVirtualWidth, aVirtualHeight);
            }
            */
            
            
            //aApp->BaseSetVirtualFrame(aVirtualX, aVirtualY, aVirtualWidth, aVirtualHeight);
        }
    } else {
        Log("Error: Expected gAppBase not NULL\n");
    }
    
    //
    //TODO: Remove Kludge
    //
    //AppShellSetSafeAreaInsets(24.0f, 5.0f, 90.0f, 5.0f);
    //
    //
}

void AppShellSetVirtualFrame(int pX, int pY, int pWidth, int pHeight) {
	gVirtualDevX = (float)pX;
	gVirtualDevY = (float)pY;
	gVirtualDevWidth = (float)pWidth;
    //TODO:
    gVirtualDevHeight = (float)pHeight;
    
    //TODO: Toggle for Galaxy Test
    //gVirtualDevHeight = (float)pWidth * 4.0f / 3.0f;
    
    //Log("Set Virtual Frame [%f %f %f %f]\n", gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    
    gAppWidth = (float)pWidth;
    gAppHeight = (float)pHeight;
    gAppWidth2 = (gAppWidth / 2.0f);
    gAppHeight2 = (gAppHeight / 2.0f);

	if (gAppBase) {
        gAppBase->BaseSetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    }
}

void AppShellSetSafeAreaInsets(int pInsetUp, int pInsetRight, int pInsetDown, int pInsetLeft) {
    
    //Log("I - AppShellSetSafeAreaInsets(%d, %d, %d, %d)\n", pInsetUp, pInsetRight, pInsetDown, pInsetLeft);
    
    gSafeAreaInsetTop = pInsetUp;
    gSafeAreaInsetRight = pInsetRight;
    gSafeAreaInsetBottom = pInsetDown;
    gSafeAreaInsetLeft = pInsetLeft;
    
    //Log("II - AppShellSetSafeAreaInsets(%f, %f, %f, %f)\n", gSafeAreaInsetTop, gSafeAreaInsetRight, gSafeAreaInsetBottom, gSafeAreaInsetLeft);
    
    if (gAppBase) {
        gAppBase->BaseSetSafeAreaInsets(gSafeAreaInsetTop, gSafeAreaInsetRight, gSafeAreaInsetBottom, gSafeAreaInsetLeft);
    }
}



void AppShellSetDirectoryBundle(const char *pFilePath) {
    gDirBundle = pFilePath;
}

void AppShellSetDirectoryDocuments(const char *pFilePath) {
    gDirDocuments = pFilePath;
}

void AppShellSetDirectoryExport(const char *pFilePath) {
    gDirExport = pFilePath;
}

void AppShellSetOSVersion(float pOSVersion) {
    gOSVersion = pOSVersion;
}

//1X, 2X, 3X, 4X...
void AppShellSetImageFileScale(int pScale) {
    gImageResolutionScale = pScale;
    if (gAppBase) gAppBase->BaseSetImageFileScale(pScale);
}

void AppShellSetSpriteDrawScale(float pScale) {
    
    gSpriteDrawScale = pScale;
    
    if (gSpriteDrawScale < 1.0f) {
        gSpriteDrawScale = 1.0f;
    } else if (gSpriteDrawScale >= 1.0f && gSpriteDrawScale < 2.0f) {
        if (gSpriteDrawScale >= 1.5f) {
            gSpriteDrawScale = 1.5f;
        } else {
            gSpriteDrawScale = 1.0f;
        }
    } else if (gSpriteDrawScale >= 2.0f && gSpriteDrawScale < 3.0f) {
        if (gSpriteDrawScale >= 2.5f) {
            gSpriteDrawScale = 2.5f;
        } else {
            gSpriteDrawScale = 2.0f;
        }
    } else if (gSpriteDrawScale >= 3.0f && gSpriteDrawScale < 4.0f) {
        
        if (gSpriteDrawScale >= 3.5f) {
            gSpriteDrawScale = 3.5f;
        } else {
            gSpriteDrawScale = 3.0f;
        }
    } else {
        gSpriteDrawScale = 4.0f;
    }
}

void AppShellFrame() {
    if (gAppBase) gAppBase->BaseFrame();
}

void AppShellTouchDownDroid(float pX, float pY, int pIndex, int pCount) {
    if (gAppBase) gAppBase->BaseTouchDownDroid(pX, pY, pIndex, pCount);
}

void AppShellTouchMoveDroid(float pX, float pY, int pIndex, int pCount) {
    if (gAppBase) gAppBase->BaseTouchMoveDroid(pX, pY, pIndex, pCount);
}

void AppShellTouchUpDroid(float pX, float pY, int pIndex, int pCount) {
    if(gAppBase)(gAppBase)->BaseTouchUpDroid(pX, pY, pIndex, pCount);
}

void AppShellTouchCanceledDroid(float pX, float pY, int pIndex, int pCount)
{
    if(gAppBase)(gAppBase)->BaseTouchCanceledDroid(pX, pY, pIndex, pCount);
}

void AppShellTouchDown(float pX, float pY, void *pData) {
    if(gAppBase) (gAppBase)->BaseTouchDown(pX, pY, pData);
}

void AppShellTouchMove(float pX, float pY, void *pData) {
    if(gAppBase)(gAppBase)->BaseTouchMove(pX, pY, pData);
}

void AppShellTouchUp(float pX, float pY, void *pData) {
    if(gAppBase) gAppBase->BaseTouchUp(pX, pY, pData);
}

void AppShellTouchCanceled(float pX, float pY, void *pData) {
    if (gAppBase) gAppBase->BaseTouchCanceled(pX, pY, pData);
}

void AppShellMouseDown(float pX, float pY, int pButton) {
	if (gAppBase) gAppBase->BaseMouseDown(pX, pY, pButton);
}

void AppShellMouseMove(float pX, float pY) {
	if (gAppBase) gAppBase->BaseMouseMove(pX, pY);
}

void AppShellMouseUp(float pX, float pY, int pButton) {
	if(gAppBase)(gAppBase)->BaseMouseUp(pX, pY, pButton);
}

void AppShellMouseWheel(int pDirection) {
	if(gAppBase)gAppBase->BaseMouseWheel(pDirection);
}

void AppShellKeyDown(int pKey) {
    if (pKey >= 0 && pKey < 256) {
        //Log("AppShellKeyDown([%d]=>%s)\n", pKey, gKeyName[pKey]);
        if (gAppBase) gAppBase->BaseKeyDown(pKey);
    } else {
        
    }
}

void AppShellKeyUp(int pKey) {
    if (pKey >= 0 && pKey < 256) {
        //Log("AppShellKeyUp([%d]=>%s)\n", pKey, gKeyName[pKey]);
        if (gAppBase) gAppBase->BaseKeyUp(pKey);
    } else {
        
    }
}

void AppShellSetAdBannerWidth(float pWidth) {
    
}

void AppShellSetAdBannerHeight(float pHeight) {
    
}

void AppShellExit() {
    if (gAppBase) {
        (gAppBase)->BaseInactive();
        (gAppBase)->BaseQuit();
    }
}

void AppShellPause() {
    if (gAppBase) {
        (gAppBase)->BaseInactive();
    }
}

void AppShellResume() {
    if (gAppBase) {
        (gAppBase)->BaseActive();
    }
}


void AppShellMemoryWarning(bool pSevere) {
    if (gAppBase) {
        
    }
}

void AppShellPurchaseSuccessful(const char *pName) {
    
}

void AppShellPurchaseFailed(const char *pName) {
    
}

void AppShellPurchaseCanceled(const char *pName) {
    
}

void AppShellAdBannerSetVisible(bool pVisible) {
    gAdBannerVisible = pVisible;
}

void AppShellAccelerometer(float pAccelX, float pAccelY, float pAccelZ) {
    
}
