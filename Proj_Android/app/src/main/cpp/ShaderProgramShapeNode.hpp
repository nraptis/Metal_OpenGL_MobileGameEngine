//
//  ShaderProgramShapeNode.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramShapeNode_hpp
#define ShaderProgramShapeNode_hpp

#include "ShaderProgram.hpp"

class ShaderProgramShapeNode: public ShaderProgram {
public:
    ShaderProgramShapeNode(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    
    virtual void                ArrayBufferData(FBuffer *pBuffer, int pOffset) override;
    virtual void                ArrayBufferPositions(FBuffer *pBuffer,int pOffset) override;
    virtual void                ArrayBufferColors(FBuffer *pBuffer, int pOffset) override;
    
    
    int                         mSlotColors;
    int                         mDataOffset;
    
};

#endif
