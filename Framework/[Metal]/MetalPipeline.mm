//
//  MetalPipeline.m
//  MacMetal
//
//  Created by Nicholas Raptis on 2/19/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "MetalPipeline.h"
#import "MetalViewController.h"
#include "os_core_graphics.h"

@interface MetalPipeline() {
    
    //int
    id <MTLRenderPipelineState> pipelineStateShape2DNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateShape2DAlphaBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateShape2DAdditiveBlending[GFX_RENDER_PASS_COUNT];
    
    id <MTLRenderPipelineState> pipelineStateShape3DNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateShape3DAlphaBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateShape3DAdditiveBlending[GFX_RENDER_PASS_COUNT];
    
    id <MTLRenderPipelineState> pipelineStateShapeNodeNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateShapeNodeAlphaBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateShapeNodeAdditiveBlending[GFX_RENDER_PASS_COUNT];
    
    id <MTLRenderPipelineState> pipelineStateSpriteNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateSpriteAlphaBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateSpriteAdditiveBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateSpritePremultipliedBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateSpriteWhiteBlending[GFX_RENDER_PASS_COUNT];
    
    id <MTLRenderPipelineState> pipelineStateSimpleModelNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateSimpleModelAlphaBlending[GFX_RENDER_PASS_COUNT];
    
    id <MTLRenderPipelineState> pipelineStateSimpleModelIndexedNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateSimpleModelIndexedAlphaBlending[GFX_RENDER_PASS_COUNT];
    
    id <MTLRenderPipelineState> pipelineStateModelIndexedNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateModelIndexedAlphaBlending[GFX_RENDER_PASS_COUNT];
    
    id <MTLRenderPipelineState> pipelineStateModelIndexedLightedAmbientNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateModelIndexedLightedAmbientAlphaBlending[GFX_RENDER_PASS_COUNT];
    
    id <MTLRenderPipelineState> pipelineStateModelIndexedLightedDiffuseNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateModelIndexedLightedDiffuseAlphaBlending[GFX_RENDER_PASS_COUNT];
    
    id <MTLRenderPipelineState> pipelineStateModelIndexedLightedPhongNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateModelIndexedLightedPhongAlphaBlending[GFX_RENDER_PASS_COUNT];
    
    id <MTLRenderPipelineState> pipelineStateModelIndexedLightedPhongOverlayNoBlending[GFX_RENDER_PASS_COUNT];
    id <MTLRenderPipelineState> pipelineStateModelIndexedLightedPhongOverlayAlphaBlending[GFX_RENDER_PASS_COUNT];
    
    
}

@end




@implementation MetalPipeline




