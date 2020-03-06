//
//  FTextureCache.cpp
//  FleetGL
//
//  Created by Nick Raptis on 2/9/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FTextureCache.hpp"
#include "core_includes.h"

FTextureCacheNode::FTextureCacheNode(FTexture *pTexture) {
    mTexture = pTexture;
    mBindCount = 0;
    mNextNode = 0;
}

FTextureCacheNode::~FTextureCacheNode() {
    
}

FTextureCache::FTextureCache() {
    mAutoMode = true;
}

FTextureCache::~FTextureCache() {
    
}

FTexture *FTextureCache::GetTexture(const char *pFileName) {
    FTextureCacheNode *aNode = (FTextureCacheNode *)mTableNodes.Get(pFileName);
    if (!aNode) {
        FTexture *aTexture = new FTexture(pFileName);
        aNode = new FTextureCacheNode(aTexture);
        mTableNodes.Add(pFileName, aNode);
        mNodeList.Add(aNode);
    }
    FTexture *aResult = aNode->mTexture;
    if (aResult) {
        aResult->Realize();
    }
    return aResult;
}

void FTextureCache::UnloadAllTextures() {
    
    EnumList(FTextureCacheNode, aNode, mNodeList) {
        //Log("--Unloading Node[%s]\n", aNode->mTexture->mFileName.c());
        if (aNode->mTexture->mBindIndex != -1) {
            Log("Unloading Texture %s (Should have been unloaded before-hand!\n", aNode->mTexture->mFileName.c());
        }
        aNode->mTexture->Unload();
    }
    
    //mNodeList.RemoveAll();
    //mTableNodes.Clear();
}

void FTextureCache::ReloadAllTextures() {
    EnumList (FTextureCacheNode, aNode, mNodeList) {
        //Log("~~Reloading Node[%s] BI[%d] (%d)\n", aNode->mTexture->mFileName.c(), aNode->mTexture->mBindIndex, aNode->mBindCount);
        if(aNode->mBindCount > 0) {
            aNode->mTexture->Realize();
            Log("Reloaded [%s] [%d x %d] Ind(%d)\n", aNode->mTexture->mFileName.c(), aNode->mTexture->mWidth,
                aNode->mTexture->mHeight, aNode->mTexture->mBindIndex);
        }
    }
}

void FTextureCache::PrintAllLoadedTextures() {
    
    printf("***\n***\nPrintAllLoadedTextures()\n***\n");
    EnumList(FTextureCacheNode, aNode, mNodeList) {
        if (aNode->mTexture != NULL) {
            if (aNode->mTexture->mBindIndex != -1) {
                printf("In Mem: [%s]\n", aNode->mTexture->mFileName.c());
            }
        }
    }
    
    
}

FTextureCacheNode *FTextureCache::GetNodeForTexture(FTexture *pTexture) {
    FTextureCacheNode *aResult = 0;
    if (pTexture) {
        FFileTableNode *aHashNode = mTableNodes.GetNode(pTexture->mFileName.c());
        FTextureCacheNode *aNode = 0;
        while(aHashNode) {
            aNode = (FTextureCacheNode *)(aHashNode->mObject);
            if(aNode) {
                if(aNode->mTexture == pTexture) {
                    aResult = aNode;
                    break;
                }
            }
            aHashNode = aHashNode->mNext;
        }
    }
    return aResult;
}

void FTextureCache::TextureBindAdd(FTexture *pTexture) {
    if (pTexture) {
        FTextureCacheNode *aNode = GetNodeForTexture(pTexture);
        if (aNode) {
            aNode->mBindCount++;
        }
    }
}

void FTextureCache::TextureBindRemove(FTexture *pTexture) {
    if (pTexture) {
        FTextureCacheNode *aNode = GetNodeForTexture(pTexture);
        if (aNode) {
            if (aNode->mBindCount > 0) {
                aNode->mBindCount--;
                if (aNode->mBindCount <= 0) {
                    //Log("Remove [%s] Has %d Binds!\n", pTexture->mFileName.c(), aNode->mBindCount);
                    aNode->mTexture->Unload();
                    
                    
                    
                    //mTableNodes.Remove(aNode->mTexture->mFileName.c());
                    //aNode->mTexture->Unload();
                    //delete aNode;
                    
                }
            }
        }
    }
}

