//
//  ShaderProgramShape3D.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgramShape3D_hpp
#define ShaderProgramShape3D_hpp

#include "ShaderProgram.hpp"

class ShaderProgramShape3D : public ShaderProgram {
public:
    ShaderProgramShape3D(const char *pVertexPath, const char *pFragmentPath);
    virtual void                Compile() override;
    virtual void                BindUniform(FUniforms *pUniform) override;
    virtual void                ArrayBufferPositions(FBuffer *pBuffer,int pOffset) override;
};


#endif
