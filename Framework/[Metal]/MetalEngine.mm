//
//  MetalEngine.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/5/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "core_includes.h"
#import "core_app_shell.hpp"
#import "os_core_graphics.h"
#import "MetalEngine.h"
#import "MetalViewController.h"

@interface MetalEngine() {
    id <MTLTexture> _resolveTextureMSAA;
    id <MTLTexture> _storageTextureMain;
    id <MTLTexture> _depthTexture;
}

@end

@implementation MetalEngine


- (void)setup {
    
    gMetalEngine = self;
    
    _device = MTLCreateSystemDefaultDevice();
    
    gMetalView.metalLayer.device = _device;
    gMetalView.metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    
    MTLDepthStencilDescriptor *aDepthDescriptor = [[MTLDepthStencilDescriptor alloc] init];
    aDepthDescriptor.depthCompareFunction = MTLCompareFunctionLess;
    aDepthDescriptor.depthWriteEnabled = YES;
    _depthState = [_device newDepthStencilStateWithDescriptor: aDepthDescriptor];
    //
    //
    MTLDepthStencilDescriptor *aDepthDisabledDescriptor = [[MTLDepthStencilDescriptor alloc] init];
    aDepthDisabledDescriptor.depthCompareFunction = MTLCompareFunctionAlways;
    aDepthDisabledDescriptor.depthWriteEnabled = NO;
    _depthStateDisabled = [_device newDepthStencilStateWithDescriptor: aDepthDisabledDescriptor];
    //
    //TODO: Turn off for screen shots eventually? Maybe?
    gMetalView.metalLayer.framebufferOnly = YES;
    //
    ///////////////////
    //
    _defaultLibrary = [_device newDefaultLibrary];
    //
    //
    //
    [self buildSamplerStates];
    
    _resolveTextureMSAA = [self createAliasingTextureFromWidth: gDeviceWidth * _screenScale andHeight: gDeviceHeight * _screenScale];
    
    _storageTextureMain = [self createStorageTextureFromWidth: (gDeviceWidth * _screenScale) andHeight: (gDeviceHeight * _screenScale)];
    
    _depthTexture = [self createStencilTextureFromWidth: (gDeviceWidth * _screenScale) andHeight: (gDeviceHeight * _screenScale)];
    
    _commandQueue = [_device newCommandQueue];
    
    _renderPassDescriptor3DMain = [[MTLRenderPassDescriptor alloc] init];
    _renderPassDescriptor3DMain.colorAttachments[0].loadAction = MTLLoadActionLoad;
    _renderPassDescriptor3DMain.colorAttachments[0].storeAction = MTLStoreActionStore;
    _renderPassDescriptor3DMain.colorAttachments[0].texture = _storageTextureMain;
    _renderPassDescriptor3DMain.depthAttachment.loadAction = MTLLoadActionClear;
    _renderPassDescriptor3DMain.depthAttachment.clearDepth = 1.0f;
    _renderPassDescriptor3DMain.depthAttachment.texture = _depthTexture;
    _renderPassDescriptor3DMain.stencilAttachment.texture = _depthTexture;
    
    _renderPassDescriptor2DMain = [[MTLRenderPassDescriptor alloc] init];
    _renderPassDescriptor2DMain.colorAttachments[0].loadAction = MTLLoadActionDontCare;
    _renderPassDescriptor2DMain.colorAttachments[0].storeAction = MTLStoreActionMultisampleResolve;
    _renderPassDescriptor2DMain.colorAttachments[0].texture = _resolveTextureMSAA;
    
    _semaphore = dispatch_semaphore_create(1);
    
    _ready = true;
}

+ (id)layerClass {
    return [CAMetalLayer class];
}

- (void)setDefaultEncoderState {
    //[_renderCommandEncoder setRenderPipelineState: _pipelineStateSpriteAlphaBlending];
    [_renderCommandEncoder setFragmentSamplerState: _samplerStateLinearClamp atIndex: SamplerIndexColor];
}

