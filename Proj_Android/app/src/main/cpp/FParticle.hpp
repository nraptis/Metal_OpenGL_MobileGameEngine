//
//  ParticleCloud.h
//  Digplex
//
//  Created by Nick Raptis on 9/27/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include "FObject.hpp"
#include "FSpriteSequence.h"
#include "FSprite.hpp"

class FParticle : public FObject
{
public:
    
    FParticle(FSpriteSequence &pSpriteSequence, bool pLoop);
    FParticle(FSpriteSequence *pSpriteSequence, bool pLoop);
    
    FParticle(FSpriteSequence &pSpriteSequence);
    FParticle(FSpriteSequence *pSpriteSequence);
    
    FParticle(FSprite &pSprite);
    FParticle(FSprite *pSprite);
    
    FParticle();
    virtual ~FParticle();
    
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    void										Draw(FSprite *pSprite);
    void										Draw(FSpriteSequence *pSpriteSequence);
    void                                        SetSprite(FSprite *pSprite);
    void                                        SetSpriteSequence(FSpriteSequence *pSpriteSequence);
    void                                        SetSpriteRandom(FSpriteSequence *pSpriteSequence);
    
    inline void									Draw(FSprite &pSprite){Draw(&pSprite);}
    inline void									Draw(FSpriteSequence &pSpriteSequence){Draw(&pSpriteSequence);}
    inline void									SetSprite(FSprite &pSprite){SetSprite(&pSprite);}
    inline void									SetSpriteSequence(FSpriteSequence &pSpriteSequence){SetSpriteSequence(&pSpriteSequence);}
    inline void									SetSpriteRandom(FSpriteSequence &pSpriteSequence){SetSpriteRandom(&pSpriteSequence);}
    
    void										DrawOffset(FSprite *pSprite, float pShiftX, float pShiftY);
    void										DrawOffset(FSprite &pSprite, float pShiftX, float pShiftY){DrawOffset(&pSprite, pShiftX, pShiftY);}
    
    FSprite										*mSprite;
    FSpriteSequence								*mSpriteSequence;
    
	void										SetDelay(int pDelayTime);
    void										SetDelay(int pDelayTime, int pDelayTimeRandom);
    void										SetPos(float pX, float pY);
    
    void										SetSpeed(float pXSpeed, float pYSpeed);
    void										SetSpeed(float pSpeed);
    
    void										SetSpeedDirectional(float pDegrees);
    void										SetSpeedDirectional(float pDegrees, float pMagnitude);
    
    void										SetAccel(float pAccel);
    
    void                                        SetScale(float pScale);
    void                                        SetScale(float pScale, float pScaleSpeed);
    void                                        SetScale(float pScale, float pScaleSpeed, float pScaleAccel);
    
    void                                        SetScaleRandom(float pScale, float pSpan);
    void                                        SetScaleRandom(float pScale, float pScaleSpeed, float pSpan);
    void                                        SetScaleRandom(float pScale, float pScaleSpeed, float pScaleAccel, float pSpan);
    
    void                                        SetColor(float pAlpha);
    void                                        SetColor(float pRed, float pGreen, float pBlue);
    void                                        SetColor(float pRed, float pGreen, float pBlue, float pAlpha);
    
    void                                        SetColorRandom(float pIntensity, float pSpan);
    void                                        SetColorRandom(float pRed, float pGreen, float pBlue, float pSpan);
    
    void                                        SetAlpha(float pAlpha);
    void                                        SetAlphaRandom(float pAlpha, float pSpan);
    
    void                                        SetAlphaSpeed(float pAlphaSpeed);
    void                                        SetAlphaSpeedRandom(float pAlphaSpeed, float pSpan);
    
    void                                        SetRotation();
    void                                        SetRotation(float pRotation);
    void                                        SetRotation(float pRotation, float pRotationSpeed, int pNegative=1);
    void                                        SetRotation(float pRotation, float pRotationSpeed, float pRotationAccel, int pNegative=1);
    
    
    void										SetSpeed(float pXSpeed, float pYSpeed, float pAccel);
    void                                        SetRotation(float pRotation, float pRotationSpeed, float pRotationAccel, bool pSpeedRandomNegative);
    void										SetGravity(float pGravityX, float pGravityY, float pGravityYAdd);
    
    void										SetScale(float pScale, float pScaleSpeed, float pScaleSpeedAdd, float pScaleSpeedAccel);
    
    void                                        SetColorSpeed(float pAlpha);
    void                                        SetColorSpeed(float pRed, float pGreen, float pBlue);
    void                                        SetColorSpeed(float pRed, float pGreen, float pBlue, float pAlpha);
    
    void                                        SetColor(float pRed, float pGreen, float pBlue, float pAlpha,
                                                         float pSpeedRed, float pSpeedGreen, float pSpeedBlue, float pSpeedAlpha);
    
    
    
    void                                        SetFrame(float pFrame, float pFrameSpeed, bool pFrameLoop);
    
    
    void                                        SetDelayAlphaAddSpeed(int pTime, float pAlphaSpeedAdd);
    void                                        SetDelayScaleAddSpeed(int pTime, float pScaleSpeedAdd);
    
    void                                        SetDelayAlphaSpeed(int pTime, float pAlphaSpeed);
    void                                        SetDelayScaleSpeed(int pTime, float pScaleSpeed);
    
    
    
    void                                        SetRR();
    void                                        SetRR(float pRotationSpeed);
    void                                        SetRR(float pRotationSpeed, float pRotationAccel);
    
    void                                        SetRRN(float pRotationSpeed);
    void                                        SetRRN(float pRotationSpeed, float pRotationAccel);
    
    
    void                                        Fling(float pDirX, float pDirY, float pPower, float pPunch);
    void                                        Fling(float pDirectionAngle, float pPower, float pPunch);
    
    
    float                                       mX;
    float                                       mY;
    
    float                                       mXSpeed;
    float                                       mYSpeed;
	float                                       mSpeedAccel;
    
	float                                       mGravityX;
	float                                       mGravityY;
	float                                       mGravityYAdd;
    
    
    float                                       mScale;
    float                                       mScaleSpeed;
	float                                       mScaleSpeedAdd;
    float                                       mScaleAccel;

    float                                       mRotation;
    float                                       mRotationSpeed;
	float                                       mRotationAccel;
	//bool										mRotationFaceDir;
    
    
    float                                       mRed;
    float                                       mGreen;
    float                                       mBlue;
    float                                       mAlpha;
    
    float                                       mRedSpeed;
    float                                       mGreenSpeed;
    float                                       mBlueSpeed;
	float                                       mAlphaSpeed;
    
    int                                         mDelayAlphaSpeedAddTime;
    float                                       mDelayAlphaSpeedAdd;
    
    
    int                                         mDelayScaleSpeedAddTime;
    float                                       mDelayScaleSpeedAdd;
    
    
    int                                         mDelayAlphaSpeedTime;
    float                                       mDelayAlphaSpeed;
    
    int                                         mDelayScaleSpeedTime;
    float                                       mDelayScaleSpeed;
    
    
    
    float                                       mFrame;
    float                                       mFrameSpeed;
    float                                       mFrameMax;
    bool                                        mFrameLoop;
    
    int                                         mTimerDelay;
    int                                         mTimerAlive;
    int                                         mTimeKill;
    
protected:
    
    void                                        BaseInitialize();
    
};




#endif 


