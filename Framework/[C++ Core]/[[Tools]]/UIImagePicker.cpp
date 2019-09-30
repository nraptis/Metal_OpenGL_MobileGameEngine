//
//  UIImagePicker.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UIImagePicker.hpp"
#include "UIImagePickerCell.hpp"
#include "core_includes.h"


UIImagePicker::UIImagePicker() {
    float aX = gDeviceWidth2 / 3.0f;
    float aY = gDeviceHeight2 / 3.0f;
    float aWidth = gDeviceWidth2 + gDeviceWidth2 / 2.0f;
    float aHeight = gDeviceHeight2 + gDeviceHeight2 / 2.0f;
    if (aWidth > 768.0f) {
        aWidth = 768.0f;
    }
    if (aHeight > 640.0f) {
        aHeight = 640.0f;
    }

    SetFrame(aX, aY, aWidth, aHeight);

    mSelectedSprite = 0;
    mSelectedSpriteSequence = 0;

    SetTitle("Image Picker");
    SetScrollMode(false);

    mManualSectionLayout = true;
    mResizeDragAllowedV = false;

    mSection = new ToolMenuSection();
    AddSection(mSection);
    mName = "Image Picker";
    mDidSetUp = false;
    mScrollContent = new UIImagePickerScrollContent();
    mSection->AddChild(mScrollContent);
}

UIImagePicker::~UIImagePicker()
{

}

void UIImagePicker::Update() {
    if (mDidSetUp == false) {
        if (mScrollContent) {
            mScrollContent->SetUp();
            mDidSetUp = true;
        }
    }
}

void UIImagePicker::Draw() {
    ToolMenu::Draw();
}

void UIImagePicker::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "pick_image_sequence") {
        UIImagePickerCellSequence *aCell = (UIImagePickerCellSequence *)pSender;
        mSelectedSpriteSequence = aCell->mSequence;
        gNotify.Post(this, "pick_image");
    }
    if (FString(pNotification) == "pick_image") {
        UIImagePickerCell *aCell = (UIImagePickerCell *)pSender;
        mSelectedSprite = aCell->mSprite;
        gNotify.Post(this, "pick_image");
    }
}

void UIImagePicker::AddSprite(const char *pSpritePath) {
    FSprite *aSprite = new FSprite();
    aSprite->Load(pSpritePath);
    UIImagePickerCell *aCell = new UIImagePickerCell(aSprite, true);
    aCell->SetUp(0.0f, 0.0f, mScrollContent->mCellWidth, mScrollContent->mCellHeight);
    mScrollContent->AddCell(aCell);
    FrameDidUpdate();
}

void UIImagePicker::AddSprite(FSprite *pSprite) {
    if (pSprite) {
        FString aPath = pSprite->mFileName.c();
        EnumList(FString, aString, mBlockedSprites) {
            if (*aString == aPath) {
                return;
            }
        }
        UIImagePickerCell *aCell = new UIImagePickerCell(pSprite, false);
        aCell->SetUp(0.0f, 0.0f, mScrollContent->mCellWidth, mScrollContent->mCellHeight);
        mScrollContent->AddCell(aCell);
        FrameDidUpdate();
    }
}

void UIImagePicker::AddSpriteSequence(FSpriteSequence *pSpriteSequence) {
    if (pSpriteSequence) {
        FString aPath = pSpriteSequence->mFilePrefix.c();
        EnumList(FString, aString, mBlockedSprites) {
            if (*aString == aPath) {
                return;
            }
        }
        UIImagePickerCellSequence *aCell = new UIImagePickerCellSequence(pSpriteSequence, false);
        aCell->SetUp(0.0f, 0.0f, mScrollContent->mCellWidth, mScrollContent->mCellHeight);
        mScrollContent->AddCell(aCell);
        FrameDidUpdate();
    }
}

void UIImagePicker::Layout() {
    ToolMenu::Layout();
    mSection->SetSize(mContent.GetWidth(), mContent.GetHeight());
}

void UIImagePicker::FillWithAny() {
    EnumList(FSprite, aSprite, gSpriteList) {
        AddSprite(aSprite);
    }
    EnumList(FSpriteSequence, aSequence, gSpriteSequenceList) {
        AddSpriteSequence(aSequence);
    }
}

void UIImagePicker::FillWithImages() {
    EnumList(FSprite, aSprite, gSpriteList) {
        AddSprite(aSprite);
    }
}

void UIImagePicker::FillWithImageSequences() {
    EnumList(FSpriteSequence, aSequence, gSpriteSequenceList) {
        AddSpriteSequence(aSequence);
    }
}


