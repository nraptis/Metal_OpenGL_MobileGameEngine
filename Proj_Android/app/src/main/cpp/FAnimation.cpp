//
//  FAnimation.cpp
//  Graveyard
//
//  Created by Nick Raptis on 2/16/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FAnimation.hpp"
#include "core_includes.h"
#include "FMath.hpp"

FAnimation::FAnimation() {

}

FAnimation::~FAnimation()
{
    
}


float FAnimation::SplineInterpolate(float pPercent, float pStartValue, float pEndValue, float pStartTan, float pEndTan)
{
    
    //float aHold = pStartTan;
    //pStartTan = pEndTan;
    pEndTan = -pEndTan;
    
    /*
     
    if(circular)
    {
        if(!aDer[0])theDerivative[0]=-theDerivative[1];
        if(!aDer[1])theDerivative[1]=-theDerivative[0];
        theCoef[aCoefOffStart++]=theDerivative[0];
        theCoef[aCoefOffStart++]=3*(theCoordinate[1]-theCoordinate[0])-2*theDerivative[0]-theDerivative[1];
        theCoef[aCoefOffStart++]=2*(theCoordinate[0]-theCoordinate[1])+theDerivative[0]+theDerivative[1];
        theCoef[aCoefOffStart++]=theDerivative[1];
        theCoef[aCoefOffStart++]=3*(theCoordinate[0]-theCoordinate[1])-2*theDerivative[1]-theDerivative[0];
        theCoef[aCoefOffStart++]=2*(theCoordinate[1]-theCoordinate[0])+theDerivative[1]+theDerivative[0];
    }
    */
    
    float aCoef[3];
    
    aCoef[0] = pStartTan;
    aCoef[1] = 3.0f * (pEndValue-pStartValue) - 2.0f * pStartTan - pEndTan;
    aCoef[2] = 2.0f * (pStartValue - pEndValue) + pStartTan + pEndTan;
    
    float aPercent = pPercent;
    float aPercent2 = aPercent * pPercent;
    float aPercent3 = aPercent2 * pPercent;
    
    
    
    return pStartValue + aCoef[0]*aPercent + aCoef[1]*aPercent2 + aCoef[2]*aPercent3;
}

