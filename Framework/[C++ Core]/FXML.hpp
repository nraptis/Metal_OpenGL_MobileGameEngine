// (C) 2006-2009 Nick Rapis

#include "FString.hpp"
#include "FColor.hpp"

#ifndef FRAMEWORK_XML_H
#define FRAMEWORK_XML_H

#define EnumTags(_tag,_subtag_name)for(FXMLTag **_enum_start=(FXMLTag**)_tag->mTags.mElement,**_enum_end=((_tag->mTags.mCount > 0)?((FXMLTag**)(&(_tag->mTags.mElement[_tag->mTags.mCount]))) : ((FXMLTag**)0)),*_subtag_name=((_tag->mTags.mCount > 0)?(*_enum_start):((FXMLTag*)0));_subtag_name!=((FXMLTag*)0);_subtag_name=(++_enum_start<_enum_end)?*_enum_start:NULL)

#define EnumParams(_tag,_param_name)for(FXMLParameter **_enum_start=(FXMLParameter**)_tag->mParameters.mElement,**_enum_end=((_tag->mParameters.mCount > 0)?((FXMLParameter**)(&(_tag->mParameters.mElement[_tag->mParameters.mCount]))):((FXMLParameter**)0)),*_param_name=((_tag->mParameters.mCount > 0)?(*_enum_start):((FXMLParameter*)0));_param_name!=((FXMLParameter*)0);_param_name=(++_enum_start<_enum_end)?*_enum_start:NULL)

#define EnumTagsMatching(_tag,_subtag_name,_name)EnumTags(_tag,_subtag_name)if(_subtag_name->mName&&_name)if(strcmp(_subtag_name->mName,_name)==0)
#define EnumParamsMatching(_tag,_param_name,_name)EnumParams(_tag,_param_name)if(strcmp(_param_name->mName,_name)==0)

#define XML_VARIABLE_START(c) (((c>='a'&&c<='z')||(c>='A'&&c<='Z'))||c=='_'||c=='$')
#define XML_VARIABLE_BODY(c) (((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9'))||c=='_'||c=='$')

class FXMLElement {
public:
	FXMLElement() { mName=0;mValue=0; }
	virtual         ~FXMLElement(){delete[]mName;mName=0;delete[]mValue;mValue=0;}
    
    void            SetName(char *pName);
    void            SetName(const char *pName){SetName((char*)pName);}
    
    void            SetValue(char *pValue);
    void            SetValue(const char *pValue){SetValue((char*)pValue);}
    
	char            *mName;
	char            *mValue;
};

class FXMLElementList
{
public:
	FXMLElementList(){mElement=0;mCount=0;mSize=0;}
	~FXMLElementList(){Clear();}
	void					Clear();
	void					operator += (FXMLElement *theElement);
	inline FXMLElement		*operator[](int theSlot){if(theSlot>=0&&theSlot<mCount)return mElement[theSlot];else return 0;}
	FXMLElement				**mElement;
	int						mCount;
	int						mSize;
};


class FXMLParameter : public FXMLElement
{
public:
	
    FXMLParameter(const char *pName=0, const char *pValue=0){FXMLElement();mName=0;mValue=0;FXMLElement();SetName(pName);SetValue(pValue);}
    
};

class FXMLTag : public FXMLElement
{
public:
    FXMLTag(const char *pName=0, const char *pValue=0){FXMLElement();mName=0;mValue=0;FXMLElement();SetName(pName);SetValue(pValue);}
    
	virtual				~FXMLTag(){delete[]mName;delete[]mValue;mName=0;mValue=0;}
	inline void			operator += (FXMLTag *theTag){mTags += theTag;}
	inline void			operator += (FXMLParameter *theParam){mParameters += theParam;}
	
	char				*GetParamValue(char *pName, const char*pDefault=0);
	inline char			*GetParamValue(const char *pName, const char*pDefault=0){return GetParamValue((char*)pName);}
	inline char			*GetParamValue(FString pName, const char*pDefault=0){return GetParamValue((char*)pName.c());}
    
    char				*GetSubtagValue(char *pName, const char*pDefault=0);
	inline char			*GetSubtagValue(const char *pName, const char*pDefault=0){return GetSubtagValue((char*)pName);}
	inline char			*GetSubtagValue(FString pName, const char*pDefault=0){return GetSubtagValue((char*)pName.c());}
    
    void                AddTag(const char* pName, const char* pValue);
    void                AddParam(const char* pName, const char* pValue);
    
    void                AddParamInt(const char* pName, int pInt);
	void                AddParamFloat(const char* pName, float pFloat);
	void                AddParamSafeFloat(const char* pName, float pFloat);
    void                AddParamBool(const char* pName, bool pBool);
    void                AddParamChar(const char* pName, char pChar);

	void                AddTagSafeColor(const char* pName, FColor *pColor);

	void                ReadTagSafeColor(const char* pName, FColor *pColor);
	void                ReadTagSafeColor(const char* pName, FColor *pColor, FColor *pDefaultColor);
    
	int                 GetParamInt(const char* pName);
	float               GetParamFloat(const char* pName);
	float               GetParamSafeFloat(const char* pName);
	bool                GetParamBool(const char* pName);
	char                GetParamChar(const char* pName);
    
	int                 GetParamInt(const char* pName, int pDefault);
	float               GetParamFloat(const char* pName, float pDefault);
	float               GetParamSafeFloat(const char* pName, float pDefault);
	bool                GetParamBool(const char* pName, bool pDefault);
	char                GetParamChar(const char* pName, char pDefault);
    
	FXMLElementList		mTags;
	FXMLElementList		mParameters;
};

class FXML
{
public:
    
	FXML();
	~FXML();
	
	void				Load(char *pFile);
	inline void			Load(const char *pFile){Load((char*)pFile);}
	inline void			Load(FString pFile){Load(pFile.c());}
    
    
    void                Save(char *pFile);
    inline void			Save(const char *pFile){Save((char*)pFile);}
	inline void			Save(FString pFile){Save(pFile.c());}
	
	void				Parse(char *pData, int pLength);
	
	void				Print();
	void				Export();
	void				Export(int depth, FXMLTag *tag);
	void				ExportAppend(char *pText);
	inline void			ExportAppend(const char *pText){ExportAppend((char*)pText);}
    
	FXMLTag				*GetNestedTag1(char *pName1);
	inline FXMLTag		*GetNestedTag1(FString pName1){return GetNestedTag1(pName1.c());}
	
	FXMLTag				*GetNestedTag2(char *pName1, char *pName2);
	inline FXMLTag		*GetNestedTag2(FString pName1, FString pName2){return GetNestedTag2(pName1.c(),pName2.c());}
	
	FXMLTag				*GetNestedTag3(char *pName1, char *pName2, char *pName3);
	inline FXMLTag		*GetNestedTag3(FString pName1, FString pName2, FString pName3){return GetNestedTag3(pName1.c(),pName2.c(),pName3.c());}
	
	FXMLTag				*GetNestedTag4(char *pName1, char *pName2, char *pName3, char *pName4);
	inline FXMLTag		*GetNestedTag4(FString pName1, FString pName2, FString pName3, FString pName4){return GetNestedTag4(pName1.c(),pName2.c(),pName3.c(),pName4.c());}
    
	void				Clear();
	
	inline FXMLTag		*GetRoot(){return mRoot;}
	
	FXMLTag				*mRoot;
    
	char				*mOutput;
	int					mOutputSize;
	int					mOutputLength;
};

char *SkipQuote(char *pSeek);
char *SkipComment(char *pSeek);

#endif