- (void)setup {
    
    id <MTLLibrary> aLibrary = gMetalEngine.defaultLibrary;
    
    _shape2DVertexProgram = [aLibrary newFunctionWithName:@"shape_2d_vertex"];
    _shape2DFragmentProgram = [aLibrary newFunctionWithName:@"shape_2d_fragment"];
    
    _shape3DVertexProgram = [aLibrary newFunctionWithName:@"shape_3d_vertex"];
    _shape3DFragmentProgram = [aLibrary newFunctionWithName:@"shape_3d_fragment"];
    
    _shapeNodeVertexProgram = [aLibrary newFunctionWithName:@"shape_node_vertex"];
    _shapeNodeFragmentProgram = [aLibrary newFunctionWithName:@"shape_node_fragment"];
    _spriteVertexProgram = [aLibrary newFunctionWithName:@"sprite_vertex"];
    _spriteFragmentProgram = [aLibrary newFunctionWithName:@"sprite_fragment"];
    _spriteFragmentProgramWhite = [aLibrary newFunctionWithName:@"sprite_fragment_white"];
    _simpleModelVertexProgram = [aLibrary newFunctionWithName:@"simple_model_vertex"];
    _simpleModelFragmentProgram = [aLibrary newFunctionWithName:@"simple_model_fragment"];
    _simpleModelIndexedVertexProgram = [aLibrary newFunctionWithName:@"simple_indexed_model_vertex"];
    _simpleModelIndexedFragmentProgram = [aLibrary newFunctionWithName:@"simple_indexed_model_fragment"];
    _modelIndexedVertexProgram = [aLibrary newFunctionWithName:@"indexed_model_vertex"];
    _modelIndexedFragmentProgram = [aLibrary newFunctionWithName:@"indexed_model_fragment"];
    _modelIndexedAmbientVertexProgram = [aLibrary newFunctionWithName:@"indexed_model_lighted_ambient_vertex"];
    _modelIndexedAmbientFragmentProgram = [aLibrary newFunctionWithName:@"indexed_model_lighted_ambient_fragment"];
    _modelIndexedDiffuseVertexProgram = [aLibrary newFunctionWithName:@"indexed_model_lighted_diffuse_vertex"];
    _modelIndexedDiffuseFragmentProgram = [aLibrary newFunctionWithName:@"indexed_model_lighted_diffuse_fragment"];
    _modelIndexedPhongVertexProgram = [aLibrary newFunctionWithName:@"indexed_model_lighted_phong_vertex"];
    _modelIndexedPhongFragmentProgram = [aLibrary newFunctionWithName:@"indexed_model_lighted_phong_fragment"];
    
    _modelIndexedPhongOverlayVertexProgram = [aLibrary newFunctionWithName:@"indexed_model_lighted_phong_overlay_vertex"];
    _modelIndexedPhongOverlayFragmentProgram = [aLibrary newFunctionWithName:@"indexed_model_lighted_phong_overlay_fragment"];

    
    
    
    [self buildPipelineStatesShape2D: GFX_RENDER_PASS_2D_MAIN];
    
    [self buildPipelineStatesShape3D: GFX_RENDER_PASS_3D_MAIN];
    
    [self buildPipelineStatesSprite: GFX_RENDER_PASS_2D_MAIN];
    
    [self buildPipelineStatesSimpleModel: GFX_RENDER_PASS_3D_MAIN];
    
    [self buildPipelineStatesSimpleModelIndexed: GFX_RENDER_PASS_3D_MAIN];
    
    [self buildPipelineStatesModelIndexed: GFX_RENDER_PASS_3D_MAIN];
    
    [self buildPipelineStatesModelIndexedLightedAmbient: GFX_RENDER_PASS_3D_MAIN];
    
    [self buildPipelineStatesModelIndexedLightedDiffuse: GFX_RENDER_PASS_3D_MAIN];
    
    [self buildPipelineStatesModelIndexedLightedPhong: GFX_RENDER_PASS_3D_MAIN];
    
    [self buildPipelineStatesModelIndexedLightedPhongOverlay: GFX_RENDER_PASS_3D_MAIN];
    
    [self buildPipelineStatesShapeNode: GFX_RENDER_PASS_3D_MAIN];
    [self buildPipelineStatesShapeNode: GFX_RENDER_PASS_2D_MAIN];
    
}

- (void)setRenderPass: (int)renderPass {
    _renderPass = renderPass;
    
}

- (void)prerender {
    _renderPass = -1;
    
}

- (void)postrender {
    
}

- (void)pipelineStateSetShape2DNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateShape2DNoBlending[_renderPass]];
}

- (void)pipelineStateSetShape2DAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateShape2DAlphaBlending[_renderPass]];
}

- (void)pipelineStateSetShape2DAdditiveBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateShape2DAdditiveBlending[_renderPass]];
}

- (void)pipelineStateSetShape3DNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateShape3DNoBlending[_renderPass]];
}

- (void)pipelineStateSetShape3DAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateShape3DAlphaBlending[_renderPass]];
}

- (void)pipelineStateSetShape3DAdditiveBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateShape3DAdditiveBlending[_renderPass]];
}

- (void)pipelineStateSetShapeNodeNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateShapeNodeNoBlending[_renderPass]];
}

- (void)pipelineStateSetShapeNodeAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateShapeNodeAlphaBlending[_renderPass]];
}

- (void)pipelineStateSetShapeNodeAdditiveBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateShapeNodeAdditiveBlending[_renderPass]];
}

- (void)pipelineStateSetSpriteNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateSpriteNoBlending[_renderPass]];
}

- (void)pipelineStateSetSpriteAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateSpriteAlphaBlending[_renderPass]];
}

- (void)pipelineStateSetSpriteAdditiveBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateSpriteAdditiveBlending[_renderPass]];
}

- (void)pipelineStateSetSpritePremultipliedBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateSpritePremultipliedBlending[_renderPass]];
}

- (void)pipelineStateSetSpriteWhiteBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateSpriteWhiteBlending[_renderPass]];
}

- (void)pipelineStateSetSimpleModelNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateSimpleModelNoBlending[_renderPass]];
}

- (void)pipelineStateSetSimpleModelAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateSimpleModelAlphaBlending[_renderPass]];
}

- (void)pipelineStateSetSimpleModelIndexedNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateSimpleModelIndexedNoBlending[_renderPass]];
}

- (void)pipelineStateSetSimpleModelIndexedAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateSimpleModelIndexedAlphaBlending[_renderPass]];
}

- (void)pipelineStateSetModelIndexedNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateModelIndexedNoBlending[_renderPass]];
}

- (void)pipelineStateSetModelIndexedAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateModelIndexedAlphaBlending[_renderPass]];
}

- (void)pipelineStateSetModelIndexedLightedAmbientNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateModelIndexedLightedAmbientNoBlending[_renderPass]];
}

- (void)pipelineStateSetModelIndexedLightedAmbientAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateModelIndexedLightedAmbientAlphaBlending[_renderPass]];
}

- (void)pipelineStateSetModelIndexedLightedDiffuseNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateModelIndexedLightedDiffuseNoBlending[_renderPass]];
}

- (void)pipelineStateSetModelIndexedLightedDiffuseAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateModelIndexedLightedDiffuseAlphaBlending[_renderPass]];
}

- (void)pipelineStateSetModelIndexedLightedPhongNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateModelIndexedLightedPhongNoBlending[_renderPass]];
}

- (void)pipelineStateSetModelIndexedLightedPhongAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateModelIndexedLightedPhongAlphaBlending[_renderPass]];
}

- (void)pipelineStateSetModelIndexedLightedPhongOverlayNoBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateModelIndexedLightedPhongOverlayNoBlending[_renderPass]];
}

- (void)pipelineStateSetModelIndexedLightedPhongOverlayAlphaBlending {
    [gMetalEngine.renderCommandEncoder setRenderPipelineState: pipelineStateModelIndexedLightedPhongOverlayAlphaBlending[_renderPass]];
}



- (void)buildPipelineStatesShape2D: (int)pRenderPass {
    int aSampleCount = 4;
    if (pRenderPass != GFX_RENDER_PASS_2D_MAIN) {
        aSampleCount = 1;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLVertexDescriptor *aShapeVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    //
    aShapeVertexDescriptor.attributes[ShapeVertexAttributePosition].format = MTLVertexFormatFloat2;
    aShapeVertexDescriptor.attributes[ShapeVertexAttributePosition].offset = 0;
    aShapeVertexDescriptor.attributes[ShapeVertexAttributePosition].bufferIndex = ShapeBufferIndexMeshPositions;
    //
    aShapeVertexDescriptor.layouts[ShapeBufferIndexMeshPositions].stride = sizeof(float) * 2;
    aShapeVertexDescriptor.layouts[ShapeBufferIndexMeshPositions].stepRate = 1;
    aShapeVertexDescriptor.layouts[ShapeBufferIndexMeshPositions].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    aPipelineDescriptor.label = @"Shape 2D State, No Blending";
    aPipelineDescriptor.sampleCount = aSampleCount;
    aPipelineDescriptor.vertexDescriptor = aShapeVertexDescriptor;
    aPipelineDescriptor.vertexFunction = _shape2DVertexProgram;
    aPipelineDescriptor.fragmentFunction = _shape2DFragmentProgram;
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    
    if (pRenderPass != GFX_RENDER_PASS_2D_MAIN) {
        //If we are not on the SPRITE render pass, then
        //we are illegal to have the stencil pixel format.
        aPipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
        aPipelineDescriptor.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    }
    //
    NSError *pipelineError01 = NULL;
    pipelineStateShape2DNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Shape 2D State, Alpha Blending";
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    //
    NSError *pipelineError02 = NULL;
    pipelineStateShape2DAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Shape 2D State, Additive Blending";
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOne;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOne;
    //
    NSError *pipelineError03 = NULL;
    pipelineStateShape2DAdditiveBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError03];
    if (pipelineError03 != NULL) {
        NSLog(@"Pipeline State Error 03: %@", pipelineError03.description);
        return;
    }
}


