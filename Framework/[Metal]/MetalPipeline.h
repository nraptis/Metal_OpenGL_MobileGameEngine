//
//  MetalPipeline.h
//  MacMetal
//
//  Created by Nicholas Raptis on 2/19/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "MetalEngine.h"


NS_ASSUME_NONNULL_BEGIN

@interface MetalPipeline : NSObject

@property (nonatomic, assign) int screenScale;
@property (nonatomic, assign) int renderPass;


@property (nonatomic, strong) id <MTLFunction> shape2DVertexProgram;
@property (nonatomic, strong) id <MTLFunction> shape2DFragmentProgram;
@property (nonatomic, strong) id <MTLFunction> shape3DVertexProgram;
@property (nonatomic, strong) id <MTLFunction> shape3DFragmentProgram;

@property (nonatomic, strong) id <MTLFunction> shapeNodeVertexProgram;
@property (nonatomic, strong) id <MTLFunction> shapeNodeFragmentProgram;

@property (nonatomic, strong) id <MTLFunction> shapeNodeSpriteFragmentProgram;

@property (nonatomic, strong) id <MTLFunction> spriteVertexProgram;
@property (nonatomic, strong) id <MTLFunction> spriteFragmentProgram;
@property (nonatomic, strong) id <MTLFunction> spriteFragmentProgramWhite;
@property (nonatomic, strong) id <MTLFunction> simpleModelVertexProgram;
@property (nonatomic, strong) id <MTLFunction> simpleModelFragmentProgram;
@property (nonatomic, strong) id <MTLFunction> simpleModelIndexedVertexProgram;
@property (nonatomic, strong) id <MTLFunction> simpleModelIndexedFragmentProgram;
@property (nonatomic, strong) id <MTLFunction> modelIndexedVertexProgram;
@property (nonatomic, strong) id <MTLFunction> modelIndexedFragmentProgram;
@property (nonatomic, strong) id <MTLFunction> modelIndexedAmbientVertexProgram;
@property (nonatomic, strong) id <MTLFunction> modelIndexedAmbientFragmentProgram;
@property (nonatomic, strong) id <MTLFunction> modelIndexedDiffuseVertexProgram;
@property (nonatomic, strong) id <MTLFunction> modelIndexedDiffuseFragmentProgram;
@property (nonatomic, strong) id <MTLFunction> modelIndexedPhongVertexProgram;
@property (nonatomic, strong) id <MTLFunction> modelIndexedPhongFragmentProgram;
@property (nonatomic, strong) id <MTLFunction> modelIndexedPhongOverlayVertexProgram;
@property (nonatomic, strong) id <MTLFunction> modelIndexedPhongOverlayFragmentProgram;


- (void)setup;

- (void)setRenderPass: (int)renderPass;

- (void)prerender;
- (void)postrender;

- (void)pipelineStateSetShape2DNoBlending;
- (void)pipelineStateSetShape2DAlphaBlending;
- (void)pipelineStateSetShape2DAdditiveBlending;

- (void)pipelineStateSetShape3DNoBlending;
- (void)pipelineStateSetShape3DAlphaBlending;
- (void)pipelineStateSetShape3DAdditiveBlending;

- (void)pipelineStateSetShapeNodeNoBlending;
- (void)pipelineStateSetShapeNodeAlphaBlending;
- (void)pipelineStateSetShapeNodeAdditiveBlending;


- (void)pipelineStateSetShapeNodeSpriteNoBlending;
- (void)pipelineStateSetShapeNodeSpriteAlphaBlending;
- (void)pipelineStateSetShapeNodeSpriteAdditiveBlending;
- (void)pipelineStateSetShapeNodeSpritePremultipliedBlending;

- (void)pipelineStateSetSpriteNoBlending;
- (void)pipelineStateSetSpriteAlphaBlending;
- (void)pipelineStateSetSpriteAdditiveBlending;
- (void)pipelineStateSetSpritePremultipliedBlending;
- (void)pipelineStateSetSpriteWhiteBlending;

- (void)pipelineStateSetSimpleModelNoBlending;
- (void)pipelineStateSetSimpleModelAlphaBlending;
- (void)pipelineStateSetSimpleModelPremultipliedBlending;
- (void)pipelineStateSetSimpleModelAdditiveBlending;

- (void)pipelineStateSetSimpleModelIndexedNoBlending;
- (void)pipelineStateSetSimpleModelIndexedAlphaBlending;

- (void)pipelineStateSetModelIndexedNoBlending;
- (void)pipelineStateSetModelIndexedAlphaBlending;

- (void)pipelineStateSetModelIndexedLightedAmbientNoBlending;
- (void)pipelineStateSetModelIndexedLightedAmbientAlphaBlending;

- (void)pipelineStateSetModelIndexedLightedDiffuseNoBlending;
- (void)pipelineStateSetModelIndexedLightedDiffuseAlphaBlending;

- (void)pipelineStateSetModelIndexedLightedPhongNoBlending;
- (void)pipelineStateSetModelIndexedLightedPhongAlphaBlending;

- (void)pipelineStateSetModelIndexedLightedPhongOverlayNoBlending;
- (void)pipelineStateSetModelIndexedLightedPhongOverlayAlphaBlending;

@end

NS_ASSUME_NONNULL_END
