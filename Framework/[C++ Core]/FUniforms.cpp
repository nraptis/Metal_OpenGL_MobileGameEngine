//
//  FUniforms.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/22/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FUniforms.hpp"
#include "os_core_graphics.h"
#include "core_includes.h"

FUniforms::FUniforms() {
    
}

FUniforms::~FUniforms() {
    
}

unsigned int FUniforms::GetType() {
    return UNIFORM_TYPE_BASIC;
}

unsigned int FUniforms::GetVertexSize() {
    return sizeof(float) * 32;
}

unsigned int FUniforms::GetFragmentSize() {
    return sizeof(float) * 4;
}

void FUniforms::WriteVertexToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aMatrixSize = sizeof(float) * 16;
    memcpy(aPtr, mProjection.m, aMatrixSize);
    aPtr = &(aPtr[aMatrixSize]);
    memcpy(aPtr, mModelView.m, aMatrixSize);
}

void FUniforms::WriteFragmentToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aSize = sizeof(mColor);
    memcpy(aPtr, &mColor, aSize);
}

FUniformsLightAmbient::FUniformsLightAmbient() {
    
}

FUniformsLightAmbient::~FUniformsLightAmbient() {
    
}

unsigned int FUniformsLightAmbient::GetType() {
    return UNIFORM_TYPE_LIGHT_AMBIENT;
}

unsigned int FUniformsLightAmbient::GetVertexSize() {
    int aSize = FUniforms::GetVertexSize();
    return aSize;
}

unsigned int FUniformsLightAmbient::GetFragmentSize() {
    int aSize = FUniforms::GetFragmentSize();
    aSize += sizeof(mLight);
    return aSize;
}

void FUniformsLightAmbient::WriteVertexToBuffer(void *pData, unsigned int pOffset) {
    FUniforms::WriteVertexToBuffer(pData, pOffset);
}

void FUniformsLightAmbient::WriteFragmentToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aColorSize = sizeof(mColor);
    static int aLightSize = sizeof(mLight);
    memcpy(aPtr, &mColor, aColorSize);
    aPtr = &(aPtr[aColorSize]);
    memcpy(aPtr, &mLight, aLightSize);
}

FUniformsLightDiffuse::FUniformsLightDiffuse() {
    
}

FUniformsLightDiffuse::~FUniformsLightDiffuse() {
    
}

unsigned int FUniformsLightDiffuse::GetType() {
    return UNIFORM_TYPE_LIGHT_DIFFUSE;
}

unsigned int FUniformsLightDiffuse::GetVertexSize() {
    int aSize = FUniforms::GetVertexSize();
    aSize += sizeof(float) * 16;
    return aSize;
}

unsigned int FUniformsLightDiffuse::GetFragmentSize() {
    int aSize = FUniforms::GetFragmentSize();
    aSize += sizeof(mLight);
    return aSize;
}

void FUniformsLightDiffuse::WriteVertexToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aMatrixSize = sizeof(float) * 16;
    memcpy(aPtr, mProjection.m, aMatrixSize);
    aPtr = &(aPtr[aMatrixSize]);
    memcpy(aPtr, mModelView.m, aMatrixSize);
    aPtr = &(aPtr[aMatrixSize]);
    memcpy(aPtr, mNormal.m, aMatrixSize);
}

void FUniformsLightDiffuse::WriteFragmentToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aColorSize = sizeof(mColor);
    static int aLightSize = sizeof(mLight);
    memcpy(aPtr, &mColor, aColorSize);
    aPtr = &(aPtr[aColorSize]);
    memcpy(aPtr, &mLight, aLightSize);
    
}