- (void)buildPipelineStatesShape3D: (int)pRenderPass {
    int aSampleCount = 4;
    if (pRenderPass != GFX_RENDER_PASS_2D_MAIN) {
        aSampleCount = 1;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLVertexDescriptor *aShapeVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    //
    aShapeVertexDescriptor.attributes[ShapeVertexAttributePosition].format = MTLVertexFormatFloat3;
    aShapeVertexDescriptor.attributes[ShapeVertexAttributePosition].offset = 0;
    aShapeVertexDescriptor.attributes[ShapeVertexAttributePosition].bufferIndex = ShapeBufferIndexMeshPositions;
    //
    aShapeVertexDescriptor.layouts[ShapeBufferIndexMeshPositions].stride = sizeof(float) * 3;
    aShapeVertexDescriptor.layouts[ShapeBufferIndexMeshPositions].stepRate = 1;
    aShapeVertexDescriptor.layouts[ShapeBufferIndexMeshPositions].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    aPipelineDescriptor.label = @"Shape 3D State, No Blending";
    aPipelineDescriptor.sampleCount = aSampleCount;
    aPipelineDescriptor.vertexDescriptor = aShapeVertexDescriptor;
    aPipelineDescriptor.vertexFunction = _shape3DVertexProgram;
    aPipelineDescriptor.fragmentFunction = _shape3DFragmentProgram;
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    
    if (pRenderPass != GFX_RENDER_PASS_2D_MAIN) {
        aPipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
        aPipelineDescriptor.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    }
    
    //
    NSError *pipelineError01 = NULL;
    pipelineStateShape3DNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Shape 3D State, Alpha Blending";
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    //
    NSError *pipelineError02 = NULL;
    pipelineStateShape3DAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Shape 3D State, Additive Blending";
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOne;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOne;
    //
    NSError *pipelineError03 = NULL;
    pipelineStateShape3DAdditiveBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError03];
    if (pipelineError03 != NULL) {
        NSLog(@"Pipeline State Error 03: %@", pipelineError03.description);
        return;
    }
}

