//
//  LandingScene.hpp
//  Mac
//
//  Created by Nick Raptis on 10/27/19.
//  Copyright © 2019 Nick Raptis. All rights reserved.
//

#ifndef LandingScene_hpp
#define LandingScene_hpp

#include "GFXApp.hpp"
#include "FloatingCamera.hpp"

class LandingScene : public FCanvas {
public:
    LandingScene();
    virtual ~LandingScene();
    
    virtual void                                Layout() override;
    virtual void                                LayoutTransform() override;
    
    virtual void                                Update() override;
    virtual void                                Draw() override;
    void                                        Draw3D();
    
    virtual void                                TouchDown(float pX, float pY, void *pData) override;
    virtual void                                TouchMove(float pX, float pY, void *pData) override;
    virtual void                                TouchUp(float pX, float pY, void *pData) override;
    virtual void                                TouchFlush() override;
    
    virtual void                                KeyDown(int pKey) override;
    virtual void                                KeyUp(int pKey) override;
    
    virtual void                                Notify(void *pSender, const char *pNotification) override;
    
    
    FUniformsLightDiffuse                       mUniformButterflyBody;
    FloatingCamera                              mCamera;
    
    float                                       mButterflyFrame;
    
    float                                       mButterflyRotation;
    
    
};

#endif
