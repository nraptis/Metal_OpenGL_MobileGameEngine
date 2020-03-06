#include "FString.hpp"
#include "core_includes.h"

FString::FString() {
    mData = 0; mCursor = 0; mLength = 0; mSize = 0;
}

FString::FString(const FString &pString) {
    mData = 0; mCursor = 0; mLength = 0; mSize = 0;
	Set((const char *)(pString.mData));
}

FString::FString(char *pString) {
    mData = 0; mCursor = 0; mLength = 0; mSize = 0;
	Set(pString);
}

FString::FString(const char *pString) {
    mData = 0; mCursor = 0; mLength = 0; mSize = 0;
	Set(pString);
}

FString::FString(int theInt) {
    mData = 0; mCursor = 0; mLength = 0; mSize = 0;
	ParseInt(theInt);
	//Log("FString::FStringInt(%d)(%s)\n", theInt, mData);
}

FString::FString(char theChar) {
    mCursor = 0; mLength = 1; mSize = 1;
	mData = new char[2];
	mData[0] = theChar;
	mData[1] = 0;
}

FString::FString(float pFloat) {
    mData = 0; mCursor = 0; mLength = 0; mSize = 0;
    
    FString aString;
    
    //float aAbs = pFloat;
    //if(aAbs < 0.0f)aAbs = -aAbs;
    
    //if(aAbs > 100.0f)aString.ParseFloat(pFloat, 2);
    //else if(aAbs > 10.0f)aString.ParseFloat(pFloat, 3);
    //else if(aAbs > 2.0f)aString.ParseFloat(pFloat, 4);
    //else if(aAbs > 0.25f)aString.ParseFloat(pFloat, 6);
    //else
    aString.ParseFloat(pFloat, 6);
    
    if (aString.Find('.') != -1) {
        bool aLoop = true;
        while ((aLoop == true) && (aString.mLength > 0)) {
            aLoop = false;
            if (aString.mData[aString.mLength - 1] == '0') {
                aLoop = true;
                aString.mData[aString.mLength - 1] = 0;
                aString.mLength--;
            }
        }
        
        if (aString.mLength > 0) {
            if (aString.mData[aString.mLength - 1] == '.') {
                aString += '0';
            }
        }
    }
    aString.Append('f');
    *this = aString;
}

FString::FString(float pFloat, int pDecimals) {
    mData = 0; mCursor = 0; mLength = 0; mSize = 0;
	ParseFloat(pFloat, pDecimals);
}

FString::FString(bool theBool) {
    mData = 0; mCursor = 0; mLength = 0; mSize = 0;
	ParseBool(theBool);
}



FString::~FString()
{
	Free();
}

void FString::AddCommas()
{
	if(mLength > 3)
	{
		int aLength=mLength+mLength;
		char *aNew=new char[aLength+1];
		
		aLength=0;
		
		for(int i=mLength-1, k=0;i>=0;i--)
		{
            
			aNew[aLength]=mData[i];
			aLength++;
            
			k++;
			if(k==3 && i > 0)
			{
				aNew[aLength]=',';
				aLength++;
				k=0;
			}
		}
		
		delete[]mData;
		mData=aNew;
		mLength=aLength;
		mData[mLength] = 0;
		Reverse();
	}
}

FString FString::GetNumber(int thePosition)
{
	FString aResult;
	if(mData && thePosition < mLength && thePosition >= 0)
	{
		char *aSeek = &mData[thePosition];
		while(*aSeek && !(*aSeek >= '0' && *aSeek <= '9'))aSeek++;
		if(!*aSeek)goto RETURN;
		char *aStart = aSeek;
		bool aHaveDecimal = false;
		if(aStart > &mData[thePosition])
		{
			aSeek--;
			if(*aSeek == '+' || *aSeek == '-' || *aSeek == '.')
			{
				aStart--;
				if(*aSeek == '.')
				{
					aHaveDecimal=true;
					if(aStart > &mData[thePosition])
					{
						aStart--;
						if(*aStart != '+' && *aStart != '-')
                        {
                            aHaveDecimal=false;
                            aStart++;
                        }
					}
				}
			}
			aSeek++;
		}
		while(*aSeek && (*aSeek >= '0' && *aSeek <= '9'))aSeek++;
		if(!aHaveDecimal)
		{
			if(*aSeek == '.')
			{
				aSeek++;
				while(*aSeek && (*aSeek >= '0' && *aSeek <= '9'))aSeek++;
			}
		}
		int aLength = (int)(aSeek - aStart);
		char *aNumber = new char[aLength + 1];
		aNumber[aLength] = 0;
		memcpy(aNumber, aStart, aLength);
		aResult.mData = aNumber;
		aResult.mLength = aLength;
		mCursor=aSeek;
	}
RETURN:;
	return aResult;
}

void FString::Free()
{
	delete[] mData;
	mData = 0;
	
	mCursor = 0;
	mLength = 0;
	mSize = 0;
}

void FString::Clear()
{
	if(mSize > 0)
	{
		for(int i = 0; i <= mSize; i++)
		{
			mData[i] = 0;
		}
	}

	mLength = 0;
	mCursor = 0;
}

void FString::Size(int pSize) {
	if (pSize <= 0) {
		Free();
	} else if(pSize != mSize) {
		mSize = pSize;
		char *aNew = new char[mSize + 1];
		if (mLength > mSize) {
			mLength = mSize;
		}
        for (int i=0; i<mLength; i++) { aNew[i] = mData[i]; }
		//for (int i = mLength; i <= mSize; i++) aNew[i] = 0;
        aNew[mLength] = 0;
        
		delete[] mData;
		mData = aNew;
	}
}

