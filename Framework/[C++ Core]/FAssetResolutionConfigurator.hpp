//
//  FAssetResolutionConfigurator.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FAssetResolutionConfigurator_hpp
#define FAssetResolutionConfigurator_hpp

//This is used to configure your game to fit on the many sized devices available in the market.
//There is a "sprite scale" which effects the sizes of the quads used to draw the sprites in-game. [1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0]
//There is an "asset scale" which effects the image files loaded (files should be post-fixed with "_scale_1", "_scale_2", "_scale_3", and "_scale_4")

class FAssetResolutionConfigurator {
public:
    FAssetResolutionConfigurator();
    ~FAssetResolutionConfigurator();
    
    //Ask the configuration if we should, in fact, reload...
    virtual bool                                ShouldReload();
    
    //Notify the configuration that we are, in fact, reloading...
    virtual void                                NotifyReload();
    virtual void                                Invalidate();
    
    virtual void                                NotifyScreenPropertiesChanged();
    
    void                                        SetAssetScale(int pScale);
    int                                         mAssetScale;
    int                                         mPrevAssetScale;
    
    void                                        SetSpriteScale(float pScale);
    float                                       mSpriteScale;
    float                                       mPrevSpriteScale;
    
    float                                       RoundSpriteScale(float pScale);
    
    bool                                        mAutoScale;
};

#endif /* FAssetResolutionConfigurator_hpp */
