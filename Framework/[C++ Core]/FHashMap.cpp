//
//  FHashMap.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/3/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FHashMap.hpp"
#include "core_includes.h"

FHashMapNode::FHashMapNode() {
    mObject = NULL;
    mKey = NULL;
    mTableNext = NULL;
    mListPrev = NULL;
    mListNext = NULL;
    mTableIndex = -1;
}

FHashMapNode::~FHashMapNode() { }

FHashMap::FHashMap() {
    mTable = NULL;
    mTableCount = 0;
    mTableSize = 0;
    mListHead = NULL;
    mListTail = NULL;
}

FHashMap::~FHashMap() {
    FHashMapNode *aNode = NULL;
    FHashMapNode *aNext = NULL;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            delete aNode;
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = NULL;
    mTableCount = 0;
    mTableSize = 0;
    FreeList(FHashMapNode, mQueue);
    mListHead = NULL;
    mListTail = NULL;
}

void FHashMap::RemoveAll() {
    FHashMapNode *aNode = mListHead;
    while (aNode) {
        mQueue.Add(aNode);
        mTable[aNode->mTableIndex] = 0;
        aNode = aNode->mListNext;
    }
    mListHead = NULL;
    mListTail = NULL;
    mTableCount = 0;
}

void FHashMap::Add(void *pKey, void *pObject) {
    if ((pObject == NULL) || (pKey == NULL)) return;
    FHashMapNode *aNode = NULL;
    FHashMapNode *aHold = NULL;
    unsigned int aHashBase = FHashMap::Hash(pKey);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while(aNode) {
            if(aNode->mKey == pKey) {
                return;
            }
            aNode = aNode->mTableNext;
        }
        if (mTableCount >= (mTableSize / 2)) {
            int aNewSize = FHashMap::IncreaseTableSize(mTableCount);
            SetTableSize(aNewSize);
            aHash = (aHashBase % mTableSize);
        }
    } else {
        SetTableSize(7);
        aHash = (aHashBase % mTableSize);
    }
    
    FHashMapNode *aNew = (FHashMapNode *)mQueue.PopLast();
    if (aNew == NULL) {
        aNew = new FHashMapNode();
    }
    aNew->mKey = pKey;
    aNew->mObject = pObject;
    aNew->mTableNext = NULL;
    aNew->mTableIndex = aHash;
    if (mTable[aHash]) {
        aNode = mTable[aHash];
        while (aNode) {
            aHold = aNode;
            aNode = aNode->mTableNext;
        }
        aHold->mTableNext = aNew;
    } else {
        mTable[aHash] = aNew;
    }
    ListAdd(aNew);
    mTableCount += 1;
}

void FHashMap::Remove(void *pKey) {
    if (mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pKey) % mTableSize);
        FHashMapNode *aPreviousNode = NULL;
        FHashMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                if (aPreviousNode) {
                    aPreviousNode->mTableNext = aNode->mTableNext;
                } else {
                    mTable[aHash] = aNode->mTableNext;
                }
                mQueue.Add(aNode);
                ListRemove(aNode);
                mTableCount -= 1;
                return;
            }
            aPreviousNode = aNode;
            aNode = aNode->mTableNext;
        }
    }
}

void FHashMap::ListAdd(FHashMapNode *pNode) {
    pNode->mListNext = NULL;
    if (mListHead == NULL) {
        mListHead = pNode;
        mListTail = pNode;
        pNode->mListPrev = NULL;
    } else {
        pNode->mListPrev = mListTail;
        mListTail->mListNext = pNode;
        mListTail = pNode;
    }
}

void FHashMap::ListRemove(FHashMapNode *pNode) {
    if (pNode == mListHead) {
        if (mListHead->mListNext) {
            mListHead = mListHead->mListNext;
            mListHead->mListPrev = NULL;
        } else {
            mListTail = NULL;
            mListHead = NULL;
        }
    } else if(pNode == mListTail) {
        mListTail = mListTail->mListPrev;
        mListTail->mListNext = NULL;
    } else {
        pNode->mListPrev->mListNext = pNode->mListNext;
        pNode->mListNext->mListPrev = pNode->mListPrev;
    }
    pNode->mListPrev = NULL;
    pNode->mListNext = NULL;
}