int	FString::Length(const char *pString) {
	int aResult = 0;
	if (pString) {
		const char *aPtr = pString;
        while (*aPtr) { aPtr++; }
		aResult = (int)(aPtr - pString);
	}
	return aResult;
}

void FString::Reset() {
    mLength = 0;
    if (mData != 0) {
        mData[0] = 0;
    }
}

void FString::Set(const char *pString) {
    
    /*
    Free();
    mLength = Length(pString);
    mData = new char[mLength+1];
    for (int i=0;i<mLength;i++) {
        mData[i] = pString[i];
    }
    mData[mLength] = 0;
    mSize = mLength;
    */
    
    mLength = Length(pString);
	if ((pString != NULL) && (pString != mData)) {
        if (mLength > mSize) {
            
            mSize = mLength;
            delete [] mData;
            mData = new char[mLength + 1];
            
            char *aPaste = mData;
            char *aCopy = (char *)pString;
            if (aCopy != NULL) {
                while (*aCopy) {
                    *aPaste++ = *aCopy++;
                }
            }
            *aPaste = 0;
        } else {
            
            if (mLength == 0) {
                if (mSize > 0) {
                    mData[0] = 0;
                }
            } else {
                char *aPaste = mData;
                char *aCopy = (char *)pString;
                if (aCopy != NULL) {
                    while (*aCopy) {
                        *aPaste++ = *aCopy++;
                    }
                }
                *aPaste = 0;
            }
        }
    } else if (mLength == 0) {
        mLength = 0;
        if (mSize > 0) {
            mData[0] = 0;
        }
    }
    
    
}

void FString::Append(char pChar) {
    if ((mLength + 1) >= mSize) {
        Size(mLength + mLength / 2 + 2);
    }
	mData[mLength] = pChar;
	mLength++;
    mData[mLength] = 0;
}

void FString::Append(const char *pString) {
	int aLength = Length(pString);
	Append(pString, aLength);
}

void FString::Append(FString &pString) {
	Append(pString.mData, pString.mLength);
}

void FString::Append(const char *pString, int pCount) {
	if ((pString != mData) && (pCount > 0)) {
        int aNewLength = mLength + pCount;
        if (aNewLength > mSize) {
            Size(aNewLength + aNewLength / 2 + 1);
        }

		for (int i = 0; i < pCount; i++) {
			mData[i + mLength] = pString[i];
		}

		mLength = aNewLength;
        mData[mLength] = 0;
	}
}


void FString::Set(FString &pString) {
	Set(pString.c());
}

void FString::Truncate(int pSize) {
	if (pSize <= 0) {
        Reset();
	} else if (pSize < mLength) {
		mLength = pSize;
        mData[mLength] = 0;
	}
}

void FString::RemoveBeforeIndex(int pIndex) {
    
    if (pIndex <= 0) {
        
    } else if (pIndex >= mLength) {
        Reset();
        return;
    } else {
        
        for (int i=pIndex;i<mLength;i++) {
            mData[i - pIndex] = mData[i];
        }
        int aNewLen = mLength - pIndex;
        mData[aNewLen] = 0;
        mLength = aNewLen;
    }
    
    
    
}


char *FString::GetCharArray() {
    int aLength = mLength;
    if (aLength < 0) { aLength = 0; }
    char *aResult = new char[aLength + 1];
    for (int i=0;i<mLength;i++) {
        aResult[i] = mData[i];
    }
    aResult[mLength] = 0;
    return aResult;
}

/*
void FString::Ins(const char *pString, int pLength, int pSlot)
{
	if(pSlot < 0)
	{
		int aShift = (-pSlot);

		pString = &(pString[aShift]);
		pLength -= aShift;
		pSlot = 0;
	}

	if(pSlot > mLength)
	{
		pSlot = mLength;
	}

	if ((pLength > 0) && (pSlot >= 0)) {
        int aNewLength = pSlot + pLength;
        if(aNewLength > mSize)Size(aNewLength + aNewLength / 2 + 1);
		for(int i = 0; i < pLength; i++) {
			mData[i + pSlot] = pString[i];
		}

		if (aNewLength > mLength) {
			mLength = aNewLength;
			mData[mLength] = 0;
		}
	}
}
*/

void FString::Insert(char pChar, int pCount, int pSlot) {
    
    if (pSlot < 0) {
        pCount += pSlot;
    }
    
	if (pCount > 0) {
        
        if (pSlot < 0) { pSlot = 0; }
        if (pSlot > mLength) { pSlot = mLength; }
        
        int aNewLength = mLength + pCount;
        if (aNewLength > mSize) {
            Size(aNewLength + aNewLength / 2 + 1);
        }
        
        for (int i = mLength + (pCount - 1);i>pSlot;i--) {
            mData[i] = mData[i-pCount];
        }
        
        int aIndex = pSlot;
        int aCount = pCount;
        while (aCount > 0) {
            mData[aIndex] = pChar;
            aIndex++;
            --aCount;
        }
        mLength = aNewLength;
        mData[mLength] = 0;
	}
}

void FString::Insert(char pChar, int pSlot) {
    
    if (pSlot < 0) { pSlot = 0; }
    if (pSlot > mLength) { pSlot = mLength; }
    
    int aNewLength = mLength + 1;
    if (aNewLength > mSize) {
        Size(aNewLength + aNewLength / 2 + 1);
    }
    
    for (int i=mLength;i>pSlot;i--) {
        mData[i] = mData[i-1];
    }
    mData[pSlot] = pChar;
    mLength = aNewLength;
    mData[mLength] = 0;
}