UIImagePickerScrollContent::UIImagePickerScrollContent() {
    mClipEnabled = true;
    mName = "Image Picker Scroller";
    mMaxRows = 5;
    mCellGrid = 0;
    mScrollSpeedX = 0.0f;
    mScrollSpeedY = 0.0f;
    mScrollOffsetX = 0.0f;
    mScrollOffsetY = 0.0f;
    mStartOffsetX = 0.0f;
    mStartOffsetY = 0.0f;
    mGridOffsetX = 0;
    mGridOffsetY = 0;
    mCellSpacingH = 2.0f;
    mCellSpacingV = 2.0f;
    mCellWidth = 60.0f;
    mCellHeight = 60.0f;
    mCellHeight = 100.0f;
    mCellWidth = (mCellHeight * 1.4f);
    mColCount = 0;
    mRowCount = 0;
    float aWidth = gAppWidth;
    float aProbeX = mCellSpacingH;
    int aScreenColCount = 0;
    while (aProbeX < aWidth) {
        aScreenColCount++;
        aProbeX += (mCellWidth + mCellSpacingH);
    }
    mScreenGridWidth = (aScreenColCount);// + 2);
    mCellGrid = 0;
    mColCount = 0;
    mRowCount = 1;
}

UIImagePickerScrollContent::~UIImagePickerScrollContent() {
    for (int aCol=0;aCol<mColCount;aCol++) {
        delete [] mCellGrid[aCol];
    }
    delete [] mCellGrid;
    mCellGrid = 0;
    mColCount = 0;
    mRowCount = 0;
}

void UIImagePickerScrollContent::Layout() {
    if (!mParent) return;
    SetFrame(2.0f, 2.0f, mParent->mWidth - 4.0f, mParent->mHeight - 4.0f);
}

void UIImagePickerScrollContent::SetUp() {
    float aIdealCellHeight = 88.0f;
    if (mWidth < 200 || mHeight < 200) {
        mMaxRows = 5;
        mCellSpacingH = 2.0f;
        mCellSpacingV = 2.0f;
        mCellWidth = 60.0f;
        mCellHeight = 60.0f;
        mCellHeight = 100.0f;
        mCellWidth = (mCellHeight * 1.4f);
        mColCount = 0;
        mRowCount = 0;
    } else {
        mCellSpacingH = 2.0f;
        mCellSpacingV = 2.0f;
        mMaxRows = (int)(mHeight / aIdealCellHeight);
        if (mMaxRows < 3) { mMaxRows = 3; }
        if (mMaxRows > 8) { mMaxRows = 8; }
        float aMaxRows = (float)mMaxRows;
        mCellHeight = mHeight - mCellSpacingV * (aMaxRows + 1.0f);
        mCellHeight /= aMaxRows;
        mCellWidth = mCellHeight * 1.46f;
    }
    int aCount = mCellList.mCount;
    for (int aCol=0;aCol<mColCount;aCol++) {
        delete [] mCellGrid[aCol];
    }
    if(mScreenGridWidth < 2) { mScreenGridWidth = 2; }
    mCellGrid = 0;
    mColCount = 0;
    mRowCount = 1;
    if (aCount > 0) {
        if (aCount <= mScreenGridWidth) {
            mColCount = aCount;
        } else {
            int aScan = aCount;
            while (aScan > mScreenGridWidth) {
                aScan -= mScreenGridWidth;
                mRowCount++;
            }
            if (mRowCount > mMaxRows) {
                mRowCount = mMaxRows;
                mColCount = (aCount / mRowCount);
                if((aCount % mRowCount) != 0) { mColCount++; }
            } else {
                mColCount = mScreenGridWidth;
            }
        }

        mCellGrid = new UIImagePickerCell**[mColCount];
        for (int aCol=0;aCol<mColCount;aCol++) {
            mCellGrid[aCol] = new UIImagePickerCell*[mRowCount];
            for (int aRow=0;aRow<mRowCount;aRow++) {
                mCellGrid[aCol][aRow] = 0;
            }
        }

        int aIndex = 0;
        float aProbeX = mCellSpacingH;
        float aProbeY = mCellSpacingV;
        for (int aRow=0;aRow<mRowCount;aRow++) {
            aProbeX = mCellSpacingH;
            for (int aCol=0;aCol<mColCount;aCol++) {
                UIImagePickerCell *aCell = ((UIImagePickerCell *)(mCellList.Fetch(aIndex)));
                if (aCell) {
                    mCellGrid[aCol][aRow] = aCell;
                    aCell->SetUp(aProbeX, aProbeY, mCellWidth, mCellHeight);
                }
                aProbeX += (mCellWidth + mCellSpacingH);
                aIndex++;
            }
            aProbeY += (mCellHeight + mCellSpacingV);
        }
    }
}

