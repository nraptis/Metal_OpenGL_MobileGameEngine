
//New Idea:

//As the touches come in, just enqueue them all - and on the next update, consolidate the batch of touches that came in...

#ifndef F_TOUCH_MANAGER_H
#define F_TOUCH_MANAGER_H

#define TOUCH_HISTORY_STATES 128

#define MOUSE_BUTTON_LEFT 0
#define MOUSE_BUTTON_MIDDLE 1
#define MOUSE_BUTTON_RIGHT 2

#define MOUSE_MOVE 0
#define MOUSE_DOWN 1
#define MOUSE_UP 2
#define MOUSE_WHEEL_SCROLL 3

#define TOUCH_STATE_INACTIVE 0
#define TOUCH_STATE_DOWN 1
#define TOUCH_STATE_MOVING 2
#define TOUCH_STATE_RELEASED 3
#define TOUCH_STATE_CANCELED 4

#define TOUCH_FAKE_POINTER_COUNT 8

#define TOUCH_MANAGER_MAX_TOUCHES 32
#define TOUCH_MANAGER_MAX_QUEUE_TOUCHES 64

#include "FList.hpp"

class FMouseAction {
public:
    FMouseAction();
    ~FMouseAction();
    float                                   mX;
    float                                   mY;
    int                                     mType;
    int                                     mDirection;
    int                                     mButton;
};

class FTouchAction {
public:
    FTouchAction();
    ~FTouchAction();
    float                                   mX;
    float                                   mY;
    int                                     mTouchState;
    void                                    *mData;
};

class FTouch {
public:
    FTouch();
    ~FTouch();
    void                                    Reset(float pX, float pY, void *pData);
    void                                    Reset(float pX, float pY);
    void                                    Move(float pX, float pY);
    void                                    Up(float pX, float pY);
    float                                   mHistoryX[TOUCH_HISTORY_STATES];
    float                                   mHistoryY[TOUCH_HISTORY_STATES];
    int                                     mHistoryTime[TOUCH_HISTORY_STATES];
    int                                     mHistoryCount;
    float                                   mX;
    float                                   mY;
    int                                     mTimer;
    int                                     mLastActionTime;
    int                                     mState;
    int                                     mRenderIndex;
    bool                                    mChanged;
    void                                    *mData;
};

class FTouchManager {
public:
    FTouchManager();
    ~FTouchManager();

    void                                    Update();
    void                                    Draw();
    
    void                                    Reset();
    
    void                                    Active();
    void                                    Inactive();
    
    FTouch                                  *DequeueTouch(void *pData);
    FTouch                                  *GetTouch(void *pData);

    void                                    FinishedTouch(FTouch *pTouch);
    void                                    EnqueueTouchAction(float pX, float pY, int pTouchState, void *pData);
    void                                    EnqueueTouchActionDroid(float pX, float pY, int pTouchState, int pIndex);
    void                                    EnqueueMouseAction(float pX, float pY, int pType, int pButton, int pDirection);

	void                                    EnqueueKeyDown(int pKey);
	void                                    EnqueueKeyUp(int pKey);

	int										mKeyQueue[256];
	int										mKeyActionType[256];
	int										mKeyQueueLength;
    
    FList                                   mTouchActionQueue;
    FList                                   mTouchActionRecycle;

    FList                                   mMouseActionQueue;
    FList                                   mMouseActionRecycle;
    
    void                                    BaseTouchDownDroid(float pX, float pY, int pIndex, int pCount);
    void                                    BaseTouchMoveDroid(float pX, float pY, int pIndex, int pCount);
    void                                    BaseTouchUpDroid(float pX, float pY, int pIndex, int pCount);
    void                                    BaseTouchCanceledDroid(float pX, float pY, int pIndex, int pCount);
    
    void                                    BaseTouchDown(float pX, float pY, void *pData);
    void                                    BaseTouchMove(float pX, float pY, void *pData);
	void                                    BaseTouchUp(float pX, float pY, void *pData);
    void                                    BaseTouchCanceled(float pX, float pY, void *pData);
    
    void                                    BaseMouseDown(float pX, float pY, int pButton);
    void                                    BaseMouseMove(float pX, float pY);
    void                                    BaseMouseUp(float pX, float pY, int pButton);
    void                                    BaseMouseWheel(int pDir);

    void                                    FlushTouches();

    FTouch                                  *mTouch[TOUCH_MANAGER_MAX_TOUCHES + 1];
    FTouch                                  *mTouchQueue[TOUCH_MANAGER_MAX_QUEUE_TOUCHES + 1];

    bool                                    mIsUpdating;
    
    int                                     mRenderIndex;
    
    int                                     mTouchCount;
    int                                     mTouchQueueCount;

    float                                   mCenterX;
    float                                   mCenterY;

    void                                    *mAndroidFakePointer[TOUCH_FAKE_POINTER_COUNT];
    void                                    *mMouseFakePointer[3];

	bool									mMouseLeftDown;
	bool									mMouseRightDown;
	bool									mMouseMiddleDown;
};

#endif
