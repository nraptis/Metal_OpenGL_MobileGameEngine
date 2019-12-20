//
//  FAchievementGroup.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 12/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FAchievementGroup.hpp"
#include "FAchievement.hpp"

FAchievementGroup::FAchievementGroup() {
    
}

FAchievementGroup::~FAchievementGroup() {
    
}

void FAchievementGroup::Add(FAchievement *pAchievement) {
    mAchievementList.Add(pAchievement);
}

