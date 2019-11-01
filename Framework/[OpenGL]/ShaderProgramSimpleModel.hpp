//
//  ShaderProgramSimpleModel.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramSimpleModel_hpp
#define ShaderProgramSimpleModel_hpp

#include "ShaderProgram.hpp"

class ShaderProgramSimpleModel: public ShaderProgram {
public:
    ShaderProgramSimpleModel(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    
    virtual void                ArrayBufferPositions(FBuffer *pBuffer,int pOffset) override;
    virtual void                ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) override;
    
    int                         mSlotTextureCoords;
    int                         mSlotTexture;
};

#endif /* ShaderProgramSimpleModel_hpp */