void FUniformsLightDiffuse::Print() {
    
    /*
    Log("*** BEGIN FUniformsLightDiffuse ***\n");
    
    Log("mDiffuse.mRed = %f;\n", mDiffuse.mRed);
    Log("mDiffuse.mGreen = %f;\n", mDiffuse.mGreen);
    Log("mDiffuse.mBlue = %f;\n", mDiffuse.mBlue);
    Log("mDiffuse.mIntensity = %f;\n", mDiffuse.mIntensity);
    Log("***\n");
    Log("mDiffuse.mDirX = %f;\n", mDiffuse.mDirX);
    Log("mDiffuse.mDirY = %f;\n", mDiffuse.mDirY);
    Log("mDiffuse.mDirZ = %f;\n", mDiffuse.mDirZ);
    
    Log("*** END FUniformsLightDiffuse ***\n");
    */
}

FUniformsLightPhong::FUniformsLightPhong() {
    
}

FUniformsLightPhong::~FUniformsLightPhong() {
    
}

unsigned int FUniformsLightPhong::GetType() {
    return UNIFORM_TYPE_LIGHT_PHONG;
}

unsigned int FUniformsLightPhong::GetVertexSize() {
    int aSize = FUniforms::GetVertexSize();
    aSize += sizeof(float) * 16;
    return aSize;
}

unsigned int FUniformsLightPhong::GetFragmentSize() {
    int aSize = FUniforms::GetFragmentSize();
    aSize += sizeof(mLight);
    return aSize;
}

void FUniformsLightPhong::WriteVertexToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aMatrixSize = sizeof(float) * 16;
    memcpy(aPtr, mProjection.m, aMatrixSize);
    aPtr = &(aPtr[aMatrixSize]);
    memcpy(aPtr, mModelView.m, aMatrixSize);
    aPtr = &(aPtr[aMatrixSize]);
    memcpy(aPtr, mNormal.m, aMatrixSize);
}

void FUniformsLightPhong::WriteFragmentToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aColorSize = sizeof(mColor);
    static int aLightSize = sizeof(mLight);
    
    memcpy(aPtr, &mColor, aColorSize);
    aPtr = &(aPtr[aColorSize]);
    
    memcpy(aPtr, &mLight, aLightSize);
}


void FUniformsLightPhong::Print() {
    
    
    
    Log("*** BEGIN FUniformsLightPhong ***\n");
    
    
    Log("mLight.mAmbientIntensity = %f;\n", mLight.mAmbientIntensity);
    Log("mLight.mDiffuseIntensity = %f;\n", mLight.mDiffuseIntensity);
    Log("mLight.mSpecularIntensity = %f;\n", mLight.mSpecularIntensity);
    
    Log("mLight.mRed = %f;\n", mLight.mRed);
    Log("mLight.mGreen = %f;\n", mLight.mGreen);
    Log("mLight.mBlue = %f;\n", mLight.mBlue);
    
    
    Log("mLight.mDirX = %f;\n", mLight.mDirX);
    Log("mLight.mDirY = %f;\n", mLight.mDirY);
    Log("mLight.mDirZ = %f;\n", mLight.mDirZ);

    Log("mLight.mShininess = %f;\n", mLight.mShininess);
    
    Log("******* For Uni **********\n");
    
    Log("mUniform.mLight.mAmbientIntensity = %f;\n", mLight.mAmbientIntensity);
    Log("mUniform.mLight.mDiffuseIntensity = %f;\n", mLight.mDiffuseIntensity);
    Log("mUniform.mLight.mSpecularIntensity = %f;\n", mLight.mSpecularIntensity);
    
    Log("mUniform.mLight.mRed = %f;\n", mLight.mRed);
    Log("mUniform.mLight.mGreen = %f;\n", mLight.mGreen);
    Log("mUniform.mLight.mBlue = %f;\n", mLight.mBlue);
    
    Log("mUniform.mLight.mDirX = %f;\n", mLight.mDirX);
    Log("mUniform.mLight.mDirY = %f;\n", mLight.mDirY);
    Log("mUniform.mLight.mDirZ = %f;\n", mLight.mDirZ);
    
    Log("mUniform.mLight.mShininess = %f;\n", mLight.mShininess);
    
    Log("*** END FUniformsLightPhong ***\n");
}






