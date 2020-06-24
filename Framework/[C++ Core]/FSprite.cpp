#include "FApp.hpp"
#include "FSprite.hpp"
#include "FTexture.hpp"
//#include "FVertexBuffer.h"
#include "FString.hpp"
#include "core_includes.h"

//TODO: Turn off for release...
//bool gSpriteListEnabled = true;
//FList gSpriteList;
//FList gSpriteSequenceList;

FMatrix cSpriteMatrixHold;
FMatrix cSpriteMatrixModelView;

FSprite::FSprite() {
    mTexture = 0;
    
    mBufferPositions = NULL;
    mBufferTextureCoords = NULL;
    
    mWidth = 0;
    mHeight = 0;
    mAddToSpriteList = true;
    mDidLoad = false;
    mDidLoadFromBundle = false;
    mDidLoadFromResource = false;
    mDidLoadSingle = false;
}

FSprite::~FSprite() {
    Kill();
}

void FSprite::Kill() {
    SetTexture(0);
    
    delete mBufferPositions;
    mBufferPositions = NULL;
    
    delete mBufferTextureCoords;
    mBufferTextureCoords = NULL;
    
    mDidLoad = false;
    mDidLoadFromBundle = false;
    mDidLoadFromResource = false;
    mDidLoadSingle = false;
    
    mWidth = 0;
    mHeight = 0;
}

void FSprite::SetTexture(FTexture *pTexture) {
    if (mTexture) {
        if (pTexture != mTexture) {
            if(gTextureCache.mAutoMode == true) {
                gTextureCache.TextureBindRemove(mTexture);
                mTexture = 0; }
        }
    }
    if (pTexture) {
        mTexture = pTexture;
        if(gTextureCache.mAutoMode == true) {
            gTextureCache.TextureBindAdd(mTexture);
        }
    }
}

void FSprite::LoadNode(FImageBundler *pImageBundler, FImageBundlerLoadNode *pNode) {
    if (mDidLoad) {
        Log("Preventing Double Load [__NODE__]\n");
        return;
    }
    
    //Log("Sprite Loading With Node [%d %d %d %d]\n", pNode->mX, pNode->mY, pNode->mWidth, pNode->mHeight);
    
    Kill();
    
    if (pImageBundler == 0) return;
    if (pNode == 0) return;

    FTexture *aTexture = gTextureCache.GetTexture(pImageBundler->mBundleName.c());

    SetTexture(aTexture);
    
    float aStartU = pNode->mSpriteUStart;
    float aStartV = pNode->mSpriteVStart;
    float aEndU = pNode->mSpriteUEnd;
    float aEndV = pNode->mSpriteVEnd;

    float aScale = (1.0f / (float)aTexture->mScale) * gSpriteDrawScale;
    
    float aLeft = pNode->mSpriteLeft * aScale;
    float aRight = pNode->mSpriteRight * aScale;
    float aTop = pNode->mSpriteTop * aScale;
    float aBottom = pNode->mSpriteBottom * aScale;
    mWidth = (int)(pNode->mOriginalWidth * aScale + 0.5f);
    mHeight = (int)(pNode->mOriginalHeight * aScale + 0.5f);
    
    mTextureRect.SetQuad(aLeft, aTop, aRight, aBottom);
    mTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
    
    mDidLoad = true;
    mDidLoadFromBundle = true;
    mDidLoadSingle = false;
    
    mBufferPositions = new FBuffer(sizeof(mTextureRect.mPositions), BUFFER_TYPE_ARRAY);
    mBufferTextureCoords = new FBuffer(sizeof(mTextureRect.mTextureCoords), BUFFER_TYPE_ARRAY);
    
    WriteBuffers();
}

void FSprite::Load(char *pName, FImageBundler *pBundler) {
    if (mDidLoad) {
        Log("Preventing Double Load [%s]\n", pName);
        return;
    }
    Kill();
    if (!pBundler) { return; }
    if (pBundler->mDidLoad == false) { return; }
    FImageBundlerLoadNode *aNode = pBundler->FetchNode(pName);
    FTexture *aTexture = gTextureCache.GetTexture(pBundler->mBundleName.c());
    if ((aNode != 0) && (aTexture != 0)) {
        LoadNode(pBundler, aNode);
    }
}

void FSprite::Load(char *pFile) {
    //if (mDidLoad) {
    //    Log("Preventing Double Load [%s]\n", pFile);
    //    return;
    //}
    
    Kill();
    
    mFileName = pFile;
    mFileName.RemovePath();
    mFileName.RemoveExtension();
    
    if (gImageBundler.mAutoBundle) {
        if (gImageBundler.mBundleName.mLength > 0) {
            //FImage aImage;
            //aImage.Load(pFile);

            gImageBundler.AddImage(pFile);
        }
    }

    Load(pFile, &gImageBundler);

    if (mWidth > 0 && mHeight > 0) {
        mDidLoad = true;
        mDidLoadFromBundle = true;
        mDidLoadSingle = false;
        //if (gSpriteListEnabled == true) {
        //    gSpriteList.Add(this);
        //}
        return;
    }

    Load(gTextureCache.GetTexture(mFileName.c()));

    if (mWidth > 0 && mHeight > 0) {
        mDidLoad = true;
        mDidLoadFromBundle = false;
        mDidLoadSingle = true;
        //if (gSpriteListEnabled == true) {
        //    gSpriteList.Add(this);
        //}
    } else {
        Log("Failed To Load [%s]\n", mFileName.c());
    }
}

void FSprite::LoadN(const char *pFileStart, int pIndex) {
    Load(FString(pFileStart) + FString(pIndex));
}

void FSprite::LoadN(const char *pFileStart, int pIndex, const char *pFileEnd) {
    Load(FString(pFileStart) + FString(pIndex) + FString(pFileEnd));
}

void FSprite::LoadN(const char *pFileStart, int pIndex1, const char *pFileEnd, int pIndex2) {
    Load(FString(pFileStart) + FString(pIndex1) + FString(pFileEnd) + FString(pIndex2));
}

