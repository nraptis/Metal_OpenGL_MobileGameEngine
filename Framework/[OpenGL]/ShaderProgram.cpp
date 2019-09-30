//
//  ShaderProgram.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "ShaderProgram.hpp"
#include "FFile.hpp"
#include "core_includes.h"

ShaderProgram::ShaderProgram(const char *pVertexPath, const char *pFragmentPath) {
    
    mFragmentProgramFile = pFragmentPath;
    mVertexProgramFile = pVertexPath;
    
    mName = FString(pVertexPath);
    mName.RemoveExtension();
    mName.Replace("_vertex_", "_");
    
    mProgram = SHADER_INVALID_PROGRAM;
    mVertexShader = SHADER_INVALID_SHADER;
    mFragmentShader = SHADER_INVALID_SHADER;
    
    mSlotProjectionMatrixUniform = -1;
    mSlotModelViewMatrixUniform = -1;
    mSlotModulateColorUniform = -1;
    mSlotPositions = -1;
}

ShaderProgram::~ShaderProgram() {
    Log("Destroying Shader %s\n", mName.c());
    Kill();
}

bool ShaderProgram::IsValid() {
    if (mProgram != SHADER_INVALID_PROGRAM && mProgram != 0) {
        return true;
    }
    return false;
}

void ShaderProgram::Use() {
    if (mProgram != SHADER_INVALID_PROGRAM && mProgram != 0) {
        glUseProgram(mProgram);
    } else {
        Log("Illegally Trying to use Shader Program [%d] [%s]\n", mProgram, mName.c());
    }
}

void ShaderProgram::Compile() {
    mProgram = glCreateProgram();
    
    mVertexShader = ShaderCompileVertex(mVertexProgramFile.c());
    mFragmentShader = ShaderCompileFragment(mFragmentProgramFile.c());
    
    glAttachShader(mProgram, mVertexShader);
    glAttachShader(mProgram, mFragmentShader);
    
    glLinkProgram(mProgram);
    
    GLint aLinkSuccess;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &aLinkSuccess);
    if (aLinkSuccess == GL_FALSE) {
        GLchar messages[512];
        glGetProgramInfoLog(mProgram, sizeof(messages), 0, &messages[0]);
        Log("Couldn't Link Shader [%s] MSG: [%s]\n", mName.c(), messages);
        Kill();
        return;
    }
    
    glUseProgram(mProgram);
    
    mSlotProjectionMatrixUniform = glGetUniformLocation(mProgram, "ProjectionMatrix");
    mSlotModelViewMatrixUniform = glGetUniformLocation(mProgram, "ModelViewMatrix");
    mSlotModulateColorUniform = glGetUniformLocation(mProgram, "ModulateColor");
    mSlotPositions = glGetAttribLocation(mProgram, "Positions");
}

void ShaderProgram::ArrayBufferData(FBuffer *pBuffer, int pOffset) {
    
    /*
    void gfx_positionSetPointer(int pSize, unsigned int pOffset, unsigned int pStride)
    {
        glVertexAttribPointer(gGLSlotPosition, pSize, GL_FLOAT, GL_FALSE, (pStride << 2), (GLvoid*)(pOffset << 2));
    }
    
    void gfx_texCoordSetPointer(int pSize, unsigned int pOffset, unsigned int pStride)
    {
        glVertexAttribPointer(gGLSlotTexCoord, pSize, GL_FLOAT, GL_FALSE, (pStride << 2), (GLvoid*)(pOffset << 2));
    }
    
    void gfx_colorSetPointer(unsigned int pOffset, unsigned int pStride)
    {
        glVertexAttribPointer(gGLSlotColor, 4, GL_FLOAT, GL_FALSE, (pStride << 2), (GLvoid*)(pOffset << 2));
    }
    */
}

void ShaderProgram::ArrayBufferPositions(FBuffer *pBuffer, int pOffset) {
    if (pBuffer != NULL && pBuffer->mBindIndex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, pBuffer->mBindIndex);
    }
    glEnableVertexAttribArray(mSlotPositions);
    int aStride = 2;
    unsigned char *aOffset = NULL;
    aOffset = &(aOffset[pOffset]);
    glVertexAttribPointer(mSlotPositions, 2, GL_FLOAT, GL_FALSE, (aStride << 2), aOffset);
}

void ShaderProgram::ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset) {
    
}

void ShaderProgram::ArrayBufferColors(FBuffer *pBuffer, int pOffset) {
    
}

void ShaderProgram::ArrayBufferNormals(FBuffer *pBuffer, int pOffset) {
    
}

void ShaderProgram::Kill() {
    if (mVertexShader != SHADER_INVALID_SHADER && mVertexShader != 0) {
        if (mProgram != SHADER_INVALID_PROGRAM && mProgram != 0) {
            glDetachShader(mProgram, mVertexShader);
        }
        glDeleteShader(mVertexShader);
    }
    if (mFragmentShader != SHADER_INVALID_SHADER && mFragmentShader != 0) {
        if (mProgram != SHADER_INVALID_PROGRAM && mProgram != 0) {
            glDetachShader(mProgram, mFragmentShader);
        }
        glDeleteShader(mFragmentShader);
    }
    
    if (mProgram != SHADER_INVALID_PROGRAM && mProgram != 0) {
        glDeleteProgram(mProgram);
    }
    
    mVertexShader = SHADER_INVALID_SHADER;
    mFragmentShader = SHADER_INVALID_SHADER;
    mProgram = SHADER_INVALID_PROGRAM;
}

unsigned int ShaderProgram::ShaderCompile(const char *pShaderPath, unsigned int  pShaderType) {
    unsigned int aShader = 0;
    FFile aFile;
    aFile.Load(pShaderPath);
    if (aFile.mLength > 0) {
        aShader = glCreateShader(pShaderType);
        const char *aData = (const char*)(aFile.mData);
        int aLength = (int)aFile.mLength;
        glShaderSource(aShader, 1, &aData, &(aLength));
        glCompileShader(aShader);
        int aCompileSuccess;
        glGetShaderiv(aShader, GL_COMPILE_STATUS, &aCompileSuccess);
        if (aCompileSuccess == GL_FALSE) {
            GLchar aErrorMessage[1024];
            glGetShaderInfoLog(aShader, sizeof(aErrorMessage), 0, &aErrorMessage[0]);
            Log("Shader Error!\n");
            Log("%s", aErrorMessage);
        }
    }
    return aShader;
}

unsigned int ShaderProgram::ShaderCompileVertex(const char *pShaderPath) {
    return ShaderCompile(pShaderPath, GL_VERTEX_SHADER);
}

unsigned int ShaderProgram::ShaderCompileFragment(const char *pShaderPath) {
    return ShaderCompile(pShaderPath, GL_FRAGMENT_SHADER);
}

void ShaderProgram::BindUniform(FUniforms *pUniform) {
    //Log("***\nERROR [Not Implemented]\n***\n***\n...\n");
    
    
    glUniformMatrix4fv(mSlotProjectionMatrixUniform, 1, 0, pUniform->mProjection.m);
    glUniformMatrix4fv(mSlotModelViewMatrixUniform, 1, 0, pUniform->mModelView.m);
    glUniform4f(mSlotModulateColorUniform, pUniform->mColor.mRed, pUniform->mColor.mGreen, pUniform->mColor.mBlue, pUniform->mColor.mAlpha);
}
