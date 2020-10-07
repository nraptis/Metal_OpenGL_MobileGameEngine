//
//  FAchievementController.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 12/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FAchievementController.hpp"

FAchievementController::FAchievementController() {
    
}

FAchievementController::~FAchievementController() {
    
}

void FAchievementController::Clear() {
    
    FreeList(FAchievementGroup, mGroupList);
    FreeList(FAchievement, mAchievementList);
    
    mAchievementMap.RemoveAll();
    mGroupMap.RemoveAll();
}

void FAchievementController::AddAchievement(const char *pAchievementIdentifier, const char *pAchievementTitle, const char *pAchievementDescription, int pPoints, int pProgressMax) {
    FAchievement *aAchievement = (FAchievement *)(mAchievementMap.Get(pAchievementIdentifier));
    if (aAchievement == NULL) {
        aAchievement = new FAchievement();
        mAchievementMap.Add(pAchievementIdentifier, aAchievement);
        mAchievementList.Add(aAchievement);
    }
    aAchievement->mIdentifier = pAchievementIdentifier;
    aAchievement->mTitle = pAchievementTitle;
    aAchievement->mDescription = pAchievementDescription;
    aAchievement->mProgressMax = pProgressMax;
    aAchievement->mPoints = pPoints;
}

void FAchievementController::AddAchievement(const char *pGroupName, const char *pAchievementIdentifier, const char *pAchievementTitle, const char *pAchievementDescription, int pPoints, int pProgressMax) {
    FAchievementGroup *aGroup = (FAchievementGroup *)(mAchievementMap.Get(pGroupName));
    if (aGroup == NULL) {
        aGroup = new FAchievementGroup();
        aGroup->mName = pGroupName;
        mAchievementMap.Add(pGroupName, aGroup);
        mGroupList.Add(aGroup);
    }
    AddAchievement(pAchievementIdentifier, pAchievementTitle, pAchievementDescription, pPoints, pProgressMax);
    FAchievement *aAchievement = GetAchievement(pAchievementIdentifier);
    if (aAchievement == NULL) {
        Log("CRITICAL ERROR: Achievement not found???\n\n");
        return;
    }
    aGroup->Add(aAchievement);
}

FAchievement *FAchievementController::GetAchievement(const char *pAchievementIdentifier) {
    FAchievement *aAchievement = (FAchievement *)(mAchievementMap.Get(pAchievementIdentifier));
    return aAchievement;
}

void FAchievementController::ProgressAchievementObject(FAchievement *pAchievement) {
    if (pAchievement == NULL) { return; }
    if (pAchievement->AddProgress() == true) {
        if (mRecentlyCompletedAchievementMap.Exists(pAchievement) == false) {
            mRecentlyCompletedAchievementList.Add(pAchievement);
            mRecentlyCompletedAchievementMap.Add(pAchievement, pAchievement);
        }
    }
}

void FAchievementController::ProgressAchievement(const char *pAchievementIdentifier) {
    FAchievement *aAchievement = GetAchievement(pAchievementIdentifier);
    ProgressAchievementObject(aAchievement);
}

void FAchievementController::ProgressGroup(const char *pGroupName) {
    FAchievementGroup *aGroup = (FAchievementGroup *)(mAchievementMap.Get(pGroupName));
    if (aGroup != NULL) {
        EnumList(FAchievement, aAchievement, aGroup->mAchievementList) {
            ProgressAchievementObject(aAchievement);
        }
    }
}

void FAchievementController::ResetAchievement(const char *pAchievementIdentifier) {
    FAchievement *aAchievement = GetAchievement(pAchievementIdentifier);
    if (aAchievement != NULL) {
        aAchievement->Reset();
    }
}

void FAchievementController::ResetGroup(const char *pGroupName) {
    FAchievementGroup *aGroup = (FAchievementGroup *)(mAchievementMap.Get(pGroupName));
    if (aGroup != NULL) {
        EnumList(FAchievement, aAchievement, aGroup->mAchievementList) {
            aAchievement->Reset();
        }
    }
}


