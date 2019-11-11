#include "FSpline.hpp"
#include "core_includes.h"

//#include <string>
//#include <string.h>

#include "FFile.hpp"

#define _CRT_SECURE_NO_DEPRECATE 1

FSpline::FSpline(void)
{
	mSize=0;
	mMax=0;
	mPointCount=0;
    
	mX=0;
	mY=0;
    
	mXCoef=0;
	mYCoef=0;
    
    mStorageDelta = NULL;
    mStorageTemp = NULL;
    
	mProperties=0;
    
	mTangent=0;
	mLength=0;
    
	mChanged=true;
}

FSpline::~FSpline(void)
{
	Clear();
}

void FSpline::Translate(float theXDistance, float theYDistance)
{
	for(int i=0;i<mPointCount;i++)
	{
		mX[i]+=theXDistance;
		mY[i]+=theYDistance;
	}
}

void FSpline::InvertH(float theCenter) {
	for(int i=0;i<mPointCount;i++)mX[i]=theCenter+(theCenter-mX[i]);
	int aMax=mMax*3;
	for(int i=0;i<aMax;i++)mXCoef[i]=-mXCoef[i];
}

void FSpline::Reset() {
    mPointCount = 0;
    mMax = 0;
    mProperties = 0;
    mLength = 0;
    mChanged = true;
}

void FSpline::RemoveAll() {
    mPointCount = 0;
    mMax = 0;
    mLength = 0.0f;
    mChanged = true;
}


void FSpline::Clear()
{
	delete [] mX;
	delete [] mXCoef;
	delete [] mTangent;
	mX = NULL;
	mY = NULL;
	mXCoef = NULL;
	mYCoef = NULL;
	mTangent = NULL;
    mStorageDelta = NULL;
    mStorageTemp = NULL;
    
	mSize = 0;
	mPointCount = 0;
	mMax = 0;
	mProperties = 0;
	mLength = 0;
	mChanged = true;
}

void FSpline::Size(int size)
{
	if(size>0)
	{
		if(mSize!=size)
		{
			mChanged=true;
			float *aX;//=new float[size*5];
			float *aY;//=aX+size;
			aX=new float[size*2];
			aY=aX+size;
            if (size < mPointCount) { mPointCount=size; }
            for (int i=0;i<mPointCount;i++) { aX[i]=mX[i]; }
            for (int i=0;i<mPointCount;i++) { aY[i]=mY[i]; }
            
            delete [] mX;
            
            mX = aX;
            mY = aY;
            
            
            
            delete [] mXCoef;
            
            mXCoef = new float[size*8];
            mYCoef = mXCoef+3*size;
            
            mStorageDelta = mYCoef+3*size;
            mStorageTemp = mStorageDelta + size;
            
			if (mProperties&SPLINE_MANUAL_TANGENTS) {
				float *aXTan=new float[size*3];
				float *aYTan=aXTan+size;
				float *aTan=aYTan+size;
				float *aXTanSource=mTangent;
				float *aYTanSource=mTangent+mSize;
				float *aTanSource=aYTanSource+mSize;
				if(mSize>size)mSize=size;
				for(int i=0;i<mSize;i++)aXTan[i]=aXTanSource[i];
				for(int i=0;i<mSize;i++)aYTan[i]=aYTanSource[i];
				for(int i=0;i<mSize;i++)aTan[i]=aTanSource[i];
				for(int i=mSize;i<size;i++)aTan[i]=0;
				delete[]mTangent;
				mTangent=aXTan;
			}
            
			mSize = size;
		}
	} else {
		Clear();
	}
}

void FSpline::Clone(FSpline *pFSpline)
{
    Clear();
    
    if(pFSpline == 0)return;
    
    mProperties = pFSpline->mProperties;
    
    int aPointCount = pFSpline->mPointCount;
    
    for(int i=0;i<aPointCount;i++)
    {
        Add(pFSpline->mX[i], pFSpline->mY[i]);
    }
    
    Solve();
}

void FSpline::Add(float x,float y)
{
    
    if (mSize >= mPointCount) {
        Size(mPointCount + mPointCount / 2 + 1);
    }
	
    //if(mProperties&SPLINE_CLOSED&&mMax>0){mProperties&=~SPLINE_CLOSED;mMax--;}
	if(mProperties&SPLINE_CLOSED&&mPointCount>0){Delete(mMax);mProperties&=~SPLINE_CLOSED;}
	//if((!(mProperties&SPLINE_ALLOW_SAME_POINT_TWICE_IN_ROW))&&mPointCount>0)if(mX[mMax]==x&&mY[mMax]==y){return;}
	
    mX[mPointCount] = x;
	mY[mPointCount] = y;
	
    ++mPointCount;
	mChanged = true;
}

void FSpline::SetPoint(int theIndex,float x, float y)
{
	//if(theIndex<0||theIndex>=mPointCount)return;
    if(theIndex < 0)return;
    
    if(theIndex >= mPointCount)
    {
        Size(theIndex + (theIndex / 2) + 1);
        mPointCount = (theIndex + 1);
    }
    
	if ((mProperties&SPLINE_CLOSED) && mPointCount > 0) {
		Delete(mMax);
        mProperties &= ~SPLINE_CLOSED;
        if (theIndex == mPointCount) { theIndex=0; }
	}
    
	mX[theIndex] = x;
	mY[theIndex] = y;
	mChanged = true;
}

int FSpline::GetClosestControlIndex(float x, float y, float &dist)
{
	dist=-1;
	int aResult=-1;
	if(mPointCount>1)
	{
		aResult=0;
		float aDiffX=mX[0]-x;
		float aDiffY=mY[0]-y;
		dist=aDiffX*aDiffX+aDiffY*aDiffY;
		float aDist;
		for(int i=1;i<mPointCount;i++)
		{
			aDiffX=mX[i]-x;
			aDiffY=mY[i]-y;
			aDist=aDiffX*aDiffX+aDiffY*aDiffY;
			if(aDist<dist)
			{
				dist=aDist;
				aResult=i;
			}
		}
	}
	return aResult;
}

void FSpline::Insert(int theIndex,float x, float y)
{
	if(mSize==mPointCount)Size(mSize+mSize/2+1);
	if(mProperties&SPLINE_CLOSED&&mPointCount>0){Delete(mMax);mProperties&=~SPLINE_CLOSED;}
	if(theIndex<0)theIndex=0;
	if(theIndex>mPointCount)theIndex=mPointCount;
	for(int i=mPointCount-1;i>=theIndex;i--)mX[i+1]=mX[i];
	for(int i=mPointCount-1;i>=theIndex;i--)mY[i+1]=mY[i];
	if(mProperties&SPLINE_MANUAL_TANGENTS)
	{
		float*aTan=mTangent;
		for(int i=mSize-2;i>=theIndex;i--)aTan[i+1]=aTan[i];
		aTan+=mSize;
		for(int i=mSize-2;i>=theIndex;i--)aTan[i+1]=aTan[i];
		aTan+=mSize;
		for(int i=mSize-2;i>=theIndex;i--)aTan[i+1]=aTan[i];
		aTan[theIndex]=0;
	}
	mX[theIndex]=x;
	mY[theIndex]=y;
	//mMax=
	mPointCount++;
	mChanged=true;
}

void FSpline::Delete(int theIndex)
{
	if(theIndex<0)return;
	if(theIndex<mPointCount)
	{
		for(int i=theIndex;i<mPointCount;i++)mX[i]=mX[i+1];
		for(int i=theIndex;i<mPointCount;i++)mY[i]=mY[i+1];
		if(mPointCount)mPointCount--;
		mChanged=true;
	}
	if(theIndex<mSize&&(mProperties&SPLINE_MANUAL_TANGENTS))
	{
		float*aTan=mTangent;
		for(int i=theIndex;i<mSize;i++)aTan[i]=aTan[i+1];aTan+=mSize;
		for(int i=theIndex;i<mSize;i++)aTan[i]=aTan[i+1];aTan+=mSize;
		for(int i=theIndex;i<mSize;i++)aTan[i]=aTan[i+1];
		mChanged=true;
	}
}

void FSpline::SetTangent(int theIndex,float xtan,float ytan)
{
	if(theIndex>=0)
	{
		if(theIndex>=mSize)Size(theIndex+theIndex/2+1);
		if(!(mProperties&SPLINE_MANUAL_TANGENTS))
		{
			mProperties|=SPLINE_MANUAL_TANGENTS;
			int aSize=mSize*3;
			mTangent=new float[aSize];
			for(int i=0;i<aSize;i++)mTangent[i]=0;
		}
		mTangent[theIndex]=xtan;
		mTangent[theIndex+mSize]=ytan;
		mTangent[theIndex+(mSize<<1)]=1;//theIndex+mSize*2
		mChanged=true;
	}
}

