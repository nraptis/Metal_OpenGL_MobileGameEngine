//
//  FTextureCache.h
//  FleetGL
//
//  Created by Nick Raptis on 2/9/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_TEXTURE_CACHE_H
#define FRAMEWORK_TEXTURE_CACHE_H

#include "FFileTable.hpp"
#include "FSprite.hpp"
#include "FImage.hpp"
#include "FTexture.hpp"

class FTextureCacheNode
{
public:
    FTextureCacheNode(FTexture *pTexture);
    virtual ~FTextureCacheNode();
    
    
    //FImage                                      *mImage;
    
    FTextureCacheNode                           *mNextNode;
    FTexture                                    *mTexture;
    
    //FString                                     mName;
    
    int                                         mBindCount;
};

class FTextureCache
{
public:
    
    FTextureCache();
    virtual ~FTextureCache();
    
    FTextureCacheNode                           *GetNodeForTexture(FTexture *pTexture);
    
    FTexture                                    *GetTexture(const char *pFileName);
    inline FTexture                             *GetTexture(char *pFileName){return GetTexture((const char *)pFileName);}
    inline FTexture                             *GetTexture(FString pFileName){return GetTexture((const char *)(pFileName.c()));}
    
    void                                        UnloadAllTextures();
    void                                        ReloadAllTextures();
    
    void                                        TextureBindAdd(FTexture *pTexture);
    void                                        TextureBindRemove(FTexture *pTexture);
    
    FFileTable                                  mTableNodes;
    FList                                       mNodeList;
    
    bool                                        mAutoMode;
    
};


#endif












