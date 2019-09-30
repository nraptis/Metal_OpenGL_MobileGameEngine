#include "FVertexBuffer.h"

#include "os_core_graphics.h"
#include "core_includes.h"

FVertexBuffer::FVertexBuffer()
{
    mTexture = 0;
    
    mVertexSize = 0;
    mCoordSize = 0;
    
    mVertexCount = 0;
    mCoordCount = 0;
    
	mXYZ = 0;
	mUVW = 0;
    
    mRGBA = 0;
    
    mVertexCount = 0;
    mCoordCount = 0;
    
    mColorCount = 0;
    mColorSize = 0;
	
	//mMode = GL_TRIANGLE_STRIP;
}

FVertexBuffer::~FVertexBuffer()
{
	Kill();
}

void FVertexBuffer::Kill()
{
    SetTexture(0);
    
	mVertexSize = 0;
    mCoordSize = 0;
    
    mVertexCount = 0;
    mCoordCount = 0;
    
	delete [] mXYZ;
	delete [] mUVW;
	//delete[]mV;
    
    
    delete [] mRGBA;
    
    mVertexCount = 0;
    mCoordCount = 0;
    
    mColorCount = 0;
    mColorSize = 0;
    
	mXYZ = 0;
	mUVW = 0;
    mRGBA = 0;
}

void FVertexBuffer::SetTexture(FTexture *pTexture)
{
    //if(mTexture){if(pTexture != mTexture){gTextureCache.TextureBindRemove(mTexture);mTexture = 0;}}if(pTexture){mTexture = pTexture;gTextureCache.TextureBindAdd(mTexture);}
    SET_TEXTURE_BODY;
    
}

void FVertexBuffer::Add(float x, float y, float z, float u, float v, float w)
{
	//Log("VBUFFER %f %f\n", u, v);
    
    AddXYZ(x, y, z);
    AddUVW(u, v, w);
}

void FVertexBuffer::AddUVW(float u, float v, float w)
{
	int aTextureCount=(mCoordCount*3);
    
    if(mCoordCount==mCoordSize)
	{
		int aNewSize=mCoordSize+mCoordSize/2+1;
        int aNewSize3 = aNewSize * 3;
        float *aNewU=new float[aNewSize3];
        
        for(int i=0;i<aNewSize3;i++)
        {
            aNewU[i]=0;
        }
        
		for(int i=0;i<aTextureCount;i++) aNewU[i] = mUVW[i];
		delete[]mUVW;
        
		mUVW=aNewU;
		mCoordSize=aNewSize;
	}
    
	mUVW[aTextureCount]=u;
	mUVW[aTextureCount+1]=v;
    mUVW[aTextureCount+2]=w;
    
	mCoordCount++;
}

void FVertexBuffer::AddXYZ(float x, float y, float z)
{    
    int aVertexCount=(mVertexCount*3);
	
	if(mVertexCount==mVertexSize)
	{
		int aNewSize=mVertexSize+mVertexSize/2+1;
        
        int aNewSize3 = aNewSize * 3;
        
		float *aNewX=new float[aNewSize3];
        
        for(int i=0;i<aNewSize3;i++)aNewX[i] = 0;
		for(int i=0;i<aVertexCount;i++)aNewX[i] = mXYZ[i];
        
		delete[]mXYZ;
		
		mXYZ=aNewX;
		
		mVertexSize=aNewSize;
	}
    
	mXYZ[aVertexCount]=x;
	mXYZ[aVertexCount+1]=y;
	mXYZ[aVertexCount+2]=z;
    
	mVertexCount++;
}

void FVertexBuffer::AddQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    AddQuad(x1, y1, x2, y2, x3, y3, x4, y4, 0, 0, 0, 1, 1, 0, 1, 1);
}

