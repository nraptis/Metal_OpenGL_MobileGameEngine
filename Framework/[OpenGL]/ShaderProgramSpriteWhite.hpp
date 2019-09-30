//
//  ShaderProgramSpriteWhiteWhite.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/9/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramSpriteWhiteWhite_hpp
#define ShaderProgramSpriteWhiteWhite_hpp

#include "ShaderProgram.hpp"

class ShaderProgramSpriteWhite : public ShaderProgram {
public:
    ShaderProgramSpriteWhite(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    
    virtual void                ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) override;
    
    int                         mSlotTextureCoords;
    int                         mSlotTexture;
};


#endif
