
#include "FParticle.hpp"
#include "os_core_graphics.h"
#include "core_includes.h"

FParticle::FParticle(FSpriteSequence &pSpriteSequence, bool pLoop) {
    BaseInitialize();
    SetSpriteSequence(&pSpriteSequence);
    mFrameLoop = pLoop;
}

FParticle::FParticle(FSpriteSequence *pSpriteSequence, bool pLoop) {
    BaseInitialize();
    SetSpriteSequence(pSpriteSequence);
    mFrameLoop = pLoop;
}

FParticle::FParticle(FSpriteSequence &pSpriteSequence) {
    BaseInitialize();
    SetSpriteSequence(&pSpriteSequence);
    mFrameLoop = false;
}

FParticle::FParticle(FSpriteSequence *pSpriteSequence) {
    BaseInitialize();
    SetSpriteSequence(pSpriteSequence);
    mFrameLoop = false;
}

FParticle::FParticle(FSprite &pSprite) {
    BaseInitialize();
    SetSprite(&pSprite);
}

FParticle::FParticle(FSprite *pSprite) {
    BaseInitialize();
    SetSprite(pSprite);
}

FParticle::FParticle() {
    BaseInitialize();
}

FParticle::~FParticle()
{
    
}

void FParticle::BaseInitialize()
{
    mX = 0.0f;
    mY = 0.0f;
    
    mFrame = 0.0f;
    mFrameSpeed = 0.5f;
    mFrameMax = 0.0f;
    mFrameLoop = false;
    
    mXSpeed = 0.0f;
    mYSpeed = 0.0f;
    mGravityX = 0.0f;
    mGravityY = 0.0f;
    mGravityYAdd = 0.0f;
    mSpeedAccel = 1.0f;
    
    
    mDelayAlphaSpeedAddTime = 0;
    mDelayAlphaSpeedAdd = 0.0f;
    
    mDelayScaleSpeedAddTime = 0;
    mDelayScaleSpeedAdd = 0.0f;
    
    mDelayAlphaSpeedTime = 0;
    mDelayAlphaSpeed = 0.0f;

    mDelayScaleSpeedTime = 0;
    mDelayScaleSpeed = 0.0f;
    
    mScale = 1.0f;
    mScaleSpeed = 0.0f;
    mScaleAccel = 1.0f;
    mScaleSpeedAdd = 0.0f;
    
    mRotation = 0.0f;
    mRotationSpeed = 0.0f;
    mRotationAccel = 1.0f;
    
    mRed = 1.0f;
    mGreen = 1.0f;
    mBlue = 1.0f;
    mAlpha = 1.0f;
    
    mRedSpeed = 0.0f;
    mGreenSpeed = 0.0f;
    mBlueSpeed = 0.0f;
    mAlphaSpeed = 0.0f;
    
    mSprite = 0;
    mSpriteSequence = 0;
    
    mTimeKill = 100000;
    mTimerDelay = 0;
    mTimerAlive = 0;
}

