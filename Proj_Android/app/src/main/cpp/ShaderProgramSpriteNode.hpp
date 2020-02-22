//
//  ShaderProgramSpriteNodeNode.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramSpriteNodeNode_hpp
#define ShaderProgramSpriteNodeNode_hpp

#include "ShaderProgram.hpp"

class ShaderProgramSpriteNode: public ShaderProgram {
public:
    ShaderProgramSpriteNode(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    
    virtual void                ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) override;
    
    int                         mSlotTextureCoords;
    int                         mSlotTexture;
};

#endif /* ShaderProgramSpriteNodeNode_hpp */
