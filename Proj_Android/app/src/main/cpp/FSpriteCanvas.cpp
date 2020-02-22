//
//  FSpriteCanvas.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 11/10/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "FSpriteCanvas.hpp"

FSpriteCanvas::FSpriteCanvas() {
    mSprite = NULL;
    mConsumesTouches = false;
}

FSpriteCanvas::~FSpriteCanvas() {
    
}

void FSpriteCanvas::Layout() {
    
    if (mSprite != NULL) {
        if ((mWidth <= SQRT_EPSILON) || (mHeight <= SQRT_EPSILON)) {
            SetSize(mSprite->mWidth, mSprite->mHeight);
        }
    }
    
}

void FSpriteCanvas::LayoutTransform() {
    
}

void FSpriteCanvas::Draw() {
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor(0.75f);
    
    if (mSprite != NULL) {
        mSprite->DrawQuad(0.0f, 0.0f, mWidth, mHeight);
    }
    
    
}
