//
//  FAnimation.h
//  Graveyard
//
//  Created by Nick Raptis on 2/16/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_FANIMATION_H
#define FRAMEWORK_FANIMATION_H

#include "FString.hpp"

#define ANIMATION_TYPE_AUTOMATIC -1
#define ANIMATION_TYPE_LINEAR 0

/////////////////////////////
//
//      Smooth Group
//
//Smooth Slow-Downs
#define ANIMATION_TYPE_EASE_OUT_SIN 1
#define ANIMATION_TYPE_EASE_OUT_IN_SIN 2
#define ANIMATION_TYPE_EASE_IN_CURVE 3

//Smooth Speed-Ups
#define ANIMATION_TYPE_EASE_IN_SIN 4
#define ANIMATION_TYPE_EASE_IN_OUT_SIN 5
#define ANIMATION_TYPE_EASE_OUT_CURVE 6

//Smooth Stuck, ZOOM, Stuck..
#define ANIMATION_TYPE_EASE_IN_OUT_EXPO 7
#define EASE_IN_OUT_QUART 8
#define EASE_OUT_IN_QUART 9
//
/////////////////////////////


/////////////////////////////
//
//      Slow Down Group
//
//Slowing Down..
#define ANIMATION_TYPE_EASE_OUT_CIRC 10
#define ANIMATION_EASE_OUT_ELASTIC 11
#define ANIMATION_TYPE_EASE_OUT_BACK 12
#define ANIMATION_TYPE_OVERSHOOT (ANIMATION_TYPE_EASE_OUT_BACK)
#define ANIMATION_TYPE_OVERSHOOT_MORE 13
#define ANIMATION_TYPE_BOUNCE 14
#define ANIMATION_TYPE_BOUNCE_MORE 15
#define ANIMATION_TYPE_EASE_OUT_QUART 16 //Really fast, then GLUE
#define ANIMATION_TYPE_EASE_OUT_EXPO 17
//
/////////////////////////////


/////////////////////////////
//
//      Speed Up Group
//
//Speeding Up.. (Slow, then FAST)
#define ANIMATION_TYPE_EASE_IN_CIRC 18
#define ANIMATION_TYPE_EASE_IN_OUT_CIRC 19
#define ANIMATION_TYPE_EASE_IN_EXPO 20
#define ANIMATION_TYPE_EASE_IN_QUART 21 //Sticky like tar, then ZEWWWWWWW!!!
//
/////////////////////////////

#include "FVec2.hpp"

class FAnimation {
public:
    
    FAnimation();
    virtual ~FAnimation();
    
    static float                                    SplineInterpolate(float pPercent, float pStartValue, float pEndValue, float pStartTan, float pEndTan);
    
    
    
    
	static float									ApplyFunction(int pFunction, float pPercent);
    
    //The sexiest ones:
    static float                                   EaseInOutExpo(float pPercent);
    static float                                   EaseOutCurve(float pPercent);
    static float                                   EaseInOutQuad(float pPercent);
    static float                                   EaseOutInQuad(float pPercent);
    static float                                   EaseInOutCubic(float pPercent);
    static float                                   EaseOutInCubic(float pPercent);
    
    static float                                   EaseInQuart(float pPercent);
    static float                                   EaseOutQuart(float pPercent);
    static float                                   EaseInOutQuart(float pPercent);
    static float                                   EaseOutInQuart(float pPercent);
    static float                                   EaseInQuint(float pPercent);
    static float                                   EaseOutQuint(float pPercent);
    static float                                   EaseInOutQuint(float pPercent);
    static float                                   EaseOutInQuint(float pPercent);
    
    static float                                   EaseInSine(float pPercent);
    static float                                   EaseOutSine(float pPercent);
    static float                                   EaseInOutSine(float pPercent);
    static float                                   EaseOutInSine(float pPercent);
    static float                                   EaseInExpo(float pPercent);
    static float                                   EaseOutExpo(float pPercent);
    static float                                   EaseOutInExpo(float pPercent);
    static float                                   EaseInCirc(float pPercent);
    static float                                   EaseOutCirc(float pPercent);
    static float                                   EaseInOutCirc(float pPercent);
    static float                                   EaseInCurve(float pPercent);
    static float                                   EaseSineCurve(float pPercent);
    
    static float                                   EaseOutElastic(float pPercent, float pAmplitude = 1.0f, float pPeriod = 0.5f);
    
    static float                                   EaseOutBack(float pPercent, float pOvershoot);
    static float                                   Overshoot(float pPercent) { return EaseOutBack(pPercent, 1.70158f); }
    static float                                   OvershootMore(float pPercent) { return EaseOutBack(pPercent, 2.5f); }
    
    static float                                   EaseOutBounce(float pPercent, float pAmplitude);
    static float                                   Bounce(float pPercent) { return EaseOutBounce(pPercent, 0.23f); }
    static float                                   BounceMore(float pPercent) { return EaseOutBounce(pPercent, 0.5f); }
    
    static float                                   HelperEaseOutElastic(float pPercent, float b, float c, float d, float pAmplitude, float pPeriod);
    static float                                   HelperEaseOutBounce(float pPercent, float c, float pAmplitude);
    static float                                   HelperEaseSinProgress(float pValue);
    static float                                   HelperEaseSmoothBeginEndMixFactor(float pValue);
};

#endif
