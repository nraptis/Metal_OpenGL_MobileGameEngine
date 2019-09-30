//
//  FNotificationCenter.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "core_includes.h"
#include "FNotificationCenter.hpp"
#include "FCanvas.hpp"
#include "FFileTable.hpp"


FNotificationCenter::FNotificationCenter() {
    
}

FNotificationCenter::~FNotificationCenter() {
    
}

void FNotificationCenter::Register(FCanvas *pObserver, FCanvas *pSender, const char *pNotification) {
    if (pObserver == NULL || pNotification == NULL || pSender == NULL) { return; }
    mRegisterTable.Add(pObserver, mSendTable.Add(pNotification, pObserver, pSender));
}

void FNotificationCenter::Unregister(FCanvas *pObserver, FCanvas *pSender, const char *pNotification) {
    FNotificationReceiverMapNode *aRegistrationNode = mRegisterTable.GetNode(pObserver);
    if (aRegistrationNode != NULL) {
        mNodeList.RemoveAll();
        EnumList(FNotificationTableNode, aNotificationNode, aRegistrationNode->mNotificationNodeList) {
            //Assuming global removal...
            if (pSender == NULL && pNotification == NULL) {
                mNodeList.Add(aNotificationNode);
            } else {
                if(aNotificationNode->mSender == pSender && aNotificationNode->mNotification == pNotification) {
                    mNodeList.Add(aNotificationNode);
                }
            }
        }
        EnumList(FNotificationTableNode, aNotificationNode, mNodeList) {
            if (aRegistrationNode->mNotificationNodeList.mCount > 0) {
                aRegistrationNode->mNotificationNodeList.Remove(aNotificationNode);
                if (aRegistrationNode->mNotificationNodeList.mCount <= 0) {
                    //Log("Removing Notification Register[%s] [%s]\n", aNotificationNode->mSender->mName.c(), aNotificationNode->mNotification.c());
                    mRegisterTable.RemoveNode(aRegistrationNode);
                }
            }
        }
        EnumList(FNotificationTableNode, aNotificationNode, mNodeList) {
            if (aNotificationNode->mListenerList.mCount > 0) {
                aNotificationNode->mListenerList.Remove(pObserver);
                if (aNotificationNode->mListenerList.mCount <= 0) {
                    //Log("Removing Notification Sender[%s] [%s]\n", aNotificationNode->mSender->mName.c(), aNotificationNode->mNotification.c());
                    mSendTable.RemoveNode(aNotificationNode);
                }
            }
        }
    }
}

void FNotificationCenter::Unregister(FCanvas *pObserver) {
    Unregister(pObserver, NULL, NULL);
}

void FNotificationCenter::Post(FCanvas *pSender, const char *pNotification) {
    FNotificationTableNode *aNotificationNode = mSendTable.GetNode(pNotification, pSender);
    if (aNotificationNode != NULL) {
        mPostList.RemoveAll();
        mPostList.Add(aNotificationNode->mListenerList);
        EnumList(FCanvas, aCanvas, mPostList) {
            aCanvas->BaseNotify(pSender, pNotification);
        }
    }
}

void FNotificationCenter::PrintStats() {
    Log("FNotificationCenter::Senders(%d)\n", mSendTable.mTableCount);
    Log("FNotificationCenter::Register(%d)\n", mRegisterTable.mTableCount);
}

FNotificationReceiverMapNode::FNotificationReceiverMapNode() {
    mListener = NULL;
    mTableNext = NULL;
}

FNotificationReceiverMapNode::~FNotificationReceiverMapNode() { }

void FNotificationReceiverMapNode::Reset() {
    mNotificationNodeList.RemoveAll();
    mListener = NULL;
    mTableNext = NULL;
}

FNotificationReceiverMap::FNotificationReceiverMap() {
    mTable = NULL;
    mTableCount = 0;
    mTableSize = 0;
}

FNotificationReceiverMap::~FNotificationReceiverMap() {
    FNotificationReceiverMapNode *aNode = NULL;
    FNotificationReceiverMapNode *aNext = NULL;
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
    FreeList(FNotificationReceiverMapNode, mQueue);
}

FNotificationReceiverMapNode *FNotificationReceiverMap::Add(FCanvas *pObserver, FNotificationTableNode *pNode) {
    FNotificationReceiverMapNode *aNode = NULL;
    FNotificationReceiverMapNode *aHold = NULL;
    unsigned int aHashBase = FHashMap::Hash(pObserver);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while(aNode) {
            if(aNode->mListener == pObserver) {
                if (!aNode->mNotificationNodeList.Exists(pNode)) {
                    aNode->mNotificationNodeList.Add(pNode);
                }
                return aNode;
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

    FNotificationReceiverMapNode *aNew = (FNotificationReceiverMapNode *)mQueue.PopLast();
    if (aNew == NULL) {
        aNew = new FNotificationReceiverMapNode();
    }

    aNew->mListener = pObserver;
    aNew->mNotificationNodeList.Add(pNode);
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
    mTableCount += 1;
    return aNew;
}

FNotificationReceiverMapNode *FNotificationReceiverMap::GetNode(FCanvas *pObserver) {
    FNotificationReceiverMapNode *aResult = NULL;
    if (mTableSize > 0) {
        unsigned int aHash = FHashMap::Hash(pObserver) % mTableSize;
        FNotificationReceiverMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mListener == pObserver) {
                return aNode;
            }
            aNode = aNode->mTableNext;
        }
    }
    return aResult;
}

