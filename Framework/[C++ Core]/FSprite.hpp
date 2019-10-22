#ifndef FSprite_H
#define FSprite_H

#include "FImage.hpp"
#include "FImageBundler.h"
#include "FTexture.hpp"
#include "FString.hpp"
#include "FBuffer.hpp"
#include "FVec2.hpp"

class FTexture;

class FSprite {
public:
	FSprite();
	~FSprite();
    
    
    float                                   mWidth;
    float                                   mHeight;
    
    FTextureRect                            mTextureRect;
    
    //int                                     mBufferIndexPosition;
    //int                                     mBufferIndexTextureCoords;
    
    //void                                    WriteBuffers();
    //void                                    BindBuffers();
    
    
    FString                                 mFileName;
    
    
    
    

	void                                    Load(char *pName, FImageBundler *pBundler);
	inline void                             Load(const char *pFile, FImageBundler *pBundler) { Load((char*)pFile,pBundler); }
    inline void                             Load(FString pFile, FImageBundler *pBundler) { Load(pFile.c(),pBundler); }
    
	inline void                             Load(FString pFile) { Load(pFile.c()); }
	inline void                             Load(const char *pFile) { Load((char*)pFile); }
	void                                    Load(char *pFile);
    
    void                                    LoadN(const char *pFileStart, int pIndex);
    void                                    LoadN(const char *pFileStart, int pIndex, const char *pFileEnd);
    void                                    LoadN(const char *pFileStart, int pIndex1, const char *pFileEnd, int pIndex2);
    void                                    LoadN(const char *pFileStart, int pIndex1, const char *pFileMiddle, int pIndex2, const char *pFileEnd);
    
    void                                    LoadNode(FImageBundler *pImageBundler, FImageBundlerLoadNode *pNode);
    
    void                                    Load(FImage *pImage);
    void                                    Load(FImage *pImage, int pX, int pY, int pWidth, int pHeight);
    
    void                                    Load(FTexture *pTexture);
    void                                    Load(FTexture *pTexture, int pX, int pY, int pWidth, int pHeight);

    bool                                    DidLoad();
    
    void                                    SetTexture(FTexture *pTexture);
    FTexture                                *mTexture;
    
    FBuffer                                 *mBufferPositions;
    FBuffer                                 *mBufferTextureCoords;
    //If we need to dump our texture rect back into our buffer,
    //this is how we can do it...
    void                                    WriteBuffers();
    
    bool                                    mDidLoad;
    bool                                    mDidLoadFromBundle;
    bool                                    mDidLoadFromResource;
    bool                                    mDidLoadSingle;

	void                                    Kill();

	void                                    Draw();
	void                                    Draw(float pX, float pY);
	void                                    Draw(float pX, float pY, float pScale, float pRotation=0);
    void                                    Draw(float pX, float pY, float pScale, float pRotationDegrees, int pFacing);
	inline void                             Draw(FVec2 pPosition){Draw(pPosition.mX,pPosition.mY);}
	inline void                             Draw(FVec2 pPosition, float pScale, float pRotationDegrees=0){Draw(pPosition.mX,pPosition.mY,pScale,pRotationDegrees);}

    void                                    DrawScaled(float pX, float pY, float pScale);
    void                                    DrawScaled(float pX, float pY, float pScaleX, float pScaleY);
    
    void                                    DrawScaled(float pX, float pY, float pScaleX, float pScaleY, float pRotation);
    
    
    inline void                             DrawScaled(FVec2 pPosition, float pScale){DrawScaled(pPosition.mX,pPosition.mY, pScale);}
    inline void                             DrawScaled(FVec2 pPosition, float pScaleX, float pScaleY){DrawScaled(pPosition.mX,pPosition.mY, pScaleX, pScaleY);}
    
    void                                    DrawRotated(float pX, float pY, float pRotation);
    inline void                             DrawRotated(FVec2 pPosition, float pRotation){DrawRotated(pPosition.mX,pPosition.mY, pRotation);}

    void                                    DrawAngleRange(float pX, float pY, float pScale, float pRotation, float pAngleStart, float pAngleEnd);

    void                                    DrawTripletH(float pX, float pY, float pInsetLeft, float pInsetRight, float pLength, bool pDrawLeft=true, bool pDrawMiddle=true, bool pDrawRight=true);
    
