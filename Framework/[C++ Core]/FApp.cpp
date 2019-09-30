//
//  FApp.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 9/26/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FApp.hpp"
#include "core_includes.h"
#include "core_app_shell.hpp"
#include "PlatformGraphicsInterface.hpp"

FApp *gAppBase = NULL;
PlatformGraphicsInterface *gGraphicsInterface = NULL;

FApp::FApp() {
    gAppBase = this;
    
    mFrameCaptureUpdateCount = 0;
    
    
    mFrameCaptureDrawCount = 0;
    mSelectedCanvas = NULL;
    
    mIsGraphicsSetUpEnqueued = false;
    mGraphicsSetUpEnqueuedTimer = 0;
    
    mDarkMode = false;
    
    mDidInitialize = false;
    mDidDetachFrameController = false;
    mDidUpdate = false;
    mActive = true;
    
    mDidInitializeGraphicsInterface = false;
    
    mTouchX = 0.0f;
    mTouchY = 0.0f;
    
    mSelectedInputWindow = 0;
    
    mTimeSinceLastInteraction = 0;
    
    mQuit = false;
    
    mThrottleLock = -1;
    mSystemLock = -1;
    mInterfaceLock = -1;
    
    mWindowMain.mRoot.mName = "root-main";
    mWindowModal.mRoot.mName = "root-modal";
    mWindowTools.mRoot.mName = "root-tools";
    
    mIsLoading = false;
    mIsLoadingComplete = false;
    
    mUpdatesPerSecond = 100.0f;
    RecoverTime();
}

FApp::~FApp() {
    
}

void FApp::BaseInitialize() {
    if (mDidInitialize == false) {
        mDidInitialize = true;
        mImageLoadDirectoryList += new FString("");
        
        if (gDirBundle.mLength > 0) mImageLoadDirectoryList += new FString(gDirBundle.c());
        if (gDirDocuments.mLength > 0) mImageLoadDirectoryList += new FString(gDirDocuments.c());
        
        mImageLoadExtensionList += new FString("jpg");
        mImageLoadExtensionList += new FString("png");
        mImageLoadMutableSuffixList += new FString("");
        mImageLoadSuffixList += new FString("");
        
        while (gGraphicsInterface->IsReady() == false) {
            Log("BaseInitialize:: Waiting for GFX...\n");
            os_sleep(100);
        }
        
        Graphics::SetDeviceSize(gDeviceWidth, gDeviceHeight);
        
        
        //Initialize the graphics interface...
        gGraphicsInterface->Initialize();
        
        os_sleep(10);
        
        //Initialize the graphics engine...
        Graphics::Initialize();
        Graphics::SetUp();
        
        Initialize();
    }
}


void FApp::BaseSetDeviceSize(int pWidth, int pHeight) {
    
    //Log("DeviceSize[%.2f, %.2f]----\n", gDeviceWidth, gDeviceHeight);
    
    if (gGraphicsInterface && gGraphicsInterface->IsReady()) {
        Graphics::SetDeviceSize(pWidth, pHeight);
    }
    
    //mViewControllerTools.DeviceSizeChanged(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    SetDeviceSize(pWidth, pHeight);
    
    //mWindowTools.SetVirtualFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    
    mWindowTools.SetDeviceSize(gDeviceWidth, gDeviceHeight);
    mWindowModal.SetDeviceSize(gDeviceWidth, gDeviceHeight);
    mWindowMain.SetDeviceSize(gDeviceWidth, gDeviceHeight);
}

void FApp::BaseSetVirtualFrame(int pX, int pY, int pWidth, int pHeight) {
    
    //Log("Virtual Frame(%.2f, %.2f  %.2f, %.2f]  Dev[%.2f, %.2f]----\n", gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight, gDeviceWidth, gDeviceHeight);
    
    mWindowMain.SetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    mWindowModal.SetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    mWindowTools.SetVirtualFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    
    SetVirtualFrame(pX, pY, pWidth, pHeight);
}

