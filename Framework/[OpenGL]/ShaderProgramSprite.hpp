//
//  ShaderProgramSprite.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramSprite_hpp
#define ShaderProgramSprite_hpp

#include "ShaderProgram.hpp"

class ShaderProgramSprite: public ShaderProgram {
public:
    ShaderProgramSprite(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    
    virtual void                ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) override;
    
    int                         mSlotTextureCoords;
    int                         mSlotTexture;
};


#endif
