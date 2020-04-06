//
//  FTouchManager.cpp
//  Graveyard
//
//  Created by Nick Raptis on 2/15/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FTouchManager.hpp"
#include "FApp.hpp"
#include "core_includes.h"


FMouseAction::FMouseAction() {
    mX = 0.0f;
    mY = 0.0f;
    mType = MOUSE_MOVE;
    mDirection = 1;
    mButton = -1;
}

FMouseAction::~FMouseAction() { }

FTouchAction::FTouchAction() {
    mX = 0.0f;
    mY = 0.0f;
    mTouchState = TOUCH_STATE_INACTIVE;
    mData = 0;
}

FTouchAction::~FTouchAction() { }

FTouch::FTouch() {
    mRenderIndex = 0;
    for (int i=0;i<TOUCH_HISTORY_STATES;i++) {
        mHistoryX[i] = 0.0f;
        mHistoryY[i] = 0.0f;
        mHistoryTime[i] = 0;
    }
    
    Reset(0.0f, 0.0f, 0);
}

FTouch::~FTouch() {
    
}

void FTouch::Reset(float pX, float pY, void *pData) {
    Reset(pX, pY);
    mData = pData;
    mHistoryX[0] = pX;
    mHistoryY[0] = pY;
    mHistoryTime[0] = mTimer;
    mHistoryCount = 1;
}

void FTouch::Reset(float pX, float pY) {
    mHistoryCount = 0;
    
    mX = pX;
    mY = pY;
    
    mTimer = 0;
    mLastActionTime = 0;
    
    mState = TOUCH_STATE_DOWN;
    
    mChanged = true;
    
    mData = 0;
}

void FTouch::Move(float pX, float pY) {
    mX = pX;
    mY = pY;
    
    mChanged = true;
    
    if (mState == TOUCH_STATE_DOWN || mState == TOUCH_STATE_INACTIVE) {
        mState = TOUCH_STATE_MOVING;
    }
    
    mX = pX;
    mY = pY;
    
    mLastActionTime = mTimer;
    
    if (mHistoryCount == TOUCH_HISTORY_STATES) {
        for(int i=1;i<TOUCH_HISTORY_STATES;i++)mHistoryX[i - 1] = mHistoryX[i];
        for(int i=1;i<TOUCH_HISTORY_STATES;i++)mHistoryY[i - 1] = mHistoryY[i];
        for(int i=1;i<TOUCH_HISTORY_STATES;i++)mHistoryTime[i - 1] = mHistoryTime[i];
        
        mHistoryX[TOUCH_HISTORY_STATES - 1] = pX;
        mHistoryY[TOUCH_HISTORY_STATES - 1] = pY;
        mHistoryTime[TOUCH_HISTORY_STATES - 1] = mTimer;
    } else {
        mHistoryX[mHistoryCount] = pX;
        mHistoryY[mHistoryCount] = pY;
        mHistoryTime[mHistoryCount] = mTimer;
        mHistoryCount++;
    }
}

void FTouch::Up(float pX, float pY) {
    mX = pX;
    mY = pY;
    mChanged = true;
    mState = TOUCH_STATE_MOVING;
}

FTouchManager::FTouchManager() {
	mKeyQueueLength = 0;
    for (int i=0;i<TOUCH_MANAGER_MAX_QUEUE_TOUCHES;i++) {
        FTouch *aTouch = new FTouch();
        aTouch->Reset(0.0f, 0.0f);
        mTouchQueue[i] = aTouch;
    }
    mTouchQueue[TOUCH_MANAGER_MAX_QUEUE_TOUCHES] = 0;
    
    for (int i=0;i<TOUCH_MANAGER_MAX_TOUCHES;i++) {
        mTouch[i] = 0;
    }
    mTouch[TOUCH_MANAGER_MAX_TOUCHES] = 0;
    
    mTouchCount = 0;
    mTouchQueueCount = TOUCH_MANAGER_MAX_QUEUE_TOUCHES;
    
    mRenderIndex = 0;
    
    mIsUpdating = false;
    
    mAndroidFakePointer[0] = (void *)(0xDEADBEE5);
    mAndroidFakePointer[1] = (void *)(0xCABCABCA);
    mAndroidFakePointer[2] = (void *)(0xAABBCCDD);
    mAndroidFakePointer[3] = (void *)(0xBADBADBA);
    mAndroidFakePointer[4] = (void *)(0xE5CA1ADE);
    mAndroidFakePointer[5] = (void *)(0xF00DFACE);
    mAndroidFakePointer[6] = (void *)(0xFEEDF00D);
    mAndroidFakePointer[7] = (void *)(0x00DDBA11);

    mMouseFakePointer[0] = (void *)(0xDEADBEE4);
    mMouseFakePointer[1] = (void *)(0xBEEBDAAD);
    mMouseFakePointer[2] = (void *)(0xFADE1333);
    
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    
	mMouseLeftDown = false;
	mMouseRightDown = false;
	mMouseMiddleDown = false;
}

