#ifndef AssetWadGameInterface_hpp
#define AssetWadGameInterface_hpp

#include "FAssetWad.hpp"

class AssetWadGameInterface : public FAssetWad {
public:
    AssetWadGameInterface();
    ~AssetWadGameInterface();
    
    virtual void                                    Load();
    virtual void                                    Unload();
    
    FSprite                                         mProgressBarEmpty;
    FSprite                                         mProgressBarFull;
    FSprite                                         mProgressBarShine;
    FSprite                                         mProgressBarStroke;
    
    FSprite                                         mProgressLoopBubbles;
    FSprite                                         mProgressLoopStripes;
};


#endif
