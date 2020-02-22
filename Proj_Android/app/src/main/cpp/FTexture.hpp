//
//  FTexture.h
//  Graveyard
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_TEXTURE_H
#define FRAMEWORK_TEXTURE_H

#define SET_TEXTURE_BODY if(mTexture){if(pTexture != mTexture){if(gTextureCache.mAutoMode == true)gTextureCache.TextureBindRemove(mTexture);mTexture = 0;}}if(pTexture){mTexture = pTexture;if(gTextureCache.mAutoMode == true)gTextureCache.TextureBindAdd(mTexture);}

#include "FString.hpp"

class FSprite;
class FImage;
class FTexture {
public:
    FTexture(const char *pFileName);
    virtual ~FTexture();
    
    FString                                 mFileName;

    void                                    Load(FImage *pImage);
    void                                    Realize();
    void                                    Unload();
    
    //For METAL this will reference internal texture table stored on graphics pipe.
    int                                     mBindIndex;
    
    bool                                    mDidFailLoad;
    bool                                    mDidUnload;
    
    int                                     mWidth;
    int                                     mHeight;
    
    int                                     mOffsetX;
    int                                     mOffsetY;
    
    int                                     mExpandedWidth;
    int                                     mExpandedHeight;
    
    int                                     mScale;

    float                                   GetStartU();
    float                                   GetStartV();

    float                                   GetEndU();
    float                                   GetEndV();
};

class FTextureRect {
public:
    
    FTextureRect();
    virtual ~FTextureRect();
    
    float                                   mPositions[8];
    float                                   mTextureCoords[8];
    
    void                                    Set(FTexture *pTexture, float pX=0, float pY=0);
    
    inline float                            GetStartU(){return mTextureCoords[0];}
    inline float                            GetStartV(){return mTextureCoords[1];}
    inline float                            GetEndU(){return mTextureCoords[6];}
    inline float                            GetEndV(){return mTextureCoords[7];}
    
    inline float                            GetStartX(){return mPositions[0];}
    inline float                            GetStartY(){return mPositions[1];}
    inline float                            GetEndX(){return mPositions[6];}
    inline float                            GetEndY(){return mPositions[7];}

    inline void                             SetStartU(float pU){mTextureCoords[0]=pU;mTextureCoords[4]=pU;}
    inline void                             SetStartV(float pV){mTextureCoords[1]=pV;mTextureCoords[3]=pV;}
    inline void                             SetEndU(float pU){mTextureCoords[6]=pU;mTextureCoords[2]=pU;}
    inline void                             SetEndV(float pV){mTextureCoords[7]=pV;mTextureCoords[5]=pV;}
    
    inline void                             SetStartX(float pX){mPositions[0]=pX;mPositions[4]=pX;}
    inline void                             SetStartY(float pY){mPositions[1]=pY;mPositions[3]=pY;}
    inline void                             SetEndX(float pX){mPositions[6]=pX;mPositions[2]=pX;}
    inline void                             SetEndY(float pY){mPositions[7]=pY;mPositions[5]=pY;}
    
    void                                    SetUVQuad(float pStartU, float pStartV, float pEndU, float pEndV);
    void                                    SetUVRect(float pStartU, float pStartV, float pWidthU, float pHeightV);
    
    void                                    SetQuad(float pStartX, float pStartY, float pEndX, float pEndY);
    void                                    SetRect(float pStartX, float pStartY, float pWidth, float pHeight);
    
    void                                    SetQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4);
};

class FTextureTriangle {
public:
    
    FTextureTriangle();
    virtual ~FTextureTriangle();
    
    float                                   mTextureCoords[6];
    float                                   mPositions[6];
    
    void                                    SetXYTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3);
    void                                    SetUVTriangle(float pU1, float pV1, float pU2, float pV2, float pU3, float pV3);
};

#endif /* defined(__Graveyard__FTexture__) */
