//
//  FFont.cpp
//  CrazyDartsArc
//
//  Created by Nick Raptis on 10/27/11.
//  Copyright (c) 2011 Nick Raptis. All rights reserved.
//

#include "core_includes.h"
#include "FFont.hpp"
#include "FXML.hpp"

FFont::FFont() {
    mPointSize = 0.0f;
    for (int i=0;i<256;i++) {
        mCharacterStrideX[i] = 0.0f;
        mCharacterOffsetX[i] = 0.0f;
    }
    for (int i=0;i<256;i++) {
        for (int n=0;n<256;n++) {
            mKern[i][n] = 0.0f;
        }
    }
    mDataScale = 1.0f;
    mSpriteScale = 1.0f;
    mGlobalSqueeze = 0.0f;
}

FFont::~FFont() {
    
}

void FFont::LoadRange(const char *pFilePrefix, char pStart, char pEnd) {
    int aStart = (int)((unsigned char)pStart);
    int aEnd = (int)((unsigned char)pEnd);
    if (aStart > aEnd) {
        int aHold=aStart;
        aStart=aEnd;
        aEnd=aHold;
    }

    bool aKludgePointSize = false;
    if (mPointSize <= 2.0) {
        aKludgePointSize = true;
    }

    for (int i=aStart;i<=aEnd;i++) {
        FString aCharString = FString(i);
        FString aPathString = FString(pFilePrefix) + aCharString;
        
        mCharacterSprite[i].Load(aPathString.c());

        Log("Font[%s] = (%f x %f)\n", pFilePrefix, mCharacterSprite[i].mWidth, mCharacterSprite[i].mHeight);
        if(mCharacterStrideX[i] <= 0.0f)mCharacterStrideX[i] = mCharacterSprite[i].mWidth;

        if (aKludgePointSize && mPointSize < mCharacterSprite[i].mHeight) {
            mPointSize = mCharacterSprite[i].mHeight;
        }

        mCharacterStrideX[i] = mCharacterSprite[i].mWidth;
    }
    if(mPrefix.mLength == 0)mPrefix = pFilePrefix;
}

void FFont::Load(char *pFilePrefix, char *pCharacters) {
    if(pFilePrefix == 0)pFilePrefix = mPrefix.c();
    FString aPrefixString = FString(pFilePrefix);
    FString aPath;
    int aIndex = 0;
    if (pCharacters) {
        while (*pCharacters) {
            aIndex = (int)((unsigned char)(*pCharacters));
            //aPath = FString(aPrefixString.c()) + FString((*pCharacters));
            //mCharacterSprite[aIndex].Load(aPath);
            //if (mCharacterSprite[aIndex].mWidth <= 0) {
            aPath = FString(aPrefixString.c()) + FString(aIndex);
            mCharacterSprite[aIndex].Load(aPath);
            //}
        
            if(mCharacterStrideX[aIndex] <= 0.0f)mCharacterStrideX[aIndex] = mCharacterSprite[aIndex].mWidth;
            if(mPointSize < mCharacterSprite[aIndex].mHeight)mPointSize = mCharacterSprite[aIndex].mHeight;
            mCharacterStrideX[aIndex] = mCharacterSprite[aIndex].mWidth;
            pCharacters++;
        }
    }
}

void FFont::LoadAlphaNumeric(const char *pFilePrefix)
{
    LoadRange(pFilePrefix, 'a', 'z');
    LoadRange(pFilePrefix, 'A', 'Z');
    LoadRange(pFilePrefix, '0', '9');
}

void FFont::LoadScore(const char *pFilePrefix) {
    Load(pFilePrefix, "0123456789,.()!#$%*-+=");
}

void FFont::Unload() {
    mPointSize = 0.0f;
    for (int i=0;i<256;i++) {
        mCharacterSprite[i].Kill();
        mCharacterStrideX[i] = 0.0f;
        mCharacterOffsetX[i] = 0.0f;
    }
    
    for (int i=0;i<256;i++) {
        for (int n=0;n<256;n++) {
            mKern[i][n] = 0.0f;
        }
    }
    mDataScale = 1.0f;
    mSpriteScale = 1.0f;
    mGlobalSqueeze = 0.0f;
    
}

void FFont::Draw(const char *pText, float pX, float pY) {
    Draw(pText, pX, pY, 1.0f);
}

void FFont::Draw(const char *pText, float pX, float pY, float pScale) {
    unsigned char aChar = 0;
    float aDrawX = pX;
    float aDrawY = pY;
    int aCharIndex = -1;
    int aCharIndexPrev = -1;
    float aKern = 0.0f;
    float aScale = (mDataScale * pScale);
    float aPointSize = mPointSize * mDataScale * pScale;
    float aSpriteScale = mSpriteScale * pScale;
    if (pText) {
        unsigned char *aPtr = (unsigned char *)pText;
        while (*aPtr) {
            aKern = 0.0f;
            aCharIndexPrev = aCharIndex;
            aChar = *aPtr;
            aCharIndex = aChar;
            if(aCharIndexPrev != -1)aKern = mKern[aCharIndexPrev][aCharIndex];
            float aSpriteWidth = mCharacterSprite[aCharIndex].mWidth * aSpriteScale;
            mCharacterSprite[aCharIndex].Draw(aDrawX + ((mCharacterOffsetX[aCharIndex] + aKern) * aScale) + aSpriteWidth  * 0.5f, aDrawY + aPointSize / 2.0f, aSpriteScale, 0.0f);
            //mCharacterSprite[aCharIndex].Draw(aDrawX + ((mCharacterOffsetX[aCharIndex] + aKern) * aScale), aDrawY + aPointSize / 2.0f, aSpriteScale, 0.0f);
            
            aDrawX += (mCharacterStrideX[aCharIndex] + aKern) * aScale;
            aPtr++;
        }
    }
}

