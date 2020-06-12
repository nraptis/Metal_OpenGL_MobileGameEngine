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

float FAnimation::SplineInterpolate(float pPercent, float pStartValue, float pEndValue, float pStartTan, float pEndTan) {
    pEndTan = -pEndTan;

    float aCoef[3];
    
    aCoef[0] = pStartTan;
    aCoef[1] = 3.0f * (pEndValue-pStartValue) - 2.0f * pStartTan - pEndTan;
    aCoef[2] = 2.0f * (pStartValue - pEndValue) + pStartTan + pEndTan;
    
    float aPercent = pPercent;
    float aPercent2 = aPercent * pPercent;
    float aPercent3 = aPercent2 * pPercent;
    
    return pStartValue + aCoef[0]*aPercent + aCoef[1]*aPercent2 + aCoef[2]*aPercent3;
}

float FAnimation::ApplyFunction(int pFunction, float pPercent) {
    float aResult = pPercent;
    if (pFunction == ANIMATION_TYPE_EASE_OUT_SIN) { aResult = EaseOutSine(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_OUT_IN_SIN) { aResult = EaseOutInSine(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_IN_CURVE) { aResult = EaseInCurve(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_IN_SIN) { aResult = EaseInSine(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_IN_OUT_SIN) { aResult = EaseInOutSine(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_OUT_CURVE) { aResult = EaseOutCurve(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_IN_OUT_EXPO) { aResult = EaseInOutExpo(pPercent); }
    else if (pFunction == EASE_IN_OUT_QUART) { aResult = EaseInOutQuart(pPercent); }
    else if (pFunction == EASE_OUT_IN_QUART) { aResult = EaseOutInQuart(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_OUT_CIRC) { aResult = EaseOutCirc(pPercent); }
    else if (pFunction == ANIMATION_EASE_OUT_ELASTIC) { aResult = EaseOutElastic(pPercent); }
    else if (pFunction == ANIMATION_TYPE_OVERSHOOT) { aResult = Overshoot(pPercent); }
    else if (pFunction == ANIMATION_TYPE_OVERSHOOT_MORE) { aResult = OvershootMore(pPercent); }
    else if (pFunction == ANIMATION_TYPE_BOUNCE) { aResult =  Bounce(pPercent); }
    else if (pFunction == ANIMATION_TYPE_BOUNCE_MORE) { aResult = BounceMore(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_OUT_QUART) { aResult = EaseOutQuart(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_OUT_EXPO) { aResult = EaseOutExpo(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_IN_CIRC) { aResult = EaseInCirc(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_IN_OUT_CIRC) { aResult = EaseInOutCirc(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_IN_EXPO) { aResult = EaseInExpo(pPercent); }
    else if (pFunction == ANIMATION_TYPE_EASE_IN_QUART) { aResult = EaseInQuart(pPercent); }
    return aResult;
}

float FAnimation::EaseInOutQuad(float pPercent) {
    pPercent *= 2.0f;
    if(pPercent < 1.0f) {
        return pPercent * pPercent / 2.0f;
    } else {
        pPercent -= 1.0f;
        return -0.5f * (pPercent * (pPercent - 2.0f) - 1.0f);
    }
}

float EaseInQuad(float pPercent) {
    return pPercent * pPercent;
}

float EaseOutQuad(float pPercent) {
    return -pPercent * (pPercent - 2.0f);
}

float FAnimation::EaseOutInQuad(float pPercent) {
    if (pPercent < 0.5f) {
        return EaseOutQuad(pPercent * 2.0f) * 0.5f;
    } else {
        return EaseInQuad((2.0f * pPercent) - 1.0f) * 0.5f + 0.5f;
    }
}

float FAnimation::EaseInOutCubic(float pPercent) {
    pPercent *= 2.0f;
    if (pPercent < 1.0f) {
        return 0.5f * pPercent * pPercent * pPercent;
    } else {
        pPercent -= 2.0f;
        return 0.5f * (pPercent * pPercent * pPercent + 2.0f);
    }
}

float EaseInCubic(float pPercent) {
    return pPercent * pPercent * pPercent;
}

float EaseOutCubic(float pPercent) {
    pPercent -= 1.0f;
    return pPercent * pPercent * pPercent + 1.0f;
}

float FAnimation::EaseOutInCubic(float pPercent) {
    if (pPercent < 0.5f) {
        return EaseOutCubic (2.0f * pPercent) * 0.5f;
    } else {
        return EaseInCubic(2.0f * pPercent - 1.0f) * 0.5f + 0.5f;
    }
}

float FAnimation::EaseInQuart(float pPercent) {
    return pPercent * pPercent * pPercent * pPercent;
}

float FAnimation::EaseOutQuart(float pPercent) {
    pPercent -= 1.0f;
    return -(pPercent * pPercent * pPercent * pPercent - 1.0f);
}

float FAnimation::EaseInOutQuart(float pPercent) {
    pPercent *= 2.0f;
    if (pPercent < 1.0f) {
        return 0.5f * pPercent * pPercent * pPercent * pPercent;
    } else {
        pPercent -= 2.0f;
        return -0.5f * (pPercent * pPercent * pPercent * pPercent - 2.0f);
    }
}

float FAnimation::EaseOutInQuart(float pPercent) {
    if (pPercent < 0.5f) {
        return EaseOutQuart(2.0f * pPercent) * 0.5f;
    } else {
        return EaseInQuart(2.0f * pPercent - 1.0f) * 0.5f + 0.5f;
    }
}

float FAnimation::EaseInQuint(float pPercent) {
    return pPercent * pPercent * pPercent * pPercent * pPercent;
}

float FAnimation::EaseOutQuint(float pPercent) {
    pPercent -= 1.0f;
    return pPercent * pPercent * pPercent * pPercent * pPercent + 1.0f;
}

float FAnimation::EaseInOutQuint(float pPercent) {
    pPercent *= 2.0f;
    if (pPercent < 1.0f) {
        return 0.5f * pPercent * pPercent * pPercent * pPercent * pPercent;
    } else {
        pPercent -= 2.0f;
        return 0.5f * (pPercent * pPercent * pPercent * pPercent * pPercent + 2);
    }
}

float FAnimation::EaseOutInQuint(float pPercent) {
    if (pPercent < 0.5f) {
        return EaseOutQuint(2.0f * pPercent) * 0.5f;
    } else {
        return EaseInQuint(2.0f * pPercent - 1.0f) * 0.5f + 0.5f;
    }
}

float FAnimation::EaseInSine(float pPercent) {
    if (pPercent >= 1.0f) {
        return 1.0f;
    } else {
        return -cosf(pPercent * PI_2) + 1.0f;
    }
}

float FAnimation::EaseOutSine(float pPercent) {
    return sinf(pPercent * PI_2);
}

float FAnimation::EaseInOutSine(float pPercent) {
    return -0.5f * (cosf(PI * pPercent) - 1.0f);
}

float FAnimation::EaseOutInSine(float pPercent) {
    if (pPercent < 0.5f) {
        return EaseOutSine (2.0f * pPercent) * 0.5f;
    } else {
        return EaseInSine(2.0f * pPercent - 1.0f) * 0.5f + 0.5f;
    }
}

float FAnimation::EaseInExpo(float pPercent) {
    if ((pPercent == 0.0f || pPercent == 1.0f)) {
        return pPercent;
    } else {
        return powf(2.0f, 10.0f * (pPercent - 1.0f)) - 0.001f;
    }
}

float FAnimation::EaseOutExpo(float pPercent) {
    if (pPercent == 1.0f) {
        return 1.0f;
    } else {
        return 1.001f * (-powf(2.0f, -10.0f * pPercent) + 1.0f);
    }
}

float FAnimation::EaseInOutExpo(float pPercent) {
    if (pPercent <= 0.0f) { return 0.0f; }
    if (pPercent >= 1.0f) { return 1.0f; }
    pPercent *= 2.0f;
    if (pPercent < 1.0f) {
        return 0.5f * powf(2.0f, 10.0f * (pPercent - 1.0f)) - 0.0005f;
    } else {
        return 0.5f * 1.0005f * (-powf(2.0f, -10.0f * (pPercent - 1.0f)) + 2.0f);
    }
}

float FAnimation::EaseOutInExpo(float pPercent) {
    if (pPercent < 0.5f) {
        return EaseOutExpo (2.0f * pPercent) * 0.5f;
    } else {
        return EaseInExpo(2.0f * pPercent - 1.0f) * 0.5f + 0.5f;
    }
}

float FAnimation::EaseInCirc(float pPercent) {
    return -(sqrtf(1.0f - pPercent * pPercent) - 1.0f);
}

float FAnimation::EaseOutCirc(float pPercent) {
    pPercent -= 1.0f;
    return sqrtf(1.0f - pPercent * pPercent);
}

float FAnimation::EaseInOutCirc(float pPercent) {
    pPercent *= 2.0f;
    if (pPercent < 1.0f) {
        return -0.5f * (sqrtf(1.0f - pPercent*pPercent) - 1.0f);
    } else {
        pPercent -= 2.0f;
        return 0.5f * (sqrtf(1.0f - pPercent*pPercent) + 1.0f);
    }
}

float FAnimation::EaseOutElastic(float pPercent, float a, float p) {
    return HelperEaseOutElastic(EaseInCirc(pPercent), 0.0f, 1.0f, 1.0f, a, p);
}

float FAnimation::EaseOutBack(float pPercent, float pOvershoot) {
    pPercent -= 1.0f;
    return pPercent * pPercent * ((pOvershoot + 1.0f) * pPercent + pOvershoot) + 1.0f;
}

float FAnimation::EaseOutBounce(float pPercent, float pAmplitude) {
    return HelperEaseOutBounce(pPercent, 1.0f, pAmplitude);
}

float FAnimation::EaseInCurve(float pPercent) {
    const float aSinProgress = HelperEaseSinProgress(pPercent);
    const float aMix = HelperEaseSmoothBeginEndMixFactor(pPercent);
    return aSinProgress * aMix + pPercent * (1.0f - aMix);
}

float FAnimation::EaseOutCurve(float pPercent) {
    const float aSinProgress = HelperEaseSinProgress(pPercent);
    const float aMix = HelperEaseSmoothBeginEndMixFactor(1.0f - pPercent);
    return aSinProgress * aMix + pPercent * (1.0f - aMix);
}

float FAnimation::EaseSineCurve(float pPercent) {
    return (sinf(((pPercent * PI2)) - PI_2) + 1.0f) / 2.0f;
}

float FAnimation::HelperEaseOutBounce(float pPercent, float c, float pAmplitude) {
    if (pPercent >= 1.0f) {
        return c;
    }
    if (pPercent < (4.0f / 11.0f)) {
        return c * (7.5625f * pPercent * pPercent);
    } else if (pPercent < (8.0f / 11.0f)) {
        pPercent -= (6.0f / 11.0f);
        return -pAmplitude * (1.0f - (7.5625f * pPercent * pPercent + 0.75f)) + c;
    } else if (pPercent < (10.0f / 11.0f)) {
        pPercent -= (9.0f / 11.0f);
        return -pAmplitude * (1.0f - (7.5625f * pPercent * pPercent + 0.9375f)) + c;
    } else {
        pPercent -= (21.0f / 22.0f);
        return -pAmplitude * (1.0f - (7.5625f * pPercent * pPercent + 0.984375f)) + c;
    }
}

float FAnimation::HelperEaseOutElastic(float pPercent, float b, float c, float d, float a, float p) {
    if (pPercent <= 0.0f) { return 0.0f; }
    if (pPercent >= 1.0f) { return c; }
    float s = 0.0f;
    if (a < c) {
        a = c;
        s = p / 4.0f;
    } else {
        s = p / (PI2) * asinf(c / a);
    }
    return (a * powf(2.0f, -10.0f * pPercent) * sinf((pPercent - s) * (PI2) / p ) + c);
}

float FAnimation::HelperEaseSinProgress(float pValue) {
    return sinf((pValue * PI) - PI_2) / 2.0f + 0.5f;
}

float FAnimation::HelperEaseSmoothBeginEndMixFactor(float pValue) {
    return MinC(MaxC(1.0f - pValue * 2.0f + 0.3f, 0.0f), 1.0f);
}
