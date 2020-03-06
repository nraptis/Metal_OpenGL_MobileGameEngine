//
//  Util_SpritePoints.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 2/28/20.
//  Copyright © 2020 Froggy Studios. All rights reserved.
//

#include "Util_SpritePoints.hpp"
#include "core_includes.h"
#include "core_app_shell.hpp"
#include "FApp.hpp"

Util_SpritePoints::Util_SpritePoints() {
    mConsumesTouches = false;
    mRecievesOutsideTouches = true;
    mRecievesConsumedTouches = true;
    mClipEnabled = false;
    SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    mSprite = NULL;
    mSpriteIndex = -1;
    
    mCenterX = gDeviceWidth2;
    mCenterY = gDeviceHeight2;
    
    mMode = 0;
    mSelectedPoint = -1;
    
}

Util_SpritePoints::~Util_SpritePoints() {
    
}

void Util_SpritePoints::Layout() {
    
}

void Util_SpritePoints::Update() {
    
}

void Util_SpritePoints::Draw() {
    
    Graphics::PipelineStateSetShape2DNoBlending();
    Graphics::SetColor(0.125f, 0.125f, 0.125f, 1.0f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    if (mSprite != NULL) {
        
        Graphics::PipelineStateSetSpriteAdditiveBlending();
        Graphics::SetColor();
        mSprite->Center(mCenterX, mCenterY);
        
        
    }
    
    Graphics::PipelineStateSetShape2DNoBlending();
    for (int i=0;i<mPointList.mCount;i++) {
    
        float aX = mPointList.mX[i];
        float aY = mPointList.mY[i];
        Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.85f);
        Graphics::DrawPoint(aX, aY, 6.0f);
        
        Graphics::SetColorSwatch(i);
        Graphics::DrawPoint(aX, aY, 4.0f);
        
        Graphics::SetColor(0.0f, 0.0f, 0.0f);
        Graphics::DrawPoint(aX, aY, 2.0f);
    }
    
    
    
    
}

void Util_SpritePoints::TouchDown(float pX, float pY, void *pData) {
    
    mPointList.Add(pX, pY);
    Print();
}

void Util_SpritePoints::TouchMove(float pX, float pY, void *pData) {
    
}

void Util_SpritePoints::TouchUp(float pX, float pY, void *pData) {
    
}

void Util_SpritePoints::SetSprite(FSprite *pSprite) {
    AddSprite(pSprite);
}

void Util_SpritePoints::AddSprite(FSprite *pSprite) {
    
    if (pSprite == NULL) {
        return;
    }
    
    if (pSprite->DidLoad() == false) {
        return;
    }
    
    if (mSprite == NULL) {
        mSpriteIndex = 0;
        mSprite = pSprite;
    }
    
    mSpriteList.Add(pSprite);
    
}

void Util_SpritePoints::ClearPoints() {
    
}

void Util_SpritePoints::Print() {
    
    if (mSprite != NULL) {
        
        float aWidth = mSprite->mWidth;
        float aHeight = mSprite->mHeight;
        
        if ((aWidth > 4.0f) && (aHeight > 4.0f)) {
            
            printf("Points for [%s]\n", mSprite->mFileName.c());
            for (int i=0;i<mPointList.mCount;i++) {
                
                float aX = mPointList.mX[i];
                float aY = mPointList.mY[i];
                
                float aDiffX = aX - mCenterX;
                float aDiffY = aY - mCenterY;
                
                printf("Diff[%d] = (%.2ff, %.2ff);\n", i, aDiffX, aDiffY);
                
                
            }
            
            for (int i=0;i<mPointList.mCount;i++) {
                
                float aX = mPointList.mX[i];
                float aY = mPointList.mY[i];
                
                float aDiffX = aX - mCenterX;
                float aDiffY = aY - mCenterY;
                
                float aPercentX = aDiffX / (aWidth / 2.0f);
                float aPercentY = aDiffY / (aHeight / 2.0f);
                
                
                
                
                printf("Perc[%d] = (%.4ff, %.4ff);\n", i, aPercentX, aPercentY);
                
                
            }
            
            
            
            
        }
    }
}

//L1
//Perc[0] = (-0.5854f, -0.8553f);
//Perc[1] = (-0.1583f, -0.7886f);
//Perc[2] = (-0.4038f, -0.5907f);
//Perc[3] = (-0.2385f, -0.2016f);
//Perc[4] = (-0.6248f, 0.2172f);
//Perc[5] = (-0.3891f, 0.6634f);
//Perc[6] = (0.6085f, 0.4881f);
//Perc[7] = (0.2179f, 0.6991f);

//E1

//Perc[0] = (0.6812f, -0.8456f);
//Perc[1] = (0.3527f, -0.0731f);
//Perc[2] = (0.7669f, 0.6540f);
//Perc[3] = (-0.6234f, -0.8194f);
//Perc[4] = (0.0609f, -0.8467f);
//Perc[5] = (-0.3872f, -0.2609f);
//Perc[6] = (-0.1652f, 0.5024f);
//Perc[7] = (-0.1917f, 0.1689f);
//Perc[8] = (-0.4853f, 0.5781f);
//Perc[9] = (0.3144f, 0.7034f);
//Perc[10] = (-0.0702f, -0.5864f);