void FFont::SetSpaceWidth(float pSpaceWidth) {
    mCharacterStrideX[32] = pSpaceWidth;
}

int FFont::GetCursor(float pTouchX, float pTouchY, const char *pText, float pX, float pY, float pScale) {
    if (pTouchX < pX) { return 0; }
    unsigned char aChar = 0;
    float aDrawX = pX;
    int aResult = 0;
    int aCharIndex = -1;
    int aCharIndexPrev = -1;
    float aKern = 0.0f;
    float aScale = (mDataScale * pScale);
    float aBestDist = 4096.0f;
    if (pText) {
        unsigned char *aPtr = (unsigned char *)pText;
        int aIndex = 1;
        while (*aPtr) {
            aKern = 0.0f;
            aCharIndexPrev = aCharIndex;
            aChar = *aPtr;
            aCharIndex = aChar;
            if (aCharIndexPrev != -1) {
                aKern = mKern[aCharIndexPrev][aCharIndex];
            }
            
            float aLeftX = aDrawX;
            aDrawX += (mCharacterStrideX[aCharIndex] + aKern) * aScale;
            
            float aDistLeft = pTouchX - aLeftX;
            if (aDistLeft < 0.0f) { aDistLeft = -aDistLeft; }
            
            float aDistRight = pTouchX - aDrawX;
            if (aDistRight < 0.0f) { aDistRight = -aDistRight; }
            
            if (aDistLeft < aDistRight) {
                if (aDistLeft < aBestDist) {
                    aBestDist = aDistLeft;
                    aResult = aIndex - 1;
                }
            } else {
                if (aDistRight < aBestDist) {
                    aBestDist = aDistRight;
                    aResult = aIndex;
                }
            }
            ++aPtr;
            ++aIndex;
        }
    }
    return aResult;
}

float FFont::LocationOfCursor(int pCursor, const char *pText, float pX, float pY, float pScale) {
    if (pCursor <= 0) { return pX; }
    unsigned char aChar = 0;
    float aResult = pX;
    int aCharIndex = -1;
    int aCharIndexPrev = -1;
    float aKern = 0.0f;
    float aScale = (mDataScale * pScale);
    if (pText) {
        unsigned char *aPtr = (unsigned char *)pText;
        int aIndex = 0;
        while (*aPtr) {
            if (aIndex == pCursor) { return aResult; }
            aKern = 0.0f;
            aCharIndexPrev = aCharIndex;
            aChar = *aPtr;
            aCharIndex = aChar;
            if (aCharIndexPrev != -1) { aKern = mKern[aCharIndexPrev][aCharIndex]; }
            
            
            
            
            aResult += (mCharacterStrideX[aCharIndex] + aKern) * aScale;

            
            ++aPtr;
            ++aIndex;
        }
    }
    
    return aResult;
}

void FFont::Right(const char *pText, float pX, float pY) {
    float aWidth = Width(pText);
    Draw(pText, pX - aWidth, pY);
}

void FFont::Center(const char *pText, float pX, float pY) {
    Center(pText, pX, pY, 1.0f);
}

void FFont::Center(const char *pText, float pX, float pY, float pScale) {
    float aWidth = Width(pText, pScale);
    Draw(pText, pX - aWidth * 0.5f, pY - (mPointSize * (mDataScale * pScale) * 0.5f), pScale);
}

void FFont::Right(const char *pText, float pX, float pY, float pScale) {
    float aWidth = Width(pText, pScale);
    Draw(pText, pX - aWidth, pY, pScale);
}

void FFont::RightCenter(const char *pText, float pX, float pY, float pScale) {
    float aWidth = Width(pText, pScale);
    Draw(pText, pX - aWidth, pY - (mPointSize * (mDataScale * pScale) * 0.5f), pScale);
}

void FFont::Left(const char *pText, float pX, float pY, float pScale) {
    Draw(pText, pX, pY, pScale);
}

void FFont::LeftCenter(const char *pText, float pX, float pY, float pScale) {
    Draw(pText, pX, pY - (mPointSize * (mDataScale * pScale) * 0.5f), pScale);
}


float FFont::Width(const char *pText, float pScale) {
    float aResult = 0.0f;
    unsigned char aChar = 0;
    int aCharIndex = -1;
    int aCharIndexPrev = -1;
    float aKern = 0.0f;
    float aScale = (pScale * mDataScale);
    if (pText) {
        unsigned char *aPtr = (unsigned char *)pText;
        while (*aPtr) {
            aKern = 0.0f;
            aChar = *aPtr;
            aCharIndexPrev = aCharIndex;
            aCharIndex = aChar;
            if(aCharIndexPrev != -1)aKern = mKern[aCharIndexPrev][aCharIndex];
            aResult += ((mCharacterStrideX[aCharIndex] + aKern) * aScale);
            aPtr++;
        }
    }
    return aResult;
}

float FFont::Width(const char *pText) {
    return Width(pText, 1.0f);
}


float FFont::ScaleForWidth(const char *pText, float pLabelWidth, float pLabelPadding) {
    float aWidthBase =  Width(pText);
    float aLabelWidth = pLabelWidth - (pLabelPadding * 2.0f);
    float aScale = 1.0f;
    if ((aLabelWidth > 1.0f) && (aWidthBase > 1.0f)) {
        aScale = (aLabelWidth / aWidthBase);
    }
    return aScale;
}