- (void)buildPipelineStatesShapeNode: (int)pRenderPass {
    
    int aSampleCount = 4;
    if (pRenderPass != GFX_RENDER_PASS_2D_MAIN) {
        aSampleCount = 1;
    }
    
    MTLVertexDescriptor *aShapeVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    //
    aShapeVertexDescriptor.attributes[NodePackedVertexAttributeData].format = MTLVertexFormatFloat3;
    aShapeVertexDescriptor.attributes[NodePackedVertexAttributeData].offset = 0;
    aShapeVertexDescriptor.attributes[NodePackedVertexAttributeData].bufferIndex = NodePackedBufferIndexMeshData;
    //
    aShapeVertexDescriptor.layouts[NodePackedBufferIndexMeshData].stride = sizeof(float) * (3 + 3 + 4);
    aShapeVertexDescriptor.layouts[NodePackedBufferIndexMeshData].stepRate = 1;
    aShapeVertexDescriptor.layouts[NodePackedBufferIndexMeshData].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    aPipelineDescriptor.label = @"Shape Node State, No Blending";
    aPipelineDescriptor.sampleCount = aSampleCount;
    aPipelineDescriptor.vertexDescriptor = aShapeVertexDescriptor;
    aPipelineDescriptor.vertexFunction = _shapeNodeVertexProgram;
    aPipelineDescriptor.fragmentFunction = _shapeNodeFragmentProgram;
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    if (pRenderPass != GFX_RENDER_PASS_2D_MAIN) {
        //If we are not on the SPRITE render pass, then
        //we are illegal to have the stencil pixel format.
        aPipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
        aPipelineDescriptor.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    }
    //
    NSError *pipelineError01 = NULL;
    pipelineStateShapeNodeNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Shape Node State, Alpha Blending";
    
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    NSError *pipelineError02 = NULL;
    pipelineStateShapeNodeAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Shape Node State, Additive Blending";
    
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOne;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOne;
    //
    NSError *pipelineError03 = NULL;
    pipelineStateShapeNodeAdditiveBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError03];
    if (pipelineError03 != NULL) {
        NSLog(@"Pipeline State Error 03: %@", pipelineError03.description);
        return;
    }
}

