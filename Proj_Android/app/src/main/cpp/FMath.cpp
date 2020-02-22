#include "FMath.hpp"
#include "core_includes.h"

float Distance(float x1, float y1, float x2, float y2)
{
    float aXDiff=x1-x2;
    float aYDiff=y1-y2;
    return sqrtf(aXDiff*aXDiff+aYDiff*aYDiff);
}

float DistanceSquared(float x1, float y1, float x2, float y2) {
    float aXDiff = x1 - x2;
    float aYDiff = y1 - y2;
    return aXDiff * aXDiff + aYDiff * aYDiff;
}

float DistanceSquared(float x1, float y1, float z1, float x2, float y2, float z2) {
    float aXDiff = x1 - x2;
    float aYDiff = y1 - y2;
    float aZDiff = z1 - z2;
    return aXDiff * aXDiff + aYDiff * aYDiff + aZDiff * aZDiff;
}

bool CircleCircleIntersect(FVec2 pPos1, float pRadius1, FVec2 pPos2, float pRadius2) {
    float aRadiiSum = pRadius1 + pRadius2;
    return DistanceSquared(pPos1, pPos2) <= aRadiiSum * aRadiiSum;
}

FVec2 AngleToVector(float pDegrees) {
    return FVec2(Sin(pDegrees), -Cos(pDegrees));
}

FVec3 AngleToVector3D(float pDegrees) {
    return FVec3(Sin(pDegrees), -Cos(pDegrees), 0.0f);
}

bool IsPowerOfTwo(int pNumber) {
    return (pNumber&-pNumber) == pNumber;
}

int ClosestPowerOfTwo(int pNumber)
{
    
    int aResult=1;
    
    while ((aResult < pNumber) && (aResult < 4096))
    {
        aResult = (aResult * 2);
    }
    
    //while((unsigned int)pNumber<aResult&&aResult!=0x40000000)aResult=(aResult<<1);
    return (int)aResult;
}

int SideOfLine(float pTestX, float pTestY, float pLineX1, float pLineY1, float pLineX2, float pLineY2)
{
    float aCross = (pLineX2 - pLineX1) * (pTestY - pLineY1) - (pLineY2 - pLineY1) * (pTestX - pLineX1);
    if(aCross > 0)return 1;
    else if(aCross < 0)return -1;
    else return 0;
    
}

float Sin(float pDegrees) { return sinf(D_R * pDegrees); }
float Cos(float pDegrees) { return cosf(D_R * pDegrees); }
float Tan(float pDegrees) { return tanf(D_R * pDegrees); }

float DistanceBetweenAngles(float theDegrees1, float theDegrees2) {
    float aDifference = theDegrees1 - theDegrees2;
    aDifference = (float)fmodf(aDifference, 360.0f);
    if (aDifference < 0.0f) { aDifference += 360.0f; }
    if (aDifference > 180.0f) { return 360.0f - aDifference; }
    else return -aDifference;
}

float FaceTarget(float pOriginX, float pOriginY, float pTargetX, float pTargetY) {
    return RADIANS_TO_DEGREES(-atan2f(pOriginX - pTargetX, pOriginY - pTargetY));
}

float Clamp(float pNum, float pMin, float pMax) {
    float aResult = pNum;
    if (aResult < pMin) { aResult = pMin; }
    if (aResult > pMax) { aResult = pMax; }
    return aResult;
}

float MinC(float pNum, float pMin) {
    if (pNum < pMin) { return pNum; }
    else { return pMin; }
}

float MaxC(float pNum, float pMax) {
    if (pNum > pMax) { return pNum; }
    else { return pMax; }
}

bool TriangleIsClockwise(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3) {
    return (pX2 - pX1) * (pY3 - pY2) - (pX3 - pX2) * (pY2 - pY1) > 0.0f;
}

bool QuadContainsPoint(float pPointX, float pPointY, float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4) {
    float aX[4];
    float aY[4];
    
    aX[0] = pX1;
    aX[1] = pX2;
    aX[2] = pX3;
    aX[3] = pX4;
    
    aY[0] = pY1;
    aY[1] = pY2;
    aY[2] = pY3;
    aY[3] = pY4;
    
    bool aResult = false;
    for (int aStart=0,aEnd=3;aStart<4;aEnd=aStart++) {
        if((((aY[aStart]<=pPointY) && (pPointY<aY[aEnd]))||
            ((aY[aEnd]<=pPointY) && (pPointY<aY[aStart])))&&
           (pPointX < (aX[aEnd] - aX[aStart])*(pPointY - aY[aStart])
            /(aY[aEnd] - aY[aStart]) + aX[aStart])) {
            aResult=!aResult;
        }
    }
    
    return aResult;
    
}

