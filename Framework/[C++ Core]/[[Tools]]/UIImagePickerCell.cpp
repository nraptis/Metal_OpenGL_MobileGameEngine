//
//  UIImagePickerCell.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UIImagePickerCell.hpp"
#include "UIImagePicker.hpp"

UIImagePickerCell::UIImagePickerCell() {
    mName = "Image Cell (Blank)";
    mDestroySprite = false;
    mSprite = 0;
    mTouchCanceled = false;
}

UIImagePickerCell::UIImagePickerCell(FSprite *pSprite, bool pDestroy) {
    mName = "Image Cell (Sprite)";
    mDestroySprite = pDestroy;
    mSprite = pSprite;
}

UIImagePickerCell::UIImagePickerCell(const char *pPath) {
    mName = "Image Cell (Sprite File)";
    mSprite = new FSprite();
    mSprite->Load(pPath);
    mDestroySprite = true;
}

UIImagePickerCell::~UIImagePickerCell() {
    if (mDestroySprite == true) {
        if (mSprite != 0) {
            delete mSprite;
            mSprite = 0;
        }
    }
}

void UIImagePickerCell::SetUp(float pWidth, float pHeight) {
    SetUp(mX, mY, mWidth, mHeight);
}

void UIImagePickerCell::SetUp(float pX, float pY, float pWidth, float pHeight) {
    SetFrame(pX, pY, pWidth, pHeight);
    mSpriteQuad.SetQuad(0.0f, 0.0f, pWidth, 0.0f, 0.0f, pHeight, pWidth, pHeight);
    if (mSprite) {
        mSpriteQuad.SetTextureAspectFit(mSprite);
    }
}

void UIImagePickerCell::Update()
{

}

void UIImagePickerCell::Draw()
{
    Graphics::SetColor();
    if (mSprite) {
        mSpriteQuad.Draw(mSprite);
    }
    if (mTouchDownInside) {
        Graphics::SetColor(1.0f, 0.15f, 0.15f, 0.75f);
    }
    else Graphics::SetColor(0.85f, 0.85f, 0.85f, 0.75f);
    Graphics::OutlineRectInside(0.0f, 0.0f, mWidth, mHeight, 2);
    Graphics::SetColor();
}

void UIImagePickerCell::TouchUp(float pX, float pY, void *pData) {
    if ((mTouchCanceled == false) && (mParent != 0)) {
        if (mParent) {
            if (mParent->mParent) {
                mParent->mParent->Notify(this, "pick_image");
            }
        }
    }
    mTouchCanceled = false;
}

UIImagePickerCellSequence::UIImagePickerCellSequence() {
    mSequence = 0;
    mFrame = 0;
    mFrameMax = 1.0f;
}

UIImagePickerCellSequence::UIImagePickerCellSequence(FSpriteSequence *pSequence, bool pDestroy) {
    mSequence = pSequence;
    if (mSequence) {
        mFrameMax = mSequence->GetMaxFrame();
        mDestroySprite = pDestroy;
    }
    mFrame = 0;
    mFrameMax = 1.0f;
}

UIImagePickerCellSequence::~UIImagePickerCellSequence() {
    if (mDestroySprite) {
        if (mSequence != 0) {
            delete mSequence;
        }
        mSequence = 0;
    }
}

void UIImagePickerCellSequence::SetUp(float pWidth, float pHeight) {
    SetUp(mX, mY, pWidth, pHeight);
}

void UIImagePickerCellSequence::SetUp(float pX, float pY, float pWidth, float pHeight) {
    if (mSequence) {
        mSprite = mSequence->Get(mFrame);
        mFrameMax = mSequence->GetMaxFrame();
    }
    UIImagePickerCell::SetUp(pX, pY, pWidth, pHeight);
    if (mSequence) {
        mSprite = 0;
    }
}

void UIImagePickerCellSequence::Update() {
    UIImagePickerCell::Update();
    if (mSequence) {
        mFrameMax = mSequence->GetMaxFrame();
        mFrame += 0.15f;
        if(mFrame >= mFrameMax)mFrame -= mFrameMax;
    }
}

void UIImagePickerCellSequence::Draw() {
    if (mSequence) {
        FSprite *aSprite = mSequence->GetSprite(mFrame);
        SetUp(mX, mY, mWidth, mHeight);
        mSprite = aSprite;
    }
    UIImagePickerCell::Draw();
    mSprite = 0;
}

void UIImagePickerCellSequence::TouchUp(float pX, float pY, void *pData) {
    if ((mTouchCanceled == false) && (mParent != 0)) {
        if (mParent) {
            if (mParent->mParent) {
                mParent->mParent->Notify(this, "pick_image_sequence");
            }
        }
    }

    mTouchCanceled = false;
}


