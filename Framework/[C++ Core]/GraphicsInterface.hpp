//
//  GraphicsInterface.hpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef OPENGL_VIEW_HPP
#define OPENGL_VIEW_HPP

#include "FVec2.hpp"
#include "FRect.hpp"
#include "FString.hpp"
#include "core_app_shell.hpp"
#include "os_core_app_shell.h"

#if (CURRENT_ENV == ENV_WIN32)
#include <windows.h>
#endif

struct GLContextAttrs {
    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;
    int depthBits;
    int stencilBits;
    int multisamplingCount;
};

class GraphicsInterface {
public:
    GraphicsInterface();
    virtual ~GraphicsInterface();
    
    virtual void Initialize() { }

    virtual void Kill() { }
    
    virtual bool IsReady() { return false; }
    
    virtual float GetScale() { return mScale; }
    
    virtual void SetName(const char *pName) { mName = pName; }
    
    virtual void SetContext() { }
    virtual void Prerender() { }
    virtual void Postrender() { }
    virtual void Commit() { }
    
    
    virtual void PollEvents() { }
    
    virtual bool ShouldCloseWindow() { return false; };
    
    FRect                       mViewport;
    FString                     mName;
    float                       mScale;
};

extern GLContextAttrs cContextAttrs;

#endif