- (void)buildPipelineStatesSprite: (int)pRenderPass {
    int aSampleCount = 4;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLVertexDescriptor *aSpriteVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    
    aSpriteVertexDescriptor.attributes[SpriteVertexAttributePosition].format = MTLVertexFormatFloat2;
    aSpriteVertexDescriptor.attributes[SpriteVertexAttributePosition].offset = 0;
    aSpriteVertexDescriptor.attributes[SpriteVertexAttributePosition].bufferIndex = SpriteBufferIndexMeshPositions;
    
    aSpriteVertexDescriptor.attributes[SpriteVertexAttributeTextureCoord].format = MTLVertexFormatFloat2;
    aSpriteVertexDescriptor.attributes[SpriteVertexAttributeTextureCoord].offset = 0;
    aSpriteVertexDescriptor.attributes[SpriteVertexAttributeTextureCoord].bufferIndex = SpriteBufferIndexMeshTextureCoords;
    
    aSpriteVertexDescriptor.layouts[SpriteBufferIndexMeshPositions].stride = sizeof(float) * 2;
    aSpriteVertexDescriptor.layouts[SpriteBufferIndexMeshPositions].stepRate = 1;
    aSpriteVertexDescriptor.layouts[SpriteBufferIndexMeshPositions].stepFunction = MTLVertexStepFunctionPerVertex;
    
    aSpriteVertexDescriptor.layouts[SpriteBufferIndexMeshTextureCoords].stride = sizeof(float) * 2;
    aSpriteVertexDescriptor.layouts[SpriteBufferIndexMeshTextureCoords].stepRate = 1;
    aSpriteVertexDescriptor.layouts[SpriteBufferIndexMeshTextureCoords].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    aPipelineDescriptor.label = @"Sprite State, No Blending";
    aPipelineDescriptor.sampleCount = aSampleCount;
    aPipelineDescriptor.vertexFunction = _spriteVertexProgram;
    aPipelineDescriptor.fragmentFunction = _spriteFragmentProgram;
    aPipelineDescriptor.vertexDescriptor = aSpriteVertexDescriptor;
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    //
    NSError *pipelineError01 = NULL;
    
    pipelineStateSpriteNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Sprite State, Alpha Blending";
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    //
    NSError *pipelineError02 = NULL;
    
    pipelineStateSpriteAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Sprite State, Additive Blending";
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOne;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOne;
    
    //
    NSError *pipelineError03 = NULL;
    pipelineStateSpriteAdditiveBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError03];
    
    if (pipelineError03 != NULL) {
        NSLog(@"Pipeline State Error 03: %@", pipelineError03.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Sprite State, Premultiplied Blending";
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorOne;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    
    NSError *pipelineError04 = NULL;
    pipelineStateSpritePremultipliedBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError04];
    
    if (pipelineError04 != NULL) {
        NSLog(@"Pipeline State Error 04: %@", pipelineError04.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Sprite State, White Blending";
    aPipelineDescriptor.fragmentFunction = _spriteFragmentProgramWhite;
    
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    NSError *pipelineError4 = NULL;
    pipelineStateSpriteWhiteBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError4];
    if (pipelineError4 != NULL) {
        NSLog(@"Pipeline State Error 4: %@", pipelineError4.description);
        return;
    }
}


- (void)buildPipelineStatesSimpleModel: (int)pRenderPass {
    //
    MTLVertexDescriptor *aSimpleModelVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    //
    aSimpleModelVertexDescriptor.attributes[SimpleModelVertexAttributePosition].format = MTLVertexFormatFloat3;
    aSimpleModelVertexDescriptor.attributes[SimpleModelVertexAttributePosition].offset = 0;
    aSimpleModelVertexDescriptor.attributes[SimpleModelVertexAttributePosition].bufferIndex = SimpleModelBufferIndexMeshPositions;
    //
    aSimpleModelVertexDescriptor.attributes[SimpleModelVertexAttributeTextureCoord].format = MTLVertexFormatFloat3;
    aSimpleModelVertexDescriptor.attributes[SimpleModelVertexAttributeTextureCoord].offset = 0;
    aSimpleModelVertexDescriptor.attributes[SimpleModelVertexAttributeTextureCoord].bufferIndex = SimpleModelBufferIndexMeshTextureCoords;
    //
    aSimpleModelVertexDescriptor.layouts[SimpleModelBufferIndexMeshPositions].stride = sizeof(float) * 3;
    aSimpleModelVertexDescriptor.layouts[SimpleModelBufferIndexMeshPositions].stepRate = 1;
    aSimpleModelVertexDescriptor.layouts[SimpleModelBufferIndexMeshPositions].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    aSimpleModelVertexDescriptor.layouts[SimpleModelBufferIndexMeshTextureCoords].stride = sizeof(float) * 3;
    aSimpleModelVertexDescriptor.layouts[SimpleModelBufferIndexMeshTextureCoords].stepRate = 1;
    aSimpleModelVertexDescriptor.layouts[SimpleModelBufferIndexMeshTextureCoords].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    aPipelineDescriptor.label = @"Simple Model State, No Blending";
    aPipelineDescriptor.sampleCount = 1;
    aPipelineDescriptor.vertexFunction = _simpleModelVertexProgram;
    aPipelineDescriptor.fragmentFunction = _simpleModelFragmentProgram;
    aPipelineDescriptor.vertexDescriptor = aSimpleModelVertexDescriptor;
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    aPipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    aPipelineDescriptor.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    
    NSError *pipelineError01 = NULL;
    pipelineStateSimpleModelNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    aPipelineDescriptor.label = @"Simple Model, Alpha Blending";
    
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    //
    NSError *pipelineError02 = NULL;
    pipelineStateSimpleModelAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
}

- (void)buildPipelineStatesSimpleModelIndexed: (int)pRenderPass {
    
    MTLVertexDescriptor *aSimpleModelIndexedVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    //
    aSimpleModelIndexedVertexDescriptor.attributes[ModelPackedVertexAttributeData].format = MTLVertexFormatFloat3;
    aSimpleModelIndexedVertexDescriptor.attributes[ModelPackedVertexAttributeData].offset = 0;
    aSimpleModelIndexedVertexDescriptor.attributes[ModelPackedVertexAttributeData].bufferIndex = ModelPackedBufferIndexMeshData;
    //
    aSimpleModelIndexedVertexDescriptor.layouts[ModelPackedVertexAttributeData].stride = sizeof(float) * 3;
    aSimpleModelIndexedVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepRate = 1;
    aSimpleModelIndexedVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    
    
    aPipelineDescriptor.label = @"Simple Model Indexed State, No Blending";
    aPipelineDescriptor.sampleCount = 1;
    aPipelineDescriptor.vertexFunction = _simpleModelIndexedVertexProgram;
    aPipelineDescriptor.fragmentFunction = _simpleModelIndexedFragmentProgram;
    aPipelineDescriptor.vertexDescriptor = aSimpleModelIndexedVertexDescriptor;
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    aPipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    aPipelineDescriptor.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    
    NSError *pipelineError01 = NULL;
    pipelineStateSimpleModelIndexedNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////
    //
    aPipelineDescriptor.label = @"Simple Model Indexed, Alpha Blending";
    
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    //
    NSError *pipelineError02 = NULL;
    pipelineStateSimpleModelIndexedAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
}

- (void)buildPipelineStatesModelIndexed: (int)pRenderPass {
    MTLVertexDescriptor *aModelIndexedVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    //
    aModelIndexedVertexDescriptor.attributes[ModelPackedVertexAttributeData].format = MTLVertexFormatFloat3;
    aModelIndexedVertexDescriptor.attributes[ModelPackedVertexAttributeData].offset = 0;
    aModelIndexedVertexDescriptor.attributes[ModelPackedVertexAttributeData].bufferIndex = ModelPackedBufferIndexMeshData;
    //
    aModelIndexedVertexDescriptor.layouts[ModelPackedVertexAttributeData].stride = sizeof(float) * 3;
    aModelIndexedVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepRate = 1;
    aModelIndexedVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    //
    aPipelineDescriptor.label = @"Model Indexed State, No Blending";
    aPipelineDescriptor.sampleCount = 1;
    aPipelineDescriptor.vertexFunction = _modelIndexedVertexProgram;
    aPipelineDescriptor.fragmentFunction = _modelIndexedFragmentProgram;
    aPipelineDescriptor.vertexDescriptor = aModelIndexedVertexDescriptor;
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    aPipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    aPipelineDescriptor.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    
    NSError *pipelineError01 = NULL;
    pipelineStateModelIndexedNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////
    //
    aPipelineDescriptor.label = @"Model Indexed, Alpha Blending";
    
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    NSError *pipelineError02 = NULL;
    pipelineStateModelIndexedAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
}

- (void)buildPipelineStatesModelIndexedLightedAmbient: (int)pRenderPass {
    MTLVertexDescriptor *aVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    //
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].format = MTLVertexFormatFloat3;
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].offset = 0;
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].bufferIndex = ModelPackedBufferIndexMeshData;
    //
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stride = sizeof(float) * 3;
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepRate = 1;
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    //
    aPipelineDescriptor.label = @"Model Indexed + Ambient Lighting State, No Blending";
    aPipelineDescriptor.sampleCount = 1;
    aPipelineDescriptor.vertexFunction = _modelIndexedAmbientVertexProgram;
    aPipelineDescriptor.fragmentFunction = _modelIndexedAmbientFragmentProgram;
    aPipelineDescriptor.vertexDescriptor = aVertexDescriptor;
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    aPipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    aPipelineDescriptor.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    
    NSError *pipelineError01 = NULL;
    pipelineStateModelIndexedLightedAmbientNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////
    //
    aPipelineDescriptor.label = @"Model Indexed + Ambient Lighting, Alpha Blending";
    
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    NSError *pipelineError02 = NULL;
    pipelineStateModelIndexedLightedAmbientAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
}

