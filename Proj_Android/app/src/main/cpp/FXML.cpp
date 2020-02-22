
#include "FXML.hpp"
#include "FFile.hpp"
#include "FString.hpp"
#include "core_includes.h"

FXML::FXML() {
	mRoot=0;
	mOutput=0;
	mOutputSize=0;
	mOutputLength=0;
}

FXML::~FXML() {
	Clear();
}

void FXML::Clear() {
	if(mRoot)delete mRoot;
	mRoot=0;
	delete[]mOutput;
	mOutput=0;
	mOutputSize=0;
	mOutputLength=0;
}



char *SkipQuote(char *pSeek) {
	char *aSeek=pSeek;
	if(*aSeek=='\"')
	{
		aSeek++;
		while(*aSeek&&*aSeek!='\"')aSeek++;
	}
	return aSeek;
}

//*pSeek= ! or ?
//returns *'>' if not error..
char *SkipComment(char *pSeek) {
	char *aSeek=pSeek;
	while(*aSeek&&*aSeek<=32)aSeek++;
		int aBraceDepth=1;
		START_SKIP_COMMENT:
		while(*aSeek&&
			  *aSeek!='<'&&
			  *aSeek!='\"'&&
			  *aSeek!='>')aSeek++;
	
		if(*aSeek=='\"')
		{
			aSeek=SkipQuote(aSeek);
			if(*aSeek=='\"')aSeek++;
			goto START_SKIP_COMMENT;
		}
		if(*aSeek=='<')
		{
			aSeek++;
			aBraceDepth++;
			goto START_SKIP_COMMENT;
		}
		if(*aSeek=='>')
		{
			if(aBraceDepth!=1)
			{
				aSeek++;
				aBraceDepth--;
				goto START_SKIP_COMMENT;
			}
		}
	
	return aSeek;
}

void FXML::ExportAppend(char *pText)
{
	if(!pText)return;
	int aStrLen=0;
	char *aPtr=pText;
	while(*aPtr)aPtr++;
	aStrLen = (int)(aPtr - pText);
	
	int aLen=mOutputLength+aStrLen;
	if(aLen>=mOutputSize)
	{
		mOutputSize=aLen+aLen/2+1;
		char *aNew=new char[mOutputSize+1];
		memcpy(aNew,mOutput,mOutputLength);
		delete[]mOutput;
		mOutput=aNew;
	}
	//Log("Length -> %d  [%d]\n", mOutputLength, mOutputLength+aStrLen, mOutputSize);
	memcpy(mOutput+mOutputLength,pText,aStrLen);
	mOutput[aLen]=0;
	mOutputLength=aLen;
}

void FXML::Export() {
	delete[]mOutput;
	mOutput=0;
	mOutput=new char[1];
	mOutput[0]=0;
	mOutputLength=0;
	mOutputSize=0;
	if(mRoot)Export(0,mRoot);
}

void FXML::Export(int depth, FXMLTag *tag) {
	if(!tag)return;
	
	for(int aTabIndex=0;aTabIndex<depth;aTabIndex++)ExportAppend("\t");
	
	ExportAppend("<");
	ExportAppend(tag->mName);
	
	for(int i=0;i<tag->mParameters.mCount;i++)
	{
		//if(i != tag->mParameters.mCount-1)
		ExportAppend(" ");
		ExportAppend(tag->mParameters.mElement[i]->mName);
		ExportAppend("=\"");
		ExportAppend(tag->mParameters.mElement[i]->mValue);
		ExportAppend("\"");
	}

	
	if(tag->mValue)
	{
		ExportAppend(">");
		ExportAppend(tag->mValue);
		ExportAppend("</");
		ExportAppend(tag->mName);
		ExportAppend(">\n");
	}
	else
	{
		if(tag->mTags.mCount>0)
		{
			ExportAppend(">");
			ExportAppend("\n");
			for(int i=0;i<tag->mTags.mCount;i++)
			{
				Export(depth+1,(FXMLTag*)tag->mTags.mElement[i]);
			}
			for(int aTabIndex=0;aTabIndex<depth;aTabIndex++)ExportAppend("\t");
			ExportAppend("</");
			ExportAppend(tag->mName);
			//Log("Tag... [%s]\n", tag->mName);
			ExportAppend(">\n");
		}
		else
		{
			ExportAppend("/>\n");
		}
	}
}

void FXML::Print()
{
	Export();
	if(mOutput)
    {
        Log((const char*)mOutput);
        
        //Log(mOutput);
        
    }
}