void FFont::SetKern(int pStartCharIndex, int pEndCharIndex, int pKernAmount) {
    if ((pStartCharIndex >= 0) && (pEndCharIndex >= 0) && (pStartCharIndex < 256) && (pEndCharIndex < 256)) {
        mKern[pStartCharIndex][pEndCharIndex] = ((float)pKernAmount);
    }
}

void FFont::ApplyScrunch(float pScrunch) {
    for (int i=0;i<256;i++) {
        if (mCharacterStrideX[i] != 0.0f) {
            mCharacterStrideX[i] -= pScrunch;
        }
    }
}

void FFont::ApplyExpand(float pExpand) {
    for(int i=0;i<256;i++) {
        if ((mCharacterSprite[i].mWidth > 0.0f) || (mCharacterStrideX[i] > 0.0f)) {
            mCharacterStrideX[i] += pExpand;
        }
    }
}

void FFont::ApplyOffsetX(float pOffset) {
    for (int i=0;i<256;i++) {
        if ((mCharacterSprite[i].mWidth > 0.0f) || (mCharacterStrideX[i] > 0.0f)) {
            mCharacterOffsetX[i] += pOffset;
        }
    }
}

void FFont::SetStride(int pCharIndex, float pOffsetX, float pStride) {
    if ((pCharIndex >= 0) && (pCharIndex < 256)) {
        mCharacterStrideX[pCharIndex] = pStride;
        mCharacterOffsetX[pCharIndex] = pOffsetX;
    }
}


float FFont::PlotWidth(char *pText, float *pArray) {
    unsigned char aChar = 0;
    float aX = 0.0f;
    int aCharIndex = -1;
    int aCharIndexPrev = -1;
    float aKern = 0.0f;

    if (pText) {
        int aWriteIndex = 0;
        unsigned char *aPtr = (unsigned char *)pText;
        while (*aPtr) {
            aKern = 0.0f;
            aCharIndexPrev = aCharIndex;
            aChar = *aPtr;
            aCharIndex = aChar;
            if(aCharIndexPrev != -1)aKern = mKern[aCharIndexPrev][aCharIndex];
            pArray[aWriteIndex] = aX + ((mCharacterOffsetX[aCharIndex] + aKern) * mDataScale) + mCharacterSprite[aCharIndex].mWidth / 2.0f;
            aX += (mCharacterStrideX[aCharIndex] + aKern) * mDataScale;
            aPtr++;
            aWriteIndex++;
        }
    }
    return aX;
}

float FFont::PlotWidthCentered(char *pText, float *pArray) {
    float aWidth = PlotWidth(pText, pArray);
    if (pText) {
        float aWidth2 = aWidth / 2.0f;
        int aIndex = 0;
        unsigned char *aPtr = (unsigned char *)pText;
        while (*aPtr) {
            pArray[aIndex] -= aWidth2;
            aPtr++;
            aIndex++;
        }
    }
    return aWidth;
}

void FFont::PrintLoaded() {
    int aLoadedChars = 0;
    for(int i=0;i<256;i++) {
        if ((mCharacterStrideX[i] > 0.025f) || (mCharacterSprite[i].mWidth > 0.025f)) {
            aLoadedChars++;
        }
    }

    Log("_______FONT_____\n");
    Log("Name: %s\n", mPrefix.c());
    Log("Count: %d\n", aLoadedChars);
    Log("Size: %d  DataScale: %.2f  SpriteScale: %.2f\n", ((int)mPointSize), mDataScale, mSpriteScale);
    if(aLoadedChars > 0)Log("__\n");

    for (int i=0;i<256;i++) {
        if ((mCharacterStrideX[i] > 0.025f) || (mCharacterSprite[i].mWidth > 0.025f)) {
            char aChar = (char)i;
            Log("%d ( %c ) Img[%d x %d] Stride [%.1f] Offset[%.1f]\n", i, aChar, ((int)mCharacterSprite[i].mWidth), ((int)mCharacterSprite[i].mHeight), mCharacterStrideX[i], mCharacterOffsetX[i]);
        }
    }
    if(aLoadedChars > 0)Log("__\n");
    Log("____END_FONT____\n");
}


FString FFont::CharToFileSafe(char c)
{
    FString aResult;
    
    if((c >= 'a') && (c <= 'z'))
    {
        aResult = FString(c);
    }
    else if((c >= 'A') && (c <= 'Z'))
    {
        aResult = FString(c);
    }
    else if((c >= '0') && (c <= '9'))
    {
        aResult = FString(c);
    }
    else if((c == '$') || (c <= '_') || (c <= '-') || (c <= '+') || (c <= '(') || (c <= ')') || (c <= '[') || (c <= ']') || (c <= '|') || (c <= ','))
    {
        aResult = FString(c);
    }
    else
    {
        unsigned char aChar = c;
        
        
        //int aInt = (int)(((unsigned int)((unsigned char)c)));
        int aInt = aChar;//(int)(((unsigned int)((unsigned char)c)));
        
        
        aResult = FString(aInt);
    }
    
    return aResult;
}

FString FFont::CharToReadable(char pChar)
{
    
    FString aResult = FString(pChar);
    
    if(pChar == 0x07)aResult = "\a";
    else if(pChar == 0x08)aResult = "\b";
    else if(pChar == 0x0C)aResult = "\f";
    else if(pChar == 0x0A)aResult = "\n";
    else if(pChar == 0x0D)aResult = "\r";
    else if(pChar == 0x09)aResult = "\t";
    else if(pChar == 0x0B)aResult = "\v";
    else if(pChar == 0x5C)aResult = "\\";
    else if(pChar == 0x27)aResult = "\'";
    else if(pChar == 0x22)aResult = "\"";
    else if(pChar == 0x3F)aResult = "\?";
    else if(pChar == 0x00)aResult = "\0";
    else if(pChar == 0x01)aResult = "\1";
    else if(pChar == 0x02)aResult = "\2";
    else if(pChar == 0x03)aResult = "\3";
    else if(pChar == 0x04)aResult = "\4";
    else if(pChar == 0x05)aResult = "\5";
    else if(pChar == 0x06)aResult = "\6";
    else if(pChar == 0x07)aResult = "\7";
    
    
    
    //else aResult = FString(c);
    
    aResult = FString(FString("'") + aResult + FString("'")).c();
    
    return aResult;
}

