/*
 *  FRandomizer.h
 *  (c) 2009 Nick Raptis
 */

#ifndef RANDOMIZER_H
#define RANDOMIZER_H

class FRandomizer
{
public:
	FRandomizer();
	~FRandomizer();
	
	void				Seed(int pSeed); 
	int					Get(int pMax, bool pNegative=false);
	int					Get(int pMin, int pMax);
	
	inline bool			GetBool(){return Get(2)!=0;}
	inline int			Sign(){return Get(2)?1:-1;}
	
	inline int			Negate(int pNumber){return (Get(2)==0)?pNumber:-pNumber;}
	inline float		Negate(float pNumber){return (Get(2)==0)?pNumber:-pNumber;}
	
	float				GetFloat();
	float				GetFloat(float pMax);
	float				GetFloat(float pMin, float pMax);
    float				GetFloat(float pMin, float pMax, bool pNegative);
    
    inline float        F(){return GetFloat();}
    inline float        F(float pMax){return GetFloat(pMax);}
    inline float        F(float pMin, float pMax){return GetFloat(pMin, pMax);}
    inline float        F(float pMin, float pMax, bool pNegative){return GetFloat(pMin, pMax, pNegative);}
    
    float               GetRotation(){return GetFloat(360.0f);}
    inline float        Rot(){return GetRotation();}
    inline float        R(){return GetRotation();}
    
    float				GetFloatWithSpan(float pValue, float pSpan);
    float				GetFloatWithSpan(float pValue, float pSpan, bool pNegative);
    
	unsigned int		mData[624];
	
	int					mIndex;
    
    int                 mPings;
};

#endif