/*
void FAnimation::CreateSpline2D(FVec2 pStart, FVec2 pEnd, FVec2 pStartTan, FVec2 pEndTan, int pTicks)
{
    if(pTicks < 2)pTicks = 2;
    
    EnsureSize(pTicks, 2);
    
    CreateSpline(pStart.mX, pEnd.mX, pStartTan.mX, pEndTan.mX, 0, pTicks);
    CreateSpline(pStart.mY, pEnd.mY, pStartTan.mY, pEndTan.mY, 1, pTicks);
}

void FAnimation::CreateSpline(float pStart, float pEnd, float pStartTan, float pEndTan, int pDim, int pTicks)
{
    
    
    if((pTicks < 2) || (pDim < 0))
    {
        return;
    }
    
    EnsureSize(pTicks, pDim);
    
    float aCoef[3];
    
    aCoef[0] = pStartTan;
    aCoef[1] = 3.0f * (pEnd-pStart) - 2.0f * pStartTan - pEndTan;
    aCoef[2] = 2.0f * (pStart - pEnd) + pStartTan + pEndTan;
    
    float aPercent = 0.0f;
    float aPercent2 = 0.0f;
    float aPercent3 = 0.0f;
    
    float aMax = (float)(pTicks - 1);
    
    for(int i=0;i<pTicks;i++)
    {
        aPercent = ((float)i) / aMax;
        
        aPercent2 = aPercent * aPercent;
        aPercent3 = aPercent2 * aPercent;
        
        mValue[pDim][i] = pStart+aCoef[0]*aPercent+aCoef[1]*aPercent2+aCoef[2]*aPercent3;
        mValue[pDim][i] = pStart+aCoef[0]*aPercent+aCoef[1]*aPercent2+aCoef[2]*aPercent3;
    }
    
    mValueCount = pTicks;

}

void FAnimation::CreateDeceleration(FVec2 pStart, FVec2 pEnd, FVec2 pStartSpeed, FVec2 pEndSpeed)
{
    Reset();
    
    float aEndX = pEnd.mX;
    float aEndY = pEnd.mY;
    
    float aStartX = pStart.mX;
    float aStartY = pStart.mY;
    
    float aDiffX = aEndX - pStart.mX;
    float aDiffY = aEndY - pStart.mY;
    
    float aDiffSquaredX = aDiffX * aDiffX;
    float aDiffSquaredY = aDiffY * aDiffY;
    
    //float aDiff = 0.0f;
    float aDist = (aDiffX * aDiffX) + (aDiffY * aDiffY);
    
    
    float aSpeedStartX = pStartSpeed.mX;
    float aSpeedStartY = pStartSpeed.mY;
    
    float aSpeedEndX = pEndSpeed.mX;
    float aSpeedEndY = pEndSpeed.mY;
    
    float aDiffSpeedX = pEndSpeed.mX - pStartSpeed.mX;
    float aDiffSpeedY = pEndSpeed.mY - pStartSpeed.mY;
    
    
    
    int aTicks = 100;
    
    
    float aX = aStartX;
    float aY = aStartY;
    
    float aSpeedX = aSpeedStartX;
    float aSpeedY = aSpeedStartY;
    
    float aSpeedShiftX = 0.0f;
    float aSpeedShiftY = 0.0f;
    
    
    //aPercent
    
    float aBaseX = aStartX;
    float aBaseY = aStartY;
    
    bool aRetweak = gRand.GetBool();
    
    
    FAnimation aAnimation1;
    FAnimation aAnimation2;
    
    for(int i=0;i<aTicks;i++)
    {
        float aPercent = ((float)i) / ((float)(aTicks - 1));
        
        
        aPercent = (aPercent * aPercent);
        
        aSpeedX = aSpeedStartX + (aDiffSpeedX * aPercent);
        aSpeedY = aSpeedStartY + (aDiffSpeedY * aPercent);
        
        aSpeedShiftX += aSpeedX;
        aSpeedShiftY += aSpeedY;
        
        aX = aStartX + aSpeedShiftX;
        aY = aStartY + aSpeedShiftY;
        
        if(aRetweak)
        {
        aX = aStartX + (aSpeedStartX * ((float)i));
        aY = aStartY + (aSpeedStartY * ((float)i));
        }
        
        
        AddValue(aX, aY);
        aAnimation1.AddValue(aX, aY);
        
    }
    
    aSpeedX = aSpeedEndX;
    aSpeedY = aSpeedEndY;
    
    aSpeedShiftX = 0.0f;
    aSpeedShiftY = 0.0f;
    
    for(int i=0;i<aTicks;i++)
    {
        float aPercent = ((float)i) / ((float)(aTicks - 1));
        
        aPercent = (aPercent * aPercent);
        
        //aPercent = (1.0f - aPercent);
        
        aSpeedX = aSpeedEndX - (aDiffSpeedX * aPercent);
        aSpeedY = aSpeedEndY - (aDiffSpeedY * aPercent);
        
        aSpeedShiftX += aSpeedX;
        aSpeedShiftY += aSpeedY;
        
        aX = aEndX - aSpeedShiftX;
        aY = aEndY - aSpeedShiftY;
        
        
        if(aRetweak)
        {
            aX = aEndX - (aSpeedEndX * ((float)i));
            aY = aEndY - (aSpeedEndY * ((float)i));
        }
        
        AddValue(aX, aY);
        
        aAnimation2.AddValue(aX, aY);
        
    }
    
    int aStart=0;
    int aEnd=aTicks-1;
    
    
    float aX1 = 0.0f;
    float aY1 = 0.0f;
    
    float aX2 = 0.0f;
    float aY2 = 0.0f;
    
    while(aStart < aTicks)
    {
        aX1 = aAnimation1.GetX(aStart);
        aY1 = aAnimation1.GetY(aStart);
        
        
        aX2 = aAnimation2.GetX(aEnd);
        aY2 = aAnimation2.GetY(aEnd);
        
        
        
        float aPercent = ((float)aStart) / ((float)(aTicks - 1));
        
        aPercent = (aPercent * aPercent * aPercent);
        
        float aPercentInv = (1.0f - aPercent);
        
        aX = aX2 * aPercent + aX1 * aPercentInv;
        aY = aY2 * aPercent + aY1 * aPercentInv;
        
        //aX = aX1 + (aX2 - aX1) * aPercent;
        //aY = aY1 + (aY2 - aY1) * aPercent;
        
        
        //aY = aY1 + (aY2 - aY1) * aPercent;
        
        
        AddValue(aX, aY);
        
     
        aStart++;
        aEnd--;
    }
    
    
    
    //  *
    
    //float aDistSpeed = (aDiffSpeedX * aDiffSpeedX) + (aDiffSpeedY * aDiffSpeedY);
    
    
    float aDecelerationX = 0.0f;
    float aDecelerationY = 0.0f;
    
    //float aDecelerationX = (pStartSpeed.mX * pStartSpeed.mX) / (2.0f * aDiffX);
    //float aDecelerationY = (pStartSpeed.mY * pStartSpeed.mY) / (2.0f * aDiffY);
    
    bool aFail = true;
    
    
    //a = (Vf*Vf - Vi*Vi)/(2 * d)
    
    if(aDist > 0.25f)
    {
        aDist = sqrtf(aDist);
    if(aDiffSquaredX >= 0.5f)
    {
        //aDecelerationX = (pEndSpeed.mX * pEndSpeed.mX - pStartSpeed.mX * pStartSpeed.mX) / (2.0f * aDist);
        //aDecelerationX = (pEndSpeed.mX * pEndSpeed.mX - pStartSpeed.mX * pStartSpeed.mX) / (2.0f * aDiffX);
        aDecelerationX = (aDiffSpeedX * aDiffSpeedX) / (2.0f * aDiffX);
        aDecelerationX = (aDiffSpeedX * aDiffSpeedX) / (2.0f * aDist);
        
        
        //aDecelerationX = (aDiffSpeedX * aDiffSpeedX) / (2.0f * aDiffX);
        
        aFail = false;
    }
    
    
    if(aDiffSquaredY >= 0.5f)
    {
        //aDecelerationY = (pEndSpeed.mY * pEndSpeed.mY - pStartSpeed.mY * pStartSpeed.mY) / (2.0f * aDist);
        //aDecelerationY = (pEndSpeed.mY * pEndSpeed.mY - pStartSpeed.mY * pStartSpeed.mY) / (2.0f * aDiffY);
        aDecelerationY = (aDiffSpeedY * aDiffSpeedY) / (2.0f * aDiffY);
        aDecelerationY = (aDiffSpeedY * aDiffSpeedY) / (2.0f * aDist);
        
        
        //aDecelerationY = (aDiffSpeedY * aDiffSpeedY) / (2.0f * aDiffY);
        
        
        aFail = false;
    }
    }
    
    
    
    if(aFail == false)
    {
        
        //aDist = sqrtf(aDist);
        
        //float aSpeedDiffX = (pStartSpeed.mX - pEndSpeed.mX);
        //float aSpeedDiffY = (pStartSpeed.mY - pEndSpeed.mY);
        
        //(- Vo^2) / (2 * dist)  = 2*a*s
        
        //float aDecelerationX = (pStartSpeed.mX * pStartSpeed.mX) / (2.0f * aDiffX);
        //float aDecelerationY = (pStartSpeed.mY * pStartSpeed.mY) / (2.0f * aDiffY);
        
        float aSpeedX = pStartSpeed.mX;
        float aSpeedY = pStartSpeed.mY;
        
        float aX = pStart.mX;
        float aY = pStart.mY;
        
        for(int i=0;((i<200) && (aFail == false));i++)
        {
            aX -= aSpeedX;
            aY -= aSpeedY;
            
            AddValue(aX, aY);
            
            
            //position = position + velocity * dt + acceleration * dt * dt * 1/2
            //velocity = velocity + acceleration * dt
            
            
            aSpeedX -= aDecelerationX;
            aSpeedY -= aDecelerationY;
            
            
            aDiffX = aX - aEndX;
            aDiffY = aY - aEndY;
            
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            
            if(aDist <= 1.5f)
            {
                aFail = true;
            }
            
            
            //pEndSpeed
            
        }
        
        //(mScrollAnimationSpeed * mScrollAnimationSpeed) / (2 * mScrollAnimationDecelerationDistance);
        
        //mScrollAnimationDeceleration = (mScrollAnimationSpeed * mScrollAnimationSpeed) / (2 * mScrollAnimationDecelerationDistance);
        
        
    }
    
    *  //
    
}
*/

