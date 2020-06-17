//
//  FAchievement.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 12/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FAchievement.hpp"
#include "core_includes.h"

FAchievement::FAchievement() {
    
    mProgress = 0;
    mProgressMax = 1;
    
    mPoints = 1;
    
    mComplete = false;
    
    mSynchronized = false;
}

FAchievement::~FAchievement() {
    
}

void FAchievement::Reset() {
    mProgress = 0;
}

void FAchievement::Print() {
    Log("id: %s: complete: %d (%d/%d) synced: %d\n", mIdentifier.c(), mComplete, mProgress, mProgressMax, mSynchronized);
}

void FAchievement::Load(FJSONNode *pLoadNode) {
    if (pLoadNode != NULL) {
        mProgress = pLoadNode->GetInt("progress", 0);
        mComplete = pLoadNode->GetBool("complete", false);
        mSynchronized = pLoadNode->GetBool("synced", false);
    }
}

FJSONNode *FAchievement::Save() {
    FJSONNode *aSaveNode = new FJSONNode();
    aSaveNode->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    if (mProgress != 0) { aSaveNode->AddDictionaryInt("progress", mProgress); }
    if (mComplete == true) { aSaveNode->AddDictionaryBool("complete", mComplete); }
    if (mSynchronized == true) { aSaveNode->AddDictionaryBool("synced", mSynchronized); }
    
    return aSaveNode;
}

bool FAchievement::AddProgress(int pProgress) {
    if (mProgress < mProgressMax) {
        mProgress += pProgress;
        if (mProgress > mProgressMax) { mProgress = mProgressMax; }
        if (mProgress < 0) { mProgress = 0; }
        if (mProgress == mProgressMax) {
            mComplete = true;
            return true;
        }
    } else {
        mProgress = mProgressMax;
    }
    return false;
}
