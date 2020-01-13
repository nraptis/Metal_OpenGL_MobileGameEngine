#include "FString.hpp"
#include "FPointList.hpp"
#include "core_includes.h"
#include "FLine.hpp"
#include "FFile.hpp"

FPointList::FPointList() {
    mCount = 0;
    mSize = 0;
    mX = NULL;
    mY = NULL;
}

FPointList::~FPointList() {
	Clear();
}

void FPointList::Clear() {
    delete [] mX;
    mCount = 0;
    mSize = 0;
    mX = NULL;
    mY = NULL;
}

void FPointList::Add(float pX, float pY)
{
    if(mCount >= mSize)
    {
        Size(mCount + (mCount / 2) + 1);
    }
    
    mX[mCount] = pX;
    mY[mCount] = pY;
    
    mCount++;
}

void FPointList::Add(FPointList *pList) {
    if (pList != NULL) {
        if ((pList->mCount + mCount) > mSize) {
            Size(pList->mCount + mCount);
        }
        for (int i=0;i<pList->mCount;i++) {
            Add(pList->mX[i], pList->mY[i]);
        }
    }
}



/*
void FPointList::AddValues(int pCount, float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pX5, float pY5, float pX6, float pY6, float pX7, float pY7, float pX8, float pY8)
{
    if(pCount >= 8)
    {
        Add(pX1, pY1);Add(pX2, pY2);Add(pX3, pY3);Add(pX4, pY4);
        Add(pX5, pY5);Add(pX6, pY6);Add(pX7, pY7);Add(pX8, pY8);
    }
    else
    {
        if(pCount > 0)Add(pX1, pY1);if(pCount > 1)Add(pX2, pY2);if(pCount > 2)Add(pX3, pY3);
        if(pCount > 3)Add(pX4, pY4);if(pCount > 4)Add(pX5, pY5);if(pCount > 5)Add(pX6, pY6);
        if(pCount > 6)Add(pX7, pY7);if(pCount > 7)Add(pX8, pY8);
    }
}

void FPointList::AddValuesReset(int pCount, float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pX5, float pY5, float pX6, float pY6, float pX7, float pY7, float pX8, float pY8)
{
    mCount = 0;
    AddValues(pCount, pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4, pX5, pY5, pX6, pY6, pX7, pY7, pX8, pY8);
}
*/

void FPointList::AddEdge(float pX1, float pY1, float pX2, float pY2) {
    if (mCount == 0) {
        Add(pX1, pY1);
        Add(pX2, pY2);
    } else {
        float aFirstX = mX[0];
        float aFirstY = mY[0];
        
        float aLastX = mX[mCount - 1];
        float aLastY = mY[mCount - 1];
        
        float aD1_1 = DistanceSquared(pX1, pY1, aLastX, aLastY);
        float aD1_2 = DistanceSquared(pX1, pY1, aFirstX, aFirstY);
        float aD2_1 = DistanceSquared(pX2, pY2, aLastX, aLastY);
        float aD2_2 = DistanceSquared(pX2, pY2, aFirstX, aFirstY);
        
        if ((aD1_1 >= 1.0f) && (aD1_2 >= 1.0f)) {
            Add(pX1, pY1);
        }
        
        if ((aD2_1 >= 1.0f) && (aD2_2 >= 1.0f)) {
            Add(pX2, pY2);
        }
    }
}

void FPointList::Set(int pIndex, float pX, float pY) {
    if (pIndex >= mSize) {
        SetSize(pIndex + 1);
    }
    
    if (pIndex >= mCount) {
        mCount = (pIndex + 1);
    }
    
    if (pIndex >= 0) {
        mX[pIndex] = pX;
        mY[pIndex] = pY;
    }
}

int FPointList::Remove(int pIndex) {
    int aResult = pIndex;
    
    if ((pIndex >= 0) && (pIndex < mCount)) {
        for (int i=(pIndex+1);i<mCount;i++) {
            mX[i - 1] = mX[i];
            mY[i - 1] = mY[i];
        }
        mCount--;
    }
    
    if (mCount > 0) {
        if(aResult < 0)aResult = (mCount - 1);
        else if(aResult >= mCount)aResult = 0;
    }
    
    return aResult;
    
    /*
     if(pIndex < 0 || pIndex >= mCount)return;
     
     for(int i=(pIndex+1);i<mCount;i++)
     {
     mX[i - 1] = mX[i];
     mY[i - 1] = mY[i];
     }
     //mX[mCount]=0.0f;
     //mY[mCount]=0.0f;
     
     mCount--;
     */
}

