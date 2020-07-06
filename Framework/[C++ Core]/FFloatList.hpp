//
//  FFloatList.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/14/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef __DigMMMac__FFloatList__
#define __DigMMMac__FFloatList__

#include "FFile.hpp"

class FFloatList
{
public:
    
    FFloatList();
    virtual ~FFloatList();
    
    inline bool             IsEmpty() { return mCount == 0; }
    
    void                    Clear();
    void                    RemoveAll();
    void                    Reset();
    
    float                   *mData;
    int                     mCount;
    int                     mSize;
    
    void                    Add(FFloatList *pList);
    void                    Add(float pFloat);
    void                    Set(int pSlot, float pFloat);
    
    float	                Get(int pSlot);
    
    void                    Reverse();
    
    void                    Size(int pSize);
    inline void             SetSize(int pSize){ Size(pSize); }
    
    void                    Clone(FFloatList *pPointList);
    inline void             Clone(FFloatList &pPointList){ Clone(&pPointList); }
    
    void                    Save(FFile *pFile);
    void                    Load(FFile *pFile);
    
    void                    Shuffle();
};


#endif /* defined(__DigMMMac__FFloatList__) */
