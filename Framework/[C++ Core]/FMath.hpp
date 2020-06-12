#ifndef MATH_H
#define MATH_H

#define D_R 0.01745329251994329576923690768488f
#define R_D 57.2957795130823208767981548141052f

#define PI 3.1415926535897932384626433832795028841968f
#define PI2 (2 * PI)
#define PI_2 (PI * 0.5f)

#define DOT_PRODUCT(x1,y1,x2,y2)((x1)*(x2)+(y1)*(y2))
#define CROSS_PRODUCT(x1,y1,x2,y2)((x1)*(y2)-(x2)*(y1))

#define SQRT_EPSILON 0.005f
#define FLOAT_EPSILON 0.0001f

#include "FVec2.hpp"
#include "FVec3.hpp"

float Distance(float x1, float y1, float x2, float y2);
inline float Distance(float x1, float y1, FVec2 p2){return Distance(x1,y1,p2.mX,p2.mY);}
inline float Distance(FVec2 p1, float x2, float y2){return Distance(p1.mX,p1.mY,x2,y2);}
inline float Distance(FVec2 p1, FVec2 p2){return Distance(p1.mX,p1.mY,p2.mX,p2.mY);}

float DistanceSquared(float x1, float y1, float x2, float y2);
inline float DistanceSquared(float x1, float y1, FVec2 p2){return DistanceSquared(x1,y1,p2.mX,p2.mY);}
inline float DistanceSquared(FVec2 p1, float x2, float y2){return DistanceSquared(p1.mX,p1.mY,x2,y2);}
inline float DistanceSquared(FVec2 p1, FVec2 p2){return DistanceSquared(p1.mX,p1.mY,p2.mX,p2.mY);}

float DistanceSquared(float x1, float y1, float z1, float x2, float y2, float z2);
inline float DistanceSquared(FVec3 p1, FVec3 p2){return DistanceSquared(p1.mX,p1.mY,p1.mZ,p2.mX,p2.mY,p2.mZ);}



FVec2 AngleToVector(float pDegrees);

FVec3 AngleToVector3D(float pDegrees);

float Sin(float pDegree);
float Cos(float pDegrees);
float Tan(float pDegrees);

bool IsPowerOfTwo(int pNumber);

int ClosestPowerOfTwo(int pNumber);

float DistanceBetweenAngles(float theDegrees1, float theDegrees2);

float FaceTarget(float pOriginX, float pOriginY, float pTargetX = 0.0f, float pTargetY = 0.0f);
inline float FaceTarget(FVec2 pPos, FVec2 pTarget = FVec2(0.0f, 0.0f)) { return FaceTarget(pPos.mX, pPos.mY, pTarget.mX, pTarget.mY); }

float FaceTargetFlipped(float pOriginX, float pOriginY, float pTargetX = 0.0f, float pTargetY = 0.0f);
inline float FaceTargetFlipped(FVec2 pPos, FVec2 pTarget = FVec2(0.0f, 0.0f)) { return FaceTargetFlipped(pPos.mX, pPos.mY, pTarget.mX, pTarget.mY); }

FVec2 PivotPoint(FVec2 pPoint, float pDegrees, FVec2 pCenter, float pScaleX, float pScaleY);
FVec2 PivotPoint(FVec2 pPoint, float pDegrees, FVec2 pCenter, float pScale = 1.0f);
FVec2 PivotPoint(FVec2 pPoint, float pDegrees);

FVec3 PivotPoint(FVec3 pPoint, float pDegrees, FVec3 pCenter, float pScaleX, float pScaleY);
FVec3 PivotPoint(FVec3 pPoint, float pDegrees, FVec3 pCenter, float pScale = 1.0f);
FVec3 PivotPoint(FVec3 pPoint, float pDegrees);

float MinC(float pNum, float pMin);
float MaxC(float pNum, float pMax);
float Clamp(float pNum, float pMin, float pMax);

//(Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax)
int SideOfLine(float pTestX, float pTestY, float pLineX1, float pLineY1, float pLineX2, float pLineY2);

FVec3 Rotate3D(FVec3 pPoint, FVec3 pAxis, float pDegrees);

FVec3 Rotate3DNormalized(FVec3 pPoint, FVec3 pAxis, float pDegrees);


