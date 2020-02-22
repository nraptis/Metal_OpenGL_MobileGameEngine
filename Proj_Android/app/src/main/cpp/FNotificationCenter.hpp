//
//  FNotificationCenter.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef FNotificationCenter_hpp
#define FNotificationCenter_hpp

#include "FList.hpp"
#include "FString.hpp"

class FNotificationCenter;
class FCanvas;
class FNotificationTableNode {
    friend class FNotificationCenter;
    friend class FNotificationTable;
    
private:
    FNotificationTableNode();
    virtual ~FNotificationTableNode();
    void                                                Reset();
    FString                                             mNotification;
    FCanvas                                             *mSender;
    FNotificationTableNode                              *mNextNode;

    //List of FCanvas objects, this could be sped up
    //by using a linked list + hash table combination
    //structure, however, for our implementation, the
    //overhead of the hash table is more expensive than
    //the benefit received.
    FList                                               mListenerList;
};

class FNotificationTable {
    friend class FNotificationCenter;

private:
    FNotificationTable();
    virtual ~FNotificationTable();
    FNotificationTableNode                              *Add(const char *pNotification, FCanvas *pObserver, FCanvas *pSender);
    bool                                                RemoveNode(FNotificationTableNode *pNode);
    FNotificationTableNode                              *GetNode(const char *pNotification, FCanvas *pSender);
    void                                                SetTableSize(int pSize);
    unsigned int                                        Hash(const char *pNotification, FCanvas *pSender);

    FNotificationTableNode                              **mTable;
    int                                                 mTableCount;
    int                                                 mTableSize;
    FList                                               mQueue;
};

class FNotificationReceiverMapNode {
    friend class FNotificationReceiverMap;
    friend class FNotificationCenter;

private:
    FNotificationReceiverMapNode();
    virtual ~FNotificationReceiverMapNode();
    void                                        Reset();
    FCanvas                                     *mListener;
    FNotificationReceiverMapNode                *mTableNext;

    //List of FNotificationTableNode
    FList                                       mNotificationNodeList;
};

class FNotificationReceiverMap {
    friend class FNotificationCenter;

private:
    FNotificationReceiverMap();
    ~FNotificationReceiverMap();
    FNotificationReceiverMapNode                *Add(FCanvas *pObserver, FNotificationTableNode *pNode);
    FNotificationReceiverMapNode                *GetNode(FCanvas *pObserver);
    bool                                        RemoveNode(FNotificationReceiverMapNode *pNode);
    void                                        SetTableSize(int pSize);
    FNotificationReceiverMapNode                **mTable;
    int                                         mTableCount;
    int                                         mTableSize;
    FList                                       mQueue;
};

class FNotificationCenter {
public:
    FNotificationCenter();
    ~FNotificationCenter();

    void                                        Register(FCanvas *pObserver, FCanvas *pSender, const char *pNotification);
    void                                        Unregister(FCanvas *pObserver, FCanvas *pSender, const char *pNotification);
    void                                        Unregister(FCanvas *pObserver);
    void                                        Post(FCanvas *pSender, const char *pNotification);

    void                                        PrintStats();
    
    

protected:

    //"Forward" map...
    FNotificationTable                          mSendTable;

    //"Backward" map...
    FNotificationReceiverMap                    mRegisterTable;

    FList                                       mNodeList;
    FList                                       mPostList;
};

#endif

