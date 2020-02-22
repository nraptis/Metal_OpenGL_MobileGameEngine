/*
 *   FImageBundler.cpp
 *   Ninja
 *
 *   Created by Nick Raptis on 4/26/11.
 *   Copyright 2011 Nick Raptis. All rights reserved.
 *
 */

#include "core_includes.h"
#include "FImageBundler.h"
//#include "FXML.hpp"
#include "FJSON.hpp"
#include "FFile.hpp"

FImageBundler gImageBundler;

FImageBundler::FImageBundler() {
    mEdgeBorder = 2;
    mBorder = 2;
    mInset = 0;
    mMultiRez = false;
    mAutoBundle = false;
    mKeepAllAlpha = false;
    mBundleWidth = 0;
    mBundleHeight = 0;
    mBundleScale = 1.0f;
    mSplatArea = 0;
    mSuccess = false;
    mDidLoad = false;
    mRepeatH = false;
}

FImageBundler::~FImageBundler() {
    Clear();
}

void FImageBundler::Clear() {
    FreeList(FImageBundlerSaveNode,mSaveNodeList);
    FreeList(FImageBundlerLoadNode,mLoadNodeList);
    mDidLoad = false;
    mBundleWidth = 0;
    mBundleHeight = 0;
    mSplatArea = 0;
    mSuccess = false;
    mImage.Kill();
}