void FFont::Kill() {
    for (int i=0;i<256;i++) {
        mCharacterSprite[i].Kill();
    }
}


void FFont::LoadNew(const char *pDataFile, const char *pImagePrefix, const char *pCharacters) {
    mPointSize = 24.0f;
    
    int aCharIndex[256];
    char aChar[256];
    char aCharAllowed[256];
    
    
    for (int i=0;i<256;i++) {
        aChar[i] = 0;
        aCharIndex[i] = 0;
        aCharAllowed[i] = 1;
    }
    
    if (pCharacters != 0) {
        
        unsigned char *aPtr = ((unsigned char *)pCharacters);
        int aLen = FString::Length(pCharacters);
        
        if(aLen > 0)
        {
            for(int i=0;i<256;i++)aCharAllowed[i] = 0;
            int aCharIndex = -1;
            while(((*aPtr) != 0) && (aLen > 0))
            {
                unsigned char aReadChar = *aPtr;aCharIndex = aReadChar;
                if((aCharIndex >= 0) && (aCharIndex < 256))aCharAllowed[aCharIndex] = true;
                aPtr++;aLen--;
            }
        }
    }
    
    int aCharIndexCursor = 0;

    
    for (int i=0;i<256;i++) { mCharacterStrideX[i] = 0.0f; }
    for (int i=0;i<256;i++) {
        for (int n=0;n<256;n++) {
            mKern[i][n] = 0.0f;
        }
    }
    
    FFile aLoadFile;
    aLoadFile.Load(pDataFile);
    
    FString aPath = FString(pDataFile);
    aPath.RemoveExtension();
    
    if(aLoadFile.mLength <= 0)aLoadFile.Load(aPath + FString(".dat"));

    
    mPointSize = ((float)(aLoadFile.ReadShort()));
    int aCharCount = (int)(aLoadFile.ReadShort());

    if (aCharCount <= 0) {
        //Log("__Font (%s) Failed To Load__\n\n", aPath.c());
        //Log("File \"%s\"   Length = %d\n", pDataFile, aLoadFile.mLength);
        //Log("Char Count = %d    Point Size = %f\n", aCharCount, mPointSize);
        //Log("Image File [%s]\n______\n", pImagePrefix);
        
        return;
    }
    
    
    gSpriteListEnabled = false;
    
    unsigned char aScanChar = 0;
    int aReadIndex = -1;
    
    
    //unsigned char aReadChar = 0;
    //unsigned short aReadShort = 0;
    
    
    for (int aLoopIndex = 0;aLoopIndex < aCharCount;aLoopIndex++) {
        aScanChar = aLoadFile.ReadChar();
        aReadIndex = aScanChar;
        
        //((int)((unsigned int)((unsigned char)(aLoadFile.ReadChar()))));
        //unsigned char aReadChar = aScanChar;//((char)((unsigned char)(((unsigned int)(aReadIndex)))));
        
        
        mCharacterStrideX[aReadIndex] = ((float)(aLoadFile.ReadShort()));
        mCharacterOffsetX[aReadIndex] = ((float)(aLoadFile.ReadShort()));
        
        if (aCharAllowed[aReadIndex]) {
            FString aPath = FString(pImagePrefix) + FString(aScanChar);
            mCharacterSprite[aReadIndex].Load(aPath);
        } else {
            mCharacterStrideX[aReadIndex] = 0.0f;
            mCharacterOffsetX[aReadIndex] = 0.0f;
        }
        
        if (aCharIndexCursor < 256) {
            aCharIndex[aCharIndexCursor] = aReadIndex;
            aChar[aCharIndexCursor] = aScanChar;
            aCharIndexCursor++;
        }
    }
    
    if (aLoadFile.ReadBool()) {
        unsigned char aKernPartnerChar = 0;
        int aKernPartnerIndex = -1;
        
        int aKernAmount = 0;
        
        int aTotalKernCount = ((int)(aLoadFile.ReadShort()));
        if(aTotalKernCount > 40000)aTotalKernCount = 40000;
        
        int aCharKernCount = 0;
        int aLoopIndex = 0;
        int aTotalKernIndex = 0;
        
        for (int i=0;((i<aCharCount) && (aTotalKernIndex < aTotalKernCount) && (aLoopIndex < aCharIndexCursor));i++) {
            aCharKernCount = ((int)(aLoadFile.ReadShort()));
            aReadIndex = aCharIndex[aLoopIndex];
            aScanChar = aChar[aLoopIndex];
            
            while ((aCharKernCount > 0) && (aTotalKernIndex < aTotalKernCount)) {
                aKernPartnerChar = aLoadFile.ReadChar();
                aKernAmount = ((int)(aLoadFile.ReadShort()));
                
                aKernPartnerIndex = aKernPartnerChar;
                
                if ((aReadIndex >= 0) && (aReadIndex < 256) && (aKernPartnerIndex >= 0) && (aKernPartnerIndex < 256)) {
                    mKern[aReadIndex][aKernPartnerIndex] = aKernAmount;
                }
                
                //Log("__________[[%d]] Loaded Kern [%d] => [%d]  ((%c => %c)) [%d]\n", aTotalKernIndex, aReadIndex, aKernPartnerIndex, aScanChar, aKernPartnerChar, aKernAmount);
                
                aCharKernCount--;
                aTotalKernIndex++;
            }
            
            
            aLoopIndex++;
        }
    }
    
    gSpriteListEnabled = true;
    
}

