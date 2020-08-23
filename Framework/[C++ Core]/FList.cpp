#include "FList.hpp"
#include "core_includes.h"

FList::FList() {
	mData = 0;
	mSize = 0;
	mCount = 0;
}

FList::~FList() {
	Clear();
}
		
void FList::Clear() {
	delete [] mData;
	mData = 0;
	mSize = 0;
	mCount = 0;
}

void FList::Size(int pSize) {
	if (pSize <= 0) {
		Clear();
	} else if (pSize != mSize) {
		void **aNewData = new void*[pSize];
        if (mCount > pSize) {
            mCount = pSize;
        }
        for (int i=0;i<mCount;i++) {
            aNewData[i] = mData[i];
        }
        for (int i=mCount;i<mSize;i++) {
            aNewData[i] = NULL;
        }
		mSize = pSize;
		delete[] mData;
		mData = aNewData;
	}
}

void FList::Add(void *pItem) {
    if (pItem == NULL) { return; }
	if (mCount >= mSize) {
		Size(mCount + mCount / 2 + 1);
	}
	mData[mCount]=pItem;
	mCount++;
}

void FList::Insert(void *pItem, int pSlot) {
	if (!pItem) return;
	if (mCount == mSize) {
		mSize = mCount + mCount / 2 + 1;
		void **aData = new void*[mSize];
		void **aCopy = mData;
		void **aPaste = aData;
		void **aShelf = mData + mCount;
		while (aCopy < aShelf) {
			*aPaste = *aCopy;
			aCopy++;
			aPaste++;
		}
		delete[]mData;
		mData = aData;
	}
	if (pSlot < 0) pSlot = 0;
	if (pSlot > mCount) pSlot = mCount;
	void **aSlot=&mData[pSlot-1];
	void **aPaste=&mData[mCount];
	void **aCopy=&mData[mCount-1];
	while (aCopy>aSlot) {
		*aPaste=*aCopy;
		aPaste--;
		aCopy--;
	}
	mData[pSlot]=pItem;
	mCount++;
}

void FList::Add(FList &pList) {
    int aNewCount = mCount + pList.mCount;
	if (aNewCount > mSize) {
        Size(aNewCount);
	}
    for (int i = 0;i<pList.mCount;i++) {
        Add(pList.mData[i]);
    }
}

//TODO: Improve speed possible.
void FList::Remove(FList &pList) {
    for (int i = 0;i<pList.mCount;i++) {
        Remove(pList.mData[i]);
    }
}

void FList::RemoveAtIndex(int pIndex) {
    if(pIndex < 0 || pIndex >= mCount)return;
    void **aSeek=mData+pIndex;
	void **aShelf=mData+mCount;
    void **aCopy=aSeek;
    aSeek++;
    while (aSeek<aShelf) {
        *aCopy=*aSeek;
        aCopy++;
        aSeek++;
    }
    mCount--;
}

void FList::Remove(void *pItem) {
	void **aSeek=mData;
	void **aShelf=mData+mCount;
	while (aSeek < aShelf) {
        if (*aSeek == pItem) { break; }
		aSeek++;
	}
	if (aSeek < aShelf) {
		void **aCopy = aSeek;
		aSeek++;
		while (aSeek<aShelf) {
			if (*aSeek != pItem) {
				*aCopy = *aSeek;
				aCopy++;
			}
			aSeek++;
		}
		mCount = (int)(aCopy - mData);
	}
}

void *FList::FetchClosest(int pIndex) {
    int aIndex = pIndex;
    if (aIndex >= mCount) {
        aIndex = mCount - 1;
    }
    if (aIndex <= 0) {
        aIndex = 0;
    }
    return Fetch(aIndex);
}

void *FList::Fetch(int pIndex) {
    if ((pIndex >= 0) && (pIndex < mCount)) {
        return mData[pIndex];
    }
    return NULL;
}

void *FList::FetchRandom() {
    void *aResult = NULL;
    if (mCount > 0) {
        aResult = mData[gRand.Get(mCount)];
    }
    return aResult;
}