FVec2 PivotPoint(FVec2 pPoint, float pDegrees, FVec2 pCenter, float pScaleX, float pScaleY) {
    FVec2 aResult;
    float aDiffX = pCenter.mX - pPoint.mX;
    float aDiffY = pCenter.mY - pPoint.mY;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if (aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
        float aRotation = FaceTarget(aDiffX, aDiffY);
        aRotation = pDegrees + aRotation;
        aResult.mX = pCenter.mX + Sin(180.0f -aRotation) * pScaleX * aDist;
        aResult.mY = pCenter.mY + Cos(180.0f -aRotation) * pScaleY * aDist;
    } else {
        aResult = pPoint;
    }
    return aResult;
}


FVec2 PivotPoint(FVec2 pPoint, float pDegrees, FVec2 pCenter, float pScale) {
    FVec2 aResult;
    float aDiffX = pCenter.mX - pPoint.mX;
    float aDiffY = pCenter.mY - pPoint.mY;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if (aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
        float aRotation = FaceTarget(aDiffX, aDiffY);
        aRotation = pDegrees + aRotation;
        aResult.mX = pCenter.mX + Sin(180.0f -aRotation) * pScale * aDist;
        aResult.mY = pCenter.mY + Cos(180.0f -aRotation) * pScale * aDist;
    } else {
        aResult = pPoint;
    }
    return aResult;
}

FVec2 PivotPoint(FVec2 pPoint, float pDegrees) {
    FVec2 aOrigin;
    return PivotPoint(pPoint, pDegrees, aOrigin, 1.0f);
}

FVec3 PivotPoint(FVec3 pPoint, float pDegrees, FVec3 pCenter, float pScaleX, float pScaleY) {
    FVec3 aResult;
    float aDiffX = pCenter.mX - pPoint.mX;
    float aDiffY = pCenter.mY - pPoint.mY;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if (aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
        float aRotation = FaceTarget(aDiffX, aDiffY);
        aRotation = pDegrees + aRotation;
        aResult.mX = pCenter.mX + Sin(180.0f -aRotation) * pScaleX * aDist;
        aResult.mY = pCenter.mY + Cos(180.0f -aRotation) * pScaleY * aDist;
    } else {
        aResult = pPoint;
    }
    aResult.mZ = pPoint.mZ;
    return aResult;
}

FVec3 PivotPoint(FVec3 pPoint, float pDegrees, FVec3 pCenter, float pScale) {
    FVec3 aResult;
    float aDiffX = pCenter.mX - pPoint.mX;
    float aDiffY = pCenter.mY - pPoint.mY;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if (aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
        float aRotation = FaceTarget(aDiffX, aDiffY);
        aRotation = pDegrees + aRotation;
        aResult.mX = pCenter.mX + Sin(180.0f - aRotation) * pScale * aDist;
        aResult.mY = pCenter.mY + Cos(180.0f - aRotation) * pScale * aDist;
    } else {
        aResult = pPoint;
    }
    aResult.mZ = pPoint.mZ;
    return aResult;
}

FVec3 PivotPoint(FVec3 pPoint, float pDegrees) {
    FVec3 aOrigin;
    return PivotPoint(pPoint, pDegrees, aOrigin, 1.0f);
}

FVec3 Rotate3D(FVec3 pPoint, FVec3 pAxis, float pDegrees) {
    FVec3 aDir = FVec3(pAxis.mX, pAxis.mY, pAxis.mZ);
    float aLength = aDir.Length();
    if (aLength > SQRT_EPSILON) {
        aDir /= aLength;
    } else {
        aDir.mX = 1;
        aDir.mY = 0;
        aDir.mZ = 0;
    }
    return Rotate3DNormalized(pPoint, aDir, pDegrees);
}

FMatrix cVector3DRotationMatrix;
FVec3 Rotate3DNormalized(FVec3 pPoint, FVec3 pAxis, float pDegrees) {
    cVector3DRotationMatrix.ResetRotationNormalized(pDegrees, pAxis.mX, pAxis.mY, pAxis.mZ);
    return cVector3DRotationMatrix.ProcessVec3RotationOnly(pPoint);
}

