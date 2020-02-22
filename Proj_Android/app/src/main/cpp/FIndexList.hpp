//
//  FIndexList.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/14/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef __DigMMMac__FIndexList__
#define __DigMMMac__FIndexList__

#define GFX_MODEL_INDEX_TYPE unsigned short
//#define GFX_MODEL_INDEX_TYPE unsigned int

#include "FSprite.hpp"
#include "FString.hpp"
#include "FFile.hpp"

class FIndexList {
public:
    
    FIndexList();
    virtual ~FIndexList();
    
    inline bool             IsEmpty() { return mCount == 0; }
    
    void                    Clear();
    void                    RemoveAll();
    
    GFX_MODEL_INDEX_TYPE	*mIndex;
    int                     mCount;
    int                     mSize;
    
    void                    Add(FIndexList *pList);
    void                    Add(GFX_MODEL_INDEX_TYPE pIndex);
    
    GFX_MODEL_INDEX_TYPE	Get(int pIndex);
    
    void                    Reverse();
    
    void                    Size(int pSize);
    
    void                    Save(FFile *pFile);
    void                    Load(FFile *pFile);
    
    int                     GetPrintLineCount();
    FString                 GetPrintLine(int pLineNumber);
    FString                 GetPrintString(const char *pVariableName);
    
    
};

#endif