void *FList::FetchCircular(int pIndex) {
    if (mCount > 0) {
        if (pIndex < 0 || pIndex >= mCount) {
            pIndex = (pIndex % mCount);
            if (pIndex < 0) {
                pIndex += mCount;
            }
        }
        return mData[pIndex];
    }
    return NULL;
}

void *FList::PopFirst() {
    void *aResult = 0;
    if (mCount > 0) {
        aResult = mData[0];
        for (int i=1;i<mCount;i++) {
            mData[i - 1] = mData[i];
        }
        mCount--;
    }
    return aResult;
}

void *FList::PopLast() {
    void *aResult = 0;
    if (mCount > 0) {
        aResult = mData[mCount - 1];
        mCount--;
    }
    return aResult;
}

void FList::RemoveFirst(void *pItem) {
	void **aSeek = mData;
	void **aShelf = mData + mCount;
	while (aSeek < aShelf) {
        if (*aSeek == pItem) { break; }
		aSeek++;
	}
	if (aSeek < aShelf) {
		void **aCopy = aSeek;
		aSeek++;
		while (aSeek < aShelf) {
			*aCopy = *aSeek;
			aCopy++;
			aSeek++;
		}
		mCount--;
	}
}

void FList::MoveObjectUp(void *pItem) {
	if ((pItem != 0) && (mCount > 0)) {
		void **aSeek = mData;
		void **aShelf = mData + mCount;
		while (aSeek < aShelf) {
			if(*aSeek == pItem)break;
			aSeek++;
		}
		if (aSeek < (aShelf - 1)) {
			void *aHold = *aSeek;
			*aSeek = *(aSeek + 1);
			*(aSeek + 1) = aHold;
		}
	}
}

void FList::MoveObjectDown(void *pItem) {
	if ((pItem != 0) && (mCount > 0)) {
		void **aSeek = mData;
		void **aShelf = mData + mCount;
		while (aSeek < aShelf) {
			if(*aSeek == pItem)break;
			aSeek++;
		}
		if (aSeek < aShelf) {
			if (aSeek > mData) {
				void *aHold = *aSeek;
				*aSeek = *(aSeek - 1);
				*(aSeek - 1) = aHold;
			}
		}
	}
}

void FList::RotateObjectUp(void *pItem) {
    int aIndex = Find(pItem);
    if (aIndex != -1) {
        if (aIndex >= (mCount - 1)) {
            MoveToFirst(pItem);
        } else {
            MoveObjectUp(pItem);
        }
    }
}

void FList::RotateObjectDown(void *pItem) {
    int aIndex = Find(pItem);
    if (aIndex != -1) {
        if (aIndex <= 0) {
            MoveToLast(pItem);
        } else {
            MoveObjectDown(pItem);
        }
    }
}

int FList::Find(void *pItem) {
	void **aSeek = mData;
	void **aShelf = mData + mCount;
	while (aSeek < aShelf) {
        if (*aSeek == pItem) { break; }
		aSeek++;
	}
	int aResult = -1;
    if (aSeek < aShelf) {
        aResult = (int)(aSeek - mData);
    }
	return aResult;
}

bool FList::Exists(void *pItem) {
	void **aSeek = mData;
	void **aShelf = mData + mCount;
	while (aSeek < aShelf) {
        if (*aSeek == pItem) { break; }
		aSeek++;
	}
	return (aSeek < aShelf);
}

void FList::Reverse() {
	if (mCount > 0) {
		void **aTop = mData + (mCount - 1);
		void **aBottom = mData;
		void *aHold;
		while (aTop > aBottom) {
			aHold = *aTop;
			*aTop = *aBottom;
			*aBottom = aHold;
			aTop--;
			aBottom++;
		}
	}
}