void FSpline::Solve(float *theCoordinate,float*theDelta,float*theDerivative,float*theTemp,float*theCoef,bool linear,bool circular)
{
	if(mPointCount > 1)
	{
		float *aDer=mTangent+mSize+mSize;
		unsigned int aCoefOffStart=0;
		if(mPointCount==2&&((mProperties&SPLINE_MANUAL_TANGENTS)!=0))
		{
            
			if(circular)
			{
				if(!aDer[0])theDerivative[0]=-theDerivative[1];
				if(!aDer[1])theDerivative[1]=-theDerivative[0];
				theCoef[aCoefOffStart++]=theDerivative[0];
				theCoef[aCoefOffStart++]=3*(theCoordinate[1]-theCoordinate[0])-2*theDerivative[0]-theDerivative[1];
				theCoef[aCoefOffStart++]=2*(theCoordinate[0]-theCoordinate[1])+theDerivative[0]+theDerivative[1];
				theCoef[aCoefOffStart++]=theDerivative[1];
				theCoef[aCoefOffStart++]=3*(theCoordinate[0]-theCoordinate[1])-2*theDerivative[1]-theDerivative[0];
				theCoef[aCoefOffStart++]=2*(theCoordinate[1]-theCoordinate[0])+theDerivative[1]+theDerivative[0];
			}
			else
			{
				if(!aDer[0])theDerivative[0]=0;
				if(!aDer[1])theDerivative[1]=0;
				theCoef[aCoefOffStart++]=theDerivative[0];
				theCoef[aCoefOffStart++]=3*(theCoordinate[1]-theCoordinate[0])-2*theDerivative[0]-theDerivative[1];
				theCoef[aCoefOffStart++]=2*(theCoordinate[0]-theCoordinate[1])+theDerivative[0]+theDerivative[1];
			}
		}
		else if(linear||mPointCount==2)
		{
			for(int i=1,j=0;i<mPointCount;j=i++)
			{
				theCoef[aCoefOffStart++]=theCoordinate[i]-theCoordinate[j];
				theCoef[aCoefOffStart++]=0;
				theCoef[aCoefOffStart++]=0;
			}
			if(circular)
			{
				theCoef[aCoefOffStart++]=theCoordinate[0]-theCoordinate[mPointCount-1];
				theCoef[aCoefOffStart++]=0;
				theCoef[aCoefOffStart++]=0;
			}
		}
		else
		{
			int aMax;
			int aMax1;
			if(circular)
			{
				aMax=mPointCount-1;
				aMax1=aMax-1;
				theDelta[1]=0.25f;
				theTemp[0]=0.25f*3*(theCoordinate[1]-theCoordinate[aMax]);
				float G=1.0f,H=4.0f,F=3.0f*(theCoordinate[0]-theCoordinate[aMax1]);
				for(int i=1;i<aMax;i++)
				{
					theDelta[i+1]=-0.25f*theDelta[i];
					theTemp[i]=0.25f*(3*(theCoordinate[i+1]-theCoordinate[i-1])-theTemp[i-1]);
					H=H-G*theDelta[i];
					F=F-G*theTemp[i-1];
					G=-0.25f*G;
				}
				H=H-(G+1)*(0.25f+theDelta[aMax]);
				theTemp[aMax]=F-(G+1)*theTemp[aMax1];
				if(!aDer[aMax])theDerivative[aMax]=theTemp[aMax]/H;
				if(!aDer[aMax1])theDerivative[aMax1]=theTemp[aMax1]-(0.25f+theDelta[aMax])*theDerivative[aMax];
				for(int i=aMax-2;i>=0;i--)
				{
					if(!aDer[i])
					{
						theDerivative[i]=theTemp[i]-0.25f*theDerivative[i+1]-theDelta[i+1]*theDerivative[aMax];
					}
				}
				int aIndex=aMax*3;
				theCoef[aIndex]=theDerivative[aMax];
				theCoef[aIndex+1]=3*(theCoordinate[0]-theCoordinate[aMax])-2*theDerivative[aMax]-theDerivative[0];
				theCoef[aIndex+2]=2*(theCoordinate[aMax]-theCoordinate[0])+theDerivative[aMax]+theDerivative[0];
			}
			else
			{
				aMax=mMax;
				aMax1=aMax-1;
				theDelta[0]=3.0f*(theCoordinate[1]-theCoordinate[0])*0.25f;
				for(int i=1;i<aMax;i++)theDelta[i]=(3.0f*(theCoordinate[i+1]-theCoordinate[i-1])-theDelta[i-1])*0.25f;
				theDelta[aMax]=(3.0f*(theCoordinate[aMax]-theCoordinate[aMax1])-theDelta[aMax1])*0.25f;
				if(!aDer[aMax])theDerivative[aMax]=theDelta[aMax];
				for(int i=aMax1;i>=0;i--)
				{
					if(!aDer[i])
					{
						theDerivative[i]=theDelta[i]-0.25f*theDerivative[i+1];
					}
				}
			}
			for(int i=0;i<aMax;i++)
			{
				theCoef[aCoefOffStart++]=theDerivative[i];
				theCoef[aCoefOffStart++]=3*(theCoordinate[i+1]-theCoordinate[i])-2*theDerivative[i]-theDerivative[i+1];
				theCoef[aCoefOffStart++]=2*(theCoordinate[i]-theCoordinate[i+1])+theDerivative[i]+theDerivative[i+1];
			}
		}
	}
}

void FSpline::Solve(float *theCoordinate,float*theDelta,float*theDerivative,float*theCoef,bool linear,bool circular)
{
	if(mPointCount > 1)
	{
		unsigned int aCoefOffStart=0;
		if(linear||mPointCount==2)
		{
			for(int i=1,j=0;i<mPointCount;j=i++)
			{
				theCoef[aCoefOffStart++]=theCoordinate[i]-theCoordinate[j];
				theCoef[aCoefOffStart++]=0;
				theCoef[aCoefOffStart++]=0;
			}
			if(circular)
			{
				theCoef[aCoefOffStart++]=theCoordinate[0]-theCoordinate[mPointCount-1];
				theCoef[aCoefOffStart++]=0;
				theCoef[aCoefOffStart++]=0;
			}
		}
		else
		{
			int aMax;
			int aMax1;
			if(circular)
			{
				aMax=mPointCount-1;
				aMax1=aMax-1;
				theDelta[1]=0.25f;
				theDerivative[0]=0.25f*3*(theCoordinate[1]-theCoordinate[aMax]);
				float G=1.0f,H=4.0f,F=3.0f*(theCoordinate[0]-theCoordinate[aMax1]);
				for(int i=1;i<aMax;i++)
				{
					theDelta[i+1]=-0.25f*theDelta[i];
					theDerivative[i]=0.25f*(3*(theCoordinate[i+1]-theCoordinate[i-1])-theDerivative[i-1]);
					H=H-G*theDelta[i];
					F=F-G*theDerivative[i-1];
					G=-0.25f*G;
				}
				H=H-(G+1)*(0.25f+theDelta[aMax]);
				theDerivative[aMax]=F-(G+1)*theDerivative[aMax1];
				theDerivative[aMax]=theDerivative[aMax]/H;
				theDerivative[aMax1]=theDerivative[aMax1]-(0.25f+theDelta[aMax])*theDerivative[aMax];
				for(int i=aMax-2;i>=0;i--)theDerivative[i]=theDerivative[i]-0.25f*theDerivative[i+1]-theDelta[i+1]*theDerivative[aMax];
				int aIndex=aMax*3;
				theCoef[aIndex]=theDerivative[aMax];
				theCoef[aIndex+1]=3*(theCoordinate[0]-theCoordinate[aMax])-2*theDerivative[aMax]-theDerivative[0];
				theCoef[aIndex+2]=2*(theCoordinate[aMax]-theCoordinate[0])+theDerivative[aMax]+theDerivative[0];
			}
			else
			{
				aMax=mMax;
				aMax1=aMax-1;
				theDelta[0]=3.0f*(theCoordinate[1]-theCoordinate[0])*0.25f;
				for(int i=1;i<aMax;i++)theDelta[i]=(3.0f*(theCoordinate[i+1]-theCoordinate[i-1])-theDelta[i-1])*0.25f;
				theDelta[aMax]=(3.0f*(theCoordinate[aMax]-theCoordinate[aMax1])-theDelta[aMax1])*0.25f;
				theDerivative[aMax]=theDelta[aMax];
				for(int i=aMax1;i>=0;i--)theDerivative[i]=theDelta[i]-0.25f*theDerivative[i+1];
			}
			for(int i=0;i<aMax;i++)
			{
				theCoef[aCoefOffStart++]=theDerivative[i];
				theCoef[aCoefOffStart++]=3*(theCoordinate[i+1]-theCoordinate[i])-2*theDerivative[i]-theDerivative[i+1];
				theCoef[aCoefOffStart++]=2*(theCoordinate[i]-theCoordinate[i+1])+theDerivative[i]+theDerivative[i+1];
			}
		}
	}
}


