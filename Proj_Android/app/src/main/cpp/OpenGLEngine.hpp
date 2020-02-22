//
//  OpenGLEngine.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef OpenGLEngine_hpp
#define OpenGLEngine_hpp

#include "ShaderProgram.hpp"
#include "ShaderProgramSprite.hpp"
#include "ShaderProgramSpriteWhite.hpp"
#include "ShaderProgramShape3D.hpp"

#include "ShaderProgramShapeNode.hpp"
#include "ShaderProgramShapeNodeSprite.hpp"
#include "ShaderProgramSpriteNode.hpp"
#include "ShaderProgramSimpleModel.hpp"
#include "ShaderProgramSimpleModelIndexed.hpp"
#include "ShaderProgramModelIndexed.hpp"
#include "ShaderProgramModelIndexedLightedAmbient.hpp"
#include "ShaderProgramModelIndexedLightedDiffuse.hpp"
#include "ShaderProgramModelIndexedLightedPhong.hpp"
#include "ShaderProgramModelIndexedLightedSimpleSpotlight.hpp"

class OpenGLEngine {
public:
    
    OpenGLEngine();
    ~OpenGLEngine();
    
    void                                            SetUp();
    void                                            TearDown();
    
    void                                            BuildPrograms();
    
    void                                            Prerender();
    void                                            Postrender();
    
    
    bool                                            IsReady();
    bool                                            mIsReady;
    
    void                                            UseProgram(ShaderProgram *pProgram);
    
    void                                            UseProgramShape2D();
    void                                            UseProgramShape3D();
    
    void                                            UseProgramSprite();
    void                                            UseProgramSpriteWhite();
    void                                            UseProgramShapeNode();
    void                                            UseProgramShapeNodeSprite();
    void                                            UseProgramSimpleModel();
    void                                            UseProgramSimpleModelIndexed();
    void                                            UseProgramModelIndexed();
    
    
    void                                            UseProgramModelIndexedAmbient();
    void                                            UseProgramModelIndexedDiffuse();
    void                                            UseProgramModelIndexedPhong();
    void                                            UseProgramModelIndexedPhongOverlay();
    
    void                                            UseProgramModelIndexedSimpleSpotlight();
    
    
    
    
    
    
    ShaderProgram                                   *mShaderProgramShape2D;
    ShaderProgramShape3D                            *mShaderProgramShape3D;
    ShaderProgramSprite                             *mShaderProgramSprite;
    ShaderProgramSpriteWhite                        *mShaderProgramSpriteWhite;
    
    
    
    ShaderProgramShapeNode                          *mShaderProgramShapeNode;//ShaderProgramShapeNode
    ShaderProgramShapeNodeSprite                    *mShaderProgramShapeNodeSprite;
    ShaderProgramSpriteNode                         *mShaderProgramSpriteNode;//ShaderProgramSpriteNode
    ShaderProgramSimpleModel                        *mShaderProgramSimpleModel;//ShaderProgramSimpleModel
    ShaderProgramSimpleModelIndexed                 *mShaderProgramSimpleModelIndexed;
    
    ShaderProgramModelIndexed                       *mShaderProgramModelIndexed;
    
    ShaderProgramModelIndexedLightedAmbient         *mShaderProgramModelIndexedLightedAmbient;
    
    ShaderProgramModelIndexedLightedDiffuse         *mShaderProgramModelIndexedLightedDiffuse;
    
    ShaderProgramModelIndexedLightedPhong           *mShaderProgramModelIndexedLightedPhong;
    ShaderProgramModelIndexedLightedPhong           *mShaderProgramModelIndexedLightedPhongOverlay;
    
    
    
    ShaderProgramModelIndexedLightedSimpleSpotlight *mShaderProgramModelIndexedLightedSimpleSpotlight;
    
    
    //model_lighted_phong_vertex_shader.glsl
    
    //model_lighted_phong_vertex_shader.glsl
    //model_lighted_ambient_diffuse_fragment_shader.glsl
    //model_lighted_ambient_diffuse_vertex_shader.glsl
    
    //model_lighted_phong_fragment_shader.glsl
    
    
};

extern OpenGLEngine *gOpenGLEngine;

#endif /* OpenGLEngine_hpp */
