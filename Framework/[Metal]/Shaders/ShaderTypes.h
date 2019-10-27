//
//  ShaderTypes.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/20/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef ShaderTypes_h
#define ShaderTypes_h

#ifdef __METAL_VERSION__
#define NS_ENUM(_type, _name) enum _name : _type _name; enum _name : _type
#define NSInteger metal::int32_t
#else
#import <Foundation/Foundation.h>
#endif

#include <simd/simd.h>

typedef NS_ENUM(NSInteger, TextureIndex) {
    TextureIndexColor = 0
};

typedef NS_ENUM(NSInteger, SamplerIndex) {
    SamplerIndexColor = 0
};


typedef NS_ENUM(NSInteger, Shape3DVertexAttribute) {
    Shape3DVertexAttributePosition  = 0
};
//
///////////////////////////////////
//
typedef NS_ENUM(NSInteger, SpriteBufferIndex) {
    SpriteBufferIndexMeshPositions = 0,
    SpriteBufferIndexMeshTextureCoords = 1,
    SpriteBufferIndexUniforms      = 2
};
//
typedef NS_ENUM(NSInteger, SpriteVertexAttribute) {
    SpriteVertexAttributePosition  = 0,
    SpriteVertexAttributeTextureCoord  = 1
};
//
///////////////////////////////////
//
typedef NS_ENUM(NSInteger, NodePackedBufferIndex) {
    NodePackedBufferIndexMeshData = 0,
    NodePackedBufferIndexUniforms = 1
};

typedef NS_ENUM(NSInteger, NodePackedVertexAttribute) {
    NodePackedVertexAttributeData  = 0
};
//
///////////////////////////////////
//
typedef NS_ENUM(NSInteger, ShapeBufferIndex) {
    ShapeBufferIndexMeshPositions = 0,
    ShapeBufferIndexUniforms      = 1
};

typedef NS_ENUM(NSInteger, ShapeVertexAttribute) {
    ShapeVertexAttributePosition  = 0,
    ShapeVertexAttributeTextureCoord  = 1
};
//
///////////////////////////////////
//
typedef NS_ENUM(NSInteger, SimpleModelBufferIndex) {
    SimpleModelBufferIndexMeshPositions = 0,
    SimpleModelBufferIndexMeshTextureCoords = 1,
    SimpleModelBufferIndexUniforms      = 2
};

typedef NS_ENUM(NSInteger, SimpleModelVertexAttribute) {
    SimpleModelVertexAttributePosition  = 0,
    SimpleModelVertexAttributeTextureCoord  = 1
};
//
///////////////////////////////////
//
typedef NS_ENUM(NSInteger, ModelPackedBufferIndex) {
    ModelPackedBufferIndexMeshData = 0,
    ModelPackedBufferIndexUniforms = 1
};

typedef NS_ENUM(NSInteger, ModelPackedVertexAttribute) {
    ModelPackedVertexAttributeData  = 0
};
//
///////////////////////////////////
//
typedef NS_ENUM(NSInteger, ModelBufferIndex) {
    ModelBufferIndexMeshPositions = 0,
    ModelBufferIndexMeshTextureCoords = 1,
    ModelBufferIndexMeshNormals = 2,
    ModelBufferIndexUniforms = 3
};

typedef NS_ENUM(NSInteger, ModelVertexAttribute) {
    ModelVertexAttributePosition  = 0,
    ModelVertexAttributeTextureCoord  = 1,
    ModelVertexAttributeNormal  = 2
};
//
///////////////////////////////////
//
typedef struct {
    matrix_float4x4 projectionMatrix;
    matrix_float4x4 modelViewMatrix;
} BasicVertexUniforms;
//
typedef struct {
    matrix_float4x4 projectionMatrix;
    matrix_float4x4 modelViewMatrix;
    matrix_float4x4 normalMatrix;
} DiffuseVertexUniforms;
//
typedef struct {
    float r;
    float g;
    float b;
    float a;
} ModulateFragmentUniforms;
//
///////////////////////////////////
//
typedef struct {
    float r;
    float g;
    float b;
    float a;
    //
    float lightR;
    float lightG;
    float lightB;
    //
    float lightAmbientIntensity;
} AmbientFragmentUniforms;
//
///////////////////////////////////
//
typedef struct {
    float r;
    float g;
    float b;
    float a;
    //
    float lightR;
    float lightG;
    float lightB;
    //
    float lightAmbientIntensity;
    float lightDiffuseIntensity;
    //
    float lightDirX;
    float lightDirY;
    float lightDirZ;
    //
} DiffuseFragmentUniforms;

/*
float mRed;
float mGreen;
float mBlue;

float mAmbientIntensity;
float mDiffuseIntensity;
float mSpecularIntensity;

float mDirX;
float mDirY;
float mDirZ;

float mEyeDirX;
float mEyeDirY;
float mEyeDirZ;

float mShininess;
*/

typedef struct {
    float r;
    float g;
    float b;
    float a;
    //
    float lightR;
    float lightG;
    float lightB;
    //
    float lightAmbientIntensity;
    float lightDiffuseIntensity;
    float lightSpecularIntensity;
    //
    float lightDirX;
    float lightDirY;
    float lightDirZ;
    //
    float lightShininess;
    
} PhongFragmentUniforms;

#endif