void FSpline::Solve(bool linear,bool circular)
{
	mChanged=false;
	
    //delete[]mXCoef;
	//mXCoef=0;
	//mYCoef=0;
    
	mMax=0;
	mProperties&=~SPLINE_CLOSED;
	mProperties&=~SPLINE_LINEAR;
	if(mPointCount>1)
	{
		mMax=mPointCount-1;
		if(circular)
		{
			mProperties|=SPLINE_CLOSED;
			mMax++;
		}
		Size(mPointCount);
		if(linear)mProperties|=SPLINE_LINEAR;
		//if(linear||(mPointCount==2&&!(mProperties&SPLINE_MANUAL_TANGENTS)))mProperties|=SPLINE_LINEAR;
		
		if(mProperties&SPLINE_MANUAL_TANGENTS) {
			Solve(mX,mStorageDelta,mTangent,mStorageTemp,mXCoef,linear,circular);
			Solve(mY,mStorageDelta,mTangent+mSize,mStorageTemp,mYCoef,linear,circular);
		} else {
			Solve(mX,mStorageDelta,mStorageTemp,mXCoef,linear,circular);
			Solve(mY,mStorageDelta,mStorageTemp,mYCoef,linear,circular);
		}
	}
}

float FSpline::Rot(float pos)
{
	if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
	if(mXCoef)
	{
		float aTanX, aTanY;
		Tan(pos,aTanX,aTanY);
		return -atan2f(aTanX,aTanY)*180.0f/3.1415925511f;
	}
	return 0;
}

void FSpline::Tan(float pos,float &x,float &y)
{
	if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
	if(mXCoef)
	{
		int aIndex=(int)pos;
		if(pos<0){aIndex=0;pos=0;}
		if(aIndex>=mMax){aIndex=mMax-1;pos=(float)(aIndex+1);}
		float aPos=pos-(float)aIndex;
		float aPos2=aPos*aPos;
		//3duu+2cu+b
		aIndex=((aIndex<<1)+aIndex);//aIndex*3
		x=3.0f*mXCoef[aIndex+2]*aPos2+2.0f*mXCoef[aIndex+1]*aPos+mXCoef[aIndex];
		//aIndex+=((mMax<<1)+mMax);//aIndex+=mMax*3;
		y=3.0f*mYCoef[aIndex+2]*aPos2+2.0f*mYCoef[aIndex+1]*aPos+mYCoef[aIndex];
		return;
	}
	x=0;
	y=0;
}

//We may use this to smooth curves -- and the curves are not all necessarily smooth.
//So, we will step back one and assume t=1 instead of staying in place with t=0.
void FSpline::Tan(int pos,float &x,float &y)
{
	if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
	if(mXCoef)
	{
		if(pos<=0)
		{
			x=mXCoef[0];
			y=mYCoef[0];//mMax*3
			return;
		}
		pos--;
		if(pos>=mMax)pos=mMax-1;
		pos=(pos<<1)+pos;//pos*3
		x=3.0f*mXCoef[pos+2]+2.0f*mXCoef[pos+1]+mXCoef[pos];
		//pos=pos+(mMax<<1)+mMax;//mMax*3
		y=3.0f*mYCoef[pos+2]+2.0f*mYCoef[pos+1]+mYCoef[pos];
		return;
	}
	x=0;
	y=0;
}

float FSpline::GetX(float pos)
{
    if(mProperties&SPLINE_CLOSED)
    {
        if(mMax > 0)
        {
            if(pos < 0 || pos > (float)mMax)
            {
                pos = fmodf(pos, mMax);
                if(pos < 0)
                {
                    pos += (float)mMax;
                }
            }
        }
    }
	if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
	if(mXCoef)
	{
		int aIndex=(int)pos;
		if(pos<0)
		{
			return*mX;
		}
		float aPos=pos-(float)aIndex;
		if(aIndex>=mMax)
		{
			aIndex=mMax-1;
			aPos=1;
		}
		float aPos2=aPos*aPos;
		float aPos3=aPos*aPos2;

		int aCoefIndex=((aIndex<<1)+aIndex);//aIndex*3
		//duuu+cuu+bu+a
		return mX[aIndex]+mXCoef[aCoefIndex]*aPos+mXCoef[aCoefIndex+1]*aPos2+mXCoef[aCoefIndex+2]*aPos3;
	}
	return 0;
}

float FSpline::GetY(float pos)
{
    if(mProperties&SPLINE_CLOSED)
    {
        if(mMax > 0)
        {
            if(pos < 0 || pos > (float)mMax)
            {
                pos = fmodf(pos, mMax);
                if(pos < 0)
                {
                    pos += (float)mMax;
                }
            }
        }
    }
	if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
	if(mXCoef)
	{
		int aIndex=(int)pos;
		if(pos<0)
		{
			return*mY;
		}
		float aPos=pos-(float)aIndex;
		if(aIndex>=mMax)
		{
			aIndex=mMax-1;
			aPos=1;
		}
		float aPos2=aPos*aPos;
		float aPos3=aPos*aPos2;
		int aCoefIndex=((aIndex<<1)+aIndex);//+((mMax<<1)+mMax);
		//duuu+cuu+bu+a
		return mY[aIndex]+mYCoef[aCoefIndex]*aPos+mYCoef[aCoefIndex+1]*aPos2+mYCoef[aCoefIndex+2]*aPos3;
	}
	return 0;
}

void FSpline::Get(float pos,float&x,float&y)
{
	if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
	if(mXCoef)
	{
		if(IsCircular())
		{
			if(pos<0||pos>(float)mMax)
			{
				pos=fmodf(pos,(float)mMax);
				if(pos<0)pos+=(float)mMax;
			}
		}
		int aIndex=(int)pos;
		if(pos<0)
		{
			x=*mX;
			y=*mY;
			return;
		}
		float aPos=pos-(float)aIndex;
		if(aIndex>=mMax)
		{
			aIndex=mMax-1;
			aPos=1;
		}
		x=mX[aIndex];
		y=mY[aIndex];
		aIndex=((aIndex<<1)+aIndex);//aIndex*3
		x+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
		y+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
		return;
	}
	x=0;
	y=0;
}

void FSpline::Get(int pos,float&x,float&y)
{
	if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
	if(mPointCount>0)
	{
		if(pos<0){x=*mX;y=*mY;return;}
		
		if(pos>=mPointCount)
		{
			if(mProperties&SPLINE_CLOSED)
			{
				x=*mX;y=*mY;return;
			}
			else
			{
				x=mX[mPointCount-1];y=mY[mPointCount-1];return;
			}
		}
		x=mX[pos];y=mY[pos];return;
	}
	x=0;
	y=0;
}

float FSpline::GetClosestPosition(float x, float y, float &pDist)
{
	if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
	if(!mXCoef||mPointCount<2)return 0;
#define CP_FIDELITY 0.10f
	float aX, aY, aLastX, aLastY;
	aLastX=mX[0];
	aLastY=mY[0];
	int aIndex=(int)CP_FIDELITY;
	float aPos=CP_FIDELITY-(float)aIndex;
	if(aIndex>=mMax)
	{
		aIndex=mMax-1;
		aPos=1;
	}
	aX=mX[aIndex];
	aY=mY[aIndex];
	aIndex=((aIndex<<1)+aIndex);
	aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
	aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
	float aDirX=aX-aLastX;
	float aDirY=aY-aLastY;
	float aDiffX=x-aLastX;
	float aDiffY=y-aLastY;
	float aFactor=(aDirX*aDiffX+aDirY*aDiffY)/(aDirX*aDirX+aDirY*aDirY);
	float aClosestX;
	float aClosestY;
	if(aFactor<0)
	{
		aClosestX=aLastX;
		aClosestY=aLastY;
	}
	else if(aFactor>1)
	{
		aClosestX=aX;
		aClosestY=aY;
	}
	else
	{
		aClosestX=aLastX+aFactor*aDirX;
		aClosestY=aLastY+aFactor*aDirY;
	}
	aDiffX=x-aClosestX;
	aDiffY=y-aClosestY;
	float aBestDist=aDiffX*aDiffX+aDiffY*aDiffY;
	float aBestPos=CP_FIDELITY;
	float aBestFactor=aFactor;
	float aCurDist;
	float aMax=(float)mMax+CP_FIDELITY*0.5f;
	for(float i=CP_FIDELITY+CP_FIDELITY;i<=aMax;i+=CP_FIDELITY)
	{
		aLastX=aX;
		aLastY=aY;
		aIndex=(int)i;
		aPos=i-(float)aIndex;
		if(aIndex>=mMax)
		{
			aIndex=mMax-1;
			aPos=1;
		}
		aX=mX[aIndex];
		aY=mY[aIndex];
		aIndex=((aIndex<<1)+aIndex);
		aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
		aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
		aDirX=aX-aLastX;
		aDirY=aY-aLastY;
		aDiffX=x-aLastX;
		aDiffY=y-aLastY;
		aFactor=(aDirX*aDiffX+aDirY*aDiffY)/(aDirX*aDirX+aDirY*aDirY);
		if(aFactor<0)
		{
			aClosestX=aLastX;
			aClosestY=aLastY;
		}
		else if(aFactor>1)
		{
			aClosestX=aX;
			aClosestY=aY;
		}
		else
		{
			aClosestX=aLastX+aFactor*aDirX;
			aClosestY=aLastY+aFactor*aDirY;
		}
		aDiffX=x-aClosestX;
		aDiffY=y-aClosestY;
		aCurDist=aDiffX*aDiffX+aDiffY*aDiffY;
		if(aCurDist<aBestDist)
		{
			aBestDist=aCurDist;
			aBestPos=i;
			aBestFactor=aFactor;
		}
	}
	pDist=aBestDist;
	if(aBestFactor<0)aBestFactor=0;
	if(aBestFactor>1)aBestFactor=1;
	aBestPos=aBestPos-CP_FIDELITY*(1-aBestFactor);
	return aBestPos;
}

