//
//  FModelDataPackedSequence.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/4/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FModelDataPackedSequence_hpp
#define FModelDataPackedSequence_hpp

#include "FModelData.h"
#include "FModelDataPacked.hpp"
#include "FFile.hpp"
#include "FImage.hpp"
#include "FSprite.hpp"
#include "FSpriteSequence.h"
#include "os_core_graphics.h"

class FModelDataPackedSequence {
public:
    
    FModelDataPackedSequence();
    virtual ~FModelDataPackedSequence();
    
    void                                Free();
    
    FModelDataPacked                    *GetModel(float pFrame);
    float                               GetMaxFrame();
    
    
    void                                Save(FFile *pFile);
    void                                Save(const char *pFile);
    inline void                         Save(FString pName) { Save((const char*)pName.c()); }
    
    //This is for loading a sequence of 3DM files... Basically an OBJ sequence with a single sprite...
    void                                LoadData(FFile *pFile, FSprite *pSprite);
    void                                LoadData(const char *pFile, FSprite *pSprite);
    inline void                         LoadData(FString pFile, FSprite *pSprite) { LoadData((const char*)pFile.c(), pSprite); }
    
    
    //This is for loading a sequence of 3DM files...
    //First parameter is SINGLE MODEL (3dp) file.
    //We then fit the UVW to the sequence and spawn clones...
    void                                LoadDataBillboardSequence(FFile *pFile, FSpriteSequence *pSpriteSequence);
    void                                LoadDataBillboardSequence(const char *pFile, FSpriteSequence *pSpriteSequence);
    inline void                         LoadDataBillboardSequence(FString pFile, FSpriteSequence *pSpriteSequence) { LoadDataBillboardSequence((const char*)pFile.c(), pSpriteSequence); }
    
    
    void                                LoadOBJSequence(const char *pFile, int pStartIndex, int pEndIndex);
    inline void                         LoadOBJSequence(FString pFile, int pStartIndex, int pEndIndex) { LoadOBJSequence((const char*)pFile.c(), pStartIndex, pEndIndex); }
    
    
    void                                LoadOBJBillboardSequence(const char *pFile, FSpriteSequence *pSpriteSequence);
    inline void                         LoadOBJBillboardSequence(FString pFile, FSpriteSequence *pSpriteSequence) { LoadOBJBillboardSequence((const char*)pFile.c(), pSpriteSequence); }
    
    
    void                                CopyData(float *pXYZ, int pCount);
    void                                CopyIndex(GFX_MODEL_INDEX_TYPE *pIndex, int pCount);
    
    GFX_MODEL_INDEX_TYPE                *mIndex;
    int                                 mIndexCount;
    
    //List of FModelDataPacked
    FList                               mList;
    
    bool                                mUseUVW;
    bool                                mUseNormals;
    bool                                mUseTangents;
    bool                                mUseUNormals;
};

#endif