void FXML::Save(char *pFile)
{
    Export();
    if(mOutput)
    {
        FFile aFile;
        aFile.Write(mOutput, mOutputLength);
        aFile.Save(pFile);
    }
}

void FXML::Load(char *pFile) {
	FFile aFile;
    aFile.Load(pFile);
    
    if (aFile.mLength <= 0) {
        bool aBlock = false;
        while (aBlock == false) {
            aBlock = true;
            
            FString aFileName = FString(pFile);
            aFileName.RemoveExtension();
            
            aFile.Load(aFileName + FString(".xml"));
            if (aFile.mLength > 0) { break; }
            
            aFile.Load(aFileName + FString(".XML"));
            if (aFile.mLength > 0) { break; }
            
            aFile.Load(aFileName + FString(".csv"));
            if (aFile.mLength > 0) { break; }
            
            aFile.Load(aFileName + FString(".CSV"));
            if (aFile.mLength > 0) { break; }
            
            aFileName.RemovePath();
            aFile.Load(aFileName + FString(".xml"));
            if (aFile.mLength > 0) { break; }
            
            aFile.Load(aFileName + FString(".XML"));
            if (aFile.mLength > 0) { break; }
            
            aFile.Load(aFileName + FString(".csv"));
            if (aFile.mLength > 0) { break; }
            
            aFile.Load(aFileName + FString(".CSV"));
            if (aFile.mLength > 0) { break; }
        }
    }
	Parse((char*)aFile.mData, aFile.mLength);
}