bool FSpline::GetNextPointSloppy(float &x, float &y, float &t,float theDistance)
{
	float aX,aY;
	float aDiffX,aDiffY;
	float aMin=t;
	t+=0.01f;
	float aCount=(float)mMax;
	Get(t,aX,aY);
	aDiffX=aX-x;
	aDiffY=aY-y;
	float aDist=aDiffX*aDiffX+aDiffY*aDiffY;
	theDistance*=theDistance;
	while(aDist<theDistance&&t<aCount)
	{
		aMin=t;
		t+=0.01f;
		Get(t,aX,aY);
		aDiffX=aX-x;
		aDiffY=aY-y;
		aDist=aDiffX*aDiffX+aDiffY*aDiffY;
	}
	float aMid=(t+aMin)*0.5f;
	while(fabsf(aMin-t)>(0.001f))
	{
		Get(aMid,aX,aY);
		aDiffX=aX-x;
		aDiffY=aY-y;
		aDist=aDiffX*aDiffX+aDiffY*aDiffY;
		if(aDist<theDistance)aMin=aMid;
		else t=aMid;
		aMid=(t+aMin)*0.5f;
	}
	x=aX;
	y=aY;
	return!(aDist<theDistance*0.5f);
}

bool FSpline::GetNextPoint(float &x, float &y, float &t,float theDistance)
{
	float aX,aY;
	float aDiffX,aDiffY;
	float aMin=t;
	t+=SPLINE_SHORT_STEP;
	float aCount=(float)mMax;
	Get(t,aX,aY);
	aDiffX=aX-x;
	aDiffY=aY-y;
	float aDist=aDiffX*aDiffX+aDiffY*aDiffY;
	theDistance*=theDistance;
	while(aDist<theDistance&&t<aCount)
	{
		aMin=t;
		t+=SPLINE_SHORT_STEP;
		Get(t,aX,aY);
		aDiffX=aX-x;
		aDiffY=aY-y;
		aDist=aDiffX*aDiffX+aDiffY*aDiffY;
	}
	float aMid=(t+aMin)*0.5f;
	while(fabsf(aMin-t)>SPLINE_EPSILON)
	{
		Get(aMid,aX,aY);
		aDiffX=aX-x;
		aDiffY=aY-y;
		aDist=aDiffX*aDiffX+aDiffY*aDiffY;
		if(aDist<theDistance)aMin=aMid;
		else t=aMid;
		aMid=(t+aMin)*0.5f;
	}
	x=aX;
	y=aY;
	return!(aDist<theDistance*0.5f);
}


/*
float FSpline::GetLength(float pStart,float pEnd)
{
    float aDiffX, aDiffY, aDist, aX, aY;
    float aLastX, aLastY;
    
    if(pStart > pEnd)
    {
        float aHold = pStart;
        pStart = pEnd;
        pEnd = pStart;
    }
    
    float aResult=0;
    
    for(float i=pStart;i<=pEnd;i+=0.01f)
    {
        aX=GetX(i);
        aY=GetY(i);
        
        
        
    }
    
    
}
*/

float FSpline::LengthPredict(float pStepSpeed)
{
    float aResult = 0.0f;
    
    float aMax = Max();
    
    float aLastX = 0.0f;
    float aLastY = 0.0f;
    
    float aX = 0.0f;
    float aY = 0.0f;
    
    
    Get(0.0f, aLastX, aLastY);
    //pStepSpeed
    
    float aDiffX = 0.0f;
    float aDiffY = 0.0f;
    float aDist = 0.0f;
    
    
    for(float aPos=pStepSpeed;aPos<=aMax;aPos+=pStepSpeed)
    {
        Get(aPos, aX, aY);
        
        aDiffX = aX - aLastX;
        aDiffY = aY - aLastY;
        
        aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        if(aDist > 0.01f)aDist = sqrtf(aDist);
        
        aResult += aDist;
        
        aLastX = aX;
        aLastY = aY;
    }
    
    return aResult;
}

float FSpline::GetLength(float start,float end)
{
    
	int aMax=mPointCount-1;
	if(mProperties&SPLINE_CLOSED)aMax++;
	if(end<0||end>=(float)aMax)
	{
		if((!mChanged)&&(mLength>=0)&&(start==0)&&(end<0))
		{
			return mLength;
		}
		end=(float)aMax;
	}
	if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
	if(start<0)start=0;
	if(end<=start||!mXCoef)return 0;
	float aLastX,aLastY,aX,aY,aDiffX,aDiffY,aDist,aPos;
	float aResult=0;
	int aIndex;
    /*
	if(mProperties&SPLINE_LINEAR)
	{
		int aStart=(int)start;
		int aEnd=(int)end;
		if(aStart==aEnd)
		{
			aResult=mArcLength[aStart]*(end-start);
		}
		else
		{
			float aStartFactor=1-(start-(float)aStart);
			float aEndFactor=end-(float)aEnd;
			aResult=mArcLength[aStart]*aStartFactor + mArcLength[aEnd]*aEndFactor;
			aStart++;
			while(aStart<aEnd)aResult+=mArcLength[aStart++];
		}
	}
	else
	{
    */
		aIndex=(int)start;
		aPos=start-(float)aIndex;
		if(aIndex>=mMax)
		{
			aIndex=mMax-1;
			aPos=1;
		}
		aLastX=mX[aIndex];
		aLastY=mY[aIndex];
		aIndex=((aIndex<<1)+aIndex);
		aLastX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
		aLastY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
		float aMid;
		float aSeek=start,aMin=0;
		while(aSeek<end)
		{

			aIndex=(int)aSeek;
			aPos=aSeek-(float)aIndex;
			if(aIndex>=mMax)
			{
				aIndex=mMax-1;
				aPos=1;
			}
			aX=mX[aIndex];
			aY=mY[aIndex];
			aIndex=((aIndex<<1)+aIndex);
			aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
			aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
			aDiffX=aX-aLastX;
			aDiffY=aY-aLastY;
			aDist=aDiffX*aDiffX+aDiffY*aDiffY;
			while(aDist<1&&aSeek<end)
			{
				aMin=aSeek;
				aSeek+=SPLINE_SHORT_STEP;

				aIndex=(int)aSeek;
				aPos=aSeek-(float)aIndex;
				if(aIndex>=mMax)
				{
					aIndex=mMax-1;
					aPos=1;
				}
				aX=mX[aIndex];
				aY=mY[aIndex];
				aIndex=((aIndex<<1)+aIndex);
				aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
				aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
				
				//Get(aSeek,aX,aY);
				
				aDiffX=aX-aLastX;
				aDiffY=aY-aLastY;
				aDist=aDiffX*aDiffX+aDiffY*aDiffY;
			}
			aMid=(aSeek+aMin)*0.5f;
			while(fabsf(aMin-aSeek)>SPLINE_EPSILON)
			{
				aIndex=(int)aMid;
				aPos=aMid-(float)aIndex;
				if(aIndex>=mMax)
				{
					aIndex=mMax-1;
					aPos=1;
				}
				aX=mX[aIndex];
				aY=mY[aIndex];
				aIndex=((aIndex<<1)+aIndex);
				aX+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
				aY+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
				
				//Get(aMid,aX,aY);
				aDiffX=aX-aLastX;
				aDiffY=aY-aLastY;
				aDist=aDiffX*aDiffX+aDiffY*aDiffY;
				if(aDist<1)aMin=aMid;
				else aSeek=aMid;
				aMid=(aSeek+aMin)*0.5f;
			}
			aResult+=aDist;
			aLastX=aX;
			aLastY=aY;
		}
		if((mProperties&SPLINE_CLOSED)&&end==(float)mMax&&start==(float)0)aResult++;
	//}
	if((end=(float)mMax)&&(start==0))
	{
		mLength=aResult;
	}
	return aResult;
}

void FSpline::SetCoefs(int theIndex, float xa, float xb, float xc, float ya, float yb, float yc)
{
	if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
	if(theIndex<=mMax&&theIndex>=0)
	{
		theIndex*=3;
		mXCoef[theIndex]=xa;
		mXCoef[theIndex+1]=xb;
		mXCoef[theIndex+2]=xc;
		mYCoef[theIndex]=ya;
		mYCoef[theIndex+1]=yb;
		mYCoef[theIndex+2]=yc;
	}
}

