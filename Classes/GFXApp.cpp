//
//  GFXApp.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/29/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

//#include "MetalEngine.h"

//1.) Get main menu flow / memory leaks cleaned up.
//2.) Add prize box EVERYWHERE (all buttons, loops, etc - before it gets out of hand...)

#include "core_app_shell.hpp"
#include "GFXApp.hpp"
#include "Util_ScreenFrame.h"
#include "LandingScene.hpp"

GFXApp *gApp = 0;
GFXApp::GFXApp() {
    
    gApp = this;
    mLandingScene = NULL;
    mScreenTool = NULL;
    
}

GFXApp::~GFXApp() {
    
}

void GFXApp::Load() {
    
    Log("GFXApp::Load()\n");
    
    
    
}

void GFXApp::Unload() {
    
    
}

void GFXApp::LoadComplete() {
    
    Log("GFXApp::LoadComplete()\n");
    
    
    if (mLandingScene == NULL) {
        mLandingScene = new LandingScene();
        mWindowMain.AddChild(mLandingScene);
    }
    
    
    if (mScreenTool == NULL) {
        mScreenTool = new Util_ScreenFrame();
        mScreenTool->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
        mScreenTool->RefreshVirtualFrame();
        mWindowTools.AddChild(mScreenTool);
    }
    
}

void GFXApp::Update() {
    
    
    
    
}

void GFXApp::DrawLoading() {
    Graphics::Clear(0.25f, 0.35f, 0.75f);
    Graphics::RenderPassBegin(GFX_RENDER_PASS_3D_MAIN,
                              true, //Clear Color
                              true); //Clear Depth
    Graphics::RenderPassBegin(GFX_RENDER_PASS_2D_MAIN,
                              false, //Clear Color
                              false); //Clear Depth
    
    
}

void GFXApp::Draw() {
    
    Graphics::RenderPassBegin(GFX_RENDER_PASS_3D_MAIN,
                              true, //Clear Color
                              true); //Clear Depth
    
    if (mLandingScene != NULL) { mLandingScene->Draw3D(); }
    
    Graphics::RenderPassBegin(GFX_RENDER_PASS_2D_MAIN,
                              false, //Clear Color
                              false); //Clear Depth
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    
    

}

void GFXApp::SetVirtualFrame(int pX, int pY, int pWidth, int pHeight) {
    
}

void GFXApp::TouchDown(float pX, float pY, void *pData) {
    
}

void GFXApp::TouchMove(float pX, float pY, void *pData) {
    
    
}

void GFXApp::TouchUp(float pX, float pY, void *pData) {
    
}

void GFXApp::TouchFlush() {
    
}

void GFXApp::MouseWheel(int pDirection) {
    
}

void GFXApp::KeyDown(int pKey) {
    
}

void GFXApp::KeyUp(int pKey) {
    
}

void GFXApp::SetDeviceSize(int pWidth, int pHeight) {
    
    //This is for our test app, to go to iPad resolution by default.
    
    static int aFixRez = 0;
    
    float aTop = gSafeAreaInsetTop + 20.0f;
    float aBottom = pHeight - (gSafeAreaInsetBottom + 20.0f);
    
    float aHeight = (aBottom - aTop);
    float aWidth = aHeight * 0.75f;
    
    if (aFixRez < 2) {
        aFixRez++;
        float aMaxWidth = (int)(pHeight * 0.75f + 0.5f);
        if (pWidth > aMaxWidth) {
            AppShellSetVirtualFrame(pWidth / 2.0f - aWidth / 2.0f, aTop, aWidth, aHeight);
        }
    }
    
}

void GFXApp::Inactive() {
    
}

void GFXApp::Active() {
    
}

void GFXApp::ExecuteWadReload() {
    
    Log("*** BEGIN:: GFXApp::ExecuteWadReload()\n");
    
    Log("*** End:: GFXApp::ExecuteWadReload()\n");
}