bool FHashMap::IsEmpty() {
    return mTableCount <= 0;
}

bool FHashMap::Exists(void *pKey) {
    return Get(pKey) != 0;
}

void *FHashMap::Get(void *pKey) {
    if(mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pKey) % mTableSize);
        FHashMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                return aNode->mObject;
            }
            aNode = aNode->mTableNext;
        }
    }
    return 0;
}

void FHashMap::AddObjectsToList(FList *pList) {
    FHashMapNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mObject);
        aNode = aNode->mListNext;
    }
}

void FHashMap::AddObjectsToListAndRemoveAll(FList *pList) {
    FHashMapNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mObject);
        mQueue.Add(aNode);
        mTable[aNode->mTableIndex] = 0;
        aNode = aNode->mListNext;
    }
    mListHead = 0;
    mListTail = 0;
    mTableCount = 0;
}

int FHashMap::IncreaseTableSize(int pTableCount) {
    int aNewSize = pTableCount + 1;
    if(pTableCount < ((7 / 2) - 1))aNewSize = 7;
    else if(pTableCount < ((13 / 2) - 1))aNewSize = 13;
    else if(pTableCount < ((29 / 2) - 1))aNewSize = 29;
    else if(pTableCount < ((41 / 2) - 1))aNewSize = 41;
    else if(pTableCount < ((53 / 2) - 1))aNewSize = 53;
    else if(pTableCount < ((97 / 2) - 1))aNewSize = 97;
    else if(pTableCount < ((149 / 2) - 5))aNewSize = 149;
    else if(pTableCount < ((193 / 2) - 5))aNewSize = 193;
    else if(pTableCount < ((269 / 2) - 5))aNewSize = 269;
    else if(pTableCount < ((389 / 2) - 5))aNewSize = 389;
    else if(pTableCount < ((439 / 2) - 5))aNewSize = 439;
    else if(pTableCount < ((631 / 2) - 5))aNewSize = 631;
    else if(pTableCount < ((769 / 2) - 5))aNewSize = 769;
    else if(pTableCount < ((907 / 2) - 7))aNewSize = 907;
    else if(pTableCount < ((1213 / 2) - 7))aNewSize = 1213;
    else if(pTableCount < ((1543 / 2) - 7))aNewSize = 1543;
    else if(pTableCount < ((2089 / 2) - 7))aNewSize = 2089;
    else if(pTableCount < ((2557 / 2) - 9))aNewSize = 2557;
    else if(pTableCount < ((3079 / 2) - 13))aNewSize = 3079;
    else if(pTableCount < ((3613 / 2) - 13))aNewSize = 3613;
    else if(pTableCount < ((4013 / 2) - 13))aNewSize = 4013;
    else if(pTableCount < ((5119 / 2) - 13))aNewSize = 5119;
    else if(pTableCount < ((6151 / 2) - 13))aNewSize = 6151;
    else if(pTableCount < ((7151 / 2) - 13))aNewSize = 7151;
    else if(pTableCount < ((12289 / 2) - 17))aNewSize = 12289;
    else if(pTableCount < ((19073 / 2) - 17))aNewSize = 19073;
    else if(pTableCount < ((25453 / 2) - 17))aNewSize = 25453;
    else if(pTableCount < ((31013 / 2) - 17))aNewSize = 31013;
    else if(pTableCount < ((40127 / 2) - 17))aNewSize = 40127;
    else if(pTableCount < ((53549 / 2) - 21))aNewSize = 53549;
    else if(pTableCount < ((67121 / 2) - 21))aNewSize = 67121;
    else if(pTableCount < ((82003 / 2) - 21))aNewSize = 82003;
    else if(pTableCount < ((104729 / 2) - 21))aNewSize = 104729;
    else { aNewSize = (pTableCount + (pTableCount * 2) + 7); }
    return aNewSize;
}

