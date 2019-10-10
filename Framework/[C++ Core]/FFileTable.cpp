//
//  FFileTable.cpp
//  FleetGL
//
//  Created by Nick Raptis on 2/9/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FFileTable.hpp"
#include "core_includes.h"

FFileTableNode::FFileTableNode() {
    mObject = 0;
    mNext = 0;
}

FFileTableNode::~FFileTableNode() { }

FFileTable::FFileTable() {
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
    mAllowDuplicateKeys = false;
    mAllowDuplicateFullKeys = false;
}

FFileTable::~FFileTable() {
    Clear();
}

void FFileTable::Clear() {
    FFileTableNode *aNode = NULL;
    FFileTableNode *aNext = NULL;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mNext;
            delete aNode;
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = NULL;
    mTableCount = 0;
    mTableSize = 0;
    FreeList(FFileTableNode, mQueue);
}

FFileTableNode *FFileTable::Add(const char *pKey, const char *pKeyFull, void *pObject) {
    FFileTableNode *aNode = 0;
    FFileTableNode *aHold = 0;
    unsigned int aHashBase = FFileTable::Hash(pKey);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                if (mAllowDuplicateKeys == false) {
                    return aNode;
                } else {
                    if (aNode->mKeyFull == pKeyFull) {
                        if (mAllowDuplicateFullKeys == false) {
                            return aNode;
                        }
                    }
                }
            }
            aNode = aNode->mNext;
        }
        
        if (mTableCount >= (mTableSize / 2)) {
            int aNewSize = FHashMap::IncreaseTableSize(mTableCount);
            SetTableSize(aNewSize);//mTableCount + (mTableCount / 2) + 12);
            aHash = (aHashBase % mTableSize);
        }
    } else {
        SetTableSize(7);
        aHash = (aHashBase % mTableSize);
    }

    FFileTableNode *aNew = (FFileTableNode *)mQueue.PopLast();
    if (!aNew) {
        aNew = new FFileTableNode();
    }
    aNew->mKey = pKey;
    aNew->mKeyFull = pKeyFull;
    aNew->mObject = pObject;
    aNew->mNext = 0;
    
    if (mTable[aHash]) {
        aNode = mTable[aHash];
        while (aNode) {
            aHold = aNode;
            aNode = aNode->mNext;
        }
        aHold->mNext = aNew;
    } else {
        mTable[aHash] = aNew;
    }
    mTableCount++;
    return aNew;
}



bool FFileTable::Remove(const char *pKey) {
    if (mTableSize > 0) {
        unsigned int aHash = (FFileTable::Hash(pKey) % mTableSize);
        FFileTableNode *aPreviousNode = 0;
        FFileTableNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                if (aPreviousNode) {
                    aPreviousNode->mNext = aNode->mNext;
                } else {
                    mTable[aHash] = aNode->mNext;
                }
                mQueue.Add(aNode);
                mTableCount -= 1;
                return true;
            }
            aPreviousNode = aNode;
            aNode = aNode->mNext;
        }
    }
    return false;
}

bool FFileTable::RemoveNode(FFileTableNode *pNode) {
    if (mTableSize > 0 && pNode != 0) {
        unsigned int aHash = (FFileTable::Hash(pNode->mKey.c()) % mTableSize);
        FFileTableNode *aPreviousNode = 0;
        FFileTableNode *aNode = mTable[aHash];
        while (aNode) {
            if(aNode == pNode) {
                if (aPreviousNode) {
                    aPreviousNode->mNext = aNode->mNext;
                } else {
                    mTable[aHash] = aNode->mNext;
                }
                mQueue.Add(aNode);
                mTableCount -= 1;
                return true;
            }
            aPreviousNode = aNode;
            aNode = aNode->mNext;
        }
    }
    return false;
}

void *FFileTable::Get(const char *pKey) {
    void *aResult = 0;
    if (mTableSize > 0) {
        unsigned int aHash = (FFileTable::Hash(pKey) % mTableSize);
        FFileTableNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                return aNode->mObject;
            }
            aNode = aNode->mNext;
        }
    }
    return aResult;
}

FFileTableNode *FFileTable::GetNode(const char *pKey) {
    if (mTableSize > 0) {
        unsigned int aHash = (FFileTable::Hash(pKey) % mTableSize);
        FFileTableNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                return aNode;
            }
            aNode = (aNode->mNext);
        }
    }
    return 0;
}

void FFileTable::GetAllNodes(const char *pKey, FList &pList) {
    if (mTableSize > 0) {
        unsigned int aHash = (FFileTable::Hash(pKey) % mTableSize);
        FFileTableNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                pList.Add(aNode);
            }
            aNode = (aNode->mNext);
        }
    }
}

void FFileTable::SetTableSize(int pSize) {
	FFileTableNode *aCheck = 0;
    FFileTableNode *aNext = 0;
    FFileTableNode *aNode = 0;
    int aNewSize = pSize;
    FFileTableNode **aTableNew = new FFileTableNode*[aNewSize];
    for (int i=0;i<aNewSize;i++) {
        aTableNew[i] = 0;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
		while (aNode) {
			aNext = aNode->mNext;
			aNode->mNext = 0;
			aHash = (FFileTable::Hash(aNode->mKey.c()) % aNewSize);
			if (aTableNew[aHash] == 0) {
				aTableNew[aHash] = aNode;
			} else {
				aCheck = aTableNew[aHash];
				while (aCheck->mNext) {
					aCheck = aCheck->mNext;
				}
				aCheck->mNext = aNode;
			}
			aNode = aNext;
		}
    }
    delete [] mTable;
    mTable = aTableNew;
    mTableSize = aNewSize;
}

unsigned int FFileTable::Hash(const char *pString) {
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

void FFileTable::Print() {
	Log("____\n____Hash Table____\n_Count = %d  Size = %d\n\n", mTableCount, mTableSize);

    FFileTableNode *aNode = 0;

    for (int i=0;i<mTableSize;i++) {
        int aCount = 0;
        aNode = mTable[i];
        while (aNode) {
            aCount++;
            aNode = aNode->mNext;
        }
        
		Log("Row[%d] (%d)\t{", i, aCount);
        
        aNode = mTable[i];
        while (aNode) {
			Log("{%s}", aNode->mKey.c());
            aNode = aNode->mNext;
        }
		Log("}\n");
    }
}