FUniformsLightSimpleSpotlight::FUniformsLightSimpleSpotlight() {
    
}

FUniformsLightSimpleSpotlight::~FUniformsLightSimpleSpotlight() {
    
}

unsigned int FUniformsLightSimpleSpotlight::GetType() {
    return UNIFORM_TYPE_LIGHT_SIMPLE_SPOTLIGHT;
    
    //mLight
}

unsigned int FUniformsLightSimpleSpotlight::GetVertexSize() {
    int aSize = FUniforms::GetVertexSize();
    
    //Size of normal matrix.
    aSize += sizeof(float) * 16;
    
    return aSize;
}

unsigned int FUniformsLightSimpleSpotlight::GetFragmentSize() {
    int aSize = FUniforms::GetFragmentSize();
    aSize += sizeof(mLight);
    return aSize;
}

void FUniformsLightSimpleSpotlight::WriteVertexToBuffer(void *pData, unsigned int pOffset) {
    FUniforms::WriteVertexToBuffer(pData, pOffset);
}

void FUniformsLightSimpleSpotlight::WriteFragmentToBuffer(void *pData, unsigned int pOffset) {
    char *aContents = (char *)pData;
    char *aPtr = &aContents[pOffset];
    static int aColorSize = sizeof(mColor);
    static int aLightSize = sizeof(mLight);
    
    memcpy(aPtr, &mColor, aColorSize);
    aPtr = &(aPtr[aColorSize]);
    
    memcpy(aPtr, &mLight, aLightSize);
    //aPtr = &(aPtr[aLightSize]);
    
    //memcpy(aPtr, &mDiffuse, aDiffuseSize);
    
}


void FUniformsLightSimpleSpotlight::Print() {
    
    
    
    Log("*** BEGIN FUniformsLightSimpleSpotlight ***\n");
    
    
    Log("mLight.mAmbientIntensity = %f;\n", mLight.mAmbientIntensity);
    Log("mLight.mDiffuseIntensity = %f;\n", mLight.mDiffuseIntensity);
    Log("mLight.mSpecularIntensity = %f;\n", mLight.mSpecularIntensity);
    
    Log("mLight.mRed = %f;\n", mLight.mRed);
    Log("mLight.mGreen = %f;\n", mLight.mGreen);
    Log("mLight.mBlue = %f;\n", mLight.mBlue);
    
    
    Log("mLight.mDirX = %f;\n", mLight.mDirX);
    Log("mLight.mDirY = %f;\n", mLight.mDirY);
    Log("mLight.mDirZ = %f;\n", mLight.mDirZ);
    
    Log("mLight.mShininess = %f;\n", mLight.mShininess);
    
    Log("******* For Uni **********\n");
    
    Log("mUniform.mLight.mAmbientIntensity = %f;\n", mLight.mAmbientIntensity);
    Log("mUniform.mLight.mDiffuseIntensity = %f;\n", mLight.mDiffuseIntensity);
    Log("mUniform.mLight.mSpecularIntensity = %f;\n", mLight.mSpecularIntensity);
    
    Log("mUniform.mLight.mRed = %f;\n", mLight.mRed);
    Log("mUniform.mLight.mGreen = %f;\n", mLight.mGreen);
    Log("mUniform.mLight.mBlue = %f;\n", mLight.mBlue);
    
    Log("mUniform.mLight.mDirX = %f;\n", mLight.mDirX);
    Log("mUniform.mLight.mDirY = %f;\n", mLight.mDirY);
    Log("mUniform.mLight.mDirZ = %f;\n", mLight.mDirZ);
    
    Log("mUniform.mLight.mShininess = %f;\n", mLight.mShininess);
    
    Log("*** END FUniformsLightSimpleSpotlight ***\n");
}




