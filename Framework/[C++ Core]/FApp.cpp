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
#include "FAssetResolutionConfigurator.hpp"

FApp *gAppBase = NULL;
PlatformGraphicsInterface *gGraphicsInterface = NULL;

FApp::FApp() {
    gAppBase = this;
    
    mFrameCaptureUpdateCount = 0;

    mDidUnload = false;
    
    mFrameCaptureDrawCount = 0;
    mSelectedCanvas = NULL;
    
    mDarkMode = false;
    
    mThrottleMode = -1;
    
    mAssetResolutionConfigurator = NULL;
    mWadReloadIsEnqueued = false;
    mWadReloadOnNextFrame = false;
    
    mDidInitialize = false;
    mDidDetachFrameController = false;
    mDidUpdate = false;
    mActive = true;
    
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

void AppFrameThread(void *pArgs) {
    if (gAppBase != NULL) {
        gAppBase->MainRunLoop();
    }
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
        
        Initialize();

        if (mDidDetachFrameController == false) {
            mDidDetachFrameController = true;
            os_detach_thread(AppFrameThread, (void*)0xB00BFACE);
        }
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
    
    ReevaluateScreenResolution();
}

void FApp::BaseSetVirtualFrame(int pX, int pY, int pWidth, int pHeight) {
    
    mWindowMain.SetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    mWindowModal.SetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    mWindowTools.SetVirtualFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    SetVirtualFrame(pX, pY, pWidth, pHeight);
    
    ReevaluateScreenResolution();
}

void FApp::BaseSetSafeAreaInsets(int pInsetUp, int pInsetRight, int pInsetDown, int pInsetLeft) {
    
    mWindowMain.SetSafeAreaInsets(gSafeAreaInsetTop + 0.5f, gSafeAreaInsetRight + 0.5f, gSafeAreaInsetBottom + 0.5f, gSafeAreaInsetLeft + 0.5f);
    mWindowModal.SetSafeAreaInsets(gSafeAreaInsetTop + 0.5f, gSafeAreaInsetRight + 0.5f, gSafeAreaInsetBottom + 0.5f, gSafeAreaInsetLeft + 0.5f);
    mWindowTools.SetSafeAreaInsets(gSafeAreaInsetTop + 0.5f, gSafeAreaInsetRight + 0.5f, gSafeAreaInsetBottom + 0.5f, gSafeAreaInsetLeft + 0.5f);
    
    SetSafeAreaInsets(pInsetUp, pInsetRight, pInsetDown, pInsetLeft);
    
    ReevaluateScreenResolution();
}

//Externally, we are getting a "frame" ...
void FApp::BaseFrame() {

    if (mActive == false) {
        Log("Attempting to draw when APP INACTIVE...\n");
        return;
    }

    if (gGraphicsInterface == NULL) {
        Log("BASE FRAME... gGraphicsInterface == NULL!!!\n\n");
    }
    
    if (mDidInitialize == false) {
        Log("Waiting for An Initialize...\n");
        
        ThrottleLock();
        BaseInitialize();
        ThrottleUnlock();
    }
    
    //if (mDidInitialize == false) {
    //    Log("BASE FRAME... mDidInitialize == false!!!\n\n");
    //    ThrottleLock();
    //    BaseInitialize();
    //    ThrottleUnlock();
    //}
    
    gBufferCache.Reset();
    
    while (mDidUpdate == false) {
        Log("Waiting for An Update...\n");
        os_sleep(40);
    }

    while (mThrottleMode == 1) {
        //Don't draw again until we pass through the update cycle... Older iOS devices
        //seem to re-lock inunpredictable order and one thread can starve...
        os_sleep(5);
    }

    ThrottleLock();
    mThrottleMode = 1;

    if (gGraphicsInterface != NULL) {
        gGraphicsInterface->SetContext();
        gGraphicsInterface->Prerender();
    }
    
    Graphics::PreRender();
    gAppBase->Prerender();
    
    if (mWadReloadIsEnqueued) {
        if (mWadReloadOnNextFrame) {
            mWadReloadIsEnqueued = false;
            mWadReloadOnNextFrame = false;
            
            BaseExecuteWadReload();
            
            mWindowMain.RefreshAll();
            mWindowModal.RefreshAll();
            mWindowTools.RefreshAll();
        }
    }
    
    if ((mIsLoading == true) || (mDidUnload == true) || (mIsLoadingComplete == false)) {
        Graphics::Clear(0.66f, 0.66f, 0.66f);
        BaseDrawLoading();
    } else {
        BaseDraw();
    }
    
    gAppBase->Postrender();
    Graphics::PostRender();
    
    if (gGraphicsInterface != NULL) {
        gGraphicsInterface->Postrender();
        gGraphicsInterface->Commit();
    }
    
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

void FApp::BaseDrawLoading() {
    
    if (mActive == false) { return; }
    DrawLoading();
}


void FApp::BaseDraw() {
    
    if (mActive == false) { return; }



    
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
    
    //if ((mIsLoading == false) && (mIsLoadingComplete == true)) {
    mWindowMain.Draw();
    mWindowModal.Draw();
    mWindowTools.Draw();
    //}
    
    Graphics::MatrixProjectionSet(aOrtho);
    Graphics::MatrixModelViewReset();
    
    
    /*
    if (Graphics::RenderPass() == GFX_RENDER_PASS_2D_MAIN) {
        Graphics::MatrixProjectionResetOrtho();
        Graphics::MatrixModelViewReset();
        Graphics::SetColor();
        Graphics::PipelineStateSetSpritePremultipliedBlending();
        
        FString aResString = FString("HW: ") + FString(gDeviceWidth, 1) + FString("x") + FString(gDeviceHeight, 1) + FString(", VD: ") + FString(gVirtualDevWidth, 1) + FString("x") + FString(gVirtualDevHeight, 1);
        mSysFont.Center(aResString, gDeviceWidth2, gDeviceHeight - 80.0f - 20.0f);
        
        FString aFPSString = FString("FPS: ") + FString(GetFPS()) + FString(", ") + FString("UPS: ") + FString(GetUPS());
        mSysFont.Center(aFPSString, gDeviceWidth2, gDeviceHeight - 52.0f - 20.0f);
        
        FString aScaleString = FString("SCL: ") + FString(gSpriteDrawScale) + FString(", ") + FString("REZ: ") + FString(gImageResolutionScale);
        mSysFont.Center(aScaleString, gDeviceWidth2, gDeviceHeight - 24.0f - 20.0f);
    }
    */
    
    if (mDarkMode == true) {
        Graphics::PipelineStateSetShape2DAlphaBlending();
        
#if (CURRENT_ENV == ENV_IOS)
        Graphics::SetColor(0.0075f, 0.0075f, 0.0075f, 0.785f);
#else
        Graphics::SetColor(0.0075f, 0.0075f, 0.0075f, 0.825f);
#endif
        
        Graphics::DrawRect(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
        Graphics::SetColor();
    }
}

void FApp::BaseLoad() {
    
    if (gGraphicsInterface != NULL) {
        gGraphicsInterface->SetContext();
    }

    if (mDidInitialize == false) {
        BaseInitialize();
    }

    mIsLoading = true;
    mDidUnload = false;
    
    BaseSetDeviceSize(gDeviceWidth, gDeviceHeight);
    BaseSetVirtualFrame(gVirtualDevX, gVirtualDevY, gVirtualDevWidth, gVirtualDevHeight);
    BaseSetSafeAreaInsets(gSafeAreaInsetTop, gSafeAreaInsetRight, gSafeAreaInsetBottom, gSafeAreaInsetLeft);
    
    AppShellSetImageFileScale(1);
    AppShellSetSpriteDrawScale(1.0f);
    
    
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
    
    mSysFontBold.mDataScale = 0.125f;
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
    
    mSysFont.mDataScale = 0.125f;
    mSysFont.ApplyExpand(14.0f);
    mSysFont.SetSpaceWidth(64.0f);
    
    if (mAssetResolutionConfigurator == NULL) { mAssetResolutionConfigurator = GetAssetResolutionConfigurator(); }
    
    mAssetResolutionConfigurator->Invalidate();
    
    //Seems odd.. We want to FORCE the re-check of changing screen size. This is mainly to accomodate dynamic screen sizing...
    mAssetResolutionConfigurator->NotifyScreenPropertiesChanged();
    BaseExecuteWadReload();
    
    Load();
    
    mWindowMain.RefreshAll();
    mWindowModal.RefreshAll();
    mWindowTools.RefreshAll();
}

void FApp::BaseLoadComplete() {
    ThrottleLock();
    mIsLoading = false;
    mIsLoadingComplete = true;
    mDidUnload = false;
    LoadComplete();
    ThrottleUnlock();
}

void FApp::BaseUnload() {
    
    mDidUnload = true;
    mIsLoadingComplete = false;
    
    mSysFont.Kill();
    mSysFontBold.Kill();
    
    Unload();
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

        //TODO: Remove, once verified on old Android.
    #if (CURRENT_ENV == ENV_ANDROID)
        
        //Log("**** Teardown Graphics [Graphics::TearDown()] ****\n");
        //ThrottleLock();
        //BaseUnload();
        //Graphics::TearDown();
        //ThrottleUnlock();
        
    #endif
        
    }
}

void FApp::BaseActive() {
    if(mActive == false) {
        
        mActive = true;
        Active();
        
        //TODO: Remove, once verified on old Android.
        //#if (CURRENT_ENV == ENV_ANDROID) || (CURRENT_ENV == ENV_IOS)
        //if (mDidUnload == true) {
        //    mIsGraphicsSetUpEnqueued = true;
        //    mGraphicsSetUpEnqueuedTimer = 1;
        //}
        //#endif
        
        InterfaceLock();
        gTouch.Active();
        InterfaceUnlock();
        
        mWindowMain.Active();
        mWindowModal.Active();
        mWindowTools.Active();
        
        music_active();
        sound_active();
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

void FApp::BaseExecuteWadReload() {
    
    DequeueWadReload();
    
    if (mAssetResolutionConfigurator == NULL) {
        mAssetResolutionConfigurator = GetAssetResolutionConfigurator();
    }
    
    if ((mIsLoading == false) && (mIsLoadingComplete == false)) {
        //We haven't loaded, we haven't started loading...
        mAssetResolutionConfigurator->Invalidate();
        return;
    }
    
    if (mAssetResolutionConfigurator->ShouldReload() == false) {
        return;
    }
    
    //We pick these scales...
    AppShellSetImageFileScale(mAssetResolutionConfigurator->mAssetScale);
    AppShellSetSpriteDrawScale(mAssetResolutionConfigurator->mSpriteScale);
    
    //Talk to the configurator...
    mAssetResolutionConfigurator->NotifyReload();
    
    ExecuteWadReload();
    
}

void FApp::EnqueueWadReload() {
    mWadReloadIsEnqueued = true;
    mWadReloadOnNextFrame = true;
}

void FApp::DequeueWadReload() {
    mWadReloadIsEnqueued = false;
    mWadReloadOnNextFrame = false;
}

void FApp::ReevaluateScreenResolution() {
    if (mAssetResolutionConfigurator == NULL) {
        mAssetResolutionConfigurator = GetAssetResolutionConfigurator();
    }
    if (mIsLoadingComplete) {
        mAssetResolutionConfigurator->NotifyScreenPropertiesChanged();
        EnqueueWadReload();
    }
}

FAssetResolutionConfigurator *FApp::GetAssetResolutionConfigurator() {
    FAssetResolutionConfigurator *aResult = new FAssetResolutionConfigurator();
    return aResult;
}

void FApp::BaseSetImageFileScale(int pScale) {
    mImageLoadScaleSuffix = FString("_scale_") + FString(gImageResolutionScale);
    SetImageFileScale(pScale);
}

void FApp::ThrottleLock() {
    if (os_thread_lock_exists(mThrottleLock) == false) {
        mThrottleLock = os_create_thread_lock();
    }
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
    /*
    if (gGraphicsInterface) {
        SystemLock();
        gGraphicsInterface->PollEvents();
        SystemUnlock();
    }
    */
}

void FApp::MainRunLoop() {
    while (mQuit == false) {
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
    
    while (mThrottleMode == 0) {
        //Don't draw again until we pass through the update cycle... Older iOS devices
        //seem to re-lock in unpredictable order and one thread can starve...
        os_sleep(5);
    }

    ThrottleLock();
    mThrottleMode = 0;
    
    if (mActive == false) {
        if (os_updates_in_background()) {
            os_sleep(200);
        } else {
            SystemProcess();
            os_sleep(20);
            return;
        }
    }
    
    mFrame.mDesiredUpdate = (float)(os_system_time() - mFrame.mBaseUpdateTime);
    mFrame.mDesiredUpdate /= 10;
    mFrame.mDesiredUpdate *= (float)mUpdatesPerSecond / 100.0f;
    
    if (mFrame.mDesiredUpdate < mFrame.mCurrentUpdateNumber) {
        RecoverTime();
    }
    
    mFrame.mBreakUpdate = false;
    int aUpdateCheck = (int)mFrame.mDesiredUpdate - mFrame.mCurrentUpdateNumber;
    
    if (aUpdateCheck > 0) {
        if ((aUpdateCheck > 80) || (mActive == false)) {
            if (!mFrame.mBreakUpdate) {
                SystemProcess();
                if (!mQuit) {
                    mFrame.mCurrentUpdateNumber = mFrame.mDesiredUpdate;
                    BaseUpdate();
                }
                
            }
        } else {
            while (mFrame.mCurrentUpdateNumber < (int)mFrame.mDesiredUpdate && !mFrame.mBreakUpdate) {
                
                SystemProcess();
                if (mQuit == true) { break; }
                mFrame.mCurrentUpdateNumber++;
                BaseUpdate();
            }
        }
    }
    ThrottleUnlock();
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