FTouchManager::~FTouchManager() {
    
}

void FTouchManager::Update() {
    
	if (gAppBase == 0) {
        Reset();
        return;
    }

    for (int i = 0; i < mKeyQueueLength; i++) {
        if (mKeyActionType[i] == 1) { gAppBase->ProcessKeyDown(mKeyQueue[i]); }
        if (mKeyActionType[i] == -1) { gAppBase->ProcessKeyUp(mKeyQueue[i]); }
    }
    mKeyQueueLength = 0;

    EnumList(FTouchAction, aAction, mTouchActionQueue) {
        if(aAction->mTouchState == TOUCH_STATE_MOVING) {
            gAppBase->ProcessTouchMove(aAction->mX, aAction->mY, aAction->mData);
            FTouch *aTouch = GetTouch(aAction->mData);
            if(aTouch) {
                aTouch->Move(aAction->mX, aAction->mY);
            }
        } else if(aAction->mTouchState == TOUCH_STATE_DOWN) {
            FTouch *aTouch = DequeueTouch(aAction->mData);
            if(aTouch) {
                aTouch->mRenderIndex = mRenderIndex;
                aTouch->Reset(aAction->mX, aAction->mY, aAction->mData);
                mRenderIndex++;
                if(mRenderIndex > 5)mRenderIndex = 0;
            }
            
            gAppBase->ProcessTouchDown(aAction->mX, aAction->mY, aAction->mData);
            
        } else { //if((aAction->mTouchState == TOUCH_STATE_RELEASED) || (aAction->mTouchState == TOUCH_STATE_CANCELED))
            gAppBase->ProcessTouchUp(aAction->mX, aAction->mY, aAction->mData);
            FinishedTouch(GetTouch(aAction->mData));
        }
    }
    
    
    FTouch *aAutoDequeue = 0;
    for (int i=0;i<mTouchCount;i++) {
        mTouch[i]->mTimer++;
        if ((mTouch[i]->mTimer - mTouch[i]->mLastActionTime) > 1000) {
            aAutoDequeue = mTouch[i];
        }
    }
    
    if (aAutoDequeue) {
        Log("Touch Expired.. [%x]\n", (unsigned int)((unsigned long)(aAutoDequeue->mData)));
        FinishedTouch(aAutoDequeue);
    }
    
    EnumList (FTouchAction, aAction, mTouchActionQueue) {
        mTouchActionRecycle.Add(aAction);
    }
    mTouchActionQueue.RemoveAll();
    
    
    EnumList(FMouseAction, aAction, mMouseActionQueue) {
        if(aAction->mType == MOUSE_MOVE) {
            gAppBase->ProcessMouseMove(aAction->mX, aAction->mY);
        } else if(aAction->mType == MOUSE_DOWN) {
            gAppBase->ProcessMouseDown(aAction->mX, aAction->mY, aAction->mButton);
        } else if(aAction->mType == MOUSE_UP) {
            gAppBase->ProcessMouseUp(aAction->mX, aAction->mY, aAction->mButton);
        } else {
            gAppBase->ProcessMouseWheel(aAction->mDirection);
        }
    }
    EnumList (FMouseAction, aAction, mMouseActionQueue) {
        mMouseActionRecycle.Add(aAction);
    }
    mMouseActionQueue.RemoveAll();
    
    
}

void FTouchManager::Draw() {
    Graphics::SetColor(1.0f, 0.0f, 1.0f);
    for (int i=0;i<mTouchCount;i++) {
        Graphics::DrawPoint(mTouch[i]->mX, mTouch[i]->mY, 16.0f);
    }
}

void FTouchManager::Reset() {
    
}

