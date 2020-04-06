//
//  FSpriteSequence.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/19/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "core_includes.h"
#include "FSpriteSequence.h"
#include "FFileTable.hpp"

FSpriteSequence::FSpriteSequence()
{
    mWidth = 0.0f;
    mHeight = 0.0f;
}

FSpriteSequence::~FSpriteSequence() {
    Kill();
}

void FSpriteSequence::Kill() {
    
    //gSpriteSequenceList.Remove(this);
    EnumList (FSprite, aSprite, mList) {
    //    gSpriteList.Remove(aSprite);
        delete aSprite;
    }
    mList.RemoveAll();
    
    mWidth = 0.0f;
    mHeight = 0.0f;
}

void FSpriteSequence::LoadBundle(const char *pBundleName) {
    //gSpriteListEnabled = false;
    
    mFilePrefix = pBundleName;
    
    gImageBundler.Load(pBundleName);
    
    EnumList(FImageBundlerLoadNode, aNode, gImageBundler.mLoadNodeList) {
        FSprite *aSprite = new FSprite();
        aSprite->LoadNode(&gImageBundler, aNode);
        aSprite->mFileName = aNode->mName;
        mList.Add(aSprite);
    }
    
    //if (mList.mCount > 0) {
    //    if (gSpriteSequenceList.Exists(this) == false) {
    //        gSpriteSequenceList.Add(this);
    //    }
    //}
    //gSpriteListEnabled = true;
    
    ComputeBounds();
}

void FSpriteSequence::Load(const char *pFilePrefix) {
    //gSpriteListEnabled = false;
    
    mFilePrefix = pFilePrefix;
    
    bool aSuccess = false;
    
    FString aFileBase = pFilePrefix;
    //FString aNumberString;
    FString aNumberStringUnpadded;
    FString aNumberStringPadded;
    
    FString aPath;
    FSprite *aSprite = new FSprite();
    aSprite->mAddToSpriteList = false;
    
    int aLoops = 0;
    
    FString aZeroString;
    
    for (int aStartIndex=0;(aStartIndex < 5) && (aSuccess == false);aStartIndex++) {
        aLoops++;
        
        for (int aLeadingZeroes=1;(aLeadingZeroes < 7) && (aSuccess == false);aLeadingZeroes++) {
            aLoops++;
            
            aNumberStringUnpadded.ParseInt(aStartIndex);
            if (aNumberStringUnpadded.mLength < aLeadingZeroes) {
                aZeroString.Reset();
                aZeroString.Insert('0', (aLeadingZeroes - aNumberStringUnpadded.mLength), 0);
                aNumberStringPadded.Reset();
                aNumberStringPadded.Append(aZeroString);
                aNumberStringPadded.Append(aNumberStringUnpadded);
            } else {
                aNumberStringPadded.Set(aNumberStringUnpadded);
            }
            aPath.Reset();
            aPath.Append(aFileBase);
            aPath.Append(aNumberStringPadded);
            
            aSprite->Load(aPath);
            
            if (aSprite->DidLoad()) {
                mList += aSprite;
                aSprite = new FSprite();
                aSprite->mAddToSpriteList = false;
                
                int aIndex = aStartIndex + 1;
                
                while (true) {
                    aLoops++;
                    
                    aNumberStringUnpadded.ParseInt(aIndex);
                    if (aNumberStringUnpadded.mLength < aLeadingZeroes) {
                        aZeroString.Reset();
                        aZeroString.Insert('0', (aLeadingZeroes - aNumberStringUnpadded.mLength), 0);
                        aNumberStringPadded.Reset();
                        aNumberStringPadded.Append(aZeroString);
                        aNumberStringPadded.Append(aNumberStringUnpadded);
                    } else {
                        aNumberStringPadded.Set(aNumberStringUnpadded);
                    }
                    aPath.Reset();
                    aPath.Append(aFileBase);
                    aPath.Append(aNumberStringPadded);
                    
                    
                    aSprite->Load(aPath);
                    
                    if (aSprite->DidLoad()) {
                        mList += aSprite;
                        aSprite = new FSprite();
                        aSprite->mAddToSpriteList = false;
                        
                        aIndex++;
                    } else {
                        break;
                    }
                }
                aSuccess = true;
            }
        }
    }
    
    //if (mList.mCount > 0) {
    //    gSpriteSequenceList.Add(this);
    //}
    
    delete aSprite;
    
    //gSpriteListEnabled = true;
    
    ComputeBounds();
}