void FParticle::Update()
{
    if (mTimerDelay > 0) {
        mTimerDelay--;
    } else {
        mTimerAlive++;
        
        if (mRedSpeed != 0.0f) { mRed += mRedSpeed; }
        if (mGreenSpeed != 0.0f) { mGreen += mGreenSpeed; }
        if (mBlueSpeed != 0.0f) { mBlue += mBlueSpeed; }
        if (mAlphaSpeed != 0.0f) { mAlpha += mAlphaSpeed; }
        
        if (mXSpeed != 0.0f) { mX += mXSpeed; }
        if (mYSpeed != 0.0f) { mY += mYSpeed; }
        
        if (mGravityX != 0.0f) { mXSpeed += mGravityX; }
        if (mGravityY != 0.0f) { mYSpeed += mGravityY; }
        if (mGravityYAdd != 0.0f) { mGravityY += mGravityYAdd; }
        
		if (mSpeedAccel != 1.0f) {
			mXSpeed *= mSpeedAccel;
			mYSpeed *= mSpeedAccel;
		}
        
        if (mRotationSpeed != 0.0f) { mRotation += mRotationSpeed; }
        if (mRotationAccel != 1.0f) { mRotationSpeed *= mRotationAccel; }
        
        if (mScaleSpeed != 0.0f) { mScale += mScaleSpeed; }
        if (mScaleAccel != 1.0f) { mScaleSpeed *= mScaleAccel; }
        if (mScaleSpeedAdd != 0.0f) { mScaleSpeed += mScaleSpeedAdd; }
        
        
        if (mDelayScaleSpeedAdd != 0.0f) {
            if (mTimerAlive >= mDelayScaleSpeedAddTime) { mScaleSpeed += mDelayScaleSpeedAdd; }
        }
        
        if (mDelayAlphaSpeedAdd != 0.0f) {
            if (mTimerAlive >= mDelayAlphaSpeedAddTime) { mAlphaSpeed += mDelayAlphaSpeedAdd; }
        }
        
        if (mDelayAlphaSpeed != 0.0f) {
            if (mTimerAlive >= mDelayAlphaSpeedTime) { mAlpha += mDelayAlphaSpeed; }
        }
        
        if (mDelayScaleSpeed != 0.0f) {
            if (mTimerAlive >= mDelayScaleSpeedTime) { mScale += mDelayScaleSpeed; }
        }
        
        if (mAlpha <= 0.0f) {
            Kill();
        }
        if (mScale <= 0.0f) {
            Kill();
        }
        if (mTimerAlive >= mTimeKill) {
            Kill();
        }
        
        if (mFrameMax > 0.5f) {
            mFrame += mFrameSpeed;
            if (mFrame > mFrameMax) {
                if (mFrameLoop) {
                    mFrame -= mFrameMax;
                } else {
                    mFrame = mFrameMax;
                    Kill();
                }
            } else if(mFrame < 0) {
                if (mFrameLoop) {
                    mFrame += mFrameMax;
                } else {
                    mFrame = 0.0f;
                    Kill();
                }
            }
        }
    }
}

void FParticle::Draw() {
    
    float aRed = mRed;
    if (aRed > 1.0f) { aRed = 1.0f; }
    if (aRed < 0.0f) { aRed = 0.0f; }
    
    float aGreen = mGreen;
    if (aGreen > 1.0f) { aGreen = 1.0f; }
    if (aGreen < 0.0f) { aGreen = 0.0f; }
    
    float aBlue = mBlue;
    if (aBlue > 1.0f) { aBlue = 1.0f; }
    if (aBlue < 0.0f) { aBlue = 0.0f; }
    
    float aAlpha = mAlpha;
    if (aAlpha > 1.0f) { aAlpha = 1.0f; }
    if (aAlpha < 0.0f) { aAlpha = 0.0f; }
    
    float aRotation = mRotation;

    if ((mAlpha > 0.0f) && (mScale > 0.0f) && (mTimerDelay <= 0)) {
        Graphics::SetColor(aRed, aGreen, aBlue, aAlpha);
        if (mSprite) {
            mSprite->Draw(mX, mY, mScale, aRotation);
        }
        
        if (mSpriteSequence) {
            mSpriteSequence->Draw(mFrame, mX, mY, mScale, aRotation);
        }
    }
}

void FParticle::Draw(FSprite *pSprite)
{
    if ((pSprite != NULL) && (mTimerDelay <= 0)) {
        
        float aRed = mRed;
        if (aRed > 1.0f) { aRed = 1.0f; }
        if (aRed < 0.0f) { aRed = 0.0f; }
        
        float aGreen = mGreen;
        if (aGreen > 1.0f) { aGreen = 1.0f; }
        if (aGreen < 0.0f) { aGreen = 0.0f; }
        
        float aBlue = mBlue;
        if (aBlue > 1.0f) { aBlue = 1.0f; }
        if (aBlue < 0.0f) { aBlue = 0.0f; }
        
        float aAlpha = mAlpha;
        if (aAlpha > 1.0f) { aAlpha = 1.0f; }
        if (aAlpha < 0.0f) { aAlpha = 0.0f; }
        
        Graphics::SetColor(aRed, aGreen, aBlue, aAlpha);
        
        pSprite->Draw(mX, mY, mScale, mRotation);
    }
}

