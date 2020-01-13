//
//  QuadSpewer.h
//  Digplex
//
//  Created by Nick Raptis on 9/23/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef QUAD_H
#define QUAD_H

#include "core_includes.h"

#include "FTexture.hpp"
//#include "FVertexBuffer.h"
#include "FPrimitive.hpp"
#include "FColor.hpp"

#define QUAD_INDEX_1 0
#define QUAD_INDEX_2 1
#define QUAD_INDEX_3 2
#define QUAD_INDEX_4 3

class FDrawQuad {
public:
	FDrawQuad();
	virtual ~FDrawQuad();
    
	FDrawNode                       mVertex[4];
    
	void                            Draw(FSprite *pSprite);
	void                            Draw(FSprite &pSprite);
    
    void                            DrawUncolored(FSprite *pSprite);

    void                            Draw();
    void                            DrawCorners();
    
    void                            DrawOutline();
    
    void                            Print();
    
    void                            SetQuad(float pStartX, float pStartY, float pEndX, float pEndY);
    void                            SetQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4);
    
    void                            SetRect(float pX, float pY, float pWidth, float pHeight);
    
    void                            SetTextureQuad(float pStartU, float pStartV, float pEndU, float pEndV);
    void                            SetTextureRect(FSprite *pSprite, float pX, float pY, float pWidth, float pHeight);
    
    void                            Copy(FDrawQuad *pQuad);
    
    void                            CopyXYZ(FDrawQuad *pQuad);
    void                            CopyUVW(FDrawQuad *pQuad);
    void                            CopyRGBA(FDrawQuad *pQuad);
    
    void                            Shift(float pX, float pY, float pZ);
    void                            Shift(float pX, float pY){Shift(pX, pY, 0.0f);}
    
    void                            RotateAndScale(float pDegrees, float pScale);
    void                            Rotate(float pDegrees);
    void                            Rotate(float pDegrees, float pCenterX, float pCenterY);
    void                            Scale(float pScale);
    void                            Translate(float pX, float pY);
    
    void                            SetTextureAspectFit(FSprite *pSprite);
    void                            SetTextureAspectFit(FSprite &pSprite){SetTextureAspectFit(&pSprite);}
    
    void                            SetTextureAspectFill(FSprite *pSprite);
    void                            SetTextureAspectFill(FSprite &pSprite){SetTextureAspectFill(&pSprite);}
    
    void                            ResetColor(float pAlpha=1.0f);
    void                            ResetColor(float pRed, float pGreen, float pBlue, float pAlpha=1.0f);
    
    void                            SetHexRGB(int pCorner, unsigned int pHexColor);
    void                            SetHexRGBA(int pCorner, unsigned int pHexColor);
    
    void                            SetHexRGB(unsigned int pHexColor);
    void                            SetHexRGBA(unsigned int pHexColor);
    
    void                            SetColorTop(float pRed, float pGreen, float pBlue, float pAlpha=1.0f){Corner1SetColor(pRed, pGreen, pBlue, pAlpha);Corner2SetColor(pRed, pGreen, pBlue, pAlpha);}
    void                            SetColorRight(float pRed, float pGreen, float pBlue, float pAlpha=1.0f){Corner2SetColor(pRed, pGreen, pBlue, pAlpha);Corner4SetColor(pRed, pGreen, pBlue, pAlpha);}
    void                            SetColorBottom(float pRed, float pGreen, float pBlue, float pAlpha=1.0f){Corner3SetColor(pRed, pGreen, pBlue, pAlpha);Corner4SetColor(pRed, pGreen, pBlue, pAlpha);}
    void                            SetColorLeft(float pRed, float pGreen, float pBlue, float pAlpha=1.0f){Corner1SetColor(pRed, pGreen, pBlue, pAlpha);Corner3SetColor(pRed, pGreen, pBlue, pAlpha);}
    
    void                            SetColorTop(FColor pColor){SetColorTop(pColor.mRed, pColor.mGreen, pColor.mBlue, pColor.mAlpha);}
    void                            SetColorRight(FColor pColor){SetColorRight(pColor.mRed, pColor.mGreen, pColor.mBlue, pColor.mAlpha);}
    void                            SetColorBottom(FColor pColor){SetColorBottom(pColor.mRed, pColor.mGreen, pColor.mBlue, pColor.mAlpha);}
    void                            SetColorLeft(FColor pColor){SetColorLeft(pColor.mRed, pColor.mGreen, pColor.mBlue, pColor.mAlpha);}
    
    void                            ColorFlipH();
    void                            ColorFlipV();
    
    void                            ColorMultiply(float pRed, float pGreen, float pBlue, float pAlpha);
    void                            ColorMultiplyAlpha(float pAlpha);
    
    void                            ColorSwap(int pIndex1, int pIndex2);
    
    void                            ColorDarkenAll(float pPercent);
    void                            ColorLightenAll(float pPercent);
    
    bool                            ContainsPoint(float pX, float pY);
    
    void                            TransformSpriteCorners(float pCenterX, float pCenterY, FSprite *pSprite, float pRotation, float pScale);
    
    inline void                     Corner1SetPos(float pX, float pY, float pZ){mVertex[QUAD_INDEX_1].mX=pX;mVertex[QUAD_INDEX_1].mY=pY;mVertex[QUAD_INDEX_1].mZ=pZ;}
    inline void                     Corner1SetPos(float pX, float pY){Corner1SetPos(pX, pY, 1.0f);}
    
    inline void                     Corner1SetX(float pX){mVertex[QUAD_INDEX_1].mX=pX;}
    inline void                     Corner1SetY(float pY){mVertex[QUAD_INDEX_1].mY=pY;}
    inline void                     Corner1SetZ(float pZ){mVertex[QUAD_INDEX_1].mZ=pZ;}
    
    inline void                     Corner1SetTextureCoord(float pU, float pV, float pW){mVertex[QUAD_INDEX_1].mU=pU;mVertex[QUAD_INDEX_1].mV=pV;mVertex[QUAD_INDEX_1].mW=pW;}
    inline void                     Corner1SetTextureCoord(float pU, float pV){Corner1SetTextureCoord(pU, pV, 0.0f);}
    inline void                     Corner1SetU(float pU){mVertex[QUAD_INDEX_1].mU=pU;}
    inline void                     Corner1SetV(float pV){mVertex[QUAD_INDEX_1].mV=pV;}
    inline void                     Corner1SetW(float pW){mVertex[QUAD_INDEX_1].mW=pW;}
    
    inline void                     Corner1SetColor(float pRed, float pGreen, float pBlue, float pAlpha=1.0f){mVertex[QUAD_INDEX_1].mR=pRed;mVertex[QUAD_INDEX_1].mG=pGreen;mVertex[QUAD_INDEX_1].mB=pBlue;mVertex[QUAD_INDEX_1].mA=pAlpha;}
    inline void                     Corner1SetColor(float pAlpha=1.0f){Corner1SetColor(1.0f, 1.0f, 1.0f, pAlpha);}
    
    inline void                     Corner1SetRed(float pRed){mVertex[QUAD_INDEX_1].mR=pRed;}
    inline void                     Corner1SetGreen(float pGreen){mVertex[QUAD_INDEX_1].mG=pGreen;}
    inline void                     Corner1SetBue(float pBlue){mVertex[QUAD_INDEX_1].mB=pBlue;}
    inline void                     Corner1SetAlpha(float pAlpha){mVertex[QUAD_INDEX_1].mA=pAlpha;}
    inline void                     Corner1SetHexRGB(unsigned int pColor){SetHexRGB(0, pColor);}
    inline void                     Corner1SetHexRGBA(unsigned int pColor){SetHexRGBA(0, pColor);}
    
    inline void                     Corner2SetPos(float pX, float pY, float pZ){mVertex[QUAD_INDEX_2].mX=pX;mVertex[QUAD_INDEX_2].mY=pY;mVertex[QUAD_INDEX_2].mZ=pZ;}
    inline void                     Corner2SetPos(float pX, float pY){Corner2SetPos(pX, pY, 2.0f);}
    
    inline void                     Corner2SetX(float pX){mVertex[QUAD_INDEX_2].mX=pX;}
    inline void                     Corner2SetY(float pY){mVertex[QUAD_INDEX_2].mY=pY;}
    inline void                     Corner2SetZ(float pZ){mVertex[QUAD_INDEX_2].mZ=pZ;}
    
    inline void                     Corner2SetTextureCoord(float pU, float pV, float pW){mVertex[QUAD_INDEX_2].mU=pU;mVertex[QUAD_INDEX_2].mV=pV;mVertex[QUAD_INDEX_2].mW=pW;}
    inline void                     Corner2SetTextureCoord(float pU, float pV){Corner2SetTextureCoord(pU, pV, 0.0f);}
    inline void                     Corner2SetU(float pU){mVertex[QUAD_INDEX_2].mU=pU;}
    inline void                     Corner2SetV(float pV){mVertex[QUAD_INDEX_2].mV=pV;}
    inline void                     Corner2SetW(float pW){mVertex[QUAD_INDEX_2].mW=pW;}
    
    inline void                     Corner2SetColor(float pRed, float pGreen, float pBlue, float pAlpha=2.0f){mVertex[QUAD_INDEX_2].mR=pRed;mVertex[QUAD_INDEX_2].mG=pGreen;mVertex[QUAD_INDEX_2].mB=pBlue;mVertex[QUAD_INDEX_2].mA=pAlpha;}
    inline void                     Corner2SetColor(float pAlpha=2.0f){Corner2SetColor(2.0f, 2.0f, 2.0f, pAlpha);}
    
    inline void                     Corner2SetRed(float pRed){mVertex[QUAD_INDEX_2].mR=pRed;}
    inline void                     Corner2SetGreen(float pGreen){mVertex[QUAD_INDEX_2].mG=pGreen;}
    inline void                     Corner2SetBue(float pBlue){mVertex[QUAD_INDEX_2].mB=pBlue;}
    inline void                     Corner2SetAlpha(float pAlpha){mVertex[QUAD_INDEX_2].mA=pAlpha;}
    inline void                     Corner2SetHexRGB(unsigned int pColor){SetHexRGB(1, pColor);}
    inline void                     Corner2SetHexRGBA(unsigned int pColor){SetHexRGBA(1, pColor);}
    
    
    
    inline void                     Corner3SetPos(float pX, float pY, float pZ){mVertex[QUAD_INDEX_3].mX=pX;mVertex[QUAD_INDEX_3].mY=pY;mVertex[QUAD_INDEX_3].mZ=pZ;}
    inline void                     Corner3SetPos(float pX, float pY){Corner3SetPos(pX, pY, 3.0f);}
    
    inline void                     Corner3SetX(float pX){mVertex[QUAD_INDEX_3].mX=pX;}
    inline void                     Corner3SetY(float pY){mVertex[QUAD_INDEX_3].mY=pY;}
    inline void                     Corner3SetZ(float pZ){mVertex[QUAD_INDEX_3].mZ=pZ;}
    
    inline void                     Corner3SetTextureCoord(float pU, float pV, float pW){mVertex[QUAD_INDEX_3].mU=pU;mVertex[QUAD_INDEX_3].mV=pV;mVertex[QUAD_INDEX_3].mW=pW;}
    inline void                     Corner3SetTextureCoord(float pU, float pV){Corner3SetTextureCoord(pU, pV, 0.0f);}
    inline void                     Corner3SetU(float pU){mVertex[QUAD_INDEX_3].mU=pU;}
    inline void                     Corner3SetV(float pV){mVertex[QUAD_INDEX_3].mV=pV;}
    inline void                     Corner3SetW(float pW){mVertex[QUAD_INDEX_3].mW=pW;}
    
    inline void                     Corner3SetColor(float pRed, float pGreen, float pBlue, float pAlpha=3.0f){mVertex[QUAD_INDEX_3].mR=pRed;mVertex[QUAD_INDEX_3].mG=pGreen;mVertex[QUAD_INDEX_3].mB=pBlue;mVertex[QUAD_INDEX_3].mA=pAlpha;}
    inline void                     Corner3SetColor(float pAlpha=3.0f){Corner3SetColor(3.0f, 3.0f, 3.0f, pAlpha);}
    
    inline void                     Corner3SetRed(float pRed){mVertex[QUAD_INDEX_3].mR=pRed;}
    inline void                     Corner3SetGreen(float pGreen){mVertex[QUAD_INDEX_3].mG=pGreen;}
    inline void                     Corner3SetBue(float pBlue){mVertex[QUAD_INDEX_3].mB=pBlue;}
    inline void                     Corner3SetAlpha(float pAlpha){mVertex[QUAD_INDEX_3].mA=pAlpha;}
    inline void                     Corner3SetHexRGB(unsigned int pColor){SetHexRGB(2, pColor);}
    inline void                     Corner3SetHexRGBA(unsigned int pColor){SetHexRGBA(2, pColor);}
    inline void                     Corner4SetPos(float pX, float pY, float pZ){mVertex[QUAD_INDEX_4].mX=pX;mVertex[QUAD_INDEX_4].mY=pY;mVertex[QUAD_INDEX_4].mZ=pZ;}
    inline void                     Corner4SetPos(float pX, float pY){Corner4SetPos(pX, pY, 4.0f);}
    inline void                     Corner4SetX(float pX){mVertex[QUAD_INDEX_4].mX=pX;}
    inline void                     Corner4SetY(float pY){mVertex[QUAD_INDEX_4].mY=pY;}
    inline void                     Corner4SetZ(float pZ){mVertex[QUAD_INDEX_4].mZ=pZ;}
    
    inline void                     Corner4SetTextureCoord(float pU, float pV, float pW){mVertex[QUAD_INDEX_4].mU=pU;mVertex[QUAD_INDEX_4].mV=pV;mVertex[QUAD_INDEX_4].mW=pW;}
    inline void                     Corner4SetTextureCoord(float pU, float pV){Corner4SetTextureCoord(pU, pV, 0.0f);}
    inline void                     Corner4SetU(float pU){mVertex[QUAD_INDEX_4].mU=pU;}
    inline void                     Corner4SetV(float pV){mVertex[QUAD_INDEX_4].mV=pV;}
    inline void                     Corner4SetW(float pW){mVertex[QUAD_INDEX_4].mW=pW;}
    
    inline void                     Corner4SetColor(float pRed, float pGreen, float pBlue, float pAlpha=4.0f){mVertex[QUAD_INDEX_4].mR=pRed;mVertex[QUAD_INDEX_4].mG=pGreen;mVertex[QUAD_INDEX_4].mB=pBlue;mVertex[QUAD_INDEX_4].mA=pAlpha;}
    inline void                     Corner4SetColor(float pAlpha=4.0f){Corner4SetColor(4.0f, 4.0f, 4.0f, pAlpha);}
    
    inline void                     Corner4SetRed(float pRed){mVertex[QUAD_INDEX_4].mR=pRed;}
    inline void                     Corner4SetGreen(float pGreen){mVertex[QUAD_INDEX_4].mG=pGreen;}
    inline void                     Corner4SetBue(float pBlue){mVertex[QUAD_INDEX_4].mB=pBlue;}
    inline void                     Corner4SetAlpha(float pAlpha){mVertex[QUAD_INDEX_4].mA=pAlpha;}
    inline void                     Corner4SetHexRGB(unsigned int pColor){SetHexRGB(3, pColor);}
    inline void                     Corner4SetHexRGBA(unsigned int pColor){SetHexRGBA(3, pColor);}
    
    inline float                    X1(){return mVertex[QUAD_INDEX_1].mX;}
    inline float                    Y1(){return mVertex[QUAD_INDEX_1].mY;}
    inline float                    Z1(){return mVertex[QUAD_INDEX_1].mZ;}
    inline float                    U1(){return mVertex[QUAD_INDEX_1].mU;}
    inline float                    V1(){return mVertex[QUAD_INDEX_1].mV;}
    inline float                    W1(){return mVertex[QUAD_INDEX_1].mW;}
    inline float                    X2(){return mVertex[QUAD_INDEX_2].mX;}
    inline float                    Y2(){return mVertex[QUAD_INDEX_2].mY;}
    inline float                    Z2(){return mVertex[QUAD_INDEX_2].mZ;}
    inline float                    U2(){return mVertex[QUAD_INDEX_2].mU;}
    inline float                    V2(){return mVertex[QUAD_INDEX_2].mV;}
    inline float                    W2(){return mVertex[QUAD_INDEX_2].mW;}
    inline float                    X3(){return mVertex[QUAD_INDEX_3].mX;}
    inline float                    Y3(){return mVertex[QUAD_INDEX_3].mY;}
    inline float                    Z3(){return mVertex[QUAD_INDEX_3].mZ;}
    inline float                    U3(){return mVertex[QUAD_INDEX_3].mU;}
    inline float                    V3(){return mVertex[QUAD_INDEX_3].mV;}
    inline float                    W3(){return mVertex[QUAD_INDEX_3].mW;}
    inline float                    X4(){return mVertex[QUAD_INDEX_4].mX;}
    inline float                    Y4(){return mVertex[QUAD_INDEX_4].mY;}
    inline float                    Z4(){return mVertex[QUAD_INDEX_4].mZ;}
    inline float                    U4(){return mVertex[QUAD_INDEX_4].mU;}
    inline float                    V4(){return mVertex[QUAD_INDEX_4].mV;}
    inline float                    W4(){return mVertex[QUAD_INDEX_4].mW;}
};



