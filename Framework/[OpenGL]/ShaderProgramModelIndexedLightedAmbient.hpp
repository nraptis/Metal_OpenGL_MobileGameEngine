//
//  ShaderProgramModelIndexedLightedAmbientLightedAmbient.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramModelIndexedLightedAmbientLightedAmbient_hpp
#define ShaderProgramModelIndexedLightedAmbientLightedAmbient_hpp

#include "ShaderProgram.hpp"


class ShaderProgramModelIndexedLightedAmbient: public ShaderProgram {
public:
    ShaderProgramModelIndexedLightedAmbient(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    
    virtual void                ArrayBufferData(FBuffer *pBuffer, int pOffset) override;
    virtual void                ArrayBufferPositions(FBuffer *pBuffer,int pOffset) override;
    virtual void                ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) override;
    
    int                         mSlotTextureCoords;
    int                         mSlotTexture;
    
    int                         mSlotAmbient;
    
    int                         mDataOffset;
    
    
    //mSlotAmbient
    //Ambient
    
};

#endif /* ShaderProgramModelIndexedLightedAmbientLightedAmbient_hpp */