void FHashMap::SetTableSize(int pSize) {
    FHashMapNode *aCheck = 0;
    FHashMapNode *aNext = 0;
    FHashMapNode *aNode = 0;
    int aNewSize = pSize;
    FHashMapNode **aTableNew = new FHashMapNode*[aNewSize];
    for(int i=0;i<aNewSize;i++) {
        aTableNew[i] = 0;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            aNode->mTableNext = 0;
            aHash = FHashMap::Hash(aNode->mKey) % aNewSize;
            aNode->mTableIndex = aHash;
            if(aTableNew[aHash] == 0) {
                aTableNew[aHash] = aNode;
            } else {
                aCheck = aTableNew[aHash];
                while (aCheck->mTableNext) {
                    aCheck = aCheck->mTableNext;
                }
                aCheck->mTableNext = aNode;
            }
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = aTableNew;
    mTableSize = aNewSize;
}



void FHashMap::GetAllNodes(void *pKey, FList &pList) {
    if (mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pKey) % mTableSize);
        FHashMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                pList.Add(aNode);
            }
            aNode = (aNode->mTableNext);
        }
    }
}


void FHashMap::Print() {
    Log("____\n____Hash Table____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueue.mCount, mQueue.mSize);
    FHashMapNode *aNode = 0;
    for (int i=0;i<mTableSize;i++) {
        int aCount = 0;
        aNode = mTable[i];
        while (aNode) {
            aCount++;
            aNode = aNode->mTableNext;
        }
        Log("Row[%d] (%d)\t{", i, aCount);
        aNode = mTable[i];
        while(aNode) {
            Log("{%lx}", (unsigned long)(aNode->mObject));
            aNode = aNode->mTableNext;
        }
        Log("}\n");
    }
}

void FHashMap::PrintList() {
    Log("____\n____Hash List____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueue.mCount, mQueue.mSize);
    int aIndex = 0;
    if (mListHead == 0) {
        Log("*** EMPTY ***\n");
    } else {
        FHashMapNode *aNode = mListHead;
        while (aNode) {
            Log("[%lx], ", (unsigned long)(aNode->mObject));
            aNode = aNode->mListNext;
            aIndex += 1;
            if (aIndex >= 10) {
                aIndex -= 10;
                Log("\n");
            }
        }
    }
    Log("\n\n");
}








FIntMapNode::FIntMapNode() {
    mObject = 0;
    mKey = 0;
    mTableNext = 0;
    mListPrev = 0;
    mListNext = 0;
    mTableIndex = -1;
}

FIntMapNode::~FIntMapNode() { }

FIntMap::FIntMap() {
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
    mListHead = 0;
    mListTail = 0;
}

FIntMap::~FIntMap() {
    FIntMapNode *aNode = 0;
    FIntMapNode *aNext = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            delete aNode;
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
    FreeList(FIntMapNode, mQueue);
    mListHead = 0;
    mListTail = 0;
}

void FIntMap::RemoveAll() {
    FIntMapNode *aNode = mListHead;
    while (aNode) {
        mQueue.Add(aNode);
        mTable[aNode->mTableIndex] = 0;
        aNode = aNode->mListNext;
    }
    mListHead = 0;
    mListTail = 0;
    mTableCount = 0;
}

void FIntMap::Add(int pKey, void *pObject) {
    FIntMapNode *aNode = 0;
    FIntMapNode *aHold = 0;
    unsigned int aHashBase = FIntMap::Hash(pKey);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while(aNode) {
            if(aNode->mKey == pKey) {
                return;
            }
            aNode = aNode->mTableNext;
        }
        if (mTableCount >= (mTableSize / 2)) {
            int aNewSize = FHashMap::IncreaseTableSize(mTableCount);
            SetTableSize(aNewSize);
            aHash = (aHashBase % mTableSize);
        }
    } else {
        SetTableSize(7);
        aHash = (aHashBase % mTableSize);
    }
    
    FIntMapNode *aNew = (FIntMapNode *)mQueue.PopLast();
    if (aNew == 0) {
        aNew = new FIntMapNode();
    }
    aNew->mKey = pKey;
    aNew->mObject = pObject;
    aNew->mTableNext = 0;
    aNew->mTableIndex = aHash;
    if (mTable[aHash]) {
        aNode = mTable[aHash];
        while (aNode) {
            aHold = aNode;
            aNode = aNode->mTableNext;
        }
        aHold->mTableNext = aNew;
    } else {
        mTable[aHash] = aNew;
    }
    ListAdd(aNew);
    mTableCount += 1;
}

void FIntMap::Remove(int pKey) {
    if (mTableSize > 0) {
        unsigned int aHash = (FIntMap::Hash(pKey) % mTableSize);
        FIntMapNode *aPreviousNode = 0;
        FIntMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                if (aPreviousNode) {
                    aPreviousNode->mTableNext = aNode->mTableNext;
                } else {
                    mTable[aHash] = aNode->mTableNext;
                }
                mQueue.Add(aNode);
                ListRemove(aNode);
                mTableCount -= 1;
                return;
            }
            aPreviousNode = aNode;
            aNode = aNode->mTableNext;
        }
    }
}

