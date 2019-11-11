//
//  FSpriteCanvas.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 11/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FSpriteCanvas_hpp
#define FSpriteCanvas_hpp

#include "FCanvas.hpp"
#include "FSprite.hpp"

class FSpriteCanvas : public FCanvas {
public:
    FSpriteCanvas();
    virtual ~FSpriteCanvas();
    
    virtual void                                Layout() override;
    virtual void                                LayoutTransform() override;
    
    virtual void                                Draw() override;
    
    FSprite                                     *mSprite;
    
};

#endif /* FSpriteCanvas_hpp */
