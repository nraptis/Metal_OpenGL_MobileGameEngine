//
//  FVec3.h
//  SRT
//
//  Created by Nick Raptis on 10/8/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_VEC_3
#define FRAMEWORK_VEC_3

#include "FVec2.hpp"

class FVec3
{
public:
	FVec3() {mX=0;mY=0;mZ=0;}
	FVec3(const float pX, const float pY, const float pZ) {mX=pX;mY=pY;mZ=pZ;}
	FVec3(const FVec3 &pFVec3) {*this=pFVec3;}
	FVec3(const FVec2 &pFVec2) {*this=pFVec2;}
	
	inline FVec3 &operator=(const FVec3 &pFVec3) {if(this!=&pFVec3) {mX=pFVec3.mX;mY=pFVec3.mY;mZ=pFVec3.mZ;}return *this;}
	inline FVec3 &operator=(const FVec2 &pFVec2) {mX=pFVec2.mX;mY=pFVec2.mY;mZ=0;return *this;}
	
	inline bool	operator==(const FVec3 &pFVec3) {return (mX==pFVec3.mX)&(mY==pFVec3.mY)&(mZ==pFVec3.mZ);}
	inline bool	operator!=(const FVec3 &pFVec3) {return (mX!=pFVec3.mX)|(mY!=pFVec3.mY)|(mZ!=pFVec3.mZ);}
	
	inline const FVec3	operator*(const FVec3 &pFVec3) const {return FVec3(mX*pFVec3.mX,mY*pFVec3.mY,mZ*pFVec3.mZ);}
	inline FVec3 &operator*=(const FVec3 &pFVec3) {mX*=pFVec3.mX;mY*=pFVec3.mY;mZ*=pFVec3.mZ;return *this;}
	inline const FVec3 operator*(const float pFloat) const {return FVec3(mX*pFloat,mY*pFloat,mZ*pFloat);}
	inline FVec3 &operator*=(const float pFloat) {mX*=pFloat;mY*=pFloat;mZ*=pFloat;return *this;}
	inline const FVec3	operator/(const FVec3 &pFVec3) const {return FVec3(mX/pFVec3.mX,mY/pFVec3.mY,mZ/pFVec3.mZ);}
	inline FVec3 &operator/=(const FVec3 &pFVec3) {mX/=pFVec3.mX;mY/=pFVec3.mY;mZ/=pFVec3.mZ;return *this;}
	inline const FVec3 operator/(const float pFloat) const {return FVec3(mX/pFloat,mY/pFloat,mZ/pFloat);}
	inline FVec3 &operator/=(const float pFloat) {mX/=pFloat;mY/=pFloat;mZ/=pFloat;return *this;}
	inline const FVec3 operator+(const FVec3 &pFVec3) const {return FVec3(mX+pFVec3.mX,mY+pFVec3.mY,mZ+pFVec3.mZ);}
	inline FVec3 &operator+=(const FVec3 &pFVec3) {mX+=pFVec3.mX;mY+=pFVec3.mY;mZ+=pFVec3.mZ;return *this;}
	inline const FVec3 operator+(const float pFloat) const {return FVec3(mX+pFloat,mY+pFloat,mZ+pFloat);}
	inline FVec3 &operator+=(const float pFloat) {mX+=pFloat;mY+=pFloat;mZ+=pFloat;return *this;}
	inline const FVec3 operator-(const FVec3 &pFVec3) const {return FVec3(mX-pFVec3.mX,mY-pFVec3.mY,mZ-pFVec3.mZ);}
	inline FVec3 &operator-=(const FVec3 &pFVec3) {mX-=pFVec3.mX;mY-=pFVec3.mY;mZ-=pFVec3.mZ;return *this;}
	inline const FVec3 operator-(const float pFloat) const {return FVec3(mX-pFloat,mY-pFloat,mZ-pFloat);}
	inline FVec3 & operator-=(const float pFloat) {mX-=pFloat;mY-=pFloat;mZ-=pFloat;return *this;}
	inline const FVec3 operator-() const {return FVec3(-mX,-mY,-mZ);}
	
    
	inline const FVec3	operator*(const FVec2 &pFVec2) const {return FVec3(mX*pFVec2.mX,mY*pFVec2.mY,mZ);}
	inline FVec3 &operator*=(const FVec2 &pFVec2) {mX*=pFVec2.mX;mY*=pFVec2.mY;return *this;}
	inline const FVec3	operator/(const FVec2 &pFVec2) const {return FVec3(mX/pFVec2.mX,mY/pFVec2.mY,mZ);}
	inline FVec3 &operator/=(const FVec2 &pFVec2) {mX/=pFVec2.mX;mY/=pFVec2.mY;;return *this;}
	inline const FVec3 operator+(const FVec2 &pFVec2) const {return FVec3(mX+pFVec2.mX,mY+pFVec2.mY,mZ);}
	inline FVec3 &operator+=(const FVec2 &pFVec2) {mX+=pFVec2.mX;mY+=pFVec2.mY;return *this;}
	inline const FVec3 operator-(const FVec2 &pFVec2) const {return FVec3(mX-pFVec2.mX,mY-pFVec2.mY,mZ);}
	inline FVec3 &operator-=(const FVec2 &pFVec2) {mX-=pFVec2.mX;mY-=pFVec2.mY;return *this;}
    
    
    float                               Length();
    float                               LengthSquared();
    
    void                                Normalize();
    
    float                               mX;
	float                               mY;
    float                               mZ;
    
    float                               Dot(FVec3 &pVector);
    FVec3                               Cross(FVec3 &pVector);
    
    FVec3                               RotateX(float pDegrees);
    FVec3                               RotateY(float pDegrees);
    FVec3                               RotateZ(float pDegrees);
    
    FVec3                               GetPerp();
    FVec3                               GetProjected(FVec3 pPlaneOrigin, FVec3 pPlaneNormal);
    
};

#endif
