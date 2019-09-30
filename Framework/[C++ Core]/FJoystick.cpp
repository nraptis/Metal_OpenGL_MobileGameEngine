#include "FJoystick.h"

#include "core_includes.h"

FJoystick::FJoystick()
{
    mData = 0;
    mCancelTimer = 0;
    
    mCancelTimer = 0;
    mData = 0;
    
    mDirX = 0;
    mDirY = 0;
    mLength = 0;
    
    mLengthSquared = 0;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mDiffMultX = 1.0f;
    mDiffMultY = 1.0f;
    
    mPercentX = 0.0f;
    mPercentY = 0.0f;
    
    mRotation = 0.0f;
    mRotationFJoystick = 0.0f;
    
    mMaxDragLength = 42.0f;
    
    mRotateBack = false;
    
    mKnobMoves = true;
    mBackRotates = false;
    
    mSpriteBackground = 0;
    mSpriteKnob = 0;
    
    SetRadius(140);
    
    mRotationFJoystickStart = 0.0f;
    mRotationStart = 0.0f;
    
    mColor = FColor(1.0f, 1.0f, 1.0f, 1.0f);
}

FJoystick::~FJoystick()
{
    
}

void FJoystick::Update()
{
    if(mData)
    {
        /*
        mCancelTimer--;
        if(mCancelTimer <= 0)
        {
            mCancelTimer=0;
            mData=0;
            mLength=0;
            mDirX=0;
            mDirY=0;
        }
        */
    }
    else
    {
        mCancelTimer=0;
    }
}

void FJoystick::Draw()
{
    Graphics::SetColor(mColor);
    
    if(mRotateBack)
    {
        if(mSpriteBackground)mSpriteBackground->Draw(mX, mY, 1.0f, mRotationFJoystick);
    }
    else
    {
        if(mSpriteBackground)mSpriteBackground->Draw(mX, mY, 1.0f, 0.0f);
    }
    
    if(mSpriteKnob)
    {
        if(mKnobMoves)
        {
            mSpriteKnob->Center(mX + mDirX * mLength, mY + mDirY * mLength);
        }
        else
        {
            mSpriteKnob->Center(mX, mY);
        }
    }
}

bool FJoystick::IsClicked()
{
    
    if(mData)return true;
    
    else return false;
    
}




void FJoystick::TouchDown(float pX, float pY, void *pData)
{
    
    float aDiffX = (pX - mX);
    float aDiffY = (pY - mY);
    
    float aLengthSquared = aDiffX * aDiffX + aDiffY * aDiffY;
    
    if(aLengthSquared < mRadiusSquared)
    {
        bool aHit=false;
        
        if(mData)
        {
            if(aLengthSquared < mLengthSquared)
            {
                aHit = true;
            }
        }
        else
        {
            aHit = true;
        }
        
        if(aHit)
        {
            mData = pData;
            
            TouchMove(pX, pY, pData);
        }
    }
}

void FJoystick::TouchMove(float pX, float pY, void *pData)
{
    if(pData == mData)
    {
        float aDiffX = (pX - mX);
        float aDiffY = (pY - mY);
        
        aDiffX *= mDiffMultX;
        aDiffY *= mDiffMultY;
        
        float aLengthSquared = aDiffX * aDiffX + aDiffY * aDiffY;
        
        mLengthSquared = aLengthSquared;
        
        if(mLengthSquared > 1)
        {
            mLength = sqrtf(mLengthSquared);
            
            mDirX = aDiffX / mLength;
            mDirY = aDiffY / mLength;
            
            mRotation = //180.0f -
            
            FaceTarget(mDirX, mDirY);
            
            mRotationFJoystick = mRotationFJoystickStart + (mRotation - mRotationStart);
        }
        else
        {
            mLengthSquared = 0;
            mLength = 0;
            mDirX = 0;
            mDirY = 0;
        }
        
        if(mLength > mMaxDragLength)
        {
            mLength=mMaxDragLength;
        }
        
        mPercentX = (mDirX * mLength) / mMaxDragLength;
        mPercentY = (mDirY * mLength) / mMaxDragLength;
        
    }
}

void FJoystick::TouchUp(float pX, float pY, void *pData)
{
    bool aRelease = (pData == mData);
    //KLUDGE: To make Android better for now...
    if(aRelease == false)
    {
        float aDiffX = (pX - mX);
        float aDiffY = (pY - mY);
        
        float aLengthSquared = aDiffX * aDiffX + aDiffY * aDiffY;
        
        if(aLengthSquared < (mRadiusSquared * 2))
        {
            aRelease = true;
        }
    }
    
    if(aRelease)
    {
        mData=0;
        mCancelTimer=0;
        mLength = 0;
        mDirX = 0.0f;
        mDirY = 0.0f;
        mPercentX = 0.0f;
        mPercentY = 0.0f;
    }
}

void FJoystick::TouchFlush()
{
    mData=0;
    
    mCancelTimer=0;
    mLength = 0;
    mDirX = 0;
    mDirY = 0;
    
    mPercentX = 0.0f;
    mPercentY = 0.0f;
}