void FImageBundler::AddImage(const char*pImagePath) {
    FString aPath = pImagePath;
    aPath.RemovePath();
    aPath.RemoveExtension();
    
    //aPath.Replace("_scale_1", "");
    //aPath.Replace("_scale_2", "");
    //aPath.Replace("@1_5x", "");
    //aPath.Replace("_scale_3", "");
    //aPath.Replace("_scale_4", "");
    //aPath.Replace("_scale_2", "");
    //aPath.Replace("@1_5X", "");
    //aPath.Replace("_scale_3", "");
    //aPath.Replace("_scale_4", "");
    

    FImage aImage;
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.png"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.jpg"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.jpeg"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.PNG"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.JPG"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.JPEG"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.png"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.jpg"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.jpeg"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.PNG"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.JPG"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString("_scale_1.JPEG"));

    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".png"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".jpg"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".jpeg"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".PNG"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".JPG"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".JPEG"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".png"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".jpg"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".jpeg"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".PNG"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".JPG"));
    if (aImage. mWidth == 0) aImage.Load(aPath + FString(".JPEG"));

    if (aImage.mWidth == 0) {
        Log("** Image Bundler FAILED [%s] **\n\n", pImagePath);
        return;
    }


    FImage aDoubleRez;
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.png"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.jpg"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.jpeg"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.PNG"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.JPG"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.JPEG"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.png"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.jpg"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.jpeg"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.PNG"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.JPG"));
    if (aDoubleRez. mWidth == 0) aDoubleRez.Load(aPath + FString("_scale_2.JPEG"));
    if (aDoubleRez.mWidth > 0) {
        if(aDoubleRez.mWidth != (aImage.mWidth * 2))Log("***\nWIDTH MISMATCH (%s) Low[%d] Hi[%d]\n***\n", aPath.c(), aImage.mWidth, aDoubleRez.mWidth);
        if(aDoubleRez.mHeight != (aImage.mHeight * 2))Log("***\nHEIGHT MISMATCH (%s) Low[%d] Hi[%d]\n***\n", aPath.c(), aImage.mHeight, aDoubleRez.mHeight);
    }

    FImage aTripleRez;
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.png"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.jpg"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.jpeg"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.PNG"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.JPG"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.JPEG"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.png"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.jpg"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.jpeg"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.PNG"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.JPG"));
    if (aTripleRez. mWidth == 0) aTripleRez.Load(aPath + FString("_scale_3.JPEG"));
    if (aTripleRez.mWidth > 0) {
        if(aTripleRez.mWidth != (aImage.mWidth * 3))Log("***\nWIDTH MISMATCH (%s) Low[%d] Hi[%d]\n***\n", aPath.c(), aImage.mWidth, aTripleRez.mWidth);
        if(aTripleRez.mHeight != (aImage.mHeight * 3))Log("***\nHEIGHT MISMATCH (%s) Low[%d] Hi[%d]\n***\n", aPath.c(), aImage.mHeight, aTripleRez.mHeight);
    }

    FImage aQuadrupleRez;
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.png"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.jpg"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.jpeg"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.PNG"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.JPG"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.JPEG"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.png"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.jpg"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.jpeg"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.PNG"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.JPG"));
    if (aQuadrupleRez. mWidth == 0) aQuadrupleRez.Load(aPath + FString("_scale_4.JPEG"));
    if (aQuadrupleRez.mWidth > 0) {
        if(aQuadrupleRez.mWidth != (aImage.mWidth * 4))Log("***\nWIDTH MISMATCH (%s) Low[%d] Ultra[%d]\n***\n", aPath.c(), aImage.mWidth, aQuadrupleRez.mWidth);
        if(aQuadrupleRez.mHeight != (aImage.mHeight * 4))Log("***\nHEIGHT MISMATCH (%s) Low[%d] Ultra[%d]\n***\n", aPath.c(), aImage.mHeight, aQuadrupleRez.mHeight);
    }
    
    
    FImageBundlerSaveNode *aNode=new FImageBundlerSaveNode();
    AddNode(aNode);
    
    aNode->mName = aPath;
    aNode->mX = 0;
    aNode->mY = 0;
    
    aNode->mOriginalWidth = aImage.mWidth;
    aNode->mOriginalHeight = aImage.mHeight;

    
    if (mRepeatH == true) {
        aNode->mRepeatH = true;
        aNode->mImage = aImage.Clone();
        aNode->mInset = 0;
        aNode->mOffsetX = 0;
        aNode->mOffsetY = 0;
        aNode->mWidth = aNode->mImage->mWidth;
        aNode->mHeight = aNode->mImage->mHeight;
        aNode->mArea = aNode->mWidth * aNode->mHeight;
        if (aDoubleRez.mWidth > 0) {
            aNode->mImageRez2X = aDoubleRez.Clone();
            aNode->mImageRez2X->BufferEdges(mInset * 2);
            aDoubleRez.Kill();
        }
        if (aTripleRez.mWidth > 0) {
            aNode->mImageRez3X = aTripleRez.Clone();
            aNode->mImageRez3X->BufferEdges(mInset * 3);
            aTripleRez.Kill();
        }
        if (aQuadrupleRez.mWidth > 0) {
            aNode->mImageRez4X = aQuadrupleRez.Clone();
            aNode->mImageRez4X->BufferEdges(mInset * 4);
            aQuadrupleRez.Kill();
        }
        return;
    }
    
    
    
    if (mInset > 0) {
        aNode->mImage = aImage.Clone();
        aNode->mImage->BufferEdges(mInset);
        aNode->mInset = mInset;
        aNode->mOffsetX = 0;
        aNode->mOffsetY = 0;
        aNode->mWidth = (aNode->mImage->mWidth);
        aNode->mHeight = (aNode->mImage->mHeight);
        aNode->mArea = aNode->mWidth * aNode->mHeight;
        if (aDoubleRez.mWidth > 0) {
            aNode->mImageRez2X = aDoubleRez.Clone();
            aNode->mImageRez2X->BufferEdges(mInset * 2);
            aDoubleRez.Kill();
        }
        if (aTripleRez.mWidth > 0) {
            aNode->mImageRez3X = aTripleRez.Clone();
            aNode->mImageRez3X->BufferEdges(mInset * 3);
            aTripleRez.Kill();
        }
        if (aQuadrupleRez.mWidth > 0) {
            aNode->mImageRez4X = aQuadrupleRez.Clone();
            aNode->mImageRez4X->BufferEdges(mInset * 4);
            aQuadrupleRez.Kill();
        }
        return;
    }

    int aLeft, aRight, aTop, aBottom, aWidth, aHeight;
    aImage.GetEdges(aLeft,aRight,aTop,aBottom);

    if (mKeepAllAlpha) {
        aWidth = aImage.mWidth;
        aHeight = aImage.mHeight;
        aLeft = 0;
        aRight = (aWidth - 1);
        aTop = 0;
        aBottom = (aHeight - 1);
    }

    aWidth = aRight - aLeft + 1;
    aHeight = aBottom - aTop + 1;

    aNode->mWidth = aWidth;
    aNode->mHeight = aHeight;
    aNode->mArea=aNode->mWidth*aNode->mHeight;
    aNode->mOffsetX = aLeft;
    aNode->mOffsetY = aTop;

    FImage *aNewImage = 0;
    if (mKeepAllAlpha) {
        aNewImage = aImage.Clone();
    } else {
        aNewImage = aImage.Crop(aLeft,aTop,aWidth,aHeight);
    }
    aNode->mImage=aNewImage;

    if (aDoubleRez.mWidth > 0) aNode->mImageRez2X = aDoubleRez.Crop(aLeft*2, aTop*2, aWidth*2, aHeight*2);
    if (aTripleRez.mWidth > 0) aNode->mImageRez3X = aTripleRez.Crop(aLeft*3, aTop*3, aWidth*3, aHeight*3);
    if (aQuadrupleRez.mWidth > 0) aNode->mImageRez4X = aQuadrupleRez.Crop(aLeft*4, aTop*4, aWidth*4, aHeight*4);
}

void FImageBundler::AddNode(FImageBundlerSaveNode *pNode) {
    mSaveNodeList += pNode;
}

