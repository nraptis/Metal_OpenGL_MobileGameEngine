//
//  ShaderProgramShapeNodeSpriteSprite.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 1/8/20.
//  Copyright © 2020 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramShapeNodeSpriteSprite_hpp
#define ShaderProgramShapeNodeSpriteSprite_hpp

#include "ShaderProgram.hpp"

class ShaderProgramShapeNodeSprite: public ShaderProgram {
public:
    ShaderProgramShapeNodeSprite(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    
    virtual void                ArrayBufferData(FBuffer *pBuffer, int pOffset) override;
    virtual void                ArrayBufferPositions(FBuffer *pBuffer,int pOffset) override;
    virtual void                ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) override;
    virtual void                ArrayBufferColors(FBuffer *pBuffer, int pOffset) override;
    
    
    int                         mSlotColors;
    int                         mDataOffset;
    
    int                         mSlotTextureCoords;
    int                         mSlotTexture;
    
};

#endif