void FVertexBuffer::AddQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,
                            float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4)
{
    /*
    Graphics::SetColor(1,0,0,0.5f);
    Graphics::DrawRect(x1-2,y1-2,5,5);
    
    Graphics::SetColor(0,1,0,0.5f);
    Graphics::DrawRect(x2-2,y2-2,5,5);
    
    Graphics::SetColor(0,0,1,0.5f);
    Graphics::DrawRect(x3-2,y3-2,5,5);
    
    Graphics::SetColor(1,1,1,0.5f);
    Graphics::DrawRect(x4-2,y4-2,5,5);
    */
    
    Add(x1,y1,u1,v1);
    Add(x2,y2,u2,v2);
    Add(x3,y3,u3,v3);
    
    Add(x2,y2,u2,v2);
    Add(x3,y3,u3,v3);
    Add(x4,y4,u4,v4);    
}

void FVertexBuffer::AddRGBA(float pRed, float pGreen, float pBlue, float pAlpha)
{
    int aColorCount = (mColorCount*4);
    
    if(mColorCount == mColorSize)
    {
        /*
        int aNewSize=mColorSize+mColorSize/2+1;
		float *aNewRed=new float[mColorSize*4];
		for(int i=0;i<aColorCount;i++)aNewRed[i]=mRGBA[i];
		delete[]mRGBA;
        
        
		mRGBA=aNewRed;
		mVertexSize=aNewSize;
        */
        
        int aNewSize=mColorSize+mColorSize/2+1;
        
        float *aOldRed      = mRGBA;
        float *aOldGreen    = mRGBA + mColorSize;
        float *aOldBlue     = mRGBA + mColorSize * 2;
        float *aOldAlpha    = mRGBA + mColorSize * 3;
        
		float *aNewRed      = new float[aNewSize*4];
        float *aNewGreen    = aNewRed + aNewSize;
        float *aNewBlue     = aNewRed + aNewSize * 2;
        float *aNewAlpha    = aNewRed + aNewSize * 3;
        
		for(int i=0;i<mColorCount;i++)aNewRed[i] = aOldRed[i];
        for(int i=0;i<mColorCount;i++)aNewGreen[i] = aOldGreen[i];
        for(int i=0;i<mColorCount;i++)aNewBlue[i] = aOldBlue[i];
        for(int i=0;i<mColorCount;i++)aNewAlpha[i] = aOldAlpha[i];
        
		delete[]mRGBA;
		
		mRGBA=aNewRed;
		
		mColorSize=aNewSize;
    }
    
    mRGBA[aColorCount+0]=pRed;
    mRGBA[aColorCount+1]=pGreen;
    mRGBA[aColorCount+2]=pBlue;
    mRGBA[aColorCount+3]=pAlpha;
    
    mColorCount++;
}

/*

void FVertexBuffer::StereoscopicShift(float pShiftMin, float pShiftMax, FVertexBuffer *pBuffer, Color pColorOuter, Color pColorInner)
{
    mCoordCount=0;
    mVertexCount=0;
    mColorCount=0;
    
    float *aUVW=pBuffer->mUVW;
    float *aXYZ=pBuffer->mXYZ;
    
    int aCount = pBuffer->mVertexCount * 3;
    
    float aX, aY, aZ;
    float aU, aV, aW;
    float aRed, aGreen, aBlue, aAlpha;
    float aPercent;
    
    float aBaseRed=pColorInner.mRed;
    float aBaseGreen=pColorInner.mGreen;
    float aBaseBlue=pColorInner.mBlue;
    float aBaseAlpha=pColorInner.mAlpha;
    
    float aDiffRed=aBaseRed - pColorOuter.mRed;
    float aDiffGreen=aBaseGreen - pColorOuter.mGreen;
    float aDiffBlue=aBaseBlue - pColorOuter.mBlue;
    float aDiffAlpha=aBaseAlpha - pColorOuter.mAlpha;
    
    float aBaseShift = pShiftMin;
    float aShiftDiff = pShiftMax - aBaseShift;
    
    
    for(int i=0;i<aCount;i+=3)
    {
        aX=aXYZ[i+0];
        aY=aXYZ[i+1];
        aZ=aXYZ[i+2];
        
        aPercent=aZ;
        
        aU=aUVW[i+0];
        aV=aUVW[i+1];
        
        aRed = aBaseRed - aPercent * aDiffRed;
        aGreen = aBaseGreen - aPercent * aDiffGreen;
        aBlue = aBaseBlue - aPercent * aDiffBlue;
        aAlpha = aBaseAlpha - aPercent * aDiffAlpha;
        
        AddXYZ(aX + aBaseShift + aShiftDiff * aPercent, aY, aZ);
        AddUV(aU, aV);
        AddRGBA(aRed,aGreen,aBlue,aAlpha);
        
    }
}

*/