void FXML::Parse(char *pData, int pLength) {
	Clear();
    
	if (!pData || (pLength<0)) return;
	
	int aError=0;
	
	int aStackCount=0;
	int aStackSize=1;
	FXMLTag**aStack=new FXMLTag*[aStackSize];
	FXMLTag**aNewStack;
	FXMLTag*aParent;
	FXMLTag*aTag=0;
	FXMLParameter *aParam;
	
	aStack[0]=0;
	
	char *aName=0;
	char *aValue=0;
	
	int aLength;
	
	//bool aFoundEscape;
	
	char *aHold;
	char *aCheck;
	
	char *aData=new char[pLength+1];
	aData[pLength]=0;
	memcpy(aData,pData,pLength);
	
	char *aSeek=aData;
	
	//Search for initial open bracket...
FIND_ROOT_TAG:
	while(*aSeek&&*aSeek<=32)aSeek++;
	if(*aSeek!='<')goto XML_PARSE_ERROR;
	aSeek++;
	
	//Skip White Space..
	while(*aSeek&&*aSeek<=32)aSeek++;
	if(*aSeek==0)goto XML_PARSE_ERROR;
	if(*aSeek=='!'||*aSeek=='?')
	{
		aSeek=SkipComment(aSeek);
		if(*aSeek!='>')goto XML_PARSE_ERROR;
		aSeek++;
		goto FIND_ROOT_TAG;
	}
	
	//Tag Name
	if(!XML_VARIABLE_START(*aSeek))goto XML_PARSE_ERROR;
	aHold=aSeek;
	aSeek++;
	while(*aSeek&&XML_VARIABLE_BODY(*aSeek))aSeek++;
	if(*aSeek==0)goto XML_PARSE_ERROR;
	aLength=aSeek-aHold;
	aName=new char[aLength+1];
	memcpy(aName,aHold,aLength);
	aName[aLength]=0;
	//End Tag Name
	
	//Create the tag..
	mRoot=new FXMLTag();
	mRoot->mName=aName;
	aName=0;
	
	//Keep on parsing it I guess.. We need to look for parameters...
FIND_ROOT_PARAMETERS:
	//Skip white space..
	while(*aSeek&&*aSeek<=32)aSeek++;
	if(*aSeek==0)goto XML_PARSE_ERROR;
	if(XML_VARIABLE_START(*aSeek))
	{
		//Parameter Name
		aHold=aSeek;
		aSeek++;
		while(*aSeek&&XML_VARIABLE_BODY(*aSeek))aSeek++;
		if(*aSeek==0)goto XML_PARSE_ERROR;
		aLength=(int)(aSeek-aHold);
		aName=new char[aLength+1];
		memcpy(aName,aHold,aLength);
		aName[aLength]=0;
		
		//=
		while(*aSeek&&*aSeek<=32)aSeek++;
		if(*aSeek!='=')goto XML_PARSE_ERROR;
		aSeek++;
		while(*aSeek&&*aSeek<=32)aSeek++;
		//Stuff in quotes
		if(*aSeek!='\"')goto XML_PARSE_ERROR;
		aSeek++;
		aHold=aSeek;
		while(*aSeek&&*aSeek!='\"')aSeek++;
		//endquotes
		if(*aSeek!='\"')goto XML_PARSE_ERROR;
		aLength=(int)(aSeek-aHold);
		aValue=new char[aLength+1];
		aValue[aLength]=0;
		memcpy(aValue,aHold,aLength);
		
		aParam=new FXMLParameter();
		aParam->mName=aName;
		aParam->mValue=aValue;
		
		aName=0;
		aValue=0;
		
		*mRoot+=aParam;
		
		aSeek++;
		
		goto FIND_ROOT_PARAMETERS;
	}
	
	if(*aSeek=='/')
	{
		aSeek++;
		while(*aSeek&&*aSeek<=32)aSeek++;
		if(*aSeek!='>')goto XML_PARSE_ERROR;
		//Ok, we had a single self-terminating root tag
		goto SUCCESS;
	}
	
	if(*aSeek!='>')goto XML_PARSE_ERROR;
	aSeek++;
    
	aStack[0]=mRoot;
	aStackCount=1;
	aParent=mRoot;
    
BEGIN_STACK_LOOP:
	
	if(aStackCount<=0)
	{
        //
		//Could eventually eliminate illegal trailing tags here...
        //
        
		goto SUCCESS;
	}
	
	aParent=aStack[aStackCount-1];
	
	while(*aSeek&&*aSeek<=32)aSeek++;
	if(*aSeek=='>'||*aSeek==0)goto XML_PARSE_ERROR;
	if(*aSeek=='<')
	{
		aSeek++;
		while(*aSeek&&*aSeek<=32)aSeek++;
		
		if(*aSeek=='!'||*aSeek=='?')
		{
			aSeek=SkipComment(aSeek);
			if(*aSeek!='>')goto XML_PARSE_ERROR;
			aSeek++;
			goto BEGIN_STACK_LOOP;
		}
		
		if(*aSeek=='/')
		{
			aSeek++;
			while(*aSeek&&*aSeek<=32)aSeek++;
			if(!XML_VARIABLE_START(*aSeek))goto XML_PARSE_ERROR;
			
			aHold=aSeek;
			aSeek++;
			while(*aSeek&&XML_VARIABLE_BODY(*aSeek))aSeek++;
			if(*aSeek==0)goto XML_PARSE_ERROR;
			
			aCheck=aParent->mName;
			
			while(aHold<aSeek&&*aCheck&&*aHold==*aCheck)
			{
				aCheck++;
				aHold++;
			}
			
			if(*aCheck||(aHold<aSeek))goto XML_PARSE_ERROR;
			
			while(*aSeek&&*aSeek<=32)aSeek++;
			
			if(*aSeek!='>')goto XML_PARSE_ERROR;
			aSeek++;//move past end brace..
			
			//
			//We pop the stack when we get a closing tag...
			//
			aStackCount--;
			goto BEGIN_STACK_LOOP;
		}
		//non-closing tag it seems
		else
		{
			if(aParent->mValue)goto XML_PARSE_ERROR;
			
			while(*aSeek&&*aSeek<=32)aSeek++;
			if(!XML_VARIABLE_START(*aSeek))goto XML_PARSE_ERROR;
			aHold=aSeek;
			aSeek++;
			while(*aSeek&&XML_VARIABLE_BODY(*aSeek))aSeek++;
			if(*aSeek==0)goto XML_PARSE_ERROR;
			
			aLength=(int)(aSeek-aHold);
			aName=new char[aLength+1];
			memcpy(aName,aHold,aLength);
			aName[aLength]=0;
			
			aTag=new FXMLTag();
			aTag->mName=aName;
			*aParent+=aTag;
			
			//We always add our opening tag to the stack? k.
			if(aStackCount==aStackSize)
			{
				aStackSize=aStackSize+aStackSize+1;
				aNewStack=new FXMLTag*[aStackSize];
				for(int i=0;i<aStackCount;i++)aNewStack[i]=aStack[i];
				delete[]aStack;
				aStack=aNewStack;
			}
			aStack[aStackCount++]=aTag;
			
			aName=0;
			
			
			
		FIND_PARAMETERS:
			//Skip white space..
			while(*aSeek&&*aSeek<=32)aSeek++;
			if(*aSeek==0)goto XML_PARSE_ERROR;
			if(XML_VARIABLE_START(*aSeek))
			{
				//Parameter Name
				aHold=aSeek;
				aSeek++;
				while(*aSeek&&XML_VARIABLE_BODY(*aSeek))aSeek++;
				if(*aSeek==0)goto XML_PARSE_ERROR;
				aLength=(int)(aSeek-aHold);
				aName=new char[aLength+1];
				memcpy(aName,aHold,aLength);
				aName[aLength]=0;
				
				//=
				while(*aSeek&&*aSeek<=32)aSeek++;
				if(*aSeek!='=')goto XML_PARSE_ERROR;
				aSeek++;
				while(*aSeek&&*aSeek<=32)aSeek++;
				if(*aSeek!='\"')goto XML_PARSE_ERROR;
				aSeek++;
				aHold=aSeek;
				while(*aSeek&&*aSeek!='\"')aSeek++;
				if(*aSeek!='\"')goto XML_PARSE_ERROR;
				aLength=(int)(aSeek-aHold);
				aValue=new char[aLength+1];
				aValue[aLength]=0;
				memcpy(aValue,aHold,aLength);
				
				aParam=new FXMLParameter();
				aParam->mName=aName;
				aParam->mValue=aValue;
				
				//if()
				
				aName=0;
				aValue=0;
				
				*aTag+=aParam;
				
				aSeek++;
				
				goto FIND_PARAMETERS;
			}
			
			if(*aSeek=='/')
			{
				aSeek++;
				while(*aSeek&&*aSeek<=32)aSeek++;
				if(*aSeek!='>')goto XML_PARSE_ERROR;
				aStackCount--;
			}
			
			if(*aSeek!='>')goto XML_PARSE_ERROR;
			aSeek++;
			goto BEGIN_STACK_LOOP;
		}
	}
    
	if(aParent->mTags.mCount>0)goto XML_PARSE_ERROR;
	
	while(*aSeek&&*aSeek<32)aSeek++;
	if(*aSeek==0)goto XML_PARSE_ERROR;
	
	aHold=aSeek;
	while(*aSeek&&*aSeek!='<')aSeek++;
	if(*aSeek==0)goto XML_PARSE_ERROR;
	
	aLength=(int)(aSeek-aHold);
	
	aValue=new char[aLength+1];
	memcpy(aValue,aHold,aLength);
	memset(aValue,0,aLength);
	aValue[aLength]=0;
	aCheck=aValue;
	while(aHold<aSeek)
	{
		while(aHold<aSeek
			  //&&*aHold!='&'
			  )*aCheck++=*aHold++;
		/*if(*aHold=='&')
		 {
		 aFoundEscape=false;
		 if(aHold+5<aSeek)
		 {
		 if(*(aHold+1)=='a'&&
		 *(aHold+2)=='p'&&
		 *(aHold+3)=='o'&&
		 *(aHold+4)=='s'&&
		 *(aHold+5)==';')
		 {
		 *aCheck++='\'';
		 aFoundEscape=true;
		 aHold+=6;
		 }
		 else if(*(aHold+1)=='q'&&
		 *(aHold+2)=='u'&&
		 *(aHold+3)=='o'&&
		 *(aHold+4)=='t'&&
		 *(aHold+5)==';')
		 {
		 *aCheck++='\"';
		 aFoundEscape=true;
		 aHold+=6;
		 }
		 }
		 if(aHold+4<aSeek&&aFoundEscape==false)
		 {
		 if(*(aHold+1)=='a'&&
		 *(aHold+2)=='m'&&
		 *(aHold+3)=='p'&&
		 *(aHold+4)==';')
		 {
		 *aCheck++='&';
		 aFoundEscape=true;
		 aHold+=5;
		 }
		 }
		 if(aHold+3<aSeek&&aFoundEscape==false)
		 {
		 if(*(aHold+1)=='g'&&
		 *(aHold+2)=='t'&&
		 *(aHold+3)==';')
		 {
		 *aCheck++='>';
		 aFoundEscape=true;
		 aHold+=4;
		 }
		 else if(*(aHold+1)=='l'&&
		 *(aHold+2)=='t'&&
		 *(aHold+3)==';')
		 {
		 *aCheck++='<';
		 aFoundEscape=true;
		 aHold+=4;
		 }
		 }
		 if(!aFoundEscape)
		 {
		 //goto XML_PARSE_ERROR;
		 
		 //How about.. if it's not an escape sequence
		 //we just allow the ampersand lol..
		 *aCheck++=*aHold++;
		 }
		 }*/
	}
	while(aCheck>aValue&&*aCheck<32)
	{
		*aCheck--=0;
	}
	aParent->mValue=aValue;
	aValue=0;
	goto BEGIN_STACK_LOOP;
	
XML_PARSE_ERROR:
	Clear();
	Log("***FXML Parse Error***\n");
	aError=1;
SUCCESS:
	delete[]aData;
	delete[]aStack;
	delete[]aName;
	delete[]aValue;
	if(!aError)
	{
		//Log("FXML Parse Success :(\n");
	}
}