void FSpriteSequence::Load(const char *pFilePrefix, int pStartIndex, int pEndIndex) {
    mFilePrefix = pFilePrefix;
    
    //gSpriteListEnabled = false;
    
    bool aSuccess = false;
    
    FString aFileBase = pFilePrefix;
    FString aNumberStringUnpadded;
    FString aNumberStringPadded;
    
    FString aPath;
    FSprite *aSprite = new FSprite();
    aSprite->mAddToSpriteList = false;
    
    FString aZeroString;
    //int aLoops = 0;
    //for (int aStartIndex=pStartIndex;aStartIndex <= pEndIndex;aStartIndex++) {
    
        for (int aLeadingZeroes=1;(aLeadingZeroes < 7)&&(aSuccess == false);aLeadingZeroes++) {
            
            aNumberStringUnpadded.ParseInt(pStartIndex);
            if (aNumberStringUnpadded.mLength < aLeadingZeroes) {
                aZeroString.Reset();
                aZeroString.Insert('0', (aLeadingZeroes - aNumberStringUnpadded.mLength), 0);
                aNumberStringPadded.Reset();
                aNumberStringPadded.Append(aZeroString);
                aNumberStringPadded.Append(aNumberStringUnpadded);
            } else {
                aNumberStringPadded.Set(aNumberStringUnpadded);
            }
            aPath.Reset();
            aPath.Append(aFileBase);
            aPath.Append(aNumberStringPadded);
            
            aSprite->Load(aPath);
            if (aSprite->DidLoad()) {
                //printf("Loaded First: [%s]\n", aSprite->mFileName.c());
                
                mList += aSprite;
                aSprite = new FSprite();
                aSprite->mAddToSpriteList = false;
                int aIndex = pStartIndex + 1;
                while (aIndex <= pEndIndex) {
                    
                    aNumberStringUnpadded.ParseInt(aIndex);
                    if (aNumberStringUnpadded.mLength < aLeadingZeroes) {
                        aZeroString.Reset();
                        aZeroString.Insert('0', (aLeadingZeroes - aNumberStringUnpadded.mLength), 0);
                        aNumberStringPadded.Reset();
                        aNumberStringPadded.Append(aZeroString);
                        aNumberStringPadded.Append(aNumberStringUnpadded);
                    } else {
                        aNumberStringPadded.Set(aNumberStringUnpadded);
                    }
                    
                    aPath.Reset();
                    aPath.Append(aFileBase);
                    aPath.Append(aNumberStringPadded);
                    
                    aSprite->Load(aPath);
                    if (aSprite->DidLoad()) {
                        //printf("Loaded Next: [%s]\n", aSprite->mFileName.c());
                        
                        mList += aSprite;
                        aSprite = new FSprite();
                        aSprite->mAddToSpriteList = false;
                        aIndex++;
                    } else {
                        break;
                    }
                }
                aSuccess = true;
            }
        }
    //}
    
    //if (mList.mCount > 0) {
    //    if (gSpriteSequenceList.Exists(this) == false) {
    //        gSpriteSequenceList.Add(this);
    //    }
    //}
    
    delete aSprite;
    //gSpriteListEnabled = true;
    ComputeBounds();
}

void FSpriteSequence::ComputeBounds() {
    if(mList.mCount > 0) {
        FSprite *aFirstSprite = (FSprite *)(mList.Fetch(0));
        if (aFirstSprite) {
            mWidth = aFirstSprite->mWidth;
            mHeight = aFirstSprite->mHeight;
        }

        EnumList(FSprite, aSprite, mList) {
            if (aSprite->mWidth > mWidth) {
                mWidth = aSprite->mWidth;
            }
            if (aSprite->mHeight > mHeight) {
                mHeight = aSprite->mHeight;
            }
        }
    }
}


float FSpriteSequence::GetMaxFrame() {
    return (float)(mList.mCount);
}


float FSpriteSequence::LoopFrame(float pFrame, float pFrameSpeed)
{
    float aResult = pFrame;
    
    if(mList.mCount <= 0)
    {
        aResult = 0.0f;
    }
    else
    {
        aResult += pFrameSpeed;
        
        if(aResult < 0.0f)aResult += GetMaxFrame();
        if(aResult >= GetMaxFrame())aResult -= GetMaxFrame();
    }
    
    return aResult;
}

