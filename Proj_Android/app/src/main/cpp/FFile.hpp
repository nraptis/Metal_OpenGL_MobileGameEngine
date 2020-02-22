//
//  FFile.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/1/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_FILE_H
#define FRAMEWORK_FILE_H

#include "FString.hpp"
#include "FList.hpp"
#include "FColor.hpp"

class FFile {
public:

    FFile();
    virtual ~FFile();
    
    virtual void		Clear();
	
	void				Size(int pSize);
	
	void				WriteBool(bool pWrite);
    void				WriteChar(char pWrite);
    void				WriteShort(short pWrite);
    void				WriteInt(int pWrite);
    void				WriteFloat(float pWrite);
    
	bool				ReadBool();
	char				ReadChar();
	short				ReadShort();
    int					ReadInt();
	float				ReadFloat();
	
	void				Write(char *write, int theLength);
	void				Write(char *write);

	void				WriteString(char *pString);
    inline void			WriteString(FString pString) { WriteString(pString.c()); }
    inline void			WriteString(const char * pString) { WriteString((char*)pString); }
	FString				ReadString();

    void                WriteColor(FColor pColor);
    FColor              ReadColor();
    
	void				Save(char *pFile=0);
    virtual void		Save(const char *pFile) {Save((char*)pFile); }
	inline void			Save(FString pString) {Save(pString.c()); }
	
	void				Load(char *pFile = 0);
    virtual void		Load(const char *pFile) { Load((char*)pFile); }
	inline void			Load(FString pString) { Load(pString.c()); }
    
    void				LoadDirect(char *pFile=0);

	void				Print();

	char				*MakeFile(char *pFile, bool pMakeDirectory=true);
	char				*GetFile(char *pFile){return MakeFile(pFile,false);}
	
	FString             mFileName;
    
	unsigned char		*mData;

    unsigned int        mLength;
    unsigned int        mCursorRead;
    unsigned int        mCursorWrite;
};

int FloatToInt(float pFloat);
float IntToFloat(int pInt);

#endif
