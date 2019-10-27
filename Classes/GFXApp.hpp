//
//  GFXApp.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/29/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef GFXApp_hpp
#define GFXApp_hpp

#include "FApp.hpp"

class LandingScene;
class Util_ScreenFrame;
class GFXApp : public FApp {
public:
    GFXApp();
    virtual ~GFXApp();
    
    virtual void                            Update() override;
    virtual void                            Draw() override;
    virtual void                            DrawLoading() override;
    
    virtual void                            Load() override;
    virtual void                            Unload() override;
    virtual void                            LoadComplete() override;
    
    virtual void                            SetVirtualFrame(int pX, int pY, int pWidth, int pHeight) override;
    virtual void                            SetDeviceSize(int pWidth, int pHeight) override;
    
    virtual void                            MouseWheel(int pDirection) override;
    virtual void                            KeyDown(int pKey) override;
    virtual void                            KeyUp(int pKey) override;
    
    virtual void                            TouchDown(float pX, float pY, void *pData) override;
    virtual void                            TouchMove(float pX, float pY, void *pData) override;
    virtual void                            TouchUp(float pX, float pY, void *pData) override;
    virtual void                            TouchFlush() override;
    
    virtual void                            Inactive() override;
    virtual void                            Active() override;
    
    virtual void                            ExecuteWadReload() override;
    
    LandingScene                            *mLandingScene;
    Util_ScreenFrame                        *mScreenTool;
    
    
    
    FModelDataPackedSequence                mButterflyBodySequence;
    FModelDataPackedSequence                mButterflyWingSequence;
    FSprite                                 mButterflyMap;
    
    
};

extern GFXApp *gApp;

#endif /* GFXApp_hpp */