void FApp::BaseSetSafeAreaInsets(int pInsetUp, int pInsetRight, int pInsetDown, int pInsetLeft) {
    
    //Log("SafeAreaInsets(%.2f, %.2f, %.2f, %.2f)----\n", gSafeAreaInsetTop, gSafeAreaInsetRight, gSafeAreaInsetBottom, gSafeAreaInsetLeft);
    
    mWindowMain.SetSafeAreaInsets(gSafeAreaInsetTop + 0.5f, gSafeAreaInsetRight + 0.5f, gSafeAreaInsetBottom + 0.5f, gSafeAreaInsetLeft + 0.5f);
    mWindowModal.SetSafeAreaInsets(gSafeAreaInsetTop + 0.5f, gSafeAreaInsetRight + 0.5f, gSafeAreaInsetBottom + 0.5f, gSafeAreaInsetLeft + 0.5f);
    mWindowTools.SetSafeAreaInsets(gSafeAreaInsetTop + 0.5f, gSafeAreaInsetRight + 0.5f, gSafeAreaInsetBottom + 0.5f, gSafeAreaInsetLeft + 0.5f);
    SetSafeAreaInsets(pInsetUp, pInsetRight, pInsetDown, pInsetLeft);
}

void AppFrameThread(void *pArgs) {
    gAppBase->MainRunLoop();
}

//Externally, we are getting a "frame" ...
void FApp::BaseFrame() {

    if (mDidInitialize == false) {
        BaseInitialize();
    }
    
    if (mDidDetachFrameController == false) {
        mDidDetachFrameController = true;
        os_detach_thread(AppFrameThread, (void*)0xB00BFACE);
        
    }
    
    if (mIsGraphicsSetUpEnqueued) {
        if (mGraphicsSetUpEnqueuedTimer > 0) {
            mGraphicsSetUpEnqueuedTimer -= 1;
        } else {
            mIsGraphicsSetUpEnqueued = false;
            Graphics::SetUp();
        }
    }
    
    gBufferCache.Reset();
    
    while (mDidUpdate == false) {
        Log("Waiting for An Update...\n");
        os_sleep(18);
    }
    
    //for (int i=0;i<aUpdateCount;i++) {
    //BaseUpdate();
    
        ThrottleLock();
    
        if (gGraphicsInterface) {
            gGraphicsInterface->SetContext();
        }
        gGraphicsInterface->Prerender();
        Graphics::PreRender();
        gAppBase->Prerender();
        //
        ////
        //
        BaseDraw();
        //
        ////
        //
        
        gAppBase->Postrender();
        Graphics::PostRender();
        gGraphicsInterface->Postrender();
        
        gGraphicsInterface->Commit();
        
        ThrottleUnlock();
    
}

void FApp::BaseUpdate() {
    if (mDidInitialize == false) {
        BaseInitialize();
    }
    
    
    int aSlot = 0;
    if (mFrameCaptureUpdateCount < FRAME_TIME_CAPTURE_COUNT) {
        aSlot = mFrameCaptureUpdateCount;
        ++mFrameCaptureUpdateCount;
    } else {
        for (int i=1;i<FRAME_TIME_CAPTURE_COUNT;i++) {
            mFrameCaptureUpdateTime[i-1] = mFrameCaptureUpdateTime[i];
        }
        aSlot = FRAME_TIME_CAPTURE_COUNT - 1;
    }
    mFrameCaptureUpdateTime[aSlot] = os_system_time();
    
    
    //if (mLo == false) {
    //    gTouch.Reset();
    //    return;
    //}
    
    mDidUpdate = true;
    
    InterfaceLock();
    gTouch.Update();
    InterfaceUnlock();
    
    Update();
    
    mWindowMain.Update();
    mWindowModal.Update();
    mWindowTools.Update();
    
    sound_update();
    music_update();

    
}

