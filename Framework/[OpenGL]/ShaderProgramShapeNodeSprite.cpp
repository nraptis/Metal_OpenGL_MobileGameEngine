//
//  ShaderProgramShapeNodeSpriteSprite.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 1/8/20.
//  Copyright © 2020 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "os_core_graphics.h"
#include "ShaderProgramShapeNodeSprite.hpp"

ShaderProgramShapeNodeSprite::ShaderProgramShapeNodeSprite(const char *pVertexPath, const char *pFragmentPath) : ShaderProgram(pVertexPath, pFragmentPath) {
    mDataOffset = 0;
    mSlotColors = -1;
}

void ShaderProgramShapeNodeSprite::Compile() {
    
    ShaderProgram::Compile();
    
    if (IsValid() == false) {
        return;
    }
    
    mSlotColors = glGetAttribLocation(mProgram, "Colors");
    mSlotTextureCoords = glGetAttribLocation(mProgram, "TextureCoords");
    
    mSlotTexture = glGetUniformLocation(mProgram, "Texture");
    
    
    //mSlotTexture = glGetUniformLocation(mProgram, "Texture");
    //mSlotAmbient = glGetUniformLocation(mProgram, "Ambient");
    
    //mSlotTextureCoords = glGetAttribLocation(mProgram, "TextureCoords");
    
}

void ShaderProgramShapeNodeSprite::BindUniform(FUniforms *pUniform) {
    
    if (pUniform && pUniform->GetType() == UNIFORM_TYPE_BASIC) {
        ShaderProgram::BindUniform(pUniform);
        
    } else {
        Log("Uniform wrong type? [%p]\n", pUniform);
    }
}

void ShaderProgramShapeNodeSprite::ArrayBufferData(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3 + 4;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
    
    mDataOffset = pOffset;
}

void ShaderProgramShapeNodeSprite::ArrayBufferPositions(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3 + 4;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}

void ShaderProgramShapeNodeSprite::ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotTextureCoords);
    int aStride = 3 + 3 + 4;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset]);
    glVertexAttribPointer(mSlotTextureCoords, 2, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}

void ShaderProgramShapeNodeSprite::ArrayBufferColors(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3 + 4;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotColors, 4, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}