void FPointList::Size(int pSize) {
    if (pSize != mSize) {
        if (pSize <= 0) {
            Clear();
        } else {
            if (mCount >= pSize) {
                mCount = pSize;
            }

            float *aNewX = new float[pSize * 2 + 1];
            float *aNewY = aNewX + pSize;
            
            for (int i=0;i<mCount;i++) { aNewX[i] = mX[i]; }
            for (int i=0;i<mCount;i++) { aNewY[i] = mY[i]; }
            
            for (int i=mCount;i<pSize;i++) { aNewX[i] = 0.0f; }
            for (int i=mCount;i<pSize;i++) { aNewY[i] = 0.0f; }
            
            delete [] mX;
            
            mX = aNewX;
            mY = aNewY;
            
            mSize = pSize;
        }
    }
}

void FPointList::DrawPoints(float pSize) {
    float aX = 0.0f;
    float aY = 0.0f;
    
    float aSize2 = pSize * 0.5f;
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    for (int i=0;i<mCount;i++) {
        aX = mX[i];
        aY = mY[i];
        Graphics::DrawRect(aX - aSize2, aY - aSize2, pSize, pSize);
    }
}

void FPointList::OutlinePoints(float pSize, float pBorderWidth) {
    float aX = 0.0f;
    float aY = 0.0f;
    
    float aSize2 = pSize * 0.5f;
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    for (int i=0;i<mCount;i++) {
        aX = mX[i];
        aY = mY[i];
        Graphics::OutlineRect(aX - aSize2, aY - aSize2, pSize, pSize, pBorderWidth);
    }
}


void FPointList::DrawEdges(float pLineSize) {
    if (mCount > 0) {
        float aLastX = mX[mCount - 1];
        float aLastY = mY[mCount - 1];
        
        float aX = 0.0f;
        float aY = 0.0f;
        
        for (int i=0;i<mCount;i++) {
            aX = mX[i];aY = mY[i];
            Graphics::DrawLine(aLastX, aLastY, aX, aY, pLineSize);
            aLastX = aX;aLastY = aY;
        }
    }
}


void FPointList::DrawEdgesOpen(float pLineSize) {
    if (mCount > 0) {
        float aLastX = mX[0];
        float aLastY = mY[0];
        
        float aX = 0.0f;
        float aY = 0.0f;
        
        for (int i=1;i<mCount;i++) {
            aX = mX[i];aY = mY[i];
            Graphics::DrawLine(aLastX, aLastY, aX, aY, pLineSize);
            aLastX = aX;aLastY = aY;
        }
    }
}

void FPointList::DrawEdgeLists(FPointList *pEdgeList1, FPointList *pEdgeList2, int pStartIndex, int pSkipAmount) {
    if (pSkipAmount < 1)pSkipAmount = 1;
    if ((pEdgeList1 != 0) && (pEdgeList2 != 0)) {
        int aCount = ((pEdgeList1->mCount < pEdgeList2->mCount) ? (pEdgeList1->mCount) : (pEdgeList2->mCount));
        int aIndex = pStartIndex;
        
        if (aIndex >= 0) {
            while (aIndex < aCount) {
                Graphics::DrawLine(pEdgeList1->mX[aIndex], pEdgeList1->mY[aIndex], pEdgeList2->mX[aIndex], pEdgeList2->mY[aIndex], 2);
                aIndex += pSkipAmount;
            }
        }
    }
}

void FPointList::DrawTriangleList(GFX_MODEL_INDEX_TYPE *pIndex, int pCount) {
	int aIndex1 = 0;
	int aIndex2 = 0;
	int aIndex3 = 0;
	int aSlot = 0;
	int aCap = (pCount - 2);
	while (aSlot < aCap) {
		aIndex1 = pIndex[aSlot++];
		aIndex2 = pIndex[aSlot++];
		aIndex3 = pIndex[aSlot++];
		Graphics::DrawTriangle2D(mX[aIndex1], mY[aIndex1], mX[aIndex2], mY[aIndex2], mX[aIndex3], mY[aIndex3]);

	}
}