void FVertexBuffer::DrawColored()
{
    /*
    if(mVertexCount>0)
	{
		glVertexPointer(3,GL_FLOAT,0,mXYZ);
		glTextureCoordPointer(2,GL_FLOAT,0,mUVW);
        
        if(mColorCount > 0)
        {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(4, GL_FLOAT, 0, mRGBA);
            
            glDrawArrays(mMode, 0, mVertexCount);
            
            glDisableClientState(GL_COLOR_ARRAY);
        }
	}
    */
    
    if (mColorCount > 0) {
        //Graphics::EnableColorArray();
        //Graphics::ArrayColor(mRGBA);
        
    }
    
    Draw();
}



void FVertexBuffer::DrawTriangles()
{
	if(mVertexCount>0)
	{
        Draw(mVertexCount);
		//glVertexPointer(3,GL_FLOAT,0,mXYZ);
		//glTextureCoordPointer(2,GL_FLOAT,0,mUVW);
		//glDrawArrays(GL_LINE_LOOP, 0, mVertexCount);
	}
}


void FVertexBuffer::Draw()
{
    Draw(mVertexCount);
}

void FVertexBuffer::Draw(int pCount)
{
    Draw(0, pCount);
}

void FVertexBuffer::Draw(int pStart, int pCount)
{
	//if(pStart<0)pStart=0;
    //if(pCount>mVertexCount)pCount=mVertexCount;
	
    if(mVertexCount <= 0)return;
    
    if (mTexture) {
        Graphics::TextureBind(mTexture);
        Graphics::TextureSetWrap();
    }
    
    //TODO: ???
    //Graphics::ArrayCoords(&mUVW[pStart*3],3);
    //Graphics::ArrayVertices(&mXYZ[pStart*3],3);
    //Graphics::DrawTriangles(pCount);

    if (mTexture) {
        Graphics::TextureSetClamp();
    }
}

void FVertexBuffer::DrawStrips()
{
    DrawStrips(mVertexCount);
}

void FVertexBuffer::DrawStrips(int pCount)
{
    DrawStrips(0, pCount);
}

void FVertexBuffer::DrawStrips(int pStart, int pCount)
{
    if(mVertexCount <= 0)return;
    
    if (mTexture) {
        Graphics::TextureBind(mTexture);
    }
    
    //Graphics::ArrayCoords(&mUVW[pStart*3],3);
    //Graphics::ArrayVertices(&mXYZ[pStart*3],3);
    
    Graphics::DrawTriangleStrips(pCount);
}

