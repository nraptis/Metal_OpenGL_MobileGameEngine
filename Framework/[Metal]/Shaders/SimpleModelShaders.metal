//
//  SimpleModelShaders.metal
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
} SimpleModelColorInOut;

typedef struct {
    float3 position [[attribute(SimpleModelVertexAttributePosition)]];
    float3 textureCoord [[attribute(SimpleModelVertexAttributeTextureCoord)]];
} SimpleModelVertex;

typedef struct {
    packed_float3 position [[]];
    packed_float3 textureCoord [[]];
} PackedSimpleModelVertex;

vertex SimpleModelColorInOut simple_model_vertex(SimpleModelVertex verts [[stage_in]], constant BasicVertexUniforms & uniforms [[ buffer(SimpleModelBufferIndexUniforms) ]]) {
    SimpleModelColorInOut out;
    float4 position = float4(verts.position, 1.0);
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.textureCoord = verts.textureCoord;
    return out;
}

fragment float4 simple_model_fragment(SimpleModelColorInOut in [[stage_in]],
                                      constant ModulateFragmentUniforms & uniforms [[ buffer(SimpleModelBufferIndexUniforms) ]],
                                      texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                      sampler colorSampler [[ sampler(0) ]]) {
    half4 colorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    float4 result = float4(colorSample.r * uniforms.r,
                           colorSample.g * uniforms.g,
                           colorSample.b * uniforms.b,
                           colorSample.a * uniforms.a);
    return result;
}
//
/////////////////////////
//
vertex SimpleModelColorInOut simple_indexed_model_vertex(constant PackedSimpleModelVertex *verts [[buffer(0)]], ushort vid [[vertex_id]] ,constant BasicVertexUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]]) {
    SimpleModelColorInOut out;
    float4 position = float4(verts[vid].position, 1.0);
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.textureCoord = verts[vid].textureCoord;
    return out;
}

fragment float4 simple_indexed_model_fragment(SimpleModelColorInOut in [[stage_in]],
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

