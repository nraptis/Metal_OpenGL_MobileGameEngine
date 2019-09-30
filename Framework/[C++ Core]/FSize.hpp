//
//  FSize.h
//  SRT
//
//  Created by Nick Raptis on 10/8/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#ifndef SIZE_H
#define SIZE_H

class FSize
{
public:
    FSize(){mWidth=0;mHeight=0;}
    FSize(const float pWidth, const float pHeight) {mWidth=pWidth;mHeight=pHeight;}
    FSize(const float pWidth, const int pHeight) {mWidth=pWidth;mHeight=(float)pHeight;}
    FSize(const int pWidth, const float pHeight) {mWidth=(float)pWidth;mHeight=pHeight;}
    FSize(const int pWidth, const int pHeight) {mWidth=(float)pWidth;mHeight=(float)pHeight;}
    FSize(const FSize &pFSize) {*this=pFSize;}
    
    inline FSize &operator=(const FSize &pFSize) {if(this!=&pFSize) {mWidth=pFSize.mWidth;mHeight=pFSize.mHeight;}return *this;}
    inline FSize &operator=(float &pValue) {mWidth=pValue;mHeight=pValue;return *this;}
    inline FSize &operator=(int &pValue) {mWidth=(float)pValue;mHeight=(float)pValue;return *this;}
    
    inline bool	operator==(const FSize &pFSize) {return (mWidth==pFSize.mWidth)&(mHeight==pFSize.mHeight);}
    inline bool	operator!=(const FSize &pFSize) {return (mWidth!=pFSize.mWidth)|(mHeight!=pFSize.mHeight);}
    
    inline const FSize	operator*(const FSize &pFSize) const {return FSize(mWidth*pFSize.mWidth,mHeight*pFSize.mHeight);}
    inline FSize &operator*=(const FSize &pFSize) {mWidth*=pFSize.mWidth;mHeight*=pFSize.mHeight;return *this;}
    inline const FSize operator*(const float pFloat) const {return FSize(mWidth*pFloat,mHeight*pFloat);}
    inline FSize &operator*=(const float pFloat) {mWidth*=pFloat;mHeight*=pFloat;return *this;}
    inline const FSize	operator/(const FSize &pFSize) const {return FSize(mWidth/pFSize.mWidth,mHeight/pFSize.mHeight);}
    inline FSize &operator/=(const FSize &pFSize) {mWidth/=pFSize.mWidth;mHeight/=pFSize.mHeight;return *this;}
    inline const FSize operator/(const float pFloat) const {return FSize(mWidth/pFloat,mHeight/pFloat);}
    inline FSize &operator/=(const float pFloat) {mWidth/=pFloat;mHeight/=pFloat;return *this;}
    inline const FSize operator+(const FSize &pFSize) const {return FSize(mWidth+pFSize.mWidth,mHeight+pFSize.mHeight);}
    inline FSize &operator+=(const FSize &pFSize) {mWidth+=pFSize.mWidth;mHeight+=pFSize.mHeight;return *this;}
    inline const FSize operator+(const float pFloat) const {return FSize(mWidth+pFloat,mHeight+pFloat);}
    inline FSize &operator+=(const float pFloat) {mWidth+=pFloat;mHeight+=pFloat;return *this;}
    inline const FSize operator-(const FSize &pFSize) const {return FSize(mWidth-pFSize.mWidth,mHeight-pFSize.mHeight);}
    inline FSize &operator-=(const FSize &pFSize) {mWidth-=pFSize.mWidth;mHeight-=pFSize.mHeight;return *this;}
    inline const FSize operator-(const float pFloat) const {return FSize(mWidth-pFloat,mHeight-pFloat);}
    inline FSize & operator-=(const float pFloat) {mWidth-=pFloat;mHeight-=pFloat;return *this;}
    inline const FSize operator-() const {return FSize(-mWidth,-mHeight);}
    
    float                               mWidth;
    float                               mHeight;
};


class FISize
{
public:
    FISize(){mWidth=0;mHeight=0;}
    FISize(const int pWidth, const int pHeight) {mWidth=pWidth;mHeight=pHeight;}
    FISize(const int pWidth, const float pHeight) {mWidth=pWidth;mHeight=(int)pHeight;}
    FISize(const float pWidth, const int pHeight) {mWidth=(int)pWidth;mHeight=pHeight;}
    FISize(const float pWidth, const float pHeight) {mWidth=(int)pWidth;mHeight=(int)pHeight;}
    FISize(const FISize &pFISize) {*this=pFISize;}
    
    inline FISize &operator=(const FISize &pFISize) {if(this!=&pFISize) {mWidth=pFISize.mWidth;mHeight=pFISize.mHeight;}return *this;}
    inline FISize &operator=(int &pValue) {mWidth=pValue;mHeight=pValue;return *this;}
    inline FISize &operator=(float &pValue) {mWidth=(int)pValue;mHeight=(int)pValue;return *this;}
    
    inline bool	operator==(const FISize &pFISize) {return (mWidth==pFISize.mWidth)&(mHeight==pFISize.mHeight);}
    inline bool	operator!=(const FISize &pFISize) {return (mWidth!=pFISize.mWidth)|(mHeight!=pFISize.mHeight);}
    
    inline const FISize	operator*(const FISize &pFISize) const {return FISize(mWidth*pFISize.mWidth,mHeight*pFISize.mHeight);}
    inline FISize &operator*=(const FISize &pFISize) {mWidth*=pFISize.mWidth;mHeight*=pFISize.mHeight;return *this;}
    inline const FISize operator*(const int pint) const {return FISize(mWidth*pint,mHeight*pint);}
    inline FISize &operator*=(const int pint) {mWidth*=pint;mHeight*=pint;return *this;}
    inline const FISize	operator/(const FISize &pFISize) const {return FISize(mWidth/pFISize.mWidth,mHeight/pFISize.mHeight);}
    inline FISize &operator/=(const FISize &pFISize) {mWidth/=pFISize.mWidth;mHeight/=pFISize.mHeight;return *this;}
    inline const FISize operator/(const int pint) const {return FISize(mWidth/pint,mHeight/pint);}
    inline FISize &operator/=(const int pint) {mWidth/=pint;mHeight/=pint;return *this;}
    inline const FISize operator+(const FISize &pFISize) const {return FISize(mWidth+pFISize.mWidth,mHeight+pFISize.mHeight);}
    inline FISize &operator+=(const FISize &pFISize) {mWidth+=pFISize.mWidth;mHeight+=pFISize.mHeight;return *this;}
    inline const FISize operator+(const int pint) const {return FISize(mWidth+pint,mHeight+pint);}
    inline FISize &operator+=(const int pint) {mWidth+=pint;mHeight+=pint;return *this;}
    inline const FISize operator-(const FISize &pFISize) const {return FISize(mWidth-pFISize.mWidth,mHeight-pFISize.mHeight);}
    inline FISize &operator-=(const FISize &pFISize) {mWidth-=pFISize.mWidth;mHeight-=pFISize.mHeight;return *this;}
    inline const FISize operator-(const int pint) const {return FISize(mWidth-pint,mHeight-pint);}
    inline FISize & operator-=(const int pint) {mWidth-=pint;mHeight-=pint;return *this;}
    inline const FISize operator-() const {return FISize(-mWidth,-mHeight);}
    
    int                               mWidth;
    int                               mHeight;
    
};

#endif