float FAnimation::ApplyFunction(int pFunction, float pPercent)
{
    float aResult = pPercent;
    
    
    if(pFunction == ANIMATION_TYPE_EASE_OUT_SIN)aResult = EaseOutSine(pPercent);
    
    else if(pFunction == ANIMATION_TYPE_EASE_OUT_IN_SIN)aResult = EaseOutInSine(pPercent);
    else if(pFunction == ANIMATION_TYPE_EASE_IN_CURVE)aResult = EaseInCurve(pPercent);
    
    //Smooth Speed-Ups
    else if(pFunction == ANIMATION_TYPE_EASE_IN_SIN)aResult = EaseInSine(pPercent);
    else if(pFunction == ANIMATION_TYPE_EASE_IN_OUT_SIN)aResult = EaseInOutSine(pPercent);
    else if(pFunction == ANIMATION_TYPE_EASE_OUT_CURVE)aResult = EaseOutCurve(pPercent);
    
    //Smooth Stuck, ZOOM, Stuck..
    else if(pFunction == ANIMATION_TYPE_EASE_IN_OUT_EXPO)aResult = EaseInOutExpo(pPercent);
    else if(pFunction == EASE_IN_OUT_QUART)aResult = EaseInOutQuart(pPercent);
    else if(pFunction == EASE_OUT_IN_QUART)aResult = EaseOutInQuart(pPercent);
    //
    /////////////////////////////
    
    
    /////////////////////////////
    //
    //      Slow Down Group
    //
    //Slowing Down..
    else if(pFunction == ANIMATION_TYPE_EASE_OUT_CIRC)aResult = EaseOutCirc(pPercent);
    else if(pFunction == ANIMATION_EASE_OUT_ELASTIC)aResult = EaseOutElastic(pPercent);
    //else if(pFunction == ANIMATION_TYPE_EASE_OUT_BACK)aResult = EaseOutBack(pPercent);
    else if(pFunction == ANIMATION_TYPE_OVERSHOOT)aResult = Overshoot(pPercent);
    else if(pFunction == ANIMATION_TYPE_OVERSHOOT_MORE)aResult = OvershootMore(pPercent);
    else if(pFunction == ANIMATION_TYPE_BOUNCE)aResult =  Bounce(pPercent);
    else if(pFunction == ANIMATION_TYPE_BOUNCE_MORE)aResult = BounceMore(pPercent);
    else if(pFunction == ANIMATION_TYPE_EASE_OUT_QUART)aResult = EaseOutQuart(pPercent);
    else if(pFunction == ANIMATION_TYPE_EASE_OUT_EXPO)aResult = EaseOutExpo(pPercent);
    //
    /////////////////////////////
    
    
    /////////////////////////////
    //
    //      Speed Up Group
    //
    //Speeding Up.. (Slow, then FAST)
    else if(pFunction == ANIMATION_TYPE_EASE_IN_CIRC)aResult = EaseInCirc(pPercent);
    else if(pFunction == ANIMATION_TYPE_EASE_IN_OUT_CIRC)aResult = EaseInOutCirc(pPercent);
    else if(pFunction == ANIMATION_TYPE_EASE_IN_EXPO)aResult = EaseInExpo(pPercent);
    else if(pFunction == ANIMATION_TYPE_EASE_IN_QUART)aResult = EaseInQuart(pPercent);
    //Sticky like tar, then ZEWWWWWWW!!!
    //
    /////////////////////////////
    
    
    
    return aResult;
}