void FSprite::LoadN(const char *pFileStart, int pIndex1, const char *pFileMiddle, int pIndex2, const char *pFileEnd) {
    Load(FString(pFileStart) + FString(pIndex1) + FString(pFileMiddle) + FString(pIndex2) + FString(pFileEnd));
}

void FSprite::Load(FImage *pImage) {
    if(pImage)
    {
        Load(pImage, pImage->mOffsetX, pImage->mOffsetY, pImage->mWidth, pImage->mHeight);
        //Load(pImage, 0, 0, pImage->mWidth, pImage->mHeight);
    }
}

void FSprite::Load(FImage *pImage, int pX, int pY, int pWidth, int pHeight) {
    Kill();
    if(!pImage)return;
    if((pImage->mWidth <= 0) || (pImage->mHeight <=0 ))return;
    Load(pImage->GetTexture(), pX, pY, pWidth, pHeight);
}

void FSprite::Load(FTexture *pTexture) {
    if (pTexture) {
        Load(pTexture, pTexture->mOffsetX, pTexture->mOffsetY, pTexture->mWidth, pTexture->mHeight);
    }
}

void FSprite::Load(FTexture *pTexture, int pX, int pY, int pWidth, int pHeight) {
    if (mDidLoad) {
        Log("Preventing Double Load [_TEXTURE_RECT]\n");
        return;
    }
    
    //Log("Sprite Loading With Texture [%d %d %d %d]\n", pX, pY, pWidth, pHeight);
    
    Kill();
    if (pTexture) {
        if ((pTexture->mExpandedWidth > 0) && (pTexture->mExpandedHeight > 0)) {
            SetTexture(pTexture);
            
            float aScale = (1.0f / (float)pTexture->mScale) * gSpriteDrawScale;
            
            //float aScale = 1.0f / (float)pTexture->mScale;
            //aScale *= ((float)gSpriteScale);
            
            mWidth = (int)(pWidth * aScale + 0.5f);
            mHeight = (int)(pHeight * aScale + 0.5f);
            
            float aStartU = (float)pX / (float)pTexture->mExpandedWidth;
            float aStartV = (float)pY / (float)pTexture->mExpandedHeight;
            float aEndU = (float)(pX + pWidth) / (float)pTexture->mExpandedWidth;
            float aEndV = (float)(pY + pHeight) / (float)pTexture->mExpandedHeight;

            mTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
            
            float aHeight2 = ((float)mHeight) * 0.5f;
            float aWidth2 = ((float)mWidth) * 0.5f;
            mTextureRect.SetQuad(-aWidth2, -aHeight2, aWidth2, aHeight2);
            
            mBufferPositions = new FBuffer(sizeof(mTextureRect.mPositions), BUFFER_TYPE_ARRAY);
            mBufferTextureCoords = new FBuffer(sizeof(mTextureRect.mTextureCoords), BUFFER_TYPE_ARRAY);
            WriteBuffers();
        }
    }
}

void FSprite::WriteBuffers() {
    Graphics::BufferArrayWrite(mBufferPositions, mTextureRect.mPositions, sizeof(mTextureRect.mPositions));
    Graphics::BufferArrayWrite(mBufferTextureCoords, mTextureRect.mTextureCoords, sizeof(mTextureRect.mTextureCoords));
}

bool FSprite::DidLoad() {
    bool aResult = true;
    if (mTexture == NULL) {
        aResult = false;
    }
    if ((mWidth <= 0.0f) || (mHeight <= 0.0f)) {
        aResult = false;
    }
    return aResult;
}

float FSprite::ScaleFitH(float pWidth) {
    float aResult = 1.0f;
    if (mWidth > 0.0f) {
        if (pWidth >= 0.25f) {
            aResult = pWidth / mWidth;
        }
    }
    return aResult;
}

float FSprite::ScaleFitV(float pHeight) {
    float aResult = 1.0f;
    
    if (mHeight > 0.0f) {
        if (pHeight >= 0.25f) {
            aResult = pHeight / mHeight;
        }
    }
    return aResult;
}

float FSprite::ScaleFitH(float pWidth, float pOffset) {
    return ScaleFitH(pWidth - pOffset);
}

float FSprite::ScaleFitV(float pHeight, float pOffset) {
    return ScaleFitV(pHeight - pOffset);
}

void FSprite::Draw() {
    
    if (mTexture != NULL && mBufferPositions != NULL && mBufferTextureCoords != NULL) {
        if (mBufferPositions->mBindIndex != -1 && mBufferTextureCoords->mBindIndex != -1) {
            Graphics::TextureBind(mTexture);
            Graphics::ArrayBufferPositions(mBufferPositions);
            Graphics::ArrayBufferTextureCoords(mBufferTextureCoords);
            Graphics::UniformBind();
            Graphics::DrawTriangleStrips(4);
        }
    }
}

void FSprite::Center(float pX, float pY) {
    Graphics::MatrixModelViewGet(&cSpriteMatrixHold);
    cSpriteMatrixModelView.Set(cSpriteMatrixHold);
    cSpriteMatrixModelView.Translate(pX, pY);
    Graphics::MatrixModelViewSet(cSpriteMatrixModelView);
    Draw();
    Graphics::MatrixModelViewSet(cSpriteMatrixHold);

}

void FSprite::Draw(float pX, float pY) {
    Graphics::MatrixModelViewGet(&cSpriteMatrixHold);
    cSpriteMatrixModelView.Set(cSpriteMatrixHold);
    cSpriteMatrixModelView.Translate(pX + mWidth / 2.0f, pY + mHeight / 2.0f);
    Graphics::MatrixModelViewSet(cSpriteMatrixModelView);
    Draw();
    Graphics::MatrixModelViewSet(cSpriteMatrixHold);
}

