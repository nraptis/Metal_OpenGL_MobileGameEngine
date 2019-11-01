//
//  ShaderProgramModelIndexedLightedDiffuseDiffuse.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramModelIndexedLightedDiffuseDiffuse_hpp
#define ShaderProgramModelIndexedLightedDiffuseDiffuse_hpp


#include "ShaderProgram.hpp"


class ShaderProgramModelIndexedLightedDiffuse: public ShaderProgram {
public:
    ShaderProgramModelIndexedLightedDiffuse(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    
    virtual void                ArrayBufferData(FBuffer *pBuffer, int pOffset) override;
    virtual void                ArrayBufferPositions(FBuffer *pBuffer,int pOffset) override;
    virtual void                ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) override;
    virtual void                ArrayBufferNormals(FBuffer *pBuffer, int pOffset) override;
    
    int                         mSlotNormalMatrixUniform;
    
    int                         mSlotTextureCoords;
    int                         mSlotNormals;
    int                         mSlotTexture;
    
    int                         mSlotAmbient;
    int                         mSlotDiffuse;
    
    int                         mDataOffset;
};

#endif /* ShaderProgramModelIndexedLightedDiffuseDiffuse_hpp */
