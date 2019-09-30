#include "core_includes.h"
#include "FImage.hpp"
#include "FApp.hpp"
#include "FResource.hpp"

FString cImageLoadHelper;

FImage::FImage() {
    mData = 0;
    mExpandedWidth = 0;
    mExpandedHeight = 0;
    mWidth = 0;
    mHeight = 0;
    mOffsetX = 0;
    mOffsetY = 0;
    mScale = 1;
}

FImage::~FImage() {
    Kill();
}

void FImage::LoadDirect(char *pFile) {
    Kill();
    mFileName = pFile;
    mFileName.RemovePath();
    mScale = 1.0f;
    mData = os_load_image(pFile, mWidth, mHeight);//,mScale);
    mExpandedWidth = mWidth;
    mExpandedHeight = mHeight;
    mOffsetX = 0;
    mOffsetY = 0;
}

void FImage::Load(char *pFile) {
    FString aFile = pFile;
    aFile.RemoveExtension();
    mFileName = aFile;
    
    int aWriteIndex = 0;
    int aWriteIndexHold[3];
    
    bool aDidLoad = false;
    if (aDidLoad == false) {
        FString *aPathDirectory = 0;
        FString *aPathSuffix = 0;
        FString *aPathMutableSuffix = 0;
        FString *aPathExtension = 0;
        
        
        
        for (int aDirectoryIndex = 0; (aDirectoryIndex < gAppBase->mImageLoadDirectoryList.mCount) && (aDidLoad == false); aDirectoryIndex++) {
            aPathDirectory = (FString *)(gAppBase->mImageLoadDirectoryList.Fetch(aDirectoryIndex));
            
            cImageLoadHelper.Reset();
            
            cImageLoadHelper.Append(*aPathDirectory);
            aWriteIndex = cImageLoadHelper.mLength;
            
            //aWriteIndex = cImageLoadBuffer.Write(aPathDirectory->c(), 0, aPathDirectory->mLength);
            
            //aWriteIndex = cImageLoadBuffer.Write(aFile.c(), aWriteIndex, aFile.mLength);
            cImageLoadHelper.Append(aFile);
            aWriteIndex = cImageLoadHelper.mLength;
            
            
            
            aWriteIndexHold[0] = aWriteIndex;
            
            
            for (int aSuffixIndex = 0; (aSuffixIndex < gAppBase->mImageLoadSuffixList.mCount) && (aDidLoad == false); aSuffixIndex++) {
                
                cImageLoadHelper.Truncate(aWriteIndexHold[0]);
                aPathSuffix = (FString *)(gAppBase->mImageLoadSuffixList.Fetch(aSuffixIndex));
                cImageLoadHelper.Append(*aPathSuffix);
                aWriteIndex = cImageLoadHelper.mLength;
                
                //aWriteIndex = cImageLoadBuffer.Write(aPathSuffix->c(), aWriteIndexHold[0], aPathSuffix->mLength);
                
                
                aWriteIndexHold[1] = aWriteIndex;
                
                for (int aMutableSuffixIndex = 0; (aMutableSuffixIndex < gAppBase->mImageLoadMutableSuffixList.mCount) && (aDidLoad == false); aMutableSuffixIndex++) {
                    
                    cImageLoadHelper.Truncate(aWriteIndexHold[1]);
                    aPathMutableSuffix = (FString *)(gAppBase->mImageLoadMutableSuffixList.Fetch(aMutableSuffixIndex));
                    //aWriteIndex = cImageLoadBuffer.Write(aPathMutableSuffix->c(), aWriteIndexHold[1], aPathMutableSuffix->mLength);
                    cImageLoadHelper.Append(*aPathMutableSuffix);
                    aWriteIndex = cImageLoadHelper.mLength;
                    
                    aWriteIndexHold[2] = aWriteIndex;
                    for (int aScaleSuffixIndex = 0;aScaleSuffixIndex < 2; aScaleSuffixIndex++) {
                        
                        if (gAppBase->mImageLoadScaleSuffix.mLength <= 0 && aScaleSuffixIndex > 0) continue;
                        
                        if (aScaleSuffixIndex == 0) {
                            
                            cImageLoadHelper.Truncate(aWriteIndexHold[2]);
                            //aWriteIndex = cImageLoadBuffer.Write(gAppBase->mImageLoadScaleSuffix.c(), aWriteIndexHold[2], gAppBase->mImageLoadScaleSuffix.mLength);
                            cImageLoadHelper.Append(gAppBase->mImageLoadScaleSuffix);
                            aWriteIndex = cImageLoadHelper.mLength;
                            
                            
                        } else {
                            aWriteIndex = aWriteIndexHold[2];
                        }
                        
                        cImageLoadHelper.Truncate(aWriteIndex);
                        cImageLoadHelper.Append('.');
                        aWriteIndex = cImageLoadHelper.mLength;
                        //aWriteIndex = cImageLoadBuffer.Write((const char *)".", aWriteIndex, 1);
                        
                        for (int aExtensionIndex = 0; (aExtensionIndex < gAppBase->mImageLoadExtensionList.mCount) && (aDidLoad == false); aExtensionIndex++)
                        {
                            aPathExtension = (FString *)(gAppBase->mImageLoadExtensionList.Fetch(aExtensionIndex));
                            
                            cImageLoadHelper.Truncate(aWriteIndex);
                            //cImageLoadBuffer.WriteTerminate(aPathExtension->c(), aWriteIndex, aPathExtension->mLength);
                            cImageLoadHelper.Append(*aPathExtension);
                            //aWriteIndex = cImageLoadHelper.mLength;
                            
                            LoadDirect(cImageLoadHelper.c());
                            if ((mWidth > 0) && (mHeight > 0) && (mData != 0)) {
                                if (aScaleSuffixIndex == 0) {
                                    mScale = gImageResolutionScale;
                                }
                                aDidLoad = true;
                            } else {
                                if ((gRes.mTable.mTableCount > 0) && (aDirectoryIndex == 0)) {
                                    const char *aResourcePath = gRes.GetResourcePathImage(cImageLoadHelper.c());
                                    while ((aResourcePath != NULL) && (aDidLoad == false)) {
                                        LoadDirect(aResourcePath);
                                        if((mWidth > 0) && (mHeight > 0) && (mData != 0)) {
                                            if (aScaleSuffixIndex == 0) {
                                                mScale = gImageResolutionScale;
                                            }
                                            aDidLoad = true;
                                        } else {
                                            aResourcePath = gRes.GetNextResourcePath();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (gRes.mTable.mTableCount > 0) {
        const char *aResourcePath = gRes.GetResourcePathImage(aFile.c());
        while ((aResourcePath != NULL) && (aDidLoad == false)) {
            LoadDirect(aResourcePath);
            if((mWidth > 0) && (mHeight > 0) && (mData != NULL)) {
                //Log("Scale {Default} (%d) [%d x %d] => Img[%s]\n", mScale, mWidth, mHeight, aFile.c());
                aDidLoad = true;
            }
            else aResourcePath = gRes.GetNextResourcePath();
        }
    }
}

FTexture *FImage::GetTexture() {
    FTexture *aResult = 0;
    aResult = gTextureCache.GetTexture(mFileName.c());
    return aResult;
}

void FImage::Kill() {
    delete [] mData;
    mData = 0;
    mExpandedWidth = 0;
    mExpandedHeight = 0;
    mWidth = 0;
    mHeight = 0;
    mOffsetX = 0;
    mOffsetY = 0;
    mFileName = "";
}

void FImage::ExportACompressed(char *pFile)
{
    unsigned int *aData=mData;
    unsigned int *aCap=&aData[mExpandedWidth*mExpandedHeight];
    
    FFile aFile;
    while(aData<aCap)
    {
        unsigned char aRead=(unsigned char)(*aData);
        if(aRead==0||aRead==255)
        {
            int aCount=1;
            aData++;
            while(aCount<255 && (aData<aCap) && ((unsigned char)(*aData))==aRead)
            {
                aData++;
                aCount++;
            }
            aFile.WriteChar(aRead);
            aFile.WriteChar(aCount);
            
        }
        else
        {
            aFile.WriteChar(aRead);
            aData++;
        }
    }
    //aFile.Save(gDirDocuments+pFile);
}
void FImage::ExportRGB(char *pFile)
{
    FFile aFile;
    int aArea=mExpandedWidth*mExpandedHeight;
    aFile.WriteChar('B');
    aFile.WriteChar('M');
    int aFileSize = 54 + aArea * 3;
    aFile.WriteInt(aFileSize);
    aFile.WriteInt(0);
    aFile.WriteInt(0x36);
    aFile.WriteInt(0x28);
    aFile.WriteInt(mWidth);
    aFile.WriteInt(mHeight);
    aFile.WriteShort(1);
    //Color Bits
    aFile.WriteShort(24);
    aFile.WriteInt(0);
    aFile.WriteInt(0x10);
    aFile.WriteInt(0x130B);
    aFile.WriteInt(0x130B);
    aFile.WriteInt(0);
    aFile.WriteInt(0);
    for(int aY=mExpandedHeight-1;aY>=0;aY--)
    {
        for(int aX=mExpandedWidth-1;aX>=0;aX--)
        {
            int i=(aY)*mExpandedWidth+(mExpandedWidth-1-aX);
            
            aFile.WriteChar((mData[i]>>16)&0xFF);
            
            aFile.WriteChar((mData[i]>>8)&0xFF);
            aFile.WriteChar((mData[i]>>0)&0xFF);
        }
    }
}

void FImage::ExportA(char *pFile)
{
    FFile aFile;
    int aArea=mExpandedWidth*mExpandedHeight;
    aFile.WriteChar('B');
    aFile.WriteChar('M');
    int aFileSize = 54 + aArea * 3;
    aFile.WriteInt(aFileSize);
    aFile.WriteInt(0);
    aFile.WriteInt(0x36);
    aFile.WriteInt(0x28);
    aFile.WriteInt(mWidth);
    aFile.WriteInt(mHeight);
    aFile.WriteShort(1);
    //Color Bits
    aFile.WriteShort(24);
    aFile.WriteInt(0);
    aFile.WriteInt(0x10);
    aFile.WriteInt(0x130B);
    aFile.WriteInt(0x130B);
    aFile.WriteInt(0);
    aFile.WriteInt(0);
    for(int aY=mExpandedHeight-1;aY>=0;aY--)
    {
        for(int aX=mExpandedWidth-1;aX>=0;aX--)
        {
            int i=(aY)*mExpandedWidth+(mExpandedWidth-1-aX);
            int aAlpha=(mData[i]>>24)&0xFF;
            
            aFile.WriteChar(aAlpha);
            aFile.WriteChar(aAlpha);
            aFile.WriteChar(aAlpha);
            
            //aFile.WriteChar((mData[i]>>24)&0xFF);
        }
    }
    //aFile.Save(gDirDocuments + pFile);
}

void FImage::ApplyGreyscaleAlphaInverse(FImage *pImage)
{
    if(!pImage)return;
    if(mWidth==0 || mHeight==0 || pImage->mWidth!=mWidth || pImage->mHeight!=mHeight)
    {
        return;
    }
    unsigned int *aPaste=mData;
    unsigned int *aCopy=pImage->mData;
    unsigned int *aShelf=&aCopy[mWidth*mHeight];
    while(aCopy<aShelf)
    {
        (*aPaste)&=((0x00FFFFFF)|((*aCopy)<<24));
        aCopy++;
        aPaste++;
    }
}

void FImage::ApplyGreyscaleAlpha(FImage *pImage)
{
    if(!pImage)return;
    if(mWidth==0 || mHeight==0 || pImage->mWidth!=mWidth || pImage->mHeight!=mHeight)
    {
        return;
    }
    unsigned int *aPaste=mData;
    unsigned int *aCopy=pImage->mData;
    unsigned int *aShelf=&aCopy[mWidth*mHeight];
    while(aCopy<aShelf)
    {
        //(*aPaste)&=((0x00FFFFFF)|((*aCopy)<<24));
        (*aPaste)&=((0x00FFFFFF)|((*aCopy)<<24));
        
        aCopy++;
        aPaste++;
    }
}

void FImage::ExportBMP(char *pFile)
{
    FFile aFile;
    
    int aArea=mExpandedWidth*mExpandedHeight;
    //Magic Number 2 bytes
    aFile.WriteChar('B');
    aFile.WriteChar('M');
    
    int aFileSize = 54 + aArea * 4;
    //Size of the BMP file 4 bytes
    aFile.WriteInt(aFileSize);
    
    //4 bytes app specific..
    aFile.WriteInt(0);
    
    //The offset where the bitmap data (pixels) can be found.
    aFile.WriteInt(0x36);
    //The number of bytes in the header (from this point).
    aFile.WriteInt(0x28);
    
    //The width of the bitmap in pixels
    aFile.WriteInt(mExpandedWidth);
    //The height of the bitmap in pixels
    aFile.WriteInt(mExpandedHeight);
    
    //Color Planes
    aFile.WriteShort(1);
    
    //Color Bits
    aFile.WriteShort(32);
    
    //BI_RGB, No compression used
    aFile.WriteInt(0);
    
    aFile.WriteInt(0x10);
    
    
    aFile.WriteInt(0x130B);
    aFile.WriteInt(0x130B);
    
    
    aFile.WriteInt(0);
    aFile.WriteInt(0);
    
    
    for(int aY=mExpandedHeight-1;aY>=0;aY--)
    {
        for(int aX=mExpandedWidth-1;aX>=0;aX--)
        {
            int i=(aY)*mExpandedWidth+(mExpandedWidth-1-aX);
            
            aFile.WriteChar((mData[i]>>16)&0xFF);
            
            aFile.WriteChar((mData[i]>>8)&0xFF);
            aFile.WriteChar((mData[i]>>0)&0xFF);
            
            aFile.WriteChar((mData[i]>>24)&0xFF);
        }
    }
    
    //aFile.Save(gDirDocuments + pFile);
}

void FImage::MakeBlank(int pWidth, int pHeight)
{
    Make(pWidth,pHeight,0);
}

void FImage::Make(int pWidth, int pHeight, int pColor)
{
    if(pWidth<=0||pHeight<=0)
    {
        Kill();
        return;
    }
    if((pWidth!=mExpandedWidth)||(pHeight!=mExpandedHeight))
    {
        Kill();
        mWidth=pWidth;
        mHeight=pHeight;
        mData=new unsigned int[pWidth*pHeight];
    }
    mWidth=pWidth;
    mHeight=pHeight;
    mExpandedWidth=pWidth;
    mExpandedHeight=pHeight;
    mOffsetX=0;
    mOffsetY=0;
    
    unsigned int aColor=pColor;
    unsigned int *aPaste=mData;
    unsigned int *aShelf=mData+(mExpandedWidth*mExpandedHeight);
    while(aPaste<aShelf)*aPaste++=aColor;
    //memset(mData,pColor,((pWidth*pHeight)<<2));
}

unsigned int FImage::GetColor(int x, int y)
{
    x+=mOffsetX;
    y+=mOffsetY;
    int aResult=0;
    int aIndex=x+y*mExpandedWidth;
    if(aIndex>=0&&aIndex<mExpandedWidth*mExpandedHeight)aResult=mData[aIndex];
    return aResult;
}

void FImage::WhiteToAlpha()
{
    unsigned int *aPtr=mData;
    unsigned int *aCap=&mData[mExpandedWidth*mExpandedHeight];
    while(aPtr<aCap)
    {
        *aPtr=(*aPtr<<16)|0x00FFFFFF;
        
        //*aPtr&=0x00FFFFFF;
        //*aPtr|=(*aPtr)<<24;
        //*aPtr|=0x00FFFFFF;
        aPtr++;
    }
}

void FImage::FlipV()
{
    if(mExpandedWidth>0&&mExpandedHeight>0)
    {
        unsigned int **aData=new unsigned int*[mExpandedHeight];
        unsigned int *aPtr=mData;
        int i, n;
        for(n=0;n<mExpandedHeight;n++)
        {
            aData[n]=aPtr;
            aPtr+=mExpandedWidth;
        }
        
        int aTop=0;
        int aBottom=mExpandedHeight-1;
        unsigned int aHold;
        while(aTop<aBottom)
        {
            for(i=0;i<mExpandedWidth;i++)
            {
                aHold=aData[aTop][i];
                aData[aTop][i]=aData[aBottom][i];
                aData[aBottom][i]=aHold;
            }
            aTop++;
            aBottom--;
        }
        delete[]aData;
    }
}

void FImage::GetColorCentroid(int pRed, int pGreen, int pBlue, int &x, int &y, int pTolerance)
{
    x=-1;
    y=-1;
    
    int i=0;
    int n=0;
    
    if(mExpandedWidth>0&&mExpandedHeight>0)
    {
        unsigned int **aData=new unsigned int*[mExpandedHeight];
        unsigned int *aPtr=mData;
        
        for(n=0;n<mExpandedHeight;n++)
        {
            aData[n]=aPtr;
            aPtr+=mExpandedWidth;
        }
        
        int aCount=0;
        
        int aRed, aGreen, aBlue;
        int aRedDiff, aGreenDiff, aBlueDiff;
        
        for(i=0;i<mWidth;i++)
        {
            for(n=0;n<mHeight;n++)
            {
                aRed=(IMAGE_RED(aData[n][i]));
                aGreen=(IMAGE_GREEN(aData[n][i]));
                aBlue=(IMAGE_BLUE(aData[n][i]));
                
                aRedDiff = aRed - pRed;
                if(aRedDiff<0)aRedDiff=-aRedDiff;
                
                aGreenDiff = aGreen - pGreen;
                if(aGreenDiff<0)aGreenDiff=-aGreenDiff;
                
                aBlueDiff = aBlue - pBlue;
                if(aBlueDiff<0)aBlueDiff=-aBlueDiff;
                
                if(aRedDiff <= pTolerance && aGreenDiff <= pTolerance && aBlueDiff <= pTolerance)
                {
                    x+=i;
                    y+=n;
                    aCount++;
                }
            }
        }
        
        if(aCount >=1)
        {
            x /= aCount;
            y /= aCount;
        }
        
        delete[]aData;
    }
}

void FImage::BufferEdges(int pSize)
{
    //Log("FFile Edges! [%d]\n", pSize);
    
    int aX = pSize;
    int aY = pSize;
    int aWidth = mExpandedWidth;
    int aHeight = mExpandedHeight;
    
    ExpandFView(pSize);
    
    
    FixTileBorders(aX, aY, aWidth, aHeight, pSize);
    
    /*
     for(int i=0;i<pSize;i++)
     {
     //FixTileBorders(aX, aY, aWidth, aHeight);
     
     aX --;
     aY --;
     aWidth += 2;
     aHeight += 2;
     }
     
     */
    
}

void FImage::ExpandFView(int pSize)
{
    
    unsigned int *aOldData = mData;
    
    int aOldWidth = mExpandedWidth;
    int aOldHeight = mExpandedHeight;
    
    int aNewWidth = (mExpandedWidth + (pSize * 2));
    int aNewHeight = (mExpandedHeight + (pSize * 2));
    
    mData = 0;
    
    mOffsetX = 0;
    mOffsetY = 0;
    
    mWidth = 0;
    mHeight = 0;
    
    mExpandedWidth = 0;
    mExpandedHeight = 0;
    
    MakeBlank(aNewWidth, aNewHeight);
    
    Stamp(aOldData, pSize, pSize, aOldWidth, aOldHeight);
    
    //Stamp(<#unsigned int *pData#>, <#int x#>, <#int y#>, <#int pWidth#>, <#int pHeight#>)
    
    delete[]aOldData;
}

void FImage::FixTileBorders(int pBorderSize)
{
    
    if(pBorderSize <= 0)return;
    if(pBorderSize > 100)pBorderSize=100;
    
    //int i=0;
    //int n=0;
    
    if(mExpandedWidth>0&&mExpandedHeight>0)
    {
        unsigned int *aOldData = mData;
        
        int aOldWidth=mExpandedWidth;
        int aOldHeight=mExpandedHeight;
        
        int aNewWidth = mExpandedWidth + pBorderSize * 2;
        int aNewHeight = mExpandedHeight + pBorderSize * 2;
        
        MakeBlank(aNewWidth, aNewHeight);
        
        Stamp(aOldData,pBorderSize,pBorderSize,aOldWidth,aOldHeight);
        
        
        //FixTileBorders(pBorderSize, pBorderSize, aOldWidth, aOldHeight);
        FixTileBorders(pBorderSize, pBorderSize, aOldWidth, aOldHeight, pBorderSize);
        
        
    }
}

void FImage::FixTileBorders(int pX, int pY, int pWidth, int pHeight, int pTimes)
{
    //int i=0;
    int n=0;
    
    if(mExpandedWidth>0&&mExpandedHeight>0)
    {
        unsigned int **aData=new unsigned int*[mExpandedHeight];
        unsigned int *aPtr=mData;
        
        int aLeft = pX;
        if(aLeft < 0)aLeft = 0;
        
        int aRight = pX+pWidth-1;
        if(aRight >= mExpandedWidth)aRight = mExpandedWidth-1;
        
        int aTop = pY;
        if(aTop < 0)aTop = 0;
        
        int aBottom = pY+pHeight-1;
        if(aBottom >= mExpandedHeight)aBottom = mExpandedHeight-1;
        
        
        
        
        for(n=0;n<mExpandedHeight;n++)
        {
            aData[n]=aPtr;
            aPtr+=mExpandedWidth;
        }
        
        
        //Fix the top...
        
        /*
         for(int aY = aTop-1;aY>=0;aY--)
         {
         for(int aX = aLeft;aX <= aRight;aX ++)
         {
         aData[aY][aX]=aData[aY+1][aX];
         }
         }
         
         for(int aY = aBottom+1;aY<mExpandedHeight;aY++)
         {
         for(int aX = aLeft;aX <= aRight;aX ++)
         {
         aData[aY][aX]=aData[aY-1][aX];
         }
         }
         
         for(int aX = aLeft-1;aX >=0;aX --)
         {
         for(int aY = aTop;aY<=aBottom;aY++)
         {
         aData[aY][aX]=aData[aY][aX+1];
         }
         }
         
         for(int aX = aRight+1;aX <mExpandedWidth;aX++)
         {
         for(int aY = aTop;aY<=aBottom;aY++)
         {
         aData[aY][aX]=aData[aY][aX-1];
         }
         }
         */
        
        int aLoops = pTimes;
        
        
        //Fix the top...
        for(int aY = aTop-1;(aY>=0) && (aLoops > 0);aY--)
        {
            for(int aX = aLeft;aX <= aRight;aX ++)
            {
                //aData[aY][aX]=aData[aY+1][aX];
                aData[aY][aX]= aData[aY+pHeight][aX];
                
                
                //pWidth
                
            }
            aLoops--;
        }
        
        
        aLoops = pTimes;
        for(int aY = aBottom+1;(aY<mExpandedHeight) && (aLoops > 0);aY++)
        {
            for(int aX = aLeft;aX <= aRight;aX ++)
            {
                //aData[aY][aX]=aData[aY-1][aX];
                aData[aY][aX]=aData[aY-pHeight][aX];
                
                
            }
            aLoops--;
        }
        
        
        aLoops = pTimes;
        for(int aX = aLeft-1;(aX >= 0) && (aLoops > 0);aX--)
        {
            for(int aY = aTop;aY<=aBottom;aY++)
            {
                //aData[aY][aX]=aData[aY][aX+1];
                aData[aY][aX]=aData[aY][aX+pWidth];
                
            }
            aLoops--;
        }
        
        aLoops = pTimes;
        for(int aX = aRight+1;(aX <mExpandedWidth) && (aLoops > 0);aX++)
        {
            for(int aY = aTop;aY<=aBottom;aY++)
            {
                //aData[aY][aX]=aData[aY][aX-1];
                aData[aY][aX]=aData[aY][aX-pWidth];
                
            }
            aLoops--;
        }
        
        
        
        
        
        unsigned int aColor;
        
        
        aColor = aData[aTop][aLeft];//AverageColors(aData[aTop-1][aLeft], aData[aTop][aLeft-1]);
        //for(int i=0;i<aLeft;i++)
        for(int i=(aLeft-1);i>=0;i--)
        {
            for(int n=0;n<aTop;n++)
            {
                //aData[n][i] = aColor;
                aData[n][i] = aData[n + pHeight][i + pWidth];
                
            }
        }
        
        aColor = aData[aTop][aRight];//AverageColors(aData[aTop-1][aRight], aData[aTop][aRight+1]);
        for(int i=aRight+1;i<mExpandedWidth;i++)
        {
            for(int n=0;n<aTop;n++)
            {
                //aData[n][i] = aColor;
                aData[n][i] = aData[n + pHeight][i - pWidth];
                
            }
        }
        
        
        aColor = aData[aBottom][aRight];
        for(int i=aRight+1;i<mExpandedWidth;i++)
        {
            for(int n=aBottom+1;n<mExpandedHeight;n++)
            {
                //aData[n][i] = aColor;
                aData[n][i] = aData[n - pHeight][i - pWidth];
            }
        }
        
        
        aColor = aData[aBottom][aLeft];//AverageColors(aData[aBottom+1][aLeft], aData[aTop][aLeft-1]);
        //for(int i=0;i<aLeft;i++)
        for(int i=(aLeft-1);i>=0;i--)
        {
            for(int n=aBottom+1;n<mExpandedHeight;n++)
            {
                aData[n][i] = aColor;
                aData[n][i] = aData[n - pHeight][i + pWidth];
            }
        }
        
        
        
        delete[]aData;
    }
}

void FImage::ShiftPixels(int x, int y)
{
    x=0;
    y=0;
    
    int i=0;
    int n=0;
    
    if(mExpandedWidth>0&&mExpandedHeight>0)
    {
        unsigned int **aData=new unsigned int*[mExpandedHeight];
        unsigned int *aPtr=mData;
        
        for(n=0;n<mExpandedHeight;n++)
        {
            aData[n]=aPtr;
            aPtr+=mExpandedWidth;
        }
        
        
        for(i=0;i<mWidth;i++)
        {
            for(n=256;n<512;n++)
            {
                aData[n-256][i]=aData[n][i];
                //aData[i][n]=0xFFFF00FF;
            }
        }
        
        
        delete[]aData;
    }
}

void FImage::Pad(int pPaddingLeft, int pPaddingRight, int pPaddingTop, int pPaddingBottom)
{
    PadLeft(pPaddingLeft);
    PadRight(pPaddingRight);
    PadTop(pPaddingTop);
    PadBottom(pPaddingBottom);
}

void FImage::PadLeft(int pSize)
{
    if(pSize == 0)return;
    
    int aNewWidth = (mExpandedWidth + pSize);
    int aNewHeight = (mExpandedHeight);
    
    unsigned int *aOldData = mData;
    int aOldWidth = mExpandedWidth;int aOldHeight = mExpandedHeight;
    mData = 0;mOffsetX = 0;mOffsetY = 0;mWidth = 0;mHeight = 0;mExpandedWidth = 0;mExpandedHeight = 0;
    
    MakeBlank(aNewWidth, aNewHeight);
    Stamp(aOldData, pSize, 0, aOldWidth, aOldHeight);
    
    delete[]aOldData;
}

void FImage::PadRight(int pSize)
{
    if(pSize == 0)return;
    
    int aNewWidth = (mExpandedWidth + pSize);
    int aNewHeight = (mExpandedHeight);
    
    unsigned int *aOldData = mData;
    int aOldWidth = mExpandedWidth;int aOldHeight = mExpandedHeight;
    mData = 0;mOffsetX = 0;mOffsetY = 0;mWidth = 0;mHeight = 0;mExpandedWidth = 0;mExpandedHeight = 0;
    
    MakeBlank(aNewWidth, aNewHeight);
    Stamp(aOldData, 0, 0, aOldWidth, aOldHeight);
    
    delete[]aOldData;
}

void FImage::PadTop(int pSize)
{
    if(pSize == 0)return;
    
    int aNewWidth = (mExpandedWidth);
    int aNewHeight = (mExpandedHeight + pSize);
    
    unsigned int *aOldData = mData;
    int aOldWidth = mExpandedWidth;int aOldHeight = mExpandedHeight;
    mData = 0;mOffsetX = 0;mOffsetY = 0;mWidth = 0;mHeight = 0;mExpandedWidth = 0;mExpandedHeight = 0;
    
    MakeBlank(aNewWidth, aNewHeight);
    Stamp(aOldData, 0, pSize, aOldWidth, aOldHeight);
    
    delete[]aOldData;
}

void FImage::PadBottom(int pSize)
{
    if(pSize == 0)return;
    if(pSize < 0)
    {
        TrimBottom(-(pSize));
        return;
    }
    
    int aNewWidth = (mExpandedWidth);
    int aNewHeight = (mExpandedHeight + pSize);
    
    unsigned int *aOldData = mData;
    int aOldWidth = mExpandedWidth;int aOldHeight = mExpandedHeight;
    mData = 0;mOffsetX = 0;mOffsetY = 0;mWidth = 0;mHeight = 0;mExpandedWidth = 0;mExpandedHeight = 0;
    
    MakeBlank(aNewWidth, aNewHeight);
    Stamp(aOldData, 0, 0, aOldWidth, aOldHeight);
    
    delete[]aOldData;
}

void FImage::TrimLeft(int pSize)
{
    PadLeft(-(pSize));
}

void FImage::TrimRight(int pSize)
{
    PadRight(-(pSize));
}

void FImage::TrimTop(int pSize)
{
    PadTop(-(pSize));
}

void FImage::TrimBottom(int pSize)
{
    PadBottom(-(pSize));
}

FImage *FImage::Resize50Percent()
{
    FImage *aImage = new FImage();
    
    aImage->mFileName = FString(mFileName.c());
    
    if((mExpandedWidth > 1) && (mExpandedHeight > 1))
    {
        int aWidth = mExpandedWidth / 2;
        int aHeight = mExpandedHeight / 2;
        
        if((mExpandedWidth & 1) == 1)aWidth++;
        if((mExpandedHeight & 1) == 1)aHeight++;
        
        
        aImage->MakeBlank(aWidth, aHeight);
        
        unsigned int **aSrc = Get2DGrid();
        unsigned int **aDest = aImage->Get2DGrid();
        
        for(int i=0;i<mExpandedWidth;i+=2)
        {
            for(int n=0;n<mExpandedHeight;n+=2)
            {
                aDest[n / 2][i / 2] = aSrc[n][i];
            }
        }
        
        delete [] aSrc;
        delete [] aDest;
        
        aImage->mExpandedWidth = aWidth;
        aImage->mExpandedHeight = aHeight;
        
        aImage->mWidth = mWidth / 2;
        aImage->mHeight = mHeight / 2;
    }
    
    return aImage;
}

unsigned int **FImage::Get2DGrid()
{
    int n;
    unsigned int **aData=new unsigned int*[mExpandedHeight+1];
    
    unsigned int *aPtr=mData;
    for(n=0;n<mExpandedHeight;n++)
    {
        aData[n]=aPtr;
        aPtr+=mExpandedWidth;
    }
    
    return aData;
}

void FImage::RotateRight()
{
    int n,i;
    if(mExpandedWidth>0&&mExpandedHeight>0)
    {
        unsigned int **aData=new unsigned int*[mExpandedHeight];
        unsigned int *aPtr=mData;
        
        unsigned int **aNew=new unsigned int*[mExpandedWidth];
        unsigned int *aNewData=new unsigned int[mExpandedWidth * mExpandedHeight];
        
        
        for(n=0;n<mExpandedHeight;n++)
        {
            aData[n]=aPtr;
            aPtr+=mExpandedWidth;
        }
        
        aPtr=aNewData;
        for(i=0;i<mExpandedWidth;i++)
        {
            aNew[i]=aPtr;
            aPtr+=mExpandedHeight;
        }
        
        for(i=0;i<mExpandedWidth;i++)
        {
            for(n=0;n<mExpandedHeight;n++)
            {
                aNew[i][mExpandedHeight - n - 1]=aData[n][i];//mExpandedWidth-i-1];
                
                //aNew[mExpandedWidth-i-1][n]=aData[n][i];
            }
        }
        
        delete[]aData;
        delete[]mData;
        delete[]aNew;
        mData=aNewData;
        
        int aWidth=mWidth;
        mWidth=mHeight;
        mHeight=aWidth;
        
        mExpandedWidth = mWidth;
        mExpandedHeight = mHeight;
    }
}



void FImage::RotateLeft()
{
    int n,i;
    if(mExpandedWidth>0&&mExpandedHeight>0)
    {
        unsigned int **aData=new unsigned int*[mExpandedHeight];
        unsigned int *aPtr=mData;
        
        unsigned int **aNew=new unsigned int*[mExpandedWidth];
        unsigned int *aNewData=new unsigned int[mExpandedWidth * mExpandedHeight];
        
        
        for(n=0;n<mExpandedHeight;n++)
        {
            aData[n]=aPtr;
            aPtr+=mExpandedWidth;
        }
        
        aPtr=aNewData;
        for(i=0;i<mExpandedWidth;i++)
        {
            aNew[i]=aPtr;
            aPtr+=mExpandedHeight;
        }
        
        for(i=0;i<mExpandedWidth;i++)
        {
            for(n=0;n<mExpandedHeight;n++)
            {
                aNew[mExpandedWidth-i-1][n]=aData[n][i];
            }
        }
        
        delete[]aData;
        delete[]mData;
        delete[]aNew;
        mData=aNewData;
        
        int aWidth=mWidth;
        mWidth=mHeight;
        mHeight=aWidth;
        
        aWidth=mExpandedWidth;
        mExpandedWidth=mExpandedHeight;
        mExpandedHeight=aWidth;
    }
}

int FImage::GetRight(int pCol)
{
    int aResult = -1;
    if(pCol>=0&&pCol<mHeight)
    {
        unsigned int*aStart=&mData[pCol*mWidth];
        unsigned int*aSeek=aStart;
        unsigned int*aCap=aStart+mWidth;
        
        while (aSeek<aCap)
        {
            if((*aSeek & IMAGE_ALPHA_BITS)!=0)
            {
                aResult=(int)(aSeek-aStart);
            }
            aSeek++;
        }
    }
    return aResult;
}

int FImage::GetLeft(int pCol)
{
    int aResult = -1;
    if(pCol>=0&&pCol<mHeight)
    {
        unsigned int*aStart=&mData[pCol*mWidth];
        unsigned int*aSeek=aStart;
        unsigned int*aCap=aStart+mWidth;
        
        while (aSeek<aCap)
        {
            if(((*aSeek & IMAGE_ALPHA_BITS)!=0)&&(aResult==-1))
            {
                aResult=(int)(aSeek-aStart);
            }
            aSeek++;
        }
        
    }
    return aResult;
}

void FImage::GetEdges(int &pLeft, int &pRight, int &pTop, int &pBottom)
{
    
    int aLeft=0, aRight=0, aTop=0, aBottom=0;
    int aContinue;
    int n,i;
    
    if(mExpandedWidth>0&&mExpandedHeight>0)
    {
        unsigned int **aData=new unsigned int*[mExpandedHeight];
        unsigned int *aPtr=mData;
        for(n=0;n<mExpandedHeight;n++)
        {
            aData[n]=aPtr;
            aPtr+=mExpandedWidth;
        }
        
        //Left
        aContinue=1;
        aLeft=0;
        while(aContinue==1&&aLeft<mExpandedWidth)
        {
            for(n=0;n<mExpandedHeight;n++)
            {
                if((aData[n][aLeft] & IMAGE_ALPHA_BITS)!=0)aContinue=0;
            }
            if(aContinue)aLeft++;
        }
        
        aContinue=1;
        aRight=mExpandedWidth-1;
        while(aContinue==1&&aRight>=0)
        {
            for(n=0;n<mExpandedHeight;n++)
            {
                if((aData[n][aRight] & IMAGE_ALPHA_BITS)!=0)aContinue=0;
            }
            if(aContinue)aRight--;
        }
        
        aContinue=1;
        aTop=0;
        while(aContinue==1&&aTop<mExpandedHeight)
        {
            for(i=0;i<mExpandedWidth;i++)
            {
                if((aData[aTop][i] & IMAGE_ALPHA_BITS)!=0)aContinue=0;
            }
            if(aContinue)aTop++;
        }
        
        aContinue=1;
        aBottom=mExpandedHeight-1;
        while(aContinue==1&&aBottom>=0)
        {
            for(i=0;i<mExpandedWidth;i++)
            {
                if((aData[aBottom][i] & IMAGE_ALPHA_BITS)!=0)aContinue=0;
            }
            if(aContinue)aBottom--;
        }
        
        delete[]aData;
    }
    
    if(aLeft>=aRight||aTop>aBottom)
    {
        pLeft=0;
        pRight=0;
        pTop=0;
        pBottom=0;
    }
    else
    {
        pLeft=aLeft+mOffsetX;
        pRight=aRight+mOffsetX;
        pTop=aTop+mOffsetY;
        pBottom=aBottom+mOffsetY;
    }
}

void FImage::Stroke(unsigned int pColor, unsigned int pAlpha, int pSize, int pFade)
{
    if(mExpandedWidth<=0||mExpandedHeight<=0||pSize<=0)return;
    
    unsigned int **aData=new unsigned int*[mExpandedHeight];
    unsigned int **aVisited=new unsigned int*[mExpandedHeight];
    unsigned int *aVisitedPtr=new unsigned int[(mExpandedWidth)*(mExpandedHeight)];
    unsigned int *aPtr=mData;
    
    int i, n, aX, aY;
    int aSize=pSize;
    int aSizeWeight=aSize;
    
    for(n=0;n<mExpandedHeight;n++)
    {
        //aVisited[n]=aVisitedPtr;
        aData[n]=aPtr;
        
        aPtr+=mExpandedWidth;
        //aVisitedPtr+=mExpandedWidth;
    }
    
    aPtr=aVisitedPtr;
    for(n=0;n<mExpandedHeight;n++)
    {
        aVisited[n]=aPtr;
        //aData[n]=aPtr;
        
        aPtr+=mExpandedWidth;
        //aVisitedPtr+=mExpandedWidth;
    }
    
    unsigned int aAlpha=pAlpha;
    IMAGE_ALPHA_SHIFT(aAlpha);
    
    for(i=0;i<mExpandedWidth;i++)
    {
        for(n=0;n<mExpandedHeight;n++)
        {
            aVisited[n][i]=0xFFFFFFFF;
        }
    }
    
    for(i=0;i<mExpandedWidth;i++)
    {
        for(n=0;n<mExpandedHeight;n++)
        {
            if((aData[n][i]&IMAGE_ALPHA_BITS)>aAlpha)
            {
                if(n>0)
                {
                    if((aData[n-1][i]&IMAGE_ALPHA_BITS)<=aAlpha)
                    {
                        aVisited[n-1][i]=0;
                    }
                }
                if(n<mExpandedHeight-1)
                {
                    if((aData[n+1][i]&IMAGE_ALPHA_BITS)<=aAlpha)
                    {
                        aVisited[n+1][i]=0;
                    }
                }
                if(i>0)
                {
                    if((aData[n][i-1]&IMAGE_ALPHA_BITS)<=aAlpha)
                    {
                        aVisited[n][i-1]=0;
                    }
                }
                if(i<mExpandedWidth-1)
                {
                    if((aData[n][i+1]&IMAGE_ALPHA_BITS)<=aAlpha)
                    {
                        aVisited[n][i+1]=0;
                    }
                }
            }
        }
    }
    
    int aXStart, aXEnd, aYStart, aYEnd, aWeightX, aWeightY, aWeight;
    
    for(i=0;i<mExpandedWidth;i++)
    {
        for(n=0;n<mExpandedHeight;n++)
        {
            if(aVisited[n][i]==0)
            {
                aXStart=i-aSize;
                if(aXStart<0)aXStart=0;
                
                aYStart=n-aSize;
                if(aYStart<0)aYStart=0;
                
                aXEnd=i+aSize;
                if(aXEnd>=mExpandedWidth)aXEnd=mExpandedWidth-1;
                
                aYEnd=n+aSize;
                if(aYEnd>=mExpandedHeight)aYEnd=mExpandedHeight-1;
                
                for(aX=aXStart;aX<=aXEnd;aX++)
                {
                    for(aY=aYStart;aY<=aYEnd;aY++)
                    {
                        aWeightX=aX-i;
                        aWeightY=aY-n;
                        if(aWeightX<0)aWeightX=-aWeightX;
                        if(aWeightY<0)aWeightY=-aWeightY;
                        aWeight=aWeightX+aWeightY;
                        
                        if((aWeight<=aSizeWeight)&&((aData[aY][aX]&IMAGE_ALPHA_BITS)<=aAlpha)&&(aWeight<aVisited[aY][aX]))
                        {
                            aVisited[aY][aX]=aWeight;
                        }
                    }
                }
            }
        }
    }
    
    for(n=0;n<mExpandedHeight;n++)
    {
        for(i=0;i<mExpandedWidth;i++)
        {
            if(aVisited[n][i]!=0xFFFFFFFF)
            {
                aData[n][i]=pColor;
            }
        }
    }
    delete[]aData;
    delete[]aVisited;
    delete[]aVisitedPtr;
}

void FImage::MakePowerOf2()
{
    if(mWidth<=0||mHeight<=0)return;
    
    if(((mExpandedWidth&(mExpandedWidth-1))==0)&&((mExpandedHeight&(mExpandedHeight-1))==0))
    {
        return;
    }
    
    int aPower=1;
    int aHPower=0;
    int aVPower=0;
    
    while(aHPower==0||aVPower==0)
    {
        if(aHPower==0&&aPower>=mExpandedWidth)aHPower=aPower;
        if(aVPower==0&&aPower>=mExpandedHeight)aVPower=aPower;
        aPower*=2;
    }
    
    int aOldWidth=mWidth;
    int aOldHeight=mHeight;
    
    unsigned int *aOldData=mData;
    
    mExpandedWidth=0;
    mExpandedHeight=0;
    mData=0;
    
    MakeBlank(aHPower, aVPower);
    
    
    
    mExpandedWidth=aHPower;
    mExpandedHeight=aVPower;
    
    //float aOffsetX=(mExpandedWidth-aOldWidth)/2;
    //float aOffsetY=(mExpandedHeight-aOldHeight)/2;
    
    mOffsetX=(mExpandedWidth-aOldWidth)/2;
    mOffsetY=(mExpandedHeight-aOldHeight)/2;
    
    //mOffsetX = 0;
    //mOffsetY = 0;
    
    mWidth=aOldWidth;
    mHeight=aOldHeight;
    
    Stamp(aOldData, mOffsetX, mOffsetY, mWidth, mHeight);
    
    delete[]aOldData;
    
    //mOffsetX = aOffsetX;
    //mOffsetY = aOffsetY;
}



void FImage::Stamp(unsigned int *pData, int x, int y, int pWidth, int pHeight)
{
    //Log("Stamping{%d} (x=%d, y=%d, w=%d, h=%d) (realW=%d realH=%d)\n", pData,x,y,pWidth,pHeight,mExpandedWidth,mExpandedHeight);
    
    if(!pData||x>=mExpandedWidth||y>=mExpandedHeight)return;
    
    int aWidth=pWidth;
    int aHeight=pHeight;
    
    int aStampWidth=aWidth;
    unsigned int *aSrc=pData;
    unsigned int *aLastSrc;
    
    if(x<0)
    {
        aWidth+=x;
        aSrc-=x;
        x=0;
    }
    if(y<0)
    {
        aHeight+=y;
        aSrc-=y*aStampWidth;
        y=0;
    }
    if(aWidth<1||aHeight<1)return;
    if(x+aWidth>mExpandedWidth)aWidth=mExpandedWidth-x;
    if(y+aHeight>mExpandedHeight)aHeight=mExpandedHeight-y;
    unsigned int *aPtr=&mData[y*mExpandedWidth+x];
    unsigned int *aCap;
    unsigned int aCount=aHeight;
    unsigned int aSkipAhead=(mExpandedWidth-aWidth);
    while(aCount>0)
    {
        aCap=aPtr+aWidth;
        aLastSrc=aSrc;
        while(aPtr<aCap)*aPtr++=*aSrc++;
        aSrc=aLastSrc+aStampWidth;
        aPtr+=aSkipAhead;
        aCount--;
    }
}

void FImage::Stamp(FImage *pImage, int x, int y, int pImageX, int pImageY, int pImageWidth, int pImageHeight)
{
    //Olschool Stamping...
    
    if(!pImage)return;
    
    int aOffsetX = pImage->mOffsetX;
    int aOffsetY = pImage->mOffsetY;
    
    if(x<0)
    {
        pImageWidth+=x;
        //TODO:
        //pImageX-=x;
        x=0;
    }
    
    if(y<0)
    {
        pImageHeight+=y;
        //TODO:
        //pImageY-=y;
        y=0;
    }
    
    if(pImageX<0)
    {
        pImageWidth+=pImageX;
        
        //? #2 not sire
        //aOffsetX += pImageX;
        //aOffsetY += pImageY;
        
        pImageX=0;
    }
    if(pImageY<0)
    {
        pImageHeight+=pImageY;
        pImageY=0;
    }
    
    
    if(pImageX>pImage->mWidth)return;
    if(pImageY>pImage->mHeight)return;
    
    if(pImageX+pImageWidth>pImage->mExpandedWidth)
    {
        pImageWidth -= (pImageX+pImageWidth) - pImage->mExpandedWidth;
    }
    if(pImageY+pImageHeight>pImage->mExpandedHeight)
    {
        pImageHeight -= (pImageY+pImageHeight) - pImage->mExpandedHeight;
    }
    
    
    
    if(x+pImageWidth>mWidth)
    {
        pImageWidth-=(x+pImageWidth)-(mWidth);
    }
    if(y+pImageHeight>mHeight)
    {
        pImageHeight-=(y+pImageHeight)-(mHeight);
    }
    
    
    if(pImageWidth<1 || pImageHeight<1)return;
    
    //Why would we ever wanna stamp after we bind?..
    x+=mOffsetX;
    y+=mOffsetY;
    
    pImageX+=aOffsetX;//pImage->mOffsetX;
    pImageY+=aOffsetY;//pImage->mOffsetY;
    
    //Now we stamp one line at a time...
    unsigned int *aCopy=&pImage->mData[pImageY*pImage->mExpandedWidth+pImageX];
    unsigned int aCopySkip=pImage->mExpandedWidth-pImageWidth;
    
    unsigned int *aPaste=&mData[y*mExpandedWidth+x];
    unsigned int aPasteSkip=mExpandedWidth-pImageWidth;
    
    unsigned int *aCap;
    
    unsigned int aLines=pImageHeight;
    while(aLines)
    {
        aCap=aCopy+pImageWidth;
        while(aCopy<aCap)
        {
            while(aCopy<aCap)
            {
                /*
                 int aAlpha = IMAGE_ALPHA(*aCopy);
                 
                 if(aAlpha <= 0)
                 {
                 *aPaste++=IMAGE_RGBA(gRand.Get(40), gRand.Get(16), gRand.Get(16), 80 + gRand.Get(40));
                 aCopy++;
                 }
                 else
                 {
                 *aPaste++=*aCopy++;
                 }
                 */
                
                //Log("Pasting :%x\n", *aCopy);
                *aPaste++=*aCopy++;
            }
            aCopy+=aCopySkip;
            aPaste+=aPasteSkip;
        }
        aLines--;
    }
    
    return;
}

void FImage::StampBlend(FImage *pImage,int x, int y, int pImageX, int pImageY, int pImageWidth, int pImageHeight) {
    if (!pImage) { return; }
    if (x < 0) {
        pImageWidth += x;
        pImageX -= x;
        x = 0;
    }
    if (y < 0) {
        pImageHeight+=y;
        pImageY-=y;
        y=0;
    }
    if (pImageX < 0) {
        pImageWidth+=pImageX;
        pImageX=0;
    }
    if (pImageY < 0) {
        pImageHeight+=pImageY;
        pImageY=0;
    }
    if (pImageX > pImage->mWidth) { return; }
    if (pImageY > pImage->mHeight) { return; }
    if (pImageX + pImageWidth > pImage->mWidth) {
        pImageWidth -= (pImageX + pImageWidth) - pImage->mWidth;
    }
    if (pImageY + pImageHeight > pImage->mHeight) {
        pImageHeight -= (pImageY + pImageHeight) - pImage->mHeight;
    }
    if (x + pImageWidth > mWidth) {
        pImageWidth -= (x + pImageWidth) - mWidth;
    }
    if (y + pImageHeight > mHeight) {
        pImageHeight -= (y + pImageHeight) - mHeight;
    }
    if (pImageWidth<1 || pImageHeight<1) { return; }
    x += mOffsetX;
    y += mOffsetY;

    pImageX += pImage->mOffsetX;
    pImageY += pImage->mOffsetY;

    //Now we stamp one line at a time...
    unsigned int *aCopy=&pImage->mData[pImageY*pImage->mExpandedWidth+pImageX];
    unsigned int aCopySkip=pImage->mExpandedWidth-pImageWidth;
    unsigned int *aPaste=&mData[y*mExpandedWidth+x];
    unsigned int aPasteSkip=mExpandedWidth-pImageWidth;
    unsigned int *aCap;
    unsigned int aLines=pImageHeight;
    while (aLines) {
        aCap = aCopy + pImageWidth;
        while (aCopy < aCap) {
            while (aCopy < aCap) {
                unsigned int aAlphaOriginal = IMAGE_ALPHA(*aPaste); //204
                unsigned int aAlphaOver = IMAGE_ALPHA(*aCopy); //51
                unsigned int aAlphaOverInverse = 255 - aAlphaOver;
                unsigned int aFinalAlpha = aAlphaOver + (aAlphaOverInverse * aAlphaOriginal) / 255;
                unsigned int aFinalRed = ((IMAGE_RED(*aCopy) * aAlphaOver) + ((aAlphaOverInverse * aAlphaOriginal * IMAGE_RED(*aPaste))/255))/255;
                unsigned int aFinalGreen = ((IMAGE_GREEN(*aCopy) * aAlphaOver) + ((aAlphaOverInverse * aAlphaOriginal * IMAGE_GREEN(*aPaste))/255))/255;
                unsigned int aFinalBlue = ((IMAGE_BLUE(*aCopy) * aAlphaOver) + ((aAlphaOverInverse * aAlphaOriginal * IMAGE_BLUE(*aPaste))/255))/255;
                *aPaste = ((aFinalAlpha << 24) | (aFinalRed << 0) | (aFinalBlue << 16) | (aFinalGreen << 8));
                aPaste++;
                aCopy++;
            }
            aCopy+=aCopySkip;
            aPaste+=aPasteSkip;
        }
        aLines--;
    }
}

FImage *FImage::Clone() {
    return Crop(0, 0, mExpandedWidth, mExpandedHeight);
}

FImage *FImage::Crop(int x, int y, int pWidth, int pHeight) {
    FImage *aResult=new FImage();
    aResult->mFileName = mFileName;
    
    if(pWidth <= 0 || pHeight <= 0)return aResult;
    if(pWidth > 4096 || pHeight > 4096)return aResult;
    
    aResult->Make(pWidth, pHeight, IMAGE_RGBA(255, 255, 255, 0));
    
    if(mExpandedWidth > 0 && mExpandedHeight > 0)
    {
        int aStartCopyX = x;//x;
        int aStartCopyY = y;//y;
        
        int aStartPasteX = 0; // (mExpandedWidth - pWidth) / 2;
        int aStartPasteY = 0; // (mExpandedHeight - pHeight) / 2;
        
        if(aStartCopyX < 0)
        {
            pWidth += aStartCopyX;
            aStartPasteX -= aStartCopyX;
            aStartCopyX =0 ;
        }
        
        if(aStartCopyY < 0)
        {
            pHeight += aStartCopyY;
            aStartPasteY -= aStartCopyY;
            aStartCopyY = 0;
        }
        
        if(aStartPasteX < 0)
        {
            pWidth += aStartPasteX;
            aStartCopyX -= aStartPasteX;
            aStartPasteX = 0;
        }
        
        if(aStartPasteY < 0)
        {
            pHeight += aStartPasteY;
            aStartCopyY -= aStartPasteY;
            aStartPasteY = 0;
        }
        
        if(aStartCopyX < mExpandedWidth && aStartCopyY < mExpandedHeight)
        {
            int aEndCopyX = aStartCopyX + pWidth;
            int aEndCopyY = aStartCopyY + pHeight;
            
            int aEndPasteX = aStartPasteX + pWidth;
            int aEndPasteY = aStartPasteY + pHeight;
            
            int aFix;
            
            if(aEndCopyY > mExpandedHeight)
            {
                aFix = (aEndCopyY - mExpandedHeight);
                aEndPasteY -= aFix;
                aEndCopyY -= aFix;
            }
            
            if(aEndPasteY > pHeight)
            {
                aFix = (aEndPasteY - pHeight);
                aEndPasteY -= aFix;
                aEndCopyY -= aFix;
            }
            
            if(aEndCopyX > mExpandedWidth)
            {
                aFix = (aEndCopyX - mExpandedWidth);
                aEndPasteX -= aFix;
                aEndCopyX -= aFix;
            }
            if(aEndPasteX > pWidth)
            {
                aFix = (aEndPasteX - pWidth);
                aEndPasteX -= aFix;
                aEndCopyX -= aFix;
            }
            
            if(aStartCopyX < aEndCopyX && aStartCopyY < aEndCopyY)
            {
                if(aStartPasteX < aEndPasteX && aStartPasteY  < aEndPasteY)
                {
                    unsigned int *aPtr;
                    unsigned int **aData=new unsigned int*[mExpandedHeight];
                    
                    aPtr=mData;
                    
                    for(int n=0;n<mExpandedHeight;n++)
                    {
                        aData[n]=aPtr;
                        aPtr+=mExpandedWidth;
                    }
                    
                    unsigned int **aNewData=new unsigned int*[aResult->mExpandedHeight];
                    aPtr=aResult->mData;
                    for(int n=0;n<aResult->mExpandedHeight;n++)
                    {
                        aNewData[n]=aPtr;
                        aPtr+=aResult->mExpandedWidth;
                    }
                    
                    for(int aCopyX=aStartCopyX, aPasteX=aStartPasteX;aCopyX<aEndCopyX;)
                    {
                        for(int aCopyY=aStartCopyY, aPasteY=aStartPasteY;aCopyY<aEndCopyY;)
                        {
                            aNewData[aPasteY][aPasteX]=aData[aCopyY][aCopyX];
                            
                            aCopyY++;
                            aPasteY++;
                        }
                        
                        aCopyX++;
                        aPasteX++;
                    }
                    delete[]aData;
                    delete[]aNewData;
                }
                else
                {
                    Log("Copy Indices Out Of Bounds! Copy[%d %d %d %d] Paste[%d %d %d %d]\n", aStartCopyX, aStartCopyY, aEndCopyX, aEndCopyY, aStartPasteX, aStartPasteY, aEndPasteX, aEndPasteY);
                }
            }
            else
            {
                Log("Copy Indices Out Of Bounds! Copy[%d %d %d %d] Paste[%d %d %d %d]\n", aStartCopyX, aStartCopyY, aEndCopyX, aEndCopyY, aStartPasteX, aStartPasteY, aEndPasteX, aEndPasteY);
            }
        }
    }
    return aResult;
}

void FImage::StampBlend(FImage *pImage, int x, int y) {
    if (pImage) {
        StampBlend(pImage, x, y, 0, 0, pImage->mWidth,pImage->mHeight);
    }
}

void FImage::Stamp(FImage *pImage, int x, int y) {
    if (pImage) {
        Stamp(pImage, x, y, 0, 0, pImage->mExpandedWidth, pImage->mExpandedHeight);
    }
}

void FImage::Replace(unsigned int pOldColor, unsigned int pNewColor) {
    unsigned int *aSearch=mData;
    unsigned int *aCap = &mData[mExpandedWidth*mExpandedHeight];
    while (aSearch < aCap) {
        if (*aSearch==pOldColor) {
            *aSearch = pNewColor;
        }
        aSearch++;
    }
}

void FImage::ReplaceAlpha(unsigned int pOldAlpha, unsigned int pNewColor)
{
    unsigned int *aSearch=mData;
    unsigned int *aCap=&mData[mExpandedWidth*mExpandedHeight];
    while(aSearch<aCap)
    {
        if(IMAGE_ALPHA(*aSearch)==pOldAlpha)
        {
            *aSearch=pNewColor;
        }
        aSearch++;
        
    }
}

void FImage::Invert() {
    unsigned int aRed,aGreen,aBlue,aAlpha;
    unsigned int *aSearch=mData;
    unsigned int *aCap=&mData[mExpandedWidth*mExpandedHeight];
    while (aSearch<aCap) {
        aRed = 255-IMAGE_RED(*aSearch);
        aGreen = 255-IMAGE_GREEN(*aSearch);
        aBlue = 255-IMAGE_BLUE(*aSearch);
        aAlpha = IMAGE_ALPHA(*aSearch);
        *aSearch = (IMAGE_RED_SHIFT(aRed) | IMAGE_GREEN_SHIFT(aGreen) | IMAGE_BLUE_SHIFT(aBlue) | IMAGE_ALPHA_SHIFT(aAlpha));
        aSearch++;
    }
}

void FImage::SubtractRGBA() {
    int aSubAmount=32;
    unsigned int aRed,aGreen,aBlue,aAlpha;
    unsigned int *aSearch=mData;
    unsigned int *aCap=&mData[mExpandedWidth*mExpandedHeight];
    while (aSearch<aCap) {
        aRed=IMAGE_RED(*aSearch);
        aGreen=IMAGE_GREEN(*aSearch);
        aBlue=IMAGE_BLUE(*aSearch);
        aAlpha=IMAGE_ALPHA(*aSearch);
        
        //if(aRed>=aSubAmount)aRed-=aSubAmount;
        //else aRed=0;
        //if(aGreen>=aSubAmount)aGreen-=aSubAmount;
        //else aGreen=0;
        //if(aBlue>=aSubAmount)aBlue-=aSubAmount;
        //else aBlue=0;
        
        if(aAlpha>=aSubAmount)aAlpha-=aSubAmount;
        else aAlpha=0;
        
        *aSearch=(IMAGE_RED_SHIFT(aRed) | IMAGE_GREEN_SHIFT(aGreen) | IMAGE_BLUE_SHIFT(aBlue) | IMAGE_ALPHA_SHIFT(aAlpha));
        aSearch++;
        
    }
}

void FImage::DivideRGBA() {
    unsigned int aRed,aGreen,aBlue,aAlpha;
    unsigned int *aSearch=mData;
    unsigned int *aCap=&mData[mExpandedWidth*mExpandedHeight];
    while (aSearch<aCap) {
        aRed=IMAGE_RED(*aSearch)>>1;
        aGreen=IMAGE_GREEN(*aSearch)>>1;
        aBlue=IMAGE_BLUE(*aSearch)>>1;
        aAlpha=IMAGE_ALPHA(*aSearch)>>1;
        *aSearch=(IMAGE_RED_SHIFT(aRed) | IMAGE_GREEN_SHIFT(aGreen) | IMAGE_BLUE_SHIFT(aBlue) | IMAGE_ALPHA_SHIFT(aAlpha));
        aSearch++;
    }
}


void FImage::SubtractAlpha(int pAmount) {
    unsigned int *aSearch=mData;
    unsigned int *aCap=&mData[mExpandedWidth*mExpandedHeight];
    int aAlpha;
    while (aSearch<aCap) {
        aAlpha=((int)IMAGE_ALPHA(*aSearch)) - pAmount;
        if(aAlpha<0)aAlpha=0;
        *aSearch = (*aSearch & 0x00FFFFFF) | IMAGE_ALPHA_SHIFT(aAlpha);
        aSearch++;
    }
}


void FImage::SetPixel(int x, int y, unsigned int pRed, unsigned int pGreen, unsigned int pBlue, unsigned int pAlpha)
{
    SetPixel(x, y,(pRed<<24)|(pGreen<<16)|(pBlue<<8)|(pAlpha));
}

void FImage::SetPixel(int x, int y, unsigned int pColor) {
    if (x < 0 || x >= mExpandedWidth || y < 0 || y >= mExpandedHeight) { return; }
    mData[y * mExpandedWidth + x] = pColor;
}





void FImage::SetPixelBlendMax(int x, int y, unsigned int pColor)
{
    if(x<0||x>=mExpandedWidth||
       y<0||y>=mExpandedHeight)return;
    
    unsigned int aNewRed=IMAGE_RED(pColor);
    unsigned int aNewGreen=IMAGE_GREEN(pColor);
    unsigned int aNewBlue=IMAGE_BLUE(pColor);
    unsigned int aNewAlpha=IMAGE_ALPHA(pColor);
    
    unsigned int aRed=IMAGE_RED(mData[y*mExpandedWidth+x]);
    unsigned int aGreen=IMAGE_GREEN(mData[y*mExpandedWidth+x]);
    unsigned int aBlue=IMAGE_BLUE(mData[y*mExpandedWidth+x]);
    unsigned int aAlpha=IMAGE_ALPHA(mData[y*mExpandedWidth+x]);
    
    if(aRed > aNewRed)aNewRed=aRed;
    if(aBlue > aNewBlue)aNewBlue=aBlue;
    if(aGreen > aNewGreen)aNewGreen=aGreen;
    if(aAlpha > aNewAlpha)aNewAlpha=aAlpha;
    
    mData[y*mExpandedWidth+x] = (0x00000000 | IMAGE_ALPHA_SHIFT(aNewAlpha));
}


bool FImage::IsBlank()
{
    bool aResult=true;
    unsigned int *aSearch=mData;
    unsigned int *aCap=&mData[mExpandedWidth*mExpandedHeight];
    while(aSearch<aCap)
    {
        if((IMAGE_ALPHA(*aSearch)))aResult=false;
        aSearch++;
    }
    return aResult;
}

bool FImage::DidLoad()
{
    bool aResult = false;
    
    if((mWidth > 0) && (mHeight > 0) && (mExpandedWidth > 0) && (mExpandedHeight > 0))
    {
        aResult = true;
    }
    
    return aResult;
}

//void				Flood(int pColor=0x000000FF){Flood(0,0,mExpandedWidth,mHeight,pColor);}


void FImage::Outline(int pSize, int pRed, int pGreen, int pBlue, int pAlpha)
{
    //Left Side
    
    
    unsigned int aColor = IMAGE_RGBA(pRed, pGreen, pBlue, pAlpha);
    
    
    //Left Side
    Flood(mOffsetX,mOffsetY,pSize,mHeight,aColor);
    
    
    //Right Side
    Flood(mOffsetX + mWidth - (pSize) - 1, mOffsetY, pSize, mHeight,aColor);
    
    
    //Top
    Flood(mOffsetX,mOffsetY,mWidth,pSize,aColor);
    
    
    //Bottom
    Flood(mOffsetX,mOffsetY + mHeight - pSize - 1,mWidth,pSize,aColor);
    
    
}

void FImage::OutlineRect(int x, int y, int pWidth, int pHeight, int pSize, unsigned int pColor)
{
    
    Flood(x-pSize, y-pSize, pWidth+pSize*2, pSize, pColor);
    Flood(x-pSize, y-pSize, pSize, pHeight+pSize*2, pColor);
    
    Flood(x, y + pHeight, pWidth + pSize , pSize, pColor);
    
    Flood(x+pWidth, y - pSize, pSize , pHeight+pSize * 2, pColor);
    
}

void FImage::Flood(int x, int y, int pWidth, int pHeight, unsigned int pColor)
{
    if(x<0)
    {
        pWidth+=x;
        x=0;
    }
    if(y<0)
    {
        pHeight+=y;
        y=0;
    }
    if(pWidth<0||pHeight<0||x>=mExpandedWidth||y>=mExpandedHeight)return;
    if(x+pWidth>mExpandedWidth)pWidth=mExpandedWidth-x;
    if(y+pHeight>mExpandedHeight)pHeight=mExpandedHeight-y;
    unsigned int *aPtr=&mData[y*mExpandedWidth+x];
    unsigned int *aCap;
    unsigned int aCount=pHeight;
    unsigned int aSkipAhead=(mExpandedWidth-pWidth);
    while(aCount>0)
    {
        aCap=aPtr+pWidth;
        while(aPtr<aCap)*aPtr++=pColor;
        aPtr+=aSkipAhead;
        aCount--;
    }
}

void FImage::FloodTransparent(int pColor)
{
    unsigned int *aSearch=mData;
    unsigned int *aCap=&mData[mExpandedWidth*mExpandedHeight];
    
    //int aAlpha;
    
    while(aSearch<aCap)
    {
        if(IMAGE_ALPHA(*aSearch) < 240)
        {
            *aSearch = pColor;
        }
        aSearch++;
    }
}

void FImage::Print()
{
    Log("\n");
    Log("FImage W=%d H=%d\n", mExpandedWidth, mExpandedHeight);
    Log("\n");
    for(int n=0;n<mExpandedHeight;n++)
    {
        FString aString;
        for(int i=0;i<mExpandedWidth;i++)
        {
            //aString+=SLog("%u8X|", ((mData[n*mExpandedWidth+i])<<0));
        }
        Log("Row[%3d]={%s}\n", n,aString.c());
    }
}


unsigned int AverageColors(unsigned int pColor1, unsigned int pColor2) {
    unsigned int aRed1 = IMAGE_RED(pColor1);
    unsigned int aGreen1 = IMAGE_GREEN(pColor1);
    unsigned int aBlue1 = IMAGE_BLUE(pColor1);
    unsigned int aAlpha1 = IMAGE_ALPHA(pColor1);
    
    unsigned int aRed2 = IMAGE_RED(pColor2);
    unsigned int aGreen2 = IMAGE_GREEN(pColor2);
    unsigned int aBlue2 = IMAGE_BLUE(pColor2);
    unsigned int aAlpha2 = IMAGE_ALPHA(pColor2);
    
    unsigned int aFinalRed = ((aRed1 + aRed2) >> 1);
    unsigned int aFinalGreen = ((aGreen1 + aGreen2) >> 1);
    unsigned int aFinalBlue = ((aBlue1 + aBlue2) >> 1);
    unsigned int aFinalAlpha = ((aAlpha1 + aAlpha2) >> 1);
    
    return ((aFinalAlpha << 24) | (aFinalRed << 0) | (aFinalBlue << 16) | (aFinalGreen << 8));
}






/*
 void ShatterMask::ApplyShatter(Image *pOriginal, Image *pMask, int pBorder, int pStroke)
 {
 if(pOriginal->mWidth<=0||pOriginal->mHeight<=0)return;
 
 
 if(pMask->mWidth!=pOriginal->mWidth || pMask->mHeight!=pOriginal->mHeight)return;
 
 if(pBorder<0)pBorder=0;
 if(pBorder>255)pBorder=255;
 
 if(pOriginal->mWidth>1024||pOriginal->mHeight>1024)return;
 
 
 int aWidth=pMask->mWidth;//min(pOriginal.mWidth,pMask.mWidth);
 int aHeight=pMask->mHeight;//min(pOriginal.mHeight,pMask.mHeight);
 int aArea=aWidth*aHeight;
 
 char *aMaskLinear=new char[aArea];
 char **aMask=new char*[aHeight];
 char *aPtr=aMaskLinear;
 
 
 
 unsigned int *aWriteData=pMask->mData;
 for(int i=0;i<aArea;i++)
 {
 //Log("WriteData: %x\n", *aWriteData);
 if(((*aWriteData)&0xFF)==0)
 {
 aMaskLinear[i]=1;
 }
 else
 {
 aMaskLinear[i]=0;
 }
 aWriteData++;
 }
 
 for(int i=0;i<aHeight;i++)
 {
 aMask[i]=aPtr;
 aPtr+=aWidth;
 }
 
 unsigned int **aData=new unsigned int*[aHeight];
 aWriteData=pOriginal->mData;
 for(int i=0;i<aHeight;i++)
 {
 aData[i]=aWriteData;
 
 aWriteData+=aWidth;
 }
 
 aArea=aWidth*aHeight;
 
 
 
 int aListCount=0;
 int aStackCount=0;
 int aLeft, aRight, aTop, aBottom;
 int aXOffset, aYOffset;
 int aNewImageWidth,aNewImageHeight;
 int aX=0;
 int aY=0;
 unsigned int *aSource,*aDest;
 
 unsigned int **aNewData=new unsigned int *[aHeight+pBorder+pBorder];
 
 int *aXList=new int[aArea];
 int *aYList=new int[aArea];
 int *aXStack=new int[aArea];
 int *aYStack=new int[aArea];
 
 for(int y=0;y<aHeight;y++)
 {
 for(int x=0;x<aWidth;x++)
 {
 if(!aMask[y][x])
 {
 aXList[0]=x;
 aYList[0]=y;
 aXStack[0]=x;
 aYStack[0]=y;
 aListCount=0;
 aStackCount=1;
 while(aStackCount>0)
 {
 aStackCount--;
 aX=aXStack[aStackCount];
 aY=aYStack[aStackCount];
 if(!aMask[aY][aX])
 {
 aXList[aListCount]=aX;
 aYList[aListCount]=aY;
 aListCount++;
 aMask[aY][aX]=1;
 //top
 if(aY>0)
 {
 if(!aMask[aY-1][aX])
 {
 aXStack[aStackCount]=aX;
 aYStack[aStackCount]=aY-1;
 aStackCount++;
 }
 }
 //right
 if(aX<aWidth-1)
 {
 if(!aMask[aY][aX+1])
 {
 aXStack[aStackCount]=aX+1;
 aYStack[aStackCount]=aY;
 aStackCount++;
 }
 }
 //bottom
 if(aY<aHeight-1)
 {
 if(!aMask[aY+1][aX])
 {
 aXStack[aStackCount]=aX;
 aYStack[aStackCount]=aY+1;
 aStackCount++;
 }
 }
 //left
 if(aX>0)
 {
 if(!aMask[aY][aX-1])
 {
 aXStack[aStackCount]=aX-1;
 aYStack[aStackCount]=aY;
 aStackCount++;
 }
 }
 }
 }
 
 aLeft=x;
 aRight=x;
 aTop=y;
 aBottom=y;
 
 for(int i=0;i<aListCount;i++)if(aXList[i]<aLeft)aLeft=aXList[i];
 for(int i=0;i<aListCount;i++)if(aXList[i]>aRight)aRight=aXList[i];
 for(int i=0;i<aListCount;i++)if(aYList[i]<aTop)aTop=aYList[i];
 for(int i=0;i<aListCount;i++)if(aYList[i]>aBottom)aBottom=aYList[i];
 
 aRight++;
 aBottom++;
 
 Image *aImage=new Image();
 aNewImageWidth=aRight-aLeft+pBorder+pBorder;
 aNewImageHeight=aBottom-aTop+pBorder+pBorder;
 mImageList+=aImage;
 mPointList+=new Vector2((float)(aLeft-pBorder)+((float)aNewImageWidth)/2, (float)(aTop-pBorder)+((float)aNewImageHeight)/2);
 
 aImage->MakeBlank((aNewImageWidth),(aNewImageHeight));
 
 //aImage->Print();
 
 //aImage->Make(aNewImageWidth,aNewImageHeight,gRand.Get(2500) + 0x2FFF0000);
 
 aWriteData=aImage->mData;
 for(int i=0;i<aNewImageHeight;i++)
 {
 aNewData[i]=aWriteData;
 aWriteData+=aNewImageWidth;
 }
 aXOffset=aLeft-pBorder;
 aYOffset=aTop-pBorder;
 for(int i=0;i<aListCount;i++)
 {
 aX=aXList[i];
 aY=aYList[i];
 aNewData[aY-aYOffset][aX-aXOffset]=aData[aY][aX];
 //aNewData[aX-aXOffset][aY-aYOffset]=aData[aX][aY];
 
 }
 
 if(pStroke)aImage->Stroke(0xFF000000,128,pStroke);
 
 Sprite *aSprite=new Sprite();
 //aSprite->Load(aImage);
 mSpriteList+=aSprite;
 
 
 }
 }
 }
 delete[]aNewData;
 delete[]aMaskLinear;
 delete[]aMask;
 delete[]aXList;
 delete[]aYList;
 delete[]aXStack;
 delete[]aYStack;
 delete[]aData;
 }
 */



typedef struct RGBA
{
    RGBA() {}
    RGBA(int r, int g, int b, int a)
    {
        mBlue=b;
        mRed=r;
        mGreen=g;
        mAlpha=a;
    }
    
    unsigned char mRed;
    unsigned char mGreen;
    unsigned char mBlue;
    unsigned char mAlpha;
    
} RGBA;

void FImage::Resize(int theNewWidth, int theNewHeight, FImage *theImage)
{
    //
    // First, create a new buffer for us...
    //
    RGBA *aNewData=new RGBA[theNewWidth*theNewHeight];
    
    //memset(aNewData,255,(theNewWidth*theNewHeight*4));
    int aNewWidth=theNewWidth;
    int aNewHeight=theNewHeight;
    
    //
    // Resize into it....
    //
    //*
    struct Rect
    {
        float mX;
        float mY;
        float mWidth;
        float mHeight;
    }
    
    aSrcRect, aDestRect;
    
    aSrcRect.mX=0;
    aSrcRect.mY=0;
    aSrcRect.mWidth=(float)mWidth;
    aSrcRect.mHeight=(float)mHeight;
    
    aDestRect.mX=0;
    aDestRect.mY=0;
    aDestRect.mWidth=(float)aNewWidth;
    aDestRect.mHeight=(float)aNewHeight;
    
    unsigned long* aSrcBits=(unsigned long *)mData;
    unsigned long* aDestBits=(unsigned long*)aNewData;
    
#define SRC_TYPE unsigned long
#define READ_COLOR(ptr) (*(ptr))
    
    {
        int aSrcRowWidth = mWidth;
        int aSrcXI = (int) floor(aSrcRect.mX);
        int aSrcYI = (int) floor(aSrcRect.mY);
        int aSrcWidthI = (int) ceil(aSrcRect.mWidth + (aSrcRect.mX - aSrcXI));
        int aSrcHeightI = (int) ceil(aSrcRect.mHeight + (aSrcRect.mY - aSrcYI));
        
        if(aSrcXI<0) aSrcXI = 0;
        if(aSrcYI<0) aSrcYI = 0;
        if(aSrcXI + aSrcWidthI > mWidth) aSrcWidthI = mWidth - aSrcXI;
        if(aSrcYI + aSrcHeightI > mHeight) aSrcHeightI = mHeight - aSrcYI;
        if(aSrcWidthI<=0 || aSrcHeightI<=0) return;
        
        
        int aTempDestWidth =(int)(aDestRect.mWidth+4);
        int aTempDestHeight = (int)(aDestRect.mHeight+4);
        
        // For holding horizontally resized pixels not vertically (yet)
        
        unsigned long* aNewHorzPixels = new unsigned long[aTempDestWidth*aSrcHeightI*4];
        
        memset(aNewHorzPixels,0,aTempDestWidth*aSrcHeightI*4*4);
        
        if(aSrcRect.mWidth >= aDestRect.mWidth)
        {
            
            double aDestXFactor = aDestRect.mWidth / aSrcRect.mWidth;
            double aDestXOffset = 1.0 + (aSrcXI - aSrcRect.mX) * aDestXFactor;
            
            
            // Shrinking
            
            
            for(int aSrcX = 0; aSrcX < aSrcWidthI; aSrcX++)
            {
                double aDestX1 = aDestXFactor * aSrcX + aDestXOffset;
                double aDestX2 = aDestX1 + aDestXFactor;
                
                int aDestXI1 = (int) aDestX1;
                int aDestXI2 = (int) aDestX2;
                
                SRC_TYPE* s1 = &aSrcBits[aSrcYI*aSrcRowWidth + aSrcXI+aSrcX];
                
                if(aDestXI1 == aDestXI2)
                {
                    
                    unsigned long* d = &aNewHorzPixels[aDestXI1*4];
                    int aFactor = (int) (257 * aDestXFactor);
                    
                    for(int aSrcY = 0; aSrcY < aSrcHeightI; aSrcY++)
                    {
                        unsigned long pixel = READ_COLOR(s1);
                        
                        *d++ += aFactor * ((pixel      ) & 0xFF);
                        *d++ += aFactor * ((pixel >>  8) & 0xFF);
                        *d++ += aFactor * ((pixel >> 16) & 0xFF);
                        *d++ += aFactor * ((pixel >> 24) & 0xFF);
                        
                        d += aTempDestWidth*4 - 4;
                        s1 += aSrcRowWidth;
                    }
                }
                else
                {
                    int aFactor1 = (int) (257 * (aDestXI2 - aDestX1));
                    int aFactor2 = (int) (257 * (aDestX2 - aDestXI2));
                    
                    unsigned long* d = &aNewHorzPixels[aDestXI1*4];
                    
                    for(int aSrcY = 0; aSrcY < aSrcHeightI; aSrcY++)
                    {
                        unsigned long pixel = READ_COLOR(s1);
                        
                        
                        *d++ += aFactor1 * ((pixel      ) & 0xFF);
                        *d++ += aFactor1 * ((pixel >>  8) & 0xFF);
                        *d++ += aFactor1 * ((pixel >> 16) & 0xFF);
                        *d++ += aFactor1 * ((pixel >> 24) & 0xFF);
                        
                        *d++ += aFactor2 * ((pixel      ) & 0xFF);
                        *d++ += aFactor2 * ((pixel >>  8) & 0xFF);
                        *d++ += aFactor2 * ((pixel >> 16) & 0xFF);
                        *d++ += aFactor2 * ((pixel >> 24) & 0xFF);
                        
                        
                        d += aTempDestWidth*4 - 8;
                        s1 += aSrcRowWidth;
                    }
                }
            }
            
        }
        else
        {
            
            double aSrcXFactor = (aSrcRect.mWidth - 1) / (aDestRect.mWidth - 1);
            
            for(int aDestX = 1; aDestX < aTempDestWidth-1; aDestX++)
            {
                unsigned long* d = &aNewHorzPixels[aDestX*4];
                
                double aSrcX = (aDestX - 1)*aSrcXFactor + aSrcRect.mX;
                int aSrcXI = (int) aSrcX;
                
                int aFactor1 = (int) (257 * (1.0 - (aSrcX - aSrcXI)));
                int aFactor2 = (int) (257 - aFactor1);
                
                SRC_TYPE* s = &aSrcBits[aSrcYI*aSrcRowWidth+aSrcXI];
                
                for(int aDestY = 0; aDestY < aSrcHeightI; aDestY++)
                {
                    unsigned long pixel1 = READ_COLOR(s++);
                    unsigned long pixel2 = READ_COLOR(s);
                    
                    *d++ = (aFactor1 * ((pixel1      ) & 0xFF)) + (aFactor2 * ((pixel2      ) & 0xFF));
                    *d++ = (aFactor1 * ((pixel1 >>  8) & 0xFF)) + (aFactor2 * ((pixel2 >>  8) & 0xFF));
                    *d++ = (aFactor1 * ((pixel1 >> 16) & 0xFF)) + (aFactor2 * ((pixel2 >> 16) & 0xFF));
                    *d++ = (aFactor1 * ((pixel1 >> 24) & 0xFF)) + (aFactor2 * ((pixel2 >> 24) & 0xFF));
                    
                    
                    d += aTempDestWidth*4 - 4;
                    s += aSrcRowWidth - 1;
                }
            }
        }
        
        unsigned long* aNewPixels = new unsigned long[aTempDestWidth*aTempDestHeight*4];
        
        memset(aNewPixels,0,aTempDestWidth*aTempDestHeight*4*4);
        
        // Now resize vertically
        
        if(aSrcRect.mHeight >= aDestRect.mHeight)
        {
            double aDestYFactor = aDestRect.mHeight / aSrcRect.mHeight;
            
            double aDestYOffset = 1.0 + (aSrcYI - aSrcRect.mY) * aDestYFactor;
            
            for(int aSrcY = 0; aSrcY < aSrcHeightI; aSrcY++)
            {
                double aDestY1 = aDestYFactor * aSrcY + aDestYOffset;
                double aDestY2 = aDestY1 + aDestYFactor;
                
                int aDestYI1 = (int) floor(aDestY1);
                int aDestYI2 = (int) floor(aDestY2);
                
                unsigned long* s = &aNewHorzPixels[aSrcY*aTempDestWidth*4];
                
                if(aDestYI1 == aDestYI2)
                {
                    unsigned long* d = &aNewPixels[aDestYI1*aTempDestWidth*4];
                    int aFactor = (int) (256 * aDestYFactor);
                    
                    for(int aSrcX = 0; aSrcX < aTempDestWidth; aSrcX++)
                    {
                        *d++ += aFactor * *s++;
                        *d++ += aFactor * *s++;
                        *d++ += aFactor * *s++;
                        *d++ += aFactor * *s++;
                    }
                }
                else
                {
                    int aFactor1 = (int) (256 * (aDestYI2 - aDestY1));
                    int aFactor2 = (int) (256 * (aDestY2 - aDestYI2));
                    
                    unsigned long* d1 = &aNewPixels[aDestYI1*aTempDestWidth*4];
                    unsigned long* d2 = &aNewPixels[aDestYI2*aTempDestWidth*4];
                    
                    for(int aSrcX = 0; aSrcX < aTempDestWidth; aSrcX++)
                    {
                        *d1++ += aFactor1 * *s;
                        *d2++ += aFactor2 * *s++;
                        
                        *d1++ += aFactor1 * *s;
                        *d2++ += aFactor2 * *s++;
                        
                        *d1++ += aFactor1 * *s;
                        *d2++ += aFactor2 * *s++;
                        
                        *d1++ += aFactor1 * *s;
                        *d2++ += aFactor2 * *s++;
                    }
                    
                }
            }
            
        }
        else
        {
            
            double aSrcYFactor = (aSrcRect.mHeight - 1) / (aDestRect.mHeight - 1);
            
            for(int aDestY = 1; aDestY < aDestRect.mHeight + 1; aDestY++)
            {
                unsigned long* d = &aNewPixels[(aDestY*aTempDestWidth+1)*4];
                
                double aSrcY = (aDestY-1)*aSrcYFactor + (aSrcRect.mY - ((int) aSrcRect.mY));
                int aSrcYI = (int) aSrcY;
                
                int aFactor1 = (int) (256 * (1.0 - (aSrcY - aSrcYI)));
                int aFactor2 = 256 - aFactor1;
                
                unsigned long* s1 = &aNewHorzPixels[(aSrcYI*aTempDestWidth+1)*4];
                unsigned long* s2;
                
                if(aSrcYI == aSrcHeightI - 1)
                    s2 = s1;
                else
                    s2 = &aNewHorzPixels[((aSrcYI+1)*aTempDestWidth+1)*4];
                
                for(int aDestX = 1; aDestX < aTempDestWidth-1; aDestX++)
                {
                    *d++ = (aFactor1 * *s1++) + (aFactor2 * *s2++);
                    *d++ = (aFactor1 * *s1++) + (aFactor2 * *s2++);
                    *d++ = (aFactor1 * *s1++) + (aFactor2 * *s2++);
                    *d++ = (aFactor1 * *s1++) + (aFactor2 * *s2++);
                }
            }
        }
        
        for(int y = 0; y < aDestRect.mHeight; y++)
        {
            unsigned long* aDestPixels = &aDestBits[((int)aDestRect.mY+y)*(int)aDestRect.mWidth+(int)aDestRect.mX];
            
            for(int x = 0; x < aDestRect.mWidth; x++)
            {
                unsigned long *p = &aNewPixels[((y+1)*aTempDestWidth+x+1)*4];
                
                int b = (int)((*p++) >> 16);
                int g = (int)((*p++) >> 16);
                int r = (int)((*p++) >> 16);
                int a = (int)((*p++) >> 16);
                
                *(aDestPixels++)= (b) | (g << 8) | (r << 16) | (a << 24);
            }
        }
        
        
        delete [] aNewPixels;
        delete aNewHorzPixels;
    }
    /**/
    
    //
    // Now naturalize to theImage.  If theImage==NULL, then
    // we free up this image and stick it in there.
    //
    
    if(!theImage)
    {
        theImage=this;
        delete [] mData;
        mData=NULL;
    }
    else theImage->Kill();
    
    
    
    
    theImage->mWidth=aNewWidth;
    theImage->mHeight=aNewHeight;
    theImage->mExpandedWidth=aNewWidth;
    theImage->mExpandedHeight=aNewHeight;
    theImage->mFileName = mFileName;
    
    theImage->mData = ((unsigned int *)aNewData);
}







/*
 
 // * @param src input nv12 raw data array
 // * @param dst output nv12 raw data result,
 // * the memory need to be allocated outside of the function
 // * @param srcWidth width of the input nv12 image
 // * @param srcHeight height of the input nv12 image
 // * @param dstWidth
 // * @param dstHeight
 
 
 void nv12_nearest_scale(uint8_t* __restrict src, uint8_t* __restrict dst,
 int srcWidth, int srcHeight, int dstWidth, int
 dstHeight)      //restrict keyword is for compiler to optimize program
 {
 int sw = srcWidth;  //keyword is for local var to accelorate
 int sh = srcHeight;
 int dw = dstWidth;
 int dh = dstHeight;
 int y, x;
 unsigned long int srcy, srcx, src_index, dst_index;
 unsigned long int xrIntFloat_16 = (sw << 16) / dw + 1; //better than float division
 unsigned long int yrIntFloat_16 = (sh << 16) / dh + 1;
 
 uint8_t* dst_uv = dst + dh * dw; //memory start pointer of dest uv
 uint8_t* src_uv = src + sh * sw; //memory start pointer of source uv
 uint8_t* dst_uv_yScanline;
 uint8_t* src_uv_yScanline;
 uint8_t* dst_y_slice = dst; //memory start pointer of dest y
 uint8_t* src_y_slice;
 uint8_t* sp;
 uint8_t* dp;
 
 for (y = 0; y < (dh & ~7); ++y)  //'dh & ~7' is to generate faster assembly code
 {
 srcy = (y * yrIntFloat_16) >> 16;
 src_y_slice = src + srcy * sw;
 
 if((y & 1) == 0)
 {
 dst_uv_yScanline = dst_uv + (y / 2) * dw;
 src_uv_yScanline = src_uv + (srcy / 2) * sw;
 }
 
 for(x = 0; x < (dw & ~7); ++x)
 {
 srcx = (x * xrIntFloat_16) >> 16;
 dst_y_slice[x] = src_y_slice[srcx];
 
 if((y & 1) == 0) //y is even
 {
 if((x & 1) == 0) //x is even
 {
 src_index = (srcx / 2) * 2;
 
 sp = dst_uv_yScanline + x;
 dp = src_uv_yScanline + src_index;
 *sp = *dp;
 ++sp;
 ++dp;
 *sp = *dp;
 }
 }
 }
 dst_y_slice += dw;
 }
 }
 
 void nv12_bilinear_scale (uint8_t* src, uint8_t* dst,
 int srcWidth, int srcHeight, int dstWidth,int dstHeight)
 {
 int x, y;
 int ox, oy;
 int tmpx, tmpy;
 int xratio = (srcWidth << 8)/dstWidth;
 int yratio = (srcHeight << 8)/dstHeight;
 uint8_t* dst_y = dst;
 uint8_t* dst_uv = dst + dstHeight * dstWidth;
 uint8_t* src_y = src;
 uint8_t* src_uv = src + srcHeight * srcWidth;
 
 uint8_t y_plane_color[2][2];
 uint8_t u_plane_color[2][2];
 uint8_t v_plane_color[2][2];
 int j,i;
 int size = srcWidth * srcHeight;
 int offsetY;
 int y_final, u_final, v_final;
 int u_final1 = 0;
 int v_final1 = 0;
 int u_final2 = 0;
 int v_final2 = 0;
 int u_final3 = 0;
 int v_final3 = 0;
 int u_final4 = 0;
 int v_final4 = 0;
 int u_sum = 0;
 int v_sum = 0;
 
 
 tmpy = 0;
 for (j = 0; j < (dstHeight & ~7); ++j)
 {
 //tmpy = j * yratio;
 oy = tmpy >> 8;
 y = tmpy & 0xFF;
 
 tmpx = 0;
 for (i = 0; i < (dstWidth & ~7); ++i)
 {
 // tmpx = i * xratio;
 ox = tmpx >> 8;
 x = tmpx & 0xFF;
 
 offsetY = oy * srcWidth;
 //YYYYYYYYYYYYYYYY
 y_plane_color[0][0] = src[ offsetY + ox ];
 y_plane_color[1][0] = src[ offsetY + ox + 1 ];
 y_plane_color[0][1] = src[ offsetY + srcWidth + ox ];
 y_plane_color[1][1] = src[ offsetY + srcWidth + ox + 1 ];
 
 int y_final = (0x100 - x) * (0x100 - y) * y_plane_color[0][0]
 + x * (0x100 - y) * y_plane_color[1][0]
 + (0x100 - x) * y * y_plane_color[0][1]
 + x * y * y_plane_color[1][1];
 y_final = y_final >> 16;
 if (y_final>255)
 y_final = 255;
 if (y_final<0)
 y_final = 0;
 dst_y[ j * dstWidth + i] = (uint8_t)y_final; //set Y in dest array
 //UVUVUVUVUVUV
 if((j & 1) == 0) //j is even
 {
 if((i & 1) == 0) //i is even
 {
 u_plane_color[0][0] = src[ size + offsetY + ox ];
 u_plane_color[1][0] = src[ size + offsetY + ox ];
 u_plane_color[0][1] = src[ size + offsetY + ox ];
 u_plane_color[1][1] = src[ size + offsetY + ox ];
 
 v_plane_color[0][0] = src[ size + offsetY + ox + 1];
 v_plane_color[1][0] = src[ size + offsetY + ox + 1];
 v_plane_color[0][1] = src[ size + offsetY + ox + 1];
 v_plane_color[1][1] = src[ size + offsetY + ox + 1];
 }
 else //i is odd
 {
 u_plane_color[0][0] = src[ size + offsetY + ox - 1 ];
 u_plane_color[1][0] = src[ size + offsetY + ox + 1 ];
 u_plane_color[0][1] = src[ size + offsetY + ox - 1 ];
 u_plane_color[1][1] = src[ size + offsetY + ox + 1 ];
 
 v_plane_color[0][0] = src[ size + offsetY + ox ];
 v_plane_color[1][0] = src[ size + offsetY + ox + 1 ];
 v_plane_color[0][1] = src[ size + offsetY + ox ];
 v_plane_color[1][1] = src[ size + offsetY + ox + 1 ];
 }
 }
 else // j is odd
 {
 if((i & 1) == 0) //i is even
 {
 u_plane_color[0][0] = src[ size + offsetY + ox ];
 u_plane_color[1][0] = src[ size + offsetY + ox ];
 u_plane_color[0][1] = src[ size + offsetY + srcWidth + ox ];
 u_plane_color[1][1] = src[ size + offsetY + srcWidth + ox ];
 
 v_plane_color[0][0] = src[ size + offsetY + ox + 1];
 v_plane_color[1][0] = src[ size + offsetY + ox + 1];
 v_plane_color[0][1] = src[ size + offsetY + srcWidth + ox + 1];
 v_plane_color[1][1] = src[ size + offsetY + srcWidth + ox + 1];
 }
 else //i is odd
 {
 u_plane_color[0][0] = src[ size + offsetY + ox - 1 ];
 u_plane_color[1][0] = src[ size + offsetY + srcWidth + ox - 1 ];
 u_plane_color[0][1] = src[ size + offsetY + ox + 1];
 u_plane_color[1][1] = src[ size + offsetY + srcWidth + ox + 1];
 
 v_plane_color[0][0] = src[ size + offsetY + ox ];
 v_plane_color[1][0] = src[ size + offsetY + srcWidth + ox ];
 v_plane_color[0][1] = src[ size + offsetY + ox + 2 ];
 v_plane_color[1][1] = src[ size + offsetY + srcWidth + ox + 2 ];
 }
 }
 
 int u_final = (0x100 - x) * (0x100 - y) * u_plane_color[0][0]
 + x * (0x100 - y) * u_plane_color[1][0]
 + (0x100 - x) * y * u_plane_color[0][1]
 + x * y * u_plane_color[1][1];
 u_final = u_final >> 16;
 
 int v_final = (0x100 - x) * (0x100 - y) * v_plane_color[0][0]
 + x * (0x100 - y) * v_plane_color[1][0]
 + (0x100 - x) * y * v_plane_color[0][1]
 + x * y * v_plane_color[1][1];
 v_final = v_final >> 16;
 if((j & 1) == 0)
 {
 if((i & 1) == 0)
 {
 //set U in dest array
 dst_uv[(j / 2) * dstWidth + i ] = (uint8_t)(u_sum / 4);
 //set V in dest array
 dst_uv[(j / 2) * dstWidth + i + 1] = (uint8_t)(v_sum / 4);
 u_sum = 0;
 v_sum = 0;
 }
 }
 else
 {
 u_sum += u_final;
 v_sum += v_final;
 }
 tmpx += xratio;
 }
 tmpy += yratio;
 }
 }
 
 int ImageResize(uint8_t * src, uint8_t* dst, int sw,
 int sh,int dw,int dh)
 {
 if( (src == NULL) || (dst == NULL) || (0 == dw) || (0 == dh) ||
 (0 == sw) || (0 == sh))
 {
 Log("params error\n");
 return -1;
 }
 nv12_nearest_scale(src, dst, sw, sh, dw, dh);
 //nv12_bilinear_scale(src, dst, sw, sh, dw, dh);
 //greyscale(src, dst, sw, sh, dw, dh);
 return 0;
 }
 
 int main(int argc,char**argv)
 {
 if(argc!=7)
 {
 Log("Input Error!\n");
 Log("Usage :  <Input NV12file> <Output NV12file>
 <sw><sh> <dw> <dh>");
 return 0;
 }
 
 FILE *inputfp = NULL;
 FILE *outputfp = NULL;
 
 inputfp = fopen(argv[1], "rb");
 if (!inputfp)
 {
 fLog(stderr, "fopen failed for input file[%s]\n",argv[1]);
 return -1;
 }
 
 outputfp = fopen(argv[2], "wb");
 
 if (!outputfp)
 {
 fLog(stderr, "fopen failed for output file[%s]\n",argv[2]);
 return -1;
 }
 
 int sw = atoi(argv[3]);
 int sh = atoi(argv[4]);
 int dw = atoi(argv[5]);
 int dh = atoi(argv[6]);
 
 if(sw <= 0 || sh <= 0 || dw <= 0 || dh <=0)
 {
 fLog(stderr, "parameter error [sw= %d,sh= %d,dw= %d,dh= %d]\n",sw,sh,dw,dh);
 return -1;
 }
 
 int inPixels = sw * sh * 3/2;
 int outPixels = dw * dh * 3/2;
 
 uint8_t* pInBuffer = (uint8_t*)malloc(inPixels);
 fread(pInBuffer,1,inPixels,inputfp);
 uint8_t* pOutBuffer = (uint8_t*)malloc(outPixels);
 
 ImageResize(pInBuffer,pOutBuffer,sw,sh,dw,dh);
 //compute frame per second
 int i = 0;
 clock_t start = clock();
 
 for(;i<1000;++i)
 {
 ImageResize(pInBuffer,pOutBuffer,1536,1088,1024,600);//can change to be any resolution    
 }
 clock_t finish = clock();
 float duration = (float)(finish-start)/CLOCKS_PER_SEC;
 float fps = 1000 / duration;
 Log("nv12Scaling:%d*%d-->%d*%d,time cost:%6.2ffps\n",sw,sh,dw,dh,fps);
 
 fwrite(pOutBuffer, 1 , outPixels, outputfp);
 
 free(pInBuffer);
 free(pOutBuffer);
 fclose(inputfp);
 fclose(outputfp);
 pInBuffer = NULL;
 pOutBuffer = NULL;
 inputfp = NULL;
 outputfp = NULL;
 return 0;
 }
 
 */