void FIntMap::ListAdd(FIntMapNode *pNode) {
    pNode->mListNext = NULL;
    if (mListHead == NULL) {
        mListHead = pNode;
        mListTail = pNode;
        pNode->mListPrev = NULL;
    } else {
        pNode->mListPrev = mListTail;
        mListTail->mListNext = pNode;
        mListTail = pNode;
    }
}

void FIntMap::ListRemove(FIntMapNode *pNode) {
    if (pNode == mListHead) {
        if (mListHead->mListNext) {
            mListHead = mListHead->mListNext;
            mListHead->mListPrev = NULL;
        } else {
            mListTail = NULL;
            mListHead = NULL;
        }
    } else if(pNode == mListTail) {
        mListTail = mListTail->mListPrev;
        mListTail->mListNext = NULL;
    } else {
        pNode->mListPrev->mListNext = pNode->mListNext;
        pNode->mListNext->mListPrev = pNode->mListPrev;
    }
    pNode->mListPrev = NULL;
    pNode->mListNext = NULL;
}

bool FIntMap::IsEmpty() {
    return mTableCount <= 0;
}

bool FIntMap::Exists(int pKey) {
    return Get(pKey) != NULL;
}

void *FIntMap::Get(int pKey) {
    if(mTableSize > 0) {
        unsigned int aHash = (FIntMap::Hash(pKey) % mTableSize);
        FIntMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                return aNode->mObject;
            }
            aNode = aNode->mTableNext;
        }
    }
    return NULL;
}

void FIntMap::AddObjectsToList(FList *pList) {
    FIntMapNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mObject);
        aNode = aNode->mListNext;
    }
}

void FIntMap::AddObjectsToListAndRemoveAll(FList *pList) {
    FIntMapNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mObject);
        mQueue.Add(aNode);
        mTable[aNode->mTableIndex] = NULL;
        aNode = aNode->mListNext;
    }
    mListHead = NULL;
    mListTail = NULL;
    mTableCount = 0;
}

