#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "os_core_app_shell.h"

#if (CURRENT_ENV == ENV_IOS)
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

#if (CURRENT_ENV == ENV_ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#endif

#include "OpenGLEngine.hpp"
#include "FColor.hpp"
#include "FRect.hpp"
#include "FVec2.hpp"
#include "FVec3.hpp"
#include "FPrimitive.hpp"
#include "FMatrix.hpp"
#include "FIndexList.hpp"
#include "FUniforms.hpp"
#include "ShaderProgram.hpp"
#include "FBuffer.hpp"

#define GFX_RENDER_PASS_COUNT 2

#define GFX_RENDER_PASS_2D_MAIN 0
#define GFX_RENDER_PASS_3D_MAIN 1

#define GFX_BUFFER_INDEX_DATA_INDEXED_MODEL 0
#define GFX_BUFFER_INDEX_UNIFORMS_INDEXED_MODEL 1

#define GFX_BUFFER_INDEX_DATA_INDEXED_SIMPLE_MODEL 0
#define GFX_BUFFER_INDEX_UNIFORMS_INDEXED_SIMPLE_MODEL 1

#define GFX_BUFFER_INDEX_UNIFORMS_SIMPLE_MODEL 2
#define GFX_BUFFER_INDEX_POSITIONS_SIMPLE_MODEL 0
#define GFX_BUFFER_INDEX_TEXTURE_COORDS_SIMPLE_MODEL 1

#define GFX_BUFFER_INDEX_UNIFORMS_SPRITE 2
#define GFX_BUFFER_INDEX_POSITIONS_SPRITE 0
#define GFX_BUFFER_INDEX_TEXTURE_COORDS_SPRITE 1

#define GFX_BUFFER_INDEX_POSITIONS_SHAPE 0
#define GFX_BUFFER_INDEX_UNIFORMS_SHAPE 1

#define GFX_BUFFER_INDEX_DATA_SHAPE_NODE 0
#define GFX_BUFFER_INDEX_UNIFORMS_SHAPE_NODE 1

#define GFX_MODEL_INDEX_GL_TYPE GL_UNSIGNED_SHORT

#define GRAPHICS_LIGHT_COUNT 8

class FTexture;

class Graphics
{
public:
    Graphics();
    ~Graphics();
    
    
    static void                             SetDeviceScale(float pScale);
    static void                             SetDeviceSize(float pWidth, float pHeight);
    
    static void                             Flush();
    
    static void                             Initialize();
    
    // When we get a new content, we SET UP.
    static void                             SetUp();
    
    //Before we lose out content, we TEAR DOWN.
    static void                             TearDown();
    
    
    
    static void                             PreRender();
    static void                             PostRender();
    