void FFont::LoadNew(const char *pDataFile, const char *pImagePrefix) {
    LoadNew(pDataFile, pImagePrefix, 0);
}




void FFont::BitmapDataBatch(const char *pDataPath, const char *pImagePath,
                            const char *pFilePrefixCharImages, const char *pDataFile,
                            int pPaddingCrop, int pPaddingGlyph, const char *pRemoveCharacters) {
    FFontImportData *aImport = BitmapDataImport(pDataPath, pImagePath, pPaddingCrop, pPaddingGlyph, pRemoveCharacters);
    
    if (aImport == 0) {
        Log("Failed To Batch Font[%s] [%s]\n", pDataPath, pImagePath);
    }
    
    FString aName = aImport->mName.c();
    
    
    BitmapDataExportGlyphs(aImport, pFilePrefixCharImages);
    
    BitmapDataExportTestStrips(aImport, pDataFile, 4);
    
    BitmapDataExportData(aImport, FString(FString(pDataFile) + FString(".kern")).c());
    
    //FString aRemoveString = FString(pRemoveCharacters);
    //if(aRemoveString.mLength > 0)BitmapDataRemoveCharacters(aImport, pRemoveCharacters);
    
    
    
    aImport->Clear();
    delete aImport;
    aImport = 0;
    
}

