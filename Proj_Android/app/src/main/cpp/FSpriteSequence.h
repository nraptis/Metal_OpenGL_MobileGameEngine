//
//  FSpriteSequence.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#ifndef __CoreDemo__FSpriteSequence__
#define __CoreDemo__FSpriteSequence__

#include "FString.hpp"
#include "FSprite.hpp"
#include "FList.hpp"

/*
class FSpriteSequenceSearchNode
{
public:
    
    FSpriteSequenceSearchNode(const char *pFilePath, const char *pName, int pIndex);
    virtual ~FSpriteSequenceSearchNode();
    
    FString                             mFilePath;
    FString                             mName;
    
    int                                 mIndex;
};

class FSpriteSequenceSearchBucket
{
public:
    FSpriteSequenceSearchBucket();
    virtual ~FSpriteSequenceSearchBucket();
    
    void                                AddNode(FSpriteSequenceSearchNode *pSerchNode);
    void                                Finalize();
    
    FString                             mName;
    int                                 mStartIndex;
    int                                 mEndIndex;
    int                                 mCount;
    
    FList                               mNodeList;
};
*/

class FSpriteSequence
{
public:
    
    FSpriteSequence();
    virtual ~FSpriteSequence();
    
    void                                Kill();

    void                                LoadBundle(const char *pBundleName);

    void                                Load(const char *pFilePrefix);
    inline void                         Load(char *pFilePrefix) { Load((const char*)pFilePrefix); }
    inline void                         Load(FString pFilePrefix) { Load((const char*)(pFilePrefix.c())); }
    void                                Load(const char *pFilePrefix, int pStartIndex, int pEndIndex);
    inline void                         Load(FString pFilePrefix, int pStartIndex, int pEndIndex) { Load((const char*)(pFilePrefix.c()), pStartIndex, pEndIndex); }

    void                                ComputeBounds();

    //static void                         FindAllFileSequences(FList &pFileList, FList &pSearchBucketList);
    //static void                         PrintAllFileSequences(FList &pFileList);

    void                                Add(FSprite *pSprite);
    void                                Add(FSpriteSequence *pSpriteSequence);

    float                               GetMaxFrame();
    float                               LoopFrame(float pFrame, float pFrameSpeed);
    
    FList                               mList;
    
    FString                             mFilePrefix;
    
    void                                Draw(float pFrame);
    void                                Draw(float pFrame, float pX, float pY);
    void                                DrawScaled(float pFrame, float pX, float pY, float pScale);
    void                                DrawScaled(float pFrame, float pX, float pY, float pScaleX, float pScaleY);
    void                                DrawScaled(float pFrame, float pX, float pY, float pScaleX, float pScaleY, float pRotation);
    void                                DrawRotated(float pFrame, float pX, float pY, float pRotation);
    void                                Draw(float pFrame, float pX, float pY, float pScale, float pRotation);
    
    void                                Center(float pFrame, float pX, float pY);
    
    FSprite                             *GetSprite(float pFrame);
    
    FSprite                             *Get();
    FSprite                             *Get(int pIndex);
    FSprite                             *GetRandom();
    
    float                               mWidth;
    float                               mHeight;
};

#endif
