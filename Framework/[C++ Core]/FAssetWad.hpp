//
//  FAssetWad.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FFAssetWad_hpp
#define FFAssetWad_hpp

#include "os_core_includes.h" //We need access to globals on loading assets.
#include "core_app_shell.hpp"
#include "FFont.hpp"
#include "FSprite.hpp"
#include "FSpriteSequence.h"
#include "FModelDataPacked.hpp"
#include "FModelDataPackedSequence.hpp"

//This represents a "clump" of assets which are multi-resolution that can be loaded and unloaded...

class FAssetWad {
public:
    FAssetWad();
    virtual ~FAssetWad();
    
    virtual void                                    Load();
    virtual void                                    Unload();
};

#endif