//V
//Perc[0] = (0.5015f, -0.8346f);
//Perc[1] = (0.7634f, -0.8410f);
//Perc[2] = (0.6371f, -0.5598f);
//Perc[3] = (0.2932f, 0.1791f);
//Perc[4] = (-0.0210f, 0.3181f);
//Perc[5] = (0.2844f, 0.6938f);
//Perc[6] = (-0.2920f, -0.7331f);
//Perc[7] = (-0.6622f, -0.7780f);
//Perc[8] = (-0.3928f, -0.3011f);
//Perc[9] = (-0.3472f, 0.1522f);
//Perc[10] = (0.3845f, -0.2832f);

//E2
//Perc[0] = (0.3803f, -0.8681f);
//Perc[1] = (-0.0275f, -0.6676f);
//Perc[2] = (0.6266f, -0.5878f);
//Perc[3] = (-0.5269f, -0.8656f);
//Perc[4] = (-0.6467f, -0.3021f);
//Perc[5] = (0.7383f, 0.6209f);
//Perc[6] = (0.4391f, -0.0770f);
//Perc[7] = (-0.0188f, -0.1139f);
//Perc[8] = (-0.4031f, 0.4058f);
//Perc[9] = (-0.4645f, 0.7435f);
//Perc[10] = (0.1725f, 0.6748f);

//L2
//Perc[0] = (0.7014f, 0.7820f);
//Perc[1] = (-0.5651f, 0.6778f);
//Perc[2] = (-0.2347f, 0.1088f);
//Perc[3] = (-0.4905f, -0.7067f);
//Perc[4] = (-0.1821f, -0.3949f);
//Perc[5] = (0.1125f, 0.5502f);
//Perc[6] = (-0.5990f, -0.1694f);
//Perc[7] = (0.8092f, 0.4508f);


//C
//Perc[0] = (0.5179f, -0.7140f);
//Perc[1] = (-0.1019f, -0.6098f);
//Perc[2] = (-0.5584f, 0.0402f);
//Perc[3] = (0.6042f, 0.5623f);
//Perc[4] = (-0.2399f, 0.6521f);
//Perc[5] = (-0.6577f, -0.7388f);

//O
//Perc[0] = (-0.5779f, -0.7229f);
//Perc[1] = (0.5835f, -0.8096f);
//Perc[2] = (0.3296f, -0.2530f);
//Perc[3] = (0.7158f, 0.3712f);
//Perc[4] = (0.0894f, 0.5034f);
//Perc[5] = (-0.5684f, -0.0341f);
//Perc[6] = (-0.5166f, 0.6143f);

//M
//Perc[0] = (-0.4234f, -0.7772f);
//Perc[1] = (0.5293f, -0.8538f);
//Perc[2] = (0.4314f, -0.3230f);
//Perc[3] = (0.0362f, -0.0051f);
//Perc[4] = (-0.3340f, -0.2338f);
//Perc[5] = (-0.6568f, 0.6334f);
//Perc[6] = (0.7104f, 0.2515f);
//Perc[7] = (0.5535f, 0.6877f);


//P
//Perc[0] = (-0.5942f, -0.8127f);
//Perc[1] = (0.5425f, -0.8089f);
//Perc[2] = (0.6982f, -0.3697f);
//Perc[3] = (-0.2222f, -0.0253f);
//Perc[4] = (0.1196f, -0.5053f);
//Perc[5] = (-0.3281f, 0.6736f);
//Perc[6] = (-0.5164f, 0.3438f);

//L
//Perc[0] = (-0.0558f, -0.7574f);
//Perc[1] = (-0.5214f, -0.8662f);
//Perc[2] = (-0.0799f, 0.4434f);
//Perc[3] = (0.6308f, 0.4992f);
//Perc[4] = (-0.3788f, -0.2106f);
//Perc[5] = (-0.4598f, 0.7346f);

//E1

//Perc[0] = (0.6400f, -0.7854f);
//Perc[1] = (-0.6065f, -0.7792f);
//Perc[2] = (0.3993f, -0.0575f);
//Perc[3] = (-0.3001f, 0.1334f);
//Perc[4] = (0.7590f, 0.5532f);
//Perc[5] = (-0.0339f, 0.6810f);
//Perc[6] = (-0.0041f, -0.6191f);

//T

//Perc[0] = (-0.7590f, -0.8508f);
//Perc[1] = (0.6851f, -0.7997f);
//Perc[2] = (-0.1450f, -0.5210f);
//Perc[3] = (0.2034f, 0.7309f);
//Perc[4] = (-0.0798f, 0.2279f);
//Perc[5] = (0.1326f, -0.1376f);
//Perc[6] = (-0.7173f, -0.4514f);


//E2

//Perc[0] = (0.1343f, -0.6782f);
//Perc[1] = (-0.5686f, -0.7058f);
//Perc[2] = (0.3637f, 0.0137f);
//Perc[3] = (-0.3056f, -0.2149f);
//Perc[4] = (-0.6016f, 0.2607f);
//Perc[5] = (-0.5741f, 0.7228f);
//Perc[6] = (0.6791f, 0.6774f);
//Perc[7] = (0.0975f, 0.6103f);
