//
//  .hpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef PlatformGraphicsInterface_hpp
#define PlatformGraphicsInterface_hpp


#ifndef GLFW_EXPOSE_NATIVE_NSGL
#define GLFW_EXPOSE_NATIVE_NSGL
#endif

#ifndef GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

//#include "base/CCRef.h"
//#include "platform/CCCommon.h"
//#include "platform/CCGLView.h"
#include "GraphicsInterface.hpp"

class PlatformGraphicsInterface : public GraphicsInterface
{
public:
    PlatformGraphicsInterface();
    virtual ~PlatformGraphicsInterface();
    
    //Only gets called after IsReady is true...
    virtual void Initialize() override;
    
    virtual float GetScale() override;
    
    // overrides
    virtual void Kill() override;
    virtual bool IsReady() override;
    
    virtual void SetContext() override;
    
    virtual void Prerender() override;
    virtual void Postrender() override;
    virtual void Commit() override;

protected:
    void *mMetalView;
    
    double mLastTime;
    
};

#endif

