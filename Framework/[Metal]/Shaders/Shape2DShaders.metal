//
//  ShapeShaders.metal
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/21/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include <metal_stdlib>
#import "ShaderTypes.h"

using namespace metal;

typedef struct {
    float2 position [[attribute(ShapeVertexAttributePosition)]];
} Shape2DVertex;

typedef struct {
    float4 position [[position]];
} Shape2DColorInOut;

vertex Shape2DColorInOut shape_2d_vertex(Shape2DVertex verts [[stage_in]], constant BasicVertexUniforms & uniforms [[ buffer(ShapeBufferIndexUniforms) ]]) {
    Shape2DColorInOut out;
    float4 position = float4(verts.position, 0.0, 1.0);
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    return out;
}

fragment float4 shape_2d_fragment(Shape2DColorInOut in [[stage_in]],
                               constant ModulateFragmentUniforms & uniforms [[ buffer(ShapeBufferIndexUniforms) ]]) {
    float4 result = float4(uniforms.r, uniforms.g, uniforms.b, uniforms.a);
    return result;
}
