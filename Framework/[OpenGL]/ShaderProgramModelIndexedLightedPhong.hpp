//
//  ShaderProgramModelIndexedLightedPhong.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramModelIndexedLightedPhong_hpp
#define ShaderProgramModelIndexedLightedPhong_hpp

#include "ShaderProgram.hpp"


class ShaderProgramModelIndexedLightedPhong: public ShaderProgram {
public:
    ShaderProgramModelIndexedLightedPhong(const char *pVertexPath, const char *pFragmentPath);
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
    int                         mSlotSpecular;
    
    
    int                         mDataOffset;
};

#endif /* ShaderProgramModelIndexedLightedPhong_hpp */