void FIntMap::SetTableSize(int pSize) {
    FIntMapNode *aCheck = NULL;
    FIntMapNode *aNext = NULL;
    FIntMapNode *aNode = NULL;
    int aNewSize = pSize;
    FIntMapNode **aTableNew = new FIntMapNode*[aNewSize];
    for(int i=0;i<aNewSize;i++) {
        aTableNew[i] = NULL;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            aNode->mTableNext = 0;
            aHash = FIntMap::Hash(aNode->mKey) % aNewSize;
            aNode->mTableIndex = aHash;
            if(aTableNew[aHash] == 0) {
                aTableNew[aHash] = aNode;
            } else {
                aCheck = aTableNew[aHash];
                while (aCheck->mTableNext) {
                    aCheck = aCheck->mTableNext;
                }
                aCheck->mTableNext = aNode;
            }
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = aTableNew;
    mTableSize = aNewSize;
}

void FIntMap::Print() {
    Log("____\n____Hash Table____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueue.mCount, mQueue.mSize);
    FIntMapNode *aNode = 0;
    for (int i=0;i<mTableSize;i++) {
        int aCount = 0;
        aNode = mTable[i];
        while (aNode) {
            aCount++;
            aNode = aNode->mTableNext;
        }
        Log("Row[%d] (%d)\t{", i, aCount);
        aNode = mTable[i];
        while(aNode) {
            Log("{%lx}", (unsigned long)(aNode->mObject));
            aNode = aNode->mTableNext;
        }
        Log("}\n");
    }
}

void FIntMap::PrintList() {
    Log("____\n____Hash List____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueue.mCount, mQueue.mSize);
    int aIndex = 0;
    if (mListHead == 0) {
        Log("*** EMPTY ***\n");
    } else {
        FIntMapNode *aNode = mListHead;
        while (aNode) {
            Log("[%lx], ", (unsigned long)(aNode->mObject));
            aNode = aNode->mListNext;
            aIndex += 1;
            if (aIndex >= 10) {
                aIndex -= 10;
                Log("\n");
            }
        }
    }
    Log("\n\n");
}

FStringMapNode::FStringMapNode() {
    mObject = NULL;
    mTableNext = NULL;
    mListPrev = NULL;
    mListNext = NULL;
    mTableIndex = -1;
}

FStringMapNode::~FStringMapNode() { }

FStringMap::FStringMap() {
    mTable = NULL;
    mTableCount = 0;
    mTableSize = 0;
    mListHead = NULL;
    mListTail = NULL;
}

FStringMap::~FStringMap() {
    FStringMapNode *aNode = NULL;
    FStringMapNode *aNext = NULL;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            delete aNode;
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = NULL;
    mTableCount = 0;
    mTableSize = 0;
    FreeList(FStringMapNode, mQueue);
    mListHead = NULL;
    mListTail = NULL;
}

void FStringMap::RemoveAll() {
    FStringMapNode *aNode = mListHead;
    while (aNode) {
        mQueue.Add(aNode);
        mTable[aNode->mTableIndex] = NULL;
        aNode = aNode->mListNext;
    }
    mListHead = NULL;
    mListTail = NULL;
    mTableCount = 0;
}

void FStringMap::Add(const char *pKey, void *pObject) {
    FStringMapNode *aNode = NULL;
    FStringMapNode *aHold = NULL;
    unsigned int aHashBase = FStringMap::Hash(pKey);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while(aNode) {
            if(aNode->mKey == pKey) {
                Log("Double Add[%s]\n", pKey);
                return;
            }
            aNode = aNode->mTableNext;
        }
        if (mTableCount >= (mTableSize / 2)) {
            int aNewSize = FHashMap::IncreaseTableSize(mTableCount);
            SetTableSize(aNewSize);
            aHash = (aHashBase % mTableSize);
        }
    } else {
        SetTableSize(7);
        aHash = (aHashBase % mTableSize);
    }
    
    FStringMapNode *aNew = (FStringMapNode *)mQueue.PopLast();
    if (aNew == NULL) {
        aNew = new FStringMapNode();
    }
    aNew->mKey = pKey;
    aNew->mObject = pObject;
    aNew->mTableNext = NULL;
    aNew->mTableIndex = aHash;
    if (mTable[aHash]) {
        aNode = mTable[aHash];
        while (aNode) {
            aHold = aNode;
            aNode = aNode->mTableNext;
        }
        aHold->mTableNext = aNew;
    } else {
        mTable[aHash] = aNew;
    }
    ListAdd(aNew);
    mTableCount += 1;
}

void FStringMap::Remove(const char *pKey) {
    if (mTableSize > 0) {
        unsigned int aHash = (FStringMap::Hash(pKey) % mTableSize);
        FStringMapNode *aPreviousNode = 0;
        FStringMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                if (aPreviousNode) {
                    aPreviousNode->mTableNext = aNode->mTableNext;
                } else {
                    mTable[aHash] = aNode->mTableNext;
                }
                mQueue.Add(aNode);
                ListRemove(aNode);
                mTableCount -= 1;
                return;
            }
            aPreviousNode = aNode;
            aNode = aNode->mTableNext;
        }
    }
}

void FStringMap::ListAdd(FStringMapNode *pNode) {
    pNode->mListNext = NULL;
    if (mListHead == NULL) {
        mListHead = pNode;
        mListTail = pNode;
        pNode->mListPrev = NULL;
    } else {
        pNode->mListPrev = mListTail;
        mListTail->mListNext = pNode;
        mListTail = pNode;
    }
}

