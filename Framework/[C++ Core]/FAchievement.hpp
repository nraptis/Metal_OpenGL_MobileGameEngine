//
//  FAchievement.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 12/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FAchievement_hpp
#define FAchievement_hpp

#include "FJSON.hpp"
#include "FList.hpp"

class FAchievement {
public:
    FAchievement();
    ~FAchievement();
    
    FString                                 mIdentifier; // Unique identifier for the achievement (should not be displayed to customer).
    FString                                 mTitle; // The name of the achievement.
    FString                                 mDescription; // A description of how to earn the achievement.
    int                                     mPoints; // For example, an achievement might be worth 5 points, 10 points, 25 points, 50 points, or 100 points.
    
    void                                    Load(FJSONNode *pLoadNode);
    FJSONNode                               *Save();
    
    void                                    Reset();
    bool                                    AddProgress(int pProgress = 1);
    
    void                                    Print();
    
    //Once mProgress = mProgressMax, we are complete. Great for stuff like "do 5,000 of X."
    int                                     mProgress;
    int                                     mProgressMax;
    
    bool                                    mComplete;
    
    //Is it posted to Game Center / OpenFeint yet?
    bool                                    mSynchronized;
    
};


#endif