FString FAnimation::GetFunctionNameExtended(int pFunction)
{
	FString aGroupName = "???";


	if((pFunction == ANIMATION_TYPE_EASE_OUT_SIN) ||
		(pFunction == ANIMATION_TYPE_EASE_OUT_IN_SIN) ||
		(pFunction == ANIMATION_TYPE_EASE_IN_CURVE))
	{
		aGroupName = "Smooth, Slowing";
	}


	if((pFunction == ANIMATION_TYPE_EASE_IN_SIN) ||
		(pFunction == ANIMATION_TYPE_EASE_IN_OUT_SIN) ||
		(pFunction == ANIMATION_TYPE_EASE_OUT_CURVE))
	{
		aGroupName = "Smooth, Speeding";
	}


	if((pFunction == ANIMATION_TYPE_EASE_IN_OUT_EXPO) ||
		(pFunction == EASE_IN_OUT_QUART) ||
		(pFunction == EASE_OUT_IN_QUART))
	{
		aGroupName = "Smooth";
	}



	FString aResult = aGroupName;
	aResult += " - ";
	aResult += ".....!";

	return aResult;
}

float FAnimation::EaseInOutQuad(float pPercent)
{
    pPercent*=2.0;
    if(pPercent < 1) {
        return pPercent*pPercent/float(2);
    } else {
        --pPercent;
        return -0.5 * (pPercent*(pPercent-2) - 1);
    }
}

float EaseInQuad(float pPercent)
{
    return pPercent*pPercent;
}
float EaseOutQuad(float pPercent)
{
    return -pPercent*(pPercent-2);
}

float FAnimation::EaseOutInQuad(float pPercent)
{
    if(pPercent < 0.5) return EaseOutQuad (pPercent*2)/2;
    return EaseInQuad((2*pPercent)-1)/2 + 0.5;
}