void FPointList::Save(FFile *pFile) {
    if (pFile) {
        pFile->WriteInt(mCount);
        for (int i=0;i<mCount;i++) {
            pFile->WriteFloat(mX[i]);
            pFile->WriteFloat(mY[i]);
        }
    }
}

void FPointList::Load(FFile *pFile) {
    Clear();
    if (pFile) {
        int aCount = pFile->ReadInt();
        Size(aCount);
        float aReadX = 0.0f;
        float aReadY = 0.0f;
        for (int i=0;i<aCount;i++) {
            aReadX = pFile->ReadFloat();
            aReadY = pFile->ReadFloat();
            Add(aReadX, aReadY);
        }
    }
}

void FPointList::Reverse() {
    if (mCount > 1) {
        int aStartIndex = 0;
        int aEndIndex = (mCount - 1);
        float aHoldX = 0.0f;
        float aHoldY = 0.0f;
        while (aStartIndex < aEndIndex) {
            aHoldX = mX[aEndIndex];
            aHoldY = mY[aEndIndex];
            mX[aEndIndex] = mX[aStartIndex];
            mY[aEndIndex] = mY[aStartIndex];
            mX[aStartIndex] = aHoldX;
            mY[aStartIndex] = aHoldY;
            aStartIndex++;
            aEndIndex--;
        }
    }
}

void FPointList::RotateRight90() {
	float aHold = 0.0f;

	for (int i = 0; i < mCount; i++) {
		aHold = mX[i];
		mX[i] = (-mY[i]);
		mY[i] = aHold;
	}
}

void FPointList::FlipH() {
	for (int i = 0; i < mCount; i++) {
		mX[i] = -(mX[i]);
	}
}

void FPointList::FlipV() {
	for (int i = 0; i < mCount; i++) {
		mY[i] = -(mY[i]);
	}
}



void FPointList::GenerateRect(float pX, float pY, float pWidth, float pHeight) {
    if (mSize < 4)Size(4);
    Reset();
    Add(pX, pY);
    Add(pX + pWidth, pY);
    Add(pX + pWidth, pY + pHeight);
    Add(pX, pY + pHeight);
}

void FPointList::GenerateCircle(float pRadius, float pMinDist) {
    float aCircumference = PI2 * (pRadius);
    int aPointCount = 12;
    if (pMinDist > 0.5f) {
        aPointCount = (int)((aCircumference / pMinDist) + 0.5f);
        if(aPointCount < 4)aPointCount = 4;
    }
    float aFactor = (float)(aPointCount);
    if (aFactor <= 1.0f) aFactor = 1.0f;
    if(aPointCount > mSize)SetSize(aPointCount);
    float aPercent = 0.0f;
    float aRotation = 0.0f;
    Reset();
    for (int i=0;i<aPointCount;i++) {
        aPercent = ((float)i) / aFactor;
		aRotation = aPercent * (PI2);
        Add(sin(aRotation) * pRadius, -cos(aRotation) * pRadius);
    }
}

bool FPointList::ContainsPoint(float pX, float pY) {
    bool aResult = false;
    for (int aStart=0,aEnd=(mCount - 1);aStart<mCount;aEnd=aStart++) {
        if ((((mY[aStart] <= pY) && (pY < mY[aEnd]))||
             ((mY[aEnd] <= pY) && (pY < mY[aStart])))&&
            (pX < (mX[aEnd] - mX[aStart]) * (pY - mY[aStart])
             / (mY[aEnd] - mY[aStart]) + mX[aStart])) {
            aResult = !aResult;
        }
    }
    return aResult;
}

bool FPointList::IsClockwise() {
    float aAreaSum = 0;
    for (int aStart = 0,aEnd = mCount-1;aStart < mCount;aEnd = aStart++) {
        aAreaSum += CROSS_PRODUCT(mX[aStart], mY[aStart], mX[aEnd], mY[aEnd]);
    }
    return aAreaSum < 0;
}

void FPointList::ValueAdd(float pAddX, float pAddY) {
    for (int i=0;i<mCount;i++) {
        mX[i] += pAddX;
        mY[i] += pAddY;
    }
}

