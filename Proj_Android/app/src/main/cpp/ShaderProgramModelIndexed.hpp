//
//  ShaderProgramModelIndexed.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramModelIndexed_hpp
#define ShaderProgramModelIndexed_hpp

#include "ShaderProgram.hpp"


class ShaderProgramModelIndexed: public ShaderProgram {
public:
    ShaderProgramModelIndexed(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    
    virtual void                ArrayBufferData(FBuffer *pBuffer, int pOffset) override;
    virtual void                ArrayBufferPositions(FBuffer *pBuffer,int pOffset) override;
    virtual void                ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) override;
    
    int                         mSlotTextureCoords;
    int                         mSlotTexture;
    int                         mDataOffset;
};


#endif /* ShaderProgramModelIndexed_hpp */
