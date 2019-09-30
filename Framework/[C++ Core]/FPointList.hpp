//
//  FFloatList.h
//  2015 Gnome Launcher
//
//  Created by Nicholas Raptis on 12/23/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_POINT_LIST_HPP
#define FRAMEWORK_POINT_LIST_HPP

#include "FString.hpp"
#include "FPrimitive.hpp"
#include "FIndexList.hpp"
#include "FFloatList.hpp"

class FFile;
class FPointList {
public:

    FPointList();
    ~FPointList();
    
    float                   *mX;
    float                   *mY;

    void                    Clear();
    void                    Reset() { mCount = 0; }
    void                    RemoveAll() { mCount = 0; }
    
    void                    Add(FPointList *pList);
    void                    Add(float pX, float pY);
    void                    Set(int pIndex, float pX, float pY);
    int                     Remove(int pIndex);
    
    float                   GetX(int pIndex);
    float                   GetY(int pIndex);
    
    //void                    CopyList(FPointList *pList);
    //void                    CopyListReverse(FPointList *pList);
    

    void                    Reverse();
	void					RotateRight90();
	void					FlipH();
	void					FlipV();

    //void                    (int pCount, float pX1, float pY1, float pX2=0.0f, float pY2=0.0f, float pX3=0.0f, float pY3=0.0f, float pX4=0.0f, float pY4=0.0f, float pX5=0.0f, float pY5=0.0f, float pX6=0.0f, float pY6=0.0f, float pX7=0.0f, float pY7=0.0f, float pX8=0.0f, float pY8=0.0f);
    //void                    AddValuesReset(int pCount, float pX1, float pY1, float pX2=0.0f, float pY2=0.0f, float pX3=0.0f, float pY3=0.0f, float pX4=0.0f, float pY4=0.0f, float pX5=0.0f, float pY5=0.0f, float pX6=0.0f, float pY6=0.0f, float pX7=0.0f, float pY7=0.0f, float pX8=0.0f, float pY8=0.0f);
    
    
    void                    AddEdge(float pX1, float pY1, float pX2, float pY2);
    
    
    void                    Size(int pSize);
    inline void             SetSize(int pSize){Size(pSize);}
    
    bool                    ContainsPoint(float pX, float pY);

    
    int                     LoopIndex(int pIndex);
    float                   LoopX(int pIndex);
    float                   LoopY(int pIndex);
    
    float                   LoopAngleNext(int pIndex);
    float                   LoopAnglePrev(int pIndex);
    float                   LoopAngleBetween(int pIndex);
    float                   LoopAngleBetweenInside(int pIndex);
    
    void                    ValueAdd(float pAddX, float pAddY);
    void                    ValueMultiply(float pFactorX, float pFactorY);
    void                    ValueDivide(float pFactorX, float pFactorY);
    
    inline void             ValueAdd(float pAdd){ValueAdd(pAdd, pAdd);}
    inline void             ValueMultiply(float pFactor){ValueMultiply(pFactor, pFactor);}
    inline void             ValueDivide(float pFactor){ValueDivide(pFactor, pFactor);}
    
    void					DrawTriangleList(GFX_MODEL_INDEX_TYPE *pIndex, int pCount);

    void                    DrawPoints(float pSize = 5.0f);
    void                    OutlinePoints(float pSize = 8.0f, float pBorderWidth = 1.0f);
    
    
    void                    DrawEdges(float pLineSize=2.0f);
    void                    DrawEdgesOpen(float pLineSize=2.0f);
    
    
    
    void                    DrawEdgeLists(FPointList *pEdgeList1, FPointList *pEdgeList2, int pStartIndex, int pSkipAmount);
    
	//void                    Clone(FPointList *pPointList);
    

	void                    Clone(FPointList *pPointList);
	inline void             Clone(FPointList &pPointList){ Clone(&pPointList); }

    
    void                    CloneOffset(FPointList *pPointList, FPointList *pNormalList, float pOffset);
    inline void             CloneOffset(FPointList &pPointList, FPointList &pNormalList, float pOffset){CloneOffset(&pPointList, &pNormalList, pOffset);}
    
    void                    CloneOffset(FPointList *pPointList, float pOffset);
    inline void             CloneOffset(FPointList &pPointList, float pOffset){CloneOffset(&pPointList, pOffset);}
    
    
    int                     GetNextIndex(int pIndex);
    int                     GetPrevIndex(int pIndex);
    
    
    void                    GenerateEdgeLists(FPointList *pEdgeP1, FPointList *pEdgeP2, bool pClosed);
    void                    GetSymmetryFromEdges(FPointList *pEdgeP1, FPointList *pEdgeP2, bool pSliceSide, float pPlaneOriginX, float pPlaneOriginY, float pPlaneDirX, float pPlaneDirY);
    void                    GetSymmetry(FPointList *pOriginalPath, bool pOriginalPathClosed, bool pSliceSide, float pSliceLineX1, float pSliceLineY1, float pSliceLineX2, float pSliceLineY2);
    
    void                    Transform(FPointList *pPointList, float pX, float pY, float pScaleX, float pScaleY, float pRotation);
    inline void             Transform(FPointList *pPointList, float pX, float pY, float pScale, float pRotation) { Transform(pPointList, pX, pY, pScale, pScale, pRotation); }
    inline void             Transform(FPointList &pPointList, float pX, float pY, float pScaleX, float pScaleY, float pRotation) { Transform(&pPointList, pX, pY, pScaleX, pScaleY, pRotation); }
    inline void             Transform(FPointList &pPointList, float pX, float pY, float pScale, float pRotation){Transform(&pPointList, pX, pY, pScale, pScale, pRotation);}
    void                    Transform(float pX, float pY, float pScaleX, float pScaleY, float pRotation);
    
    inline void             Transform(float pX, float pY, float pScale, float pRotation){Transform(pX, pY, pScale, pScale, pRotation);}
    
    
    
    void                    TransformRotate(float pRotation);
    void                    TransformScaleRotate(float pScaleX, float pScaleY, float pRotation);
    void                    TransformTranslate(float pX, float pY);
    
    
    void                    Untransform(float pX, float pY, float pScaleX, float pScaleY, float pRotation);
    void                    UntransformScaleRotate(float pScaleX, float pScaleY, float pRotation);
    inline void             UntransformScaleRotate(float pScale, float pRotation) { UntransformScaleRotate(pScale, pScale, pRotation); }
    void                    UntransformTranslate(float pX, float pY);
    
    
    
    int						GetClosestIndex(float pX, float pY, float &pDist, int pIgnoreIndex1, int pIgnoreIndex2, int pIgnoreIndex3);
    int						GetClosestIndex(float pX, float pY, float &pDist);
    int                     GetClosestIndex(float pX, float pY);
    
    
    int						GetClosestEdge(float pX, float pY, bool pClosed, float &pDist);

    void                    GenerateRect(float pX, float pY, float pWidth, float pHeight);
    void                    GenerateCircle(float pRadius, float pMinDist = 20.0f);
    
    //float                   GetX(float pFrame);
    //float                   GetY(float pFrame);

    bool                    IsClockwise();
    
    int                     mCount;
    int                     mSize;
    
    void                    Save(FFile *pFile);
    void                    Load(FFile *pFile);
    
    
    float                   GetMinX();
    float                   GetMaxX();
    float                   GetMinY();
    float                   GetMaxY();
    
    
    float                   GetCenterX();
    float                   GetCenterY();
    
    
};

#endif /* defined(___015_Fleet_XP__FFloatList__) */
