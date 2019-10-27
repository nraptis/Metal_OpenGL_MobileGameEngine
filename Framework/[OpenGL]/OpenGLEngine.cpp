//
//  OpenGLEngine.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "OpenGLEngine.hpp"
#include "FFile.hpp"
#include "FApp.hpp"

OpenGLEngine *gOpenGLEngine = NULL;

OpenGLEngine::OpenGLEngine() {
    
    
    mShaderProgramShape2D = NULL;
    mShaderProgramShape3D = NULL;
    mShaderProgramSprite = NULL;
    mShaderProgramSpriteWhite = NULL;
    
    mShaderProgramShapeNode = NULL;
    mShaderProgramSpriteNode = NULL;
    
    mShaderProgramSimpleModel = NULL;
    mShaderProgramSimpleModelIndexed = NULL;
    
    mShaderProgramModelIndexed = NULL;
    
    mShaderProgramModelIndexedLightedAmbient = NULL;
    mShaderProgramModelIndexedLightedDiffuse = NULL;
    
    mShaderProgramModelIndexedLightedPhong = NULL;
    mShaderProgramModelIndexedLightedPhongOverlay = NULL;
    mShaderProgramModelIndexedLightedSimpleSpotlight = NULL;
    
    //ShaderProgramModelIndexedLightedAmbient
    //ShaderProgramModelIndexedLightedDiffuse
    //ShaderProgramModelIndexedLightedPhong
    
    mIsReady = false;
}

OpenGLEngine::~OpenGLEngine() {
    
}

void OpenGLEngine::SetUp() {
    
    Log("OpenGLEngine::SetUp()\n");
    
    
    /*
    glGenFramebuffers(1, &gFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gFrameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, gRenderBuffer0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, gRenderBuffer1);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gDepthBuffer);
    */
    
    BuildPrograms();
    
    mIsReady = true;
}

void OpenGLEngine::TearDown() {
    
    Log("OpenGLEngine::TearDown()\n");
    
    
    delete mShaderProgramShape2D;
    mShaderProgramShape2D = NULL;
    
    delete mShaderProgramShape3D;
    mShaderProgramShape3D = NULL;
    
    delete mShaderProgramSprite;
    mShaderProgramSprite = NULL;
    
    delete mShaderProgramSpriteWhite;
    mShaderProgramSpriteWhite = NULL;
    
    delete mShaderProgramShapeNode;
    mShaderProgramShapeNode = NULL;
    
    delete mShaderProgramSpriteNode;
    mShaderProgramSpriteNode = NULL;
    
    delete mShaderProgramSimpleModel;
    mShaderProgramSimpleModel = NULL;
    
    delete mShaderProgramSimpleModelIndexed;
    mShaderProgramSimpleModelIndexed = NULL;
    
    delete mShaderProgramModelIndexed;
    mShaderProgramModelIndexed = NULL;
    
    delete mShaderProgramModelIndexedLightedAmbient;
    mShaderProgramModelIndexedLightedAmbient = NULL;
    
    delete mShaderProgramModelIndexedLightedDiffuse;
    mShaderProgramModelIndexedLightedDiffuse = NULL;
    
    delete mShaderProgramModelIndexedLightedPhong;
    mShaderProgramModelIndexedLightedPhong = NULL;
    
    delete mShaderProgramModelIndexedLightedPhongOverlay;
    mShaderProgramModelIndexedLightedPhongOverlay = NULL;
    
    delete mShaderProgramModelIndexedLightedSimpleSpotlight;
    mShaderProgramModelIndexedLightedSimpleSpotlight = NULL;
    
    mIsReady = false;
}