void FSprite::Draw(float pX, float pY, float pScale, float pRotationDegrees) {
    Graphics::MatrixModelViewGet(&cSpriteMatrixHold);
    cSpriteMatrixModelView.Set(cSpriteMatrixHold);
    cSpriteMatrixModelView.Translate(pX, pY);
    cSpriteMatrixModelView.Rotate(pRotationDegrees);
    cSpriteMatrixModelView.Scale(pScale);
    Graphics::MatrixModelViewSet(cSpriteMatrixModelView);
    Draw();
    Graphics::MatrixModelViewSet(cSpriteMatrixHold);
}

void FSprite::Draw(float pX, float pY, float pScale, float pRotationDegrees, int pFacing) {
    if (pFacing < 1) {
        DrawFlippedH(pX, pY, pScale, pRotationDegrees);
    } else {
        Draw(pX, pY, pScale, pRotationDegrees);
    }
}

void FSprite::DrawFlippedH(float pX, float pY) {
    Graphics::MatrixModelViewGet(&cSpriteMatrixHold);
    cSpriteMatrixModelView.Set(cSpriteMatrixHold);
    cSpriteMatrixModelView.Translate(pX + mWidth / 2.0f, pY + mHeight / 2.0f);
    cSpriteMatrixModelView.Scale(-1.0f, 1.0f, 1.0f);
    Graphics::MatrixModelViewSet(cSpriteMatrixModelView);
    Draw();
    Graphics::MatrixModelViewSet(cSpriteMatrixHold);
}

void FSprite::DrawFlippedH(float pX, float pY, float pScale, float pRotationDegrees) {
    Graphics::MatrixModelViewGet(&cSpriteMatrixHold);
    cSpriteMatrixModelView.Set(cSpriteMatrixHold);
    cSpriteMatrixModelView.Translate(pX, pY);
    cSpriteMatrixModelView.Rotate(pRotationDegrees);
    cSpriteMatrixModelView.Scale(-pScale, pScale, pScale);
    Graphics::MatrixModelViewSet(cSpriteMatrixModelView);
    Draw();
    Graphics::MatrixModelViewSet(cSpriteMatrixHold);
}

void FSprite::DrawFlippedV(float pX, float pY) {
    Graphics::MatrixModelViewGet(&cSpriteMatrixHold);
    cSpriteMatrixModelView.Set(cSpriteMatrixHold);
    cSpriteMatrixModelView.Translate(pX + mWidth / 2.0f, pY + mHeight / 2.0f);
    cSpriteMatrixModelView.Scale(1.0f, -1.0f, 1.0f);
    Graphics::MatrixModelViewSet(cSpriteMatrixModelView);
    Draw();
    Graphics::MatrixModelViewSet(cSpriteMatrixHold);
}

void FSprite::DrawFlippedV(float pX, float pY, float pScale, float pRotationDegrees) {
    Graphics::MatrixModelViewGet(&cSpriteMatrixHold);
    cSpriteMatrixModelView.Set(cSpriteMatrixHold);
    cSpriteMatrixModelView.Translate(pX, pY);
    cSpriteMatrixModelView.Rotate(pRotationDegrees);
    cSpriteMatrixModelView.Scale(pScale, -pScale, pScale);
    Graphics::MatrixModelViewSet(cSpriteMatrixModelView);
    Draw();
    Graphics::MatrixModelViewSet(cSpriteMatrixHold);
}

FTextureRect cSliceTextureRect;

void FSprite::DrawQuad(float pX1, float pY1,
                       float pX2, float pY2,
                       float pX3, float pY3,
                       float pX4, float pY4) {
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
    cSliceTextureRect.SetQuad(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4);
    
    Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
}

void FSprite::DrawQuad(float pLeft, float pTop,
                       float pRight, float pBottom) {
    DrawQuad(pLeft, pTop, pRight, pTop, pLeft, pBottom, pRight, pBottom);
}

void FSprite::CenterQuad(float pCenterX, float pCenterY, float pLeft, float pTop,
                       float pRight, float pBottom) {
    float aWidth2 = (pRight - pLeft) * 0.5f;
    float aHeight2 = (pBottom - pTop) * 0.5f;
    
    DrawQuad(pCenterX - aWidth2, pCenterY - aHeight2, pCenterX + aWidth2, pCenterY + aHeight2);
}

void FSprite::DrawQuadRect(float pX, float pY, float pWidth, float pHeight) {
    float aX1 = pX;
    float aX2 = pX + pWidth;
    float aX3 = aX1;
    float aX4 = aX2;
    
    float aY1 = pY;
    float aY2 = aY1;
    float aY3 = pY + pHeight;
    float aY4 = aY3;
    
    DrawQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
}

void FSprite::DrawQuadRectOffset(float pX, float pY, float pWidth, float pHeight, float pOffset) {
    float aOffset2 = pOffset * 2.0f;
    DrawQuadRect(pX - pOffset, pY - pOffset, pWidth + aOffset2, pHeight + aOffset2);
}