void FPointList::ValueMultiply(float pFactorX, float pFactorY) {
    for (int i=0;i<mCount;i++) {
        mX[i] *= pFactorX;
        mY[i] *= pFactorY;
    }
}

void FPointList::ValueDivide(float pFactorX, float pFactorY) {
    for (int i=0;i<mCount;i++) {
        mX[i] /= pFactorX;
        mY[i] /= pFactorY;
    }
}


void FPointList::Clone(FPointList *pPointList) {
	if (pPointList) {
		if (pPointList->mCount > mSize) {
			Size(pPointList->mCount);
		}
		Reset();
		int aCount = pPointList->mCount;
		for (int i = 0; i<aCount; i++) {
			Add(pPointList->mX[i], pPointList->mY[i]);
		}
	}
}

void FPointList::CloneOffset(FPointList *pPointList, FPointList *pNormalList, float pOffset)
{
    if((pPointList != 0) && (pNormalList != 0))
    {
        if(pPointList->mCount <= 0)
        {
            Clear();
        }
        else
        {
            if(pPointList->mCount > mSize)
            {
                Size(pPointList->mCount);
            }
            
            if(pPointList->mCount > pNormalList->mSize)
            {
                pNormalList->Size(pPointList->mCount);
            }
            
            
            Reset();
            
            pNormalList->Reset();
            
            if(pPointList->mCount == 1)
            {
                Add(pPointList->mX[0], pPointList->mY[0]);
            }
            else
            {
                
                mCount = pPointList->mCount;
                
                float aX1 = 0.0f;
                float aY1 = 0.0f;
                
                float aX2 = 0.0f;
                float aY2 = 0.0f;
                
                float aDirX = 0.0f;
                float aDirY = 0.0f;
                
                float aLength = 0.0f;
                
                for(int aStart=0, aEnd=(mCount-1);aStart<mCount;aEnd = aStart++)
                {
                    aX1 = pPointList->mX[aStart];
                    aY1 = pPointList->mY[aStart];
                    
                    aX2 = pPointList->mX[aEnd];
                    aY2 = pPointList->mY[aEnd];
                    
                    aDirX = (aX1 - aX2);
                    aDirY = (aY1 - aY2);
                    
                    aLength = aDirX * aDirX + aDirY * aDirY;
                    
                    if(aLength > 0.05f)
                    {
                        aLength = sqrtf(aLength);
                        
                        aDirX /= aLength;
                        aDirY /= aLength;
                    }
                    else
                    {
                        aDirY = -1;
                        aDirX = 0;
                    }
                    
                    pNormalList->Add(-aDirY, aDirX);
                    
                    //aNormX[aStart] = (-aDirY);
                    //aNormY[aStart] = aDirX;
                }
                
                //for(int aStart=0, aEnd=3;aStart<4;aEnd = aStart++)
                for(int aStart=0, aEnd=(pPointList->mCount-1);aStart<pPointList->mCount;aEnd = aStart++)
                {
                    FVec2 aLerp = FVec2Lerp(FVec2(pNormalList->mX[aEnd], pNormalList->mY[aEnd]), FVec2(pNormalList->mX[aStart], pNormalList->mY[aStart]), 0.5f);
                    
                    mX[aEnd] = pPointList->mX[aEnd] - (aLerp.mX * pOffset);
                    mY[aEnd] = pPointList->mY[aEnd] - (aLerp.mY * pOffset);
                }
                
                
            }
        }
    }
}

void FPointList::CloneOffset(FPointList *pPointList, float pOffset)
{
    if(pPointList)
    {
        FPointList aNormList;
        CloneOffset(pPointList, &aNormList, pOffset);
    }
}

int FPointList::LoopIndex(int pIndex)
{
    int aResult = 0;
    
    if(mCount > 1)
    {
        aResult = pIndex;
        
        if(aResult < 0)aResult += mCount;
        if(aResult >= mCount)aResult -= mCount;
        
        if(((aResult >= 0) && (aResult < mCount)) == false)
        {
            aResult = (aResult % mCount);
            if(aResult < 0)aResult += mCount;
            if(aResult >= mCount)aResult -= mCount;
        }
    }
    else
    {
        aResult = 0;
    }
    
    return aResult;
}

float FPointList::LoopX(int pIndex)
{
    return GetX(LoopIndex(pIndex));
}

