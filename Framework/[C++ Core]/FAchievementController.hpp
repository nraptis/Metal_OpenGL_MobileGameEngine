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

//The basic assumption is that the general achievement structure will be
//set up on app load, and then load will take all the previously existing
//achievements and synchronize them to the current list...

class FAchievementController {
public:
    FAchievementController();
    ~FAchievementController();
    
    void                                Clear();
    
    //Build the entire structure using only these two calls...
    //Build the entire structure, then call LOAD...
    void                                AddAchievement(const char *pAchievementName, int pProgressMax);
    void                                AddAchievement(const char *pGroupName, const char *pAchievementName, int pProgressMax);
    
    
    FAchievement                        *GetAchievement(const char *pAchievementName);
    
private:
    void                                ProgressAchievementObject(FAchievement *pAchievement);
    
public:
    void                                ProgressAchievement(const char *pAchievementName);
    void                                ProgressGroup(const char *pGroupName);
    
    
    void                                ResetAchievement(const char *pAchievementName);
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