FXMLTag *FXML::GetNestedTag1(char *pName1)
{
	EnumTagsMatching(mRoot,aSubTag1,pName1)
	{
		return aSubTag1;
	}   
	return 0;
}

FXMLTag *FXML::GetNestedTag2(char *pName1, char *pName2)
{
	EnumTagsMatching(mRoot,aSubTag1,pName1)
	{
		EnumTagsMatching(aSubTag1,aSubTag2,pName2)
		{
			return aSubTag2;
		}
	}
	return 0;
}

FXMLTag *FXML::GetNestedTag3(char *pName1, char *pName2, char *pName3)
{
	EnumTagsMatching(mRoot,aSubTag1,pName1)
	{
		EnumTagsMatching(aSubTag1,aSubTag2,pName2)
		{
			EnumTagsMatching(aSubTag2,aSubTag3,pName3)
			{
				return aSubTag3;
			}
		}
	}
	return 0;
}

FXMLTag *FXML::GetNestedTag4(char *pName1, char *pName2, char *pName3, char *pName4)
{
	EnumTagsMatching(mRoot,aSubTag1,pName1)
	{
		EnumTagsMatching(aSubTag1,aSubTag2,pName2)
		{
			EnumTagsMatching(aSubTag2,aSubTag3,pName3)
			{
				EnumTagsMatching(aSubTag3,aSubTag4,pName4)
				{
					return aSubTag4;
				}
			}
		}
	}   
	return 0;
}


