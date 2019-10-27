//
//  MetalView.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "AppDelegate.h"
#import "MetalView.h"
#import "RootViewController.h"
#import "FTouchManager.hpp"
#include "core_app_shell.hpp"


//TODO: Change contents of non-uniform buffer mid-render and compare results versus un changed non-uniform buffer which remains
//static throughout render pass, can we change the data mid render, or does the binding occur only on commit???... huh?

//TODO: You must CERTAINLY be able to use only one "sprite buffer" and
//share it among all of the different sprites? Or... ?

@interface MetalView() {
    
}

@end

@implementation MetalView

CVReturn displayCallback(CVDisplayLinkRef CV_NONNULL displayLink,
                         const CVTimeStamp * CV_NONNULL inNow,
                         const CVTimeStamp * CV_NONNULL inOutputTime,
                         CVOptionFlags flagsIn,
                         CVOptionFlags * CV_NONNULL flagsOut,
                         void * CV_NULLABLE displayLinkContext ) {
    AppShellFrame();
    return kCVReturnSuccess;
}

- (void)setup {
    _screenScale = (int)([NSScreen mainScreen].backingScaleFactor + 0.5f);
    
    self.layer = [[CAMetalLayer alloc] init];
    _metalLayer = (CAMetalLayer *)self.layer;
    gMetalLayer = _metalLayer;
    _metalLayer.frame = CGRectMake(0.0f, 0.0f, kDeviceWidth, kDeviceHeight);
    _metalLayer.contentsScale = _screenScale;
    
    //
    // Make the display link... For Mac...
    //
    CGDirectDisplayID displayID = CGMainDisplayID();
    CVReturn error = CVDisplayLinkCreateWithCGDisplay(displayID, &_displayLink);
    NSAssert((kCVReturnSuccess == error), @"Creating Display Link error %d", error);
    error = CVDisplayLinkSetOutputCallback(_displayLink, displayCallback, (__bridge void*)self);
    NSAssert((kCVReturnSuccess == error), @"Setting Display Link callback error %d", error);
    CVDisplayLinkStart(_displayLink);
    
    [self becomeFirstResponder];
}


- (void)teardown {
    if (_displayLink != NULL) {
        CVDisplayLinkStop(_displayLink);
        CVDisplayLinkRelease(_displayLink);
        _displayLink = NULL;
    }
}

- (void)resize: (NSSize)pSize {
    _metalLayer.frame = CGRectMake(0.0f, 0.0f, pSize.width, pSize.height);
    self.frame = CGRectMake(0.0f, 0.0f, pSize.width, pSize.height);
}

- (CGPoint)correctMousePos: (CGPoint)pos {
    CGPoint aResult = CGPointMake(pos.x, gDeviceHeight - pos.y);
    return aResult;
}

- (void)mouseDown:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseDown(aPoint.x, aPoint.y, MOUSE_BUTTON_LEFT);
}

- (void)mouseDragged:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseMove(aPoint.x, aPoint.y);
}

- (void)mouseUp:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseUp(aPoint.x, aPoint.y, MOUSE_BUTTON_LEFT);
}

- (void)rightMouseDown:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseDown(aPoint.x, aPoint.y, MOUSE_BUTTON_RIGHT);
}

- (void)rightMouseUp:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseUp(aPoint.x, aPoint.y, MOUSE_BUTTON_RIGHT);
}

- (void)rightMouseDragged:(NSEvent *)event {
    CGPoint aPoint = [event locationInWindow];
    aPoint = [self correctMousePos: aPoint];
    AppShellMouseMove(aPoint.x, aPoint.y);
}