void FApp::BaseDraw() {
    
    if (mActive == false) { return; }
    if (mIsGraphicsSetUpEnqueued == true) {
        Log("BLOCKING: SETUP...\n");
        return;
    }

    int aSlot = 0;
    if (mFrameCaptureDrawCount < FRAME_TIME_CAPTURE_COUNT) {
        aSlot = mFrameCaptureDrawCount;
        ++mFrameCaptureDrawCount;
    } else {
        for (int i=1;i<FRAME_TIME_CAPTURE_COUNT;i++) {
            mFrameCaptureDrawTime[i-1] = mFrameCaptureDrawTime[i];
        }
        aSlot = FRAME_TIME_CAPTURE_COUNT - 1;
    }
    mFrameCaptureDrawTime[aSlot] = os_system_time();
    

    //Graphics::ViewportSet(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    FMatrix aOrtho = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -2048.0f, 2048.0f);
    Graphics::MatrixProjectionSet(aOrtho);
    
    //FMatrix aScreenProjection = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -1024.0f, 1024.0f);
    //Graphics::MatrixProjectionSet(aScreenProjection);
    Graphics::MatrixModelViewReset();
    //Graphics::Clear(0.0f, 0.0f, 0.0f);
    
    
    Graphics::TextureSetClamp();
    
    //TODO: Attach the appropriate
    //pipeline state...
    
    //Graphics::BlendEnable();
    //Graphics::CullFacesEnable();
    //Graphics::CullFacesSetFront();
    
    Graphics::ClipDisable();
    
    
    Draw();
    
    mWindowMain.Draw();
    mWindowModal.Draw();
    mWindowTools.Draw();
    
    Graphics::MatrixProjectionSet(aOrtho);
    Graphics::MatrixModelViewReset();
    DrawOver();
    
    if (mIsLoadingComplete && Graphics::RenderPass() == GFX_RENDER_PASS_2D_MAIN) {
        
        /*
        
        Graphics::MatrixProjectionResetOrtho();
        Graphics::MatrixModelViewReset();
        Graphics::SetColor();
        Graphics::PipelineStateSetSpritePremultipliedBlending();
        
        FString aResString = FString("HW: ") + FString(gDeviceWidth, 2) + FString(" x ") + FString(gDeviceHeight, 2) + FString(", VD: ") + FString(gVirtualDevWidth, 2) + FString(" x ") + FString(gVirtualDevHeight, 2);
        mSysFont.Center(aResString, gDeviceWidth2, gDeviceHeight - 80.0f);
        
        FString aFPSString = FString("FPS: ") + FString(GetFPS()) + FString(", ") + FString("UPS: ") + FString(GetUPS());
        mSysFont.Center(aFPSString, gDeviceWidth2, gDeviceHeight - 52.0f);
        
        FString aScaleString = FString("SCL: ") + FString(gSpriteDrawScale) + FString(", ") + FString("REZ: ") + FString(gImageResolutionScale);
        mSysFont.Center(aScaleString, gDeviceWidth2, gDeviceHeight - 24.0f);
         
        */
        
        
    }
    
    if (mIsLoadingComplete && Graphics::RenderPass() == GFX_RENDER_PASS_2D_MAIN) {
        
        /*
        Graphics::PipelineStateSetShape2DAlphaBlending();
        Graphics::SetColor(0.55f, 0.55f, 0.55f, 0.5f);
        Graphics::DrawLine(gVirtualDevX + gSafeAreaInsetLeft, gVirtualDevY, gVirtualDevX + gSafeAreaInsetLeft, gVirtualDevY + gVirtualDevHeight, 2.0f);
        Graphics::DrawLine(gVirtualDevX + gVirtualDevWidth - gSafeAreaInsetRight, gVirtualDevY, gVirtualDevX + gVirtualDevWidth - gSafeAreaInsetRight, gVirtualDevY + gVirtualDevHeight, 2.0f);
        Graphics::DrawLine(gVirtualDevX, gVirtualDevY + gSafeAreaInsetTop, gVirtualDevX + gVirtualDevWidth, gVirtualDevY + gSafeAreaInsetTop, 2.0f);
        Graphics::DrawLine(gVirtualDevX, gVirtualDevY + gVirtualDevHeight - gSafeAreaInsetBottom, gVirtualDevX + gVirtualDevWidth, gVirtualDevY + gVirtualDevHeight - gSafeAreaInsetBottom, 2.0f);
        
        
        Graphics::SetColor(0.11f, 0.11f, 0.11f, 0.5f);
        Graphics::DrawLine(gVirtualDevX + gSafeAreaInsetLeft, gVirtualDevY, gVirtualDevX + gSafeAreaInsetLeft, gVirtualDevY + gVirtualDevHeight);
        Graphics::DrawLine(gVirtualDevX + gVirtualDevWidth - gSafeAreaInsetRight, gVirtualDevY, gVirtualDevX + gVirtualDevWidth - gSafeAreaInsetRight, gVirtualDevY + gVirtualDevHeight);
        Graphics::DrawLine(gVirtualDevX, gVirtualDevY + gSafeAreaInsetTop, gVirtualDevX + gVirtualDevWidth, gVirtualDevY + gSafeAreaInsetTop, 1.0f);
        Graphics::DrawLine(gVirtualDevX, gVirtualDevY + gVirtualDevHeight - gSafeAreaInsetBottom, gVirtualDevX + gVirtualDevWidth, gVirtualDevY + gVirtualDevHeight - gSafeAreaInsetBottom, 1.0f);
        */
    }
    
    if (mDarkMode == true) {
        Graphics::PipelineStateSetShape2DAlphaBlending();
        //Graphics::SetColor(0.0075f, 0.0075f, 0.0075f, 0.93f);
        Graphics::SetColor(0.0075f, 0.0075f, 0.0075f, 0.925f);
        
        Graphics::DrawRect(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
        Graphics::SetColor();
    }
    
}

void FApp::BaseLoad() {
    if (mDidInitialize == false) {
        BaseInitialize();
    }
    
    BaseSetDeviceSize(gDeviceWidth, gDeviceHeight);
    BaseSetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    BaseSetSafeAreaInsets(gSafeAreaInsetTop, gSafeAreaInsetRight, gSafeAreaInsetBottom, gSafeAreaInsetLeft);
    
    
    mIsLoading = true;
    
    //os_getAssetScale()
    
    //bndl_sys_font_data.json
    //bndl_sys_font_scale_1.png
    //bndl_sys_font_scale_2.png
    //bndl_sys_font_scale_3.png
    //bndl_sys_font_scale_4.png
    //sys_font.kern
    
    int aImageScale = (int)(gSpriteDrawScale + 0.5f);
    int aScreenScale = os_getAssetScale();
    if (aScreenScale == 0) { aScreenScale = 1; }
    if (aImageScale > aScreenScale) { aScreenScale = aImageScale; }
    AppShellSetImageFileScale(aScreenScale);
    
    
    //gImageBundler.StartBundle("bndl_roboto_bold_260");
    //if (gImageBundler.mBundleWidth > 32 && gImageBundler.mBundleHeight > 32) {
    //    mSysFontBold.LoadNew("roboto_bold_260_font.kern", "roboto_bold_260_");
    //}
    //gImageBundler.EndBundle();
    
    
    gImageBundler.StartBundle("bndl_roboto_bold_300");
    if (gImageBundler.mBundleWidth > 32 && gImageBundler.mBundleHeight > 32) {
        mSysFontBold.LoadNew("roboto_bold_300_font.kern", "roboto_bold_300_");
    }
    gImageBundler.EndBundle();
    
    mSysFontBold.mDataScale = 0.125f * aImageScale;
    mSysFontBold.ApplyExpand(14.0f);
    mSysFontBold.SetSpaceWidth(64.0f);
    
    
    
    
    //gImageBundler.StartBundle("bndl_roboto_260");
    //if (gImageBundler.mBundleWidth > 32 && gImageBundler.mBundleHeight > 32) {
    //    mSysFont.LoadNew("roboto_260_font.kern", "roboto_260_");
    //}
    //gImageBundler.EndBundle();
    
    gImageBundler.StartBundle("bndl_roboto_300");
    if (gImageBundler.mBundleWidth > 32 && gImageBundler.mBundleHeight > 32) {
        mSysFont.LoadNew("roboto_300_font.kern", "roboto_300_");
    }
    gImageBundler.EndBundle();
    
    mSysFont.mDataScale = 0.125f * aImageScale;
    mSysFont.ApplyExpand(14.0f);
    mSysFont.SetSpaceWidth(64.0f);
    
    
    AppShellSetImageFileScale(1);
    
    
    Load();
    
    
    
    
    /*
    gImageBundler.mAutoBundle = true;
    gImageBundler.StartBundle("bndl_roboto_300");
    mFontLarge.LoadNew("roboto_300_font.kern", "roboto_300_");
    gImageBundler.EndBundle();
    
    gImageBundler.StartBundle("bndl_roboto_bold_300");
    mFontSmall.LoadNew("roboto_bold_300_font.kern", "roboto_bold_300_");
    gImageBundler.EndBundle();
    */
    //
    //
    //
}

void FApp::BaseLoadComplete() {
    
    mIsLoading = false;
    mIsLoadingComplete = true;
    
    
    
    LoadComplete();
    
    //BaseSetDeviceSize(gDeviceWidth, gDeviceHeight);
    //BaseSetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    //BaseSetSafeAreaInsets(gSafeAreaInsetTop, gSafeAreaInsetRight, gSafeAreaInsetBottom, gSafeAreaInsetLeft);
    
    
}

void FApp::MouseDown(float pX, float pY, int pButton) {
    
}

void FApp::MouseMove(float pX, float pY) {
    
}

void FApp::MouseUp(float pX, float pY, int pButton) {
    
}

void FApp::MouseWheel(int pDirection) {
    
}

void FApp::KeyDown(int pKey) {
    
}

void FApp::KeyUp(int pKey) {
    
}

void FApp::BaseTouchDown(float pX, float pY, void *pData) {
    InterfaceLock();
    gTouch.BaseTouchDown(pX, pY, pData);
    InterfaceUnlock();
}

void FApp::BaseTouchMove(float pX, float pY, void *pData) {
    InterfaceLock();
    gTouch.BaseTouchMove(pX, pY, pData);
    InterfaceUnlock();
}

void FApp::BaseTouchUp(float pX, float pY, void *pData) {
    InterfaceLock();
    gTouch.BaseTouchUp(pX, pY, pData);
    InterfaceUnlock();
}

void FApp::BaseTouchCanceled(float pX, float pY, void *pData) {
    InterfaceLock();
    gTouch.BaseTouchCanceled(pX, pY, pData);
    InterfaceUnlock();
}

void FApp::BaseTouchDownDroid(float pX, float pY, int pIndex, int pCount) {
    InterfaceLock();
    gTouch.BaseTouchDownDroid(pX, pY, pIndex, pCount);
    InterfaceUnlock();
}

void FApp::BaseTouchMoveDroid(float pX, float pY, int pIndex, int pCount) {
    InterfaceLock();
    gTouch.BaseTouchMoveDroid(pX, pY, pIndex, pCount);
    InterfaceUnlock();
}

void FApp::BaseTouchUpDroid(float pX, float pY, int pIndex, int pCount) {
    InterfaceLock();
    gTouch.BaseTouchUpDroid(pX, pY, pIndex, pCount);
    InterfaceUnlock();
}

void FApp::BaseTouchCanceledDroid(float pX, float pY, int pIndex, int pCount) {
    InterfaceLock();
    gTouch.BaseTouchCanceledDroid(pX, pY, pIndex, pCount);
    InterfaceUnlock();
}

void FApp::BaseMouseDown(float pX, float pY, int pButton) {
    InterfaceLock();
    gTouch.BaseMouseDown(pX, pY, pButton);
    InterfaceUnlock();
}

void FApp::BaseMouseMove(float pX, float pY) {
    InterfaceLock();
    gTouch.BaseMouseMove(pX, pY);
    InterfaceUnlock();
}

void FApp::BaseMouseUp(float pX, float pY, int pButton) {
    InterfaceLock();
    gTouch.BaseMouseUp(pX, pY, pButton);
    InterfaceUnlock();
}

void FApp::BaseMouseWheel(int pDirection) {
    InterfaceLock();
    gTouch.BaseMouseWheel(pDirection);
    InterfaceUnlock();
}

void FApp::BaseKeyDown(int pKey) {
    if ((pKey >= 0) && (pKey < 256)) {
        InterfaceLock();
        gKeyPressed[pKey] = true;
        gTouch.EnqueueKeyDown(pKey);
        InterfaceUnlock();
    }
}

void FApp::BaseKeyUp(int pKey) {
    if ((pKey >= 0) && (pKey < 256)) {
        InterfaceLock();
        gKeyPressed[pKey] = false;
        gTouch.EnqueueKeyUp(pKey);
        InterfaceUnlock();
    }
}

void FApp::ProcessMouseDown(float pX, float pY, int pButton) {
    MouseDown(pX, pY, pButton);
    mSelectedCanvas = NULL;
    if (mWindowTools.MouseDown(pX, pY, pButton)) {
        mSelectedInputWindow = &mWindowTools;
        mSelectedCanvas = mWindowTools.mSelectedCanvas;
    } else if (mWindowModal.MouseDown(pX, pY, pButton)) {
        mSelectedInputWindow = &mWindowModal;
        mSelectedCanvas = mWindowModal.mSelectedCanvas;
    } else if (mWindowMain.MouseDown(pX, pY, pButton)) {
        mSelectedInputWindow = &mWindowMain;
        mSelectedCanvas = mWindowMain.mSelectedCanvas;
    } else {
        mSelectedInputWindow = 0;
    }
}

void FApp::ProcessMouseMove(float pX, float pY) {
    MouseMove(pX, pY);
    if (mSelectedInputWindow != 0) {
        mSelectedInputWindow->MouseMove(pX, pY);
    } else {
        if (mWindowTools.MouseMove(pX, pY)) {
        } else if (mWindowModal.MouseMove(pX, pY)) {
        } else if (mWindowMain.MouseMove(pX, pY)) { }
    }
}

void FApp::ProcessMouseUp(float pX, float pY, int pButton) {
    MouseUp(pX, pY, pButton);
    if (mSelectedInputWindow != 0) {
        mSelectedInputWindow->MouseUp(pX, pY, pButton);
    }
}

void FApp::ProcessMouseWheel(int pDir) {
    MouseWheel(pDir);
    mWindowTools.MouseWheel(pDir);
    mWindowModal.MouseWheel(pDir);
    mWindowMain.MouseWheel(pDir);
}

void FApp::ProcessTouchDown(float pX, float pY, void *pData) {
    if (mWindowTools.TouchDown(pX, pY, pData)) {
        mSelectedInputWindow = &mWindowTools;
    } else if (mWindowModal.TouchDown(pX, pY, pData)) {
        mSelectedInputWindow = &mWindowModal;
    } else if (mWindowMain.TouchDown(pX, pY, pData)) {
        mSelectedInputWindow = &mWindowMain;
    } else {
        mSelectedInputWindow = 0;
    }
    TouchDown(pX, pY, pData);
}

void FApp::ProcessTouchMove(float pX, float pY, void *pData) {
    mWindowTools.TouchMove(pX, pY, pData);
    mWindowModal.TouchMove(pX, pY, pData);
    mWindowMain.TouchMove(pX, pY, pData);
    TouchMove(pX, pY, pData);
}

void FApp::ProcessTouchUp(float pX, float pY, void *pData) {
    mTouchX = pX;
    mTouchY = pY;
    mWindowTools.TouchUp(pX, pY, pData);
    mWindowModal.TouchUp(pX, pY, pData);
    mWindowMain.TouchUp(pX, pY, pData);
    TouchUp(pX, pY, pData);
}

void FApp::ProcessTouchFlush() {
    mWindowMain.TouchFlush();
    mWindowModal.TouchFlush();
    mWindowTools.TouchFlush();
    TouchFlush();
}

void FApp::ProcessKeyDown(int pKey) {
    mWindowMain.KeyDown(pKey);
    mWindowModal.KeyDown(pKey);
    mWindowTools.KeyDown(pKey);
    KeyDown(pKey);
}

void FApp::ProcessKeyUp(int pKey) {
    mWindowMain.KeyUp(pKey);
    mWindowModal.KeyUp(pKey);
    mWindowTools.KeyUp(pKey);
    KeyUp(pKey);
}

void FApp::BaseInactive() {
    if (mActive == true) {
        mActive = false;
        ProcessTouchFlush();
        Inactive();
        
        InterfaceLock();
        gTouch.Inactive();
        InterfaceUnlock();
        
        mWindowMain.Inactive();
        mWindowModal.Inactive();
        mWindowTools.Inactive();
        
        sound_stopAll();
        sound_inactive();
        music_inactive();
        
        #if (CURRENT_ENV == ENV_ANDROID)
        //|| (CURRENT_ENV == ENV_IOS)
        Graphics::TearDown();
        #endif
        
    }
}

void FApp::BaseActive() {
    if(mActive == false) {
        mActive = true;
        Active();
        
        #if (CURRENT_ENV == ENV_ANDROID)
        //|| (CURRENT_ENV == ENV_IOS)
        mIsGraphicsSetUpEnqueued = true;
        mGraphicsSetUpEnqueuedTimer = 4;
        #endif
        
        InterfaceLock();
        gTouch.Active();
        InterfaceUnlock();
        
        mWindowMain.Active();
        mWindowModal.Active();
        mWindowTools.Active();
        
        sound_active();
        music_active();
    }
}

void FApp::BaseMemoryWarning(bool pSevere) {
    MemoryWarning(pSevere);
    mWindowMain.MemoryWarning(pSevere);
    mWindowModal.MemoryWarning(pSevere);
    mWindowTools.MemoryWarning(pSevere);
}

void FApp::BaseQuit() {
    Quit();
    mQuit = true;
}

void FApp::Quit() {
    
}

bool FApp::ShouldQuit() {
    return mQuit;
}

void FApp::BaseSetImageFileScale(int pScale) {
    mImageLoadScaleSuffix = FString("_scale_") + FString(gImageResolutionScale);
    SetImageFileScale(pScale);
}

static int clockCount = 0;
void FApp::ThrottleLock() {
    if (os_thread_lock_exists(mThrottleLock) == false) {
        mThrottleLock = os_create_thread_lock();
    }
    clockCount += 1;
    os_lock_thread(mThrottleLock);
}

void FApp::ThrottleUnlock() {
    os_unlock_thread(mThrottleLock);
}

void FApp::SystemLock() {
    if (os_thread_lock_exists(mSystemLock) == false) {
        mSystemLock = os_create_thread_lock();
    }
    os_lock_thread(mSystemLock);
}

void FApp::SystemUnlock() {
    os_unlock_thread(mSystemLock);
}

void FApp::InterfaceLock() {
    if (os_thread_lock_exists(mInterfaceLock) == false) {
        mInterfaceLock = os_create_thread_lock();
    }
    os_lock_thread(mInterfaceLock);
}

void FApp::InterfaceUnlock() {
    os_unlock_thread(mInterfaceLock);
}

void FApp::SystemProcess() {
    if (gGraphicsInterface) {
        SystemLock();
        gGraphicsInterface->PollEvents();
        SystemUnlock();
    }
}

void FApp::MainRunLoop() {
    
     while (gGraphicsInterface->IsReady() == false) {
         Log("Waiting for Graphics Module...\n");
         os_sleep(18);
     }
    
     while (!ShouldQuit()) {
         FrameController();
     }
}

void FApp::RecoverTime() {
    mFrame.mBaseUpdateTime = os_system_time();
    mFrame.mCurrentUpdateNumber = 0;
    mFrame.mBreakUpdate = true;
    mFrame.mDesiredUpdate = 0;
}

void FApp::FrameController() {

    ThrottleLock();
    
    if (mActive == false) {
        if (os_updates_in_background()) {
            
            /*
             if (mIdleWhenInBackground) {
             #ifndef AppRunsInThread
             OS_Core::Pump();
             #endif
             System_Process();
             if (mNeedBackgroundDraw)
             {
             ThrottleDraw();
             mNeedBackgroundDraw=false;
             }
             else OS_Core::Sleep(200);
             }
             */
            
        } else {
            SystemProcess();
            os_sleep(20);
            return;
        }
    }
    
    //
    // Frame controller for static number of updates/sec
    //
    {
        
        /////////////////////////////////////////////////////////////////
        //
        // Main control loop... calls Update() appropriately
        //
        /////////////////////////////////////////////////////////////////
        
        
        mFrame.mDesiredUpdate = (float)(os_system_time() - mFrame.mBaseUpdateTime);
        mFrame.mDesiredUpdate /= 10;
        mFrame.mDesiredUpdate *= (float)mUpdatesPerSecond / 100.0f;
        
        if (mFrame.mDesiredUpdate < mFrame.mCurrentUpdateNumber) {
            RecoverTime();
        }
        
        mFrame.mBreakUpdate=false;
        bool aShouldDraw = false;
        int aUpdateCheck = (int)mFrame.mDesiredUpdate - mFrame.mCurrentUpdateNumber;
        
        if (aUpdateCheck > 0) {
            
            while (mFrame.mCurrentUpdateNumber < (int)mFrame.mDesiredUpdate && !mFrame.mBreakUpdate) {
                aShouldDraw = true;
                
                SystemProcess();
                
                if (ShouldQuit()) {
                    break;
                }
                //
                // Process the actual update
                //
                mFrame.mCurrentUpdateNumber++;
                
                BaseUpdate();
            }
        }
    }
    
    
    ThrottleUnlock();
    
    
    
    //if ((mActive == false) && (true)) {
    //    RecoverTime();
    //}
    
    //if (mInBackground && mIdleWhenInBackground) RecoverTime();
    
}





int FApp::GetUPS() {
    int aResult = 100;
    if (mFrameCaptureUpdateCount > 2) {
        int aTimeDiff = (int)(mFrameCaptureUpdateTime[mFrameCaptureUpdateCount - 1] - mFrameCaptureUpdateTime[0]);
        float aSecondsEllapsed = ((float)aTimeDiff) / 1000.0f;
        if (aTimeDiff > 0) {
            aResult = (int)(((float)mFrameCaptureUpdateCount) / aSecondsEllapsed);
            
        }
    }
    return aResult;
}

int FApp::GetFPS() {
    int aResult = 60;
    if (mFrameCaptureDrawCount > 2) {
        int aTimeDiff = (int)(mFrameCaptureDrawTime[mFrameCaptureDrawCount - 1] - mFrameCaptureDrawTime[0]);
        float aSecondsEllapsed = ((float)aTimeDiff) / 1000.0f;
        if (aTimeDiff > 0) {
            aResult = (int)(((float)mFrameCaptureDrawCount) / aSecondsEllapsed);
            
        }
    }
    return aResult;
}