float FPointList::LoopY(int pIndex)
{
    return GetY(LoopIndex(pIndex));
}

float FPointList::LoopAngleNext(int pIndex)
{
    float aResult = 0.0f;
    
    if(mCount > 1)
    {
        int aIndex1 = LoopIndex(pIndex);
        int aIndex2 = (aIndex1 + 1);
        if(aIndex2 == mCount)aIndex2 = 0;
        
        float aDiffX = mX[aIndex2] - mX[aIndex1];
        float aDiffY = mY[aIndex2] - mY[aIndex1];
        
        aResult = -atan2f(-aDiffX, -aDiffY) * 57.2957795130823208767981548141052;
    }
    
    return aResult;
}


float FPointList::LoopAnglePrev(int pIndex)
{
    float aResult = 0.0f;
    
    if(mCount > 1)
    {
        int aIndex1 = LoopIndex(pIndex);
        int aIndex2 = (aIndex1 - 1);
        if(aIndex2 < 0)aIndex2 = (mCount - 1);
        
        float aDiffX = mX[aIndex2] - mX[aIndex1];
        float aDiffY = mY[aIndex2] - mY[aIndex1];
        
        aResult = -atan2f(-aDiffX, -aDiffY) * 57.2957795130823208767981548141052;
    }
    
    return aResult;
}

float FPointList::LoopAngleBetween(int pIndex)
{
    float aResult = 0.0f;
    
    if(mCount > 2)
    {
        float aNext = LoopAngleNext(pIndex);
        float aPrev = LoopAnglePrev(pIndex);
        
        aResult = ((aNext + aPrev) / 2.0f);
    }
    else if(mCount > 1)
    {
    aResult = LoopAngleNext(pIndex);
        
    }
    return aResult;
}

float FPointList::LoopAngleBetweenInside(int pIndex)
{
    float aResult = LoopAngleBetween(pIndex);
    
    if(mCount > 2)
    {
        float aX = LoopX(pIndex);
        float aY = LoopY(pIndex);
        
        float aProbeLength = 0.5f;
        
        float aAngle = aResult - 180.0f;
        if(aAngle < 0.0)aAngle += 360.0f;
        
        float aDirX = Sin(aAngle);
        float aDirY = -Cos(aAngle);
        
        float aCheckX1 = (aX + aDirX * aProbeLength);
        float aCheckY1 = (aY + aDirY * aProbeLength);
        
        if(ContainsPoint(aCheckX1, aCheckY1) == true)
        {
            aResult = aAngle;
        }
        
        
        
    }
    
    return aResult;
}

int FPointList::GetNextIndex(int pIndex)
{
    int aResult = 0;
    if(mCount > 0)
    {
        aResult = (pIndex + 1);
        if(aResult >= mCount)aResult = 0;
        else if(aResult < 0) aResult = (mCount - 1);
    }
    return aResult;
}

int FPointList::GetPrevIndex(int pIndex) {
    int aResult = 0;
    if (mCount > 0) {
        aResult = (pIndex - 1);
        if (aResult < 0) {
            aResult = (mCount - 1);
        } else if(aResult >= mCount) {
            aResult = 0;
        }
    }
    return aResult;
}

void FPointList::Transform(FPointList *pPointList, float pX, float pY, float pScaleX, float pScaleY, float pRotation) {
    Clone(pPointList);
    Transform(pX, pY, pScaleX, pScaleY, pRotation);
}

void FPointList::Transform(float pX, float pY, float pScaleX, float pScaleY, float pRotation) {
    TransformScaleRotate(pScaleX, pScaleY, pRotation);
    TransformTranslate(pX, pY);
}

void FPointList::TransformRotate(float pRotation) {
    if (pRotation != 0.0f) {
        pRotation = pRotation * 0.01745329251994329576923690768488;
        float aX = 0.0f;
        float aY = 0.0f;
        float aDist = 0.0f;
        float aPivot = 0.0f;
        for (int i=0;i<mCount;i++) {
            aX = mX[i];
            aY = mY[i];
            aDist = aX * aX + aY * aY;
            if (aDist > SQRT_EPSILON) {
                aDist = sqrtf(aDist);
                aX /= aDist;
                aY /= aDist;
            }
            aPivot = (pRotation - atan2f(-aX, -aY));
            mX[i] = (sinf(aPivot)) * aDist;
            mY[i] = (-cosf(aPivot)) * aDist;
        }
    }
}