void FVertexBuffer::GenerateMagicCube(float pSize)
{
	
	
	///////////////////////////////////////////////////
	//     -------------------------------------------
	//    |          |          |          |          |
	//    |          |          |          |          |
	//    |          |          |          |          |
	//    |          |          |          |          |
	//    |  Front   |   Back   |   Top    |  Bottom  |
	//    |          |          |          |          |
	//    |          |          |          |          |
	//    |          |          |          |          |
	//    |          |          |          |          |
	//     -------------------------------------------
	//    |          |          |          |          |
	//    |          |          |          |          |
	//    |          |          |          |          |
	//    |          |          |          |          |
	//	  |   Right  |   Left   |  -----   |   -----  |
	//    |          |          |          |          |
	//    |          |          |          |          |
	//    |          |          |          |          |
	//    |          |          |          |          |
	//     -------------------------------------------
	
	float aMinU;
	float aMinV;
	float aMaxU;
	float aMaxV;
	
	
	
	aMinU=0;
	aMaxU=0.25f;
	
	aMinV=0;
	aMaxV=0.5f;
	
	//Front Face
	Add(-pSize, -pSize, pSize, aMinU, aMinV);
	Add(pSize, -pSize, pSize, aMaxU, aMinV);
	Add(-pSize,  pSize, pSize, aMinU, aMaxV);
	Add(pSize,  pSize, pSize, aMaxU, aMaxV);
	
	
	aMinU=0.25f;
	aMaxU=0.5f;
	
	aMinV=0;
	aMaxV=0.5f;
	
	
	// Back Face
	Add(-pSize, -pSize,  -pSize, aMaxU, aMinV);
	Add(-pSize,  pSize,  -pSize, aMaxU, aMaxV);
	Add(pSize, -pSize,  -pSize, aMinU, aMinV);
	Add(pSize,  pSize,  -pSize, aMinU, aMaxV);
	
	
	aMinU=0.5f;
	aMaxU=0.75f;
	
	aMinV=0;
	aMaxV=0.5f;
	
	
	// Top Face
	Add(-pSize, -pSize,  pSize, aMinU, aMaxV);
	Add(-pSize, -pSize, -pSize, aMinU, aMinV);
	Add(pSize, -pSize,  pSize, aMaxU, aMaxV);
	Add(pSize, -pSize, -pSize, aMaxU, aMinV);
	
	aMinU=0.75f;
	aMaxU=1.0f;
	
	aMinV=0;
	aMaxV=0.5f;
	
	
	// Bottom Face
	Add(-pSize,  pSize,  pSize, aMinU, aMinV);
	Add(pSize,  pSize,  pSize, aMaxU, aMinV);
	Add(-pSize,  pSize, -pSize, aMinU, aMaxV);
	Add(pSize,  pSize, -pSize, aMaxU, aMaxV);
	
	aMinU=0;
	aMaxU=0.25f;
	
	aMinV=0.5f;
	aMaxV=1.0f;
	
	// Right Face
	Add(pSize,  pSize,  pSize, aMinU, aMaxV);
	Add(pSize, -pSize,  pSize, aMinU, aMinV);
	Add(pSize,  pSize, -pSize, aMaxU, aMaxV);
	Add(pSize, -pSize, -pSize, aMaxU, aMinV);
	
	
	aMinU=0.25f;
	aMaxU=0.5f;
	
	aMinV=0.5f;
	aMaxV=1.0f;
	
	// Left Face
	Add(-pSize,  pSize, -pSize, aMinU, aMaxV);
	Add(-pSize, -pSize, -pSize, aMinU, aMinV);
	Add(-pSize,  pSize,  pSize, aMaxU, aMaxV);
	Add(-pSize, -pSize,  pSize, aMaxU, aMinV);
}

void FVertexBuffer::GeneratePanoCube(float pSize)
{
	//Front Face
	Add(-pSize, -pSize, -pSize, 1.0f, 0.0f);
	Add(-pSize,  pSize, -pSize, 1.0f, 1.0f);
	Add(pSize, -pSize, -pSize, 0.0f, 0.0f);
	Add(pSize,  pSize, -pSize, 0.0f, 1.0f);
	// Back Face
	
	Add(-pSize, -pSize,  pSize, 0.0f, 0.0f);
	Add(pSize, -pSize,  pSize, 1.0f, 0.0f);
	Add(-pSize,  pSize,  pSize, 0.0f, 1.0f);
	Add(pSize,  pSize,  pSize, 1.0f, 1.0f);
	
	// Right Face
	Add(-pSize, -pSize,  pSize, 1.0f, 0.0f);
	Add(-pSize,  pSize,  pSize, 1.0f, 1.0f);
	Add(-pSize, -pSize, -pSize, 0.0f, 0.0f);
	Add(-pSize,  pSize, -pSize, 0.0f, 1.0f);
	
	// Left Face
	Add(pSize, -pSize, -pSize, 1.0f, 0.0f);
	Add(pSize,  pSize, -pSize, 1.0f, 1.0f);
	Add(pSize, -pSize,  pSize, 0.0f, 0.0f);
	Add(pSize,  pSize,  pSize, 0.0f, 1.0f);
	
	// Top Face
	Add(-pSize, -pSize,  pSize, 1.0f, 0.0f);
	Add(-pSize, -pSize, -pSize, 1.0f, 1.0f);
	Add(pSize, -pSize,  pSize, 0.0f, 0.0f);
	Add(pSize, -pSize, -pSize, 0.0f, 1.0f);
	
	// Bottom Face
	Add(-pSize,  pSize,  pSize, 1.0f, 1.0f);
	Add(pSize,  pSize,  pSize, 0.0f, 1.0f);
	Add(-pSize,  pSize, -pSize, 1.0f, 0.0f);
	Add(pSize,  pSize, -pSize, 0.0f, 0.0f);
}


