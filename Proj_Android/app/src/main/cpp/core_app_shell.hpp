
//Documentation is for losers.

#ifndef APP_SHELL_H
#define APP_SHELL_H

#include "os_core_outlets.h"
#include "core_includes.h"

//The bread and butter of a cross-platform app..
//OS App shell should include this, plus the necessary gfx libraries, sound libraries, and such.

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////
////      These must all be called before anything else can happen.
////

// FIRST call THESE...
//Directory from which assets are loaded.
void AppShellSetDirectoryBundle(const char *pFilePath);
//Directory to which data is saved.
void AppShellSetDirectoryDocuments(const char *pFilePath);
//Directory where files can be exported...
void AppShellSetDirectoryExport(const char *pFilePath);
//
void AppShellSetDeviceSize(int pWidth, int pHeight);
void AppShellSetVirtualFrame(int pX, int pY, int pWidth, int pHeight);
void AppShellSetSafeAreaInsets(int pInsetUp, int pInsetRight, int pInsetDown, int pInsetLeft);


// THEN call THIS...
void AppShellInitialize(int pEnvironment);

//Next, consider these...
void AppShellGraphicsSetUp();
void AppShellGraphicsTearDown();

// THEN call THIS...
void AppShellLoad();



//
void AppShellSetOSVersion(float pOSVersion);

//1X, 2X, 3X, 4X...
void AppShellSetImageFileScale(int pScale);
void AppShellSetSpriteDrawScale(float pScale);


////
////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


void AppShellFrame();

//void AppShellLoad();
//void AppShellLoadComplete();


//This will possibly be called asynchronously from the draw loop?
//void AppShellUpdate();

//This will get called before the render buffer is swapped on the OS render loop. Basically... it's the "Draw" function..
//void AppShellDraw();

void AppShellTouchDownDroid(float pX, float pY, int pIndex, int pCount);
void AppShellTouchMoveDroid(float pX, float pY, int pIndex, int pCount);
void AppShellTouchUpDroid(float pX, float pY, int pIndex, int pCount);
void AppShellTouchCanceledDroid(float pX, float pY, int pIndex, int pCount);

void AppShellTouchDown(float pX, float pY, void *pData);
void AppShellTouchMove(float pX, float pY, void *pData);
void AppShellTouchUp(float pX, float pY, void *pData);
void AppShellTouchCanceled(float pX, float pY, void *pData);

void AppShellMouseDown(float pX, float pY, int pButton);
void AppShellMouseMove(float pX, float pY);
void AppShellMouseUp(float pX, float pY, int pButton);

void AppShellMouseWheel(int pDirection);

void AppShellKeyDown(int pKey);
void AppShellKeyUp(int pKey);

void AppShellExit();
void AppShellPause();
void AppShellResume();

void AppShellMemoryWarning(bool pSevere);

void AppShellPurchaseSuccessful(const char *pName);
void AppShellPurchaseFailed(const char *pName);
void AppShellPurchaseCanceled(const char *pName);

void AppShellAdBannerSetVisible(bool pVisible);

void AppShellAccelerometer(float pAccelX, float pAccelY, float pAccelZ);


#endif