FString FString::GetLastNumber()
{
    FString aResult = "";
    
    FString aNumberString = GetNumber();
    
    while(aNumberString.mLength > 0)
    {
        aResult = aNumberString;
        aNumberString = GetNextNumber();
    }
    
    
    return aResult;
}


void FString::ToPoint(float &theX, float &theY)
{
	theX=0;
	theY=0;

	if (mData) {
		char *aPtr = mData;
		while(*aPtr && !(*aPtr == '.' || *aPtr == '-' || (*aPtr >= '0' && *aPtr <= '9')))aPtr++;
		char *aXStart=aPtr;
		if(*aPtr == '-')aPtr++;
		while(*aPtr && (*aPtr == '.' || (*aPtr >= '0' && *aPtr <= '9')))aPtr++;
		int aXLength = (int)(aPtr - aXStart);
		while(*aPtr && !(*aPtr == '.' || *aPtr == '-' || (*aPtr >= '0' && *aPtr <= '9')))aPtr++;
		char *aYStart=aPtr;
		if(*aPtr == '-')aPtr++;
		while(*aPtr && (*aPtr == '.' || (*aPtr >= '0' && *aPtr <= '9')))aPtr++;
		int aYLength = (int)(aPtr - aYStart);
		if (aXLength > 0 && aYLength > 0) {
			
			char *aX = new char[aXLength + 1];
			char *aY = new char[aYLength + 1];
			
			aX[aXLength]=0;
			aY[aYLength]=0;
			
			memcpy(aX, aXStart, aXLength);
			memcpy(aY, aYStart, aYLength);
			
			theX = (float)atof(aX);
			theY = (float)atof(aY);
			
			delete [] aX;
			delete [] aY;
		}
	}
}

/*
FString FString::RemovePath(bool pRemoveExtension)
{
	int aStartIndex=0;
	int aEndIndex=mLength;
	
	if(mLength > 0)
	{
		for(int i=mLength-1;i>=0;i--)
		{
			if(mData[i]=='\\' || mData[i]=='/')
			{
				aStartIndex=i+1;
				break;
			}
		}
		if(pRemoveExtension)
		{
			for(int i=mLength-1;i>=aStartIndex;i--)
			{
				if(mData[i] == '.')
				{
					aEndIndex=i-1;
                    break;
				}
			}
		}
	}
    
    FString aResult = GetSubString(aStartIndex, aEndIndex-aStartIndex+1);
    
    *this = GetSubString(aStartIndex, aEndIndex-aStartIndex+1);
    
    return aResult;
}
*/

FString FString::GetExtension()
{
    FString aResult;
    
    int aIndex = GetExtensionIndex();
    
    if((aIndex >= 0) && (aIndex < mLength))
    {
        aIndex++;
        aResult = GetSubString(aIndex, (mLength - aIndex));
        //Delete(aIndex);
        //Truncate(aIndex);
    }
    
    return aResult;
}

FString FString::ChopExtension()
{
    FString aResult;
    
    int aIndex = GetExtensionIndex();
    
    if((aIndex >= 0) && (aIndex < mLength))
    {
        aIndex++;
        aResult = GetSubString(aIndex, (mLength - aIndex));
        Delete(aIndex);
    }
    
    return aResult;
}

void FString::RemovePath() {
    RemoveBeforeIndex(GetPathIndex());
}

void FString::RemoveExtension() {
    int aIndex = GetExtensionIndex();
    if ((aIndex >= 0) && (aIndex < mLength)) {
		Delete(aIndex);
    }
}

void FString::RemovePathAndExtension()
{
    
    RemovePath();
    RemoveExtension();
    
    /*
    int aExtensionIndex = GetExtensionIndex() - 1;
    int aPathIndex = GetPathIndex();
    
    if((aExtensionIndex >= 0) && (aExtensionIndex < mLength))
    {
        if((aPathIndex >= 0) && (aPathIndex < mLength))
        {
            *this = GetSubString(aPathIndex, (aExtensionIndex - aPathIndex) + 1);
        }
        else
        {
            Delete(aExtensionIndex);
        }
    }
    else if((aPathIndex >= 0) && (aPathIndex < mLength))
    {
        *this = GetSubString(aPathIndex, (mLength - aPathIndex));
    }
    */
}

void FString::RemoveLastNumber() {
    if (mLength > 0) {
        int aNumberIndex = mLength - 1;
        
        while(aNumberIndex >= 0)
        {
            char aChar = mData[aNumberIndex];
            
            if((aChar >= '0') && (aChar <= '9'))
            {
                aNumberIndex--;
            }
            else
            {
                break;
            }
        }
        
        if(aNumberIndex < (mLength - 1))
        {
            Delete(aNumberIndex + 1);
        }
    }
}

int FString::GetExtensionIndex() {
    int aResult = -1;
    bool aFail = false;
    for (int aIndex=mLength-1;((aIndex>=0) && (aFail == false) && (aResult == -1));aIndex--) {
        if(mData[aIndex] == '/')aFail = true;
        if(mData[aIndex] == '\\')aFail = true;
        if(mData[aIndex] == '.')aResult = aIndex;
    }
    return aResult;
}

int FString::GetPathIndex() {
    int aResult = -1;
    for (int aIndex = mLength-1;((aIndex>=0) && (aResult == -1));aIndex--) {
        if(mData[aIndex] == '/')aResult = aIndex;
        if(mData[aIndex] == '\\')aResult = aIndex;
    }
    
    return (aResult + 1);
}

