//
//  FIntList.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/3/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FIntList_hpp
#define FIntList_hpp

//#define int unsigned int

#include "FSprite.hpp"
#include "FString.hpp"
#include "FFile.hpp"

class FIntList {
public:
    
    FIntList();
    virtual ~FIntList();
    
    inline bool             IsEmpty() { return mCount == 0; }
    
    void                    Clear();
    
    void                    RemoveAll();
    
    int                     *mData;
    int                     mCount;
    int                     mSize;
    
    void                    Add(FIntList *pList);
    void                    Add(int pIndex);
    
    int                     Get(int pIndex);
    
    void                    Reverse();
    
    void                    Size(int pSize);
    
    int                     PopFirst();
    int                     PopLast();
    
    void                    Save(FFile *pFile);
    void                    Load(FFile *pFile);
};

#endif /* FIntList_hpp */
