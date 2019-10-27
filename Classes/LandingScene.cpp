//
//  LandingScene.cpp
//  Mac
//
//  Created by Nick Raptis on 10/27/19.
//  Copyright © 2019 Nick Raptis. All rights reserved.
//

#include "core_includes.h"
#include "LandingScene.hpp"

LandingScene::LandingScene() {
    
    mName = "LandingScene";
    
    mRecievesOutsideTouches = true;
    
   
    
}

LandingScene::~LandingScene() {
    
    
}

void LandingScene::Layout() {
    
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    
}

void LandingScene::Update() {
    
    
    
}

void LandingScene::Draw() {
    
}

void LandingScene::Draw3D() {

    
    
}

void LandingScene::TouchDown(float pX, float pY, void *pData) {
    
    
    
}

void LandingScene::TouchMove(float pX, float pY, void *pData) {
    
}

void LandingScene::TouchUp(float pX, float pY, void *pData) {
    
}

void LandingScene::TouchFlush() {
    
}

void LandingScene::KeyDown(int pKey) {
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;

    
}

void LandingScene::KeyUp(int pKey) {
    
}

void LandingScene::Notify(void *pSender, const char *pNotification) {
    
}