bool FNotificationReceiverMap::RemoveNode(FNotificationReceiverMapNode *pNode) {
    if (mTableSize > 0) {
        unsigned int aHash = FHashMap::Hash(pNode->mListener) % mTableSize;
        FNotificationReceiverMapNode *aPreviousNode = NULL;
        FNotificationReceiverMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode == pNode) {
                if (aPreviousNode) {
                    aPreviousNode->mTableNext = aNode->mTableNext;
                } else {
                    mTable[aHash] = aNode->mTableNext;
                }
                aNode->Reset();
                mQueue.Add(aNode);
                mTableCount -= 1;
                return true;
            }
            aPreviousNode = aNode;
            aNode = aNode->mTableNext;
        }
    }
    return false;
}

void FNotificationReceiverMap::SetTableSize(int pSize) {
    FNotificationReceiverMapNode *aCheck = NULL;
    FNotificationReceiverMapNode *aNext = NULL;
    FNotificationReceiverMapNode *aNode = NULL;
    int aNewSize = pSize;
    FNotificationReceiverMapNode **aTableNew = new FNotificationReceiverMapNode*[aNewSize];
    for(int i=0;i<aNewSize;i++) {
        aTableNew[i] = NULL;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            aNode->mTableNext = NULL;
            aHash = FHashMap::Hash(aNode->mListener) % aNewSize;
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

FNotificationTableNode::FNotificationTableNode() {
    mSender = NULL;
    mNextNode = NULL;
}

FNotificationTableNode::~FNotificationTableNode() { }

void FNotificationTableNode::Reset() {
    mListenerList.RemoveAll();
    mSender = NULL;
    mNextNode = NULL;
}

FNotificationTable::FNotificationTable() {
    mTable = NULL;
    mTableCount = 0;
    mTableSize = 0;
}

FNotificationTable::~FNotificationTable() {
    FNotificationTableNode *aNode = NULL;
    FNotificationTableNode *aNext = NULL;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mNextNode;
            delete aNode;
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = NULL;
    mTableCount = 0;
    mTableSize = 0;
    FreeList(FNotificationTableNode, mQueue);
}

FNotificationTableNode *FNotificationTable::Add(const char *pNotification, FCanvas *pObserver, FCanvas *pSender) {
    FNotificationTableNode *aNode = NULL;
    FNotificationTableNode *aHold = NULL;
    unsigned int aHashBase = Hash(pNotification, pSender);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mNotification == pNotification && aNode->mSender == pSender) {
                if (!aNode->mListenerList.Exists(pObserver)) {
                    aNode->mListenerList.Add(pObserver);
                }
                return aNode;
            }
            aNode = aNode->mNextNode;
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

    FNotificationTableNode *aNew = (FNotificationTableNode *)mQueue.PopLast();
    if (!aNew) { aNew = new FNotificationTableNode(); }
    aNew->mNotification = pNotification;
    aNew->mSender = pSender;
    aNew->mListenerList.Add(pObserver);
    aNew->mNextNode = NULL;
    if (mTable[aHash]) {
        aNode = mTable[aHash];
        while (aNode) {
            aHold = aNode;
            aNode = aNode->mNextNode;
        }
        aHold->mNextNode = aNew;
    } else {
        mTable[aHash] = aNew;
    }
    mTableCount++;
    return aNew;
}

bool FNotificationTable::RemoveNode(FNotificationTableNode *pNode) {
    if (mTableSize > 0 && pNode != NULL) {
        unsigned int aHash = (Hash(pNode->mNotification.c(), pNode->mSender) % mTableSize);
        FNotificationTableNode *aPreviousNode = 0;
        FNotificationTableNode *aNode = mTable[aHash];
        while (aNode) {
            if(aNode == pNode) {
                if (aPreviousNode) {
                    aPreviousNode->mNextNode = aNode->mNextNode;
                } else {
                    mTable[aHash] = aNode->mNextNode;
                }
                aNode->Reset();
                mQueue.Add(aNode);
                mTableCount -= 1;
                return true;
            }
            aPreviousNode = aNode;
            aNode = aNode->mNextNode;
        }
    }
    return false;
}

FNotificationTableNode *FNotificationTable::GetNode(const char *pNotification, FCanvas *pSender) {
    FNotificationTableNode *aResult = NULL;
    if (mTableSize > 0) {
        unsigned int aHash = (Hash(pNotification, pSender) % mTableSize);
        FNotificationTableNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mNotification == pNotification && pSender == aNode->mSender) {
                return aNode;
            }
            aNode = aNode->mNextNode;
        }
    }
    return aResult;
}

void FNotificationTable::SetTableSize(int pSize) {
    FNotificationTableNode *aCheck = 0;
    FNotificationTableNode *aNext = 0;
    FNotificationTableNode *aNode = 0;
    int aNewSize = pSize;
    FNotificationTableNode **aTableNew = new FNotificationTableNode*[aNewSize];
    for (int i=0;i<aNewSize;i++) {
        aTableNew[i] = NULL;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mNextNode;
            aNode->mNextNode = NULL;
            aHash = (Hash(aNode->mNotification.c(), aNode->mSender) % aNewSize);
            if (aTableNew[aHash] == NULL) {
                aTableNew[aHash] = aNode;
            } else {
                aCheck = aTableNew[aHash];
                while (aCheck->mNextNode) {
                    aCheck = aCheck->mNextNode;
                }
                aCheck->mNextNode = aNode;
            }
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = aTableNew;
    mTableSize = aNewSize;
}

unsigned int FNotificationTable::Hash(const char *pNotification, FCanvas *pSender) {
    unsigned int aHash1 = FHashMap::Hash(pSender);
    unsigned int aHash2 = FFileTable::Hash(pNotification);
    return aHash1 ^ aHash2;
}

