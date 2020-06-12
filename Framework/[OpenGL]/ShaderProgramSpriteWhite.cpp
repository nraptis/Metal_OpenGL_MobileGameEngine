//
//  ShaderProgramSpriteWhiteWhite.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/9/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "ShaderProgramSpriteWhite.hpp"

ShaderProgramSpriteWhite::ShaderProgramSpriteWhite(const char *pVertexPath, const char *pFragmentPath) : ShaderProgram(pVertexPath, pFragmentPath) {
    mSlotTextureCoords = -1;
    mSlotTexture = -1;
}

void ShaderProgramSpriteWhite::Compile() {
    
    ShaderProgram::Compile();
    
    if (IsValid() == false) return;
    
    mSlotTexture = glGetUniformLocation(mProgram, "Texture");
    mSlotTextureCoords = glGetAttribLocation(mProgram, "TextureCoords");
}

void ShaderProgramSpriteWhite::BindUniform(FUniforms *pUniform) {
    
    if (pUniform && pUniform->GetType() == UNIFORM_TYPE_BASIC) {
        ShaderProgram::BindUniform(pUniform);
    } else {
        Log("Uniform wrong type? [%p]\n", pUniform);
    }
}

void ShaderProgramSpriteWhite::ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotTextureCoords);
    int aStride = 2;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset]);
    glVertexAttribPointer(mSlotTextureCoords, 2, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}
