//
//  Shape3DShaders.metal
//  MacMetal
//
//  Created by Nicholas Raptis on 2/22/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "ShaderTypes.h"
#include <metal_stdlib>
using namespace metal;

typedef struct {
    float3 position [[attribute(ShapeVertexAttributePosition)]];
} Shape3DVertex;

typedef struct {
    float4 position [[position]];
} Shape3DColorInOut;

vertex Shape3DColorInOut shape_3d_vertex(Shape3DVertex verts [[stage_in]], constant BasicVertexUniforms & uniforms [[ buffer(ShapeBufferIndexUniforms) ]]) {
    Shape3DColorInOut out;
    float4 position = float4(verts.position, 1.0);
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    return out;
}

fragment float4 shape_3d_fragment(Shape3DColorInOut in [[stage_in]],
                               constant ModulateFragmentUniforms & uniforms [[ buffer(ShapeBufferIndexUniforms) ]]) {
    float4 result = float4(uniforms.r, uniforms.g, uniforms.b, uniforms.a);
    return result;
}
