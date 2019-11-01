//
//  MetalView.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "core_includes.h"
#import "core_app_shell.hpp"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "MetalViewController.h"
#import "MetalView.h"
#import "FMatrix.hpp"
#import "FImage.hpp"
#import "FApp.hpp"


//TODO: Change contents of non-uniform buffer mid-render and compare results versus un changed non-uniform buffer which remains
//static throughout render pass, can we change the data mid render, or does the binding occur only on commit???... huh?

//TODO: You must CERTAINLY be able to use only one "sprite buffer" and
//share it among all of the different sprites? Or... ?

@interface MetalView() {
    //
    
    
    
}

@end

@implementation MetalView

- (void)setup {
    gMetalView = self;
    //
    //
    //
    ///////////////////
    //
    //
    //
    
    [self setMultipleTouchEnabled: YES];
    
    //
    _screenScale = (int)([UIScreen mainScreen].scale + 0.5f);
    printf("SCREEN SCALE: [[%d]]\n", _screenScale);
    //
    //
    //
    _metalLayer = (CAMetalLayer *)self.layer;
    gMetalLayer = _metalLayer;
    _metalLayer.frame = CGRectMake(0.0f, 0.0f, kDeviceWidth, kDeviceHeight);
    _metalLayer.contentsScale = _screenScale;
    //
    //
    //
    
    //
    //
    //
}

+ (id)layerClass {
    return [CAMetalLayer class];
}

- (void)displayCallback {
    //...
    AppShellFrame();
}

- (void)startAnimating {
    
    if (_displayLink == NULL) {
        _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(displayCallback)];
        [_displayLink setPreferredFramesPerSecond: 60];
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode: NSDefaultRunLoopMode];
    }
    
    
}

- (void)stopAnimating {
    if (_displayLink) {
        [_displayLink invalidate];
        _displayLink = nil;
    }
    
}

- (void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event {
    for (int i=0;i<[touches count];i++) {
        UITouch *aTouch = [[touches allObjects] objectAtIndex:i];
        if ([aTouch phase] == UITouchPhaseBegan) {
            CGPoint aLocation = [aTouch locationInView:self];
            AppShellTouchDown(aLocation.x, aLocation.y, (__bridge void*)aTouch);
        }
    }
}

- (void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event {
    for (int i=0;i<[touches count];i++) {
        UITouch *aTouch = [[touches allObjects] objectAtIndex: i];
        if ([aTouch phase] == UITouchPhaseMoved) {
            CGPoint aLocation = [aTouch locationInView: self];
            AppShellTouchMove(aLocation.x, aLocation.y, (__bridge void*)aTouch);
        }
    }
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event {
    for (int i=0;i<[touches count];i++) {
        UITouch *aTouch = [[touches allObjects] objectAtIndex: i];
        if ([aTouch phase] == UITouchPhaseEnded) {
            CGPoint aLocation = [aTouch locationInView: self];
            AppShellTouchUp(aLocation.x, aLocation.y, (__bridge void*)aTouch);
        }
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    for (int i=0;i<[touches count];i++) {
        UITouch *aTouch = [[touches allObjects] objectAtIndex: i];
        if ([aTouch phase]  == UITouchPhaseCancelled) {
            CGPoint aLocation = [aTouch locationInView: self];
            AppShellTouchCanceled(aLocation.x, aLocation.y, (__bridge void*)aTouch);
        }
    }
}

@end