FFontImportData *FFont::BitmapDataImport(const char *pDataPath, const char *pImagePath, int pPaddingCrop, int pPaddingGlyph, const char *pRemoveCharacters)
{
    FFontImportData *aImportData = 0;
    
    FImage aImage;
    aImage.Load(pImagePath);
    
    FString aPath = FString(pDataPath);
    FString aExt = aPath.ChopExtension();
    
    FFile aFile;
    aFile.Load(pDataPath);
    
    if(aFile.mLength <= 0)aFile.Load(aPath);
    if(aFile.mLength <= 0)aFile.Load(aPath + FString(".fnt"));
    if(aFile.mLength <= 0)aFile.Load(aPath + FString(".FNT"));
    if(aFile.mLength <= 0)aFile.Load(aPath + FString(".font"));
    if(aFile.mLength <= 0)aFile.Load(aPath + FString(".FONT"));
    if(aFile.mLength <= 0)aFile.Load(aPath + FString(".xml"));
    if(aFile.mLength <= 0)aFile.Load(aPath + FString(".XML"));
    
    FXML aXML;
    FXMLTag *aRoot = 0;
    
    if (aFile.mLength > 0) {
        aXML.Parse((char*)aFile.mData, aFile.mLength);aRoot = aXML.GetRoot();
    }
    
    if (aRoot == 0) {
        aXML.Load(pDataPath);aRoot = aXML.GetRoot();
    }
    
    if (aRoot == 0) {
        aXML.Load(aPath);aRoot = aXML.GetRoot();
    }
    
    FFontImportGlyph *aGlyph = 0;
    FFontImportGlyph *aGlyphCompare = 0;
    
    if (aRoot) {
        aImportData = new FFontImportData();
        
        int aPaddingUp = 0;
        int aPaddingRight = 0;
        int aPaddingDown = 0;
        int aPaddingLeft = 0;
        
        aImportData->mName = pDataPath;
        aImportData->mName.RemovePath();
        aImportData->mName.RemoveExtension();
        
        EnumTagsMatching(aRoot, aInfoTag, "info") {
            aImportData->mPointSize = aInfoTag->GetParamInt("size");
            aImportData->mBold = aInfoTag->GetParamBool("bold");
            aImportData->mItalic = aInfoTag->GetParamBool("italic");
            
            FString aPaddingString = aInfoTag->GetParamValue("padding");
            aPaddingUp = aPaddingString.GetNumberI();
            aPaddingRight = aPaddingString.GetNextNumberI();
            aPaddingDown = aPaddingString.GetNextNumberI();
            aPaddingLeft = aPaddingString.GetNextNumberI();
            
            FString aSpacingString = aInfoTag->GetParamValue("spacing");
            aImportData->mSpacingH = aSpacingString.GetNumberI();
            aImportData->mSpacingV = aSpacingString.GetNextNumberI();
        }
        
        if (aImportData->mPointSize <= 0) { aImportData->mPointSize = 24; }
        
        aImportData->mKernCount = 0;
        
        aImportData->mInsetMinU = -1;
        aImportData->mInsetMinR = -1;
        aImportData->mInsetMinD = -1;
        aImportData->mInsetMinL = -1;
        
        aImportData->mImageWidthMax = 0;
        aImportData->mImageHeightMax = 0;
        
        aImportData->mCharactersLoadedCount = 0;
        aImportData->mCharactersRemovedCount = 0;
        
        BitmapDataRemoveCharacters(aImportData, pRemoveCharacters);
        
        EnumTagsMatching(aRoot, aCharListTag, "chars") {
            EnumTagsMatching(aCharListTag, aCharTag, "char") {
                int aID = aCharTag->GetParamInt("id");
                aGlyph = aImportData->GetGlyph(aID);
                
                if (aGlyph != 0) {
                    aGlyph->Reset();
                    
                    aGlyph->mImageX = aCharTag->GetParamInt("x");
                    aGlyph->mImageY = aCharTag->GetParamInt("y");
                    aGlyph->mImageWidth = aCharTag->GetParamInt("width");
                    aGlyph->mImageHeight = aCharTag->GetParamInt("height");
                    aGlyph->mStrideX = aCharTag->GetParamInt("xadvance");
                    aGlyph->mImageOffsetX = aCharTag->GetParamInt("xoffset");
                    aGlyph->mImageOffsetY = aCharTag->GetParamInt("yoffset");
                    
                    if((aImage.mWidth > 0) && (aImage.mHeight > 0) && (aGlyph->mAllowed == true) && (aImportData->mPointSize > 0)) {
                        int aCropX = (aGlyph->mImageX - pPaddingCrop);
                        int aCropY = (aGlyph->mImageY - pPaddingCrop);
                        
                        int aCropWidth = (aGlyph->mImageWidth + pPaddingCrop * 2);
                        int aCropHeight = (aGlyph->mImageHeight + pPaddingCrop * 2);
                        
                        FImage *aImageBase = aImage.Crop(aCropX, aCropY, aCropWidth, aCropHeight);
                        
                        if (aImageBase) {
                            if ((aImageBase->mWidth > 0) && (aImageBase->mHeight > 0)) {
                                int aFixedWidth = (aImageBase->mWidth + pPaddingGlyph * 2);
                                int aFixedHeight = (aImportData->mPointSize + pPaddingGlyph * 2);
                                
                                
                                int aFixedX = pPaddingGlyph;
                                int aFixedY = pPaddingGlyph + aGlyph->mImageOffsetY;
                                //aFixedY -= ((aFixedHeight - aImageBase->mHeight) / 2);
                                
                                aGlyph->mImageOffsetY = 0;
                                
                                bool aOdd = false;
                                
                                //Note: If we want to revert to use padding radix, this will achieve the task.
                                //However, the render logic needs to be rewritten to handle the case where padding
                                //is non ubiquitous across all glyphs.
                                /*
                                if ((pPaddingRadix > 1) && (pPaddingRadix < 512)) {
                                    for (int aRadixLoop=0;aRadixLoop<=pPaddingRadix;aRadixLoop++) {
                                        if((aFixedWidth % pPaddingRadix) != 0){aFixedWidth++;if(aOdd == true)aFixedX++;}
                                        if((aFixedHeight % pPaddingRadix) != 0){aFixedHeight++;if(aOdd == true)aFixedY++;}
                                        aOdd = (!aOdd);
                                    }
                                }
                                */
                                
                                FImage *aImageAdjusted = new FImage();
                                //aImageAdjusted->Make (aFixedWidth, aFixedHeight, IMAGE_RGBA(gRand.Get(200), gRand.Get(200), gRand.Get(220), 30 + gRand.Get(70)));
                                //aImageAdjusted->StampBlend(aImageBase, aFixedX, aFixedY, 0, 0, aImageBase->mWidth, aImageBase->mHeight);
                                
                                aImageAdjusted->MakeBlank(aFixedWidth, aFixedHeight);
                                aImageAdjusted->Stamp(aImageBase, aFixedX, aFixedY, 0, 0, aImageBase->mWidth, aImageBase->mHeight);
                                
                                
                                aImageBase->Kill();
                                delete aImageBase;
                                aGlyph->mImage = aImageAdjusted;
                                
                                
                                if(aImageAdjusted->mWidth > aImportData->mImageWidthMax)aImportData->mImageWidthMax = aImageAdjusted->mWidth;
                                if(aImageAdjusted->mHeight > aImportData->mImageHeightMax)aImportData->mImageHeightMax = aImageAdjusted->mHeight;
                                
                                aGlyph->mEdgeInsetU = -1;aGlyph->mEdgeInsetR = -1;aGlyph->mEdgeInsetD = -1;aGlyph->mEdgeInsetL = -1;
                                
                                aImageAdjusted->GetEdges(aGlyph->mEdgeInsetL, aGlyph->mEdgeInsetR, aGlyph->mEdgeInsetU, aGlyph->mEdgeInsetD);
                                
                                aGlyph->mEdgeInsetR = ((aImageAdjusted->mWidth - aGlyph->mEdgeInsetR));
                                aGlyph->mEdgeInsetD = ((aImageAdjusted->mHeight - aGlyph->mEdgeInsetD));
                                
                                if(aImageAdjusted->IsBlank() == false)
                                {
                                    if((aImageAdjusted->mWidth > 0) && (aImageAdjusted->mHeight > 0))
                                    {
                                        aGlyph->mLoadSuccess = true;
                                    }
                                }
                                
                                if(aImportData->mInsetMinU == -1)aImportData->mInsetMinU = aGlyph->mEdgeInsetU;
                                else if(aGlyph->mEdgeInsetU < aImportData->mInsetMinU)aImportData->mInsetMinU = aGlyph->mEdgeInsetU;
                                if(aImportData->mInsetMinR == -1)aImportData->mInsetMinR = aGlyph->mEdgeInsetR;
                                else if(aGlyph->mEdgeInsetR < aImportData->mInsetMinR)aImportData->mInsetMinR = aGlyph->mEdgeInsetR;
                                if(aImportData->mInsetMinD == -1)aImportData->mInsetMinD = aGlyph->mEdgeInsetD;
                                else if(aGlyph->mEdgeInsetD < aImportData->mInsetMinD)aImportData->mInsetMinD = aGlyph->mEdgeInsetD;
                                if(aImportData->mInsetMinL == -1)aImportData->mInsetMinL = aGlyph->mEdgeInsetL;
                                else if(aGlyph->mEdgeInsetL < aImportData->mInsetMinL)aImportData->mInsetMinL = aGlyph->mEdgeInsetL;
                            }
                        }
                    }
                    
                    //Spaces...
                    if(aID == 32)aGlyph->mLoadSuccess = true;
                }
                
                EnumTagsMatching(aRoot, aKernListTag, "kernings") {
                    EnumTagsMatching(aKernListTag, aKernTag, "kerning")
{
                        int aKernChar1 = aKernTag->GetParamInt("first");
                        int aKernChar2 = aKernTag->GetParamInt("second");
                        int aKernAmount = aKernTag->GetParamInt("amount");
                        
                        aGlyph = aImportData->GetGlyph(aKernChar1);
                        aGlyphCompare = aImportData->GetGlyph(aKernChar2);
                        
                        if((aGlyph != 0) && (aGlyphCompare != 0))
                        {
                            if((aGlyph->Valid() == true) && (aGlyphCompare->Valid() == true))aGlyph->mKern[aKernChar2] = aKernAmount;
                        }
                    }
                }
            }
            
            if(aImportData->mName.mLength <= 0)aImportData->mName = "unknown";
            
            if((aImportData->mBold == true) && (aImportData->mName.Contains("bold") == false))aImportData->mName += "_bold";
            if((aImportData->mItalic == true) && (aImportData->mName.Contains("italic") == false))aImportData->mName += "_italic";
            
            aImportData->mName.Replace(" ", "_");
            for(int i=0;i<4;i++)aImportData->mName.Replace("__", "_");
            
        }
        
        
        aImportData->mCharactersLoadedCount = 0;
        aImportData->mKernCount = 0;
        aImportData->mKerningEnabled = false;
        
        for(int i=0;i<256;i++)
        {
            aGlyph = aImportData->GetGlyph(i);
            if(aGlyph != 0)
            {
                if(aGlyph->Valid())
                {
                    aImportData->mCharactersLoadedCount++;
                    
                    aGlyph->mKernCount = 0;
                    for(int aCheck=0;aCheck<256;aCheck++)
                    {
                        if(aGlyph->mKern[aCheck] != 0)aGlyph->mKernCount++;
                    }
                    
                    if(aGlyph->mKernCount > 0)
                    {
                        aImportData->mKerningEnabled = true;
                        aImportData->mKernCount += aGlyph->mKernCount;
                    }
                }
            }
        }
    }
    return aImportData;
}

