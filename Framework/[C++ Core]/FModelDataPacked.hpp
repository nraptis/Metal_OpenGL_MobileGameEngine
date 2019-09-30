//
//  FModelDataPacked.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/7/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FModelDataPacked_hpp
#define FModelDataPacked_hpp

#include "os_core_graphics.h"
#include "FModelData.h"
#include "FFile.hpp"
#include "FImage.hpp"
#include "FSprite.hpp"
#include "FBuffer.hpp"

class FModelDataPacked {
public:
    
    FModelDataPacked();
    virtual ~FModelDataPacked();
    
    void                                Free();
    void                                DiscardBuffer();
    void                                DiscardData();
    void                                DiscardIndices();
    
    void                                Draw();
    void                                Draw(FTexture *pTexture);
    
    FModelDataPacked                    *Clone();
    
    void                                CopyIndex(GFX_MODEL_INDEX_TYPE *pIndex, int pCount);
    void                                CopyData(float *pData, int pCount);
    
    
    void                                KillBuffers();
    
    void                                FitUVW(float pStartU, float pEndU, float pStartV, float pEndV);
    
    void                                Save(FFile *pFile);
    void                                Save(const char *pFile);
    inline void                         Save(FString pName) { Save((const char*)pName.c()); }
    
    //For a sequence of files, with one sprite...
    void                                LoadData(FFile *pFile, FSprite *pSprite);
    void                                LoadData(const char *pFile, FSprite *pSprite);
    inline void                         LoadData(FString pFile, FSprite *pSprite) { LoadData((const char*)pFile.c(), pSprite); }
    
    
    //For a sequence of files, where the sprite UVW is precomputed and baked in...
    void                                LoadData(FFile *pFile);
    void                                LoadData(const char *pFile);
    inline void                         LoadData(FString pFile) { LoadData((const char*)pFile.c()); }
    
    
    
    void                                LoadOBJ(FFile *pFile);
    void                                LoadOBJ(const char *pFile);
    inline void                         LoadOBJ(FString pFile) { LoadOBJ((const char*)pFile.c()); }
    
    void                                LoadIndexedModel(FModelDataIndexed *pModel);
    
    void                                InvertX();
    void                                InvertY();
    void                                InvertZ();
    
    int                                 GetStride();
    
    void                                WriteBuffers();
    
    FString                             mFileName;
    
    bool                                mHasXYZ;
    bool                                mHasUVW;
    bool                                mHasNormals;
    bool                                mHasTangents;
    bool                                mHasUNormals;
    
    GFX_MODEL_INDEX_TYPE                *mIndex;
    int                                 mIndexCount;
    
    float                               *mData;
    int                                 mDataCount;
    
    bool                                mUseUVW;
    bool                                mUseNormals;
    bool                                mUseTangents;
    bool                                mUseUNormals;
    
    int                                 mStride;
    
    FBuffer                             *mBuffer;
};

#endif /* FModelDataPacked_hpp */
