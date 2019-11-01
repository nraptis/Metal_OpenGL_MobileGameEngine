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
    
   
    mUniformButterflyBody.mLight.mAmbientIntensity = 0.5f;
    mUniformButterflyBody.mLight.mDiffuseIntensity = 0.5f;
    mUniformButterflyBody.mLight.mDirX = -0.759005f;
    mUniformButterflyBody.mLight.mDirY = 0.372714f;
    mUniformButterflyBody.mLight.mDirZ = -0.533850f;
    
    
    mButterflyRotation = 0.0f;
    
    mButterflyFrame = 0.0f;
    
}

LandingScene::~LandingScene() {
    
    
}

void LandingScene::Layout() {
    
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    
}

void LandingScene::LayoutTransform() {
    
    mCamera.mAspect = gDeviceWidth / gDeviceHeight;
    
    mCamera.mDistance = (gDeviceHeight + gDeviceWidth) * 0.00125f;
    
    
    //We re-compute the center of our game window...
    float aAbsoluteCenterX = gAppBase->mWindowMain.mRoot.mX + gAppBase->mWindowMain.mRoot.mWidth2;
    float aAbsoluteCenterY = gAppBase->mWindowMain.mRoot.mY + gAppBase->mWindowMain.mRoot.mHeight2;
    mCamera.mCenterOffset = FVec2(gDeviceWidth2 - aAbsoluteCenterX, gDeviceHeight2 - aAbsoluteCenterY);
}

void LandingScene::Update() {
    
    mButterflyRotation += 1.0f;
    if (mButterflyRotation >= 360.0f) { mButterflyRotation -= 360.0f; }
    
    mButterflyFrame += 0.3f;
    if (mButterflyFrame >= gApp->mButterflyWingSequence.GetMaxFrame()) {
        mButterflyFrame -= gApp->mButterflyWingSequence.GetMaxFrame();
    }
    
    
}

void LandingScene::Draw() {
    
}

void LandingScene::Draw3D() {

    
    Graphics::SetColor();
    Graphics::CullFacesSetDisabled();
    Graphics::DepthEnable();
    
    
    
    FMatrix aProjection = mCamera.GetProjection();
    
    Graphics::PipelineStateSetModelIndexedAlphaBlending();
    
    FModelDataPacked *aModelBody = gApp->mButterflyBodySequence.GetModel(mButterflyFrame);
    if (aModelBody != NULL) {
        
        Graphics::PipelineStateSetModelIndexedLightedDiffuseNoBlending();
        
        FMatrix aModelView;
        aModelView.RotateX(-90.0f);
        aModelView.RotateY(180.0f);
        aModelView.RotateZ(mButterflyRotation);
        
        FMatrix aNormal;
        aNormal.SetNormalMatrix(aModelView);
        
        mUniformButterflyBody.mProjection.Set(aProjection);
        mUniformButterflyBody.mModelView.Set(aModelView);
        mUniformButterflyBody.mNormal.Set(aNormal);
        
        Graphics::UniformBind(&mUniformButterflyBody);
        Graphics::DrawTrianglesIndexedWithPackedBuffers(aModelBody->mBuffer, 0,
                                                        gApp->mButterflyBodySequence.mIndex, gApp->mButterflyBodySequence.mIndexCount,
                                                        gApp->mButterflyMap.mTexture);
    }
    
    
    
    FModelDataPacked *aModelWings = gApp->mButterflyWingSequence.GetModel(mButterflyFrame);
    if (aModelWings != NULL) {
        
        Graphics::PipelineStateSetModelIndexedAlphaBlending();
        
        FMatrix aModelView;
        aModelView.RotateX(-90.0f);
        aModelView.RotateY(180.0f);
        aModelView.RotateZ(mButterflyRotation);
        
        Graphics::MatrixProjectionSet(aProjection);
        Graphics::MatrixModelViewSet(aModelView);
        
        Graphics::UniformBind();
        Graphics::DrawTrianglesIndexedWithPackedBuffers(aModelWings->mBuffer, 0,
                                                        gApp->mButterflyWingSequence.mIndex, gApp->mButterflyWingSequence.mIndexCount,
                                                        gApp->mButterflyMap.mTexture);
    }
    
    Graphics::CullFacesSetBack();
    Graphics::DepthDisable();
    
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
