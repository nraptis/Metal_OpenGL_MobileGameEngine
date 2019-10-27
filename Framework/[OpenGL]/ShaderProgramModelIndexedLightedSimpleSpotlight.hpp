//
//  ShaderProgramModelIndexedLightedSimpleSpotlight.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramModelIndexedLightedSimpleSpotlight_hpp
#define ShaderProgramModelIndexedLightedSimpleSpotlight_hpp

#include "ShaderProgram.hpp"

class ShaderProgramModelIndexedLightedSimpleSpotlight: public ShaderProgram {
public:
    ShaderProgramModelIndexedLightedSimpleSpotlight(const char *pVertexPath, const char *pFragmentPath);
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
    int                         mSlotMaterial;
    
    
    int                         mDataOffset;
};


#endif /* ShaderProgramModelIndexedLightedSimpleSpotlight_hpp */