void FPointList::TransformScaleRotate(float pScaleX, float pScaleY, float pRotation) {
    if (pRotation != 0.0f) {
        pRotation = pRotation * 0.01745329251994329576923690768488;
        float aX = 0.0f;
        float aY = 0.0f;
        float aDist = 0.0f;
        float aPivot = 0.0f;
        for (int i=0;i<mCount;i++) {
            aX = mX[i] * pScaleX;
            aY = mY[i] * pScaleY;
            aDist = aX * aX + aY * aY;
            if (aDist > SQRT_EPSILON) {
                aDist = sqrtf(aDist);
                aX /= aDist;
                aY /= aDist;
            }
            aPivot = (pRotation - atan2f(-aX, -aY));
            mX[i] = (sinf(aPivot)) * aDist;
            mY[i] = (-cosf(aPivot)) * aDist;
        }
    } else {
        if (pScaleX != 1.0f) {
            for (int i=0;i<mCount;i++) {
                mX[i] *= pScaleX;
            }
        }
        if (pScaleY != 1.0f) {
            for (int i=0;i<mCount;i++) {
                mY[i] *= pScaleY;
            }
        }
    }
}

void FPointList::TransformTranslate(float pX, float pY) {
    if (pX != 0)for(int i=0;i<mCount;i++) {
        mX[i] += pX;
    }
    if (pY != 0)for(int i=0;i<mCount;i++) {
        mY[i] += pY;
    }
}

void FPointList::Untransform(float pX, float pY, float pScaleX, float pScaleY, float pRotation)
{
    UntransformTranslate(pX, pY);
    
    if((pScaleX != 1.0f) || (pScaleY != 1.0f) || (pRotation != 0.0f))
    UntransformScaleRotate(pScaleX, pScaleY, pRotation);
}

void FPointList::UntransformScaleRotate(float pScaleX, float pScaleY, float pRotation)
{
    if((pScaleX < -0.01f) || (pScaleX > -0.01f) || (pScaleY < -0.01f) || (pScaleY > -0.01f))
    {
        TransformScaleRotate(1.0 / pScaleX, 1.0 / pScaleY, -pRotation);
    }
}

void FPointList::UntransformTranslate(float pX, float pY)
{
    TransformTranslate(-pX, -pY);
}

int FPointList::GetClosestIndex(float pX, float pY, float &pDist, int pIgnoreIndex1, int pIgnoreIndex2, int pIgnoreIndex3) {
    int aResult = -1;
    if (mCount > 0) {
        
        float aBestDist = 90.0f * 90.0f;
        
        float aDiffX = 0.0f;
        float aDiffY = 0.0f;
        float aDist = 0.0f;
        
        for (int i=0;i<mCount;i++) {
            aDiffX = mX[i] - pX;
            aDiffY = mY[i] - pY;
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            if (aDist < aBestDist) {
                if ((i != pIgnoreIndex1) && (i != pIgnoreIndex2) && (i != pIgnoreIndex3)) {
                    aBestDist = aDist;
                    aResult = i;
                
                    pDist = aDist;
                }
            }
        }
    }
    
    return aResult;
}

int FPointList::GetClosestIndex(float pX, float pY, float &pDist)
{
    int aResult = -1;
    
    if (mCount > 0) {
        aResult = 0;
        float aDiffX = mX[0] - pX;
        float aDiffY = mY[0] - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        pDist = aDist;
        for (int i=1;i<mCount;i++) {
            aDiffX = mX[i] - pX;
            aDiffY = mY[i] - pY;
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            if (aDist < pDist) {
                pDist = aDist;
                aResult = i;
            }
        }
    }
    
    return aResult;
}

int FPointList::GetClosestIndex(float pX, float pY)
{
    int aResult = -1;
    
    if(mCount > 0)
    {
        aResult = 0;
        float aDiffX = mX[0] - pX;
        float aDiffY = mY[0] - pY;
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        float aBestDist = aDist;
        for(int i=1;i<mCount;i++)
        {
            aDiffX = mX[i] - pX;
            aDiffY = mY[i] - pY;
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            if(aDist < aBestDist)
            {
                aBestDist = aDist;
                aResult = i;
            }
        }
    }
    
    return aResult;
}

