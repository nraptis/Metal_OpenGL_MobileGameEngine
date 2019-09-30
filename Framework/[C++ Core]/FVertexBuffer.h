#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#define VERTEX_BUFFER_MODE_TRIANGLES 0
#define VERTEX_BUFFER_MODE_TRIANGLE_STRIPS 1
#define VERTEX_BUFFER_MODE_TRIANGLE_FANS 2
#define VERTEX_BUFFER_MODE_LINES 3

#include "FColor.hpp"

class FTexture;
class FVertexBuffer
{
public:
    
	FVertexBuffer();
    ~FVertexBuffer();
    
    void                                    SetTexture(FTexture *pTexture);
    FTexture                                *mTexture;
    
    void                                    AddQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    void                                    AddQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,
                                                    float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4
                                                    );
	
	inline void                             Add(float x, float y, float u, float v){Add(x, y, 0, u, v, 1.0f);}
	void                                    Add(float x, float y, float z, float u, float v, float w=1.0f);
    
    
    void                                    AddUV(float u, float v){AddUVW(u,v,1.0f);}
    void                                    AddUVW(float u, float v, float w);
    void                                    AddXYZ(float x, float y, float z);
    
    void                                    AddRGBA(float pRed, float pGreen, float pBlue, float pAlpha);
    void                                    AddExtraStereo(float pRed, float pGreen, float pBlue, float pAlpha);
    
    
    //void                StereoscopicShift(float pShiftMin, float pShiftMax, FVertexBuffer *pBuffer, Color pColorOuter=Color(1.0f,0.5f,0.5f,0.25f), Color pColorInner=Color(1.0f,1.0f,1.0f,0.65f));
	
    void                                    DrawColored();
    
	void                                    Draw();
	void                                    Draw(int pCount);
	void                                    Draw(int pStart, int pCount);
    
    void                                    DrawStrips();
	void                                    DrawStrips(int pCount);
	void                                    DrawStrips(int pStart, int pCount);
	
	void                                    DrawTriangles();
	
	void                                    GenerateMagicCube(float pSize=1);
	void                                    GenerateCube(float pSize=1);
	void                                    GeneratePanoCube(float pSize=1);
	
    void                                    Reset() { mVertexCount = 0; mCoordCount = 0; mColorCount=0; }
	void                                    Clear() { mVertexCount = 0; }
    
    void                                    Kill();
    
	int                                     mVertexSize;
    int                                     mCoordSize;
    
    int                                     mVertexCount;
    int                                     mCoordCount;
    
    int                                     mColorCount;
    int                                     mColorSize;
    
    int                                     mBindIndex;
	
	int                                     mMode;
	
	float                                   *mXYZ;
	float                                   *mUVW;
    float                                   *mRGBA;
    //float                                   *mExtra;
    
    //int                                     mExtraDimensionality;

    
};

#endif