void FSpline::ImportData(char *theData)
{
	if(!theData)return;
	int aDataLen=(int)(strlen(theData));
	char *aRead=theData;
	if(aDataLen>0)
	{
		if(aDataLen>0)
		{
			char *aShelf=&aRead[aDataLen];
			float aLeft=0.0f;
			float aTop=0.0f;
			float aWidth=800.0f;
			float aHeight=600.0f;
			bool aFoundBox=false;
			while(aRead<aShelf)
			{
				char *aLineStart=aRead;
				while(*aRead!=0xD&&aRead<aShelf&&*aRead!=';')aRead++;
				while(*aLineStart=='%'&&aLineStart<aRead)aLineStart++;
				char *aNameStart=aLineStart;
				while(*aLineStart!=':'&&aLineStart<aRead)aLineStart++;
				if(!aFoundBox)
				{
					if(strncmp(aNameStart,"BoundingBox",(int)(aLineStart-aNameStart))==0)
					{
						aLineStart++;
						int aIter=0;
						while(aLineStart<aRead)
						{
							while(*aLineStart==' '&&aLineStart<aRead)aLineStart++;
							char *aNumStart=aLineStart;
							while(*aLineStart!=' '&&aLineStart<aRead)aLineStart++;
							int aLength=(int)(aLineStart-aNumStart);
							char *aNum=new char[aLength+1];
							aNum[aLength]=0;
							memcpy(aNum,aNumStart,aLength);
							float aFloat=(float)(atof(aNum));
							if(aIter==0)aLeft=aFloat;
							if(aIter==1)aTop=aFloat;
							if(aIter==2)aWidth=aFloat;
							if(aIter==3)aHeight=aFloat;
							aIter++;
							delete[]aNum;
						}
						if(aWidth==0)aWidth=800;
						if(aHeight==0)aHeight=600;
					}
				}
				while((*aRead<33||*aRead==';')&&aRead<aShelf)aRead++;
                
                int aCheck = aRead-aNameStart;
                if(aCheck < 0)aCheck=0;
                
				if(strncmp(aNameStart,"Note",aCheck)==0)break;
			}
			int aListSize=2;
			int aListCount=0;
			float**aList=new float*[aListSize];
			float *aFloat;

			bool aFoundGoodLine=false;

			while(aRead<aShelf)
			{
				char *aLineStart=aRead;
				while(*aRead!=0xD&&aRead<aShelf&&*aRead!=';')aRead++;
				aFloat=new float[8];
				int aIndex=2;
				bool aLoop=true;
				while(aLineStart<aRead&&aLoop&&aIndex<8)
				{
					aLoop=false;
					while(*aLineStart<=32&&aLineStart<aRead)aLineStart++;
					char *aNumStart=aLineStart;
					if((*aNumStart >= '0' && *aNumStart <= '9')||*aNumStart=='.'||*aNumStart=='-'||*aNumStart=='+')
					{
						while(*aLineStart>32&&aLineStart<aRead)aLineStart++;
						int aLength=(int)(aLineStart-aNumStart);
						char *aNum=new char[aLength+1];
						aNum[aLength]=0;
						memcpy(aNum,aNumStart,aLength);
						aFloat[aIndex++]=(float)(atof(aNum));
						aLoop=true;
						delete[]aNum;
					}
				}
				if(aIndex==4||aIndex==6||aIndex==8)
				{
					if(aListSize==aListCount)
					{
						aListSize=aListSize*2+4;
						float**aNewList=new float*[aListSize];
						for(int i=0;i<aListCount;i++)aNewList[i]=aList[i];
						delete[]aList;
						aList=aNewList;
					}
					char *aLast=aRead;
					while(aLast>=aLineStart&&!((*aLast>='a'&&*aLast<='z')||(*aLast>='A'&&*aLast<='Z')))aLast--;
					aFloat[1]=(float)*aLast;
					aFloat[0]=(float)aIndex;
					aList[aListCount++]=aFloat;
					aFoundGoodLine=true;
				}
				else
				{
					delete[]aFloat;
					if(aFoundGoodLine)break;
				}
				while((*aRead<33||*aRead==';')&&aRead<aShelf)aRead++;
				if(aRead==aLineStart)break;
			}
			if(aListCount>0)
			{
				Clear();
				Size(aListCount);
				for(int i=0;i<aListCount;i++)
				{
					float *aAry=aList[i];
					int aCount=(int)(aAry[0]);
					Add(aAry[aCount-2], aHeight-aAry[aCount-1]);
				}
				mMax=mPointCount-1;
				delete[]mXCoef;
				mXCoef=new float[mMax*6];
				mYCoef=mXCoef+mMax*3;
				float aX1, aX2, aY1, aY2;
				int aIndex=0;
				for(int i=1,i1=0;i<aListCount;i1=i++)
				{
					float *aAry=(float*)aList[i];
					int aCount=(int)(aAry[0]);
					aIndex=i1*3;
					if(aCount==4)
					{
						mXCoef[aIndex]=mX[i]-mX[i1];
						mXCoef[aIndex+1]=0;
						mXCoef[aIndex+2]=0;
						//aIndex+=mMax*3;
						mYCoef[aIndex]=mY[i]-mY[i1];
						mYCoef[aIndex+1]=0;
						mYCoef[aIndex+2]=0;
					}
					else
					{
						if(((char)aAry[1]=='v'||(char)aAry[1]=='V')&&aCount==6)
						{
							aX1=mX[i1];
							aY1=mY[i1];
							aX2=aAry[2];
							aY2=aHeight-aAry[3];
						}
						else
						{
							aX2=aAry[4];
							aY2=aHeight-aAry[5];
							aX1=aAry[2];
							aY1=aHeight-aAry[3];
						}
						mXCoef[aIndex]=3*(aX1-mX[i1]);
						mXCoef[aIndex+1]=3*(aX2-aX1)-mXCoef[aIndex];
						mXCoef[aIndex+2]=mX[i]-mX[i1]-mXCoef[aIndex+1]-mXCoef[aIndex];
						//aIndex+=mMax*3;
						mYCoef[aIndex]=3*(aY1-mY[i1]);
						mYCoef[aIndex+1]=3*(aY2-aY1)-mYCoef[aIndex];
						mYCoef[aIndex+2]=mY[i]-mY[i1]-mYCoef[aIndex+1]-mYCoef[aIndex];
					}
				}
				for(int i=0;i<aListCount;i++)delete[]aList[i];

				mChanged=false;
			}
			delete[]aList;
		}
	}
}


void FSpline::Save(FFile *pFFile)
{
    Clear();
    
    if(!pFFile)return;
    
    pFFile->WriteInt(mPointCount);
    pFFile->WriteInt(mMax);
    pFFile->WriteInt(mSize);
    pFFile->WriteInt(mProperties);
    
    if(mSize <= 0 || mPointCount <= 0)
    {
        return;
    }
    
    for(int i=0;i<mPointCount;i++)pFFile->WriteFloat(mX[i]);
    for(int i=0;i<mPointCount;i++)pFFile->WriteFloat(mY[i]);
    
    if(mProperties & SPLINE_MANUAL_TANGENTS)
    {
        float *aXTan=mTangent;
        float *aYTan=aXTan+mSize;
        float *aTan=aYTan+mSize;
        
        for(int i=0;i<mSize;i++)pFFile->WriteFloat(aXTan[i]);
        for(int i=0;i<mSize;i++)pFFile->WriteFloat(aYTan[i]);
        for(int i=0;i<mSize;i++)pFFile->WriteFloat(aTan[i]);
    }
    
}

void FSpline::Load(FFile *pFFile)
{
    Clear();
    
    if(!pFFile)return;
    
    mPointCount=pFFile->ReadInt();
    mMax=pFFile->ReadInt();
    mSize=pFFile->ReadInt();
    mProperties=(unsigned int)(pFFile->ReadInt());
    
    if(mSize <= 0 || mPointCount <= 0)
    {
        return;
    }
    
    int aSize=mSize;
    mSize=0;
    Size(aSize);
    
    for(int i=0;i<mPointCount;i++)mX[i]=pFFile->ReadFloat();
    for(int i=0;i<mPointCount;i++)mY[i]=pFFile->ReadFloat();
    
    if(mProperties & SPLINE_MANUAL_TANGENTS)
    {
        float *aXTan=mTangent;
        float *aYTan=aXTan+mSize;
        float *aTan=aYTan+mSize;
        
        for(int i=0;i<mSize;i++)aXTan[i]=pFFile->ReadFloat();
        for(int i=0;i<mSize;i++)aYTan[i]=pFFile->ReadFloat();
        for(int i=0;i<mSize;i++)aTan[i]=pFFile->ReadFloat();
    }
    
    Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);
}



FSpline3D::FSpline3D()
{
    mSize=0;
    mMax=0;
    mPointCount=0;
    
    mX=0;
    mY=0;
    mZ=0;
    
    mXCoef=0;
    mYCoef=0;
    mZCoef=0;
    
    mProperties=0;
    
    mTangent=0;
    mLength=0;
    
    mChanged=true;
}

FSpline3D::~FSpline3D(void)
{
    Clear();
}

void FSpline3D::Translate(float theXDistance, float theYDistance, float theZDistance)
{
    for(int i=0;i<mPointCount;i++)
    {
        mX[i]+=theXDistance;
        mY[i]+=theYDistance;
        mZ[i]+=theZDistance;
    }
}

void FSpline3D::Reset()
{
    mPointCount=0;
    mMax=0;
    mProperties=0;
    mLength=0;
    mChanged=true;
}

