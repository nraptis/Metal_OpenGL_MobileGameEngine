/*
 *  PrimitiveMesh.h
 *  Darts
 *
 *  Created by Nick Raptis on 12/9/10.
 *  Copyright 2010 Nick Raptis. All rights reserved.
 *
 */

#ifndef PRIMITIVE_MESH_H
#define PRIMITIVE_MESH_H


#include "FString.hpp"
#include "FIndexList.hpp"

class FFile;
class FSprite;

struct FDrawNode
{
    float							mX;
    float							mY;
    float							mZ;
    
    float							mU;
    float							mV;
    float							mW;
    
    float							mR;
    float							mG;
    float							mB;
    float							mA;
};

class FDrawNodeList
{
public:
    FDrawNodeList();
    virtual ~FDrawNodeList();
    
    virtual void                    Size(int pSize);
    virtual void                    Reset();
    virtual void                    Clear();
    
    
    void                            Add(FDrawNode *pNode);
    void                            Add(float pX, float pY, float pZ, float pU, float pV, float pW, float pRed, float pGreen, float pBlue, float pAlpha);
    
    
    void                            Set(int pIndex, float pX, float pY, float pZ, float pU, float pV, float pW, float pRed, float pGreen, float pBlue, float pAlpha);
    
    void                            SetXY(int pIndex, float pX, float pY);
    void                            SetUV(int pIndex, float pU, float pV);
    
    void                            SetXYZ(int pIndex, float pX, float pY, float pZ);
    void                            SetUVW(int pIndex, float pU, float pV, float pW);
    void                            SetRGBA(int pIndex, float pRed, float pGreen, float pBlue, float pAlpha);
    
    void                            SwapUV();
    
    FDrawNode                       *mData;
    FIndexList                      mIndexList;
    
    int                             mNodeSize;
    
    int                             mCountNodes;
    
    int                             mCountXYZ;
    int                             mCountUVW;
    int                             mCountC;
    
    bool                            mEnabledTexture;
    bool                            mEnabledColor;
    
    inline void                     DrawSetup(FSprite *pSprite);
    
    virtual void					Draw(FSprite *pSprite, bool pStrips=false);
    virtual void					Draw(FSprite &pSprite, bool pStrips=false){Draw(&pSprite, pStrips);}
    
    virtual void					DrawTris(FSprite *pSprite) { Draw(pSprite, false); }
    virtual void					DrawTris(FSprite &pSprite) { Draw(&pSprite, false); }
    virtual void					DrawTris() { Draw(0, false); }
    
    virtual void					DrawTriStrips(FSprite *pSprite) { Draw(pSprite, true); }
    virtual void					DrawTriStrips(FSprite &pSprite) { Draw(&pSprite, true); }
    virtual void					DrawTriStrips() { Draw(0, true); }
    
    void                            DrawNodes(int pHighlightIndex);
    void                            DrawNodes(){DrawNodes(-1);}
    
    int                             GetClosestNode(float pX, float pY, float &pDist);
    int                             GetClosestNode(float x, float y);
    
    void                            AdjustTextureCoordinates(float pStartU, float pStartV, float pEndU, float pEndV);
    void                            AdjustTextureCoordinates(FSprite *pSprite);
    void                            AdjustTextureCoordinates(FSprite &pSprite) { AdjustTextureCoordinates(&pSprite); }
    
    void                            SetX(int pIndex, float pX);
    void                            SetY(int pIndex, float pY);
    void                            SetZ(int pIndex, float pZ);
    
    void                            SetU(int pIndex, float pU);
    void                            SetV(int pIndex, float pV);
    void                            SetW(int pIndex, float pW);
    
    void                            SetR(int pIndex, float pRed);
    void                            SetG(int pIndex, float pGreen);
    void                            SetB(int pIndex, float pBlue);
    void                            SetA(int pIndex, float pAlpha);
    
    inline float                    GetX(int pIndex){return ((pIndex>=0)&&(pIndex<mCountNodes))?(mData[pIndex].mX):(0.0f);}
    inline float                    GetY(int pIndex){return ((pIndex>=0)&&(pIndex<mCountNodes))?(mData[pIndex].mY):(0.0f);}
    inline float                    GetZ(int pIndex){return ((pIndex>=0)&&(pIndex<mCountNodes))?(mData[pIndex].mZ):(0.0f);}
    
    inline float                    GetU(int pIndex){return ((pIndex>=0)&&(pIndex<mCountNodes))?(mData[pIndex].mU):(0.0f);}
    inline float                    GetV(int pIndex){return ((pIndex>=0)&&(pIndex<mCountNodes))?(mData[pIndex].mV):(0.0f);}
    inline float                    SetW(int pIndex){return ((pIndex>=0)&&(pIndex<mCountNodes))?(mData[pIndex].mW):(0.0f);}
    
    inline float                    GetR(int pIndex){return ((pIndex>=0)&&(pIndex<mCountNodes))?(mData[pIndex].mR):(0.0f);}
    inline float                    GetG(int pIndex){return ((pIndex>=0)&&(pIndex<mCountNodes))?(mData[pIndex].mG):(0.0f);}
    inline float                    GetB(int pIndex){return ((pIndex>=0)&&(pIndex<mCountNodes))?(mData[pIndex].mB):(0.0f);}
    inline float                    GetA(int pIndex){return ((pIndex>=0)&&(pIndex<mCountNodes))?(mData[pIndex].mA):(0.0f);}
};


class FDrawNodeMesh : public FDrawNodeList
{
public:
    
    FDrawNodeMesh();
    virtual ~FDrawNodeMesh();
    
    virtual void                    Reset();
    virtual void                    Clear();
    
    void                            AddConnection(int pStartIndex, int pEndIndex);
    
    void                            Generate();
    FDrawNodeList                   mRenderNodes;
    
    void                            Print(float pCenterX=0.0f, float pCenterY=0.0f);
    
    short                           *mConLink1;
    short                           *mConLink2;
    int                             mConLinkSize;
    int                             mConLinkCount;

    void                            AddTriangle(short pIndex1, short pIndex2, short pIndex3);
    
    short                           *mTriList1;
    short                           *mTriList2;
    short                           *mTriList3;
    
    int                             mTriListSize;
    int                             mTriListCount;
    
    void                            DrawConnections();
};










#endif