void FString::Encrypt(char *theKey)
{
	if(!theKey || !mData)return;
	char *aTraverseData = mData;
	char *aShelf = &mData[mLength];
	char *aTraverseKey = theKey;
	while(aTraverseData < aShelf)
	{
		if(*aTraverseKey==0)aTraverseKey=theKey;
		if(*aTraverseData != *aTraverseKey)*aTraverseData ^= *aTraverseKey;
		aTraverseData++;
		aTraverseKey++;
	}
}

void FString::Decrypt(char *theKey)
{
	if(!theKey || !mData)return;
	char *aTraverseData = mData;
	char *aShelf = &mData[mLength];
	char *aTraverseKey = theKey;
	while(aTraverseData < aShelf)
	{
		if(*aTraverseKey==0)aTraverseKey=theKey;
		if(*aTraverseData != *aTraverseKey)*aTraverseData ^= *aTraverseKey;
		aTraverseData++;
		aTraverseKey++;
	}
}

bool FString::IsNumber()
{
	if(!mData)return false;
	char *aChar = mData;
	bool aResult = false;
	if(*aChar == '-' || *aChar == '+')aChar++;
	if(*aChar >= '0' && *aChar <= '9')
	{
		aResult=true;
		while(*aChar >= '0' && *aChar <= '9')aChar++;
	}
	if(*aChar == '.')aChar++;
	if(*aChar >= '0' && *aChar <= '9')
	{
		aResult=true;
		while(*aChar >= '0' && *aChar <= '9')aChar++;
	}
	aResult &= *aChar == 0;
	return aResult;
}

int FString::CountCharacter(char c)
{
	int aResult=0;
	char *aStart = mData;
	char *aEnd = &mData[mLength];
	while(aStart < aEnd){if(*aStart++==c)aResult++;}
	return aResult;
}

bool FString::ContainsDuplicateCharacters()
{
	for(int i=0;i<256;i++)
	{
		if(CountCharacter((char)i)>1)return true;
	}
	return false;
}


void FString::Reverse()
{
	if(mLength > 1)
	{
		//PrepForInlineModification();
		char *aStart = mData;
		char *aEnd = &mData[mLength-1];
		char *aHalf = &mData[mLength / 2];
		char aTemp;
		while(aStart < aHalf)
		{
			aTemp = *aStart;
			*aStart = *aEnd;
			*aEnd = aTemp;
			aStart++;
			aEnd--;
		}
	}
}

void FString::Remove(char *theDisallowed)
{
	if(!theDisallowed || mLength <= 0)return;

	char *aNew = new char[mLength+1];
	char *aStamp = aNew;
	char *aChar = mData;
	char *aTraverse;
	while(*aChar)
	{
		aTraverse = theDisallowed;
		*aStamp = *aChar;
		aStamp++;
		while(*aTraverse)
		{
			if(*aTraverse == *aChar)
			{
				aStamp--;
				break;
			}
			aTraverse++;
		}
		aChar++;
	}
	*aStamp=0;
	Free();
	mLength = (int)(aStamp - aNew);
	mData = aNew;
	mSize = mLength;
	//mRefs = new int;*mRefs=1;
}

void FString::Filter(char *theAllowed)
{
	if(!theAllowed || mLength == 0)
	{
		Free();
		return;
	}
	char *aNew = new char[mLength+1];
	char *aStamp = aNew;
	char *aChar = mData;
	char *aTraverse;
	while(*aChar)
	{
		aTraverse = theAllowed;
		while(*aTraverse)
		{
			if(*aTraverse == *aChar)
			{
				*aStamp = *aTraverse;
				aStamp++;
				break;
			}
			aTraverse++;
		}
		aChar++;
	}
	*aStamp=0;
	Free();
	mLength = (int)(aStamp - aNew);
	mSize = mLength;
	mData = aNew;
	//mRefs = new int;*mRefs=1;
}

void FString::Delete(char *pString)
{
    Replace(pString, (char *)"");
}

void FString::Delete(int thePosition, int theLength)
{
    if (thePosition < 0) {
        theLength += thePosition;
        thePosition = 0;
    }
    
    int aEndIndex = thePosition + theLength;
    if (aEndIndex > mLength) {
        theLength -= (aEndIndex - mLength);
    }
    
    if (theLength > 0) {
        
        for (int i=0;i<theLength;i++) {
            mData[i + thePosition] = mData[i + thePosition + theLength];
        }
        mLength -= theLength;
        mData[mLength] = 0;
    }
    


	/*
	int aFinish = thePosition + theLength;
	if(aFinish > mLength)aFinish = mLength;
	if(thePosition < 0)thePosition=0;
	theLength=aFinish-thePosition;
	if(thePosition >= mLength || mLength == 0 || theLength < 1)return;
	int aNewLength = thePosition + (mLength - (thePosition + theLength));
	char *aChar = new char[aNewLength + 1];
	aChar[aNewLength]=0;
	Stamp(aChar, mData, 0, thePosition);
	Stamp(aChar, &mData[thePosition + theLength], thePosition, (mLength - (thePosition + theLength)));
	Free();
	mData = aChar;
	//mRefs = new int;*mRefs=1;
	mLength = aNewLength;
	*/

}

void FString::Delete(int thePosition) {
	Truncate(thePosition);
}