void FSprite::DrawTripletH(float pX, float pY, float pInsetLeft, float pInsetRight, float pLength, bool pDrawLeft, bool pDrawMiddle, bool pDrawRight) {
    
    if (mWidth <= 2.0f) { return; }
    if (pLength <= 2.0f) { return; }
    
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    float aLengthCenter = (pLength - (pInsetLeft + pInsetRight));
    
    float aTripletLeftX = pX;
    float aTripletCenterX1 = pX + pInsetLeft;
    float aTripletCenterX2 = aTripletCenterX1 + aLengthCenter;
    float aTripletRightX = pX + pLength;
    
    float aTripletCenterU1 = aStartU;
    float aTripletCenterU2 = aEndU;
    
    aTripletCenterU1 = pInsetLeft / mWidth;
    aTripletCenterU2 = (mWidth - pInsetRight) / mWidth;
    aTripletCenterU1 = (aStartU + ((aEndU - aStartU) * aTripletCenterU1));
    aTripletCenterU2 = (aStartU + ((aEndU - aStartU) * aTripletCenterU2));
    
    float aX1 = aTripletLeftX;
    float aX2 = aTripletCenterX1;
    float aX3 = aX1;
    float aX4 = aX2;
    
    float aY1 = pY;
    float aY2 = aY1;
    float aY3 = pY + mHeight;
    float aY4 = aY3;
    
    if (pDrawLeft) {
        cSliceTextureRect.SetUVQuad(aStartU, aStartV, aTripletCenterU1, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    }
    
    aX1 = aTripletCenterX1;
    aX2 = aTripletCenterX2;
    aX3 = aX1;
    aX4 = aX2;
    
    if (pDrawMiddle) {
        cSliceTextureRect.SetUVQuad(aTripletCenterU1, aStartV, aTripletCenterU2, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    }
    
    aX1 = aTripletCenterX2;
    aX2 = aTripletRightX;
    aX3 = aX1;
    aX4 = aX2;
    
    if (pDrawRight) {
        cSliceTextureRect.SetUVQuad(aTripletCenterU2, aStartV, aEndU, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    }
}

void FSprite::DrawEndCappedTripletH(float pX, float pY, float pInsetLeft, float pInsetRight, float pLength) {
    
    if (mWidth <= 2.0f) { return; }
    if (pLength <= 2.0f) { return; }
    
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    float aLengthCenter = (pLength - (pInsetLeft + pInsetRight));
    
    float aTripletLeftX = pX;
    float aTripletCenterX1 = pX + pInsetLeft;
    float aTripletCenterX2 = aTripletCenterX1 + aLengthCenter;
    float aTripletRightX = pX + pLength;
    
    float aTripletCenterU1 = aStartU;
    float aTripletCenterU2 = aEndU;
    
    aTripletCenterU1 = pInsetLeft / mWidth;
    aTripletCenterU2 = (mWidth - pInsetRight) / mWidth;
    
    aTripletCenterU1 = (aStartU + ((aEndU - aStartU) * aTripletCenterU1));
    aTripletCenterU2 = (aStartU + ((aEndU - aStartU) * aTripletCenterU2));
    
    float aX1 = aTripletLeftX;
    float aX2 = aTripletCenterX1;
    float aX3 = aX1;
    float aX4 = aX2;
    
    float aY1 = pY;
    float aY2 = aY1;
    float aY3 = pY + mHeight;
    float aY4 = aY3;
    
    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aTripletCenterU1, aEndV);
    cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
    Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    
    aX1 = aTripletCenterX2;
    aX2 = aTripletRightX;
    aX3 = aX1;
    aX4 = aX2;
    cSliceTextureRect.SetUVQuad(aTripletCenterU2, aStartV, aEndU, aEndV);
    cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
    Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    
    float aMiddleSectionWidth = mWidth - (pInsetLeft + pInsetRight);
    
    float aMiddleSectionLeft = pLength / 2.0f - aMiddleSectionWidth / 2.0f;
    float aMiddleSectionRight = pLength / 2.0f + aMiddleSectionWidth / 2.0f;
    
    aX1 = aMiddleSectionLeft;
    aX2 = aTripletCenterX1;
    aX3 = aX1;
    aX4 = aX2;
    
    cSliceTextureRect.SetUVQuad(aTripletCenterU1, aStartV, aTripletCenterU1, aEndV);
    cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
    Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    
    aX1 = aMiddleSectionRight;
    aX2 = aTripletCenterX2;
    aX3 = aX1;
    aX4 = aX2;
    
    cSliceTextureRect.SetUVQuad(aTripletCenterU2, aStartV, aTripletCenterU2, aEndV);
    cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
    Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    
    aX1 = aMiddleSectionLeft;
    aX2 = aMiddleSectionRight;
    aX3 = aX1;
    aX4 = aX2;
    
    cSliceTextureRect.SetUVQuad(aTripletCenterU1, aStartV, aTripletCenterU2, aEndV);
    cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
    Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    
    
}

void FSprite::DrawTripletHProgress(float pX, float pY, float pInsetLeft, float pInsetRight, float pLength,
                                   float pProgressInsetLeft, float pProgressInsetRight, float pProgress) {
    
    if (mWidth <= 2.0f) { return; }
    if (pLength <= 2.0f) { return; }
    
    if (pProgress < 0.0f) { pProgress = 0.0f; }
    if (pProgress > 1.0f) { pProgress = 1.0f; }
    
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    float aStartX = pX + pProgressInsetLeft;
    float aEndX = pX + pLength - (pProgressInsetRight);
    float aBarLength = (aEndX - aStartX);
    
    if (aBarLength <= 0.0f) { return; }
    
    float aInnerEndU;
    
    float aProgressLength = aBarLength * pProgress;
    float aProgressX = aStartX + aProgressLength;
    float aLengthCenter = (pLength - (pInsetLeft + pInsetRight));
    
    float aPercentU = 0.0f;
    
    float aTripletLeftX = pX;
    float aTripletCenterX1 = pX + pInsetLeft;
    float aTripletCenterX2 = aTripletCenterX1 + aLengthCenter;
    float aTripletRightX = pX + pLength;
    
    float aTripletCenterU1 = aStartU;
    float aTripletCenterU2 = aEndU;
    
    aTripletCenterU1 = pInsetLeft / mWidth;
    aTripletCenterU2 = (mWidth - pInsetRight) / mWidth;
    aTripletCenterU1 = (aStartU + ((aEndU - aStartU) * aTripletCenterU1));
    aTripletCenterU2 = (aStartU + ((aEndU - aStartU) * aTripletCenterU2));
    
    float aX1 = aTripletLeftX;
    float aX2 = aTripletCenterX1;
    float aX3 = aX1;
    float aX4 = aX2;
    float aY1 = pY;
    float aY2 = aY1;
    float aY3 = pY + mHeight;
    float aY4 = aY3;
    if (aProgressX <= aTripletCenterX1) {
        aX2 = aProgressX;
        aX4 = aX2;
        aTripletCenterU1 = (aProgressX - pX) / mWidth;
        aTripletCenterU1 = (aStartU + ((aEndU - aStartU) * aTripletCenterU1));
        cSliceTextureRect.SetUVQuad(aStartU, aStartV, aTripletCenterU1, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
        return;
    } else {
        cSliceTextureRect.SetUVQuad(aStartU, aStartV, aTripletCenterU1, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    }
    
    aX1 = aTripletCenterX1;
    aX2 = aTripletCenterX2;
    aX3 = aX1;
    aX4 = aX2;
    if (aProgressX <= aTripletCenterX2) {
        aX2 = aProgressX;
        aX4 = aX2;
        aPercentU = (aProgressX - aTripletCenterX1) / (aTripletCenterX2 - aTripletCenterX1);
        aTripletCenterU2 = (aTripletCenterU1 + ((aTripletCenterU2 - aTripletCenterU1) * aPercentU));
        cSliceTextureRect.SetUVQuad(aTripletCenterU1, aStartV, aTripletCenterU2, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
        return;
    } else {
        cSliceTextureRect.SetUVQuad(aTripletCenterU1, aStartV, aTripletCenterU2, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    }
    
    aX1 = aTripletCenterX2;
    aX2 = aTripletRightX;
    aX3 = aX1;
    aX4 = aX2;
    if (aProgressX < aEndX) {
        aX2 = aProgressX;
        aX4 = aX2;
        aPercentU = (aProgressX - aTripletCenterX2) / (aEndX - aTripletCenterX2);
        aInnerEndU = aStartU + (aEndU - aStartU) * ((mWidth - pProgressInsetRight) / mWidth);
        aEndU = (aTripletCenterU2 + ((aInnerEndU - aTripletCenterU2) * aPercentU));
        cSliceTextureRect.SetUVQuad(aTripletCenterU2, aStartV, aEndU, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    } else {
        cSliceTextureRect.SetUVQuad(aTripletCenterU2, aStartV, aEndU, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
    }
}

void FSprite::Draw9x9(float pX, float pY, float pWidth, float pHeight, float pScale, float pRotation, float pInsetTop, float pInsetRight, float pInsetBottom, float pInsetLeft)
{
    if(mWidth < 1.0)return;
    if(mHeight < 1.0)return;
    
    float aX[4];
    float aY[4];
    float aU[4];
    float aV[4];
    
    float aWidth = pWidth * pScale;
    float aHeight = pHeight * pScale;
    
    float aQuadInsetLeft = pInsetLeft * pScale;
    float aQuadInsetRight = pInsetRight * pScale;
    float aQuadInsetTop = pInsetTop * pScale;
    float aQuadInsetBottom = pInsetBottom * pScale;
    
    float aQuadRight = pX + aWidth;
    float aQuadBottom = pY + aHeight;
    
    
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    float aSpanU = (aEndU - aStartU);
    float aSpanV = (aEndV - aStartV);
    
    aX[0] = pX;
    aX[1] = pX + aQuadInsetLeft;
    aX[3] = aQuadRight;
    aX[2] = (aQuadRight - aQuadInsetRight);
    
    aY[0] = pY;
    aY[1] = pY + aQuadInsetTop;
    aY[3] = aQuadBottom;
    aY[2] = (aQuadBottom - aQuadInsetBottom);
    
    aU[0] = aStartU;
    aU[3] = aEndU;
    aV[0] = aStartV;
    aV[3] = aEndV;
    
    aU[1] = (pInsetLeft / mWidth);
    aU[2] = ((mWidth - pInsetRight) / mWidth);
    aV[1] = (pInsetTop / mHeight);
    aV[2] = ((mHeight - pInsetBottom) / mHeight);
    
    aU[1] = (aU[1] * aSpanU) + aStartU;
    aU[2] = (aU[2] * aSpanU) + aStartU;
    aV[1] = (aV[1] * aSpanV) + aStartV;
    aV[2] = (aV[2] * aSpanV) + aStartV;
    
    for (int i=1;i<4;i++) {
        for (int n=1;n<4;n++) {
            cSliceTextureRect.SetUVQuad(aU[i - 1], aV[n - 1], aU[i], aV[n]);
            cSliceTextureRect.SetQuad(aX[i - 1], aY[n - 1], aX[i], aY[n]);
            Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
        }
    }
}

void FSprite::DrawShiftedCorners(float pX, float pY, float pScale, float pRotationDegrees, FVec2 pShiftUL, FVec2 pShiftUR, FVec2 pShiftDL, FVec2 pShiftDR) {
    float aX1 = mTextureRect.GetStartX();
    float aX2 = mTextureRect.GetEndX();
    float aX3 = aX1;
    float aX4 = aX2;
    
    float aY1 = mTextureRect.GetStartY();
    float aY2 = aY1;
    float aY3 = mTextureRect.GetEndY();
    float aY4 = aY3;
    
    aX1 += pShiftUL.mX;
    aY1 += pShiftUL.mY;
    
    aX2 += pShiftUR.mX;
    aY2 += pShiftUR.mY;
    
    aX3 += pShiftDL.mX;
    aY3 += pShiftDL.mY;
    
    aX4 += pShiftDR.mX;
    aY4 += pShiftDR.mY;
    
    cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
    
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
    
    Graphics::DrawSprite(pX, pY, 1.0f, 1.0f, 1.0f, pRotationDegrees, cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
}

void FSprite::DrawSliceTo(FTextureRect *pTextureRect, float pStartX, float pStartY, float pEndX, float pEndY, float pDrawStartX, float pDrawStartY, float pDrawEndX, float pDrawEndY) {
    if ((mWidth > 0.0f) && (mHeight > 0.0f) && (pTextureRect != 0)) {
        float aBaseStartU = mTextureRect.GetStartU();
        float aBaseStartV = mTextureRect.GetStartV();
        
        float aBaseEndU = mTextureRect.GetEndU();
        float aBaseEndV = mTextureRect.GetEndV();
        
        float aBaseRangeU = aBaseEndU - aBaseStartU;
        float aBaseRangeV = aBaseEndV - aBaseStartV;
        
        float aStartU = pStartX / mWidth;
        float aEndU = pEndX / mWidth;
        
        float aStartV = pStartY / mHeight;
        float aEndV = pEndY / mHeight;
        
        aStartU = aBaseStartU + aBaseRangeU * aStartU;
        aEndU = aBaseStartU + aBaseRangeU * aEndU;
        
        aStartV = aBaseStartV + aBaseRangeV * aStartV;
        aEndV = aBaseStartV + aBaseRangeV * aEndV;
        
        pTextureRect->SetQuad(pDrawStartX, pDrawStartY, pDrawEndX, pDrawEndY);
        pTextureRect->SetUVQuad(aStartU, aStartV, aEndU, aEndV);
        
        Graphics::DrawSprite(pTextureRect->mPositions, pTextureRect->mTextureCoords, mTexture);
    }
}

static FTextureTriangle cRadialTriangle;
void FSprite::DrawAngleRange(float pX, float pY, float pScale, float pRotation, float pStartRotation, float pEndRotation) {
    float aAngleDiff = (pEndRotation - pStartRotation);
    
    if(aAngleDiff <= 0.0f) { return; }
    
    if(aAngleDiff >= 360.0f) {
        Draw(pX, pY, pScale, pRotation);
        return;
    }
    
    if (pStartRotation < 0 || pStartRotation >= 360.0f) {
        pStartRotation = fmodf(pStartRotation, 360.0f);
        if(pStartRotation < 0)pStartRotation += 360.0f;
    }
    
    if (pEndRotation < 0 || pEndRotation >= 360.0f) {
        pEndRotation = fmodf(pEndRotation, 360.0f);
        if(pEndRotation < 0)pEndRotation += 360.0f;
    }
    
    float aStartU = GetStartU();
    float aStartV = GetStartV();
    
    float aEndU = GetEndU();
    float aEndV = GetEndV();
    
    float aStartX = GetStartX();
    float aStartY = GetStartY();
    
    float aEndX = GetEndX();
    float aEndY = GetEndY();
    
    float aX[4] = {aStartX, aEndX, aEndX, aStartX};
    float aY[4] = {aStartY, aStartY, aEndY, aEndY};
    
    float aURange = (aEndU - aStartU);
    float aVRange = (aEndV - aStartV);
    
    float aXRange = (aEndX - aStartX);
    float aYRange = (aEndY - aStartY);
    
    float aCenterU = aStartU + aURange * 0.5f;
    float aCenterV = aStartV + aVRange * 0.5f;
    
    float aLineStartX, aLineStartY, aLineEndX, aLineEndY;
    
    float aLineDirX, aLineDirY;
    float aLineNormX, aLineNormY;
    
    float aPlaneLength;
    
    float aDirX1 = Sin(pStartRotation);
    float aDirY1 = -Cos(pStartRotation);
    
    float aDirX2 = Sin(pEndRotation);
    float aDirY2 = -Cos(pEndRotation);
    
    float aCheckLength1, aCheckLength2;
    
    int aHitLine1 = -1;
    int aHitLine2 = -1;
    
    float aBestLength1 = 9999000000000.0f;
    float aBestLength2 = 9999000000000.0f;
    
    float aNumer, aDenom;
    
    int aStart = 3;
    int aEnd = 0;
    while (aEnd < 4) {
        aLineStartX = aX[aStart];
        aLineStartY = aY[aStart];
        
        aLineEndX = aX[aEnd];
        aLineEndY = aY[aEnd];
        
        aLineDirX = (aLineEndX - aLineStartX);
        aLineDirY = (aLineEndY - aLineStartY);
        
        aLineNormX = (-aLineDirY);
        aLineNormY = aLineDirX;
        
        aPlaneLength = (aLineDirX * aLineDirX) + (aLineDirY * aLineDirY);
        
        if (aPlaneLength > 0.01f) {
            aPlaneLength = sqrtf(aPlaneLength);
            
            aLineDirX /= aPlaneLength;
            aLineDirY /= aPlaneLength;
        }
        
        aNumer = (-(aLineNormX * aLineStartX + aLineNormY * aLineStartY));
        aDenom = (aDirX1 * aLineNormX + aDirY1 * aLineNormY);
        aCheckLength1 = -(aNumer / aDenom);
        
        //return
        
        if (aCheckLength1 > 0) {
            if (aCheckLength1 < aBestLength1) {
                aBestLength1 = aCheckLength1;
                aHitLine1 = aStart;
            }
        }
        
        aDenom = (aDirX2 * aLineNormX + aDirY2 * aLineNormY);
        aCheckLength2 = -(aNumer / aDenom);
        
        if (aCheckLength2 > 0) {
            if (aCheckLength2 < aBestLength2) {
                aBestLength2 = aCheckLength2;
                aHitLine2 = aStart;
            }
        }
        
        aStart = aEnd;
        aEnd++;
    }
    
    if ((aHitLine1 == -1) || (aHitLine2 == -1)) { return; }
    
    float aEdgeX1 = aDirX1 * aBestLength1;
    float aEdgeY1 = aDirY1 * aBestLength1;
    
    float aEdgeX2 = aDirX2 * aBestLength2;
    float aEdgeY2 = aDirY2 * aBestLength2;
    
    float aEdgeU1 = aStartU + ((aEdgeX1 - aStartX) / aXRange) * aURange;
    float aEdgeV1 = aStartV + ((aEdgeY1 - aStartY) / aYRange) * aVRange;
    float aEdgeU2 = aStartU + ((aEdgeX2 - aStartX) / aXRange) * aURange;
    float aEdgeV2 = aStartV + ((aEdgeY2 - aStartY) / aYRange) * aVRange;
    
    float aOctantX[8] = { 0.0f, aEndX, aEndX, aEndX, 0.0f, aStartX, aStartX, aStartX };
    float aOctantY[8] = { aStartY, aStartY, 0.0f, aEndY, aEndY, aEndY, 0.0f, aStartY };
    float aOctantU[8] = { aCenterU,aEndU,aEndU,aEndU,aCenterU,aStartU, aStartU, aStartU };
    float aOctantV[8] = { aStartV, aStartV, aCenterV, aEndV, aEndV, aEndV, aCenterV, aStartV };
    bool aOctantDraw[8] = { false, false, false, false, false, false, false, false };
    
    aOctantDraw[0] = false;
    aOctantDraw[1] = false;
    aOctantDraw[2] = false;
    aOctantDraw[3] = false;
    aOctantDraw[4] = false;
    aOctantDraw[5] = false;
    aOctantDraw[6] = false;
    aOctantDraw[7] = false;
    
    int aOctantStart = 7;
    int aOctantEnd = 7;
    
    if (aHitLine1 == 0) {
        if(aEdgeX1 >= 0)aOctantStart = 0;
        else aOctantStart = 7;
    }
    
    if (aHitLine1 == 1) {
        if(aEdgeY1 <= 0)aOctantStart = 1;
        else aOctantStart = 2;
    }
    
    if (aHitLine1 == 2) {
        if(aEdgeX1 > 0)aOctantStart = 3;
        else aOctantStart = 4;
    }
    
    if (aHitLine1 == 3) {
        if(aEdgeY1 < 0)aOctantStart = 6;
        else aOctantStart = 5;
    }
    
    if (aHitLine2 == 0) {
        if(aEdgeX2 >= 0)aOctantEnd = 0;
        else aOctantEnd = 7;
    }
    
    if (aHitLine2 == 1) {
        if(aEdgeY2 <= 0)aOctantEnd = 1;
        else aOctantEnd = 2;
    }
    
    if (aHitLine2 == 2) {
        if(aEdgeX2 > 0)aOctantEnd = 3;
        else aOctantEnd = 4;
    }
    
    if (aHitLine2 == 3) {
        if(aEdgeY2 < 0)aOctantEnd = 6;
        else aOctantEnd = 5;
    }
    
    if (aOctantStart == aOctantEnd) {
        if (pEndRotation < pStartRotation) {
            int aDrawOctant1 = aOctantStart;
            int aDrawOctant2 = aDrawOctant1 + 1;
            if(aDrawOctant2 == 8)aDrawOctant2 = 0;
            
            cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aEdgeX1, aEdgeY1, aOctantX[aDrawOctant2], aOctantY[aDrawOctant2]);
            cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aEdgeU1, aEdgeV1, aOctantU[aDrawOctant2], aOctantV[aDrawOctant2]);
            Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mPositions, cRadialTriangle.mTextureCoords, mTexture);
            
            aDrawOctant1 = aOctantEnd;
            cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aOctantX[aDrawOctant1], aOctantY[aDrawOctant1], aEdgeX2, aEdgeY2);
            cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aOctantU[aDrawOctant1], aOctantV[aDrawOctant1], aEdgeU2, aEdgeV2);
            Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mPositions, cRadialTriangle.mTextureCoords, mTexture);
            
            for (int i=0;i<8;i++) {
                if (i != aOctantStart) {
                    aOctantDraw[i] = true;
                }
            }
        } else {
            cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aEdgeX1, aEdgeY1, aEdgeX2, aEdgeY2);
            cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aEdgeU1, aEdgeV1, aEdgeU2, aEdgeV2);
            Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mPositions, cRadialTriangle.mTextureCoords, mTexture);
        }
    } else {
        int aDrawOctant1 = aOctantStart;
        int aDrawOctant2 = aDrawOctant1 + 1;
        if (aDrawOctant2 == 8) { aDrawOctant2 = 0; }
        
        cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aEdgeX1, aEdgeY1, aOctantX[aDrawOctant2], aOctantY[aDrawOctant2]);
        cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aEdgeU1, aEdgeV1, aOctantU[aDrawOctant2], aOctantV[aDrawOctant2]);
        Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mPositions, cRadialTriangle.mTextureCoords, mTexture);
        
        
        aDrawOctant1 = aOctantEnd;
        cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aOctantX[aDrawOctant1], aOctantY[aDrawOctant1], aEdgeX2, aEdgeY2);
        cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aOctantU[aDrawOctant1], aOctantV[aDrawOctant1], aEdgeU2, aEdgeV2);
        Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mPositions, cRadialTriangle.mTextureCoords, mTexture);
        
        int aOctant = aOctantStart;
        for (int i=0;i<8;i++) {
            aOctant++;
            if(aOctant == 8)aOctant = 0;
            if(aOctant == aOctantEnd)break;
            aOctantDraw[aOctant] = true;
        }
    }
    
    for (int aOctant=0;aOctant<8;aOctant++) {
        if (aOctantDraw[aOctant]) {
            int aOctant2 = aOctant + 1;
            if(aOctant2 == 8)aOctant2 = 0;
            cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aOctantX[aOctant], aOctantY[aOctant], aOctantX[aOctant2], aOctantY[aOctant2]);
            cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aOctantU[aOctant], aOctantV[aOctant], aOctantU[aOctant2], aOctantV[aOctant2]);
            Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mPositions, cRadialTriangle.mTextureCoords, mTexture);
        }
    }
}