void FXMLElementList::Clear()
{
	for(int i=0;i<mCount;i++)delete mElement[i];
	delete[]mElement;
	mElement=0;
	mCount=0;
}

void FXMLElementList::operator += (FXMLElement *theElement)
{
	if(mCount==mSize)
	{
		mSize=mSize+(mSize>>1)+1;
		FXMLElement**aElement=new FXMLElement*[mSize];
		for(int i=0;i<mCount;i++)aElement[i]=mElement[i];
		delete[]mElement;
		mElement=aElement;
	}
	mElement[mCount++]=theElement;
}

char *FXMLTag::GetParamValue(char *pName, const char*pDefault)
{
	EnumParamsMatching(this,aCheck,pName)return aCheck->mValue;
	return (char*)pDefault;
}



char *FXMLTag::GetSubtagValue(char *pName, const char*pDefault)
{
    EnumTagsMatching(this, aCheck, pName)return aCheck->mValue;
	return (char*)pDefault;
}



void FXMLElement::SetName(char *pString)
{
    char *aString = 0;
    if(pString)
    {
        char *aPtr=(char*)pString;
        while(*aPtr)aPtr++;
        int aLength = (int)(aPtr-(char*)pString);
        aString = new char[aLength+1];
        aPtr=aString;
        while(*pString)
        {
            *aString = *pString;
            pString++;
            aString++;
        }
        aString=aPtr;
        aString[aLength]=0;
    }
    mName=aString;
}

void FXMLElement::SetValue(char *pString)
{
    char *aString = 0;
    if(pString)
    {
        char *aPtr=(char*)pString;
        while(*aPtr)aPtr++;
        int aLength = (int)(aPtr-(char*)pString);
        aString = new char[aLength+1];
        aPtr=aString;
        while(*pString)
        {
            *aString = *pString;
            pString++;
            aString++;
        }
        aString=aPtr;
        aString[aLength]=0;
    }
    mValue=aString;
}

void FXMLTag::AddParam(const char* pName, const char* pValue)
{
    FXMLParameter *aParam = new FXMLParameter();
    
    aParam->SetName(pName);
    aParam->SetValue(pValue);
    
    *this += aParam;
}

void FXMLTag::AddTag(const char* pName, const char* pValue)
{
    FXMLTag *aTag=new FXMLTag();
    
    aTag->SetName(pName);
    aTag->SetValue(pValue);
    
    *this += aTag;
}