- (void)buildPipelineStatesModelIndexedLightedDiffuse: (int)pRenderPass {
    MTLVertexDescriptor *aVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    //
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].format = MTLVertexFormatFloat3;
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].offset = 0;
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].bufferIndex = ModelPackedBufferIndexMeshData;
    //
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stride = sizeof(float) * 3;
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepRate = 1;
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    //
    aPipelineDescriptor.label = @"Model Indexed + Diffuse Lighting State, No Blending";
    aPipelineDescriptor.sampleCount = 1;
    
    aPipelineDescriptor.vertexFunction = _modelIndexedDiffuseVertexProgram;
    aPipelineDescriptor.fragmentFunction = _modelIndexedDiffuseFragmentProgram;
    aPipelineDescriptor.vertexDescriptor = aVertexDescriptor;
    
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    
    aPipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    aPipelineDescriptor.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    
    NSError *pipelineError01 = NULL;
    
    pipelineStateModelIndexedLightedDiffuseNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////
    //
    aPipelineDescriptor.label = @"Model Indexed + Diffuse Lighting, Alpha Blending";
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    
    //
    NSError *pipelineError02 = NULL;
    pipelineStateModelIndexedLightedDiffuseAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
}



- (void)buildPipelineStatesModelIndexedLightedPhong: (int)pRenderPass {
    MTLVertexDescriptor *aVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    //
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].format = MTLVertexFormatFloat3;
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].offset = 0;
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].bufferIndex = ModelPackedBufferIndexMeshData;
    //
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stride = sizeof(float) * 3;
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepRate = 1;
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    //
    aPipelineDescriptor.label = @"Model Indexed + Phong Lighting State, No Blending";
    aPipelineDescriptor.sampleCount = 1;
    aPipelineDescriptor.vertexFunction = _modelIndexedPhongVertexProgram;
    aPipelineDescriptor.fragmentFunction = _modelIndexedPhongFragmentProgram;
    aPipelineDescriptor.vertexDescriptor = aVertexDescriptor;
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    aPipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    aPipelineDescriptor.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    
    NSError *pipelineError01 = NULL;
    
    pipelineStateModelIndexedLightedPhongNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////
    //
    aPipelineDescriptor.label = @"Model Indexed + Phong Lighting, Alpha Blending";
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    //
    NSError *pipelineError02 = NULL;
    pipelineStateModelIndexedLightedPhongAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
}