    static void                             BufferSetIndicesShape();
    static void                             BufferSetIndicesShapeNode();
    static void                             BufferSetIndicesSprite();
    static void                             BufferSetIndicesSimpleModel();
    static void                             BufferSetIndicesSimpleModelIndexed();
    static void                             BufferSetIndicesModelIndexed();
    
    
    static void                             BufferSetUniformsIndex(int pIndex);
    static void                             BufferSetPositionsIndex(int pIndex);
    static void                             BufferSetTextureCoordsIndex(int pIndex);
    static void                             BufferSetNormalsIndex(int pIndex);
    static void                             BufferSetTangentsIndex(int pIndex);
    static void                             BufferSetUNormalsIndex(int pIndex);
    static void                             BufferSetDataIndex(int pIndex);
    static void                             BufferSetTexturesIndex(int pIndex);
    
    
    static void                             DrawBox(float x1, float y1, float z1, float x2, float y2, float z2, float pSize, float pRotation=0);
    static void                             DrawQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4);
	static void                             DrawQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4);
    
    
    static void                             RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, FTexture *pTexture);
    static void                             RenderQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4,
                                                       float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture);
    
    //static void                             RenderQuadPushed(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4,
                                                       //float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, //float pV4, FTexture *pTexture, float pPush);
    
    
    static void								RenderQuadScaled(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture, float pScale);
    
    static void								RenderQuadScaled(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4, float pU1, float pV1, float pU2, float pV2, float pU3, float pV3, float pU4, float pV4, FTexture *pTexture, float pScale, float pCenterX, float pCenterY);


	static void                             RenderTriangle(float pX1, float pY1, float pZ1, float pX2, float pY2, float pZ2, float pX3, float pY3, float pZ3);
	static void                             RenderTriangle(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3);
    
    static void                             SetColorHex(int pRed, int pGreen, int pBlue, int pAlpha);
    static void                             SetColorHex(int pRed, int pGreen, int pBlue);
    static void                             SetColorHex(int pAlpha);
    
    static void                             SetColor(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                             SetColor(float pRed, float pGreen, float pBlue);
    static void                             SetColor(float pIntensity);
    static void                             SetColor();
    static void                             SetColor(FColor pColor);
    static void                             SetColorSwatch(int pSwatchIndex);
    static void                             SetColorSwatch(int pSwatchIndex, float pAlpha);
    
    static void                             OutlineRect(float pX, float pY, float pWidth, float pHeight, float pThickness);
    static void                             OutlineRectInside(float pX, float pY, float pWidth, float pHeight, float pThickness);
    
    static void                             OutlineRect(FRect pRect, float pThickness);
    static void                             OutlineRectInside(FRect pRect, float pThickness);
    
    
    static void                             DrawCurrentTile();
    
    static void                             DrawRect(float pX, float pY, float pWidth, float pHeight);
    inline static void                             DrawRect(FVec2 pPos, float pWidth, float pHeight){DrawRect(pPos.mX,pPos.mY,pWidth,pHeight);}
    inline static void                             DrawRect(FVec2 pPos, FVec2 pSize){DrawRect(pPos.mX,pPos.mY,pSize.mX,pSize.mY);}
    inline static void                             DrawRect(FRect pRect){DrawRect(pRect.mX,pRect.mY,pRect.mWidth,pRect.mHeight);}
    //inline static void                             DrawRect(FRect pRect){DrawRect(pRect.mX,pRect.mY,pRect.mWidth,pRect.mHeight);}
    
    static void                             DrawLine(float pX1, float pY1, float pX2, float pY2);
    inline static void                             DrawLine(FVec2 pPoint1, FVec2 pPoint2){DrawLine(pPoint1.mX,pPoint1.mY,pPoint2.mX,pPoint2.mY);}
    

    
    static void                             DrawLine(float pX1, float pY1, float pX2, float pY2, float pThickness);
    inline static void                             DrawLine(FVec2 pPoint1, FVec2 pPoint2, float pThickness){DrawLine(pPoint1.mX,pPoint1.mY,pPoint2.mX,pPoint2.mY, pThickness);}
    
    
    
    static void                             DrawArrow(float pStartX, float pStartY, float pEndX, float pEndY, float pHeadLength=12, float pThickness=2.0f);
    
    
    static void                             DrawPoint(float pX, float pY, float pSize=7);
    inline static void                             DrawPoint(FVec2 pPoint, float pSize=7){DrawPoint(pPoint.mX,pPoint.mY,pSize);}
    
    
    static void                             DepthEnable();
    
    static void                             DepthDisable();
    
    static void                             DepthClear();
    
    
    static void                             Clear(float pRed, float pGreen, float pBlue, float pAlpha);
    static void                             Clear(float pRed, float pGreen, float pBlue);
    static void                             Clear();
    
    
    static void                             ClipEnable();
    static void                             ClipDisable();

    static void                             Clip(float pX, float pY, float pWidth, float pHeight);
    
    static void                             ClipSetAppFrame(float pX, float pY, float pWidth, float pHeight);
    
    static void                             ViewportSet(float pX, float pY, float pWidth, float pHeight);
    
    static void                             MatrixProjectionSet(FMatrix &pMatrix);
    static void                             MatrixModelViewSet(FMatrix &pMatrix);
    
    
    static void                             MatrixProjectionResetOrtho();
    //FMatrix aOrtho = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -2048.0f, 2048.0f);
    //Graphics::MatrixProjectionSet(aOrtho);
    
    static void                             MatrixProjectionReset();
    static void                             MatrixModelViewReset();
    
    static FMatrix                          MatrixProjectionGet();
    static void                             MatrixProjectionGet(FMatrix *pMatrix);
    
    static FMatrix                          MatrixModelViewGet();
    static void                             MatrixModelViewGet(FMatrix *pMatrix);
    
    static void                             CullFacesSetFront();
    static void                             CullFacesSetBack();
    static void                             CullFacesSetDisabled();
    
    static void                             Ortho2D(float pLeft, float pRight, float pBottom, float pTop);
    static void                             Ortho2D();
    
    
    static void                             TextureSetWrap();
    static void                             TextureSetClamp();
    
    static void                             TextureSetFilterMipMap();
    static void                             TextureSetFilterLinear();
    static void                             TextureSetFilterNearest();
    
    //Uniforms...
    
    //When we BIND a uniform, we are assuming that the data on it
    //is finalized, we copy everything to the video card. Keep in mind
    //that we can only use ONE of these uniforms per render command.
    //
    //Think of this like "batched" information that pertains to one render command...
    //
    
    
    //static void                             FlushUniforms();
    static void                             UniformBind();
    static void                             UniformBind(FUniforms *pUniforms);
    
    
    
    //Textures...
    static int                              TextureGenerate(unsigned int *pData, int pWidth, int pHeight);
    static void                             TextureSetData(int pIndex, unsigned int *pData, int pWidth, int pHeight);
    static void                             TextureDelete(int pIndex);
    static void                             TextureBind(int pIndex);
    static void                             TextureBind(FTexture *pTexture);
    
    
    //Buffers...
    static int                              BufferArrayGenerate(int pLength);
    static void                             BufferArrayDelete(int pIndex);
    static void                             BufferArrayWrite(FBuffer *pBuffer, void *pData, int pLength);
    static void                             BufferArrayWrite(FBuffer *pBuffer, void *pData, int pOffset, int pLength);
    
    
    static int                              BufferElementGenerate(int pLength);
    static void                             BufferElementDelete(int pIndex);
    static void                             BufferElementWrite(FBuffer *pBuffer, void *pData, int pLength);
    static void                             BufferElementWrite(FBuffer *pBuffer, void *pData, int pOffset, int pLength);
    
    //
    //
    //
	static void                             DrawTriangle2D(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3);
    //
    //
    //
    //
    //
    static void                             ArrayBufferData(FBuffer *pBuffer);
    static void                             ArrayBufferData(FBuffer *pBuffer, int pOffset);
    //
    static void                             ArrayBufferPositions(FBuffer *pBuffer);
    static void                             ArrayBufferPositions(FBuffer *pBuffer, int pOffset);
    //
    static void                             ArrayBufferTextureCoords(FBuffer *pBuffer);
    static void                             ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset);
    //
    
    static void                             ArrayBufferColors(FBuffer *pBuffer);
    static void                             ArrayBufferColors(FBuffer *pBuffer, int pOffset);
    //
    static void                             ArrayBufferNormals(FBuffer *pBuffer);
    static void                             ArrayBufferNormals(FBuffer *pBuffer, int pOffset);
    //
    static void                             ArrayBufferTangents(FBuffer *pBuffer);
    static void                             ArrayBufferTangents(FBuffer *pBuffer, int pOffset);
    //
    //
    ///////////////////////////////////////
    //
    //
    
    static FBuffer                          *ArrayWriteData(void *pData, int pCount);
    
    
    //
    //
    ///////////////////////////////////////
    //
    //
    static void                             DrawTriangles(int pCount);
    static void                             DrawTriangleStrips(int pCount);
    
    static void                             DrawTrianglesIndexed(GFX_MODEL_INDEX_TYPE *pIndices, int pCount);
    
    
    static void                             DrawTrianglesIndexedWithPackedBuffers(FBuffer *pVertexBuffer,
                                                                                  int pVertexBufferOffset,
                                                                                  GFX_MODEL_INDEX_TYPE *pIndices,
                                                                                  int pCount,
                                                                                  FTexture *pTexture);
    
    
    
    static void                             DrawTriangleStripsIndexed(GFX_MODEL_INDEX_TYPE *pIndices, int pCount);
    
    static void                             DrawTriangles(int pCount, float *pPositions, float *pTextureCoords = 0, float *pNormals = 0);
    
    //Assumed - triangle list
    
    static void                             DrawModelEfficientSetup(float *pPositions, float *pTextureCoords, float *pNormals, FTexture *pTexture);
    
    
    static void                             DrawModelIndexedEfficientSetup(float *pPositions, float *pTextureCoords, float *pNormals, FTexture *pTexture);
    
    static void                             DrawModel(float *pPositions, float *pTextureCoords, float *pNormals, int pCount, FTexture *pTexture);
    
    static void                             DrawModelIndexed(float *pPositions, int pPositionsCount, float *pTextureCoords, int pTextureCoordsCount, float *pNormals, int pNormalsCount, GFX_MODEL_INDEX_TYPE *pIndex, int pCount, FTexture *pTexture);
    
    static void                             DrawModelIndexed(float *pPositions, int pPositionsCount, float *pTextureCoords, int pTextureCoordsCount, float *pNormals, int pNormalsCount, GFX_MODEL_INDEX_TYPE *pIndex, FTexture *pTexture, int pStartIndex, int pEndIndex);
    
    
    static void                             DrawSprite(float pX, float pY, float pScaleX, float pScaleY, float pScaleZ, float pRotation, float *pPositions, float *pTextureCoords, FTexture *pTexture);
    static void                             DrawSprite(float *pPositions, float *pTextureCoords, FTexture *pTexture);
    
    static bool                             DrawSpriteSetup(float *pPositions, float *pTextureCoords);
    
    
    
    
    static void                             DrawSpriteTriangle(float pX, float pY, float pScaleX, float pScaleY, float pScaleZ, float pRotation, float *pPositions, float *pTextureCoords, FTexture *pTexture);
    static void                             DrawSpriteTriangle(float *pPositions, float *pTextureCoords, FTexture *pTexture);
    static bool                             DrawSpriteTriangleSetup(float *pPositions, float *pTextureCoords);
    
    
    
    
    static void                             PipelineStateSetShape2DNoBlending();
    static void                             PipelineStateSetShape2DAlphaBlending();
    static void                             PipelineStateSetShape2DAdditiveBlending();
    
    static void                             PipelineStateSetShape3DNoBlending();
    static void                             PipelineStateSetShape3DAlphaBlending();
    static void                             PipelineStateSetShape3DAdditiveBlending();
    
    static void                             PipelineStateSetShapeNodeNoBlending();
    static void                             PipelineStateSetShapeNodeAlphaBlending();
    static void                             PipelineStateSetShapeNodeAdditiveBlending();
    
    static void                             PipelineStateSetSpriteNoBlending();
    static void                             PipelineStateSetSpriteAlphaBlending();
    static void                             PipelineStateSetSpriteAdditiveBlending();
    static void                             PipelineStateSetSpritePremultipliedBlending();
    static void                             PipelineStateSetSpriteWhiteBlending();
    
    static void                             PipelineStateSetSimpleModelNoBlending();
    static void                             PipelineStateSetSimpleModelAlphaBlending();
    
    static void                             PipelineStateSetSimpleModelIndexedNoBlending();
    static void                             PipelineStateSetSimpleModelIndexedAlphaBlending();
    
    static void                             PipelineStateSetModelIndexedNoBlending();
    static void                             PipelineStateSetModelIndexedAlphaBlending();
    
    static void                             PipelineStateSetModelIndexedLightedAmbientNoBlending();
    static void                             PipelineStateSetModelIndexedLightedAmbientAlphaBlending();
    
    static void                             PipelineStateSetModelIndexedLightedDiffuseNoBlending();
    static void                             PipelineStateSetModelIndexedLightedDiffuseAlphaBlending();
    
    static void                             PipelineStateSetModelIndexedLightedPhongNoBlending();
    static void                             PipelineStateSetModelIndexedLightedPhongAlphaBlending();
    
    static void                             PipelineStateSetModelIndexedLightedPhongOverlayNoBlending();
    static void                             PipelineStateSetModelIndexedLightedPhongOverlayAlphaBlending();
    
    static void                             PipelineStateSetModelIndexedLightedSimpleSpotlightNoBlending();
    static void                             PipelineStateSetModelIndexedLightedSimpleSpotlightAlphaBlending();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    static int                              RenderPass();
    
    static void                             RenderPassBegin(int pRenderPass, bool pClearColor, bool pClearDepth);
    
    
    

    static void                             SetShaderProgram(ShaderProgram *pShaderProgram);
    
    
    static void                             BlendEnable();
    static void                             BlendDisable();
    
    static void                             BlendSetAlpha();
    static void                             BlendSetAdditive();
    static void                             BlendSetPremultiplied();
    
    
};

#endif