void FList::RemoveLast(void *pItem) {
    if (mCount == 0) { return; }
	void **aSeek = mData + (mCount - 1);
	void **aShelf = mData;
	while (aSeek >= aShelf) {
		if(*aSeek == pItem)break;
		aSeek--;
	}
    while ((aSeek < aShelf) && (*aSeek != pItem)) { aSeek++; }
	if (aSeek >= aShelf) {
		void **aCopy = aSeek;
		aShelf = mData + mCount;
		aSeek++;
		while (aSeek < aShelf) {
			*aCopy = *aSeek;
			aCopy++;
			aSeek++;
		}
		mCount--;
	}
}

void FList::RemoveAllBefore(int pIndex) {
    if (pIndex >= (mCount - 1)) {
        mCount = 0;
    } else if(pIndex <= 0) {
        //Do Nothing
    } else {
        int aNewCount = mCount - pIndex;
        for (int i = 0;i<aNewCount;i++) {
            mData[i]=mData[i+pIndex];
        }
        mCount = aNewCount;
    }
}

void FList::RemoveAllAtOrBefore(int pIndex) {
    RemoveAllBefore(pIndex + 1);
}

void FList::RemoveAllAfter(int pIndex) {
    if (pIndex >= (mCount - 1)) {
        //Do Nothing
    } else if(pIndex < 0) {
        mCount = 0;
    } else {
        mCount = pIndex + 1;
    }
}

void FList::RemoveAllAtOrAfter(int pIndex) {
    RemoveAllAfter(pIndex - 1);
}


void FList::MoveToFirst(void *pItem)
{
	void **aSeek=mData;
	void **aShelf=mData+mCount;
	while(aSeek<aShelf)
	{
		if(*aSeek==pItem)break;
		aSeek++;
	}
	if(aSeek<aShelf)
	{
		aShelf=mData;
		while(aSeek>mData)
		{
			*aSeek=*(aSeek-1);
			aSeek--;
		}
		*mData=pItem;
	}
}

void FList::MoveToLast(void *pItem) {
	void **aSeek = mData;
	void **aShelf = mData + mCount;
	while (aSeek < aShelf) {
        if(*aSeek == pItem) { break; }
		aSeek++;
	}
	if (aSeek < aShelf) {
		aShelf--;
		while (aSeek < aShelf) {
			*aSeek = *(aSeek+1);
			aSeek++;
		}
		*aShelf = pItem;
	}
}

void FList::Swap(void *pItem1, void *pItem2) {
	void **aSeek1 = mData;
	void **aSeek2 = mData;
	void **aShelf = mData + mCount;
	while (aSeek1<aShelf) {
        if (*aSeek1 == pItem1) { break; }
		aSeek1++;
	}
	while (aSeek2 < aShelf) {
        if (*aSeek2 == pItem2) { break; }
		aSeek2++;
	}
	if ((aSeek1 < aShelf) && (aSeek2 < aShelf)) {
		*aSeek1 = pItem2;
		*aSeek2 = pItem1;
	}
}

void FList::Shuffle() {
	void *aHold = NULL;
	int aRand = 0;
	for (int i=0;i<mCount;i++) {
		aHold = mData[i];
		aRand = gRand.Get(mCount);
		mData[i] = mData[aRand];
		mData[aRand] = aHold;
	}
}

void FList::RotateFrontToBack() {
    if (mCount > 1) {
        void *aHold = mData[0];
        for (int i=1;i<mCount;i++) {
            mData[i - 1] = mData[i];
        }
        mData[mCount - 1] = aHold;
    }
}

void FList::RotateBackToFront() {
    if (mCount > 1) {
        void *aHold = mData[mCount - 1];
        for (int i=(mCount - 1);i>=1;i--) {
            mData[i] = mData[i - 1];
        }
        mData[0] = aHold;
    }
}


/*
void FList::Sort(void *pParameter)
{
	for(int i=1,int j;i<mCount;i++)
	{
		void *aHold=mData[i];
		j=i;
		while((j>0) && ((mData[j-1]+<aHold))
		{
			mIndex[j]=mIndex[j-1];
			j--;
		}
		mIndex[j]=aHold;
	}
}
 */