void FAchievementController::Save() {
    FString aPath = gDirDocuments + "achievement_data.json";
    Save(((const char *)aPath.c()));
}

void FAchievementController::Save(const char *pFile) {
    FJSON aJSON;
    FJSONNode *aRoot = new FJSONNode();
    aRoot->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    Save(aRoot, "achievement_data");
    aJSON.mRoot = aRoot;
    aJSON.Save(pFile);
}

void FAchievementController::Save(FJSONNode *pNode, const char *pTagName) {
    if (pNode == NULL) { return; }
    
    FJSONNode *aAchiementDataNode = new FJSONNode();
    aAchiementDataNode->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    pNode->AddDictionary(pTagName, aAchiementDataNode);
    
    FJSONNode *aAchiementListNode = new FJSONNode();
    aAchiementListNode->mNodeType = JSON_NODE_TYPE_DICTIONARY;
    aAchiementDataNode->AddDictionary("list", aAchiementListNode);
    
    EnumList(FAchievement, aAchievement, mAchievementList) {
        aAchiementListNode->AddDictionary(aAchievement->mIdentifier.c(), aAchievement->Save());
    }
    
    if (mRecentlyCompletedAchievementList.mCount > 0) {
        FJSONNode *aRecentlyCompletedListNode = new FJSONNode();
        aRecentlyCompletedListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
        aAchiementDataNode->AddDictionary("recently_completed", aRecentlyCompletedListNode);
        
        EnumList(FAchievement, aAchievement, mRecentlyCompletedAchievementList) {
            aRecentlyCompletedListNode->ArrayAddString(aAchievement->mIdentifier.c());
        }
    }
}

void FAchievementController::Load() {
    FString aPath = gDirDocuments + "achievement_data.json";
    Load(((const char *)aPath.c()));
}

void FAchievementController::Load(const char *pFile) {
    
    FJSON aJSON;
    aJSON.Load(pFile);
    
    FJSONNode *aRoot = aJSON.mRoot;
    if (aRoot == NULL) {
        return;
    }
    
    Load(aRoot, "achievement_data");
}

void FAchievementController::Load(FJSONNode *pNode, const char *pTagName) {
    
    if (pNode == NULL) { return; }
    
    
    
    
    FJSONNode *aAchiementDataNode = pNode->GetDictionary(pTagName);
    
    if (aAchiementDataNode == NULL) {
        printf("Missing Achiement Data...\n");
        return;
    }
    
    
    
    FJSONNode *aAchiementListNode = aAchiementDataNode->GetDictionary("list");
    if (aAchiementListNode != NULL) {
        
        FStringMap *aInfo = aAchiementListNode->mInfo;
        if (aInfo != NULL) {
            
            FStringMapNode *aNode = aInfo->mListHead;
            while (aNode != NULL) {
                
                FAchievement *aAchievement = GetAchievement(aNode->mKey.c());
                
                if (aAchievement != NULL) {
                    
                    FJSONNode *aLoadNode = ((FJSONNode *)aNode->mObject);
                    if (aLoadNode != NULL) {
                        aAchievement->Load(aLoadNode);
                    }
                }
                aNode = aNode->mListNext;
            }
        }
    }
    
    FJSONNode *aRecentlyCompletedListNode = aAchiementDataNode->GetArray("recently_completed");
    if (aRecentlyCompletedListNode != NULL) {
        EnumJSONArray(aRecentlyCompletedListNode, aRecentlyCompletedNode) {
            FAchievement *aAchievement = GetAchievement(aRecentlyCompletedNode->mValue);
            if (aAchievement != NULL) {
                if (mRecentlyCompletedAchievementMap.Exists(aAchievement) == false) {
                    mRecentlyCompletedAchievementList.Add(aAchievement);
                    mRecentlyCompletedAchievementMap.Add(aAchievement, aAchievement);
                }
            }
        }
    }
}
