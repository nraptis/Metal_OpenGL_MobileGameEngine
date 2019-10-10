//
//  FFileTable.h
//  Graveyard
//
//  Created by Nick Raptis on 2/25/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_HASH_TABLE_H
#define FRAMEWORK_HASH_TABLE_H

#include "FString.hpp"
#include "FList.hpp"

class FFileTableNode {
public:
    FFileTableNode();
    virtual ~FFileTableNode();
    
    void                                        *mObject;
    
    FString                                     mKey;
    FString                                     mKeyFull;

    FFileTableNode                              *mNext;
};

class FFileTable {
public:
    FFileTable();
    virtual ~FFileTable();
    
    FFileTableNode                              *Add(const char *pKey, const char *pKeyFull, void *pObject);
    FFileTableNode                              *Add(char *pKey, char *pKeyFull, void *pObject) { return Add((const char *)(pKey), (const char *)(pKeyFull), pObject); }
    FFileTableNode                              *Add(FString pKey, FString pKeyFull, void *pObject) { return Add((const char *)(pKey.c()), (const char *)(pKeyFull.c()), pObject); }
    FFileTableNode                              *Add(const char *pKey, void *pObject) { return Add(pKey, 0, pObject); }
    FFileTableNode                              *Add(char *pKey, void *pObject) { return Add((const char *)(pKey), pObject); }
    FFileTableNode                              *Add(FString pKey, void *pObject) { return Add((const char *)(pKey.c()), pObject); }

    bool                                        Remove(const char *pKey);
    bool                                        RemoveNode(FFileTableNode *pNode);
    
    //void                                        *Get(void *pKey); //, void *pObject
    void                                        *Get(const char *pKey);
    void                                        *Get(char *pKey){return Get((const char *)(pKey));}
    void                                        *Get(FString pKey){return Get((const char *)(pKey.c()));}
    
    FFileTableNode                              *GetNode(const char *pKey);
    FFileTableNode                              *GetNode(char *pKey){return GetNode((const char *)(pKey));}
    FFileTableNode                              *GetNode(FString pKey){return GetNode((const char *)(pKey.c()));}
    
    void                                        GetAllNodes(const char *pKey, FList &pList);

    static unsigned int                         Hash(const char *pString);
    
    
    void                                        SetTableSize(int pSize);
    
    bool                                        mAllowDuplicateKeys;
    bool                                        mAllowDuplicateFullKeys;
    
    void                                        Clear();
    
    void                                        Print();
    
    FFileTableNode                              **mTable;
    int                                         mTableCount;
    int                                         mTableSize;

    FList                                       mQueue;
};



#endif 