/*
void FImageBundler::ExportChunksWithCropData() {
    //FXML aXML;
    FJSON aJSON;
    
    FString aName;
    
    FJSONNode *aRootNode = new FJSONNode();
    aRootNode->mNodeType = JSON_NODE_TYPE_ARRAY;
    
    //FXMLTag *aRootTag = new FXMLTag("image_crops");
    //aXML.mRoot = aRootTag;
    
    FXMLTag *aCropListTag = new FXMLTag("crop_list");
    *aRootTag += aCropListTag;
    
    FString aPrefix = gDirExport;
    EnumList(FImageBundlerSaveNode, aSaveNode, mSaveNodeList) {
        aName = aSaveNode->mName;
        FXMLTag *aCropTag = new FXMLTag("crop");
        *aCropListTag += aCropTag;
        aCropTag->AddParam("offset_x", FString(aSaveNode->mOffsetX).c());
        aCropTag->AddParam("offset_y", FString(aSaveNode->mOffsetY).c());
        aCropTag->AddParam("name", aName.c());
        FString aImagePath = FString(aPrefix + FString("bundle_") + FString(aName) + FString(".png")).c();
        os_exportPNGImage(aSaveNode->mImage->mData, aImagePath.c(), aSaveNode->mImage->mWidth, aSaveNode->mImage->mHeight);
    }
    
    FString aPathXML = FString(aPrefix + FString("image_crop_data") + FString(aName) + FString(".json")).c();
    aXML.Save(aPathXML.c());
}
*/