FString FString::GetSubString(int thePosition, int theLength)
{
    /*
	int aStartIndex = thePosition;
	int aEndIndex = thePosition + theLength;

	if(aStartIndex < 0)aStartIndex = 0;
	if(aEndIndex > mLength)aEndIndex = mLength;

	int aLength = (aEndIndex - aStartIndex);

	FString aResult;

	if ((aStartIndex < mLength) && (mLength > 0) && (aLength > 0))
	{
		aResult.Size(aLength);
		int aPaste = 0;

		while (aStartIndex < aEndIndex)
		{
			aResult.mData[aPaste] = mData[aStartIndex];
			aStartIndex++;
			aPaste++;
		}
		aResult.mData[aPaste] = 0;
		aResult.mLength = aPaste;
	}
	return aResult;
    */
    
    
    int aStartIndex = thePosition;
    int aCeiling = thePosition + theLength;
    
    if (aStartIndex < 0) { aStartIndex = 0; }
    if (aCeiling > mLength) { aCeiling = mLength; };
    
    int aLength = (aCeiling - aStartIndex);
    
    FString aResult;
    
    if ((aStartIndex < mLength) && (mLength > 0) && (aLength > 0)) {
        aResult.Size(aLength);
        int aPaste = 0;
        while (aStartIndex < aCeiling) {
            aResult.mData[aPaste] = mData[aStartIndex];
            aStartIndex++;
            aPaste++;
        }
        aResult.mData[aPaste] = 0;
        aResult.mLength = aPaste;
    }
    return aResult;
    
}

void FString::RemoveLeadingSpaces()
{
	int aCount = 0;

	for(int i = 0; i < mLength; i++)
	{
		if(mData[i] > 32)
		{
			aCount = i;
			break;
		}
	}

	if(aCount > 0)
	{
		for(int i = mLength - 1;i >= aCount;i--)mData[i - aCount] = mData[i];

		mLength -= aCount;
		mData[mLength] = 0;

		for(int i = mLength + 1; i < mSize; i++)mData[i] = 0;
	}
}

void FString::RemoveTrailingSpaces()
{
	int aIndex = -1;

	if(mLength > 0)
	{
		for(int i = mLength - 1; i >= 0; i--)
		{
			if(mData[i] > 32)
			{
				aIndex = i;
				break;
			}
		}
		if(aIndex != -1)
		{
			mLength = aIndex + 1;
			mData[mLength] = 0;
			for(int i = mLength + 1; i < mSize; i++)mData[i] = 0;
		}
	}
}

FString FString::operator+(FString pString)
{
	FString aResult;
    
    int aNewLength = mLength + pString.mLength;
	aResult.Size(aNewLength);

    char *aPaste = aResult.mData;
    char *aCopy = mData;
    
    if (aCopy != NULL) {
        while (*aCopy) {
            *aPaste++ = *aCopy++;
        }
    }
    
    aCopy = pString.mData;
    if (aCopy != NULL) {
        while (*aCopy) {
            *aPaste++ = *aCopy++;
        }
    }
    
    *aPaste = 0;
    
	//for(int i = 0; i < mLength; i++)aResult.mData[i] = mData[i];
    //int aCap = pString.mLength + mLength;
	//for(int i = 0; i < pString.mLength; i++)aResult.mData[i + mLength] = pString.mData[i];
    
    aResult.mLength = aNewLength;
    
	return aResult;
}

FString FString::operator+(const char *pString) {
	return *this + FString(pString);
}

FString FString::operator+(char *pString) {
	return *this + FString(pString);
}

FString FString::operator+(char pChar) {
	return *this + FString(pChar);
}



int FString::Compare(FString &pString) {
	int aResult = 0;
	int aLoops = mLength;
	if(pString.mLength < aLoops)aLoops = pString.mLength;

	char aC1 = 0;
	char aC2 = 0;

	int aIndex = 0;
	while (aIndex < aLoops) {
		aC1 = mData[aIndex];// lower();
		aC2 = pString.mData[aIndex];// lower();
		if(aC1 != aC2)break;
		aIndex++;
	}

	if (aIndex < aLoops) {
		if(aC1 < aC2)return -1;
		if(aC1 > aC2)return 1;
	} else {
        if (mLength < pString.mLength) { aResult = -1; }
        if (mLength > pString.mLength) { aResult = 1; }
	}
	return aResult;
}

int FString::CompareI(FString &pString) {
	int aResult = 0;
	int aLoops = mLength;
    if (pString.mLength < aLoops) {
        aLoops = pString.mLength;
    }

	char aC1 = 0;
	char aC2 = 0;

	int aIndex = 0;
	while (aIndex < aLoops)
	{
		aC1 = lower(mData[aIndex]);
		aC2 = lower(pString.mData[aIndex]);

		if(aC1 != aC2)
		{
			break;

		}
		aIndex++;
	}

	if(aIndex < aLoops)
	{
		if(aC1 < aC2)return -1;
		if(aC1 > aC2)return 1;
	}
	else
	{
		if(mLength < pString.mLength)aResult = -1;
		if(mLength > pString.mLength)aResult = 1;
	}
	return aResult;
}

/*

int FString::CompareI(char *pString)
{
	if(theCount<=0)return 0;
	if(!mData){if(pString)return -1;return 0;}if(!pString)return 1;
	char *aChar = mData;
	while(lower(*aChar)==lower(*pString)&&*aChar&&theCount)
	{
		aChar++;
		pString++;
		theCount--;
	}
	if(theCount)
	{
		if(*aChar>*pString)return 1;
		if(*aChar<*pString)return -1;
	}
	return 0;
}

int FString::CompareS(char *pString, int theCount)
{
	if(theCount<=0)return 0;
	if(!mData){if(pString)return -1;return 0;}if(!pString)return 1;
	char *aChar = mData;
	while(*aChar==*pString&&*aChar&&theCount)
	{
		aChar++;
		pString++;
		theCount--;
	}
	if(theCount)
	{
		if(*aChar>*pString)return 1;
		if(*aChar<*pString)return -1;
	}
	return 0;
}
*/


