//
//  SpriteShaders.metal
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
    float2 position [[attribute(SpriteVertexAttributePosition)]];
    float2 textureCoord [[attribute(SpriteVertexAttributeTextureCoord)]];
} SpriteVertex;

typedef struct {
    float4 position [[position]];
    float2 textureCoord;
} SpriteColorInOut;


vertex SpriteColorInOut sprite_vertex(SpriteVertex verts [[stage_in]], constant BasicVertexUniforms & uniforms [[ buffer(SpriteBufferIndexUniforms) ]]) {
    SpriteColorInOut out;
    float4 position = float4(verts.position, 0.0, 1.0);
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.textureCoord = verts.textureCoord;
    return out;
}

fragment float4 sprite_fragment(SpriteColorInOut in [[stage_in]],
                                constant ModulateFragmentUniforms & uniforms [[ buffer(SpriteBufferIndexUniforms) ]],
                                texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                sampler colorSampler [[ sampler(0) ]]) {
    half4 colorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    float4 result = float4(colorSample.r * uniforms.r,
                           colorSample.g * uniforms.g,
                           colorSample.b * uniforms.b,
                           colorSample.a * uniforms.a);
    return result;
}

fragment float4 sprite_fragment_white(SpriteColorInOut in [[stage_in]],
                                      constant ModulateFragmentUniforms & uniforms [[ buffer(SpriteBufferIndexUniforms) ]],
                                      texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                      sampler colorSampler [[ sampler(0) ]]) {
    half4 colorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    float4 result = float4(uniforms.r,
                           uniforms.g,
                           uniforms.b,
                           colorSample.a * uniforms.a);
    return result;
}


//
/////////////////////////
//

