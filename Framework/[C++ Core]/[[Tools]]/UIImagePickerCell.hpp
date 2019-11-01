//
//  UIImagePickerCell.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UIImagePickerCell_hpp
#define UIImagePickerCell_hpp

#include "FCanvas.hpp"
#include "FSprite.hpp"
#include "FSpriteSequence.h"
#include "FDrawQuad.hpp"

class UIImagePickerCell : public FCanvas {
public:
    UIImagePickerCell();
    UIImagePickerCell(FSprite *pSprite, bool pDestroy);
    UIImagePickerCell(const char *pPath);
    virtual ~UIImagePickerCell();

    virtual void                                Update();
    virtual void                                Draw();

    void                                        SetUp(float pWidth, float pHeight);
    void                                        SetUp(float pX, float pY, float pWidth, float pHeight);

    virtual void                                TouchUp(float pX, float pY, void *pData);

    FSprite                                     *mSprite;
    bool                                        mDestroySprite;
    bool                                        mTouchCanceled;

    FDrawQuad                                   mSpriteQuad;
};

class UIImagePickerCellSequence : public UIImagePickerCell {
public:
    UIImagePickerCellSequence();
    UIImagePickerCellSequence(FSpriteSequence *pSequence, bool pDestroy);

    virtual ~UIImagePickerCellSequence();

    virtual void                                SetUp(float pWidth, float pHeight);
    virtual void                                SetUp(float pX, float pY, float pWidth, float pHeight);

    virtual void                                Update();
    virtual void                                Draw();

    virtual void                                TouchUp(float pX, float pY, void *pData);

    FSpriteSequence                             *mSequence;

    float                                       mFrame;
    float                                       mFrameMax;


};

#endif