void FSpriteSequence::Draw(float pFrame)
{
    FSprite *aSprite = GetSprite(pFrame);
    if(aSprite)aSprite->Draw();
}

void FSpriteSequence::Draw(float pFrame, float pX, float pY)
{
    FSprite *aSprite = GetSprite(pFrame);
    if(aSprite)aSprite->Draw(pX, pY);
}

void FSpriteSequence::DrawScaled(float pFrame, float pX, float pY, float pScale)
{
    FSprite *aSprite = GetSprite(pFrame);
    if(aSprite)aSprite->DrawScaled(pX, pY, pScale);
}


void FSpriteSequence::DrawScaled(float pFrame, float pX, float pY, float pScaleX, float pScaleY)
{
    FSprite *aSprite = GetSprite(pFrame);
    if(aSprite)aSprite->DrawScaled(pX, pY, pScaleX, pScaleY);
}

void FSpriteSequence::DrawScaled(float pFrame, float pX, float pY, float pScaleX, float pScaleY, float pRotation)
{
    FSprite *aSprite = GetSprite(pFrame);
    if(aSprite)aSprite->DrawScaled(pX, pY, pScaleX, pScaleY, pRotation);
}

void FSpriteSequence::DrawRotated(float pFrame, float pX, float pY, float pRotation)
{
    FSprite *aSprite = GetSprite(pFrame);
    if(aSprite)aSprite->DrawRotated(pX, pY, pRotation);
}

void FSpriteSequence::Draw(float pFrame, float pX, float pY, float pScale, float pRotation)
{
    FSprite *aSprite = GetSprite(pFrame);
    if(aSprite)aSprite->Draw(pX, pY, pScale, pRotation);
}

void FSpriteSequence::Center(float pFrame, float pX, float pY)
{
    FSprite *aSprite = GetSprite(pFrame);
    if(aSprite)aSprite->Center(pX, pY);
}

FSprite *FSpriteSequence::Get()
{
    return Get(0);
}

FSprite *FSpriteSequence::Get(int pIndex)
{
    return (FSprite *)(mList.Fetch(pIndex));
}

FSprite *FSpriteSequence::GetRandom()
{
    return Get(gRand.Get(mList.mCount));
}

FSprite *FSpriteSequence::GetSprite(float pFrame)
{
    FSprite *aResult = 0;
    
    int aIndex = (int)(pFrame + 0.01f);
    
    if(mList.mCount > 0)
    {
        if(aIndex < 0)aIndex = 0;
        if(aIndex >= mList.mCount)aIndex = (mList.mCount - 1);
        
        aResult = (FSprite *)(mList.mData[aIndex]);
    }
    
    return aResult;
}

/*
void FSpriteSequence::FindAllFileSequences(FList &pFileList, FList &pSearchBucketList) {
    FList aNodeList;
    FList aBucketList;
    FSpriteSequenceSearchBucket *aBucket = 0;
    FFileTable aHashTable;
    EnumList(FString, aString, pFileList)
    {
        FString aName = FString(aString->c());
        aName.RemovePathAndExtension();
        
        Log("Name = [%s]\n", aName.c());
        
        FString aNumberString = aName.GetLastNumber();
        
        if(aNumberString.mLength > 0)
        {
            aName.Remove(aNumberString.c());
            
            Log("File[%s] (%s)\n", aName.c(), aNumberString.c());
            
            FSpriteSequenceSearchNode *aNode = new FSpriteSequenceSearchNode(aString->c(), aName.c(), aNumberString.ToInt());
            
            
            //aNode->mFilePath = FString(aString->c());
            //aNode->mIndex = aNumberString.ToInt();
            
            
            aBucket = ((FSpriteSequenceSearchBucket *)aHashTable.Get(aName.c()));
            
            if(aBucket)
            {
                
            }
            else
            {
                aBucket = new FSpriteSequenceSearchBucket();
                aHashTable.Add(aName.c(), aBucket);
                aBucket->mName = aName.c();
                
                aBucketList.Add(aBucket);
                
            }
            
            aBucket->AddNode(aNode);
            
        }
    }
    
    EnumList(FSpriteSequenceSearchBucket, aCheckBucket, aBucketList)
    {
        Log("Final Bucket [%s]  (%d)  (%d - %d)\n", aCheckBucket->mName.c(), aCheckBucket->mCount, aCheckBucket->mStartIndex, aCheckBucket->mEndIndex);
        
        if(aCheckBucket->mCount > 3)
        {
            aCheckBucket->Finalize();
            pSearchBucketList.Add(aCheckBucket);
        }
        
        
        //aCheckBucket->
    }
    
}
 */

