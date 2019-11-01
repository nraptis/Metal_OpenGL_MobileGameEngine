//
//  ShaderProgramShapeNode.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/15/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "os_core_graphics.h"
#include "ShaderProgramShapeNode.hpp"

ShaderProgramShapeNode::ShaderProgramShapeNode(const char *pVertexPath, const char *pFragmentPath) : ShaderProgram(pVertexPath, pFragmentPath) {
    mDataOffset = 0;
    mSlotColors = -1;
}

void ShaderProgramShapeNode::Compile() {
    
    ShaderProgram::Compile();
    
    if (IsValid() == false) return;
    
    mSlotColors = glGetAttribLocation(mProgram, "Colors");
    
    Log("Shader[%s] mSlotProjectionMatrixUniform = %d\n", mName.c(), mSlotProjectionMatrixUniform);
}

void ShaderProgramShapeNode::BindUniform(FUniforms *pUniform) {
    
    if (pUniform && pUniform->GetType() == UNIFORM_TYPE_BASIC) {
        ShaderProgram::BindUniform(pUniform);
        
    } else {
        Log("Uniform wrong type? [%x]\n", pUniform);
    }
}

void ShaderProgramShapeNode::ArrayBufferData(FBuffer *pBuffer, int pOffset) {
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

void ShaderProgramShapeNode::ArrayBufferPositions(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3 + 4;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotPositions, 3, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
    
}

void ShaderProgramShapeNode::ArrayBufferColors(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 3 + 3 + 4;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset + mDataOffset]);
    glVertexAttribPointer(mSlotColors, 4, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}


