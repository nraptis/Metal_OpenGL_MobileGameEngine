//
//  FAchievementController.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 12/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FAchievementController_hpp
#define FAchievementController_hpp

#include "FAchievement.hpp"
#include "FAchievementGroup.hpp"
#include "FHashMap.hpp"

//Everything is uniquified based on "AchievementIdentifier"
//"AchievementTitle" and "AchievementDescription" are not saved, it is expected that
//the achievement structure is built-up by the program itself. You can re-organize it however
//you like, as long as you keep the same "AchievementIdentifier"

class FAchievementController {
public:
    FAchievementController();
    ~FAchievementController();
    
    void                                Clear();
    
    //Build the entire structure using only these two calls...
    //Build the entire structure, then call LOAD...
    void                                AddAchievement(const char *pAchievementIdentifier, const char *pAchievementTitle, const char *pAchievementDescription, int pPoints, int pProgressMax);
    void                                AddAchievement(const char *pGroupName, const char *pAchievementIdentifier, const char *pAchievementTitle, const char *pAchievementDescription, int pPoints, int pProgressMax);
    
    //mDescription
    FAchievement                        *GetAchievement(const char *pAchievementIdentifier);
    
private:
    void                                ProgressAchievementObject(FAchievement *pAchievement);
    
public:
    void                                ProgressAchievement(const char *pAchievementIdentifier);
    void                                ProgressGroup(const char *pGroupName);
    
    
    void                                ResetAchievement(const char *pAchievementIdentifier);
    void                                ResetGroup(const char *pGroupName);
    
    void                                Save();
    void                                Save(const char *pFile);
    
    void                                Load();
    void                                Load(const char *pFile);
    
    
    
    //List of all the groups...
    FList                               mGroupList;
    
    //List of all the achievements...
    FList                               mAchievementList;
    

    FList                               mRecentlyCompletedAchievementList;
    
private:
    FStringMap                          mGroupMap;
    FStringMap                          mAchievementMap;
    FHashMap                            mRecentlyCompletedAchievementMap;
    
};

#endif /* FAchievementController_hpp */