void FImageBundler::Save(char *pName) {
    
    if (mSaveNodeList.mCount <= 0) {
        Log("Skipping Bundle [%s] (0 Nodes!)\n", pName);
        return;
    }
    
    mSuccess = false;

    int aTryWidth[32];
    int aTryHeight[32];

    aTryWidth[0] = 256;aTryHeight[0] = 256;
    aTryWidth[1] = 256;aTryHeight[1] = 256;
    aTryWidth[2] = 512;aTryHeight[2] = 512;
    aTryWidth[3] = 1024;aTryHeight[3] = 512;
    aTryWidth[4] = 1024;aTryHeight[4] = 1024;
    aTryWidth[5] = 2048;aTryHeight[5] = 1024;
    aTryWidth[6] = 2048;aTryHeight[6] = 2048;
    
    FImageBundlerSaveNode *aNode, *aCheckNode;
    
    int aNodeCount=mSaveNodeList.mCount;
    FImageBundlerSaveNode **aArray = new FImageBundlerSaveNode*[mSaveNodeList.mCount+1];
    for(int i=0;i<aNodeCount;i++)
    {
        aArray[i]=(FImageBundlerSaveNode*)mSaveNodeList.Fetch(i);
    }
    
    int aLowRezCount=0;
    int aDoubleRezCount=0;
    int aTripleRezCount=0;
    int aQuadrupleRezCount=0;
    
    EnumList (FImageBundlerSaveNode, aSaveNode, mSaveNodeList) {
        aLowRezCount++;
        if (aSaveNode->mImageRez2X) aDoubleRezCount++;
        if (aSaveNode->mImageRez3X) aTripleRezCount++;
        if (aSaveNode->mImageRez4X) aQuadrupleRezCount++;
        aSaveNode->mArea=aSaveNode->mWidth*aSaveNode->mHeight;
    }
    
    Log("\n***\nFound %d Images and %d High Rez\n***\n", aLowRezCount, aDoubleRezCount);
    
    for(int i=0;i<aNodeCount;i++)
    {
        aArray[i]=(FImageBundlerSaveNode*)mSaveNodeList.Fetch(i);
        aArray[i]->mArea=aArray[i]->mWidth*aArray[i]->mHeight;
    }
    
    
    //Sort By Area
    int aStart, aCheck;
    for(aStart=1; aStart<aNodeCount;aStart++)
    {
        aNode=aArray[aStart];
        aCheck=aStart-1;
        
        while(aCheck>=0 && aArray[aCheck]->mArea < aNode->mArea)
        {
            aArray[aCheck+1]=aArray[aCheck];
            aCheck--;
        }
        aArray[aCheck+1]=aNode;
    }
    
    int aNodeWidth, aNodeHeight;
    
    bool aNodePlaced;
    bool aIntersects;
    bool aEdgeIntersect;
    
    
    for (int aSplatSizeIndex=0;aSplatSizeIndex<7;aSplatSizeIndex++) {
        mBundleWidth = aTryWidth[aSplatSizeIndex];
        mBundleHeight = aTryHeight[aSplatSizeIndex];

        for (int i=0;i<aNodeCount;i++) {
            aArray[i]->mPlaced=false;
            if (aArray[i]->mRepeatH == true) {
                aArray[i]->mWidth = mBundleWidth;
            }
        }

        for (int i=0;i<aNodeCount;i++) {
            aNode = aArray[i];
            aNodePlaced = false;
            aNodeWidth = aNode->mWidth;
            aNodeHeight = aNode->mHeight;
            
            if (aArray[i]->mRepeatH == true) {
                for (int aY=0;aNodePlaced==false && aY<=mBundleHeight-aNodeHeight;aY+=4) {
                    aIntersects = false;
                    for (int aCheckIndex=i-1;aCheckIndex>=0;aCheckIndex--) {
                        aCheckNode = aArray[aCheckIndex];
                        if (!((aY+aNodeHeight<=(aCheckNode->mY-mBorder))
                              || (aY>=(aCheckNode->mY+aCheckNode->mHeight+mBorder)))) {
                            aIntersects=true;
                        }
                    }
                    if (aIntersects == false) {
                        aNode->mX=0;
                        aNode->mY=aY;
                        aNodePlaced=true;
                    }
                }
            } else {
                for (int aY=0;aNodePlaced==false && aY<=mBundleHeight-aNodeHeight;aY+=4) {
                    for (int aX=0;aNodePlaced==false && aX <= mBundleWidth - aNodeWidth;aX+=4) {
                        aEdgeIntersect = ((aX+aNodeWidth >(mBundleWidth-mEdgeBorder))
                                          || (aY+aNodeHeight>(mBundleHeight-mEdgeBorder))
                                          || (aX<mEdgeBorder)
                                          || (aY<mEdgeBorder));
                        
                        if (aEdgeIntersect == false) {
                            aIntersects = false;
                            for (int aCheckIndex=i-1;aCheckIndex>=0;aCheckIndex--) {
                                aCheckNode = aArray[aCheckIndex];
                                if (!((aX+aNodeWidth<=(aCheckNode->mX-mBorder))
                                     || (aY+aNodeHeight<=(aCheckNode->mY-mBorder))
                                     || (aX>=(aCheckNode->mX+aCheckNode->mWidth+mBorder))
                                     || (aY>=(aCheckNode->mY+aCheckNode->mHeight+mBorder)))) {
                                    aIntersects=true;
                                }
                            }
                            if (aIntersects == false) {
                                aNode->mX=aX;
                                aNode->mY=aY;
                                aNodePlaced=true;
                            }
                        }
                    }
                }
            }
            
            if (aNodePlaced == false) {
                break;
            } else {
                aNode->mPlaced = true;
            }
        }
        
        mSuccess = true;
        
        int aHitCount=0;
        for (int i=0;i<aNodeCount;i++) {
            if (aArray[i]->mPlaced == false) {
                mSuccess = false;
            } else {
                aHitCount++;
            }
        }
        
        if (aNodeCount == 0) {
            mSuccess = false;
        }

        if (mSuccess) {
            mImage.Kill();
            mImage.MakeBlank(mBundleWidth, mBundleHeight);
            
            FImage aImage2X;
            if(aDoubleRezCount > 0)aImage2X.MakeBlank(mBundleWidth * 2, mBundleHeight * 2);

            FImage aImage3X;
            if(aTripleRezCount > 0)aImage3X.MakeBlank(mBundleWidth * 4, mBundleHeight * 4);

            FImage aImage4X;
            if (aQuadrupleRezCount > 0)aImage4X.MakeBlank(mBundleWidth * 4, mBundleHeight * 4);

            for (int i=0;i<aNodeCount;i++) {
                aNode = aArray[i];
                if (true) {
                    mImage.Stamp(aNode->mImage, aNode->mX, aNode->mY);
                }
                if (aNode->mImageRez2X) {
                    aImage2X.Stamp(aNode->mImageRez2X, aNode->mX*2, aNode->mY*2);
                }
                if (aNode->mImageRez2X) {
                    aImage3X.Stamp(aNode->mImageRez3X, aNode->mX*3, aNode->mY*3);
                }
                if (aNode->mImageRez4X) {
                    aImage4X.Stamp(aNode->mImageRez4X, aNode->mX*4, aNode->mY*4);
                }
                
                if ((aNode->mRepeatH == true) && (aNode->mImage != NULL)) {
                    
                    aNode->mWidth = aNode->mImage->mWidth;
                    aNode->mHeight = aNode->mImage->mHeight;
                    
                    int aMoveH = aNode->mImage->mWidth;
                    int aNodeX = aNode->mX;
                    
                    if (aMoveH > 0) {
                        aNodeX = aNode->mX;
                        if (aNode->mImage != NULL) {
                            while (aNodeX < (mImage.mWidth)) {
                                mImage.Stamp(aNode->mImage, aNodeX, aNode->mY);
                                aNodeX += aMoveH;
                            }
                        }
                        
                        aNodeX = aNode->mX * 2;
                        if (aNode->mImageRez2X != NULL) {
                            while (aNodeX < (aImage2X.mWidth)) {
                                aImage2X.Stamp(aNode->mImageRez2X, aNodeX, aNode->mY * 2);
                                aNodeX += aMoveH * 2;
                            }
                        }
                        
                        aNodeX = aNode->mX * 3;
                        if (aNode->mImageRez3X != NULL) {
                            while (aNodeX < (aImage3X.mWidth)) {
                                aImage3X.Stamp(aNode->mImageRez3X, aNodeX, aNode->mY * 3);
                                aNodeX += aMoveH * 3;
                            }
                        }
                        
                        aNodeX = aNode->mX * 4;
                        if (aNode->mImageRez4X != NULL) {
                            while (aNodeX < (aImage4X.mWidth)) {
                                aImage4X.Stamp(aNode->mImageRez4X, aNodeX, aNode->mY * 4);
                                aNodeX += aMoveH * 4;
                            }
                        }
                    }
                }
            }
            
            FJSON aJSON;
            
            FJSONNode *aRootNode = new FJSONNode();
            aRootNode->mNodeType = JSON_NODE_TYPE_DICTIONARY;
            aJSON.mRoot = aRootNode;

            aRootNode->AddDictionaryInt("width", mImage.mWidth);
            aRootNode->AddDictionaryInt("height", mImage.mHeight);
            aRootNode->AddDictionaryInt("border", mBorder);
            aRootNode->AddDictionaryInt("edge", mEdgeBorder);
            
            FJSONNode *aNodeListNode = new FJSONNode();
            aNodeListNode->mNodeType = JSON_NODE_TYPE_ARRAY;
            aRootNode->AddDictionary("node_list", aNodeListNode);
            
            EnumList(FImageBundlerSaveNode, aSaveNode, mSaveNodeList) {
                FJSONNode *aNodeNode = new FJSONNode();
                aNodeNode->mNodeType = JSON_NODE_TYPE_DICTIONARY;
                
                aNodeNode->AddDictionaryString("name", aSaveNode->mName.c());
                aNodeNode->AddDictionaryInt("inset", aSaveNode->mInset);
                aNodeNode->AddDictionaryInt("image_width", aSaveNode->mOriginalWidth);
                aNodeNode->AddDictionaryInt("image_height", aSaveNode->mOriginalHeight);
                aNodeNode->AddDictionaryInt("offset_x", aSaveNode->mOffsetX);
                aNodeNode->AddDictionaryInt("offset_y", aSaveNode->mOffsetY);
                aNodeNode->AddDictionaryInt("rect_x", aSaveNode->mX + aSaveNode->mInset);
                aNodeNode->AddDictionaryInt("rect_y", aSaveNode->mY + aSaveNode->mInset);
                aNodeNode->AddDictionaryInt("rect_width", aSaveNode->mWidth - (aSaveNode->mInset * 2));
                aNodeNode->AddDictionaryInt("rect_height", aSaveNode->mHeight - (aSaveNode->mInset * 2));
                
                aNodeListNode->AddArray(aNodeNode);
            }

            FString aPath = FString(gDirExport + FString("") + FString(pName) + FString("_scale_1.png")).c();
            FString aPath2X = FString(gDirExport + FString("") + FString(pName) + FString("_scale_2.png")).c();
            FString aPath3X = FString(gDirExport + FString("") + FString(pName) + FString("_scale_3.png")).c();
            FString aPath4X = FString(gDirExport + FString("") + FString(pName) + FString("_scale_4.png")).c();

            if (mImage.mWidth >= 32 && mImage.mHeight >= 32) {
                os_exportPNGImage(mImage.mData, aPath.c(), mImage.mWidth, mImage.mHeight);
            }
            if (aImage2X.mWidth >= 32 && aImage2X.mHeight >= 32) {
                os_exportPNGImage(aImage2X.mData, aPath2X.c(), aImage2X.mWidth, aImage2X.mHeight);
            }
            if (aImage3X.mWidth >= 32 && aImage3X.mHeight >= 32) {
                os_exportPNGImage(aImage3X.mData, aPath3X.c(), aImage3X.mWidth, aImage3X.mHeight);
            }
            if (aImage4X.mWidth >= 32 && aImage4X.mHeight >= 32) {
                os_exportPNGImage(aImage4X.mData, aPath4X.c(), aImage4X.mWidth, aImage4X.mHeight);
            }

            aPath = FString(gDirExport + FString("") + FString(pName) + FString("_data.json")).c();
            aJSON.Save(aPath.c());
            
            return;
        }
    }
}

