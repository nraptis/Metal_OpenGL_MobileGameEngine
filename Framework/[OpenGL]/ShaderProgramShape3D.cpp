//
//  ShaderProgramShape3D.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "ShaderProgramShape3D.hpp"

ShaderProgramShape3D::ShaderProgramShape3D(const char *pVertexPath, const char *pFragmentPath) : ShaderProgram(pVertexPath, pFragmentPath) {
}

void ShaderProgramShape3D::Compile() {
    
    ShaderProgram::Compile();
    
    if (IsValid() == false) return;
}

void ShaderProgramShape3D::BindUniform(FUniforms *pUniform) {
    if (pUniform && pUniform->GetType() == UNIFORM_TYPE_BASIC) {
        ShaderProgram::BindUniform(pUniform);
    } else {
        Log("Uniform wrong type? [%p]\n", pUniform);
    }
}

void ShaderProgramShape3D::ArrayBufferPositions(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}