void UIImagePickerScrollContent::Update() {
    if (mScrollFlingSpeed > 0) {
        mScrollFlingSpeed *= 0.940f;
        mScrollFlingSpeed -= 0.1f;
        if (mScrollFlingSpeed <= 0) {
            mScrollFlingSpeed = 0;
        }
        mScrollOffsetX += mScrollFlingSpeed * mScrollSpeedX;
    }

    float aCellWidth = (mCellWidth + mCellSpacingH);

    UIImagePickerCell *aHold = 0;
    if (mCellGrid != 0) {
        while (mScrollOffsetX >= aCellWidth) {
            mGridOffsetX++;
            if(mGridOffsetX >= mColCount) { mGridOffsetX -= mColCount; }
            mScrollOffsetX -= aCellWidth;
            mStartOffsetX -= aCellWidth;

            for (int n = 0; n < mRowCount; n++) {
                aHold = mCellGrid[mColCount - 1][n];
                for (int i = (mColCount - 2); i >= 0; i--) {
                    mCellGrid[i + 1][n] = mCellGrid[i][n];
                }
                mCellGrid[0][n] = aHold;
            }
        }
        while (mScrollOffsetX <= 0.0f) {
            mGridOffsetX--;
            if (mGridOffsetX < 0) { mGridOffsetX += mColCount; }
            mScrollOffsetX += aCellWidth;
            mStartOffsetX += aCellWidth;
            for (int n = 0; n < mRowCount; n++) {
                aHold = mCellGrid[0][n];
                for (int i = 1; i < mColCount; i++) {
                    mCellGrid[i - 1][n] = mCellGrid[i][n];
                }
                mCellGrid[mColCount - 1][n] = aHold;
            }
        }

        int aIndex = 0;
        float aProbeX = mCellSpacingH;
        float aProbeY = mCellSpacingV;
        for (int aRow = 0; aRow < mRowCount; aRow++) {
            aProbeX = (mCellSpacingH - aCellWidth);

            for (int aCol = 0; aCol < mColCount; aCol++) {
                UIImagePickerCell *aCell = mCellGrid[aCol][aRow];

                if (aCell) {
                    aCell->SetFrame(aProbeX + mScrollOffsetX, aProbeY, mCellWidth, mCellHeight);

                    if ((aCell->mX >= (-mCellWidth)) && (aCell->mX < (mWidth))) {
                        aCell->mHidden = false;
                        aCell->mEnabled = true;
                    } else {
                        aCell->mHidden = true;
                        aCell->mEnabled = false;
                    }
                }
                aProbeX += (mCellWidth + mCellSpacingH);
                aIndex++;
            }
            aProbeY += (mCellHeight + mCellSpacingV);
        }
    }
}

void UIImagePickerScrollContent::Draw() {

}

void UIImagePickerScrollContent::AddCell(UIImagePickerCell *pCell) {
    if (pCell) {
        float aPlaceX = ((float)(mCellList.mCount)) * mCellWidth;
        pCell->SetFrame(aPlaceX, 0.0f, mCellWidth, mCellHeight);
        mCellList += pCell;
        AddChild(pCell);
        pCell->mConsumesTouches = false;
    }
}

void UIImagePickerScrollContent::TouchDown(float pX, float pY, void *pData)
{
    mScrollFlingSpeed = 0.0f;

    mScrollSpeedX = 0.0f;
    mScrollSpeedY = 0.0f;
}

void UIImagePickerScrollContent::PanBegin(float pX, float pY) {
    mStartOffsetX = mScrollOffsetX;
    mStartOffsetY = mScrollOffsetY;
}

void UIImagePickerScrollContent::Pan(float pX, float pY) {
    mScrollOffsetX = mStartOffsetX + mGesturePanDistX;
    mScrollOffsetY = mStartOffsetY + mGesturePanDistY;
    EnumList(UIImagePickerCell, aCell, mCellList) {
        aCell->mTouchCanceled = true;
    }
}

void UIImagePickerScrollContent::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY) {
    float aSpeed = pSpeedX * pSpeedX + pSpeedY * pSpeedY;
    if (aSpeed > 0.1f) {
        aSpeed = sqrtf(aSpeed);
        pSpeedX /= aSpeed;
        pSpeedY /= aSpeed;
    }
    
    mScrollSpeedX = (pSpeedX);
    mScrollSpeedY = (pSpeedY);

    mScrollFlingSpeed = aSpeed;

    if(mScrollFlingSpeed > 50.0f)mScrollFlingSpeed = 50.0f;


    EnumList(UIImagePickerCell, aCell, mCellList)
    {
        aCell->mTouchCanceled = false;
    }

}