/**
 * Easing equation function for a cubic (pPercent^3) easing in/out: acceleration until halfway, then deceleration.
 *
 * @param t Current time (in frames or seconds).
 * @return The correct value.
 */
float FAnimation::EaseInOutCubic(float pPercent)
{
    pPercent*=2.0;
    if(pPercent < 1)
    {
        return 0.5*pPercent*pPercent*pPercent;
    }
    else
    {
        pPercent -= float(2.0);
        return 0.5*(pPercent*pPercent*pPercent + 2);
    }
}


float EaseInCubic(float pPercent)
{
    return pPercent*pPercent*pPercent;
}

float EaseOutCubic(float pPercent)
{
    pPercent-=1.0;
    return pPercent*pPercent*pPercent + 1;
}

float FAnimation::EaseOutInCubic(float pPercent)
{
    if(pPercent < 0.5)
    {
        return EaseOutCubic (2*pPercent)/2;
    }
    else
    {
        return EaseInCubic(2*pPercent - 1)/2 + 0.5;
    }//return 77.0f;
    
}



float FAnimation::EaseInQuart(float pPercent)
{
    return pPercent*pPercent*pPercent*pPercent;
}

float FAnimation::EaseOutQuart(float pPercent)
{
    pPercent-= float(1.0);
    return - (pPercent*pPercent*pPercent*pPercent- 1);
}

float FAnimation::EaseInOutQuart(float pPercent)
{
    pPercent *= 2;
    
    if(pPercent < 1)
    {
        return 0.5*pPercent*pPercent*pPercent*pPercent;
    }
    else
    {
        pPercent -= 2.0f;
        return -0.5 * (pPercent*pPercent*pPercent*pPercent- 2);
    }
}

float FAnimation::EaseOutInQuart(float pPercent)
{
    if(pPercent < 0.5) return EaseOutQuart(2*pPercent)/2;
    return EaseInQuart(2*pPercent-1)/2 + 0.5;
}

float FAnimation::EaseInQuint(float pPercent) {
    return pPercent * pPercent * pPercent * pPercent * pPercent;
}

float FAnimation::EaseOutQuint(float pPercent) {
    pPercent -= 1.0f;
    return pPercent*pPercent*pPercent*pPercent*pPercent + 1.0f;
}

float FAnimation::EaseInOutQuint(float pPercent)
{
    pPercent*=2.0;
    if(pPercent < 1)
    {
        return 0.5*pPercent*pPercent*pPercent*pPercent*pPercent;
    }
    else
    {
        pPercent -= 2.0;
        return 0.5*(pPercent*pPercent*pPercent*pPercent*pPercent + 2);
    }
}

float FAnimation::EaseOutInQuint(float pPercent)
{
    if(pPercent < 0.5)return EaseOutQuint (2*pPercent)/2;
    return EaseInQuint(2*pPercent - 1)/2 + 0.5;
}

float FAnimation::EaseInSine(float pPercent)
{
    return (pPercent == 1.0) ? 1.0 : -cos(pPercent * PI_2) + 1.0;
}

float FAnimation::EaseOutSine(float pPercent)
{
    return sin(pPercent* PI_2);
}

float FAnimation::EaseInOutSine(float pPercent)
{
    return -0.5 * (cos(PI*pPercent) - 1);
}

float FAnimation::EaseOutInSine(float pPercent)
{
    if(pPercent < 0.5) return EaseOutSine (2*pPercent)/2;
    return EaseInSine(2*pPercent - 1)/2 + 0.5;
}

/**
 * Easing equation function for an exponential (2^pPercent easing in: accelerating from zero velocity.
 *
 * @param t Current time (in frames or seconds).
 * @return The correct value.
 */
float FAnimation::EaseInExpo(float pPercent)
{
    return (pPercent==0 || pPercent == 1.0) ? pPercent : powf(2.0, 10 * (pPercent - 1)) - 0.001f;
}

/**
 * Easing equation function for an exponential (2^pPercent easing out: decelerating from zero velocity.
 *
 * @param t Current time (in frames or seconds).
 * @return The correct value.
 */
float FAnimation::EaseOutExpo(float pPercent)
{
    return (pPercent==1.0) ? 1.0 : 1.001 * (-pow(2.0f, -10 * pPercent) + 1);
}

/**
 * Easing equation function for an exponential (2^pPercent easing in/out: acceleration until halfway, then deceleration.
 *
 * @param t Current time (in frames or seconds).
 * @return The correct value.
 */
