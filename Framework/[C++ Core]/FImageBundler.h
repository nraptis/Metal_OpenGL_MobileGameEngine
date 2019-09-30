/*
*  FImageBundler.h
*  Ninja
*
*  Created by Nick Raptis on 4/26/11.
*  Copyright 2011 Nick Raptis. All rights reserved.
*
*/

#ifndef IMAGE_BUNDLER_H
#define IMAGE_BUNDLER_H

#include "FImage.hpp"
#include "FString.hpp"
#include "FList.hpp"

class FImageBundlerSaveNode {
public:
	FImageBundlerSaveNode();
	~FImageBundlerSaveNode();
    
	int					mX;
	int					mY;
	
	int					mWidth;
	int					mHeight;
	
    int					mOffsetX;
	int					mOffsetY;
	
	int					mOriginalWidth;
	int					mOriginalHeight;
    
	int					mArea;
    
    int                 mInset;

    bool                mPlaced;
    
    //TODO:
    FImage              *mImage;
    FImage              *mImageRez2X;
    FImage              *mImageRez3X;
    FImage              *mImageRez4X;

	FString				mName;
};

class FImageBundlerLoadNode {
public:
    
	FImageBundlerLoadNode();
	~FImageBundlerLoadNode();
    
    FImageBundlerLoadNode           *Clone();
    
	int                             mX;
	int                             mY;
    
	int                             mWidth;
	int                             mHeight;
	
    int                             mOffsetX;
	int                             mOffsetY;
	
	int                             mOriginalWidth;
	int                             mOriginalHeight;
    
    float                           mSpriteLeft;
    float                           mSpriteRight;
    float                           mSpriteTop;
    float                           mSpriteBottom;
    
    float                           mSpriteUStart;
    float                           mSpriteUEnd;
    
    float                           mSpriteVStart;
    float                           mSpriteVEnd;
    
    float                           mSpriteWidth;
    float                           mSpriteHeight;
    
	FString                         mName;
};

class FImageBundler
{
    
public:
	
	FImageBundler();
	~FImageBundler();
	
    void                            AddImage(const char*pImagePath);
    void                            AddImage(char*pImagePath) { AddImage((const char*)pImagePath); }
    void                            AddImage(FString pImagePath) { AddImage((const char*)pImagePath.c()); }

	void                            AddNode(FImageBundlerSaveNode *pNode);
	FImageBundlerLoadNode           *FetchNode(char *pName);

    //void                            ExportChunksWithCropData();
    
    FList                           mSaveNodeList;
    FList                           mLoadNodeList;
	
	//The edge border only applies to the edges of the entire splat,
	//which ignore mBorder.
	int                             mEdgeBorder;
	
	//The number of border pixels between each tile on the splat,
	//except for edges, see above.
	int                             mBorder;

	//This is basically for edge bleeding fixers, like a duplicated
	//ring of pixels so opengl can blend tiles more sexy.
	int                             mInset;
    
    bool                            mDidLoad;
    
    bool                            mAutoBundle;
    bool                            mMultiRez;

    bool                            mKeepAllAlpha;
	
    //int                             mImageWidth;
    //int                             mImageHeight;
    
    int                             mBundleWidth;
    int                             mBundleHeight;
    
    int                             mBundleScale;

	int                             mSplatArea;
    
	bool                            mSuccess;
    
    bool                            mScreenCenter;
	
	FImage                          mImage;
    
    void                            Clear();
	
	void                            Save(char *pName);
	inline void                     Save(const char *pName) { Save((char*)pName); }
	inline void                     Save(FString pName) { Save((char*)pName.c()); }
    
	void                            Load(char *pName);
	inline void                     Load(const char *pName){Load((char*)pName);}
	inline void                     Load(FString pName){Load((char*)pName.c());}
    
    void                            Load(const char *pFileName, const char *pImageName);
    void                            LoadBundle(const char *pFile);

    void                            StartBundle(const char *pBundleName);
    void                            EndBundle();
    FString                         mBundleName;

    static bool                     SliceUpBundle(FImage *pImage, FList *pImageList, int pTolerance=3);
    static bool                     FindSequenceCrop(FList *pFileList, int &pCropX, int &pCropY, int &pCropWidth, int &pCropHeight);
};

extern FImageBundler gImageBundler;

#endif



