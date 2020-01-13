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
    
    FDrawNodeList                   mNodeList;
    
    bool                            mRefresh;
    
    float                           mLength;
    
};


#endif /* FTextureSnake_hpp */
