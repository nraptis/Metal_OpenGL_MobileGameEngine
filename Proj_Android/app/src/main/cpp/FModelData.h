//
//  FModelData.h
//
//  Created by Nick Raptis on 1/18/12.
//  Copyright (c) 2012 Nick Raptis. All rights reserved.
//


#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include "os_core_graphics.h"
#include "FString.hpp"
#include "FFile.hpp"
#include "FImage.hpp"
#include "FSprite.hpp"

extern bool gModelDiscardNormals;
extern bool gModelDiscardUVW;

class FTexture;

class FModelData
{
public:
    
    FModelData();
    virtual ~FModelData();
    
    virtual void            LoadData(FFile *pFile);
    virtual void            LoadData(const char *pFile);
    
    virtual void            LoadOBJ(FFile *pFile);
    virtual void            LoadOBJ(const char *pFile);
    
    void                    Draw();
    
    float                   *mXYZ;
    float                   *mUVW;
    float                   *mNormal;
    
    virtual void            Save(FFile *pFile);
    virtual void            Save(const char *pFile);
    
    void                    SetSprite(FSprite *pSprite, bool pFixUVW=true);
    void                    SetTexture(FTexture *pTexture);
    FTexture                *mTexture;
    
    void                    SetImage(FImage *pImage);
    void                    SetImage(const char *pImagePath);
    
    void                    DiscardXYZ();
    void                    DiscardUVW();
    void                    DiscardNormal();
    
    void                    FitUVW(float pStartU, float pEndU, float pStartV, float pEndV);
    
    FModelData              *Clone();
    
    virtual void            GetCentroid(float &pCentroidX, float &pCentroidY, float &pCentroidZ);
    
    void                    AddXYZ(float pX, float pY, float pZ);
    void                    SizeXYZ(int pSize);
    
    void                    AddUVW(float pU, float pV, float pW);
    void                    SizeUVW(int pSize);
    
    void                    AddNormal(float pNormX, float pNormY, float pNormZ);
    void                    SizeNormal(int pSize);
    
    inline float            *ResizeTriple(float *pData, int pCount, int pSize);
    inline void             SetTriple(unsigned int pIndex, float *pArray, float pValue1, float pValue2, float pValue3);
    
    void                    CopyXYZ(float *pXYZ, int pCount);
    void                    CopyUVW(float *pUVW, int pCount);
    void                    CopyNorm(float *pNorm, int pCount);
    
    void                    InvertU();
    void                    InvertV();
    void                    InvertW();
    
    void                    Scale(float pScale);
    
    void                    ShiftX(float pShiftAmount);
    void                    ShiftY(float pShiftAmount);
    void                    ShiftZ(float pShiftAmount);
    
    void                    ShiftCentroid();
    
    
    void                    FlipXY();
    void                    FlipYZ();
    void                    FlipZX();
    
    void                    NegateX();
    void                    NegateY();
    void                    NegateZ();
    
    float                   GetX(int pIndex);
    float                   GetY(int pIndex);
    float                   GetZ(int pIndex);
    
    float                   GetU(int pIndex);
    float                   GetV(int pIndex);
    float                   GetW(int pIndex);
    
    float                   GetNormX(int pIndex);
    float                   GetNormY(int pIndex);
    float                   GetNormZ(int pIndex);
    
    int                     mXYZCount;
    int                     mXYZSize;
    
    int                     mUVWCount;
    int                     mUVWSize;
    
    int                     mNormalCount;
    int                     mNormalSize;
    
    virtual void            Print();
    virtual void            PrintOverview();
    
    virtual void            Free();
};

class FModelDataIndexed : public FModelData
{
public:
    
    FModelDataIndexed();
    virtual ~FModelDataIndexed();
    
    void                        Load(const char *pFile);
    inline void                 Load(char *pFile){Load((const char *)pFile);}
    inline void                 Load(FString pFile){Load((const char *)(pFile.c()));}
    
    void                        Draw();
    void                        Draw(FTexture *pTexture);
    
    virtual void                Save(FFile *pFile);
    virtual void                Save(const char *pFile);
    
    virtual void                LoadData(FFile *pFile);
    virtual void                LoadData(const char *pFile);
    
    virtual void                LoadOBJ(FFile *pFile);
    virtual void                LoadOBJ(const char *pFile);
    
    
    
    //void                      Load(const char *pFile, Sprite &pSprite);
    //inline void               Load(char *pFile, Sprite &pSprite){Load((const char *)pFile, pSprite);}
    //inline void               Load(FString pFile, Sprite &pSprite){Load((const char *)(pFile.c()), pSprite);}
    
    //void                      Load(const char *pFileStart, int pIndex, const char *pFileEnd=0);
    //void                      Load(const char *pFileStart, int pIndex, const char *pFileEnd, Sprite &pSprite);
    
    FModelData                  *GetData();
    void                        DiscardIndices();
    
    virtual void                GetCentroid(float &pCentroidX, float &pCentroidY, float &pCentroidZ);
    
    void                        CopyIndex(GFX_MODEL_INDEX_TYPE *pIndex, int pCount);
    
    FModelDataIndexed           *Clone();
    
    void                        Clone(FModelDataIndexed *pTarget);
    
    void                        PrintCode();
    
    GFX_MODEL_INDEX_TYPE        *mIndex;
    int                         mIndexCount;
    int                         mIndexSize;
    
    void                        AddIndex(GFX_MODEL_INDEX_TYPE pIndex);
    void                        SizeIndex(int pSize);
    
    virtual void                Free();
};

class FModelDataOptimizerNode {
public:
    
    float                           mX, mY, mZ;
    float                           mU, mV, mW;
    float                           mNormX, mNormY, mNormZ;
    
    int                             mCount;
    
    int                             mIndex;
    int                             mMapIndex;
    
    FModelDataOptimizerNode         *mNextNode;
};

class FModelDataOptimizer
{
public:
    
    FModelDataOptimizer();
    ~FModelDataOptimizer();
    
    bool                            mIgnoreXYZ;
    bool                            mIgnoreUVW;
    bool                            mIgnoreNormal;
    
    unsigned int                    *mIndex;
    int                             mIndexCount;
    int                             mIndexSize;
    
    unsigned int                    *mCypher;
    int                             mCypherCount;
    
    float                           *mUVW;
    
    //Warning: Do not use for now.
    void                            ClearHashTable();
    
    unsigned int                    HashFloat(unsigned int pRunningSum, float pFloat);
    
    int                             Hash(float pX, float pY, float pZ,
                                     float pU, float pV, float pW,
                                     float pNormX, float pNormY, float pNormZ);
    
    int                             PushNode(int pMapToIndex, float pX, float pY, float pZ,
                                         float pU, float pV, float pW,
                                         float pNormX, float pNormY, float pNormZ, FList *pList);
    
    void                            Push(FModelData *pData, FList *pList);
    
    void                            Generate(FModelData *pData);
    void                            Convert(FModelData *pData, FModelDataIndexed *pTarget);
    FModelDataIndexed               *Convert(FModelData *pData);
    
    void                            SolveXYZ(FModelData *pReference, FModelData *pTarget);
    void                            SolveUVW(FModelData *pData, FModelData *pTarget);
    void                            SolveNormal(FModelData *pData, FModelData *pTarget);
    
    void                            Print();
    void                            PrintOverview();
    
    void                            SizeHashTable(int pSize, FList *pList);
    int                             mHashTableSize;
    
    FModelDataOptimizerNode         **mHashTable;
};

#endif