void FSpline3D::Clear()
{
    delete[]mX;
    delete[]mXCoef;
    delete[]mTangent;
    
    mX=0;
    mY=0;
    mZ=0;
    
    mXCoef=0;
    mYCoef=0;
    mZCoef=0;
    
    mTangent=0;
    mSize=0;
    mPointCount=0;
    mMax=0;
    mProperties=0;
    mLength=0;
    mChanged=true;
}

void FSpline3D::Size(int size)
{
    if(size>0)
    {
        if(mSize!=size)
        {
            mChanged=true;
            
            float *aX;//=new float[size*5];
            float *aY;//=aX+size;
            float *aZ;
            
            aX=new float[size*3];
            aY=aX+size;
            aZ=aY+size;
            
            if(size<mPointCount)mPointCount=size;
            for(int i=0;i<mPointCount;i++)aX[i]=mX[i];
            for(int i=0;i<mPointCount;i++)aY[i]=mY[i];
            for(int i=0;i<mPointCount;i++)aZ[i]=mZ[i];
            
            
            delete[]mX;
            
            mX=aX;
            mY=aY;
            mZ=aZ;
            
            
            
            delete [] mXCoef;
            
            mXCoef = new float[size*11];
            mYCoef = mXCoef+3*size;
            mZCoef=mYCoef+3*mMax;
            
            mStorageDelta = mZCoef+3*size;
            mStorageTemp = mStorageDelta + size;
            
            
            //if(linear||(mPointCount==2&&!(mProperties&SPLINE_3D_MANUAL_TANGENTS)))mProperties|=SPLINE_3D_LINEAR;
            //mXCoef=new float[mMax*9];
            //mYCoef=mXCoef+3*mMax;
            //mZCoef=mYCoef+3*mMax;
            //float *aStore=new float[mPointCount*3];
            
            
            if(mProperties&SPLINE_3D_MANUAL_TANGENTS)
            {
                float *aXTan=new float[size*3];
                float *aYTan=aXTan+size;
                float *aZTan=aYTan+size;
                
                float *aTan=aYTan+size;
                float *aXTanSource=mTangent;
                float *aYTanSource=aXTanSource+mSize;
                float *aZTanSource=aYTanSource+mSize;
                
                float *aTanSource=aYTanSource+mSize;
                
                if(mSize>size)mSize=size;
                
                for(int i=0;i<mSize;i++)aXTan[i]=aXTanSource[i];
                for(int i=0;i<mSize;i++)aYTan[i]=aYTanSource[i];
                for(int i=0;i<mSize;i++)aZTan[i]=aZTanSource[i];
                
                for(int i=0;i<mSize;i++)aTan[i]=aTanSource[i];
                for(int i=mSize;i<size;i++)aTan[i]=0;
                delete[]mTangent;
                mTangent=aXTan;
            }
            
            
            
            mSize=size;
        }
    }
    else
    {
        Clear();
    }
}

void FSpline3D::Add(float x, float y, float z)
{
    if(mSize==mPointCount)Size(mSize+mSize/2+1);
    
    mX[mPointCount]=x;
    mY[mPointCount]=y;
    mZ[mPointCount]=z;
    
    mPointCount++;
    mChanged=true;
}

void FSpline3D::SetPoint(int theIndex,float x, float y, float z)
{
    if(theIndex<0||theIndex>=mPointCount)return;
    
    mX[theIndex]=x;
    mY[theIndex]=y;
    mZ[theIndex]=z;
    
    mChanged=true;
}

int FSpline3D::GetClosestControlIndex(float x, float y, float z, float &dist)
{
    dist=-1;
    int aResult=-1;
    if(mPointCount>1)
    {
        aResult=0;
        float aDiffX=mX[0]-x;
        float aDiffY=mY[0]-y;
        float aDiffZ=mZ[0]-z;
        
        dist=aDiffX*aDiffX+aDiffY*aDiffY+aDiffZ*aDiffZ;
        float aDist;
        for(int i=1;i<mPointCount;i++)
        {
            aDiffX=mX[i]-x;
            aDiffY=mY[i]-y;
            aDiffY=mZ[i]-z;
            aDist=aDiffX*aDiffX+aDiffY*aDiffY+aDiffZ*aDiffZ;
            if(aDist<dist)
            {
                dist=aDist;
                aResult=i;
            }
        }
    }
    return aResult;
}

void FSpline3D::Insert(int theIndex,float x, float y, float z)
{
    if(mSize==mPointCount)Size(mSize+mSize/2+1);
    //if(mProperties&SPLINE_3D_CLOSED&&mPointCount>0){Delete(mMax);mProperties&=~SPLINE_3D_CLOSED;}
    if(theIndex<0)theIndex=0;
    if(theIndex>mPointCount)theIndex=mPointCount;
    for(int i=mPointCount-1;i>=theIndex;i--)mX[i+1]=mX[i];
    for(int i=mPointCount-1;i>=theIndex;i--)mY[i+1]=mY[i];
    if(mProperties&SPLINE_3D_MANUAL_TANGENTS)
    {
        float*aTan=mTangent;
        for(int i=mSize-2;i>=theIndex;i--)aTan[i+1]=aTan[i];
        aTan+=mSize;
        for(int i=mSize-2;i>=theIndex;i--)aTan[i+1]=aTan[i];
        aTan+=mSize;
        for(int i=mSize-2;i>=theIndex;i--)aTan[i+1]=aTan[i];
        aTan[theIndex]=0;
    }
    
    mX[theIndex]=x;
    mY[theIndex]=y;
    mZ[theIndex]=z;
    
    mPointCount++;
    mChanged=true;
}

void FSpline3D::Delete(int theIndex)
{
    if(theIndex<0)return;
    if(theIndex<mPointCount)
    {
        for(int i=theIndex;i<mPointCount;i++)mX[i]=mX[i+1];
        for(int i=theIndex;i<mPointCount;i++)mY[i]=mY[i+1];
        if(mPointCount)mPointCount--;
        mChanged=true;
    }
    if(theIndex<mSize&&(mProperties&SPLINE_3D_MANUAL_TANGENTS))
    {
        float*aTan=mTangent;
        for(int i=theIndex;i<mSize;i++)aTan[i]=aTan[i+1];aTan+=mSize;
        for(int i=theIndex;i<mSize;i++)aTan[i]=aTan[i+1];aTan+=mSize;
        for(int i=theIndex;i<mSize;i++)aTan[i]=aTan[i+1];
        mChanged=true;
    }
}

void FSpline3D::SetTangent(int theIndex, float xtan, float ytan, float ztan)
{
    if(theIndex>=0)
    {
        if(theIndex>=mSize)Size(theIndex+theIndex/2+1);
        if(!(mProperties&SPLINE_3D_MANUAL_TANGENTS))
        {
            mProperties|=SPLINE_3D_MANUAL_TANGENTS;
            int aSize=mSize*3;
            mTangent=new float[aSize];
            for(int i=0;i<aSize;i++)mTangent[i]=0;
        }
        
        mTangent[theIndex]=xtan;
        mTangent[theIndex+mSize]=ytan;
        mTangent[theIndex+(mSize + mSize)]=ztan;
        
        mTangent[theIndex+(mSize<<1)]=1;//theIndex+mSize*2
        mChanged=true;
    }
}

