//
//  Shaders.metal
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/18/19.
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
    float4 position [[position]];
    float3 textureCoord;
    float3 normal;
    float3 eye;
} PhongModelColorInOut;


typedef struct {
    packed_float3 position [[]];
    packed_float3 textureCoord [[]];
    packed_float3 normal [[]];
} PackedModelVertex;

vertex ModelColorInOut indexed_model_lighted_ambient_vertex(constant PackedModelVertex *verts [[buffer(0)]], ushort vid [[vertex_id]] ,constant BasicVertexUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]]) {
    ModelColorInOut out;
    float4 position = float4(verts[vid].position, 1.0);
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.textureCoord = verts[vid].textureCoord;
    out.normal = verts[vid].normal;
    return out;
}

fragment float4 indexed_model_lighted_ambient_fragment(ModelColorInOut in [[stage_in]],
                                       constant AmbientFragmentUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]],
                                       texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                       sampler colorSampler [[ sampler(0) ]]) {
    float ambient = uniforms.lightAmbientIntensity;
    half4 colorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    float4 result = float4(colorSample.r * uniforms.r * ambient * uniforms.lightR,
                           colorSample.g * uniforms.g * ambient * uniforms.lightG,
                           colorSample.b * uniforms.b * ambient * uniforms.lightB,
                           colorSample.a * uniforms.a);
    return result;
}

vertex ModelColorInOut indexed_model_lighted_diffuse_vertex(constant PackedModelVertex *verts [[buffer(0)]], ushort vid [[vertex_id]] ,constant DiffuseVertexUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]]) {
    
    ModelColorInOut out;
    
    float4 position = float4(verts[vid].position, 1.0);
    float4 normal = float4(verts[vid].normal, 1.0);
    
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.textureCoord = verts[vid].textureCoord;
    out.normal = float3(uniforms.normalMatrix * normal);
    
    return out;
}

fragment float4 indexed_model_lighted_diffuse_fragment(ModelColorInOut in [[stage_in]],
                                                       constant DiffuseFragmentUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]],
                                                       texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                                       sampler colorSampler [[ sampler(0) ]]) {
    float3 N = normalize(in.normal);
    float3 Direction = float3(-uniforms.lightDirX, -uniforms.lightDirY, -uniforms.lightDirZ);
    
    float DiffuseIntensity = max(dot(N, Direction), 0.0f) * uniforms.lightDiffuseIntensity;
    
    float AmbientIntensity = uniforms.lightAmbientIntensity;
    
    float LightIntensity = AmbientIntensity + DiffuseIntensity;
    
    half4 ColorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    
    float4 result = float4(ColorSample.r * uniforms.r * uniforms.lightR * LightIntensity,
                           ColorSample.g * uniforms.g * uniforms.lightG * LightIntensity,
                           ColorSample.b * uniforms.b * uniforms.lightB * LightIntensity,
                           ColorSample.a * uniforms.a);
    
    return result;
}

vertex PhongModelColorInOut indexed_model_lighted_phong_vertex(constant PackedModelVertex *verts [[buffer(0)]], ushort vid [[vertex_id]] ,constant DiffuseVertexUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]]) {
    //
    PhongModelColorInOut out;
    //
    float4 position = float4(verts[vid].position, 1.0);
    float4 normal = float4(verts[vid].normal, 1.0);
    //
    
    
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.textureCoord = verts[vid].textureCoord;
    out.normal = float3(uniforms.normalMatrix * normal);
    out.eye = float3(uniforms.normalMatrix * position);
    
    return out;
    //
}


fragment float4 indexed_model_lighted_phong_fragment(PhongModelColorInOut in [[stage_in]],
                                                     constant PhongFragmentUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]],
                                                     texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                                     sampler colorSampler [[ sampler(0) ]]) {
    float3 N = normalize(in.normal);
    float3 Direction = float3(-uniforms.lightDirX, -uniforms.lightDirY, -uniforms.lightDirZ);
    float3 E = normalize(in.eye);
    float3 R = normalize(-reflect(Direction, N));
    
    float AmbientIntensity = uniforms.lightAmbientIntensity;
    AmbientIntensity = clamp(AmbientIntensity, 0.0, 1.0);
    
    float DiffuseIntensity = max(dot(N, Direction), 0.0) * uniforms.lightDiffuseIntensity;
    DiffuseIntensity = clamp(DiffuseIntensity, 0.0, 1.0);
    
    float SpecularIntensity = pow(max(dot(R, E), 0.0), uniforms.lightShininess) * uniforms.lightSpecularIntensity;
    SpecularIntensity = clamp(SpecularIntensity, 0.0, 10.0);
    
    float LightIntensity = AmbientIntensity + DiffuseIntensity + SpecularIntensity;
    
    half4 ColorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    
    float4 result = float4(ColorSample.r * uniforms.r * uniforms.lightR * LightIntensity,
                           ColorSample.g * uniforms.g * uniforms.lightG * LightIntensity,
                           ColorSample.b * uniforms.b * uniforms.lightB * LightIntensity,
                           ColorSample.a * uniforms.a);
    
    return result;
}