void FImageBundler::StartBundle(const char *pBundleName) {
    if (mAutoBundle) {
        if (mSaveNodeList.mCount > 0) {
            Save(mBundleName);
            Clear();
        }
        mBundleName = pBundleName;
    } else {
        Load(pBundleName);
    }
}

void FImageBundler::EndBundle() {
    if (mAutoBundle) {
        if (mSaveNodeList.mCount > 0) {
            Save(mBundleName);
            Clear();
        }
    } else {
        Clear();
    }
}

void FImageBundler::Load(const char *pFileName, const char *pImageName) {
    Clear();
    mBundleName = FString(pImageName);
    mBundleName.RemoveExtension();
    FImage aImage;
    aImage.Load(pImageName);
    
    //Log("Loaded Image Bundle: (%s) Scale: %d\n", aImage.mFileName.c(), aImage.mScale);
    
    
    if (aImage.mScale == 1) {
        mBundleScale = 1;
    } else if (aImage.mScale == 2) {
        mBundleScale = 2;
    } else if (aImage.mScale == 3) {
        mBundleScale = 3;
    } else if (aImage.mScale == 4) {
        mBundleScale = 4;
    }
    LoadBundle(pFileName);
    if (mLoadNodeList.mCount > 0) {
        mDidLoad = true;
    }
}


