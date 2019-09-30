//
//  FLine.h
//  2015 Gnome Launcher
//
//  Created by Nicholas Raptis on 1/4/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef ___015_Fleet_XP__FLine__
#define ___015_Fleet_XP__FLine__

class FLine
{
public:
    
    FLine(float x1,float y1,float x2,float y2);
    FLine();
    ~FLine();
    
    void					Make(float x1,float y1,float x2,float y2);
    virtual void			Draw();
    
    
    float					GetDist(float x, float y, int &pIndex);
    
    int						GetPoint(float x, float y, float pDist=50.0f);
    void					SetPoint(int pIndex, float x, float y);
    
    void					ClosestPoint(float x, float y, float &pClosestX, float &pClosestY);
    float					RayPlaneDist(float x, float y, float pDirX, float pDirY);
    
    
    
    static bool                         SegmentClosestPoint(float pLineX1, float pLineY1, float pLineX2, float pLineY2, float pPointX, float pPointY, float &pClosestX, float &pClosestY);
    
    
    static bool                         SegmentSegmentIntersection(float pL_1_x1, float pL_1_y1, float pL_1_x2, float pL_1_y2,
                                                                   float pL_2_x1, float pL_2_y1, float pL_2_x2, float pL_2_y2,
                                                                   float &pCollideX, float &pCollideY);

    //No range checking, no divisor checking, only use when you know
    //the lines collide..
    static bool                         LineLineIntersection(float pL_1_x1, float pL_1_y1, float pL_1_x2, float pL_1_y2,
                                                                   float pL_2_x1, float pL_2_y1, float pL_2_x2, float pL_2_y2,
                                                                   float &pCollideX, float &pCollideY);
    
    
    static bool                         SegmentPlaneIntersection(float pL_1_x1, float pL_1_y1, float pL_1_x2, float pL_1_y2,
                                                       float pPlaneX, float pPlaneY, float pPlaneDirX, float pPlaneDirY,
                                                       float &pCollideX, float &pCollideY, float &pCollideDistance);
    
    static bool                         SegmentRayIntersection(float pL_1_x1, float pL_1_y1, float pL_1_x2, float pL_1_y2,
                                                float pRayX, float pRayY, float pRayDirX, float pRayDirY, float pRayLength, 
                                                float &pCollideX, float &pCollideY, float &pCollideDistance);
    
    
    
    
    //void					ComputeBoundingBox();
    
    float					mX1,mY1,mX2,mY2;
    
    float					mNormalX;
    float					mNormalY;
    
    float					mDirX;
    float					mDirY;
    
    float					mDiffX;
    float					mDiffY;
    
    float					mLength;
    
    float					mCosAlpha;
    
};

#endif /* defined(___015_Fleet_XP__FLine__) */