void FParticle::DrawOffset(FSprite *pSprite, float pShiftX, float pShiftY)
{
    if(pSprite && (mTimerDelay <= 0))
    {
        float aRed = mRed;
        if(aRed > 1.0f)aRed = 1.0f;
        if(aRed < 0.0f)aRed = 0.0f;
        
        float aGreen = mGreen;
        if(aGreen > 1.0f)aGreen = 1.0f;
        if(aGreen < 0.0f)aGreen = 0.0f;
        
        float aBlue = mBlue;
        if(aBlue > 1.0f)aBlue = 1.0f;
        if(aBlue < 0.0f)aBlue = 0.0f;
        
        float aAlpha = mAlpha;
        if(aAlpha > 1.0f)aAlpha = 1.0f;
        if(aAlpha < 0.0f)aAlpha = 0.0f;
        
        Graphics::SetColor(aRed, aGreen, aBlue, aAlpha);
        
        pSprite->Draw(mX + pShiftX, mY + pShiftY, mScale, mRotation);
    }
}

void FParticle::Draw(FSpriteSequence *pSpriteSequence) {
    Draw(pSpriteSequence->GetSprite(0.0f));
}

void FParticle::SetSprite(FSprite *pSprite) {
    mSprite = pSprite;
}

void FParticle::SetSpriteSequence(FSpriteSequence *pSpriteSequence) {
    mSpriteSequence = pSpriteSequence;
    if (mSpriteSequence != NULL) {
        mFrameMax = mSpriteSequence->GetMaxFrame();
    }
}

void FParticle::SetSpriteRandom(FSpriteSequence *pSpriteSequence) {
    if (pSpriteSequence != NULL) {
        SetSprite(pSpriteSequence->GetRandom());
    }
}

void FParticle::SetDelay(int pDelayTime) {
    mTimerDelay = pDelayTime;
}

void FParticle::SetDelay(int pDelayTime, int pDelayTimeRandom) {
    SetDelay(pDelayTime + gRand.Get(pDelayTimeRandom));
}

void FParticle::SetPos(float pX, float pY) {
    mX = pX;
    mY = pY;
}

void FParticle::SetSpeed(float pXSpeed, float pYSpeed) {
    mXSpeed = pXSpeed;
    mYSpeed = pYSpeed;
}

void FParticle::SetSpeed(float pSpeed) {
    SetSpeedDirectional(gRand.R(), pSpeed);
}

void FParticle::SetSpeedDirectional(float pDegrees) {
    mXSpeed = Sin(pDegrees);
    mYSpeed = -Cos(pDegrees);
}

void FParticle::SetSpeedDirectional(float pDegrees, float pMagnitude) {
    mXSpeed = Sin(pDegrees) * pMagnitude;
    mYSpeed = (-Cos(pDegrees)) * pMagnitude;
}

void FParticle::SetAccel(float pAccel) {
	mSpeedAccel = pAccel;
}

void FParticle::SetScale(float pScale) {
    mScale = pScale;
}

void FParticle::SetScale(float pScale, float pScaleSpeed) {
    mScale = pScale;
    mScaleSpeed = pScaleSpeed;
}

void FParticle::SetScale(float pScale, float pScaleSpeed, float pScaleAccel) {
    mScale = pScale;
    mScaleSpeed = pScaleSpeed;
    mScaleAccel = pScaleAccel;
}

void FParticle::SetScaleRandom(float pScale, float pSpan) {
    mScale = gRand.GetFloatWithSpan(pScale, pSpan);
}

void FParticle::SetScaleRandom(float pScale, float pScaleSpeed, float pSpan) {
    mScale = gRand.GetFloatWithSpan(pScale, pSpan);
    mScaleSpeed = pScaleSpeed;
}