void FString::Split(char pSplitter, FList *pResult) {
    
    if (pResult == NULL) { return; }
    if ((mLength <= 0)) { return; }
    
    int aStartIndex = 0;
    while ((aStartIndex < mLength) && (mData[aStartIndex] == pSplitter)) { aStartIndex++; }
    
    int aIndex = aStartIndex;
    int aLength = 0;
    
    while (aIndex < mLength) {
        
        while ((aIndex < mLength) && (mData[aIndex] != pSplitter)) { ++aIndex; }
        
        aLength = (aIndex - aStartIndex);
        
        FString *aChunk = new FString();
        aChunk->Size(aLength + 1);
        memcpy(aChunk->mData, &(mData[aStartIndex]), aLength);
        aChunk->mData[aLength] = NULL;
        pResult->Add(aChunk);

        while ((aIndex < mLength) && (mData[aIndex] == pSplitter)) { ++aIndex; }
        aStartIndex = aIndex;
    }
    
    
    
}



bool FString::StartsWith(char *pString)
{
	if(!mData)return false;
	if(!pString)return true;
	
	char *aChar = mData;
	
	while(*aChar==*pString&&*aChar)
	{
		aChar++;
		pString++;
	}
	
	if(*pString==0)return true;
	return false;
}

bool FString::StartsWithI(char *pString)
{
	if(!mData)return false;
	if(!pString)return true;
	
	char *aChar = mData;
	
	while(lower(*aChar)==lower(*pString)&&*aChar)
	{
		aChar++;
		pString++;
	}
	
	if(*pString==0)return true;
	return false;
}


bool FString::EndsWith(char *pString)
{
    bool aResult = true;
    int aLength = Length(pString);
    if((aLength > 0) && (aLength <= mLength))
    {
        char *aChar = &mData[mLength - aLength];
        while(*aChar == *pString && *aChar)
        {
            aChar++;
            pString++;
        }
        
        if(*pString!=0)aResult = false;
    }
    return aResult;
}

bool FString::EndsWithI(char *pString)
{
    bool aResult = true;
    int aLength = Length(pString);
    if((aLength > 0) && (aLength <= mLength))
    {
        char *aChar = &mData[mLength - aLength];
        while(lower(*aChar)==lower(*pString)&&*aChar)
        {
            aChar++;
            pString++;
        }
        if(*pString!=0)aResult = false;
    }
    return aResult;
}

void FString::SetChar(int theIndex, char theChar)
{
	if(theIndex >= 0 && theIndex < mLength)
	{
		mData[theIndex] = theChar;
		if(theChar == 0)mLength = theIndex;
	}
}


int FString::FindReverse(char pChar, int pPosition)
{
    int aResult = -1;
    
    if((pPosition >= 0) && (pPosition < mLength))
    {
        for(int i=pPosition;((i>=0) && (aResult == -1));i--)
        {
            if(mData[i] == pChar)
            {
                aResult = i;
            }
        }
    }
    
    return aResult;
}

int FString::FindReverse(char pChar)
{
    return FindReverse(pChar, mLength - 1);
}


int FString::FindI(char theChar, int thePosition)
{
	if(thePosition >= mLength || thePosition < 0)return -1;
	if(theChar >= 'A' && theChar <= 'Z')theChar+=32;
	char *aFinal = &mData[mLength];
	char *aChar = &mData[thePosition];
	while(aChar < aFinal)
	{
		char aCompare = *aChar;
		if(aCompare >= 'A' && aCompare <= 'Z')aCompare+=32;
		if(aCompare == theChar)return (int)(aChar - mData);
		aChar++;
	}
	return -1;
}

int FString::Find(char theRangeLow, char theRangeHigh, int thePosition)
{
	if(thePosition >= mLength || thePosition < 0)return -1;
	char *aFinal = &mData[mLength];
	char *aChar = &mData[thePosition];
	while(aChar < aFinal)
	{
		if(*aChar >= theRangeLow && *aChar <= theRangeHigh)return (int)(aChar - mData);
		aChar++;
	}
	return -1;
}

int FString::Find(char theChar, int thePosition)
{
	if(thePosition >= mLength || thePosition < 0)return -1;
	char *aFinal = &mData[mLength];
	char *aChar = &mData[thePosition];
	while(aChar < aFinal)
	{
		if(*aChar == theChar)return (int)(aChar - mData);
		aChar++;
	}
	return -1;
}

int FString::Find(char *pString, int thePosition)
{
	if(!pString || thePosition >= mLength || thePosition < 0)return -1;
	char *aChar = &mData[thePosition];
	char *aFinish = &mData[mLength];
	while(aChar<aFinish)
	{
		if(*aChar == *pString)
		{
			char *aChar2 = aChar;
			char *aString2 = pString;
			while(aChar2 <= aFinish)
			{
				if(*aString2 == 0)return (int)(aChar - mData);
				if(*aString2 != *aChar2)break;
				aString2++;
				aChar2++;
			}
		}
		aChar++;
	}
	return -1;
}

int FString::ToInt() {
    if (mData != NULL) {
        return (int)atoi(mData);
    }
    return 0;
}


char FString::ToChar() {
    if (mData != NULL) {
        return (char)atoi(mData);
    }
    return 0;
}

float FString::ToFloat() {
    if (mData != NULL) {
        return (float)atof(mData);
    }
    return 0;
}

bool FString::ToBool() {
    if(CompareI("true") == 0)return true;
    if(CompareI("yes") == 0)return true;
    if(CompareI("1") == 0)return true;
    return false;
}

