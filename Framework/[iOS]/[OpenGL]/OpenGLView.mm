//
//  OpenGLView.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "core_includes.h"
#import "core_app_shell.hpp"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "OpenGLViewController.h"
#import "OpenGLView.h"
#import "FMatrix.hpp"
#import "FImage.hpp"
#import "FApp.hpp"


//TODO: Change contents of non-uniform buffer mid-render and compare results versus un changed non-uniform buffer which remains
//static throughout render pass, can we change the data mid render, or does the binding occur only on commit???... huh?

//TODO: You must CERTAINLY be able to use only one "sprite buffer" and
//share it among all of the different sprites? Or... ?

@interface OpenGLView() {
    EAGLContext *context;
    
    GLint framebufferWidth;
    GLint framebufferHeight;
    
    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
    GLuint defaultFramebuffer, colorRenderbuffer;
    GLuint depthRenderbuffer;
}

@end

@implementation OpenGLView

- (void)setup {
    gOpenGLView = self;
    //
    //
    //
    ///////////////////
    //
    //
    //
    
    _screenScale = (int)([UIScreen mainScreen].scale + 0.5f);
    
    Graphics::SetDeviceScale(_screenScale);
    
    self.multipleTouchEnabled = YES;
    self.contentScaleFactor = _screenScale;
    
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
    
    gOpenGLLayer = _eaglLayer;
    
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    
    context = [[EAGLContext alloc] initWithAPI:api];
    
    if (!context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext: context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
    
    [self createFramebuffer];
    [self setFramebuffer];
}

+ (id)layerClass {
    return [CAEAGLLayer class];
}

- (void)displayCallback {
    AppShellFrame();
}

- (void)active {
    if (_displayLink == NULL) {
        _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(displayCallback)];
        [_displayLink setPreferredFramesPerSecond: 60];
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode: NSDefaultRunLoopMode];
    }
}

- (void)inactive {
    if (_displayLink != NULL) {
        [_displayLink invalidate];
        _displayLink = nil;
    }
}


- (void)createFramebuffer {
    if (context && !defaultFramebuffer) {
        [EAGLContext setCurrentContext: context];
        
        glGenFramebuffers(1, &defaultFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        glGenRenderbuffers(1, &colorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        glGenRenderbuffers(1, &depthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, framebufferWidth, framebufferHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
        
        NSLog(@"Frame Buffer Size [%d x %d]\n", framebufferWidth, framebufferHeight);
        NSLog(@"Device Size [%d x %d]\n", (int)gDeviceWidth, (int)gDeviceHeight);
    }
}

- (void)deleteFramebuffer {
    if (context) {
        [EAGLContext setCurrentContext: context];
        if (defaultFramebuffer) {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        if(colorRenderbuffer)
        {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }
    }
}

- (void)setFramebuffer {
    if (context) {
        [EAGLContext setCurrentContext:context];
//        if (!defaultFramebuffer) {
//            NSLog(@"ASDF... createFramebuffer...\n");
//
//            //[self performSelectorOnMainThread: @selector(createFramebuffer) withObject: nil waitUntilDone: YES];
//
//        }
//
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        glViewport(0, 0, framebufferWidth, framebufferHeight);
    }
}

- (void)setContext {
    if (context != NULL) {
        [EAGLContext setCurrentContext: context];
    }
}

- (BOOL)presentFramebuffer {
    BOOL success = FALSE;
    if (context) {
        [EAGLContext setCurrentContext: context];
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        success = [context presentRenderbuffer: GL_RENDERBUFFER];
    }
    return success;
}

- (void)commit {
    if (context != NULL) {
        [context presentRenderbuffer: GL_RENDERBUFFER];
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

- (void) touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event {
    for (int i=0;i<[touches count];i++) {
        UITouch *aTouch = [[touches allObjects] objectAtIndex: i];
        if ([aTouch phase] == UITouchPhaseEnded) {
            CGPoint aLocation = [aTouch locationInView: self];
            AppShellTouchUp(aLocation.x, aLocation.y, (__bridge void*)aTouch);
        }
    }
}

- (void) touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    for (int i=0;i<[touches count];i++) {
        UITouch *aTouch = [[touches allObjects] objectAtIndex: i];
        if ([aTouch phase]  == UITouchPhaseCancelled) {
            CGPoint aLocation = [aTouch locationInView: self];
            AppShellTouchCanceled(aLocation.x, aLocation.y, (__bridge void*)aTouch);
        }
    }
}

@end