float FAnimation::EaseInOutExpo(float pPercent)
{
    if(pPercent==0.0) return float(0.0);
    if(pPercent==1.0) return float(1.0);
    pPercent*=2.0;
    if(pPercent < 1) return 0.5 * pow(float(2.0), 10 * (pPercent - 1)) - 0.0005;
    return 0.5 * 1.0005 * (-pow(float(2.0), -10 * (pPercent - 1)) + 2);
}

/**
 * Easing equation function for an exponential (2^pPercent easing out/in: deceleration until halfway, then acceleration.
 *
 * @param t Current time (in frames or seconds).
 * @return The correct value.
 */
float FAnimation::EaseOutInExpo(float pPercent)
{
    if(pPercent < 0.5) return EaseOutExpo (2*pPercent)/2;
    return EaseInExpo(2*pPercent - 1)/2 + 0.5;
}

/**
 * Easing equation function for a circular (sqrt(1-pPercent^2)) easing in: accelerating from zero velocity.
 *
 * @param t Current time (in frames or seconds).
 * @return The correct value.
 */
float FAnimation::EaseInCirc(float pPercent)
{
    return -(sqrt(1 - pPercent*pPercent) - 1);
}

/**
 * Easing equation function for a circular (sqrt(1-pPercent^2)) easing out: decelerating from zero velocity.
 *
 * @param t Current time (in frames or seconds).
 * @return The correct value.
 */
float FAnimation::EaseOutCirc(float pPercent)
{
    pPercent -= 1.0f;
    return sqrt(1 - pPercent* pPercent);
}

/**
 * Easing equation function for a circular (sqrt(1-pPercent^2)) easing in/out: acceleration until halfway, then deceleration.
 *
 * @param t Current time (in frames or seconds).
 * @return The correct value.
 */
float FAnimation::EaseInOutCirc(float pPercent)
{
    pPercent*=float(2.0);
    if(pPercent < 1)
    {
        return -0.5 * (sqrt(1 - pPercent*pPercent) - 1);
    } else {
        pPercent -= float(2.0);
        return 0.5 * (sqrt(1 - pPercent*pPercent) + 1);
    }
}


/**
 * Easing equation function for an elastic (exponentially decaying sine wave) easing in: accelerating from zero velocity.
 *
 * @param t Current time (in frames or seconds).
 * @param a Amplitude.
 * @param p Period.
 * @return The correct value.
 
float FAnimation::EaseInElastic(float pPercent, float a, float p)
{
    return HelperEaseInElastic(EaseInCirc(pPercent), 0, 1, 1, a, p);
}
*/


/**
 * Easing equation function for an elastic (exponentially decaying sine wave) easing out: decelerating from zero velocity.
 *
 * @param t Current time (in frames or seconds).
 * @param a Amplitude.
 * @param p Period.
 * @return The correct value.
 */
float FAnimation::EaseOutElastic(float pPercent, float a, float p)
{
    /*
    float c = 1.0f;
    
    float s;
    if(a < c)
    {
        a = c;
        //
        s = p / 4.0f;
        
    }
    else
    {
        s = p / (2 * PI) * asin(c / a);
    }
    
    return (a*pow(2.0f,-10*pPercent) * sin( (pPercent-s)*(2*PI)/p ) + c);
    */
    
    return HelperEaseOutElastic(EaseInCirc(pPercent), 0, 1, 1, a, p);
    
    //HelperEaseOutElastic
}

/**
 * Easing equation function for an elastic (exponentially decaying sine wave) easing in/out: acceleration until halfway, then deceleration.
 *
 * @param t Current time (in frames or seconds).
 * @param a Amplitude.
 * @param p Period.
 * @return The correct value.
 
float FAnimation::EaseInOutElastic(float pPercent, float a, float p)
{
    if(pPercent==0) return 0.0;
    pPercent*=2.0;
    if(pPercent==2) return 1.0;
    
    pPercent = EaseInCirc(pPercent);
    
    float s;
    if(a < 1.0) {
        a = 1.0;
        s = p / 4.0f;
    } else {
        s = p / (2 * PI) * asin(1.0 / a);
    }
    
    if(pPercent < 1) return -.5*(a*pow(2.0f,10*(pPercent-1)) * sin( (pPercent-1-s)*(2*PI)/p ));
    return a*pow(2.0f,-10*(pPercent-1)) * sin( (pPercent-1-s)*(2*PI)/p )*.5 + 1.0;
}
*/