    void                                    DrawTripletHProgress(float pX, float pY, float pInsetLeft, float pInsetRight, float pLength,
    float pProgressInsetLeft, float pProgressInsetRight, float pProgress);
    
    
    
    void                                    Draw9x9(float pX, float pY, float pWidth, float pHeight, float pScale, float pRotation, float pInsetTop, float pInsetRight, float pInsetBottom, float pInsetLeft);
	
	void                                    DrawFlippedH(float pX, float pY);
	void                                    DrawFlippedH(float pX, float pY, float pScale, float pRotationDegrees=0);
	inline void                             DrawFlippedH(FVec2 pPos){DrawFlippedH(pPos.mX,pPos.mY);}
	inline void                             DrawFlippedH(FVec2 pPos, float pScale, float pRotationDegrees=0){DrawFlippedH(pPos.mX,pPos.mY,pScale,pRotationDegrees);}
	
	void                                    DrawFlippedV(float pX, float pY);
	void                                    DrawFlippedV(float pX, float pY, float pScale, float pRotationDegrees=0);
	inline void                             DrawFlippedV(FVec2 pPos){DrawFlippedV(pPos.mX,pPos.mY);}
	inline void                             DrawFlippedV(FVec2 pPos, float pScale, float pRotationDegrees=0){DrawFlippedV(pPos.mX,pPos.mY,pScale,pRotationDegrees);}
	
	
	void                                    Center(float pX, float pY);
	void                                    Center(FVec2 pPosition) { Center(pPosition.mX, pPosition.mY); }
    
    void                                    DrawShiftedCorners(float pX, float pY, float pScale, float pRotationDegrees, FVec2 pShiftUL, FVec2 pShiftUR, FVec2 pShiftDL, FVec2 pShiftDR);

    void                                    DrawSliceTo(FTextureRect *pTextureRect, float pStartX, float pStartY, float pEndX, float pEndY, float pDrawStartX, float pDrawStartY, float pDrawEndX, float pDrawEndY);
    void                                    DrawSlice(FTextureRect *pTextureRect, float pStartX, float pStartY, float pEndX, float pEndY);
    
    void                                    DrawSliceTo(float pStartX, float pStartY, float pEndX, float pEndY, float pDrawStartX, float pDrawStartY, float pDrawEndX, float pDrawEndY);
    void                                    DrawSlice(float pStartX, float pStartY, float pEndX, float pEndY);

    void                                    DrawQuad(float pX1, float pY1,
                                             float pX2, float pY2,
                                             float pX3, float pY3,
                                             float pX4, float pY4);
    
    void                                    DrawQuad(float pLeft, float pTop,
                                             float pRight, float pBottom);
    
    void                                    CenterQuad(float pCenterX, float pCenterY, float pLeft, float pTop,
                                             float pRight, float pBottom);

    void                                    DrawQuadRect(float pX, float pY, float pWidth, float pHeight);
    void                                    DrawQuadRectOffset(float pX, float pY, float pWidth, float pHeight, float pOffset);
    
    void                                    PrintQuadData();
    
    float                                   ScaleFitH(float pWidth);
    float                                   ScaleFitH(float pWidth, float pOffset);
    
    float                                   ScaleFitV(float pHeight);
    float                                   ScaleFitV(float pHeight, float pOffset);
    
    
    inline float                            GetStartU(){return mTextureRect.GetStartU();}
    inline float                            GetStartV(){return mTextureRect.GetStartV();}
    inline float                            GetEndU(){return mTextureRect.GetEndU();}
    inline float                            GetEndV(){return mTextureRect.GetEndV();}
    
    inline float                            GetStartX(){return mTextureRect.GetStartX();}
    inline float                            GetStartY(){return mTextureRect.GetStartY();}
    inline float                            GetEndX(){return mTextureRect.GetEndX();}
    inline float                            GetEndY(){return mTextureRect.GetEndY();}

    bool                                    mAddToSpriteList;
};


extern bool gSpriteListEnabled;
extern FList gSpriteList;
extern FList gSpriteSequenceList;
//extern FList gPackedModelList;

#ifdef SETUP_MODE

extern int gTestSpriteIndex;
extern int gTestSpriteSequenceIndex;

#endif


#endif