- (void)prerender {
    
    dispatch_semaphore_wait(_semaphore, DISPATCH_TIME_FOREVER);
    
    _renderPass = -1;
    _renderCommandEncoder = NULL;
    
    
    //"Unless you want to do encoding work across threads, you only need to create one command buffer per frame. Also, unless you need to perform rendering in multiple passes (not just multiple draw calls, actually reading image data back from one pass in a subsequent pass), you only need one render command encoder per command buffer."
    _commandBuffer = [_commandQueue commandBuffer];
    if (_commandBuffer == NULL) { NSLog(@"Failed to get Command Buffer"); return; }
    
    _drawable = gMetalLayer.nextDrawable;
    if (_drawable == NULL) {
        NSLog(@"No Next Drawable..."); return; }
    
    /*
    
    
    //_renderPassDescriptorClearDepth.colorAttachments[0].resolveTexture = _resolveTextureMSAA;
    
    //
    
    _didClearDepth = NO;
    
    _renderCommandEncoder = [_commandBuffer renderCommandEncoderWithDescriptor: _renderPassDescriptor];
    if (_commandBuffer == NULL) { NSLog(@"Failed to get Render Command Encoder..."); return; }
     
    */
    
    
    
    
    __block dispatch_semaphore_t aSemaphore = _semaphore;
    [_commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
        dispatch_semaphore_signal(aSemaphore);
    }];
    
    [self setDefaultEncoderState];
}

- (void)postrender {
    
    //if (_didClearDepth == NO) {
    //    [self clearDepth];
    //}
    
    [_renderCommandEncoder endEncoding];
}

- (void)commit {
    if (_drawable == NULL) { NSLog(@"Failed to have Drawable..."); return; }
    if (_commandBuffer == NULL) { NSLog(@"Failed to have Command Buffer"); return; }
    
    [_commandBuffer presentDrawable: _drawable];
    [_commandBuffer commit];
}

- (MTLRenderPassDescriptor *)renderPassDescriptor: (int)renderPass {
    MTLRenderPassDescriptor *aResult = NULL;
    
    if (renderPass == GFX_RENDER_PASS_3D_MAIN) {
        aResult = _renderPassDescriptor3DMain;
    }
    
    if (renderPass == GFX_RENDER_PASS_2D_MAIN) {
        aResult = _renderPassDescriptor2DMain;
    }
    
    return aResult;
}

- (void)startRenderPass: (int)renderPass clearingColor: (BOOL)clearColor clearingDepth: (BOOL)clearDepth {
    
    if (_renderCommandEncoder) {
        [_renderCommandEncoder endEncoding];
        _renderCommandEncoder = nil;
    }
    
    _renderPass = renderPass;
    gMetalPipeline.renderPass = renderPass;
    
    MTLRenderPassDescriptor *aRenderPassDescriptor = [self renderPassDescriptor: renderPass];
    
    if (aRenderPassDescriptor == NULL) {
        NSLog(@"NO RENDER PASS DESCRIPTOR [%d]...\n", renderPass);
        return;
    }
    
    if (clearColor) {
        MTLClearColor aClearColor;
        aClearColor.red = 0.25f;
        aClearColor.green = 0.25f;
        aClearColor.blue = 0.25f;
        aClearColor.alpha = 1.0f;
        aRenderPassDescriptor.colorAttachments[0].clearColor = aClearColor;
        aRenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    }
    
    if (clearDepth) {
        aRenderPassDescriptor.depthAttachment.loadAction = MTLLoadActionClear;
        aRenderPassDescriptor.depthAttachment.clearDepth = 1.0f;
    }
    
    if (renderPass == GFX_RENDER_PASS_2D_MAIN) {
        aRenderPassDescriptor.colorAttachments[0].resolveTexture = _drawable.texture;
    }
    
    _renderCommandEncoder = [_commandBuffer renderCommandEncoderWithDescriptor: aRenderPassDescriptor];
    if (_commandBuffer == NULL) { NSLog(@"Failed to get Render Command Encoder..."); return; }
    
    
    [_renderCommandEncoder setFragmentSamplerState: _samplerStateLinearClamp atIndex: SamplerIndexColor];
    
    if (renderPass == GFX_RENDER_PASS_2D_MAIN) {
        [_renderCommandEncoder setFragmentTexture: _storageTextureMain atIndex: 0];
        Graphics::DrawCurrentTile();
    }
}

- (void)displayCallback {
    
}