void FVertexBuffer::GenerateCube(float aSize)
{
	Add(-aSize, -aSize, aSize, 0, 0);
	Add(-aSize, aSize, aSize, 0, 0.25f);
	Add(aSize, -aSize, aSize, 0.25f, 0);
	
	Add(aSize, -aSize, aSize, 0.25f, 0);
	Add(-aSize, aSize, aSize, 0, 0.25f);
	Add(aSize, aSize, aSize, 0.25f, 0.25f);
	
	//Back Face
	Add(-aSize, aSize, -aSize, 0.75f, 0.5f);
	Add(-aSize, -aSize, -aSize, 0.75f, 0.75f);
	Add(aSize, -aSize, -aSize, 1.0f, 0.75f);
	
	Add(-aSize, aSize, -aSize, 0.75f, 0.5f);
	Add(aSize, -aSize, -aSize, 1.0f, 0.75f);
	Add(aSize, aSize, -aSize, 1.0f, 0.5f);
	
	//Top Face
	Add(-aSize, -aSize, -aSize, 0.25f, 0.25f);
	Add(-aSize, -aSize, aSize, 0.25f, 0.5f);
	Add(aSize, -aSize, -aSize, 0.5f, 0.25f);
	
	Add(-aSize, -aSize, aSize, 0.25f, 0.5f);
	Add(aSize, -aSize, aSize, 0.5f, 0.5f);
	Add(aSize, -aSize, -aSize, 0.5f, 0.25f);
	
	
	//Bottom Face
	Add(-aSize, aSize, aSize, 0.5f, 0.5f);
	Add(-aSize, aSize, -aSize, 0.5f, 0.75f);
	Add(aSize, aSize, -aSize, 0.75f, 0.75f);
	
	Add(aSize, aSize, aSize, 0.75f, 0.5f);
	Add(-aSize, aSize, aSize, 0.5f, 0.5f);
	Add(aSize, aSize, -aSize, 0.75f, 0.75f);
	
	
	//Right Face
	Add(aSize, -aSize, -aSize, 0.25f, 0);
	Add(aSize, -aSize, aSize, 0.25f, 0.25f);
	Add(aSize, aSize, -aSize, 0.5f, 0);
	
	Add(aSize, -aSize, aSize, 0.25f, 0.25f);
	Add(aSize, aSize, aSize, 0.5f, 0.25f);
	Add(aSize, aSize, -aSize, 0.5f, 0);
	
	//Left Face
	Add(-aSize, -aSize, aSize, 0.5f, 0.5f);
	Add(-aSize, -aSize, -aSize, 0.75f, 0.5f);
	Add(-aSize, aSize, -aSize, 0.75f, 0.25f);
	
	Add(-aSize, aSize, aSize, 0.5f, 0.25f);
	Add(-aSize, -aSize, aSize, 0.5f, 0.5f);
	Add(-aSize, aSize, -aSize, 0.75f, 0.25f);
}


