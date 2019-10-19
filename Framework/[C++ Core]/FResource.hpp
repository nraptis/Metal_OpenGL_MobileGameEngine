//
//  FResource.h
//  2015 Gnome Launcher
//
//  Created by Nick Raptis on 12/12/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef ___015_Fleet_XP__FResource__
#define ___015_Fleet_XP__FResource__

#define RESOURCE_TYPE_UNKNOWN 0
#define RESOURCE_TYPE_DIRECTORY 1
#define RESOURCE_TYPE_IMAGE 2
#define RESOURCE_TYPE_AUDIO 4

#define RESOURCE_TYPE_MODEL_OBJ 8
#define RESOURCE_TYPE_MODEL_DATA 16


#define RESOURCE_TYPE_SOUND_EFFECT 64
#define RESOURCE_TYPE_MUSIC 128

#define RESOURCE_TYPE_BINARY 256
#define RESOURCE_TYPE_CONFIG 512
#define RESOURCE_TYPE_BUNDLE 1024

#define RESOURCE_TYPE_VIDEO 2048
#define RESOURCE_TYPE_XMLJSON 4096
//#define RESOURCE_TYPE_ARCHIVE 1024
//#define RESOURCE_TYPE_FILE 2048

#include "FString.hpp"
#include "FList.hpp"
#include "FFileTable.hpp"


class FResource
{
public:
    FResource();
    virtual ~FResource();
    
    FString                                     mName;
    FString                                     mExtension;
    
    int                                         mResourceType;

    //FResource                                   *mNext;
};

class FResourceManager
{
public:
	FResourceManager();
	virtual ~FResourceManager();
    
    FResource                                   *AddResource(const char *pResourcePath, bool pPrint=false);
    inline FResource                            *AddResource(char *pResourcePath, bool pPrint=false){return AddResource((const char *)pResourcePath, pPrint);}
    inline FResource                            *AddResource(FString pResourcePath, bool pPrint=false){return AddResource((const char *)(pResourcePath.c()), pPrint);}

	const char                                  *GetResourcePath(const char *pFileName);
    const char									*GetResourcePathOfType(const char *pFileName, int pType);
    const char									*GetResourcePathImage(const char *pFileName);
    const char									*GetResourcePathSound(const char *pFileName);
    const char									*GetResourcePathMusic(const char *pFileName);
	const char									*GetResourcePathFile(const char *pFileName);
    
	const char									*GetNextResourcePath();
    
    static FString                              ResourceName(const char *pFilePath);
    
    void                                        GetAllFiles(FList *pList); //List of FFileTableNode...
    void                                        GetAllFilesWithExtension(FList *pList, const char *pExtension); //List of FFileTableNode...
    void                                        GetAllFilesContainingText(FList *pList, const char *pText); //List of FFileTableNode...
    void                                        GetAllFilesContainingTextWithExtension(FList *pList, const char *pText, const char *pExtension); //List of FFileTableNode...
    
    
    
    
    
	FList										mMatchingResourceList;
	int											mMatchingResourceIndex;
    
    FList										mResourceList;
    
    FList                                       mSearchResultsFilter;
    FList                                       mSearchResults;
    int                                         mSearchIndex;
    
    FFileTable                                  mTable;
    
    void                                        Print();
    
};

extern FResourceManager gRes;

#endif