- (void)buildSamplerStates {
    MTLSamplerDescriptor *aSamplerDescriptor = [MTLSamplerDescriptor new];
    aSamplerDescriptor.minFilter = MTLSamplerMinMagFilterLinear;
    aSamplerDescriptor.magFilter = MTLSamplerMinMagFilterLinear;
    aSamplerDescriptor.sAddressMode = MTLSamplerAddressModeClampToEdge;
    aSamplerDescriptor.tAddressMode = MTLSamplerAddressModeClampToEdge;
    _samplerStateLinearClamp = [_device newSamplerStateWithDescriptor: aSamplerDescriptor];
    
    aSamplerDescriptor.sAddressMode = MTLSamplerAddressModeRepeat;
    aSamplerDescriptor.tAddressMode = MTLSamplerAddressModeRepeat;
    _samplerStateLinearRepeat = [_device newSamplerStateWithDescriptor: aSamplerDescriptor];
}

- (id<MTLTexture>)createAliasingTextureFromWidth: (int)pWidth andHeight: (int)pHeight {
    int aSampleCount = 4;
    MTLTextureDescriptor *aDescriptor = [[MTLTextureDescriptor alloc] init];
    [aDescriptor setPixelFormat: MTLPixelFormatBGRA8Unorm];
    [aDescriptor setWidth: pWidth];
    [aDescriptor setHeight: pHeight];
    [aDescriptor setTextureType: MTLTextureType2DMultisample];
    [aDescriptor setUsage: MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead];
    [aDescriptor setSampleCount: aSampleCount];
    [aDescriptor setResourceOptions: MTLResourceStorageModePrivate];
    return  [_device newTextureWithDescriptor: aDescriptor];
}

- (id<MTLTexture>)createStorageTextureFromWidth: (int)pWidth andHeight: (int)pHeight {
    int aSampleCount = 1;
    MTLTextureDescriptor *aDescriptor = [[MTLTextureDescriptor alloc] init];
    [aDescriptor setPixelFormat: MTLPixelFormatBGRA8Unorm];
    [aDescriptor setWidth: pWidth];
    [aDescriptor setHeight: pHeight];
    [aDescriptor setTextureType: MTLTextureType2D];
    [aDescriptor setUsage: MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead];
    [aDescriptor setSampleCount: aSampleCount];
    return  [_device newTextureWithDescriptor: aDescriptor];
}

- (id<MTLTexture>)createStencilTextureFromWidth: (int)pWidth andHeight: (int)pHeight {
    int aSampleCount = 1;
    MTLTextureDescriptor *aDescriptor = [[MTLTextureDescriptor alloc] init];
    [aDescriptor setPixelFormat: MTLPixelFormatDepth32Float_Stencil8];
    [aDescriptor setWidth: pWidth];
    [aDescriptor setHeight: pHeight];
    [aDescriptor setTextureType: MTLTextureType2D];
    [aDescriptor setUsage: MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead];
    [aDescriptor setSampleCount: aSampleCount];
    [aDescriptor setResourceOptions: MTLResourceStorageModePrivate];
    return  [_device newTextureWithDescriptor: aDescriptor];
}

/*
Drawable [<AGXA7Texture: 0x11bd73c20>
          label = Drawable
          textureType = MTLTextureType2D
          pixelFormat = MTLPixelFormatBGRA8Unorm
          width = 1536
          height = 2048
          depth = 1
          arrayLength = 1
          mipmapLevelCount = 1
          sampleCount = 1
          cpuCacheMode = MTLCPUCacheModeDefaultCache
          storageMode = MTLStorageModeShared
          resourceOptions = MTLResourceCPUCacheModeDefaultCache MTLResourceStorageModeShared
          usage = MTLTextureUsageShaderRead MTLTextureUsageShaderWrite MTLTextureUsageRenderTarget MTLTextureUsagePixelFormatView
          framebufferOnly = 1
          purgeableState = MTLPurgeableStateNonVolatile
          swizzle = [MTLTextureSwizzleRed, MTLTextureSwizzleGreen, MTLTextureSwizzleBlue, MTLTextureSwizzleAlpha]
          isCompressed = 0
          parentTexture = <null>
          parentRelativeLevel = 0
          parentRelativeSlice = 0
          buffer = <null>
          bufferOffset = 0
          bufferBytesPerRow = 0]
*/



@end
