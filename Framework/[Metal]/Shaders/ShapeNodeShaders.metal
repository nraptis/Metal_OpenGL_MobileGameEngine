//
//  ShapeNodeShaders.metal
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include <metal_stdlib>
#import "ShaderTypes.h"

using namespace metal;

typedef struct {
    float4 position [[position]];
    float3 textureCoord;// [[textureCoord]];
    float4 color;
} ShapeNodeColorInOut;

typedef struct {
    packed_float3 position [[]];
    packed_float3 textureCoord [[]];
    packed_float4 color [[]];
} PackedNodeVertex;

/*
vertex SpriteColorInOut sprite_vertex(SpriteVertex verts [[stage_in]], constant BasicVertexUniforms & uniforms [[ buffer(SpriteBufferIndexUniforms) ]]) {
    SpriteColorInOut out;
    float4 position = float4(verts.position, 0.0, 1.0);
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.textureCoord = verts.textureCoord;
    return out;
}
*/

vertex ShapeNodeColorInOut shape_node_vertex(constant PackedNodeVertex *verts [[buffer(0)]], ushort vid [[vertex_id]], constant BasicVertexUniforms & uniforms [[ buffer(NodePackedBufferIndexUniforms) ]]) {
    ShapeNodeColorInOut out;
    float4 position = float4(verts[vid].position, 1.0);
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.color = verts[vid].color;
    out.textureCoord = verts[vid].textureCoord;
    return out;
}

fragment float4 shape_node_fragment(ShapeNodeColorInOut in [[stage_in]],
                                    constant ModulateFragmentUniforms & uniforms [[ buffer(NodePackedBufferIndexUniforms) ]],
                                    texture2d<half> colorMap [[ texture(TextureIndexColor) ]]) {
    float4 result = float4(uniforms.r * in.color[0],
                           uniforms.g * in.color[1],
                           uniforms.b * in.color[2],
                           uniforms.a * in.color[3]);
    return float4(result);
}



fragment float4 shape_node_sprite_fragment(ShapeNodeColorInOut in [[stage_in]],
                                    constant ModulateFragmentUniforms & uniforms [[ buffer(NodePackedBufferIndexUniforms) ]],
                                    texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                    sampler colorSampler [[ sampler(0) ]]) {
    half4 colorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    float4 result = float4(colorSample.r * uniforms.r * in.color[0],
                           colorSample.g * uniforms.g * in.color[1],
                           colorSample.b * uniforms.b * in.color[2],
                           colorSample.a * uniforms.a * in.color[3]);
    return float4(result);
}

/*
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
*/


/*
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
*/
