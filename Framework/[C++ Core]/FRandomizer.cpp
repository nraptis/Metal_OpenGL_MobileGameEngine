#include "FRandomizer.hpp"
#include "core_includes.h"

FRandomizer::FRandomizer()
{
    
    mPings = 0;
    
    //Seed((int)(os_system_time()));

    int *aMemory1 = new int[10];
    int *aMemory2 = new int[10];
    int *aMemory3 = new int[10];

    int aSeed1 = aMemory1[0];
    int aSeed2 = aMemory2[4];
    int aSeed3 = aMemory3[8];

    int aSeed4 = (long)(&(aMemory1));
    int aSeed5 = (long)(&(aMemory2));
    int aSeed6 = (long)(&(aMemory3));

    int aSeed = aSeed1 ^ aSeed2 ^ aSeed3 ^ aSeed4 ^ aSeed5 ^ aSeed6;

    Seed(aSeed);
    
    //Seed(os_system_time());
}

FRandomizer::~FRandomizer()
{
	
}

void FRandomizer::Seed(int pSeed)
{
    
    mIndex=624;
 
    mData[0]=pSeed;
	
    for(int i=1;i<624;i++)
    {
        mData[i]=(1812433253*(mData[i-1]^(mData[i-1]>>30))+i);
    }
    
}

int FRandomizer::Get(int pMax, bool pNegative)
{
    mPings++;
    
	int aResult=0;
	if(pMax<0)
	{
		pMax=-pMax;
		pNegative=true;
	}
	
	if(mIndex==624)
	{
		int i=0;
		int aFinalMask[2]={0,0x9908b0d};
		for(;i<624-397;i++)
		{
			aResult=(mData[i]&0x80000000)|(mData[i+1]&0x7fffffff);
			mData[i]=mData[i+397]^(aResult>>1)^(aFinalMask[aResult&1]);
        }
		for(;i<624;i++)
		{
	
			aResult=(mData[i]&0x80000000)|(mData[i+1]&0x7fffffff);
			mData[i]=mData[i+(397-624)]^(aResult>>1)^(aFinalMask[aResult&1]);
		}
		mIndex=0;
	}
	
	pNegative=pNegative&&((mData[mIndex]&0x8)==0);
	
	aResult = mData[mIndex++];
	aResult ^= aResult>>11;
	aResult ^= (aResult<<7)&0x9d2c5680;
	aResult ^= (aResult<<15)&0xefc60000;
	aResult ^= (aResult>>18);
	if(aResult&&pMax>0)aResult %= pMax;
	if(pMax==0)aResult=0;
	if(pNegative)aResult=-aResult;
	
	return aResult;
}

int FRandomizer::Get(int pMin, int pMax)
{
	return pMin+Get(pMax-pMin);
}

float FRandomizer::GetFloat()
{
	return (float)Get(0xFFFFFFF+1)/(float)(0xFFFFFFF);
}

float FRandomizer::GetFloat(float pMax)
{
	return GetFloat()*pMax;
}

float FRandomizer::GetFloat(float pMin, float pMax)
{
	return pMin+(pMax-pMin)*GetFloat();
}

float FRandomizer::GetFloatWithSpan(float pValue, float pSpan)
{
    float aSpan2 = pSpan * 0.5f;
    return GetFloat(-aSpan2, aSpan2);
}

float FRandomizer::GetFloatWithSpan(float pValue, float pSpan, bool pNegative)
{
    float aSpan2 = pSpan * 0.5f;
    return GetFloat(-aSpan2, aSpan2, pNegative);
}

float FRandomizer::GetFloat(float pMin, float pMax, bool pNegative)
{
	pNegative=pNegative&&((mData[mIndex]&0x8)==0);
	float aResult=pMin+(pMax-pMin)*GetFloat();
	if(pNegative)aResult=-aResult;
	return aResult;
}

