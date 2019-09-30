
//
//  FFont.h
//  CrazyDartsArc
//
//  Created by Nick Raptis on 10/27/11.
//  Copyright (c) 2011 Nick Raptis. All rights reserved.
//
//

#ifndef FONT_DRAW_H
#define FONT_DRAW_H

#include "FSprite.hpp"

class FFontKern;
class FFontImportGlyph;
class FFontImportData;

class FFont {
public:

    FFont();
    ~FFont();
    
    void                            Kill();
    
    float                           mPointSize;

    float                           mDataScale;
    float                           mSpriteScale;
    float                           mGlobalSqueeze;

    void                            SetSpaceWidth(float pSpaceWidth);
    //float                           mSpaceWidth;

    FString                         mPrefix;
    FSprite                         mCharacterSprite[256];
    
    void                            SetStride(int pCharIndex, float pOffsetX, float pStride);
    
    float                           mCharacterStrideX[256];
    float                           mCharacterOffsetX[256];
    
    void                            SetKern(int pStartCharIndex, int pEndCharIndex, int pKernAmount);
    float                           mKern[256][256];
    
    
    int                             GetCursor(float pTouchX, float pTouchY, const char *pText, float pX, float pY, float pScale);
    float                           LocationOfCursor(int pCursor, const char *pText, float pX, float pY, float pScale);
    

    void                            Draw(const char *pText, float pX, float pY);
    void                            Draw(FString pText, float pX, float pY){Draw((const char *)pText.c(), pX, pY);}

    void                            Draw(const char *pText, float pX, float pY, float pScale);
    void                            Draw(FString pText, float pX, float pY, float pScale) { Draw((const char *)pText.c(), pX, pY, pScale); }
    
    void                            Right(const char *pText, float pX, float pY);
    void                            Right(FString pText, float pX, float pY) { Right((const char *)pText.c(), pX, pY); }

    void                            Right(const char *pText, float pX, float pY, float pScale);
    void                            Right(FString pText, float pX, float pY, float pScale) { Right((const char *)pText.c(), pX, pY, pScale); }
    void                            RightCenter(const char *pText, float pX, float pY, float pScale);
    void                            RightCenter(FString pText, float pX, float pY, float pScale) { RightCenter((const char *)pText.c(), pX, pY, pScale); }


    void                            Left(const char *pText, float pX, float pY, float pScale);
    void                            Left(FString pText, float pX, float pY, float pScale) { Left((const char *)pText.c(), pX, pY, pScale); }
    void                            LeftCenter(const char *pText, float pX, float pY, float pScale);
    void                            LeftCenter(FString pText, float pX, float pY, float pScale) { LeftCenter((const char *)pText.c(), pX, pY, pScale); }
    

    void                            Center(const char *pText, float pX, float pY);
    void                            Center(const char *pText, float pX, float pY, float pScale);

    void                            Center(FString pText, float pX, float pY) { Center((const char *)pText.c(), pX, pY); }
    void                            Center(FString pText, float pX, float pY, float pScale) { Center((const char *)pText.c(), pX, pY, pScale); }


    static FString                  CharToReadable(char c);
    static FString                  CharToFileSafe(char c);
    
    int                             CharIndex(char pChar);
    bool                            CharExists(char pChar);
    
    float                           PointSize(){return (mPointSize * mDataScale);}
    



    
    float                           Width(const char *pText, float pScale);
    float                           Width(const char *pText);


    float                           ScaleForWidth(const char *pText, float pLabelWidth, float pLabelPadding=0.0);

    float                           ScaleForWidth(FString pText, float pLabelWidth, float pLabelPadding=0.0) { return ScaleForWidth((const char *)pText.c(), pLabelWidth, pLabelPadding); }


    void                            ApplyScrunch(float pScrunch);
    void                            ApplyExpand(float pExpand);
    void                            ApplyOffsetX(float pOffset);

    float                           PlotWidth(char *pText, float *pArray);
    float                           PlotWidthCentered(char *pText, float *pArray);
    
    void                            LoadRange(const char *pFilePrefix, char pStart, char pEnd);
    
    void                            LoadAlphaNumeric(const char *pFilePrefix);
    void                            LoadScore(const char *pFilePrefix);
    void                            Load(char *pFilePrefix, char *pCharacters);
    inline void                     Load(const char *pFilePrefix, char *pCharacters){Load((char *)pFilePrefix, (char *)pCharacters);}
    inline void                     Load(char *pFilePrefix, const char *pCharacters){Load((char *)pFilePrefix, (char *)pCharacters);}
    inline void                     Load(const char *pFilePrefix, const char *pCharacters){Load((char *)pFilePrefix, (char *)pCharacters);}
    
    void                            Unload();
    

    //NOTE: Do not use padding radix, this will unevenly space glyphs.
    static void                     BitmapDataBatch(const char *pDataPath, const char *pImagePath,
                                                    const char *pFilePrefixCharImages, const char *pDataFile,
                                                    int pPaddingCrop, int pPaddingGlyph, const char *pRemoveCharacters=0);
    
    static FFontImportData          *BitmapDataImport(const char *pDataPath, const char *pImagePath, int pPaddingCrop, int pPaddingGlyph, const char *pRemoveCharacters=0);
    
    static void                     BitmapDataRemoveCharacters(FFontImportData *pImport, const char *pRemoveCharacters);
    
    static void                     BitmapDataExportGlyphs(FFontImportData *pImport, const char *pName);
    static void                     BitmapDataExportData(FFontImportData *pImport, const char *pName);
    static void                     BitmapDataExportTestStrips(FFontImportData *pImport, const char *pName, int pCount=6);

    void                            LoadNew(const char *pDataFile, const char *pImagePrefix);
    void                            LoadNew(const char *pDataFile, const char *pImagePrefix, const char *pCharacters);

    void                            PrintLoaded();
};

class FFontImportGlyph {
public:
    FFontImportGlyph();
    ~FFontImportGlyph();
    
    void                        Reset();
    void                        Clear();
    
    bool                        Valid();
    
    bool                        mLoadSuccess;
    bool                        mAllowed;
    
    int                         mImageX;
    int                         mImageY;
    
    int                         mImageWidth;
    int                         mImageHeight;
    int                         mImageOffsetX;
    int                         mImageOffsetY;
    
    int                         mStrideX;
    
    int                         mPaddingU;
    int                         mPaddingD;
    int                         mPaddingR;
    int                         mPaddingL;
    
    int                         mEdgeInsetU;
    int                         mEdgeInsetD;
    int                         mEdgeInsetR;
    int                         mEdgeInsetL;
    
    int                         mKernCount;
    
    short                       mKern[256];
    
    int                         mIndex;
    char                        mChar;
    
    FImage                      *mImage;
};

class FFontImportData {
public:
    FFontImportData();
    ~FFontImportData();
    
    void                        Clear();
    
    FFontImportGlyph            *GetGlyph(int pIndex);
    FFontImportGlyph            *mGlyph[256];
    
    FString                     mName;
    
    int                         mCharactersLoadedCount;
    int                         mCharactersRemovedCount;
    
    int                         mPointSize;
    
    int                         mImageWidthMax;
    int                         mImageHeightMax;

    int                         mInsetMinU;
    int                         mInsetMinR;
    int                         mInsetMinD;
    int                         mInsetMinL;
    
    int                         mSpacingH;
    int                         mSpacingV;
    
    bool                        mBold;
    bool                        mItalic;
    
    bool                        mKerningEnabled;
    int                         mKernCount;
    
    FString                     mRemovedCharacters;
};



#endif








