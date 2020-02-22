//
//  ShaderProgram.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include "FString.hpp"
#include "FUniforms.hpp"
#include "FBuffer.hpp"

#define SHADER_INVALID_PROGRAM 99999999
#define SHADER_INVALID_SHADER 99999999

class ShaderProgram {
public:
    ShaderProgram(const char *pVertexPath, const char *pFragmentPath);
    ~ShaderProgram();
    
    virtual void                Compile();
    virtual void                BindUniform(FUniforms *pUniform);
    
    virtual void                ArrayBufferData(FBuffer *pBuffer, int pOffset);
    virtual void                ArrayBufferPositions(FBuffer *pBuffer, int pOffset);
    virtual void                ArrayBufferTextureCoords(FBuffer *pBuffer, int pOffset);
    virtual void                ArrayBufferColors(FBuffer *pBuffer, int pOffset);
    virtual void                ArrayBufferNormals(FBuffer *pBuffer, int pOffset);
    
    bool                        IsValid();
    
    void                        Use();
    void                        Kill();
    
    unsigned int                ShaderCompileVertex(const char *pShaderPath);
    unsigned int                ShaderCompileFragment(const char *pShaderPath);
    unsigned int                ShaderCompile(const char *pShaderPath, unsigned int pShaderType);
    
    FString                     mName;
    FString                     mFragmentProgramFile;
    FString                     mVertexProgramFile;
    
    unsigned int                mProgram;
    unsigned int                mVertexShader;
    unsigned int                mFragmentShader;
    
    int                         mSlotProjectionMatrixUniform;
    int                         mSlotModelViewMatrixUniform;
    int                         mSlotModulateColorUniform;
    
    int                         mSlotPositions;
    
};

#endif /* ShaderProgram_hpp */