int FString::FindI(char *pString, int thePosition) {
	if(!pString || thePosition >= mLength || thePosition < 0)return -1;
	char *aChar = &mData[thePosition];
	char *aFinish = &mData[mLength];
	char aC1, aC2;
	while (aChar < aFinish) {
		aC1 = *aChar;
		aC2 = *pString;
		if (aC1 >= 'A' && aC1 <= 'Z')aC1+=32;
		if (aC2 >= 'A' && aC2 <= 'Z')aC2+=32;
		if (aC1 == aC2) {
			char *aChar2 = aChar;
			char *aString2 = pString;
			while (aChar2 <= aFinish) {
                if (*aString2 == 0) { return (int)(aChar - mData); }
				aC1 = *aString2;
				aC2 = *aChar2;
				if (aC1 >= 'A' && aC1 <= 'Z')aC1+=32;
				if (aC2 >= 'A' && aC2 <= 'Z')aC2+=32;
				if (aC1 != aC2)break;
				aString2++;
				aChar2++;
			}
		}
		aChar++;
	}
	return -1;
}

/*
int FString::GetHash(char *pString, int theCount, int theTableSize)//, int &theLength)
{
	if(!pString || theTableSize < 1)return 0;
	unsigned long aResult = 5381;
	char *aString=pString;
	while(int aChar = *aString++ != 0 && theCount--)aResult=((aResult<< 5)+aResult)^aChar;
	//theLength = (int)(aString - pString);
	return aResult % theTableSize;
}

int FString::GetHashI(char *pString, int theCount, int theTableSize)//, int &theLength)
{
	if(!pString || theTableSize < 1)return 0;
	unsigned long aResult = 5381;
	char *aString=pString;
	while(int aChar = *aString++ != 0 && theCount--)
	{
		if(aChar >= 'A' && aChar <= 'Z')aChar+=32;
		aResult=((aResult<< 5)+aResult)^aChar;
	}
	//theLength = (int)(aString - pString);
	return aResult % theTableSize;
}

int FString::GetHash(char *pString, int theTableSize)
{
	if(!pString || theTableSize < 1)return 0;
	unsigned long aResult = 5381;
	char *aString=pString;
	while(int aChar = *aString++)aResult=((aResult<< 5)+aResult)^aChar;
	return aResult % theTableSize;
}

int FString::GetHashI(char *pString, int theTableSize)
{
	if(!pString || theTableSize < 1)return 0;
	unsigned long aResult = 5381;
	char *aString=pString;
	while(int aChar = *aString++)
	{
		if(aChar >= 'A' && aChar <= 'Z')aChar+=32;
		aResult=((aResult<< 5)+aResult)^aChar;
	}
	return aResult % theTableSize;
}

int FString::GetHash(int theTableSize)
{
	if(!mData || theTableSize < 1)return 0;
	unsigned long aResult = 5381;
	char *aString = mData;
	while (int aChar = *aString++)aResult = ((aResult << 5) + aResult) ^ aChar;
	return aResult % theTableSize;
}

int FString::GetHashI(int theTableSize)
{
	if(!mData || theTableSize < 1)return 0;
	unsigned long aResult = 5381;
	char *aString=mData;
	while(int aChar = *aString++)
	{
		if(aChar >= 'A' && aChar <= 'Z')aChar+=32;
		aResult=((aResult<< 5)+aResult)^aChar;
	}
	return aResult % theTableSize;
}
*/

unsigned int FString::GetHash()
{
	return GetHash(mData);
}

unsigned int FString::GetHashI()
{
	return GetHashI(mData);
}

unsigned int FString::GetHash(char *pString)
{
	unsigned long aResult = 0;

	if(pString)
	{
		if(*pString)
		{
			aResult = 5381;
			char *aString = pString;
			while (int aChar = *aString++)aResult = ((aResult << 5) + aResult) ^ aChar;
		}
	}

	return (unsigned int)aResult;
}

unsigned int FString::GetHashI(char *pString)
{
	unsigned long aResult = 0;

	if(pString)
	{
		if(*pString)
		{
			aResult = 5381;
			char *aString = pString;
			while (int aChar = *aString++)
			{
				if(aChar >= 'A' && aChar <= 'Z')aChar += 32;
				aResult = ((aResult << 5) + aResult) ^ aChar;
			}
		}
	}

	return (unsigned int)aResult;
}

void FString::Replace(char theOriginal, char theNew)
{
	if(mLength == 0)return;
	int aFind = Find(theOriginal);
	if(aFind != -1)
	{
		//PrepForInlineModification();
		char *aChar = &mData[aFind];
		while(*aChar)
		{
			if(*aChar == theOriginal)*aChar=theNew;
			aChar++;
		}
	}
}

void FString::Replace(char *theOriginal, char *theNew)
{
    
	if(mLength == 0 || !theOriginal || !theNew)return;
	
    int aFindFirst = Find(theOriginal);
    
    
	if(aFindFirst != -1)
	{
        int aFind = aFindFirst;
        int aFindPrevious = 0;
        
		int aLengthO = Length(theOriginal);
		int aLengthN = Length(theNew);
		int aDiff = aLengthN - aLengthO;
		
        int aNewLength = mLength;
        int aFindCount = 0;
        
		while(aFind != -1)
		{
			aFind = Find(theOriginal, aFind+aLengthO);
            
			aNewLength += aDiff;
            aFindCount++;
		}
        
        
        char *aChar = new char[aNewLength + 1];
        aChar[aNewLength] = 0;


        char *aOld = mData;
        char *aPaste = aChar;
        char *aCopy = mData;
        char *aGet = 0;
        

        aFindPrevious = 0;
        aFind = aFindFirst;
        
        while(aFind != -1)
		{
            aGet = &(mData[aFind]);
            
            while(aOld < aGet)
            {
                *aPaste=*aOld;
                aPaste++;
                aOld++;
            }
            
            aCopy = theNew;
            while(*aCopy)
            {
                *aPaste=*aCopy;
                aPaste++;
                aCopy++;
            }
            
            aOld+=aLengthO;
            
            aFindPrevious = aFind;
			aFind = Find(theOriginal, aFind+aLengthO);
		}

        aGet = &mData[mLength];
        while(aOld<aGet)
        {
            *aPaste=*aOld;
            aPaste++;
            aOld++;
        }
        
        Clear();
        Set(aChar);
	}
    
}

