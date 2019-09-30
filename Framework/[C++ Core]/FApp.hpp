#ifndef FRAMEWORK_APP_H
#define FRAMEWORK_APP_H

#include "core_includes.h"
#include "FFont.hpp"

#define FRAME_TIME_CAPTURE_COUNT 200

class PlatformGraphicsInterface;


class FApp
{
public:

    FApp();
    virtual ~FApp();

protected:
    bool                                        mDidInitialize;
    
    bool                                        mDidDetachFrameController;
    bool                                        mDidUpdate;
    
public:
    
    virtual void                                Initialize() { }
    
    virtual void                                SetDeviceSize(int pWidth, int pHeight) { }
    
	virtual void                                SetVirtualFrame(int pX, int pY, int pWidth, int pHeight) { }
    virtual void                                SetSafeAreaInsets(int pInsetUp, int pInsetRight, int pInsetDown, int pInsetLeft) { }
    
    virtual void                                Load() {}
    virtual void                                LoadComplete() {}

    virtual void                                Update() {}
    virtual void                                Draw() {}
    virtual void                                DrawOver() {}
    
    virtual void                                Prerender() { }
    virtual void                                Postrender() { }
    
    virtual void                                TouchDown(float pX, float pY, void *pData) { }
    virtual void                                TouchMove(float pX, float pY, void *pData) { }
    virtual void                                TouchUp(float pX, float pY, void *pData) { }
    virtual void                                TouchFlush() { }
    virtual void                                MouseDown(float pX, float pY, int pButton);
    virtual void                                MouseMove(float pX, float pY);
    virtual void                                MouseUp(float pX, float pY, int pButton);
    virtual void                                MouseWheel(int pDirection);

    virtual void                                KeyDown(int pKey);
    virtual void                                KeyUp(int pKey);

    virtual void                                Inactive(){}
    virtual void                                Active(){}

    virtual void                                MemoryWarning(bool pSevere) { }
    virtual void                                SetImageFileScale(int pScale) { }
    
    bool                                        mActive;
    
    FWindow                                     mWindowMain;
    FWindow                                     mWindowModal;
    FWindow                                     mWindowTools;
    FWindow                                     *mSelectedInputWindow;
    FCanvas                                     *mSelectedCanvas;
    
    int                                         mTimeSinceLastInteraction;
    
    FFont                                       mSysFont;
    FFont                                       mSysFontBold;
    
    float                                       mTouchX;
    float                                       mTouchY;

    FList                                       mImageLoadDirectoryList;
    FList                                       mImageLoadExtensionList;
    FList                                       mImageLoadSuffixList;
    FList                                       mImageLoadMutableSuffixList;
    
    FString                                     mImageLoadScaleSuffix;

    void                                        ProcessMouseDown(float pX, float pY, int pButton);
    void                                        ProcessMouseMove(float pX, float pY);
    void                                        ProcessMouseUp(float pX, float pY, int pButton);
    void                                        ProcessMouseWheel(int pDir);
    void                                        ProcessTouchDown(float pX, float pY, void *pData);
    void                                        ProcessTouchMove(float pX, float pY, void *pData);
    void                                        ProcessTouchUp(float pX, float pY, void *pData);
    void                                        ProcessTouchFlush();
    void                                        ProcessKeyDown(int pKey);
    void                                        ProcessKeyUp(int pKey);

    void                                        BaseLoad();
    
    //mFrameController.Active();
    
    //Externally, we are getting a "frame" ...
    void                                        BaseFrame();
    
    void                                        BaseUpdate();
    void                                        BaseDraw();
    void                                        BaseSetDeviceSize(int pWidth, int pHeight);
    void                                        BaseSetVirtualFrame(int pX, int pY, int pWidth, int pHeight);
    void                                        BaseSetSafeAreaInsets(int pInsetUp, int pInsetRight, int pInsetDown, int pInsetLeft);
    
    void                                        BaseInitialize();
    void                                        BaseLoadComplete();
    void                                        BaseActive();
    void                                        BaseInactive();
    void                                        BaseMemoryWarning(bool pSevere);
    void                                        BaseSetImageFileScale(int pScale);
    
    void                                        BaseKeyDown(int pKey);
    void                                        BaseKeyUp(int pKey);
    void                                        BaseTouchDown(float pX, float pY, void *pData);
    void                                        BaseTouchMove(float pX, float pY, void *pData);
    void                                        BaseTouchUp(float pX, float pY, void *pData);
    void                                        BaseTouchCanceled(float pX, float pY, void *pData);
    void                                        BaseTouchDownDroid(float pX, float pY, int pIndex, int pCount);
    void                                        BaseTouchMoveDroid(float pX, float pY, int pIndex, int pCount);
    void                                        BaseTouchUpDroid(float pX, float pY, int pIndex, int pCount);
    void                                        BaseTouchCanceledDroid(float pX, float pY, int pIndex, int pCount);
    void                                        BaseMouseDown(float pX, float pY, int pButton);
    void                                        BaseMouseMove(float pX, float pY);
    void                                        BaseMouseUp(float pX, float pY, int pButton);
    void                                        BaseMouseWheel(int pDirection);
    
    void                                        MainRunLoop();
    
    void                                        BaseQuit();
    virtual void                                Quit();
    bool                                        ShouldQuit();
    bool                                        mQuit;
    
    void                                        FrameController();
    
    
    int                                         mSystemLock;
    void                                        SystemLock();
    void                                        SystemUnlock();
    void                                        SystemProcess();
    
    
    int                                         mInterfaceLock;
    void                                        InterfaceLock();
    void                                        InterfaceUnlock();
    
    
    int                                         mThrottleLock;
    void                                        ThrottleLock();
    void                                        ThrottleUnlock();
    
    bool                                        mIsLoading;
    bool                                        mIsLoadingComplete;
    
    bool                                        mDarkMode;
    
    //void os_execute_on_main_thread(void (*pFunc)());
    
    //
    // Control stuff...
    //
    
    bool                                        mDidInitializeGraphicsInterface;
    
    bool                                        mIsGraphicsSetUpEnqueued;
    int                                         mGraphicsSetUpEnqueuedTimer;
    
    
    float                                       mUpdatesPerSecond;
    
    void                                        RecoverTime();
    
    struct Frame {
        unsigned int                            mBaseUpdateTime;
        int                                     mCurrentUpdateNumber;
        bool                                    mBreakUpdate;
        float                                   mDesiredUpdate;
    }                                           mFrame;
    
    int                                         GetUPS();
    int                                         GetFPS();
    
    
    int                                         mFrameCaptureUpdateCount;
    int                                         mFrameCaptureUpdateTime[FRAME_TIME_CAPTURE_COUNT];
    
    int                                         mFrameCaptureDrawCount;
    int                                         mFrameCaptureDrawTime[FRAME_TIME_CAPTURE_COUNT];
    
    
};

extern FApp *gAppBase;
extern PlatformGraphicsInterface *gGraphicsInterface;

#endif
