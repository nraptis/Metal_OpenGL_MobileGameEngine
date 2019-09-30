//
//  RootViewController.h
//  MacMetal
//
//  Created by Nicholas Raptis on 1/25/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import "MetalViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface RootViewController : NSViewController

- (void)setup;
- (BOOL)isLandscape;

- (void)resize: (NSSize)pSize;



//@property (nonatomic, strong) NSView *view;
@property (nonatomic, strong) MetalViewController *metalViewController;

@end

extern RootViewController * _Nullable gRootBase;

NS_ASSUME_NONNULL_END