class FDrawQuadRay : public FDrawQuad
{
public:
    FDrawQuadRay();
    virtual ~FDrawQuadRay();
    
    virtual void					Draw(FSprite *pSprite);
    virtual void					Draw() { Draw(mSprite); }
    
    void                            SetStartPos(float pX, float pY);
    void                            SetStartPos(FVec2 pPos);
    
    void                            SetEndPos(float pX, float pY);
    void                            SetEndPos(FVec2 pPos);
    
    void                            SetAngle(float pDegrees);
    
    void                            SetLength(float pLength);
    
    void                            SetSprite(FSprite *pSprite);
    inline void                     SetSprite(FSprite &pSprite){SetSprite(&pSprite);}
    
    void                            SetWidthStart(float pWidth);
    void                            SetWidthEnd(float pWidth);
    
    void                            SetWidth(float pStartWidth, float pEndWidth);
    void                            SetWidth(float pWidth);
    
    void                            ComputeCorners();
    
    FSprite                         *mSprite;
    
    float                           mLength;
    float                           mAngle;
    
    float                           mStartWidth;
    float                           mEndWidth;
    
    FVec2                           mStartPos;
    FVec2                           mEndPos;
    
    FVec2                           mDir;
    FVec2                           mNormal;
};

class FDrawQuadGrid
{
public:
    FDrawQuadGrid();
    virtual ~FDrawQuadGrid();
    