int	FPointList::GetClosestEdge(float pX, float pY, bool pClosed, float &pDist)
{
    int aResult = -1;
    
    float aBestDist = 512.0f * 512.0f;
    
    
        if(mCount > 1)
        {
            int aIndex = 0;
            
            float aX = 0.0f;
            float aY = 0.0f;
            
            float aLastX = aX;
            float aLastY = aY;
            
            if(pClosed)
            {
                aIndex = 0;
                aLastX = mX[mCount - 1];
                aLastY = mY[mCount - 1];
            }
            else
            {
                aIndex = 1;
                aLastX = mX[0];
                aLastY = mY[0];
            }
            
            while(aIndex < mCount)
            {
                aX = mX[aIndex];
                aY = mY[aIndex];
                
                float aClosestX = aX;
                float aClosestY = aY;
                
                FLine::SegmentClosestPoint(aLastX, aLastY, aX, aY, pX, pY, aClosestX, aClosestY);
                
                float aDiffX = aClosestX - pX;
                float aDiffY = aClosestY - pY;
                
                float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
                
                if(aDist < aBestDist)
                {
                    
                    aBestDist = aDist;
                    aResult = aIndex;
                }
                
                //if(aBestDist
                
                //FLine::
                
                //pEdgeP1->Add(aLastX, aLastY);
                //pEdgeP2->Add(aX, aY);
                
                aLastX = aX;
                aLastY = aY;
                
                aIndex++;
            }
        }
    else
    {
        return GetClosestIndex(pX, pY, pDist);
    }
    
    return aResult;
}


void FPointList::GenerateEdgeLists(FPointList *pEdgeP1, FPointList *pEdgeP2, bool pClosed)
{
    if((pEdgeP1 != 0) && (pEdgeP2 != 0))
    {
        pEdgeP1->Reset();
        pEdgeP2->Reset();
        if(mCount > 1)
        {
            int aIndex = 0;
            
            float aX = 0.0f;
            float aY = 0.0f;
            
            float aLastX = aX;
            float aLastY = aY;
            
            if(pClosed)
            {
                aIndex = 0;
                aLastX = mX[mCount - 1];
                aLastY = mY[mCount - 1];
            }
            else
            {
                aIndex = 1;
                aLastX = mX[0];
                aLastY = mY[0];
            }
            
            while(aIndex < mCount)
            {
                aX = mX[aIndex];
                aY = mY[aIndex];
                
                pEdgeP1->Add(aLastX, aLastY);
                pEdgeP2->Add(aX, aY);
                
                aLastX = aX;
                aLastY = aY;
                
                aIndex++;
            }
        }
    }
}

void FPointList::GetSymmetryFromEdges(FPointList *pEdgeP1, FPointList *pEdgeP2, bool pSliceSide, float pPlaneOriginX, float pPlaneOriginY, float pPlaneDirX, float pPlaneDirY)
{
    Reset();
    if((pEdgeP1 != 0) && (pEdgeP2 != 0))
    {
        int aCount = pEdgeP1->mCount;
        if(pEdgeP2->mCount < aCount)aCount = pEdgeP2->mCount;
        float aHitX = 0.0f;
        float aHitY = 0.0f;
        float aHitDist = 0.0f;
        FPointList aNewEdges1;
        FPointList aNewEdges2;
        for(int i=0;i<aCount;i++)
        {
            float aX1 = pEdgeP1->mX[i];
            float aY1 = pEdgeP1->mY[i];
            
            float aX2 = pEdgeP2->mX[i];
            float aY2 = pEdgeP2->mY[i];
            
            int aSide1 = SideOfLine(aX1, aY1, pPlaneOriginX, pPlaneOriginY, pPlaneOriginX + pPlaneDirX * 200.0f, pPlaneOriginY + pPlaneDirY * 200.0f);
            int aSide2 = SideOfLine(aX2, aY2, pPlaneOriginX, pPlaneOriginY, pPlaneOriginX + pPlaneDirX * 200.0f, pPlaneOriginY + pPlaneDirY * 200.0f);
            
            if(FLine::SegmentPlaneIntersection(aX1, aY1, aX2, aY2, pPlaneOriginX, pPlaneOriginY, pPlaneDirX, pPlaneDirY, aHitX, aHitY, aHitDist))
            {
                
                if(aSide1 < 0)
                {
                    aNewEdges1.Add(aX1, aY1);
                    aNewEdges2.Add(aHitX, aHitY);
                }
                else
                {
                    aNewEdges1.Add(aHitX, aHitY);
                    aNewEdges2.Add(aX2, aY2);
                }
            }
            else
            {
                if((aSide1 < 0) && (aSide1 == aSide2))
                {
                    aNewEdges1.Add(aX1, aY1);
                    aNewEdges2.Add(aX2, aY2);
                }
            }
        }
        pEdgeP1->Clear();
        pEdgeP2->Clear();
        pEdgeP1->Add(&aNewEdges1);
        pEdgeP2->Add(&aNewEdges2);
    }
}