void FSprite::DrawSlice(FTextureRect *pTextureRect, float pStartX, float pStartY, float pEndX, float pEndY) {
    DrawSliceTo(pTextureRect, pStartX, pStartY, pEndX, pEndY, 0.0f, 0.0f, pEndX - pStartX, pEndY - pStartY);
}

void FSprite::DrawSliceTo(float pStartX, float pStartY, float pEndX, float pEndY, float pDrawStartX, float pDrawStartY, float pDrawEndX, float pDrawEndY) {
    DrawSliceTo(&cSliceTextureRect, pStartX, pStartY, pEndX, pEndY, pDrawStartX, pDrawStartY, pDrawEndX, pDrawEndY);
}

void FSprite::DrawSlice(float pStartX, float pStartY, float pEndX, float pEndY) {
    DrawSlice(&cSliceTextureRect, pStartX, pStartY, pEndX, pEndY);
}

void FSprite::DrawScaled(float pX, float pY, float pScale) {
    //Draw(pX, pY, pScale, 0.0f);

    Graphics::MatrixModelViewGet(&cSpriteMatrixHold);
    cSpriteMatrixModelView.Set(cSpriteMatrixHold);
    cSpriteMatrixModelView.Translate(pX, pY);
    cSpriteMatrixModelView.Scale(pScale);
    Graphics::MatrixModelViewSet(cSpriteMatrixModelView);
    Draw();
    Graphics::MatrixModelViewSet(cSpriteMatrixHold);
    
}