void FImageBundler::LoadBundle(const char *pFile) {
    
    FJSON aJSON;
    
    aJSON.Load(pFile);
    
    FJSONNode *aRoot = aJSON.mRoot;
    
    if(aRoot == NULL) { aJSON.Load(mBundleName + FString("_data.json")); aRoot = aJSON.mRoot; }
    if(aRoot == NULL) { aJSON.Load(gDirBundle + mBundleName + FString("_data.json")); aRoot = aJSON.mRoot; }
    if(aRoot == NULL) { aJSON.Load(gDirDocuments + mBundleName + FString("_data.json")); aRoot = aJSON.mRoot; }
    
    if (aRoot != NULL) {
        
        mBundleWidth = aRoot->GetInt("width", 0);
        mBundleHeight = aRoot->GetInt("height", 0);

        if (mBundleScale <= 1) {
            //Nothing
        } else if (mBundleScale == 2) {
            mBundleWidth *= 2;
            mBundleHeight *= 2;
        } else if (mBundleScale == 3) {
            mBundleWidth *= 4;
            mBundleHeight *= 4;
        } else if (mBundleScale == 4) {
            mBundleWidth *= 4;
            mBundleHeight *= 4;
        }



        //1x = 512x512
        //2x = 1024x1024
        //3x = 2048x2048
        //4x = 2048x2048
        
        FJSONNode *aNodeListNode = aRoot->GetArray("node_list");
        
        EnumJSONArray(aNodeListNode, aNodeNode) {
         
            FImageBundlerLoadNode *aNode = new FImageBundlerLoadNode();
            mLoadNodeList += aNode;
            
            aNode->mName = aNodeNode->GetString("name", "");
            aNode->mOriginalWidth = aNodeNode->GetInt("image_width", 0) * mBundleScale;
            aNode->mOriginalHeight = aNodeNode->GetInt("image_height", 0) * mBundleScale;
            aNode->mOffsetX = aNodeNode->GetInt("offset_x", 0) * mBundleScale;
            aNode->mOffsetY = aNodeNode->GetInt("offset_y", 0) * mBundleScale;
            aNode->mX = aNodeNode->GetInt("rect_x", 0) * mBundleScale;
            aNode->mY = aNodeNode->GetInt("rect_y", 0) * mBundleScale;
            aNode->mWidth = aNodeNode->GetInt("rect_width", 0) * mBundleScale;
            aNode->mHeight = aNodeNode->GetInt("rect_height", 0) * mBundleScale;
            
            aNode->mSpriteUStart = (float)(aNode->mX) / (float)mBundleWidth;
            aNode->mSpriteVStart = (float)(aNode->mY) / (float)mBundleHeight;
            aNode->mSpriteUEnd = (float)(aNode->mX + aNode->mWidth) / (float)mBundleWidth;
            aNode->mSpriteVEnd = (float)(aNode->mY + aNode->mHeight) / (float)mBundleHeight;
            aNode->mSpriteLeft = (float)aNode->mOffsetX - ((float)aNode->mOriginalWidth / 2.0f);
            aNode->mSpriteRight = aNode->mSpriteLeft + (float)aNode->mWidth;
            aNode->mSpriteTop = (float)aNode->mOffsetY - ((float)aNode->mOriginalHeight / 2.0f);
            aNode->mSpriteBottom = aNode->mSpriteTop + (float)aNode->mHeight;
            aNode->mSpriteWidth = (float)aNode->mOriginalWidth;
            aNode->mSpriteHeight = (float)aNode->mOriginalHeight;
        }
    }
}

void FImageBundler::Load(char *pName) {
    Clear();
    Load(pName, pName);
}