void FPointList::GetSymmetry(FPointList *pOriginalPath, bool pOriginalPathClosed, bool pSliceSide, float pSliceLineX1, float pSliceLineY1, float pSliceLineX2, float pSliceLineY2) {
    Reset();
    FPointList aEdgeP1;
    FPointList aEdgeP2;
    if (pOriginalPath) {
        pOriginalPath->GenerateEdgeLists(&aEdgeP1, &aEdgeP2, pOriginalPathClosed);
        float aSlicePlaneDirX = (pSliceLineX2 - pSliceLineX1);
        float aSlicePlaneDirY = (pSliceLineY2 - pSliceLineY1);
        float aSlicePlaneLength = (aSlicePlaneDirX * aSlicePlaneDirX) + (aSlicePlaneDirY * aSlicePlaneDirY);
        
        if (aSlicePlaneLength >= SQRT_EPSILON) {
            aSlicePlaneLength = sqrtf(aSlicePlaneLength);
            
            aSlicePlaneDirX /= aSlicePlaneLength;
            aSlicePlaneDirY /= aSlicePlaneLength;
        } else {
            aSlicePlaneDirX = 0.0f;
            aSlicePlaneDirY = -1.0f;
        }
        GetSymmetryFromEdges(&aEdgeP1, &aEdgeP2, pSliceSide, pSliceLineX1, pSliceLineY1, aSlicePlaneDirX, aSlicePlaneDirY);
    }
}

float FPointList::GetX(int pIndex) {
    return ((pIndex >= 0) && (pIndex < mCount)) ? mX[pIndex] : 0.0f;
}

float FPointList::GetY(int pIndex) {
    return ((pIndex >= 0) && (pIndex < mCount)) ? mY[pIndex] : 0.0f;
}

float FPointList::GetMinX() {
    float aResult = 0.0f;
    
    if (mCount > 0) {
        aResult = mX[0];
        for (int i=1;i<mCount;i++) {
            if (mX[i] < aResult) {
                aResult = mX[i];
            }
        }
    }
    return aResult;
}

float FPointList::GetMaxX() {
    float aResult = 0.0f;
    
    if (mCount > 0) {
        aResult = mX[0];
        for (int i=1;i<mCount;i++) {
            if (mX[i] > aResult) {
                aResult = mX[i];
            }
        }
    }
    return aResult;
}

float FPointList::GetMinY() {
    float aResult = 0.0f;
    if (mCount > 0) {
        aResult = mY[0];
        for (int i=1;i<mCount;i++) {
            if (mY[i] < aResult) {
                aResult = mY[i];
            }
        }
    }
    return aResult;
}

float FPointList::GetMaxY() {
    float aResult = 0.0f;
    if (mCount > 0) {
        aResult = mY[0];
        for (int i=1;i<mCount;i++) {
            if (mY[i] > aResult) {
                aResult = mY[i];
            }
        }
    }
    return aResult;
}

float FPointList::GetCenterX() {
    float aResult = 0.0f;
    if (mCount > 0) {
        aResult = 0.0f;
        for (int i=0;i<mCount;i++) {
            aResult += mX[i];
        }
        aResult /= ((float)mCount);
    }
    return aResult;
}

float FPointList::GetCenterY() {
    float aResult = 0.0f;
    if (mCount > 0) {
        aResult = 0.0f;
        for (int i=0;i<mCount;i++) {
            aResult += mY[i];
        }
        aResult /= ((float)mCount);
    }
    return aResult;
}