/**
 * Easing equation function for an elastic (exponentially decaying sine wave) easing out/in: deceleration until halfway, then acceleration.
 *
 * @param t Current time (in frames or seconds).
 * @param a Amplitude.
 * @param p Period.
 * @return The correct value.
 
float FAnimation::EaseOutInElastic(float pPercent, float a, float p)
{
    //pPercent = EaseInCirc(pPercent);
    
    if(pPercent < 0.5) return HelperEaseOutElastic(pPercent*2, 0, 0.5, 1.0, a, p);
    return HelperEaseInElastic(2*pPercent - 1.0, 0.5, 0.5, 1.0, a, p);
}
*/

/**
 * Easing equation function for a back (overshooting cubic easing: (s+1)*pPercent^3 - s*pPercent^2) easing in: accelerating from zero velocity.
 *
 * @param t Current time (in frames or seconds).
 * @param s Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percenpPercent.
 * @return The correct value.
 
float FAnimation::EaseInBack(float pPercent, float pOvershoot)
{
    return pPercent*pPercent*((pOvershoot+1)*pPercent - pOvershoot);
}
*/

/**
 * Easing equation function for a back (overshooting cubic easing: (s+1)*pPercent^3 - s*pPercent^2) easing out: decelerating from zero velocity.
 *
 * @param t Current time (in frames or seconds).
 * @param s Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percenpPercent.
 * @return The correct value.
 */
float FAnimation::EaseOutBack(float pPercent, float pOvershoot)
{
    pPercent-= float(1.0);
    return pPercent*pPercent*((pOvershoot+1)*pPercent + pOvershoot) + 1;
}

/**
 * Easing equation function for a back (overshooting cubic easing: (s+1)*pPercent^3 - s*pPercent^2) easing in/out: acceleration until halfway, then deceleration.
 *
 * @param t Current time (in frames or seconds).
 * @param s Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percenpPercent.
 * @return The correct value.
 
float FAnimation::EaseInOutBack(float pPercent, float pOvershoot)
{
    pPercent *= 2.0;
    if(pPercent < 1)
    {
        pOvershoot *= 1.525f;
        return 0.5*(pPercent*pPercent*((pOvershoot+1)*pPercent - pOvershoot));
    }
    else
    {
        pPercent -= 2;
        pOvershoot *= 1.525f;
        return 0.5*(pPercent*pPercent*((pOvershoot+1)*pPercent+ pOvershoot) + 2);
    }
}
*/

/**
 * Easing equation function for a back (overshooting cubic easing: (s+1)*pPercent^3 - s*pPercent^2) easing out/in: deceleration until halfway, then acceleration.
 *
 * @param t Current time (in frames or seconds).
 * @param s Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percenpPercent.
 * @return The correct value.
 
float FAnimation::EaseOutInBack(float pPercent, float pOvershoot)
{
    if(pPercent < 0.5) return EaseOutBack(2*pPercent, pOvershoot) / 2.0f;
    return EaseInBack(2*pPercent - 1, pOvershoot)/2 + 0.5;
}
*/


/**
 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing out: decelerating from zero velocity.
 *
 * @param t Current time (in frames or seconds).
 * @param a Amplitude.
 * @return The correct value.
 */
float FAnimation::EaseOutBounce(float pPercent, float pAmplitude)
{
    return HelperEaseOutBounce(pPercent, 1, pAmplitude);
}

/**
 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing in: accelerating from zero velocity.
 *
 * @param t Current time (in frames or seconds).
 * @param a Amplitude.
 * @return The correct value.
 
float FAnimation::EaseInBounce(float pPercent, float pAmplitude)
{
    return 1.0 - HelperEaseOutBounce(1.0-pPercent, 1.0, pAmplitude);
}
*/

/**
 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing in/out: acceleration until halfway, then deceleration.
 *
 * @param t Current time (in frames or seconds).
 * @param a Amplitude.
 * @return The correct value.
 
float FAnimation::EaseInOutBounce(float pPercent, float pAmplitude)
{
    if(pPercent < 0.5) return EaseInBounce (2*pPercent, pAmplitude)/2;
    else return (pPercent == 1.0) ? 1.0 : EaseOutBounce (2*pPercent - 1, pAmplitude)/2 + 0.5;
}
 */

/**
 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing out/in: deceleration until halfway, then acceleration.
 *
 * @param t Current time (in frames or seconds).
 * @param a Amplitude.
 * @return The correct value.
 
float FAnimation::EaseOutInBounce(float pPercent, float pAmplitude)
{
    if(pPercent < 0.5) return HelperEaseOutBounce(pPercent*2, 0.5, pAmplitude);
    return 1.0 - HelperEaseOutBounce (2.0-2*pPercent, 0.5, pAmplitude);
}
*/

