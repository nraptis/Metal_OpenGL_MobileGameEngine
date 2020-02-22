//
//  FTextureSnake.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 1/8/20.
//  Copyright © 2020 Froggy Studios. All rights reserved.
//

#ifndef FTextureSnake_hpp
#define FTextureSnake_hpp

#include "FSprite.hpp"
#include "FPrimitive.hpp"

//The rules of texture snake.

//1.) Make sure you add enough points, to cover each image length with 4+ points.
//2.) Favor "Reset" over "Clear" if you are changing the texture snake...
//3.) If you are using a bundled image, please bundle it with mInset > 1, or there will be jaggy connections.

// Q: Why does it work THIS WAY instead of just using wrap?
// A: Because it supports bundled textures and non-power-2 textures.

class FTextureSnake {
public:
    FTextureSnake();
    virtual ~FTextureSnake();
    
    void                            Draw();
    void                            DrawMarkers();
    
    void                            Reset();
    void                            Clear();
    
    void                            Size(int pSize);
    int                             mCount;
    int                             mSize;
    
    float                           mOffsetU; // [0..1]
    
    void                            SetPoint(int pIndex, float pX, float pY);
    void                            AddPoint(float pX, float pY);
    
    void                            Generate();
    
    void                            GenerateWithFixedNormals(float pNormX, float pNormY);
    
    float                           *mCenterX;
    float                           *mCenterY;
    
    float                           *mDirX;
    float                           *mDirY;
    
    float                           *mNormX;
    float                           *mNormY;
    
    float                           *mU;
    float                           *mV;
    
    float                           *mDist;
    float                           *mPercent;
    
    void                            SetSprite(FSprite *pSprite);
    inline void                     SetSprite(FSprite &pSprite){SetSprite(&pSprite);}
    
    FSprite                         *mSprite;
    
    float                           mWidthFactor;
    
    float                           mScale;
    
    FDrawNodeList                   mNodeList;
    
    bool                            mRefresh;
    
    float                           mLength;
    
private:
    
    //Only do this after the initial generation step...
    void                            GenerateDrawNodeList();
    
};


#endif /* FTextureSnake_hpp */
