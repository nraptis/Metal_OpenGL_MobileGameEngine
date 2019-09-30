#ifndef COLOR_H
#define COLOR_H

class FColor
{
public:
	inline FColor(float pRed, float pGreen, float pBlue, float pAlpha)
	{
		mRed=pRed;
		mGreen=pGreen;
		mBlue=pBlue;
		mAlpha=pAlpha;
	}
	
	inline FColor(float pRed, float pGreen, float pBlue)
	{
		mRed=pRed;
		mGreen=pGreen;
		mBlue=pBlue;
		mAlpha=1.0f;
	}
	
	inline FColor(float pIntensity)
	{
		mRed = 1.0f;
		mGreen = 1.0f;
		mBlue = 1.0f;
		mAlpha = pIntensity;
	}
    
    inline FColor(unsigned int pHexColor, bool pIncludeAlpha=false)
    {
        mRed = ((float)((((unsigned int)(pHexColor))>>16)&0xFF)) / (255.0f);
        mGreen = ((float)((((unsigned int)(pHexColor))>>8)&0xFF)) / (255.0f);
        mBlue = ((float)(((unsigned int)(pHexColor))&0xFF)) / (255.0f);
        if(pIncludeAlpha)mAlpha = ((float)((((unsigned int)(pHexColor))>>24)&0xFF)) / (255.0f);
        else mAlpha = 1.0f;
    }
    
    inline FColor(int pHexColor, bool pIncludeAlpha=false)
    {
        mRed = ((float)((((unsigned int)(pHexColor))>>16)&0xFF)) / (255.0f);
        mGreen = ((float)((((unsigned int)(pHexColor))>>8)&0xFF)) / (255.0f);
        mBlue = ((float)(((unsigned int)(pHexColor))&0xFF)) / (255.0f);
        if(pIncludeAlpha)mAlpha = ((float)((((unsigned int)(pHexColor))>>24)&0xFF)) / (255.0f);
        else mAlpha = 1.0f;
    }
    
	
    FColor(const char *pRGBAString);
    
	
	FColor()
	{
		mRed = 1.0f;
		mGreen = 1.0f;
		mBlue = 1.0f;
		mAlpha = 1.0f;
	}
	
	void operator+=(FColor &pColor){mRed+=pColor.mRed;mGreen+=pColor.mGreen;mBlue+=pColor.mBlue;mAlpha+=pColor.mAlpha;}
	void operator-=(FColor &pColor){mRed-=pColor.mRed;mGreen-=pColor.mGreen;mBlue-=pColor.mBlue;mAlpha-=pColor.mAlpha;}
	void operator*=(FColor &pColor){mRed*=pColor.mRed;mGreen*=pColor.mGreen;mBlue*=pColor.mBlue;mAlpha*=pColor.mAlpha;}
	void operator/=(FColor &pColor){mRed/=pColor.mRed;mGreen/=pColor.mGreen;mBlue/=pColor.mBlue;mAlpha/=pColor.mAlpha;}
	
	FColor operator+(FColor &pColor){return FColor(mRed+pColor.mRed,mGreen+pColor.mGreen,mBlue+pColor.mBlue,mAlpha+pColor.mAlpha);}
	FColor operator-(FColor &pColor){return FColor(mRed-pColor.mRed,mGreen-pColor.mGreen,mBlue-pColor.mBlue,mAlpha-pColor.mAlpha);}
	FColor operator*(FColor &pColor){return FColor(mRed*pColor.mRed,mGreen*pColor.mGreen,mBlue*pColor.mBlue,mAlpha*pColor.mAlpha);}
	FColor operator/(FColor &pColor){return FColor(mRed/pColor.mRed,mGreen/pColor.mGreen,mBlue/pColor.mBlue,mAlpha/pColor.mAlpha);}
	
	void operator+=(float pVal){mRed+=pVal;mGreen+=pVal;mBlue+=pVal;mAlpha+=pVal;}
	void operator-=(float pVal){mRed-=pVal;mGreen-=pVal;mBlue-=pVal;mAlpha-=pVal;}
	void operator*=(float pVal){mRed*=pVal;mGreen*=pVal;mBlue*=pVal;mAlpha*=pVal;}
	void operator/=(float pVal){mRed/=pVal;mGreen/=pVal;mBlue/=pVal;mAlpha/=pVal;}
	
	FColor operator+(float pVal){return FColor(mRed+pVal,mGreen+pVal,mBlue+pVal,mAlpha+pVal);}
	FColor operator-(float pVal){return FColor(mRed-pVal,mGreen-pVal,mBlue-pVal,mAlpha-pVal);}
	FColor operator*(float pVal){return FColor(mRed*pVal,mGreen*pVal,mBlue*pVal,mAlpha*pVal);}
	FColor operator/(float pVal){return FColor(mRed/pVal,mGreen/pVal,mBlue/pVal,mAlpha/pVal);}
    
    inline void Set(FColor &pColor) {
        mRed = pColor.mRed;
        mGreen = pColor.mGreen;
        mBlue = pColor.mBlue;
        mAlpha = pColor.mAlpha;
    }
    
	float mRed;
	float mGreen;
	float mBlue;
	float mAlpha;
    
    void Print(const char *pName);
    
    
};

#endif