void OpenGLEngine::BuildPrograms() {
    
    mShaderProgramShape2D = new ShaderProgram("shape_2d_vertex_shader.glsl", "shape_2d_fragment_shader.glsl");
    mShaderProgramShape2D->Compile();
    
    mShaderProgramShape3D = new ShaderProgramShape3D("shape_3d_vertex_shader.glsl", "shape_3d_fragment_shader.glsl");
    mShaderProgramShape3D->Compile();
    
    mShaderProgramSprite = new ShaderProgramSprite("sprite_vertex_shader.glsl", "sprite_fragment_shader.glsl");
    mShaderProgramSprite->Compile();
    
    mShaderProgramSpriteWhite = new ShaderProgramSpriteWhite("sprite_white_vertex_shader.glsl", "sprite_white_fragment_shader.glsl");
    mShaderProgramSpriteWhite->Compile();
    
    mShaderProgramShapeNode = new ShaderProgramShapeNode("shape_node_vertex_shader.glsl", "shape_node_fragment_shader.glsl");
    mShaderProgramShapeNode->Compile();
    
    mShaderProgramSimpleModel = new ShaderProgramSimpleModel("simple_model_vertex_shader.glsl", "simple_model_fragment_shader.glsl");
    mShaderProgramSimpleModel->Compile();
    
    mShaderProgramSimpleModelIndexed = new ShaderProgramSimpleModelIndexed("simple_model_vertex_shader.glsl", "simple_model_fragment_shader.glsl");
    mShaderProgramSimpleModelIndexed->Compile();
    
    
    
    mShaderProgramModelIndexed = new ShaderProgramModelIndexed("simple_model_vertex_shader.glsl", "simple_model_fragment_shader.glsl");
    mShaderProgramModelIndexed->Compile();
    
    
    
    mShaderProgramModelIndexedLightedAmbient = new ShaderProgramModelIndexedLightedAmbient("model_lighted_ambient_vertex_shader.glsl", "model_lighted_ambient_fragment_shader.glsl");
    mShaderProgramModelIndexedLightedAmbient->Compile();
    
    mShaderProgramModelIndexedLightedDiffuse = new ShaderProgramModelIndexedLightedDiffuse("model_lighted_diffuse_vertex_shader.glsl", "model_lighted_diffuse_fragment_shader.glsl");
    mShaderProgramModelIndexedLightedDiffuse->Compile();
    
    
    
    
    
    mShaderProgramModelIndexedLightedPhong = new ShaderProgramModelIndexedLightedPhong("model_lighted_phong_vertex_shader.glsl", "model_lighted_phong_fragment_shader.glsl");
    mShaderProgramModelIndexedLightedPhong->Compile();
    
    
    mShaderProgramModelIndexedLightedPhongOverlay = new ShaderProgramModelIndexedLightedPhong("model_lighted_phong_overlay_vertex_shader.glsl", "model_lighted_phong_overlay_fragment_shader.glsl");
    mShaderProgramModelIndexedLightedPhongOverlay->Compile();
    
    
    //model_lighted_directional_vertex_shader.glsl
    //model_lighted_directional_fragment_shader.glsl
    
    
    //mShaderProgramModelIndexedLightedSimpleSpotlight = new ShaderProgramModelIndexedLightedSimpleSpotlight("model_lighted_simple_spotlight_vertex_shader.glsl", "model_lighted_simple_spotlight_fragment_shader.glsl");
    //mShaderProgramModelIndexedLightedSimpleSpotlight->Compile();
    
    
    //
    //
    
    /*
    //ShaderProgramShapeNode          *;//
    ShaderProgramSpriteNode         *mShaderProgramSpriteNode;//ShaderProgramSpriteNode
    
    ShaderProgramModel              *mShaderProgramModel;//ShaderProgramModel
    
    */
    
    
    /*
     
    
    
    
    simple_model_indexed_fragment_shader.glsl
    simple_model_indexed_vertex_shader.glsl
     
     
     
    model_fragment_shader.glsl
    model_indexed_fragment_shader.glsl
    
    
     
    model_indexed_vertex_shader.glsl
    model_vertex_shader.glsl
    
    
    */
    
    
    
    
}

bool OpenGLEngine::IsReady() {
    return mIsReady;
}

void OpenGLEngine::Prerender() {
    
}

void OpenGLEngine::Postrender() {
    
}

void OpenGLEngine::UseProgram(ShaderProgram *pProgram) {
    if (pProgram != NULL) {
        Graphics::SetShaderProgram(pProgram);
        pProgram->Use();
    } else {
        if (pProgram) {
            Log("Could Not Use Program [%s]", pProgram->mName.c());
        } else {
            Log("Could Not Use Program [???]");
        }
    }
}

void OpenGLEngine::UseProgramShape2D() {
    UseProgram(mShaderProgramShape2D);
}

void OpenGLEngine::UseProgramShape3D() {
    UseProgram(mShaderProgramShape3D);
}

void OpenGLEngine::UseProgramSprite() {
    UseProgram(mShaderProgramSprite);
}

void OpenGLEngine::UseProgramSpriteWhite() {
    UseProgram(mShaderProgramSpriteWhite);
}

void OpenGLEngine::UseProgramShapeNode() {
    UseProgram(mShaderProgramShapeNode);
}

void OpenGLEngine::UseProgramSimpleModel() {
    UseProgram(mShaderProgramSimpleModel);
}


void OpenGLEngine::UseProgramSimpleModelIndexed() {
    UseProgram(mShaderProgramSimpleModelIndexed);
}

void OpenGLEngine::UseProgramModelIndexed() {
    UseProgram(mShaderProgramModelIndexed);
}

void OpenGLEngine::UseProgramModelIndexedAmbient() {
    UseProgram(mShaderProgramModelIndexedLightedAmbient);
}


void OpenGLEngine::UseProgramModelIndexedDiffuse() {
    UseProgram(mShaderProgramModelIndexedLightedDiffuse);
}

void OpenGLEngine::UseProgramModelIndexedPhong() {
    UseProgram(mShaderProgramModelIndexedLightedPhong);
}

void OpenGLEngine::UseProgramModelIndexedPhongOverlay() {
    UseProgram(mShaderProgramModelIndexedLightedPhongOverlay);
}

void OpenGLEngine::UseProgramModelIndexedSimpleSpotlight() {
    
    Log("Not Implemented:: UseProgramModelIndexedSimpleSpotlight\n");
    exit(0);
    //UseProgram(mShaderProgramModelIndexedLightedSimpleSpotlight);
}