void FFont::BitmapDataExportTestStrips(FFontImportData *pImport, const char *pName, int pCount) {
    if (pImport == 0) { return; }
    FFontImportGlyph *aGlyph = 0;
    bool aStamped = true;
    int aStripX = 8;
    int aPointSize = pImport->mPointSize;
    for (int aTestStrip=0;aTestStrip<pCount;aTestStrip++) {
        if ((aStamped == true) && (pImport->mPointSize >= 1) && (pImport->mPointSize <= 2048)) {
            FImage aStrip;
            aGlyph = 0;
            aStamped = false;
            aStripX = 32;
            aStrip.Make(2048, aPointSize + 128, IMAGE_RGBA(0, 0, 0, 255));
            for (int i=0;i<220;i++) {
                aGlyph = pImport->GetGlyph(gRand.Get(256));
                if (aGlyph != 0) {
                    if (aGlyph->Valid()) {
                        if ((aGlyph->mImage->mWidth > 0) && ((aStripX + aGlyph->mImage->mWidth) < (aStrip.mWidth - 40))) {
                            aStamped = true;
                            aStrip.Stamp(aGlyph->mImage, aStripX, 64, 0, 0, aGlyph->mImage->mWidth, aGlyph->mImage->mHeight);
                            aStripX += (aGlyph->mImage->mWidth + 4);
                        }
                    }
                }
            }
            if (aStamped) {
                FString aPrefix = gDirExport;
                FString aNumberString = FString((int)(aTestStrip + 1));
                if(aNumberString.mLength < 2)aNumberString = FString(FString("0") + FString(aNumberString.c())).c();
                if(aNumberString.mLength < 2)aNumberString = FString(FString("0") + FString(aNumberString.c())).c();
                FString aPath = aPrefix + FString(FString("STRIP_") + FString(pName) + aNumberString + FString("_test.png")).c();
                aPath.Replace(" ", "_");
                for(int i=0;i<4;i++)aPath.Replace("__", "_");
                os_exportPNGImage(aStrip.mData, aPath.c(), aStrip.mWidth, aStrip.mHeight);
            }
        }
    }
}

void FFont::BitmapDataExportGlyphs(FFontImportData *pImport, const char *pName) {
    if (pImport == 0) return;
    FFontImportGlyph *aGlyph = 0;
    FImage *aImage = 0;
    FString aPrefix = gDirExport;
    for (int i=0;i<256;i++) {
        aGlyph = pImport->GetGlyph(i);
        if (aGlyph != 0) {
            aImage = aGlyph->mImage;
            if ((aImage != 0) && (aGlyph->mAllowed == true) && (aGlyph->mLoadSuccess == true)) {
                if ((aImage->mWidth > 0) && (aImage->mHeight > 0)) {
                    FString aPath = aPrefix + FString(pName) + FString("_") + FString(aGlyph->mIndex) + FString(".png");
                    aPath.Replace(" ", "_");
                    for(int i=0;i<4;i++)aPath.Replace("__", "_");
                    os_exportPNGImage(aImage->mData, aPath.c(), aImage->mWidth, aImage->mHeight);
                }
            }
        }
    }
}


