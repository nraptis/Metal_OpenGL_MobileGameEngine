//
//  FQuad.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef __DigMMMac__FQuad__
#define __DigMMMac__FQuad__

#include "FSprite.hpp"

class FQuad {
public:
    FQuad();
    ~FQuad();

    float                               mX[4];
    float                               mY[4];
    
    void                                Set(FQuad *pQuad);
    void                                Set(FQuad &pQuad){Set(&pQuad);}
    void                                Set(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4);
    void                                Set(float pStartX, float pStartY, float pEndX, float pEndY);
    
    void                                SetRect(float pX, float pY, float pWidth, float pHeight);

    void                                Add(FQuad *pQuad);
    void                                Add(FQuad &pQuad) { Add(&pQuad); }
    void                                Add(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4);
    
    
    void                                SetCenter(float pX, float pY);
    void                                SetCenter();
    
    
    float                               CenterX();
    float                               CenterY();
    
    static void                         Convert(float pX, float pY, FQuad *pQuad, FQuad *pTargetQuad, float &pResultX, float &pResultY);
    
    void                                Transform(float pScaleX, float pScaleY, float pRotation);
    void                                Rotate(float pDegrees);
    void                                Rotate(float pDegrees, float pCenterX, float pCenterY);
    void                                Scale(float pScale);
    void                                Translate(float pX, float pY);

    inline float                        X1(){return mX[0];}
    inline float                        Y1(){return mY[0];}
    
    inline float                        X2(){return mX[1];}
    inline float                        Y2(){return mY[1];}
    
    inline float                        X3(){return mX[2];}
    inline float                        Y3(){return mY[2];}
    
    inline float                        X4(){return mX[3];}
    inline float                        Y4(){return mY[3];}
    
    
    void                                DrawMarkers();
    void                                Draw(FSprite *pSprite);
    
};

#endif
