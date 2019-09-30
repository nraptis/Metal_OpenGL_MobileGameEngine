/*
 *  FSlider.hpp
 *  Fly Swatter
 *
 *  Created by Nick Raptis on 12/31/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#ifndef FRAMEWORK_SLIDER_H
#define FRAMEWORK_SLIDER_H

#include "FSprite.hpp"
#include "FCanvas.hpp"

class FSlider : public FCanvas {
public:
	FSlider();
	virtual ~FSlider();

    virtual void                            Draw();

    virtual void                            TouchDown(float pX, float pY, void *pData);
	virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    void                                    SetMin(float pMin);
    void                                    SetMax(float pMax);
    void                                    SetRange(float pMin, float pMax);
    
    void                                    ForceValue(float pValue);
	float                                   GetValue();
	void                                    SetValue(float pValue);

    float                                   GetRotationValue();
    void                                    SetRotationValue(float pDegrees);
    
    void                                    SetThumb(float pX, float pY, float pWidth, float pHeight);

    float                                   mThumbX;
    float                                   mThumbY;
    float                                   mThumbWidth;
    float                                   mThumbHeight;
    
    void                                    *mClickData;
    float                                   mClickStartThumbX;
    float                                   mClickStartThumbY;
    
    float                                   mClickStartTouchX;
    float                                   mClickStartTouchY;
    
    float                                   mThumbBufferLeft;
    float                                   mThumbBufferRight;
    
    float                                   mMin;
    float                                   mMax;
    
    float                                   mValue;
    float                                   mPercent;
};

#endif