void FString::Uppercase()
{
	int aFind = Find('a','z');
	if(aFind != -1)
	{
		char *aChar = &mData[aFind];
		char *aFinish = &mData[mLength];
		while(aChar < aFinish)
		{
			if(*aChar >= 'a' && *aChar <= 'z')*aChar -= 32;
			aChar++;
		}
	}
}

void FString::Lowercase()
{
	int aFind = Find('A','Z');
	if(aFind != -1)
	{
		//PrepForInlineModification();
		char *aChar = &mData[aFind];
		char *aFinish = &mData[mLength];
		while(aChar < aFinish)
		{
			if(*aChar >= 'A' && *aChar <= 'Z')*aChar+=32;
			aChar++;
		}
	}
}

void FString::CapitolizeFirstLetter(bool pForceLower)
{
	if(mLength > 0)
	{
		if(mData[0] >= 'a' && mData[0] <= 'z')
		{
			mData[0] -= 32;
		}
		if(pForceLower)
		{
			for(int i = 1; i < mLength; i++)
			{
				if(mData[i] >= 'A' && mData[i] <= 'Z')
				{
					mData[i] += 32;
				}
			}
		}
	}
}


void FString::ParseChar(char *theChar)
{
	Set((const char *)theChar);
}

static char cStringNumberChar[128];
static int cStringNumberInt[128];
void FString::ParseInt(int pNumber) {
    int aWriteLength = 0;
    int aNumberLength = 0;
    if (pNumber < 0) {
        cStringNumberChar[0] = '-';
        aWriteLength = 1;
        pNumber = (-pNumber);
    }
    
    if (pNumber == 0) {
        cStringNumberInt[0] = 0;
        aNumberLength = 1;
    } else {
        while (pNumber != 0) {
            cStringNumberInt[aNumberLength] = (pNumber % 10);
            pNumber = (pNumber / 10);
            aNumberLength++;
        }
    }
    
    while (aNumberLength > 0) {
        --aNumberLength;
        cStringNumberChar[aWriteLength] = ('0' + cStringNumberInt[aNumberLength]);
        aWriteLength++;
    }
    cStringNumberChar[aWriteLength] = 0;
	Set(cStringNumberChar);
}



void FString::ParseFloat(float pFloat, int pDecimalCount) {
    Free();
    
    bool aSign = false;
	if (pFloat < 0.0f) {
        aSign = true;
		pFloat = -pFloat;
    }
    
    // Our logic breaks for "scientific numbers"
    // Which means you probably didn't initialize
    // this float and it's filled with garbo-bits.
    if (pFloat > 100000000.0f) { pFloat = 100000000.0f; }
    
	int aWholeNumber = (int)pFloat;
	double aFraction = pFloat - (float)aWholeNumber;
    int aWholeDigits = 0;
    
    int aMultiply=10;
    int aHold=pDecimalCount;
    while (aHold > 0) {
        aMultiply *= 10;
        aHold--;
    }
    aFraction *= (float)aMultiply;
    int aFractionNumber = (int)aFraction;
    int aLastDigit = ((int)aFractionNumber) % 10;
    aFractionNumber /= 10;
    
    //.567[8] = .568
    if (aLastDigit >= 5) { aFractionNumber++; }
    
    //.9999999[9] = 1
    if (aFractionNumber >= (aMultiply / 10)) {
        aFractionNumber=0;
        aWholeNumber++;
    }
    aHold = aWholeNumber;
    while (aHold) {
        aWholeDigits++;
        aHold /= 10;
    }
    if (aWholeDigits == 0) { aWholeDigits = 1; }
    mLength = aWholeDigits + 1 + pDecimalCount;
    if (aSign) { mLength += 1; }
    //mData = new char[mLength + 1];
    
    
    if (aSign) {
        cStringNumberChar[0] = '-';
        for (int i=aWholeDigits-1;i>=0;i--) {
            cStringNumberChar[i + 1] = ((char)(aWholeNumber % 10)) + '0';
            aWholeNumber/=10;
        }
        aWholeDigits++;
        cStringNumberChar[aWholeDigits]='.';
        for (int i=mLength-1;i>aWholeDigits;i--) {
            cStringNumberChar[i] = ((char)(aFractionNumber % 10)) + '0';
            aFractionNumber/=10;
        }
    } else {
        for (int i=aWholeDigits-1;i>=0;i--) {
            cStringNumberChar[i] = ((char)(aWholeNumber % 10)) + '0';
            aWholeNumber/=10;
        }
        cStringNumberChar[aWholeDigits] = '.';
        for (int i=mLength-1;i>aWholeDigits;i--) {
            cStringNumberChar[i] = ((char)(aFractionNumber % 10)) + '0';
            aFractionNumber/=10;
        }
    }
    
    cStringNumberChar[mLength] = 0;
    Set(cStringNumberChar);
	//mSize = mLength;
}



