//
//  FObject.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FObject.hpp"
#include "core_includes.h"

FObject::FObject() {
    mKill = 0;
}

FObject::~FObject() { }

void FObject::Kill() {
    if (mKill == 0) {
        mKill = 3;
    }
}

FObjectList::FObjectList() { }

FObjectList::~FObjectList() {
    Free();
}

void FObjectList::Add(void *pObject) {
    if (pObject != 0) {
        mObjectList.Add(pObject);
    }
}

void FObjectList::Free() {
    FreeList(FObject, mObjectList);
    FreeList(FObject, mObjectListKill);
}

void FObjectList::Update() {


    EnumList (FObject, aObject, mObjectList) {
        if (aObject->mKill == 0) {
            aObject->Update();
        }
        if (aObject->mKill) {
            mObjectListTemp.Add(aObject);
        }
    }
    
    if (mObjectListTemp.mCount > 0) {
        EnumList (FObject, aObject, mObjectListTemp) {
            mObjectList.Remove(aObject);
            mObjectListKill.Add(aObject);
        }
        mObjectListTemp.RemoveAll();
    }

    EnumList (FObject, aObject, mObjectListKill) {
        aObject->mKill--;
        if (aObject->mKill <= 0) {
            mObjectListDelete.Add(aObject);
        }
    }
    
    if (mObjectListDelete.mCount > 0) {
        EnumList (FObject, aObject, mObjectListDelete) {
            mObjectListKill.Remove(aObject);
            delete aObject;
        }
        mObjectListDelete.RemoveAll();
    }
}

void FObjectList::Draw() {
    EnumList (FObject, aObject, mObjectList) {
        if (aObject->mKill == 0) {
            aObject->Draw();
        }
    }
}

bool FObjectList::Empty() {
    bool aResult = false;
    EnumList(FObject, aObject, mObjectList) {
        if (aObject->mKill == 0) { aResult = true; }
    }
    return false;
}

void FObjectList::KillAll() {
    EnumList(FObject, aObject, mObjectList) {
        aObject->Kill();
    }
}