void FSprite::DrawScaled(float pX, float pY, float pScaleX, float pScaleY) {
    //Graphics::DrawSprite(pX, pY, pScaleX, pScaleY, 1.0f, 0.0f, mTextureRect.mPositions, mTextureRect.mTextureCoords, mTexture);
    
    Graphics::MatrixModelViewGet(&cSpriteMatrixHold);
    cSpriteMatrixModelView.Set(cSpriteMatrixHold);
    cSpriteMatrixModelView.Translate(pX, pY);
    cSpriteMatrixModelView.Scale(pScaleX, pScaleY, 1.0f);
    Graphics::MatrixModelViewSet(cSpriteMatrixModelView);
    Draw();
    Graphics::MatrixModelViewSet(cSpriteMatrixHold);
    
}

void FSprite::DrawScaled(float pX, float pY, float pScaleX, float pScaleY, float pRotation) {
    Graphics::MatrixModelViewGet(&cSpriteMatrixHold);
    cSpriteMatrixModelView.Set(cSpriteMatrixHold);
    cSpriteMatrixModelView.Translate(pX, pY);
    cSpriteMatrixModelView.Rotate(pRotation);
    cSpriteMatrixModelView.Scale(pScaleX, pScaleY, 1.0f);
    Graphics::MatrixModelViewSet(cSpriteMatrixModelView);
    Draw();
    Graphics::MatrixModelViewSet(cSpriteMatrixHold);
}

