//
//  FScrollCanvas.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 11/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FScrollCanvas_hpp
#define FScrollCanvas_hpp

#include "FScrollCanvasGeneric.hpp"

//

class FScrollCanvas : public FScrollCanvasGeneric {
public:
    FScrollCanvas();
    virtual ~FScrollCanvas();
    
    virtual void                                    BaseUpdate();
    
    virtual void                                    PanBegin(float pX, float pY);
    virtual void                                    PanMove(float pX, float pY);
    virtual void                                    PanRelease(float pX, float pY, float pSpeedX, float pSpeedY);
    
    
    float                                           mRubberBandReflectFactor;
    float                                           mRubberBandReflectCutoff;
    
    float                                           mRubberBandTimeFactor;
    int                                             mRubberBandTimeBase;
    int                                             mRubberBandTimeMax;
    
    
    bool                                            mEnabledX;
    bool                                            mEnabledY;
    
    
};

#endif /* FScrollCanvas_hpp */
