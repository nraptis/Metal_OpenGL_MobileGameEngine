//
//  FVec2.h
//  SRT
//
//  Created by Nick Raptis on 10/8/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_VEC_2
#define FRAMEWORK_VEC_2

class FVec2
{
public:
	FVec2(){mX=0;mY=0;}
	FVec2(const float pX, const float pY) {mX=pX;mY=pY;}
	FVec2(const float pX, const int pY) {mX=pX;mY=(float)pY;}
	FVec2(const int pX, const float pY) {mX=(float)pX;mY=pY;}
	FVec2(const int pX, const int pY) {mX=(float)pX;mY=(float)pY;}
	FVec2(const FVec2 &pFVec2) {*this=pFVec2;}
	
	inline FVec2 &operator=(const FVec2 &pFVec2) {if(this!=&pFVec2) {mX=pFVec2.mX;mY=pFVec2.mY;}return *this;}
	inline FVec2 &operator=(float &pValue) {mX=pValue;mY=pValue;return *this;}
	inline FVec2 &operator=(int &pValue) {mX=(float)pValue;mY=(float)pValue;return *this;}
	
	inline bool	operator==(const FVec2 &pFVec2) {return (mX==pFVec2.mX)&(mY==pFVec2.mY);}
	inline bool	operator!=(const FVec2 &pFVec2) {return (mX!=pFVec2.mX)|(mY!=pFVec2.mY);}
	
	inline const FVec2	operator*(const FVec2 &pFVec2) const {return FVec2(mX*pFVec2.mX,mY*pFVec2.mY);}
	inline FVec2 &operator*=(const FVec2 &pFVec2) {mX*=pFVec2.mX;mY*=pFVec2.mY;return *this;}
	inline const FVec2 operator*(const float pFloat) const {return FVec2(mX*pFloat,mY*pFloat);}
	inline FVec2 &operator*=(const float pFloat) {mX*=pFloat;mY*=pFloat;return *this;}
	inline const FVec2	operator/(const FVec2 &pFVec2) const {return FVec2(mX/pFVec2.mX,mY/pFVec2.mY);}
	inline FVec2 &operator/=(const FVec2 &pFVec2) {mX/=pFVec2.mX;mY/=pFVec2.mY;return *this;}
	inline const FVec2 operator/(const float pFloat) const {return FVec2(mX/pFloat,mY/pFloat);}
	inline FVec2 &operator/=(const float pFloat) {mX/=pFloat;mY/=pFloat;return *this;}
	inline const FVec2 operator+(const FVec2 &pFVec2) const {return FVec2(mX+pFVec2.mX,mY+pFVec2.mY);}
	inline FVec2 &operator+=(const FVec2 &pFVec2) {mX+=pFVec2.mX;mY+=pFVec2.mY;return *this;}
	inline const FVec2 operator+(const float pFloat) const {return FVec2(mX+pFloat,mY+pFloat);}
	inline FVec2 &operator+=(const float pFloat) {mX+=pFloat;mY+=pFloat;return *this;}
	inline const FVec2 operator-(const FVec2 &pFVec2) const {return FVec2(mX-pFVec2.mX,mY-pFVec2.mY);}
	inline FVec2 &operator-=(const FVec2 &pFVec2) {mX-=pFVec2.mX;mY-=pFVec2.mY;return *this;}
	inline const FVec2 operator-(const float pFloat) const {return FVec2(mX-pFloat,mY-pFloat);}
	inline FVec2 & operator-=(const float pFloat) {mX-=pFloat;mY-=pFloat;return *this;}
	inline const FVec2 operator-() const {return FVec2(-mX,-mY);}
    
    float                               Length();
    float                               LengthSquared();
    
    void                                Normalize();
    
    float                               mX;
	float                               mY;
    
	float                               Dot(FVec2 &pVector){return mX*pVector.mX+mY*pVector.mY;}
	float                               Cross(FVec2 &pVector){return mX*pVector.mY-mY*pVector.mX;}
    
    void                                SetLength(float pLength){Normalize();mX*=pLength;mY*=pLength;}
};


class FIVec2
{
public:
    FIVec2(){mX=0;mY=0;}
    FIVec2(const int pX, const int pY) {mX=pX;mY=pY;}
    FIVec2(const int pX, const float pY) {mX=pX;mY=(int)pY;}
    FIVec2(const float pX, const int pY) {mX=(int)pX;mY=pY;}
    FIVec2(const float pX, const float pY) {mX=(int)pX;mY=(int)pY;}
    FIVec2(const FIVec2 &pFIVec2) {*this=pFIVec2;}
    
    inline FIVec2 &operator=(const FIVec2 &pFIVec2) {if(this!=&pFIVec2) {mX=pFIVec2.mX;mY=pFIVec2.mY;}return *this;}
    inline FIVec2 &operator=(int &pValue) {mX=pValue;mY=pValue;return *this;}
    inline FIVec2 &operator=(float &pValue) {mX=(int)pValue;mY=(int)pValue;return *this;}
    
    inline bool	operator==(const FIVec2 &pFIVec2) {return (mX==pFIVec2.mX)&(mY==pFIVec2.mY);}
    inline bool	operator!=(const FIVec2 &pFIVec2) {return (mX!=pFIVec2.mX)|(mY!=pFIVec2.mY);}
    
    inline const FIVec2	operator*(const FIVec2 &pFIVec2) const {return FIVec2(mX*pFIVec2.mX,mY*pFIVec2.mY);}
    inline FIVec2 &operator*=(const FIVec2 &pFIVec2) {mX*=pFIVec2.mX;mY*=pFIVec2.mY;return *this;}
    inline const FIVec2 operator*(const int pint) const {return FIVec2(mX*pint,mY*pint);}
    inline FIVec2 &operator*=(const int pint) {mX*=pint;mY*=pint;return *this;}
    inline const FIVec2	operator/(const FIVec2 &pFIVec2) const {return FIVec2(mX/pFIVec2.mX,mY/pFIVec2.mY);}
    inline FIVec2 &operator/=(const FIVec2 &pFIVec2) {mX/=pFIVec2.mX;mY/=pFIVec2.mY;return *this;}
    inline const FIVec2 operator/(const int pint) const {return FIVec2(mX/pint,mY/pint);}
    inline FIVec2 &operator/=(const int pint) {mX/=pint;mY/=pint;return *this;}
    inline const FIVec2 operator+(const FIVec2 &pFIVec2) const {return FIVec2(mX+pFIVec2.mX,mY+pFIVec2.mY);}
    inline FIVec2 &operator+=(const FIVec2 &pFIVec2) {mX+=pFIVec2.mX;mY+=pFIVec2.mY;return *this;}
    inline const FIVec2 operator+(const int pint) const {return FIVec2(mX+pint,mY+pint);}
    inline FIVec2 &operator+=(const int pint) {mX+=pint;mY+=pint;return *this;}
    inline const FIVec2 operator-(const FIVec2 &pFIVec2) const {return FIVec2(mX-pFIVec2.mX,mY-pFIVec2.mY);}
    inline FIVec2 &operator-=(const FIVec2 &pFIVec2) {mX-=pFIVec2.mX;mY-=pFIVec2.mY;return *this;}
    inline const FIVec2 operator-(const int pint) const {return FIVec2(mX-pint,mY-pint);}
    inline FIVec2 & operator-=(const int pint) {mX-=pint;mY-=pint;return *this;}
    inline const FIVec2 operator-() const {return FIVec2(-mX,-mY);}
    
    int                               mX;
    int                               mY;
    
};

FVec2 FVec2Lerp(FVec2 vectorStart, FVec2 vectorEnd, float t);

#endif