- (int)convertKey:(unichar)keycode {
    
    if (keycode == NSUpArrowFunctionKey) return __KEY__UP;
    if (keycode == NSDownArrowFunctionKey) return __KEY__DOWN;
    if (keycode == NSLeftArrowFunctionKey) return __KEY__LEFT;
    if (keycode == NSRightArrowFunctionKey) return __KEY__RIGHT;
    
    if (keycode == NSF1FunctionKey) return __KEY__F1;
    if (keycode == NSF2FunctionKey) return __KEY__F2;
    if (keycode == NSF3FunctionKey) return __KEY__F3;
    if (keycode == NSF4FunctionKey) return __KEY__F4;
    if (keycode == NSF5FunctionKey) return __KEY__F5;
    if (keycode == NSF6FunctionKey) return __KEY__F6;
    if (keycode == NSF7FunctionKey) return __KEY__F7;
    if (keycode == NSF8FunctionKey) return __KEY__F8;
    if (keycode == NSF9FunctionKey) return __KEY__F9;
    if (keycode == NSF10FunctionKey) return __KEY__F10;
    if (keycode == NSF11FunctionKey) return __KEY__F11;
    if (keycode == NSF12FunctionKey) return __KEY__F12;
    
    if (keycode == 13) return __KEY__ENTER;
    if (keycode == 27) return __KEY__ESCAPE;
    if (keycode == ' ') return __KEY__SPACE;
    if (keycode == 127) return __KEY__DELETE;
    
    if (keycode == '0') return __KEY__0;
    if (keycode == '1') return __KEY__1;
    if (keycode == '2') return __KEY__2;
    if (keycode == '3') return __KEY__3;
    if (keycode == '4') return __KEY__4;
    if (keycode == '5') return __KEY__5;
    if (keycode == '6') return __KEY__6;
    if (keycode == '7') return __KEY__7;
    if (keycode == '8') return __KEY__8;
    if (keycode == '9') return __KEY__9;
    
    if (keycode == 'a' || keycode == 'A') return __KEY__A;
    if (keycode == 'b' || keycode == 'B') return __KEY__B;
    if (keycode == 'c' || keycode == 'C') return __KEY__C;
    if (keycode == 'd' || keycode == 'D') return __KEY__D;
    if (keycode == 'e' || keycode == 'E') return __KEY__E;
    if (keycode == 'f' || keycode == 'F') return __KEY__F;
    if (keycode == 'g' || keycode == 'G') return __KEY__G;
    if (keycode == 'h' || keycode == 'H') return __KEY__H;
    if (keycode == 'i' || keycode == 'I') return __KEY__I;
    if (keycode == 'j' || keycode == 'J') return __KEY__J;
    if (keycode == 'k' || keycode == 'K') return __KEY__K;
    if (keycode == 'l' || keycode == 'L') return __KEY__L;
    if (keycode == 'm' || keycode == 'M') return __KEY__M;
    if (keycode == 'n' || keycode == 'N') return __KEY__N;
    if (keycode == 'o' || keycode == 'O') return __KEY__O;
    if (keycode == 'p' || keycode == 'P') return __KEY__P;
    if (keycode == 'q' || keycode == 'Q') return __KEY__Q;
    if (keycode == 'r' || keycode == 'R') return __KEY__R;
    if (keycode == 's' || keycode == 'S') return __KEY__S;
    if (keycode == 't' || keycode == 'T') return __KEY__T;
    if (keycode == 'u' || keycode == 'U') return __KEY__U;
    if (keycode == 'v' || keycode == 'V') return __KEY__V;
    if (keycode == 'w' || keycode == 'W') return __KEY__W;
    if (keycode == 'x' || keycode == 'X') return __KEY__X;
    if (keycode == 'y' || keycode == 'Y') return __KEY__Y;
    if (keycode == 'z' || keycode == 'Z') return __KEY__Z;
    
    if (keycode == '-') return __KEY__MINUS;
    if (keycode == '=') return __KEY__EQUALS;
    if (keycode == '.') return __KEY__PERIOD;
    if (keycode == ',') return __KEY__COMMA;
    if (keycode == ':') return __KEY__COLON;
    if (keycode == '/') return __KEY__SLASH;
    if (keycode == '\\') return __KEY__BACKSLASH;
    
    
    return -1;
}

- (void)keyDown:(NSEvent *)theEvent {
    NSString *aString = [theEvent charactersIgnoringModifiers];
    if ([aString length] > 0) {
        unichar aChar = [aString characterAtIndex: 0];
        //NSLog(@"MAC KEY [%d]\n", aChar);
        int aKey = [self convertKey: aChar];
        AppShellKeyDown(aKey);
        return;
    }
    [super keyDown:theEvent];
}

- (void)keyUp:(NSEvent *)theEvent {
    NSString *aString = [theEvent charactersIgnoringModifiers];
    if ([aString length] > 0) {
        unichar aChar = [aString characterAtIndex: 0];
        int aKey = [self convertKey: aChar];
        AppShellKeyUp(aKey);
        return;
    }
    [super keyUp:theEvent];
}

- (void)flagsChanged:(NSEvent *)theEvent {
    NSUInteger aFlags = [[NSApp currentEvent] modifierFlags];
    
    if (aFlags & NSEventModifierFlagShift) {
        gKeyDownShift = true;
    } else {
        gKeyDownShift = false;
    }
    
    if (aFlags & NSEventModifierFlagCommand) {
        gKeyDownCtrl = true;
    } else {
        gKeyDownCtrl = false;
    }
    
    if (aFlags & NSEventModifierFlagOption) {
        gKeyDownAlt = true;
    } else {
        gKeyDownAlt = false;
    }
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

@end