void FFont::BitmapDataExportData(FFontImportData *pImport, const char *pName) {
    if (pImport == 0) { return; }
    FFile aFile;
    int aKern = 0;
    unsigned char aKernChar = 0;
    FFontImportGlyph *aGlyph = 0;
    aFile.WriteShort((short)(pImport->mPointSize));
    aFile.WriteShort((short)(pImport->mCharactersLoadedCount));
    for (int aIndex = 0;aIndex < 256;aIndex++) {
        aGlyph = pImport->GetGlyph(aIndex);
        if (aGlyph) {
            if (aGlyph->Valid()) {
                aFile.WriteChar(aGlyph->mChar);
                aFile.WriteShort(aGlyph->mStrideX);
                aFile.WriteShort((short)(aGlyph->mImageOffsetX));
            }
        }
    }

    if ((pImport->mKerningEnabled == false) || (pImport->mKernCount == 0)) {
        aFile.WriteBool(false);
    } else {
        aFile.WriteBool(true);
        aFile.WriteShort(pImport->mKernCount);
    }

    for (int aIndex=0;aIndex<256;aIndex++) {
        aGlyph = pImport->GetGlyph(aIndex);
        if (aGlyph) {
            if (aGlyph->Valid()) {
                aFile.WriteShort(aGlyph->mKernCount);
                for (int k=0;k<256;k++) {
                    aKern = aGlyph->mKern[k];
                    if (aKern != 0) {
                        aKernChar = k;
                        aFile.WriteChar(aKernChar);
                        aFile.WriteShort((char)(aKern));
                    }
                }
            }
        }
    }
    
    FString aPrefix = gDirExport;
    FString aPath = FString(aPrefix + FString(pName) + FString("_font.kern")).c();
    aPath.Replace(" ", "_");
    for (int i=0;i<4;i++) { aPath.Replace("__", "_"); }
    os_write_file(aPath.c(), aFile.mData, aFile.mLength);
}

void FFont::BitmapDataRemoveCharacters(FFontImportData *pImport, const char *pCharacters) {
    unsigned char *aPtr = ((unsigned char *)pCharacters);
    int aLen = FString::Length(pCharacters);
    FFontImportGlyph *aGlyph = 0;
    if ((aLen > 0) && (pImport != 0) && (aPtr != 0)) {
        int aCharIndex = -1;
        unsigned char aChar = 0;
        while (((*aPtr) != 0) && (aLen > 0)) {
            aChar = *aPtr;
            aCharIndex = aChar;
            aGlyph = pImport->GetGlyph(aCharIndex);
            if (aGlyph) {
                if (aGlyph->mAllowed == true) {
                    pImport->mCharactersRemovedCount++;
                }
                aGlyph->Reset();
                aGlyph->mAllowed = false;
            }
            aLen--;
            aPtr++;
        }
    }
}




FFontImportGlyph::FFontImportGlyph()
{
    mImage = 0;
    
    mKernCount = 0;
    
    mIndex = -1;
    mChar = -1;
    
    mAllowed = true;
    mLoadSuccess = false;
    
    Reset();
}

FFontImportGlyph::~FFontImportGlyph()
{
    Clear();
}

void FFontImportGlyph::Reset()
{
    delete mImage;
    mImage = 0;
    
    mImageX = 0;mImageY = 0;mImageWidth = 0;mImageHeight = 0;
    mImageOffsetX = 0;mImageOffsetY = 0;
    
    mPaddingU = 0;mPaddingD = 0;mPaddingR = 0;mPaddingL = 0;
    mEdgeInsetU = 0;mEdgeInsetD = 0;mEdgeInsetR = 0;mEdgeInsetL = 0;
    
    mStrideX = 0;
    mKernCount = 0;
    
    for(int i=0;i<256;i++)mKern[i] = 0;
}

void FFontImportGlyph::Clear()
{
    mAllowed = true;
    mLoadSuccess = false;
    
    mIndex = -1;
    mChar = -1;
    
    Reset();
}

bool FFontImportGlyph::Valid()
{
    bool aResult = false;
    
    if((mAllowed == true) && (mLoadSuccess == true))
    {
        aResult = true;
    }
    
    return aResult;
}



FFontImportData::FFontImportData()
{
    for(int i=0;i<256;i++)mGlyph[i] = 0;
    
    Clear();
    
    mName = "font";
    mPointSize = 24;
}

FFontImportData::~FFontImportData()
{
    Clear();
}

void FFontImportData::Clear()
{
    for(int i=0;i<256;i++)
    {
        if(mGlyph[i])
        {
            mGlyph[i]->Clear();
            delete mGlyph[i];
            mGlyph[i] = 0;
        }
    }
    
    mRemovedCharacters.Clear();
    mName.Clear();
    
    mPointSize = 0;
    
    mSpacingH = 0;
    mSpacingV = 0;
    
    mCharactersLoadedCount = 0;
    mCharactersRemovedCount = 0;
    
    mImageWidthMax = 0;
    mImageHeightMax = 0;
    
    mInsetMinU = 0;
    mInsetMinR = 0;
    mInsetMinD = 0;
    mInsetMinL = 0;
    
    mBold = false;
    mItalic = false;
    mKerningEnabled = false;
    
    mKernCount = 0;
}

FFontImportGlyph *FFontImportData::GetGlyph(int pIndex)
{
    FFontImportGlyph *aResult = 0;
    if((pIndex >= 0) && (pIndex < 256))
    {
        if(mGlyph[pIndex] == 0)mGlyph[pIndex] = new FFontImportGlyph();
        aResult = mGlyph[pIndex];
        
        if(aResult)
        {
            aResult->mIndex = pIndex;
            aResult->mChar = ((char)(pIndex));
        }
    }
    return aResult;
}