bool FImageBundler::SliceUpBundle(FImage *pImage, FList *pImageList, int pTolerance) {
    bool aResult = false;
    int aWidth = pImage->mExpandedWidth ;
    int aHeight = pImage->mExpandedHeight;
    int aArea = aWidth * aHeight;
    char *aMaskLinear = new char[aArea];
    char **aMask = new char*[aHeight];
    char *aPtr = aMaskLinear;
    unsigned int *aWriteData = pImage->mData;
    for (int i = 0;i < aArea;i++) {
        if (IMAGE_ALPHA(*aWriteData) <= 4) {
            aMaskLinear[i] = 1;
        } else {
            aMaskLinear[i] = 0;
        }
        aWriteData++;
    }
    for (int i=0;i<aHeight;i++) {
        aMask[i]=aPtr;
        aPtr+=aWidth;
    }
    unsigned int **aData=new unsigned int*[aHeight];
    aWriteData = pImage->mData;
    for (int i=0;i<aHeight;i++) {
        aData[i] = aWriteData;
        aWriteData += aWidth;
    }
    aArea = aWidth * aHeight;
    int aListCount = 0;
    int aStackCount = 0;
    int aLeft, aRight, aTop, aBottom;
    int aXOffset, aYOffset;
    int aNewImageWidth, aNewImageHeight;
    int aX = 0;
    int aY = 0;
    unsigned int **aNewData = new unsigned int *[aHeight];
    short *aXList = new short[aArea];
    short *aYList = new short[aArea];
    short *aXStack = new short[aArea];
    short *aYStack = new short[aArea];
    for (int x=0;x<aWidth;x++) {
        for (int y=0;y<aHeight;y++) {
            if (!aMask[y][x]) {
                aXList[0] = x;
                aYList[0] = y;
                aXStack[0] = x;
                aYStack[0] = y;
                aListCount = 0;
                aStackCount = 1;
                while (aStackCount > 0) {
                    aStackCount--;
                    aX = aXStack[aStackCount];
                    aY = aYStack[aStackCount];
                    if (!aMask[aY][aX]) {
                        aXList[aListCount] = aX;
                        aYList[aListCount] = aY;
                        aListCount++;
                        aMask[aY][aX] = 1;
                        if (aY > 0) {
                            if (!aMask[aY-1][aX]) {
                                aXStack[aStackCount] = aX;
                                aYStack[aStackCount] = aY - 1;
                                aStackCount++;
                            }
                        }
                        if (aX < aWidth - 1) {
                            if(!aMask[aY][aX+1]) {
                                aXStack[aStackCount] = aX + 1;
                                aYStack[aStackCount] = aY;
                                aStackCount++;
                            }
                        }
                        if (aY < aHeight - 1) {
                            if (!aMask[aY+1][aX]) {
                                aXStack[aStackCount] = aX;
                                aYStack[aStackCount] = aY + 1;
                                aStackCount++;
                            }
                        }
                        if (aX > 0) {
                            if (!aMask[aY][aX-1]) {
                                aXStack[aStackCount] = aX - 1;
                                aYStack[aStackCount] = aY;
                                aStackCount++;
                            }
                        }
                    }
                }
                aLeft = x;
                aRight = x;
                aTop = y;
                aBottom = y;
                for (int i = 0;i < aListCount;i++) if (aXList[i] < aLeft) aLeft = aXList[i];
                for (int i = 0;i < aListCount;i++) if (aXList[i] > aRight) aRight = aXList[i];
                for (int i = 0;i < aListCount;i++) if (aYList[i] < aTop) aTop = aYList[i];
                for (int i = 0;i < aListCount;i++) if (aYList[i] > aBottom) aBottom = aYList[i];
                aRight++;
                aBottom++;
                FImage *aImage = new FImage();
                aNewImageWidth = aRight - aLeft;
                aNewImageHeight = aBottom - aTop;
                pImageList->Add(aImage);
                aImage->MakeBlank((aNewImageWidth),(aNewImageHeight));
                aWriteData=aImage->mData;
                for (int i=0;i<aNewImageHeight;i++) {
                    aNewData[i] = aWriteData;
                    aWriteData += aNewImageWidth;
                }
                aXOffset = aLeft;
                aYOffset = aTop;
                for (int i = 0;i < aListCount;i++) {
                    aX = aXList[i];
                    aY = aYList[i];
                    aNewData[aY - aYOffset][aX - aXOffset] = aData[aY][aX];
                }
                aImage->mOffsetX = aLeft;
                aImage->mOffsetY = aTop;
            }
        }
    }
    delete [] aNewData;
    delete [] aMaskLinear;
    delete [] aMask;
    delete [] aXList;
    delete [] aYList;
    delete [] aXStack;
    delete [] aYStack;
    delete [] aData;
    return aResult;
}