    virtual void					Draw(FSprite *pSprite);
    virtual void					Draw(FSprite &pSprite){Draw(&pSprite);}
    virtual void					Draw();
    
    void                            Reset();
    void                            Clear();
    
    void                            Size(int pWidth, int pHeight);
    
    void                            SetSprite(FSprite *pSprite);
    void                            SetSprite(FSprite &pSprite){SetSprite(&pSprite);}
    FSprite                         *mSprite;
    
    FDrawNodeList                   mNodeList;
    
    void                            Generate9x9(FSprite &pSprite, float pX, float pY, float pWidth, float pHeight, float pInsetTop, float pInsetRight, float pInsetBottom, float pInsetLeft);
    void                            Generate9x9(FSprite &pSprite, float pX, float pY, float pWidth, float pHeight, float pInset);
    
    
    
    void                            SetXYZ(int pGridX, int pGridY, float pX, float pY, float pZ);
    void                            SetUVW(int pGridX, int pGridY, float pU, float pV, float pW);
    void                            SetRGBA(int pGridX, int pGridY, float pRed, float pGreen, float pBlue, float pAlpha);
    
    float                           *mXYZBase;
    float                           *mUVWBase;
    float                           *mRGBABase;
    
    float                           **mXYZ;
    float                           **mUVW;
    float                           **mRGBA;
    
    int                             mWidth;
    int                             mHeight;
    
    bool                            mRefresh;
};




#endif