void FSprite::DrawRepeatingH(float pX, float pY, float pLength) {
    if ((mTexture != NULL) && (mBufferPositions != NULL) && (mBufferTextureCoords != NULL) && (pLength > 0.0f)) {
        float aWidth = (mTextureRect.GetEndX() - mTextureRect.GetStartX());
        float aHeight = (mTextureRect.GetEndY() - mTextureRect.GetStartY());
        float aStartU = mTextureRect.GetStartU();
        float aEndU = mTextureRect.GetEndU();
        float aStartV = mTextureRect.GetStartV();
        float aEndV = mTextureRect.GetEndV();
        float aPercent = 0.0f;
        float aBottomY = pY + aHeight;
        if ((mBufferPositions->mBindIndex != -1) && (mBufferTextureCoords->mBindIndex != -1) && (aWidth >= 1.0f) && (aHeight >= 1.0f)) {
            float aEndX = pX + pLength;
            float aX = pX;
            float aNextX = 0.0f;
            while (1) {
                aNextX = (aX + aWidth);
                if (aNextX > aEndX) {
                    aPercent = (aEndX - aX) / (aNextX - aX);
                    aEndU = aStartU + (aEndU - aStartU) * aPercent;
                    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
                    cSliceTextureRect.SetQuad(aX, pY, aEndX, aBottomY);
                    Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
                    return;
                } else {
                    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
                    cSliceTextureRect.SetQuad(aX, pY, aNextX, aBottomY);
                    Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
                }
                aX = aNextX;
            }
        }
    }
}