void FTouchManager::EnqueueTouchActionDroid(float pX, float pY, int pTouchState, int pIndex) {
    if ((pIndex >= 0) && (pIndex < TOUCH_FAKE_POINTER_COUNT)) {
        void *aData = mAndroidFakePointer[pIndex];
        if (pTouchState == TOUCH_STATE_MOVING) {
            
        } else if ((pTouchState == TOUCH_STATE_RELEASED) || (pTouchState == TOUCH_STATE_CANCELED)) {
            void *aHold = mAndroidFakePointer[pIndex];
            for(int i=pIndex;i<(TOUCH_FAKE_POINTER_COUNT - 1);i++)
            {
                mAndroidFakePointer[i] = mAndroidFakePointer[i + 1];
            }
            mAndroidFakePointer[TOUCH_FAKE_POINTER_COUNT - 1] = aHold;
        } else if (pTouchState == TOUCH_STATE_DOWN) {
            void *aHold = mAndroidFakePointer[TOUCH_FAKE_POINTER_COUNT - 1];
            for (int i=(TOUCH_FAKE_POINTER_COUNT - 2);i>=pIndex;i--) {
                mAndroidFakePointer[i + 1] = mAndroidFakePointer[i];
            }
            mAndroidFakePointer[pIndex] = aHold;
            aData = aHold;
        }
        EnqueueTouchAction(pX, pY, pTouchState, aData);
    }
}

void FTouchManager::EnqueueTouchAction(float pX, float pY, int pTouchState, void *pData) {
    FTouchAction *aAction = 0;
    if(pTouchState == TOUCH_STATE_MOVING) {
        for(int i=mTouchActionQueue.mCount - 1;i>=0;i--) {
            aAction = (FTouchAction *)mTouchActionQueue.mData[i];
            if(aAction->mTouchState == TOUCH_STATE_MOVING) {
                if(aAction->mData == pData) {
                    aAction->mX = pX;
                    aAction->mY = pY;
                    return;
                }
            }
        }
    }
    
    aAction = 0;

    if (mTouchActionRecycle.mCount > 0) {
        aAction = (FTouchAction *)(mTouchActionRecycle.mData[mTouchActionRecycle.mCount - 1]);
        mTouchActionRecycle.mCount --;
    }
    
    if(aAction == 0) {
        aAction = new FTouchAction();
    }

    aAction->mX = pX;
    aAction->mY = pY;
    aAction->mData = pData;
    aAction->mTouchState = pTouchState;
    mTouchActionQueue.Add(aAction);
}

void FTouchManager::EnqueueMouseAction(float pX, float pY, int pType, int pButton, int pDirection) {
    FMouseAction *aAction = 0;
    if (pType == MOUSE_MOVE) {
        for(int i=mTouchActionQueue.mCount - 1;i>=0;i--) {
            aAction = (FMouseAction *)mTouchActionQueue.mData[i];
            if(aAction->mType == MOUSE_MOVE) {
                aAction->mX = pX;
                aAction->mY = pY;
                return;
            }
        }
    }
    
    aAction = 0;

    if (mMouseActionRecycle.mCount > 0) {
        aAction = (FMouseAction *)(mMouseActionRecycle.mData[mMouseActionRecycle.mCount - 1]);
        mMouseActionRecycle.mCount --;
    }

    if(aAction == 0) {
        aAction = new FMouseAction();
    }

    aAction->mX = pX;
    aAction->mY = pY;
    aAction->mButton = pButton;
    aAction->mType = pType;
    aAction->mDirection = pDirection;
    mMouseActionQueue.Add(aAction);
}

void FTouchManager::Active() {
    FlushTouches();
}

void FTouchManager::Inactive() {
    FlushTouches();
}

void FTouchManager::FinishedTouch(FTouch *pTouch) {
    if (pTouch) {
        int aSlot = -1;
        for (int i=0;i<mTouchCount;i++) {
            if (mTouch[i] == pTouch) {
                aSlot = i;
            }
        }
        if (aSlot >= 0) {
            FTouch *aTouch = 0;
            for(int i=aSlot+1;i<mTouchCount;i++) {
                aTouch = mTouch[i];
                mTouch[i - 1] = aTouch;
            }
            mTouchCount--;
        }
        if (mTouchQueueCount < TOUCH_MANAGER_MAX_QUEUE_TOUCHES) {
            mTouchQueue[mTouchQueueCount] = pTouch;
            mTouchQueueCount++;
        }
    }
}

FTouch *FTouchManager::DequeueTouch(void *pData) {
    FTouch *aTouch = 0;
    if(mTouchCount < (TOUCH_MANAGER_MAX_TOUCHES - 1)) {
        if(mTouchQueueCount > 0) {
            aTouch = mTouchQueue[mTouchQueueCount - 1];
            mTouchQueueCount--;
        }
        if(aTouch) {
            mTouch[mTouchCount] = aTouch;
            mTouchCount++;
        }
    }
    return aTouch;
}

FTouch *FTouchManager::GetTouch(void *pData) {
    FTouch *aTouch = 0;
    for(int i=0;i<mTouchCount;i++) {
        if(mTouch[i]->mData == pData) {
            aTouch = mTouch[i];
        }
    }
    return aTouch;
}

