//
//  MetalEngine.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/5/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "os_core_app_shell.h"

#if (CURRENT_ENV == ENV_IOS)
#import <UIKit/UIKit.h>
#elif (CURRENT_ENV == ENV_MAC)
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#endif

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

#import "ShaderTypes.h"


NS_ASSUME_NONNULL_BEGIN

@interface MetalEngine : NSObject

@property (nonatomic, assign) int screenScale;
@property (nonatomic, assign) int renderPass;

@property (nonatomic, nullable) id <MTLDevice> device;

//@property (nonatomic, strong) MTLRenderPassDescriptor * _Nonnull renderPassDescriptor;
//@property (nonatomic, strong) MTLRenderPassDescriptor * _Nonnull renderPassDescriptorClearDepth;

@property (nonatomic, strong) MTLRenderPassDescriptor * _Nonnull renderPassDescriptor3DMain;
@property (nonatomic, strong) MTLRenderPassDescriptor * _Nonnull renderPassDescriptor2DMain;

//#define GFX_RENDER_PASS_3D_MAIN 0
//#define GFX_RENDER_PASS_2D_MAIN 1













//
//@property (nonatomic, strong) id <MTLRenderPipelineState> _Nonnull pipelineStateShapeNodeNoBlending;
//@property (nonatomic, strong) id <MTLRenderPipelineState> _Nonnull pipelineStateShapeNodeAlphaBlending;
//@property (nonatomic, strong) id <MTLRenderPipelineState> _Nonnull pipelineStateShapeNodeAdditiveBlending;

//
@property (nonatomic, strong) id <MTLDepthStencilState> _Nonnull depthStateDisabled;
@property (nonatomic, strong) id <MTLDepthStencilState> _Nonnull depthState;
//
@property (nonatomic, strong) id <MTLSamplerState> _Nonnull samplerStateLinearClamp;
@property (nonatomic, strong) id <MTLSamplerState> _Nonnull samplerStateLinearRepeat;

@property (nonatomic, strong) id <MTLLibrary> _Nonnull defaultLibrary;

@property (nonatomic, strong) id <MTLCommandQueue> _Nonnull commandQueue;

@property (nonatomic, strong) id <MTLCommandBuffer> _Nullable commandBuffer;

@property (nonatomic, strong) id <MTLRenderCommandEncoder> _Nullable renderCommandEncoder;

@property (nonatomic, strong) id <CAMetalDrawable> _Nullable drawable;

@property (nonatomic, strong) dispatch_semaphore_t semaphore;

@property (nonatomic, assign) BOOL ready;

- (void)setup;

- (void)prerender;
- (void)postrender;

- (void)commit;

- (void)startRenderPass: (int)renderPass clearingColor: (BOOL)clearColor clearingDepth: (BOOL)clearDepth;



@end

NS_ASSUME_NONNULL_END