bool TriangleIsClockwise(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3);

bool QuadContainsPoint(float pPointX, float pPointY, float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4);

float TriangleArea(float x1, float y1, float x2, float y2, float x3, float y3);
bool Between(float x1, float y1, float x2, float y2, float x3, float y3);
bool SegmentsIntersect(FVec2 theStart1, FVec2 theEnd1, FVec2 theStart2, FVec2 theEnd2);


bool EllipseContainsPoint(float pPointX, float pPointY, float pEllipseX, float pEllipseY, float pEllipseAxisH, float pEllipseAxisV);
bool EllipseContainsPoint(float pPointX, float pPointY, float pEllipseX, float pEllipseY, float pEllipseAxisH, float pEllipseAxisV, float pEllipseRotation);





/*
class func fallOffDampen(input:CGFloat, falloffStart:CGFloat, resultMax: CGFloat, inputMax:CGFloat) -> CGFloat {
    var result: CGFloat = input
    if result > falloffStart {
        result = resultMax
        if input < inputMax {
            //We are constrained between [falloffStart .. inputMax]
            let span = (inputMax - falloffStart)
            if span > 0.01 {
                var percentLinear = (input - falloffStart) / span
                if percentLinear < 0.0 { percentLinear = 0.0 }
                if percentLinear > 1.0 { percentLinear = 1.0 }
                //sin [0..1] => [0..pi/2]
                let factor = CGFloat(sinf(Float(percentLinear * (CGFloat.pi * 0.5))))
                result = falloffStart + factor * (resultMax - falloffStart)
            }
        }
    }
    return result
    }
    
    class func fallOffDampenInverse(input:CGFloat, falloffStart:CGFloat, resultMax: CGFloat, inputMax:CGFloat) -> CGFloat {
        var result: CGFloat = input
        if input > falloffStart {
            result = inputMax
            if input < resultMax {
                //We are constrained between [falloffStart .. resultMax]
                let span = (resultMax - falloffStart)
                if span > 0.01 {
                    var percentLinear = (input - falloffStart) / span
                    if percentLinear < 0.0 { percentLinear = 0.0 }
                    if percentLinear > 1.0 { percentLinear = 1.0 }
                    //asin [0..1] => [0..pi/2]
                    let factor = CGFloat(asinf(Float(percentLinear))) / (CGFloat.pi * 0.5)
                    result = falloffStart + factor * (inputMax - falloffStart)
                }
            }
        }
        return result
    }
*/
    

/*
double intersect(Point pOrigin, Vector pNormal, Point rOrigin, Vector rVector)
{
    double d = -(planeNormal * planeOrigin);
    double numer = planeNormal * rayOrigin + d;
    double denom = planeNormal * rayVector;
    return -(numer / denom);
}
*/



/*
	
	
	
	double intersectSphere(Point rO,
 Vector rV,
 Point sO,
 double sR)
	{
 
 float qx=mCircleTest->mX -
 
 Vector Q = sO - rO;
 double c = length of Q;
 double v = Q * rV;
 double d = sR*sR - (c*c – v*v);
 
 // If there was no intersection, return -1
 
 if(d < 0.0) return -1.0;
 
 // Return the distance to the [first] intersecting point
 
 return v - sqrtf(d);
	}
 */

/*
bool EllipseIntersectLine(FVec2 pCenter, FVec2 pRadii, FVec2 pLineStart, , FVec2 pLineEnd)
{
	//
	// Get the closest point on the line to the center of the ellipse.
	//
	Point aClosest=theLine.ClosestPoint(theCenter);
	
	//
	// Move it into ellipse space
	//
	aClosest-=theCenter;
	
	//
	// Figure out some ellipse stuff
	//
	float aMajorAxis=max(theRadius.mX,theRadius.mY);
	float aMinorAxis=min(theRadius.mX,theRadius.mY);
	float aAxisRatio=aMinorAxis/aMajorAxis;
	
	//
	// Scale our point
	//
	if(aMajorAxis==theRadius.mX) aClosest.mX*=aAxisRatio;
	if(aMajorAxis==theRadius.mY) aClosest.mY*=aAxisRatio;
	
	//
	// Is it in the circle?
	//
	if(aClosest.Length()<=aMinorAxis) return true;
	return false;
}
 */

#endif