void FSpline3D::Solve(float *theCoordinate,float*theDelta,float*theDerivative,float*theTemp,float*theCoef,bool linear,bool circular)
{
    if(mPointCount > 1)
    {
        float *aDer=mTangent+mSize+mSize;
        unsigned int aCoefOffStart=0;
        if(mPointCount==2&&((mProperties&SPLINE_3D_MANUAL_TANGENTS)!=0))
        {
            
            if(circular)
            {
                if(!aDer[0])theDerivative[0]=-theDerivative[1];
                if(!aDer[1])theDerivative[1]=-theDerivative[0];
                theCoef[aCoefOffStart++]=theDerivative[0];
                theCoef[aCoefOffStart++]=3*(theCoordinate[1]-theCoordinate[0])-2*theDerivative[0]-theDerivative[1];
                theCoef[aCoefOffStart++]=2*(theCoordinate[0]-theCoordinate[1])+theDerivative[0]+theDerivative[1];
                theCoef[aCoefOffStart++]=theDerivative[1];
                theCoef[aCoefOffStart++]=3*(theCoordinate[0]-theCoordinate[1])-2*theDerivative[1]-theDerivative[0];
                theCoef[aCoefOffStart++]=2*(theCoordinate[1]-theCoordinate[0])+theDerivative[1]+theDerivative[0];
            }
            else
            {
                if(!aDer[0])theDerivative[0]=0;
                if(!aDer[1])theDerivative[1]=0;
                theCoef[aCoefOffStart++]=theDerivative[0];
                theCoef[aCoefOffStart++]=3*(theCoordinate[1]-theCoordinate[0])-2*theDerivative[0]-theDerivative[1];
                theCoef[aCoefOffStart++]=2*(theCoordinate[0]-theCoordinate[1])+theDerivative[0]+theDerivative[1];
            }
        }
        else if(linear||mPointCount==2)
        {
            for(int i=1,j=0;i<mPointCount;j=i++)
            {
                theCoef[aCoefOffStart++]=theCoordinate[i]-theCoordinate[j];
                theCoef[aCoefOffStart++]=0;
                theCoef[aCoefOffStart++]=0;
            }
            if(circular)
            {
                theCoef[aCoefOffStart++]=theCoordinate[0]-theCoordinate[mPointCount-1];
                theCoef[aCoefOffStart++]=0;
                theCoef[aCoefOffStart++]=0;
            }
        }
        else
        {
            int aMax;
            int aMax1;
            if(circular)
            {
                aMax=mPointCount-1;
                aMax1=aMax-1;
                theDelta[1]=0.25f;
                theTemp[0]=0.25f*3*(theCoordinate[1]-theCoordinate[aMax]);
                float G=1.0f,H=4.0f,F=3.0f*(theCoordinate[0]-theCoordinate[aMax1]);
                for(int i=1;i<aMax;i++)
                {
                    theDelta[i+1]=-0.25f*theDelta[i];
                    theTemp[i]=0.25f*(3*(theCoordinate[i+1]-theCoordinate[i-1])-theTemp[i-1]);
                    H=H-G*theDelta[i];
                    F=F-G*theTemp[i-1];
                    G=-0.25f*G;
                }
                H=H-(G+1)*(0.25f+theDelta[aMax]);
                theTemp[aMax]=F-(G+1)*theTemp[aMax1];
                if(!aDer[aMax])theDerivative[aMax]=theTemp[aMax]/H;
                if(!aDer[aMax1])theDerivative[aMax1]=theTemp[aMax1]-(0.25f+theDelta[aMax])*theDerivative[aMax];
                for(int i=aMax-2;i>=0;i--)
                {
                    if(!aDer[i])
                    {
                        theDerivative[i]=theTemp[i]-0.25f*theDerivative[i+1]-theDelta[i+1]*theDerivative[aMax];
                    }
                }
                int aIndex=aMax*3;
                theCoef[aIndex]=theDerivative[aMax];
                theCoef[aIndex+1]=3*(theCoordinate[0]-theCoordinate[aMax])-2*theDerivative[aMax]-theDerivative[0];
                theCoef[aIndex+2]=2*(theCoordinate[aMax]-theCoordinate[0])+theDerivative[aMax]+theDerivative[0];
            }
            else
            {
                aMax=mMax;
                aMax1=aMax-1;
                theDelta[0]=3.0f*(theCoordinate[1]-theCoordinate[0])*0.25f;
                for(int i=1;i<aMax;i++)theDelta[i]=(3.0f*(theCoordinate[i+1]-theCoordinate[i-1])-theDelta[i-1])*0.25f;
                theDelta[aMax]=(3.0f*(theCoordinate[aMax]-theCoordinate[aMax1])-theDelta[aMax1])*0.25f;
                if(!aDer[aMax])theDerivative[aMax]=theDelta[aMax];
                for(int i=aMax1;i>=0;i--)
                {
                    if(!aDer[i])
                    {
                        theDerivative[i]=theDelta[i]-0.25f*theDerivative[i+1];
                    }
                }
            }
            for(int i=0;i<aMax;i++)
            {
                theCoef[aCoefOffStart++]=theDerivative[i];
                theCoef[aCoefOffStart++]=3*(theCoordinate[i+1]-theCoordinate[i])-2*theDerivative[i]-theDerivative[i+1];
                theCoef[aCoefOffStart++]=2*(theCoordinate[i]-theCoordinate[i+1])+theDerivative[i]+theDerivative[i+1];
            }
        }
    }
}

void FSpline3D::Solve(float *theCoordinate,float*theDelta,float*theDerivative,float*theCoef,bool linear,bool circular)
{
    if(mPointCount > 1)
    {
        unsigned int aCoefOffStart=0;
        if(linear||mPointCount==2)
        {
            for(int i=1,j=0;i<mPointCount;j=i++)
            {
                theCoef[aCoefOffStart++]=theCoordinate[i]-theCoordinate[j];
                theCoef[aCoefOffStart++]=0;
                theCoef[aCoefOffStart++]=0;
            }
            if(circular)
            {
                theCoef[aCoefOffStart++]=theCoordinate[0]-theCoordinate[mPointCount-1];
                theCoef[aCoefOffStart++]=0;
                theCoef[aCoefOffStart++]=0;
            }
        }
        else
        {
            int aMax;
            int aMax1;
            if(circular)
            {
                aMax=mPointCount-1;
                aMax1=aMax-1;
                theDelta[1]=0.25f;
                theDerivative[0]=0.25f*3*(theCoordinate[1]-theCoordinate[aMax]);
                float G=1.0f,H=4.0f,F=3.0f*(theCoordinate[0]-theCoordinate[aMax1]);
                for(int i=1;i<aMax;i++)
                {
                    theDelta[i+1]=-0.25f*theDelta[i];
                    theDerivative[i]=0.25f*(3*(theCoordinate[i+1]-theCoordinate[i-1])-theDerivative[i-1]);
                    H=H-G*theDelta[i];
                    F=F-G*theDerivative[i-1];
                    G=-0.25f*G;
                }
                H=H-(G+1)*(0.25f+theDelta[aMax]);
                theDerivative[aMax]=F-(G+1)*theDerivative[aMax1];
                theDerivative[aMax]=theDerivative[aMax]/H;
                theDerivative[aMax1]=theDerivative[aMax1]-(0.25f+theDelta[aMax])*theDerivative[aMax];
                for(int i=aMax-2;i>=0;i--)theDerivative[i]=theDerivative[i]-0.25f*theDerivative[i+1]-theDelta[i+1]*theDerivative[aMax];
                int aIndex=aMax*3;
                theCoef[aIndex]=theDerivative[aMax];
                theCoef[aIndex+1]=3*(theCoordinate[0]-theCoordinate[aMax])-2*theDerivative[aMax]-theDerivative[0];
                theCoef[aIndex+2]=2*(theCoordinate[aMax]-theCoordinate[0])+theDerivative[aMax]+theDerivative[0];
            }
            else
            {
                aMax=mMax;
                aMax1=aMax-1;
                theDelta[0]=3.0f*(theCoordinate[1]-theCoordinate[0])*0.25f;
                for(int i=1;i<aMax;i++)theDelta[i]=(3.0f*(theCoordinate[i+1]-theCoordinate[i-1])-theDelta[i-1])*0.25f;
                theDelta[aMax]=(3.0f*(theCoordinate[aMax]-theCoordinate[aMax1])-theDelta[aMax1])*0.25f;
                theDerivative[aMax]=theDelta[aMax];
                for(int i=aMax1;i>=0;i--)theDerivative[i]=theDelta[i]-0.25f*theDerivative[i+1];
            }
            for(int i=0;i<aMax;i++)
            {
                theCoef[aCoefOffStart++]=theDerivative[i];
                theCoef[aCoefOffStart++]=3*(theCoordinate[i+1]-theCoordinate[i])-2*theDerivative[i]-theDerivative[i+1];
                theCoef[aCoefOffStart++]=2*(theCoordinate[i]-theCoordinate[i+1])+theDerivative[i]+theDerivative[i+1];
            }
        }
    }
}


void FSpline3D::Solve(bool linear,bool circular)
{
    mChanged=false;
    
    //delete[]mXCoef;
    //mXCoef=0;
    //mYCoef=0;
    //mZCoef=0;
    mMax=0;
    mProperties&=~SPLINE_3D_CLOSED;
    mProperties&=~SPLINE_3D_LINEAR;
    if(mPointCount>1)
    {
        mMax=mPointCount-1;
        if(circular)
        {
            mProperties|=SPLINE_3D_CLOSED;
            mMax++;
        }
        Size(mPointCount);
        if(linear)mProperties|=SPLINE_3D_LINEAR;
        //if(linear||(mPointCount==2&&!(mProperties&SPLINE_3D_MANUAL_TANGENTS)))mProperties|=SPLINE_3D_LINEAR;
        //mXCoef=new float[mMax*9];
        //mYCoef=mXCoef+3*mMax;
        //mZCoef=mYCoef+3*mMax;
        //float *aStore=new float[mPointCount*3];
        
        if(mProperties&SPLINE_3D_MANUAL_TANGENTS)
        {
            Solve(mX,mStorageDelta,mTangent,mStorageTemp,mXCoef,linear,circular);
            Solve(mY,mStorageDelta,mTangent+mSize,mStorageTemp,mYCoef,linear,circular);
            Solve(mZ,mStorageDelta,mTangent+mSize,mStorageTemp,mZCoef,linear,circular);
        }
        else
        {
            Solve(mX,mStorageDelta,mStorageTemp,mXCoef,linear,circular);
            Solve(mY,mStorageDelta,mStorageTemp,mYCoef,linear,circular);
            Solve(mZ,mStorageDelta,mStorageTemp,mZCoef,linear,circular);
        }
        
        //delete[]aStore;
    }
}