void FSprite::DrawRepeatingV(float pX, float pY, float pHeight) {
    if ((mTexture != NULL) && (mBufferPositions != NULL) && (mBufferTextureCoords != NULL) && (pHeight > 0.0f)) {
        float aWidth = (mTextureRect.GetEndX() - mTextureRect.GetStartX());
        float aHeight = (mTextureRect.GetEndY() - mTextureRect.GetStartY());
        float aStartU = mTextureRect.GetStartU();
        float aEndU = mTextureRect.GetEndU();
        float aStartV = mTextureRect.GetStartV();
        float aEndV = mTextureRect.GetEndV();
        float aPercent = 0.0f;
        float aRightX = pX + aWidth;
        if ((mBufferPositions->mBindIndex != -1) && (mBufferTextureCoords->mBindIndex != -1) && (aWidth >= 1.0f) && (aHeight >= 1.0f)) {
            float aEndY = pY + pHeight;
            float aY = pY;
            float aNextY = 0.0f;
            while (1) {
                aNextY = (aY + aHeight);
                if (aNextY > aEndY) {
                    aPercent = (aEndY - aY) / (aNextY - aY);
                    aEndV = aStartV + (aEndV - aStartV) * aPercent;
                    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
                    cSliceTextureRect.SetQuad(pX, aY, aRightX, aEndY);
                    Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
                    return;
                } else {
                    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
                    cSliceTextureRect.SetQuad(pX, aY, aRightX, aNextY);
                    Graphics::DrawSprite(cSliceTextureRect.mPositions, cSliceTextureRect.mTextureCoords, mTexture);
                }
                aY = aNextY;
            }
        }
    }
}

void FSprite::DrawRotated(float pX, float pY, float pRotation) {
    Draw(pX, pY, 1.0f, pRotation);
}

void FSprite::PrintQuadData() {
    FString aName = mFileName.c();
    aName.RemoveExtension();
    aName.RemovePath();
    
    Log("Sprite [ %s ] Sz(%.1fx%.1f) Tex[%.3f, %.3f, %.3f, %.3f], Rec[%.1f, %.1f, %.1f, %.1f]\n", aName.c(), mWidth, mHeight, mTextureRect.GetStartU(), mTextureRect.GetStartV(), mTextureRect.GetEndU(), mTextureRect.GetEndV(), mTextureRect.GetStartX(), mTextureRect.GetStartY(), mTextureRect.GetEndX(), mTextureRect.GetEndY());
    
    
}