bool FImageBundler::FindSequenceCrop(FList *pFileList, int &pCropX, int &pCropY, int &pCropWidth, int &pCropHeight) {
    bool aResult = false;
    pCropX = 0;
    pCropY = 0;
    pCropWidth = -1;
    pCropHeight = -1;
	int aSequenceWidth = -1;
	int aSequenceHeight = -1;
    int aMinInsetTop = -1;
    int aMinInsetRight = -1;
    int aMinInsetBottom = -1;
    int aMinInsetLeft = -1;
    if (pFileList) {
        for (int aIndex=0;aIndex<(pFileList->mCount);aIndex++) {
            FString *aPath = (FString *)(pFileList->Fetch(aIndex));
            if (aPath) {
                FImage aImage;
                aImage.Load(aPath->c());
                if ((aSequenceWidth == -1) && (aImage.mWidth > 0)) {
                    aSequenceWidth = aImage.mWidth;
                    aSequenceHeight = aImage.mHeight;
                }
                if (aImage.mWidth > 0) {
					if (aImage.IsBlank() == false) {
						if ((aImage.mWidth != aSequenceWidth) || (aImage.mHeight != aSequenceHeight)) {
							aImage.Kill();
							aResult = false;
							break;
						} else {
							int aPaddingTop = -1;
							int aPaddingRight = -1;
							int aPaddingBottom = -1;
							int aPaddingLeft = -1;
							aImage.GetEdges(aPaddingLeft, aPaddingRight, aPaddingTop, aPaddingBottom);
							int aInsetTop = aPaddingTop;
							int aInsetRight = ((aImage.mWidth - aPaddingRight));
							int aInsetBottom = ((aImage.mHeight - aPaddingBottom));
							int aInsetLeft = aPaddingLeft;
							if (aMinInsetTop == -1) aMinInsetTop = aInsetTop;
							else if (aInsetTop < aMinInsetTop) aMinInsetTop = aInsetTop;
							if (aMinInsetRight == -1) aMinInsetRight = aInsetRight;
							else if(aInsetRight < aMinInsetRight) aMinInsetRight = aInsetRight;
							if (aMinInsetBottom == -1) aMinInsetBottom = aInsetBottom;
							else if(aInsetBottom < aMinInsetBottom) aMinInsetBottom = aInsetBottom;
							if (aMinInsetLeft == -1) aMinInsetLeft = aInsetLeft;
							else if (aInsetLeft < aMinInsetLeft) aMinInsetLeft = aInsetLeft;
						}
					}
                }
            }
        }
        if (aMinInsetRight < aMinInsetLeft) {
            aMinInsetLeft = aMinInsetRight;
        }
        if (aMinInsetLeft < aMinInsetRight) {
            aMinInsetRight = aMinInsetLeft;
        }
        if (aMinInsetTop < aMinInsetBottom) {
            aMinInsetBottom = aMinInsetTop;
        }
        if (aMinInsetBottom < aMinInsetTop) {
            aMinInsetTop = aMinInsetBottom;
        }
    }
	pCropX = aMinInsetLeft;
	pCropY = aMinInsetTop;
	pCropWidth = aSequenceWidth - (aMinInsetRight + aMinInsetLeft);
	pCropHeight = aSequenceHeight - (aMinInsetTop + aMinInsetBottom);
    return aResult;
}

FImageBundlerLoadNode *FImageBundler::FetchNode(char *pName) {
    FImageBundlerLoadNode *aResult = 0;
        EnumList(FImageBundlerLoadNode, aNode, mLoadNodeList) {
            if (aNode->mName == pName) {
                aResult = aNode;
                break;
            }
        }
    return aResult;
}

FImageBundlerLoadNode::FImageBundlerLoadNode() {
    mX = 0;
    mY = 0;
    mWidth = 0;
    mHeight = 0;
    mOriginalWidth = 0;
    mOriginalHeight = 0;
    mOffsetX = 0;
    mOffsetY = 0;
}

FImageBundlerLoadNode::~FImageBundlerLoadNode() { }

FImageBundlerLoadNode *FImageBundlerLoadNode::Clone() {
    FImageBundlerLoadNode *aResult = new FImageBundlerLoadNode();
    aResult->mX = mX;
    aResult->mY = mY;
    aResult->mWidth = mWidth;
    aResult->mHeight = mHeight;
    aResult->mOffsetX = mOffsetX;
    aResult->mOffsetY = mOffsetY;
    aResult->mOriginalWidth = mOriginalWidth;
    aResult->mOriginalHeight = mOriginalHeight;
    aResult->mSpriteLeft = mSpriteLeft;
    aResult->mSpriteRight = mSpriteRight;
    aResult->mSpriteTop = mSpriteTop;
    aResult->mSpriteBottom = mSpriteBottom;
    aResult->mSpriteUStart = mSpriteUStart;
    aResult->mSpriteUEnd = mSpriteUEnd;
    aResult->mSpriteVStart = mSpriteVStart;
    aResult->mSpriteVEnd = mSpriteVEnd;
    aResult->mSpriteWidth = mSpriteWidth;
    aResult->mSpriteHeight = mSpriteHeight;
    aResult->mName=mName;
    return aResult;
}

FImageBundlerSaveNode::FImageBundlerSaveNode() {
    mX = 0;
    mY = 0;
    mWidth = 0;
    mHeight = 0;
    mOriginalWidth = 0;
    mOriginalHeight = 0;
    mOffsetX = 0;
    mOffsetY = 0;
    mArea = 0;
    mInset = 0;
    mImage = 0;
    mRepeatH = false;
    mImageRez2X = 0;
    mImageRez3X = 0;
    mImageRez4X = 0;
}

FImageBundlerSaveNode::~FImageBundlerSaveNode() {
    delete mImage;
    mImage=0;
}
