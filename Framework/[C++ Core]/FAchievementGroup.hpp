//
//  FAchievementGroup.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 12/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FAchievementGroup_hpp
#define FAchievementGroup_hpp

#include "FList.hpp"
#include "FString.hpp"

class FAchievement;
class FAchievementGroup {
public:
    FAchievementGroup();
    ~FAchievementGroup();
    
    void                        Add(FAchievement *pAchievement);
    
    FList                       mAchievementList;
    FString                     mName;
    
    
};

#endif /* FAchievementGroup_hpp */