void FStringMap::ListRemove(FStringMapNode *pNode) {
    if (pNode == mListHead) {
        if (mListHead->mListNext) {
            mListHead = mListHead->mListNext;
            mListHead->mListPrev = NULL;
        } else {
            mListTail = NULL;
            mListHead = NULL;
        }
    } else if(pNode == mListTail) {
        mListTail = mListTail->mListPrev;
        mListTail->mListNext = NULL;
    } else {
        pNode->mListPrev->mListNext = pNode->mListNext;
        pNode->mListNext->mListPrev = pNode->mListPrev;
    }
    pNode->mListPrev = NULL;
    pNode->mListNext = NULL;
}

bool FStringMap::IsEmpty() {
    return mTableCount <= 0;
}

bool FStringMap::Exists(const char *pKey) {
    return Get(pKey) != NULL;
}

void *FStringMap::Get(const char *pKey) {
    if (mTableSize > 0) {
        unsigned int aHash = (FStringMap::Hash(pKey) % mTableSize);
        FStringMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                return aNode->mObject;
            }
            aNode = aNode->mTableNext;
        }
    }
    return NULL;
}

unsigned int FStringMap::Hash(const char *pString) {
    unsigned long aHash = 5381;
    if (pString) {
        unsigned char *aString = (unsigned char *)pString;
        while (*aString) {
            int aVal = *aString;
            aHash = ((aHash << 5) + aHash) ^ aVal;
            aString++;
        }
    }
    return (unsigned int)aHash;
}

void FStringMap::AddObjectsToList(FList *pList) {
    FStringMapNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mObject);
        aNode = aNode->mListNext;
    }
}

void FStringMap::AddObjectsToListAndRemoveAll(FList *pList) {
    FStringMapNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mObject);
        mQueue.Add(aNode);
        mTable[aNode->mTableIndex] = NULL;
        aNode = aNode->mListNext;
    }
    mListHead = NULL;
    mListTail = NULL;
    mTableCount = 0;
}

void FStringMap::SetTableSize(int pSize) {
    FStringMapNode *aCheck = NULL;
    FStringMapNode *aNext = NULL;
    FStringMapNode *aNode = NULL;
    int aNewSize = pSize;
    FStringMapNode **aTableNew = new FStringMapNode*[aNewSize];
    for(int i=0;i<aNewSize;i++) {
        aTableNew[i] = NULL;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            aNode->mTableNext = NULL;
            aHash = FStringMap::Hash((const char *)(aNode->mKey.c())) % aNewSize;
            aNode->mTableIndex = aHash;
            if(aTableNew[aHash] == NULL) {
                aTableNew[aHash] = aNode;
            } else {
                aCheck = aTableNew[aHash];
                while (aCheck->mTableNext) {
                    aCheck = aCheck->mTableNext;
                }
                aCheck->mTableNext = aNode;
            }
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = aTableNew;
    mTableSize = aNewSize;
}

void FStringMap::Print() {
    Log("____\n____Hash Table____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueue.mCount, mQueue.mSize);
    FStringMapNode *aNode = NULL;
    for (int i=0;i<mTableSize;i++) {
        int aCount = 0;
        aNode = mTable[i];
        while (aNode) {
            aCount++;
            aNode = aNode->mTableNext;
        }
        Log("Row[%d] (%d)\t{", i, aCount);
        aNode = mTable[i];
        while(aNode) {
            Log("{%lx}", (unsigned long)(aNode->mObject));
            aNode = aNode->mTableNext;
        }
        Log("}\n");
    }
}

void FStringMap::PrintList() {
    Log("____\n____Hash List____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueue.mCount, mQueue.mSize);
    int aIndex = 0;
    if (mListHead == NULL) {
        Log("*** EMPTY ***\n");
    } else {
        FStringMapNode *aNode = mListHead;
        while (aNode) {
            Log("[%lx], ", (unsigned long)(aNode->mObject));
            aNode = aNode->mListNext;
            aIndex += 1;
            if (aIndex >= 10) {
                aIndex -= 10;
                Log("\n");
            }
        }
    }
    Log("\n\n");
}