void FTouchManager::BaseTouchDown(float pX, float pY, void *pData) {
    EnqueueTouchAction(pX, pY, TOUCH_STATE_DOWN, pData);
    EnqueueMouseAction(pX, pY, MOUSE_DOWN, -1, 0);
}

void FTouchManager::BaseTouchMove(float pX, float pY, void *pData) {
    EnqueueTouchAction(pX, pY, TOUCH_STATE_MOVING, pData);
    EnqueueMouseAction(pX, pY, MOUSE_MOVE, 0, 0);
}

void FTouchManager::BaseTouchUp(float pX, float pY, void *pData) {
    EnqueueTouchAction(pX, pY, TOUCH_STATE_RELEASED, pData);
    EnqueueMouseAction(pX, pY, MOUSE_UP, -1, 0);
}

void FTouchManager::BaseTouchCanceled(float pX, float pY, void *pData) {
    EnqueueTouchAction(pX, pY, TOUCH_STATE_CANCELED, pData);
    EnqueueMouseAction(pX, pY, MOUSE_UP, -1, 0);
}

void FTouchManager::BaseTouchDownDroid(float pX, float pY, int pIndex, int pCount) {
    EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_DOWN, pIndex);
    EnqueueMouseAction(pX, pY, MOUSE_DOWN, -1, 0);
}

void FTouchManager::BaseTouchMoveDroid(float pX, float pY, int pIndex, int pCount) {
    EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_MOVING, pIndex);
    EnqueueMouseAction(pX, pY, MOUSE_MOVE, 0, 0);
}

void FTouchManager::BaseTouchUpDroid(float pX, float pY, int pIndex, int pCount) {
    EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_RELEASED, pIndex);
    EnqueueMouseAction(pX, pY, MOUSE_UP, -1, 0);
}

void FTouchManager::BaseTouchCanceledDroid(float pX, float pY, int pIndex, int pCount) {
    EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_CANCELED, pIndex);
    EnqueueMouseAction(pX, pY, MOUSE_UP, -1, 0);
}

void FTouchManager::BaseMouseDown(float pX, float pY, int pButton) {
	if (pButton == MOUSE_BUTTON_LEFT) {
		if(mMouseLeftDown)EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_CANCELED, 0);
		mMouseLeftDown = true;
        EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_DOWN, pButton);
	}
	if (pButton == MOUSE_BUTTON_MIDDLE) {
		mMouseMiddleDown = true;
	}
	if (pButton == MOUSE_BUTTON_RIGHT) {
		mMouseRightDown = true;
	}
    EnqueueMouseAction(pX, pY, MOUSE_DOWN, pButton, 0);
}

void FTouchManager::BaseMouseMove(float pX, float pY) {
	if (mMouseLeftDown) {
		EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_MOVING, MOUSE_BUTTON_LEFT);
    }
    EnqueueMouseAction(pX, pY, MOUSE_MOVE, 0, 0);
}

void FTouchManager::BaseMouseUp(float pX, float pY, int pButton) {
    if(pButton == MOUSE_BUTTON_LEFT) {
        mMouseLeftDown = false;
        EnqueueTouchActionDroid(pX, pY, TOUCH_STATE_RELEASED, pButton);
    }
    if (pButton == MOUSE_BUTTON_MIDDLE) { mMouseMiddleDown = false; }
    if (pButton == MOUSE_BUTTON_RIGHT) { mMouseRightDown = false; }
    EnqueueMouseAction(pX, pY, MOUSE_UP, pButton, 0);
}

void FTouchManager::BaseMouseWheel(int pDir) {
    EnqueueMouseAction(0.0f, 0.0f, MOUSE_WHEEL_SCROLL, 0, pDir);
}

void FTouchManager::FlushTouches() {
    gAppBase->ProcessTouchFlush();
    mTouchCount = 0;
}

void FTouchManager::EnqueueKeyDown(int pKey) {
	if (mKeyQueueLength < 256) {
        for (int i=0;i<mKeyQueueLength;i++) {
            if ((mKeyQueue[i]) == pKey && (mKeyActionType[i] == 1)) {
                return;
            }
        }
		mKeyQueue[mKeyQueueLength] = pKey;
		mKeyActionType[mKeyQueueLength] = 1;
		mKeyQueueLength++;
	}
}

void FTouchManager::EnqueueKeyUp(int pKey) {
	if (mKeyQueueLength < 256) {
        for (int i=0;i<mKeyQueueLength;i++) {
            if ((mKeyQueue[i]) == pKey && (mKeyActionType[i] == -1)) {
                return;
            }
        }
		mKeyQueue[mKeyQueueLength] = pKey;
		mKeyActionType[mKeyQueueLength] = -1;
		mKeyQueueLength++;
	}
}