void FXMLTag::AddTagSafeColor(const char* pName, FColor *pColor)
{
	float aRed = 1.0f;
	float aGreen = 1.0f;
	float aBlue = 1.0f;
	float aAlpha = 1.0f;

	if(pColor)
	{
		aRed = pColor->mRed;
		aGreen = pColor->mGreen;
		aBlue = pColor->mBlue;
		aAlpha = pColor->mAlpha;
	}

	FXMLTag *aTag = new FXMLTag(pName);
	aTag->AddParamSafeFloat("r", aRed);
	aTag->AddParamSafeFloat("g", aGreen);
	aTag->AddParamSafeFloat("b", aBlue);
	aTag->AddParamSafeFloat("a", aAlpha);
	
	*this += aTag;
}


void FXMLTag::ReadTagSafeColor(const char* pName, FColor *pColor)
{
	FColor aDefault;
	ReadTagSafeColor(pName, pColor, &aDefault);
}

void FXMLTag::ReadTagSafeColor(const char* pName, FColor *pColor, FColor *pDefaultColor)
{
	float aRed = 1.0f;
	float aGreen = 1.0f;
	float aBlue = 1.0f;
	float aAlpha = 1.0f;

	if(pDefaultColor)
	{
		aRed   = pDefaultColor->mRed;
		aGreen = pDefaultColor->mGreen;
		aBlue  = pDefaultColor->mBlue;
		aAlpha = pDefaultColor->mAlpha;
	}

	EnumTagsMatching(this, aTag, pName)
	{
		aRed   = aTag->GetParamSafeFloat("r", aRed  );
		aGreen = aTag->GetParamSafeFloat("g", aGreen);
		aBlue  = aTag->GetParamSafeFloat("b", aBlue );
		aAlpha = aTag->GetParamSafeFloat("a", aAlpha);
	}

	if(pColor)
	{
		pColor->mRed   = aRed;
		pColor->mGreen = aGreen;
		pColor->mBlue  = aBlue;
		pColor->mAlpha = aAlpha;
	}
}


void FXMLTag::AddParamInt(const char* pName, int pInt)
{
    AddParam(pName, FString(pInt).c());
}

void FXMLTag::AddParamFloat(const char* pName, float pFloat)
{
    AddParam(pName, FString(pFloat).c());
}

void FXMLTag::AddParamSafeFloat(const char* pName, float pFloat)
{
	AddParamInt(pName, FloatToInt(pFloat));
}

void FXMLTag::AddParamBool(const char* pName, bool pBool)
{
    AddParam(pName, FString(pBool).c());
}

void FXMLTag::AddParamChar(const char* pName, char pChar)
{
    AddParam(pName, FString(pChar).c());
}

int FXMLTag::GetParamInt(const char* pName)
{
	return GetParamInt(pName, 0);
}

float FXMLTag::GetParamFloat(const char* pName)
{
	return GetParamFloat(pName, 0.0f);
}

float FXMLTag::GetParamSafeFloat(const char* pName)
{
	return GetParamSafeFloat(pName, 0.0f);
}

bool FXMLTag::GetParamBool(const char* pName)
{
	return GetParamBool(pName, false);
}

char FXMLTag::GetParamChar(const char* pName)
{
	return GetParamChar(pName, 0);
}



int FXMLTag::GetParamInt(const char* pName, int pDefault)
{
	int aResult = pDefault;
	EnumParamsMatching(this, aCheck, pName)aResult = FString(aCheck->mValue).ToInt();
	return aResult;
}

float FXMLTag::GetParamFloat(const char* pName, float pDefault)
{
	float aResult = pDefault;
	EnumParamsMatching(this, aCheck, pName)aResult = FString(aCheck->mValue).ToFloat();
	return aResult;
}

float FXMLTag::GetParamSafeFloat(const char* pName, float pDefault)
{
	float aResult = pDefault;
	EnumParamsMatching(this, aCheck, pName)
	{
		int aData = FString(aCheck->mValue).ToInt();
		aResult = IntToFloat(aData);
	}
	return aResult;
}

bool FXMLTag::GetParamBool(const char* pName, bool pDefault)
{
	bool aResult = pDefault;
	EnumParamsMatching(this, aCheck, pName)aResult = FString(aCheck->mValue).ToBool();
	return aResult;
}

char FXMLTag::GetParamChar(const char* pName, char pDefault)
{
	char aResult = pDefault;
	EnumParamsMatching(this, aCheck, pName)aResult = FString(aCheck->mValue).ToChar();
	return aResult;
}