void FParticle::SetScaleRandom(float pScale, float pScaleSpeed, float pScaleAccel, float pSpan) {
    mScale = gRand.GetFloatWithSpan(pScale, pSpan);
    mScaleSpeed = pScaleSpeed;
    mScaleAccel = pScaleAccel;
}

void FParticle::SetRotation() {
    mRotation = gRand.GetRotation();
}

void FParticle::SetRotation(float pRotation)
{
    mRotation = pRotation;
}

void FParticle::SetRotation(float pRotation, float pRotationSpeed, int pNegative)
{
    mRotation = pRotation;
    mRotationSpeed = pRotationSpeed;
}

void FParticle::SetRotation(float pRotation, float pRotationSpeed, float pRotationAccel, int pNegative)
{
    mRotation = pRotation;
    mRotationSpeed = pRotationSpeed;
    mRotationAccel = pRotationAccel;
}

void FParticle::SetRR()
{
    SetRotation(gRand.GetRotation());
}

void FParticle::SetRR(float pRotationSpeed)
{
    SetRotation(gRand.GetRotation(), pRotationSpeed);
    
}
void FParticle::SetRR(float pRotationSpeed, float pRotationAccel)
{
    SetRotation(gRand.GetRotation(), pRotationSpeed, pRotationAccel);
}

void FParticle::SetRRN(float pRotationSpeed)
{
    SetRotation(gRand.R(), gRand.GetFloat(-pRotationSpeed, pRotationSpeed));
    
    //float aRot = gRand.GetRotation();
    //if(gRand.GetBool())SetRotation(aRot, pRotationSpeed);
    //else SetRotation(aRot, -pRotationSpeed);
}

void FParticle::SetRRN(float pRotationSpeed, float pRotationAccel)
{
    
    SetRotation(gRand.R(), gRand.GetFloat(-pRotationSpeed, pRotationSpeed), pRotationAccel);
    
    //if(gRand.GetBool())SetRotation(aRot, pRotationSpeed, pRotationAccel);
    //else SetRotation(aRot, -pRotationSpeed, pRotationAccel);
}

void FParticle::SetColor(float pAlpha)
{
    mAlpha = pAlpha;
}

void FParticle::SetColor(float pRed, float pGreen, float pBlue)
{
    mRed = pRed;
    mGreen = pGreen;
    mBlue = pBlue;
}

void FParticle::SetColor(float pRed, float pGreen, float pBlue, float pAlpha)
{
    mRed = pRed;
    mGreen = pGreen;
    mBlue = pBlue;
    
    mAlpha = pAlpha;
}

void FParticle::SetColorRandom(float pIntensity, float pSpan)
{
    mRed = gRand.GetFloatWithSpan(pIntensity, pSpan);
    mGreen = gRand.GetFloatWithSpan(pIntensity, pSpan);
    mBlue = gRand.GetFloatWithSpan(pIntensity, pSpan);
}

void FParticle::SetColorRandom(float pRed, float pGreen, float pBlue, float pSpan)
{
    mRed = gRand.GetFloatWithSpan(pRed, pSpan);
    mGreen = gRand.GetFloatWithSpan(pGreen, pSpan);
    mBlue = gRand.GetFloatWithSpan(pBlue, pSpan);
}

void FParticle::SetAlpha(float pAlpha)
{
    mAlpha = pAlpha;
}

void FParticle::SetAlphaRandom(float pAlpha, float pSpan)
{
    mAlpha = gRand.GetFloatWithSpan(pAlpha, pSpan);
}

void FParticle::SetAlphaSpeed(float pAlphaSpeed)
{
    mAlphaSpeed = pAlphaSpeed;
}

void FParticle::SetAlphaSpeedRandom(float pAlphaSpeed, float pSpan) {
    mAlphaSpeed = gRand.GetFloatWithSpan(pAlphaSpeed, pSpan);
}

void FParticle::SetSpeed(float pXSpeed, float pYSpeed, float pAccel) {
    mXSpeed = pXSpeed;
    mYSpeed = pYSpeed;
    mSpeedAccel = pAccel;
}