void FSpline3D::Tan(float pos, float &x, float &y, float &z)
{
    if(mChanged)Solve((mProperties&SPLINE_3D_LINEAR)!=0,(mProperties&SPLINE_3D_CLOSED)!=0);
    if(mXCoef)
    {
        int aIndex=(int)pos;
        if(pos<0){aIndex=0;pos=0;}
        if(aIndex>=mMax){aIndex=mMax-1;pos=(float)(aIndex+1);}
        float aPos=pos-(float)aIndex;
        float aPos2=aPos*aPos;
        
        aIndex=((aIndex<<1)+aIndex);//aIndex*3
        
        x=3.0f*mXCoef[aIndex+2]*aPos2+2.0f*mXCoef[aIndex+1]*aPos+mXCoef[aIndex];
        y=3.0f*mYCoef[aIndex+2]*aPos2+2.0f*mYCoef[aIndex+1]*aPos+mYCoef[aIndex];
        z=3.0f*mZCoef[aIndex+2]*aPos2+2.0f*mZCoef[aIndex+1]*aPos+mZCoef[aIndex];
        
        return;
    }
    x=0;
    y=0;
    z=0;
}

//We may use this to smooth curves -- and the curves are not all necessarily smooth.
//So, we will step back one and assume t=1 instead of staying in place with t=0.
void FSpline3D::Tan(int pos, float &x, float &y, float &z)
{
    if(mChanged)Solve((mProperties&SPLINE_3D_LINEAR)!=0,(mProperties&SPLINE_3D_CLOSED)!=0);
    if(mXCoef)
    {
        if(pos<=0)
        {
            x=mXCoef[0];
            y=mYCoef[0];//mMax*3
            z=mZCoef[0];//mMax*3
            
            return;
        }
        pos--;
        if(pos>=mMax)pos=mMax-1;
        pos=(pos<<1)+pos;//pos*3
        
        x=3.0f*mXCoef[pos+2]+2.0f*mXCoef[pos+1]+mXCoef[pos];
        y=3.0f*mYCoef[pos+2]+2.0f*mYCoef[pos+1]+mYCoef[pos];
        z=3.0f*mZCoef[pos+2]+2.0f*mZCoef[pos+1]+mZCoef[pos];
        
        return;
    }
    
    x=0;
    y=0;
    z=0;
}

float FSpline3D::GetX(float pos)
{
    if(mProperties&SPLINE_3D_CLOSED)
    {
        if(mMax > 0)
        {
            if(pos < 0 || pos > (float)mMax)
            {
                pos = fmodf(pos, mMax);
                if(pos < 0)
                {
                    pos += (float)mMax;
                }
            }
        }
    }
    if(mChanged)Solve((mProperties&SPLINE_3D_LINEAR)!=0,(mProperties&SPLINE_3D_CLOSED)!=0);
    if(mXCoef)
    {
        int aIndex=(int)pos;
        if(pos<0)
        {
            return*mX;
        }
        float aPos=pos-(float)aIndex;
        if(aIndex>=mMax)
        {
            aIndex=mMax-1;
            aPos=1;
        }
        float aPos2=aPos*aPos;
        float aPos3=aPos*aPos2;
        
        int aCoefIndex=((aIndex<<1)+aIndex);//aIndex*3
        //duuu+cuu+bu+a
        return mX[aIndex]+mXCoef[aCoefIndex]*aPos+mXCoef[aCoefIndex+1]*aPos2+mXCoef[aCoefIndex+2]*aPos3;
    }
    return 0;
}

float FSpline3D::GetY(float pos)
{
    if(mProperties&SPLINE_3D_CLOSED)
    {
        if(mMax > 0)
        {
            if(pos < 0 || pos > (float)mMax)
            {
                pos = fmodf(pos, mMax);
                if(pos < 0)
                {
                    pos += (float)mMax;
                }
            }
        }
    }
    if(mChanged)Solve((mProperties&SPLINE_3D_LINEAR)!=0,(mProperties&SPLINE_3D_CLOSED)!=0);
    if(mXCoef)
    {
        int aIndex=(int)pos;
        if(pos<0)
        {
            return*mY;
        }
        float aPos=pos-(float)aIndex;
        if(aIndex>=mMax)
        {
            aIndex=mMax-1;
            aPos=1;
        }
        float aPos2=aPos*aPos;
        float aPos3=aPos*aPos2;
        int aCoefIndex=((aIndex<<1)+aIndex);//+((mMax<<1)+mMax);
        //duuu+cuu+bu+a
        return mY[aIndex]+mYCoef[aCoefIndex]*aPos+mYCoef[aCoefIndex+1]*aPos2+mYCoef[aCoefIndex+2]*aPos3;
    }
    return 0;
}

float FSpline3D::GetZ(float pos)
{
    if(mProperties&SPLINE_3D_CLOSED)
    {
        if(mMax > 0)
        {
            if(pos < 0 || pos > (float)mMax)
            {
                pos = fmodf(pos, mMax);
                if(pos < 0)
                {
                    pos += (float)mMax;
                }
            }
        }
    }
    if(mChanged)Solve((mProperties&SPLINE_3D_LINEAR)!=0,(mProperties&SPLINE_3D_CLOSED)!=0);
    if(mXCoef)
    {
        int aIndex=(int)pos;
        if(pos<0)
        {
            return*mZ;
        }
        float aPos=pos-(float)aIndex;
        if(aIndex>=mMax)
        {
            aIndex=mMax-1;
            aPos=1;
        }
        float aPos2=aPos*aPos;
        float aPos3=aPos*aPos2;
        int aCoefIndex=((aIndex<<1)+aIndex);//+((mMax<<1)+mMax);
        //duuu+cuu+bu+a
        return mZ[aIndex]+mZCoef[aCoefIndex]*aPos+mZCoef[aCoefIndex+1]*aPos2+mZCoef[aCoefIndex+2]*aPos3;
    }
    return 0;
}

void FSpline3D::Get(float pos, float &x, float &y, float &z)
{
    if(mChanged)Solve((mProperties&SPLINE_3D_LINEAR)!=0,(mProperties&SPLINE_3D_CLOSED)!=0);
    if(mXCoef)
    {
        if(IsCircular())
        {
            if(pos<0||pos>(float)mMax)
            {
                pos=fmodf(pos,(float)mMax);
                if(pos<0)pos+=(float)mMax;
            }
        }
        
        int aIndex=(int)pos;
        if(pos<0)
        {
            x=*mX;
            y=*mY;
            z=*mZ;
            return;
        }
        
        float aPos=pos-(float)aIndex;
        if(aIndex>=mMax)
        {
            aIndex=mMax-1;
            aPos=1;
        }
        
        x=mX[aIndex];
        y=mY[aIndex];
        z=mZ[aIndex];
        
        aIndex=((aIndex<<1)+aIndex);//aIndex*3
        
        x+=(((mXCoef[aIndex+2]*aPos)+mXCoef[aIndex+1])*aPos+mXCoef[aIndex])*aPos;
        y+=(((mYCoef[aIndex+2]*aPos)+mYCoef[aIndex+1])*aPos+mYCoef[aIndex])*aPos;
        z+=(((mZCoef[aIndex+2]*aPos)+mZCoef[aIndex+1])*aPos+mZCoef[aIndex])*aPos;
        
        
        return;
    }
    x=0;
    y=0;
    z=0;
}

void FSpline3D::Get(int pos, float&x, float&y, float&z)
{
    if(mChanged)Solve((mProperties&SPLINE_3D_LINEAR)!=0,(mProperties&SPLINE_3D_CLOSED)!=0);
    if(mPointCount>0)
    {
        if(pos<0)
        {
            x=*mX;
            y=*mY;
            z=*mZ;
            
            return;
        }
        
        if(pos>=mPointCount)
        {
            if(mProperties&SPLINE_3D_CLOSED)
            {
                x=*mX;
                y=*mY;
                z=*mZ;
                
                
                return;
            }
            else
            {
                x=mX[mPointCount-1];
                y=mY[mPointCount-1];
                z=mZ[mPointCount-1];
                
                return;
            }
        }
        
        x=mX[pos];
        y=mY[pos];
        z=mZ[pos];
        
        return;
    }
    
    x=0;
    y=0;
    z=0;
}


FVec3 FSpline3D::Tan(float pPos)
{
    float aTanX,aTanY,aTanZ;
    Tan(pPos, aTanX, aTanY, aTanZ);
    return FVec3(aTanX, aTanY, aTanZ);
}

FVec3 FSpline3D::Perp(float pPos)
{
    FVec3 aTan = Tan(pPos);
    FVec3 aReferenceVector = FVec3(1.0f,1.0f,0);//-aTan.mX, -aTan.mY, -aTan.mZ);
    FVec3 aPerp;
    aPerp.mX = aTan.mY*aReferenceVector.mZ - aTan.mZ*aReferenceVector.mY;
    aPerp.mY = aTan.mZ*aReferenceVector.mX - aTan.mX*aReferenceVector.mZ;
    aPerp.mZ = aTan.mX*aReferenceVector.mY - aTan.mY*aReferenceVector.mX;
    return aPerp;
}

FVec3 FSpline3D::Perp(float pPos, float pAngle)
{
    return FVec3(0.0f, 0.0f, 0.0f);
}

