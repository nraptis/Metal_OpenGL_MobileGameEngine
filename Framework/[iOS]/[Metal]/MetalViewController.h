//
//  MetalViewController.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Metal/Metal.h>
#import "MetalView.h"
#import "MetalEngine.h"
#import "MetalPipeline.h"

@interface MetalViewController : UIViewController

@property (nonatomic, strong) MetalView *metalView;
@property (nonatomic, strong) MetalEngine *metalEngine;
@property (nonatomic, strong) MetalPipeline *metalPipeline;

- (void)setup;

@end

extern CAMetalLayer *gMetalLayer;
extern MetalView *gMetalView;
extern MetalEngine *gMetalEngine;
extern MetalPipeline *gMetalPipeline;