vertex PhongModelColorInOut indexed_model_lighted_phong_overlay_vertex(constant PackedModelVertex *verts [[buffer(0)]], ushort vid [[vertex_id]] ,constant DiffuseVertexUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]]) {
    //
    PhongModelColorInOut out;
    //
    float4 position = float4(verts[vid].position, 1.0);
    float4 normal = float4(verts[vid].normal, 1.0);
    //
    
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.textureCoord = verts[vid].textureCoord;
    out.normal = float3(uniforms.normalMatrix * normal);
    out.eye = float3(uniforms.normalMatrix * position);
    
    return out;
    //
}


fragment float4 indexed_model_lighted_phong_overlay_fragment(PhongModelColorInOut in [[stage_in]],
                                                     constant PhongFragmentUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]],
                                                     texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                                     sampler colorSampler [[ sampler(0) ]]) {
    float3 N = normalize(in.normal);
    float3 Direction = float3(-uniforms.lightDirX, -uniforms.lightDirY, -uniforms.lightDirZ);
    float3 E = normalize(in.eye);
    float3 R = normalize(-reflect(Direction, N));
    
    float AmbientIntensity = uniforms.lightAmbientIntensity;
    AmbientIntensity = clamp(AmbientIntensity, 0.0, 1.0);
    
    float DiffuseIntensity = max(dot(N, Direction), 0.0) * uniforms.lightDiffuseIntensity;
    DiffuseIntensity = clamp(DiffuseIntensity, 0.0, 1.0);
    
    float SpecularIntensity = pow(max(dot(R, E), 0.0), uniforms.lightShininess) * uniforms.lightSpecularIntensity;
    SpecularIntensity = clamp(SpecularIntensity, 0.0, 10.0);
    
    float LightIntensity = AmbientIntensity + DiffuseIntensity;
    
    half4 ColorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    
    float4 result = float4(ColorSample.r * uniforms.r * uniforms.lightR * LightIntensity + SpecularIntensity,
                           ColorSample.g * uniforms.g * uniforms.lightG * LightIntensity + SpecularIntensity,
                           ColorSample.b * uniforms.b * uniforms.lightB * LightIntensity + SpecularIntensity,
                           ColorSample.a * uniforms.a);
    
    return result;
}


/*
float4 eye_light_direction = uniforms.sun_eye_direction;

float3 eye_space_fragment_pos = normalize(in.eye_position) * in.position.z;

half3 halfway_vector = half3(normalize(eye_space_fragment_pos - eye_light_direction.xyz));

half specular_intensity = half(uniforms.sun_specular_intensity);

half specular_shininess = specular_contrib * half(uniforms.shininess_factor);

half specular_factor = powr( max( dot(eye_normal,halfway_vector), 0.h), specular_intensity);

half4 specular_contribution = (specular_factor *
                               base_color_sample *
                               specular_shininess *
                               direction_light_color);
*/




/*
 // 3
 fragment float4 basic_fragment(VertexOut interpolated [[stage_in]],
 const device Uniforms&  uniforms    [[ buffer(1) ]],
 texture2d<float>  tex2D     [[ texture(0) ]],
 sampler           sampler2D [[ sampler(0) ]]) {
 
 // Ambient
 Light light = uniforms.light;
 float4 ambientColor = float4(light.color * light.ambientIntensity, 1);
 
 //Diffuse
 float diffuseFactor = max(0.0,dot(interpolated.normal, float3(light.direction))); // 1
 float4 diffuseColor = float4(light.color * light.diffuseIntensity * diffuseFactor ,1.0); // 2
 
 //Specular
 float3 eye = normalize(interpolated.fragmentPosition); //1
 float3 reflection = reflect(float3(light.direction), interpolated.normal); // 2
 float specularFactor = pow(max(0.0, dot(reflection, eye)), light.shininess); //3
 float4 specularColor = float4(light.color * light.specularIntensity * specularFactor ,1.0);//4
 
 light.specularIntensity
 light.shininess
 
 float4 color = tex2D.sample(sampler2D, interpolated.texCoord);
 return color * (ambientColor + diffuseColor + specularColor);
 }
 */



