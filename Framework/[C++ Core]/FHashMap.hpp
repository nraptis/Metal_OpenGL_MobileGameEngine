//
//  FHashMap.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/3/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FHashMap_hpp
#define FHashMap_hpp

#include "FList.hpp"
#include "FString.hpp"

class FHashMap;
class FHashMapNode {
    friend class FHashMap;
    
public:
    FHashMapNode();
    virtual ~FHashMapNode();
    
    void                                        *mKey;
    void                                        *mObject;
    
    FHashMapNode                                *mListNext;
private:
    
    FHashMapNode                                *mListPrev;
    FHashMapNode                                *mTableNext;
    int                                         mTableIndex;
    
};

class FHashMap {
public:
    FHashMap();
    ~FHashMap();
    
    void                                        Add(void *pKey, void *pObject);
    void                                        Remove(void *pKey);
    bool                                        Exists(void *pKey);
    void                                        *Get(void *pKey);
    
    static inline unsigned int                  Hash(void *pKey) {
        unsigned long aResult = (unsigned long)pKey;
        aResult = ((aResult >> 16) ^ (aResult));
        return (unsigned int)aResult;
    }
    
    static int                                  IncreaseTableSize(int pTableCount);
    
    bool                                        IsEmpty();
    
    void                                        RemoveAll();
    
    void                                        AddObjectsToList(FList *pList);
    void                                        AddObjectsToListAndRemoveAll(FList *pList);
    
    void                                        GetAllNodes(void *pKey, FList &pList);
    
public:
    
    int                                         GetCount() { return mTableCount; }
    
    void                                        Print();
    void                                        PrintList();
    FHashMapNode                                *mListHead;
    FHashMapNode                                *mListTail;
    
protected:
    
    void                                        ListAdd(FHashMapNode *pNode);
    void                                        ListRemove(FHashMapNode *pNode);
    void                                        SetTableSize(int pSize);
    
    FHashMapNode                                **mTable;
    int                                         mTableCount;
    int                                         mTableSize;
    
    FList                                       mQueue;
};

class FIntMap;
class FIntMapNode {
    friend class FIntMap;
    
public:
    FIntMapNode();
    virtual ~FIntMapNode();
    
    int                                         mKey;
    void                                        *mObject;
    
    
    FIntMapNode                                 *mListNext;
private:
    
    FIntMapNode                                 *mListPrev;
    
    FIntMapNode                                 *mTableNext;
    int                                         mTableIndex;
    
};

class FIntMap {
public:
    FIntMap();
    ~FIntMap();
    
    void                                        Add(int pKey, void *pObject);
    void                                        Remove(int pKey);
    bool                                        Exists(int pKey);
    void                                        *Get(int pKey);
    
    static inline unsigned int                  Hash(int pKey) {
        unsigned long aResult = (unsigned long)pKey;
        aResult = ((aResult >> 16) ^ (aResult));
        return (unsigned int)aResult;
    }
    
    bool                                        IsEmpty();
    
    void                                        RemoveAll();
    
    void                                        AddObjectsToList(FList *pList);
    void                                        AddObjectsToListAndRemoveAll(FList *pList);
    
public:
    void                                        Print();
    void                                        PrintList();
    
    int                                         GetCount() { return mTableCount; }
    
    FIntMapNode                                 *mListHead;
    FIntMapNode                                 *mListTail;
    
protected:
    
    void                                        ListAdd(FIntMapNode *pNode);
    void                                        ListRemove(FIntMapNode *pNode);
    void                                        SetTableSize(int pSize);
    
    FIntMapNode                                 **mTable;
    int                                         mTableCount;
    int                                         mTableSize;
    
    FList                                       mQueue;
};



class FStringMap;
class FStringMapNode {
    friend class FStringMap;
    
public:
    FStringMapNode();
    virtual ~FStringMapNode();
    
    FString                                     mKey;
    void                                        *mObject;
    
    FStringMapNode                              *mListNext;
private:
    
    FStringMapNode                              *mListPrev;
    FStringMapNode                              *mTableNext;
    int                                         mTableIndex;
    
};

class FStringMap {
public:
    FStringMap();
    ~FStringMap();
    
    //
    
    void                                        Add(const char *pKey, void *pObject);
    void                                        Remove(const char *pKey);
    bool                                        Exists(const char *pKey);
    void                                        *Get(const char *pKey);
    
    static unsigned int                         Hash(const char *pString);
    
    bool                                        IsEmpty();
    
    void                                        RemoveAll();
    
    void                                        AddObjectsToList(FList *pList);
    void                                        AddObjectsToListAndRemoveAll(FList *pList);
    
public:
    void                                        Print();
    void                                        PrintList();
    
    FStringMapNode                              *mListHead;
    FStringMapNode                              *mListTail;
    
    int                                         GetCount() { return mTableCount; }
    
protected:
    
    void                                        ListAdd(FStringMapNode *pNode);
    void                                        ListRemove(FStringMapNode *pNode);
    void                                        SetTableSize(int pSize);
    
    FStringMapNode                                **mTable;
    int                                         mTableCount;
    int                                         mTableSize;
    
    FList                                       mQueue;
};




#endif /* FHashMap_hpp */
