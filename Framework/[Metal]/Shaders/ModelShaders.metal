//
//  ModelShaders.metal
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include <metal_stdlib>
#include <simd/simd.h>
#import "ShaderTypes.h"

using namespace metal;

typedef struct {
    float4 position [[position]];
    float3 textureCoord;
    float3 normal;
} ModelColorInOut;

typedef struct {
    float3 position [[attribute(SimpleModelVertexAttributePosition)]];
    float3 TextureCoord [[attribute(SimpleModelVertexAttributeTextureCoord)]];
    float3 normals [[attribute(SimpleModelVertexAttributeTextureCoord)]];
} ModelVertex;

typedef struct {
    packed_float3 position [[]];
    packed_float3 textureCoord [[]];
    packed_float3 normal [[]];
} PackedModelVertex;


vertex ModelColorInOut indexed_model_vertex(constant PackedModelVertex *verts [[buffer(0)]], ushort vid [[vertex_id]] ,constant BasicVertexUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]]) {
    ModelColorInOut out;
    float4 position = float4(verts[vid].position, 1.0);
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.textureCoord = verts[vid].textureCoord;
    out.normal = verts[vid].normal;
    return out;
}

fragment float4 indexed_model_fragment(ModelColorInOut in [[stage_in]],
                                       constant ModulateFragmentUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]],
                                       texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                       sampler colorSampler [[ sampler(0) ]]) {
    half4 colorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    float4 result = float4(colorSample.r * uniforms.r,
                           colorSample.g * uniforms.g,
                           colorSample.b * uniforms.b,
                           colorSample.a * uniforms.a);
    return result;
}

////////
////////
