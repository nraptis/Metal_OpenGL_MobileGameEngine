//
//  FQuad.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#include "core_includes.h"
#include "FQuad.hpp"

FQuad::FQuad() {
    mX[0] = 0.0f;
    mY[0] = 0.0f;
    mX[1] = 0.0f;
    mY[1] = 0.0f;
    mX[2] = 0.0f;
    mY[2] = 0.0f;
    mX[3] = 0.0f;
    mY[3] = 0.0f;
}

FQuad::~FQuad() {

}

void FQuad::Set(FQuad *pQuad) {
    if (pQuad) {
        float *aX = (pQuad->mX);
        float *aY = (pQuad->mY);
        Set(aX[0], aY[0], aX[1], aY[1], aX[2], aY[2], aX[3], aY[3]);
    }
}

void FQuad::Set(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4) {
    mX[0] = pX1;
    mX[1] = pX2;
    mX[2] = pX3;
    mX[3] = pX4;
    mY[0] = pY1;
    mY[1] = pY2;
    mY[2] = pY3;
    mY[3] = pY4;
}

void FQuad::Set(float pStartX, float pStartY, float pEndX, float pEndY) {
    Set(pStartX, pStartY, pEndX, pStartY, pStartX, pEndY, pEndX, pEndY);
}

void FQuad::SetRect(float pX, float pY, float pWidth, float pHeight) {
    Set(pX, pY, pX + pWidth, pY, pX, pY + pHeight, pX + pWidth, pY + pHeight);
}

void FQuad::Add(FQuad *pQuad) {
    if (pQuad) {
        float *aX = (pQuad->mX);
        float *aY = (pQuad->mY);
        Add(aX[0], aY[0], aX[1], aY[1], aX[2], aY[2], aX[3], aY[3]);
    }
}


void FQuad::Add(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4) {
    mX[0] += pX1;
    mX[1] += pX2;
    mX[2] += pX3;
    mX[3] += pX4;
    mY[0] += pY1;
    mY[1] += pY2;
    mY[2] += pY3;
    mY[3] += pY4;
}

float FQuad::CenterX() {
    return ((mX[0] + mX[1] + mX[2] + mX[3]) / 4.0f);
}

float FQuad::CenterY() {
    return ((mY[0] + mY[1] + mY[2] + mY[3]) / 4.0f);
}

void FQuad::Rotate(float pDegrees) {
    Rotate(pDegrees, 0.0f, 0.0f);
}

void FQuad::Rotate(float pDegrees, float pCenterX, float pCenterY) {
    if (pDegrees != 0.0f) {
        pDegrees = pDegrees * 0.01745329251994329576923690768488;
        float aX = 0.0f;
        float aY = 0.0f;
        float aDist = 0.0f;
        float aPivot = 0.0f;
        for (int i=0;i<4;i++) {
            aX = pCenterX - mX[i];
            aY = pCenterY - mY[i];
            aDist = aX * aX + aY * aY;
            if (aDist > SQRT_EPSILON) {
                aDist = sqrtf(aDist);
                aX /= aDist;
                aY /= aDist;
            }
            aPivot = (pDegrees - atan2f(aX, aY));
            mX[i] = (sin(aPivot)) * aDist + pCenterX;
            mY[i] = (-cos(aPivot)) * aDist + pCenterY;
        }
    }
}

void FQuad::Scale(float pScale) {
        if (pScale != 1.0f) {
            for (int i=0;i<4;i++) { mX[i] *= pScale; }
            for (int i=0;i<4;i++) { mY[i] *= pScale; }
        }
}

void FQuad::Translate(float pX, float pY) {
    if (pX != 0) for (int i=0;i<4;i++) { mX[i] += pX; }
    if (pY != 0) for (int i=0;i<4;i++) { mY[i] += pY; }
}

void FQuad::SetCenter(float pX, float pY) {
    float aCenterX = CenterX();
    float aCenterY = CenterY();
    for (int i=0;i<4;i++) {
        mX[i] = ((mX[i] - aCenterX) + pX);
        mY[i] = ((mY[i] - aCenterY) + pY);
    }
}

void FQuad::SetCenter() {
    SetCenter(0.0f, 0.0f);
}

void FQuad::Convert(float pX, float pY, FQuad *pQuad, FQuad *pTargetQuad, float &pResultX, float &pResultY)
{
    /*
    float aCenterX = pQuad->CenterX();
    float aCenterY = pQuad->CenterX();
    
    float aX[4];
    float aY[4];
    
    float *aOX = pQuad->mX;
    float *aOY = pQuad->mY;
    
    //aX[0] = aX[0]
    
    
    
    
    */
}

void FQuad::DrawMarkers()
{
    for(int i=0;i<4;i++)
    {
        Graphics::OutlineRect(mX[i] - 2, mY[i] - 2, 5, 5, 4);
    }
    
    Graphics::DrawLine(mX[0], mY[0], mX[1], mY[1], 2.0f);
    Graphics::DrawLine(mX[1], mY[1], mX[3], mY[3], 2.0f);
    Graphics::DrawLine(mX[2], mY[2], mX[3], mY[3], 2.0f);
    Graphics::DrawLine(mX[2], mY[2], mX[0], mY[0], 2.0f);
}

void FQuad::Draw(FSprite *pSprite)
{
    if(pSprite)
    {
        pSprite->DrawQuad(mX[0], mY[0], mX[1], mY[1], mX[2], mY[2], mX[3], mY[3]);
    }
}