/*
void FSpriteSequence::PrintAllFileSequences(FList &pFileList)
{

    
    FList aBucketList;
    
    FindAllFileSequences(pFileList, aBucketList);
    
    gImageBundler.mAutoBundle = true;

	int aSkip = 20;

	FList aNameList;

    EnumList(FSpriteSequenceSearchBucket, aCheckBucket, aBucketList)
    {
		if(aSkip > 0)
		{
			aSkip--;
		}
		else
		{
			gImageBundler.StartBundle(aCheckBucket->mName.c());


			for(int i = 0; i < aCheckBucket->mNodeList.mCount; i++)
			{
				FSpriteSequenceSearchNode *aNode = (FSpriteSequenceSearchNode *)(aCheckBucket->mNodeList.Fetch(i));

				if (aNode) {
                    gImageBundler.AddImage(aNode->mFilePath.c());
					//FImage *aImage = new FImage();
					//aImage->Load(aNode->mFilePath.c());
					//gImageBundler.AddImage(aImage);

				}
			}

            FString aTestDir;
            os_getTestDirectory(&aTestDir);
			gImageBundler.Save(aTestDir + gImageBundler.mBundleName.c());

			if(gImageBundler.mSuccess == false)
			{
				

				gImageBundler.Clear();

				for(int i = 0; i < aCheckBucket->mNodeList.mCount; i++)
				{
					FSpriteSequenceSearchNode *aNode = (FSpriteSequenceSearchNode *)(aCheckBucket->mNodeList.Fetch(i));

					if(aNode)
					{
						FImage *aImage = new FImage();
						aImage->Load(aNode->mFilePath.c());

						FImage *aSmaller = new FImage();


						aSmaller->Resize(aImage->mWidth / 2, aImage->mHeight / 2, aImage);
						gImageBundler.AddImage(aSmaller);

						delete aImage;
					}
				}
			} else {
				aNameList.Add(new FString(gImageBundler.mBundleName.c()));
			}
		}
    }
    
    gImageBundler.EndBundle();
    gImageBundler.mAutoBundle = false;

	EnumList(FString, aString, aNameList) {
		Log("mTestSequence[aSeqIndex++].LoadBundle(\"%s\");\n", aString->c());
	}
	FreeList(FString, aNameList);
    
}
*/

/*
FSpriteSequenceSearchNode::FSpriteSequenceSearchNode(const char *pFilePath, const char *pName, int pIndex)
{
    mFilePath = pFilePath;
    mName = pName;
    mIndex = pIndex;
    
    
    Log("Bucket %s(%d)\n", mName.c(), mIndex );
    
    //mName.RemovePathAndExtension();

}

FSpriteSequenceSearchNode::~FSpriteSequenceSearchNode()
{
    
}


FSpriteSequenceSearchBucket::FSpriteSequenceSearchBucket()
{
    mCount = 0;
    mStartIndex = 0;
    mEndIndex = 0;
}

FSpriteSequenceSearchBucket::~FSpriteSequenceSearchBucket()
{
    FreeList(FSpriteSequenceSearchNode, mNodeList);
}

void FSpriteSequenceSearchBucket::Finalize()
{
    
    //FList aBucketList;
    //EnumList(FSpriteSequenceSearchNode, aNode, aBucketList->)
    
}

void FSpriteSequenceSearchBucket::AddNode(FSpriteSequenceSearchNode *pSerchNode)
{
    if(pSerchNode)
    {
        if(mNodeList.mCount <= 0)
        {
            mStartIndex = pSerchNode->mIndex;
            mEndIndex = pSerchNode->mIndex;
        }
        
        mNodeList.Add(pSerchNode);
        
        mCount = mNodeList.mCount;
    }
}
 
*/
