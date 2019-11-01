//
//  MetalViewController.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import "MetalView.h"
#import "MetalEngine.h"
#import "MetalPipeline.h"

NS_ASSUME_NONNULL_BEGIN

@interface MetalViewController : NSViewController

@property (nonatomic, strong) MetalView *metalView;
@property (nonatomic, strong) MetalEngine *metalEngine;
@property (nonatomic, strong) MetalPipeline *metalPipeline;



- (void)setup;
- (void)teardown;

- (void)resize: (NSSize)pSize;


@end

extern CAMetalLayer *gMetalLayer;
extern MetalView *gMetalView;
extern MetalEngine *gMetalEngine;
extern MetalPipeline *gMetalPipeline;

NS_ASSUME_NONNULL_END
