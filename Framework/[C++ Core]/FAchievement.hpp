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
    
    FString                                 mName;
    
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