/*
fragment float4 indexed_model_lighted_diffuse_fragment(ModelColorInOut in [[stage_in]],
                                                               constant DiffuseFragmentUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]],
                                                               texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                                               sampler colorSampler [[ sampler(0) ]]) {
    
    float3 diffuseDir = float3(uniforms.diffuseDirX, uniforms.diffuseDirY, uniforms.diffuseDirZ);
    
    float diffuseFactor = max(0.0f, dot(in.normal, diffuseDir));
    //
    
    float3 ambientColor = float3(uniforms.ambientIntensity * uniforms.ambientR,
                                 uniforms.ambientIntensity * uniforms.ambientG,
                                 uniforms.ambientIntensity * uniforms.ambientB);
    //
    float3 diffuseColor = float3(uniforms.diffuseIntensity * uniforms.diffuseR * diffuseFactor,
                                 uniforms.diffuseIntensity * uniforms.diffuseG * diffuseFactor,
                                 uniforms.diffuseIntensity * uniforms.diffuseB * diffuseFactor);
    //
    float3 lightColor = float3(ambientColor[0] + diffuseColor[0],
                               ambientColor[1] + diffuseColor[1],
                               ambientColor[2] + diffuseColor[2]);
    
    half4 colorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    float4 result = float4(colorSample.r * uniforms.r * lightColor[0],
                           colorSample.g * uniforms.g * lightColor[1],
                           colorSample.b * uniforms.b * lightColor[2],
                           colorSample.a * uniforms.a);
    return result;
}

fragment float4 indexed_model_lighted_phong_fragment(ModelColorInOut in [[stage_in]],
                                                     constant PhongFragmentUniforms & uniforms [[ buffer(ModelPackedBufferIndexUniforms) ]],
                                                     texture2d<half> colorMap [[ texture(TextureIndexColor) ]],
                                                     sampler colorSampler [[ sampler(0) ]]) {
    
    float3 eyeDir = float3(uniforms.lightEyeDirX, uniforms.lightEyeDirY, uniforms.lightEyeDirZ); //1
    float3 lightDir = float3(uniforms.lightDirX, uniforms.lightDirY, uniforms.lightDirZ);
    float3 reflection = reflect(lightDir, in.normal); // 2
    
    float diffuseFactor = max(0.0f, dot(in.normal, lightDir));
    float specularFactor = pow(max(0.0, dot(reflection, eyeDir)), uniforms.lightShininess); //3
    //
    
    float3 ambientColor = float3(uniforms.lightAmbientIntensity,
                                 uniforms.lightAmbientIntensity,
                                 uniforms.lightAmbientIntensity);
    //
    float3 diffuseColor = float3(uniforms.lightDiffuseIntensity * diffuseFactor,
                                 uniforms.lightDiffuseIntensity * diffuseFactor,
                                 uniforms.lightDiffuseIntensity * diffuseFactor);
    
    float3 specularColor = float3(uniforms.lightSpecularIntensity * specularFactor,
                                  uniforms.lightSpecularIntensity * specularFactor,
                                  uniforms.lightSpecularIntensity * specularFactor);
    
    float3 lightColor = float3((ambientColor[0] + diffuseColor[0] + specularColor[0]) * uniforms.lightR,
                               (ambientColor[1] + diffuseColor[1] + specularColor[1]) * uniforms.lightG,
                               (ambientColor[2] + diffuseColor[2] + specularColor[2]) * uniforms.lightB);
    
    half4 colorSample = colorMap.sample(colorSampler, in.textureCoord.xy);
    //float4 result = float4(colorSample.r * uniforms.r * lightColor[0],
    //colorSample.g * uniforms.g * lightColor[1],
    //colorSample.b * uniforms.b * lightColor[2],
    //colorSample.a * uniforms.a);
    float4 result = float4(colorSample.r * uniforms.r * lightColor[0],
                           colorSample.g * uniforms.g * lightColor[1],
                           colorSample.b * uniforms.b * lightColor[2],
                           colorSample.a);
    
    
    return result;
}
*/