- (void)buildPipelineStatesModelIndexedLightedPhongOverlay: (int)pRenderPass {
    MTLVertexDescriptor *aVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    //
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].format = MTLVertexFormatFloat3;
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].offset = 0;
    aVertexDescriptor.attributes[ModelPackedVertexAttributeData].bufferIndex = ModelPackedBufferIndexMeshData;
    //
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stride = sizeof(float) * 3;
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepRate = 1;
    aVertexDescriptor.layouts[ModelPackedVertexAttributeData].stepFunction = MTLVertexStepFunctionPerVertex;
    //
    //////////////////////////////////////////////////////////////////////////////////
    //
    MTLRenderPipelineDescriptor *aPipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    //
    aPipelineDescriptor.label = @"Model Indexed + Phong Lighting State, No Blending";
    aPipelineDescriptor.sampleCount = 1;
    aPipelineDescriptor.vertexFunction = _modelIndexedPhongOverlayVertexProgram;
    aPipelineDescriptor.fragmentFunction = _modelIndexedPhongOverlayFragmentProgram;
    aPipelineDescriptor.vertexDescriptor = aVertexDescriptor;
    aPipelineDescriptor.colorAttachments[0].pixelFormat = gMetalLayer.pixelFormat;
    aPipelineDescriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    aPipelineDescriptor.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    
    NSError *pipelineError01 = NULL;
    
    pipelineStateModelIndexedLightedPhongOverlayNoBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError01];
    if (pipelineError01 != NULL) {
        NSLog(@"Pipeline State Error 01: %@", pipelineError01.description);
        return;
    }
    //
    //////////////
    //
    aPipelineDescriptor.label = @"Model Indexed + Phong Lighting, Alpha Blending";
    aPipelineDescriptor.colorAttachments[0].blendingEnabled = YES;
    aPipelineDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    aPipelineDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    aPipelineDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    //
    NSError *pipelineError02 = NULL;
    pipelineStateModelIndexedLightedPhongOverlayAlphaBlending[pRenderPass] = [gMetalEngine.device newRenderPipelineStateWithDescriptor: aPipelineDescriptor error: &pipelineError02];
    if (pipelineError02 != NULL) {
        NSLog(@"Pipeline State Error 02: %@", pipelineError02.description);
        return;
    }
}

@end