// SmoothBegin blends Smooth and Linear Interpolation.
// Progress 0 - 0.3 : Smooth only
// Progress 0.3 - ~ 0.5 : Mix of Smooth and Linear
// Progress ~ 0.5 - 1 : Linear only

/**
 * Easing function that starts growing slowly, then incrEases in speed. At the end of the curve the speed will be constant.
 */
float FAnimation::EaseInCurve(float pPercent)
{
    const float sinProgress = HelperEaseSinProgress(pPercent);
    const float mix = HelperEaseSmoothBeginEndMixFactor(pPercent);
    return sinProgress * mix + pPercent * (1.0f - mix);

    //const qreal sinProgress = qt_sinProgress(t);
    //const qreal mix = qt_smoothBeginEndMixFactor(t);
    //return sinProgress * mix + t * (1 - mix);
}

/**
 * Easing function that starts growing steadily, then ends slowly. The speed will be constant at the beginning of the curve.
 */
float FAnimation::EaseOutCurve(float pPercent)
{
    const float sinProgress = HelperEaseSinProgress(pPercent);
    const float mix = HelperEaseSmoothBeginEndMixFactor(1 - pPercent);
    return sinProgress * mix + pPercent * (1 - mix);
    
    //const qreal sinProgress = qt_sinProgress(t);
    //const qreal mix = qt_smoothBeginEndMixFactor(1 - t);
    //return sinProgress * mix + t * (1 - mix);
}

/**
 * Easing function where the value grows sinusoidally. Note that the calculated end value will be 0 rather than 1.
 */
float FAnimation::EaseSineCurve(float pPercent)
{
    return (sin(((pPercent * PI * 2)) - PI_2) + 1) / 2;
    
    //return (qSin(((t * M_PI * 2)) - M_PI_2) + 1) / 2;
    
}

/**
 * Easing function where the value grows cosinusoidally. Note that the calculated start value will be 0.5 and the end value will be 0.5
 * contrary to the usual 0 to 1 easing curve.
 
float FAnimation::EaseCosineCurve(float pPercent)
{
    return (cos(((pPercent * PI * 2)) - PI_2) + 1) / 2;
    
    //return (qCos(((t * M_PI * 2)) - M_PI_2) + 1) / 2;
}
*/


float FAnimation::HelperEaseOutBounce(float pPercent, float c, float pAmplitude)
{
    if(pPercent == 1.0)
    {
        return c;
    }
    if(pPercent < (4/11.0))
    {
        return c*(7.5625*pPercent*pPercent);
    }
    else if(pPercent < (8/11.0))
    {
        pPercent -= (6/11.0);
        return -pAmplitude * (1. - (7.5625*pPercent*pPercent + .75)) + c;
    }
    else if(pPercent < (10/11.0))
    {
        pPercent -= (9/11.0);
        return -pAmplitude * (1. - (7.5625*pPercent*pPercent + .9375)) + c;
    }
    else
    {
        pPercent -= (21/22.0);
        return -pAmplitude * (1. - (7.5625*pPercent*pPercent + .984375)) + c;
    }
}

float FAnimation::HelperEaseOutElastic(float pPercent, float b, float c, float d, float a, float p)
{
    if(pPercent==0) return 0;
    if(pPercent==1) return c;
    
    float s;
    if(a < c)
    {
        a = c;
        s = p / 4.0f;
    }
    else
    {
        s = p / (2 * PI) * asin(c / a);
    }
    
    return (a*pow(2.0f,-10*pPercent) * sin( (pPercent-s)*(2*PI)/p ) + c);
}

/*
float FAnimation::HelperEaseInElastic(float pPercent, float b, float c, float d, float a, float p)
{
    if(pPercent==0) return b;
    float aAdjustedPercent = pPercent / d;
    if(aAdjustedPercent==1) return b+c;
    
    float s;
    if(a < fabsf(c))
    {
        a = c;
        s = p / 4.0f;
    }
    else
    {
        s = p / (2 * PI) * asin(c / a);
    }
    
    aAdjustedPercent -= 1.0f;
    return -(a*pow(2.0f,10*aAdjustedPercent) * sin((aAdjustedPercent*d-s)*(2*PI)/p )) + b;
}
*/

float FAnimation::HelperEaseSinProgress(float value)
{
    return sin((value * PI) - PI_2) / 2 + float(0.5);
}

float FAnimation::HelperEaseSmoothBeginEndMixFactor(float value)
{
    return MinC(MaxC(1 - value * 2 + float(0.3), float(0.0)), float(1.0));
    
    //return qMin(qMax(1 - value * 2 + qreal(0.3), qreal(0.0)), qreal(1.0));
    
}