float TriangleArea(float x1, float y1, float x2, float y2, float x3, float y3) {
    return (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
}

bool Between(float x1, float y1, float x2, float y2, float x3, float y3) {
    if (x1 != x2) { return (x1 <= x3 && x3 <= x2) || (x1 >= x3 && x3 >= x2); }
    else { return (y1 <= y3 && y3 <= y2) || (y1 >= y3 && y3 >= y2); }
}

bool SegmentsIntersect(FVec2 theStart1, FVec2 theEnd1, FVec2 theStart2, FVec2 theEnd2) {
    
    if (fabsf(theStart1.mX - theEnd1.mX) <= 0.1f && fabsf(theStart1.mY - theEnd1.mY) <= 0.1f) {
        return false;
    }
    
    if (fabsf(theStart2.mX - theEnd2.mX) <= 0.1f && fabsf(theStart2.mY - theEnd2.mY) <= 0.1f) {
        return false;
    }
        
    float aArea1, aArea2, aArea3, aArea4;
    if ((aArea1 = TriangleArea(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theStart2.mX, theStart2.mY)) == 0) {
        if (Between(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theStart2.mX, theStart2.mY)) {
            return true;
        } else {
            if (TriangleArea(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theEnd2.mX, theEnd2.mY) == 0) {
                if (Between(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theStart1.mX, theStart1.mY)) {
                    return true;
                }
                if (Between (theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theEnd1.mX, theEnd1.mY)) {
                    return true;
                }
                return false;
            }
            return false;
        }
    }
    if ((aArea2 = TriangleArea(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theEnd2.mX, theEnd2.mY)) == 0) {
        return Between(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theEnd2.mX, theEnd2.mY);
    }
    if ((aArea3 = TriangleArea(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theStart1.mX, theStart1.mY)) == 0) {
        if (Between(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theStart1.mX, theStart1.mY)) {
            return true;
        } else {
            if (TriangleArea(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theEnd1.mX, theEnd1.mY) == 0) {
                if (Between(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theStart2.mX, theStart2.mY)) {
                    return true;
                }
                if (Between (theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theEnd2.mX, theEnd2.mY)) {
                    return true;
                }
                return false;
            }
            return false;
        }
    }
    if ((aArea4 = TriangleArea(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theEnd1.mX, theEnd1.mY)) == 0) {
        return Between(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theEnd1.mX, theEnd1.mY);
    }
    return (((aArea1 > 0) ^ (aArea2 > 0)) && ((aArea3 > 0) ^ (aArea4 > 0)));
}


bool EllipseContainsPoint(float pPointX, float pPointY, float pEllipseX, float pEllipseY, float pEllipseAxisH, float pEllipseAxisV) {
    if (pEllipseAxisH > 0.1f && pEllipseAxisV > 0.1f) {
        if (pPointY >= (pEllipseY - pEllipseAxisV) && pPointY <= (pEllipseY + pEllipseAxisV) && pPointX >= (pEllipseX - pEllipseAxisH) && pPointX <= (pEllipseX + pEllipseAxisH)) {
            if (pPointY < pEllipseY) {
                float aPercentV = (pEllipseY - pPointY) / pEllipseAxisV;
                aPercentV = (1.0f - aPercentV) - 1.0f;
                aPercentV = sqrtf(1.0f - aPercentV * aPercentV);
                float aAdjustedH = pEllipseAxisH * aPercentV;
                if (pPointX >= (pEllipseX - aAdjustedH) && pPointX <= (pEllipseX + aAdjustedH)) { return true; }
            } else if (pPointY > pEllipseY) {
                float aPercentV = (pPointY - pEllipseY) / pEllipseAxisV;
                aPercentV = (1.0f - aPercentV) - 1.0f;
                aPercentV = sqrtf(1.0f - aPercentV * aPercentV);
                float aAdjustedH = pEllipseAxisH * aPercentV;
                if (pPointX >= (pEllipseX - aAdjustedH) && pPointX <= (pEllipseX + aAdjustedH)) { return true; }
            } else {
                return true;
            }
        }
    }
    return false;
}

bool EllipseContainsPoint(float pPointX, float pPointY, float pEllipseX, float pEllipseY, float pEllipseAxisH, float pEllipseAxisV, float pEllipseRotation) {
    if (pEllipseRotation != 0.0f) {
        FVec2 aPoint(pPointX, pPointY);
        FVec2 aCenter(pEllipseX, pEllipseY);
        aPoint = PivotPoint(aPoint, -pEllipseRotation, aCenter);
        pPointX = aPoint.mX;
        pPointY = aPoint.mY;
    }
    return EllipseContainsPoint(pPointX, pPointY, pEllipseX, pEllipseY, pEllipseAxisH, pEllipseAxisV);
}