bool FList::IsSorted()
{
	for(int i=1;i<mCount;i++)if(mData[i-1]>mData[i])return false;
	return true;
}

void FList::ISort()
{
	int *aData=(int*)mData;
	int aStart;
	int aKey;
	int aCheck;
	for(aStart=1; aStart<mCount;aStart++)
	{
		aKey=aData[aStart];
		aCheck=aStart-1;
		while(aCheck >= 0 && aData[aCheck] > aKey)
		{
			aData[aCheck+1]=aData[aCheck];
			aCheck--;
		}
		aData[aCheck+1]=aKey;
	}
}

void FList::Sort()
{
	if(mCount<2)return;
	
	int *aData=(int*)mData;
	
	//Insertion sort blocks of a given size...
#define INSERT_SORT_BLOCK_SIZE 7
	
	int aStart, aEnd, aKey, aCheck, aIndex;
	
	for(aIndex = 0;aIndex<mCount;aIndex+=INSERT_SORT_BLOCK_SIZE)
	{
		aEnd=aIndex+INSERT_SORT_BLOCK_SIZE;
		if(aEnd>mCount)aEnd=mCount;
		for(aStart=aIndex+1; aStart<aEnd;aStart++)
		{
			aKey=aData[aStart];
			aCheck=aStart-1;
			while(aCheck>=aIndex && aData[aCheck] > aKey)
			{
				aData[aCheck+1]=aData[aCheck];
				aCheck--;
			}
			aData[aCheck+1]=aKey;
		}
	}
	
	if(mCount<INSERT_SORT_BLOCK_SIZE)return;
	
	int aBlockSize=INSERT_SORT_BLOCK_SIZE;
	int aMergeIndex1,aMergeIndex2;
	int aEndIndex1, aEndIndex2;
	int aNewIndex;
	
	int *aNew=new int[mCount];
	int *aHold=aData;
	
	aData=aNew;
	aNew=aHold;
	
	while(aBlockSize<mCount)
	{
		aHold=aData;
		aData=aNew;
		aNew=aHold;
		aIndex = 0;
		while(aIndex<mCount)
		{
			aNewIndex=aIndex;
			aMergeIndex1=aIndex;
			aIndex+=aBlockSize;
			aEndIndex1=aIndex;
			aMergeIndex2=aIndex;
			aIndex+=aBlockSize;
			aEndIndex2=aIndex;
			if(aEndIndex1>mCount)aEndIndex1=mCount;
			if(aEndIndex2>mCount)aEndIndex2=mCount;
			while(aMergeIndex1<aEndIndex1 && aMergeIndex2<aEndIndex2)
			{
				if(aData[aMergeIndex1]<aData[aMergeIndex2])
				{
					aNew[aNewIndex]=aData[aMergeIndex1];
					aMergeIndex1++;
				}
				else
				{
					aNew[aNewIndex]=aData[aMergeIndex2];
					aMergeIndex2++;
				}
				aNewIndex++;
			}
			while(aMergeIndex1<aEndIndex1)
			{
				aNew[aNewIndex]=aData[aMergeIndex1];
				aMergeIndex1++;
				aNewIndex++;
			}
			while(aMergeIndex2<aEndIndex2)
			{
				aNew[aNewIndex]=aData[aMergeIndex2];
				aMergeIndex2++;
				aNewIndex++;
			}
		}
		aBlockSize*=2;
	}
	delete[]aData;
	mData=(void**)aNew;
}

void FList::Print()
{
	Log("~*~Printing FList~*~\n");
	Log("Size=%d Count=%d\n", mSize, mCount);
	
	int aSkip = 0;
	
	for(int i = 0;i<mCount;i++)
	{
		int aInt = *((int*)(mData[i]));
        //int aInt = (int)(mData[i]);
        
		Log("[%x]", (unsigned int)aInt);
		
		aSkip++;
		if(aSkip==20)
		{
			aSkip = 0;
			Log("\n");
		}
	}
	
	Log("~*~End FList Print~*~\n");
}