void FParticle::SetRotation(float pRotation, float pRotationSpeed, float pRotationAccel, bool pSpeedRandomNegative) {
    mRotation = pRotation;
    mRotationSpeed = pRotationSpeed;
    mRotationAccel = pRotationAccel;
    if (pSpeedRandomNegative) {
        if (gRand.GetBool()) {
            mRotationSpeed = (-mRotationSpeed);
        }
    }
}

void FParticle::SetGravity(float pGravityX, float pGravityY, float pGravityYAdd) {
    mGravityX = pGravityX;
    mGravityY = pGravityY;
    mGravityYAdd = pGravityYAdd;
}

void FParticle::SetScale(float pScale, float pScaleSpeed, float pScaleSpeedAdd, float pScaleSpeedAccel) {
    mScale = pScale;
    mScaleSpeed = pScaleSpeed;
    mScaleSpeedAdd = pScaleSpeedAdd;
    mScaleAccel = pScaleSpeedAccel;
}

void FParticle::SetColorSpeed(float pAlpha) {
    mAlphaSpeed = pAlpha;
}

void FParticle::SetColorSpeed(float pRed, float pGreen, float pBlue) {
    mRedSpeed = pRed;
    mGreenSpeed = pGreen;
    mBlueSpeed = pBlue;
}

void FParticle::SetColorSpeed(float pRed, float pGreen, float pBlue, float pAlpha) {
    mRedSpeed = pRed;
    mGreenSpeed = pGreen;
    mBlueSpeed = pBlue;
    mAlphaSpeed = pAlpha;
}

void FParticle::SetColor(float pRed, float pGreen, float pBlue, float pAlpha,
                                                     float pSpeedRed, float pSpeedGreen, float pSpeedBlue, float pSpeedAlpha) {
    SetColor(pRed, pGreen, pBlue, pAlpha);
    SetColorSpeed(pSpeedRed, pSpeedGreen, pSpeedBlue, pSpeedAlpha);
}



void FParticle::SetFrame(float pFrame, float pFrameSpeed, bool pFrameLoop) {
    mFrame = pFrame;
    mFrameSpeed = pFrameSpeed;
    mFrameLoop = pFrameLoop;
}


void FParticle::SetDelayAlphaAddSpeed(int pTime, float pAlphaSpeedAdd) {
    mDelayAlphaSpeedAddTime = pTime;
    mDelayAlphaSpeedAdd = pAlphaSpeedAdd;
}

void FParticle::SetDelayScaleAddSpeed(int pTime, float pScaleSpeedAdd) {
    mDelayScaleSpeedAddTime = pTime;
    mDelayScaleSpeedAdd = pScaleSpeedAdd;
}

void FParticle::SetDelayAlphaSpeed(int pTime, float pAlphaSpeed) {
    mDelayAlphaSpeedTime = pTime;
    mDelayAlphaSpeed = pAlphaSpeed;
}

void FParticle::SetDelayScaleSpeed(int pTime, float pScaleSpeed) {
    mDelayScaleSpeedTime = pTime;
    mDelayScaleSpeed = pScaleSpeed;
}

void FParticle::Fling(float pDirX, float pDirY, float pPunch, float pPower) {
    float aDirX = pDirX;
    float aDirY = pDirY;
    float aLength = aDirX * aDirX + aDirY * aDirY;
    if (aLength > SQRT_EPSILON) {
        aLength = sqrtf(aLength);
        aDirX /= aLength;
        aDirY /= aLength;
    } else {
        aDirX = 0.0f;
        aDirY = -1.0f;
    }
    
    if (pPunch != 0.0f) {
        mX += aDirX * pPunch;
        mY += aDirY * pPunch;
    }
    
    SetSpeed(aDirX * pPower, aDirY * pPower);
}

void FParticle::Fling(float pDirectionAngle, float pPunch, float pPower) {
    
    float aDirX = Sin(pDirectionAngle);
    float aDirY = -Cos(pDirectionAngle);
    
    if (pPunch != 0.0f) {
        mX += aDirX * pPunch;
        mY += aDirY * pPunch;
    }
    
    SetSpeed(aDirX * pPower, aDirY * pPower);
}
