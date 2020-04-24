#ifndef F_SILLY_STRING_H
#define F_SILLY_STRING_H

//#include <string.h>
//#include <stdarg.h>
//#include <math.h>

#define lower(c)(((c)>=65&&(c)<=90)?(c)+32:(c))

class FList;
class FString
{
public:

	FString();
	FString(const FString &pString);
	FString(char *pString);
	FString(const char *pString);
	FString(int pInt);
	FString(char pChar);
	FString(float pFloat);
	FString(float pFloat, int pDecimals);
	FString(bool pBool);
	~FString();
	
	//
	//Raw character data.
	//Don't alter this unless you know what you're doing!
	//Strings may be sharing char arrays when you set them
	//equal to each other, so try to 
	//
	char							*mData;
	char							*mCursor;
	int								mLength;
	int								mSize;


	void							Size(int pSize);
	static int						Length(const char *pString);// { if(!pString)return 0; const char*aPtr = pString; while (*aPtr)aPtr++; return (int)(aPtr - pString); }
	static int						Length(char *pString){ return Length((const char *)pString); }


	void							Free();
	void							Clear();

    void                            Truncate(int pSize);
    
    void                            RemoveBeforeIndex(int pIndex);
    

	


	//
	//Calculate the length of a character array.
	//[Must be terminated with a null space]
	//
	
	//
	//Convert a FString that represents another data type to the desired data type...
	//
	int								ToInt();
	char							ToChar();
	float							ToFloat();
	void							ToPoint(float &theX, float &theY);
	//inline Point					ToPoint() {Point aPoint;ToPoint(aPoint.mX,aPoint.mY);return aPoint;}
	bool							ToBool();
    

	FString							GetNumber(int thePosition);
    inline FString					GetNumber() { return GetNumber(0); }
    inline FString					GetNextNumber() { return GetNumber((int)(mCursor - mData)); }
    
    inline int						GetNumberI() { FString aString = GetNumber(); return aString.ToInt(); }
    inline int						GetNextNumberI(){FString aString = GetNextNumber(); return aString.ToInt(); }
    
    inline float					GetNumberF() { FString aString = GetNumber(); return aString.ToFloat(); }
    inline float					GetNextNumberF() { FString aString = GetNextNumber(); return aString.ToFloat(); }
    
    
    
    FString							GetLastNumber();
	void							AddCommas();


	//
	//Get the length of the FString nice and quick.
	//
	inline int						Length(){return mLength;}
	inline int						GetLength(){return mLength;}
	
	
	//bool					EndsWith(char *pString);
	//bool					StartsWith(char *pString);
	
	//bool					EqualsStar(char *pString);

	//
	//Honestly, these shouldn't ever be used outside of the FString function...
	//If you set up the char array manually, just use Realize()
	//

	//inline int					GetLen(){return Length(mData);}
	//inline int					Len(){return Length(mData);}
	//inline int					strlen(){return Length(mData);}

	//
	//Some advanced operations for removing all characters from a FString,
	//or removing everything but some characters from a FString.
	//

	void					        Filter(char *theAllowed);
	void					        Filter(FString &theAllowed){Filter(theAllowed.mData);}

	void					        Remove(char *theDisallowed);
	void					        Remove(FString &theDisallowed){Remove(theDisallowed.mData);}

	
	int						        CountCharacter(char c);
	bool					        ContainsDuplicateCharacters();
	
	//
	//{+/-}{.}0-9{.}0-9{.} Where one or none of the decimals exist...
	//
	bool					        IsNumber();

    
    char                            *GetCharArray();
    
	//
	//Get a subString of the FString.
	//
	FString					        GetSubString(int thePosition, int theLength);
	FString					        GetSubString(int thePosition){return GetSubString(thePosition, mLength);}

    
    void                            Reset();
    
	void					        Set(const char *pString);
	void					        Set(char *pString) { Set((const char *)pString); }
	void					        Set(FString &pString);

	void					        Append(char pChar);
	void					        Append(const char *pString);
	void					        Append(FString &pString);
	void					        Append(const char *pString, int pCount);
	void					        Append(char *pString, int pCount){Append((const char *)pString, pCount);}
	void					        Append(FString &pString, int pCount){Append((const char *)(pString.mData), pCount);}
	
	//void					        Ins(const char *pString, int pLength, int pSlot);
	//void					        Ins(char *pString, int pLength, int pSlot){ Ins((const char *)pString, pLength, pSlot); }
	//void					        Ins(FString &pString, int pLength, int pSlot){ Ins((const char *)(pString.mData), pLength, pSlot); }

    void                            Insert(char pChar, int pCount, int pSlot);
    void                            Insert(char pChar, int pSlot);
    

    
    void                            Split(char pSplitter, FList *pResult);
    


	//
	//Write over the FString starting at the specified location...
	//"Hat".Write("Jam", 2) -> "HaJam"
	//"abcdefg".Write("123", 0) -> "123defg"
	//
    
    
	//void					Write(char theChar, int thePosition=0);
	//void					Write(char *pString, int thePosition=0);
	//void					Write(FString &pString, int thePosition=0);
	//void					Write(char *pString, int thePosition, int theAmount);
	//void					Write(FString &pString, int thePosition, int theAmount);
	//void					Write(char theChar, int theQuantity, int thePosition);
    
	//inline void				strpad(char theChar, int theQuantity){Write(theChar,theQuantity);}

	//inline void				strcpy(char *pString){*this=pString;}
	//inline void				strcpy(const char *pString){*this=(char*)pString;}
	//inline void				strcpy(FString &pString){*this=pString;}
	//inline void				strcpy(){Free();}
	//inline void				strncpy(char *pString, int theLen){Free();Write(pString,0,theLen);}
	//inline void				strncpy(FString &pString, int theLen){Free();Write(pString,0,theLen);}

	//
	//Format the FString...
	//
	//void					Format(char *theFormat, va_list &aArgs);
	//void					Format(char *theFormat, ...){va_list aArgs;va_start(aArgs, theFormat);Format(theFormat, aArgs);va_end(aArgs);}
	//void					sLog(char *theFormat, ...){va_list aArgs;va_start(aArgs, theFormat);Format(theFormat, aArgs);va_end(aArgs);}

	//
	//String representations of other data types...
	//
	
	void					ParseFloat(float pFloat, int pDecimalCount);
	inline void				ParseFloat(float pFloat){ ParseFloat(pFloat, 6); }
	
	
	void					ParseChar(char *theChar); 
	void					ParseBool(bool theBool){if(theBool)*this="true";else *this="false";}
    void                    ParseInt(int pNumber);

    
	//
	//Eliminate "spaces" (ASCII characters less than 33) from the
	//beginning or end of the FString...
	//
	void					RemoveLeadingSpaces();
	void					RemoveTrailingSpaces();

	//
	//Goes through the FString and replaces all cases
	//of one substring with different text...
	//
	void					Replace(char *theOriginal, char *theNew);
	void					Replace(char theOriginal, char theNew);
    void					Replace(const char *pOriginal, const char *pNew){Replace((char *)pOriginal, (char *)pNew);}
    
	void					Delete(char *pString);
	void					Delete(int thePosition, int theLength);
	void					Delete(int thePosition);
    
	void					Reverse();

	//
	//For oldschool windows machines that need carriage return before line feeds.
	void					AppendCRLF(){*this += "\r\n";}

	//
	//Set character at an index to something.
	//
	void					SetChar(int theIndex, char theChar);

	//
	//Find the first location in the FString where
	//the specified data is stored. Returns -1
	//if the specified data does not exist in the FString.
	//
	int						Find(char *pString, int thePosition);
	inline int				Find(FString &pString, int thePosition){return Find(pString.mData, thePosition);}
	inline int				Find(const char *pString, int thePosition){return Find((char*)pString, thePosition);}
	int						Find(char theRangeLow, char theRangeHigh, int thePosition);
	int						Find(char theChar, int thePosition);
	inline int				Find(char *pString){return Find(pString,0);}
	inline int				Find(const char *pString){return Find((char*)pString,0);}
	inline int				Find(FString &pString){return Find(pString.mData,0);}
	inline int				Find(char theRangeLow, char theRangeHigh){return Find(theRangeLow,theRangeHigh,0);}
	inline int				Find(char theChar){return Find(theChar,0);}

	int						FindI(char *pString, int thePosition);
	inline int				FindI(FString &pString, int thePosition){return FindI(pString.mData, thePosition);}
	inline int				FindI(const char *pString, int thePosition){return FindI((char*)pString, thePosition);}
	int						FindI(char theChar, int thePosition);
	inline int				FindI(char *pString){return FindI(pString, 0);}
	inline int				FindI(FString &pString){return FindI(pString.mData, 0);}
	inline int				FindI(const char *pString){return FindI((char*)pString, 0);}
	inline int				FindI(char theChar){return FindI(theChar, 0);}

    
    //, int thePosition
    
    int                     FindReverse(char pChar, int pPosition);
    int                     FindReverse(char pChar);
    
    
    

	inline int				strchr(char theChar){return Find(theChar);}

	//
	//Does the FString contain some of this stuff? Find out today!
	//
	inline bool				Contains(char theRangeLow, char theRangeHigh){return Find(theRangeLow,theRangeHigh)!=-1;}
	inline bool				Contains(char theChar){return Find(theChar)!=-1;}
	inline bool				Contains(const char *pString){return Find(pString,0) != -1;}
    inline bool				Contains(char *pString){return Contains((const char *)pString);}
	inline bool				Contains(FString &pString){return Find(pString.mData,0) != -1;}
	
	
	
    //FString					RemovePath(bool pRemoveExtension);
    FString								GetExtension();
    FString								ChopExtension();
    
    void								RemovePathAndExtension();
    void								RemovePath();
    void								RemoveExtension();
    
    //void                    RemoveFirstNumber();
    void								RemoveLastNumber();
    
    int									GetExtensionIndex();
    int									GetPathIndex();
    
    
    static FString                      GetCharsLetters(){FString aString;aString.Set("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ");return aString;}
    static FString                      GetCharsLettersLower(){FString aString;aString.Set("abcdefghijklmnopqrstuvwxyz");return aString;}
    static FString                      GetCharsLettersUpper(){FString aString;aString.Set("ABCDEFGHIJKLMNOPQRSTUVWXYZ");return aString;}
    static FString                      GetCharsAlphanumeric(){FString aString;aString.Set("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ0123456789");return aString;}
    static FString                      GetCharsNumeric(){FString aString;aString.Set("0123456789");return aString;}

	//
	//Generates a number between 0 and theTableSize.
	//Each FString produces a unique hash value,
	//but different FStrings may produce the same
	//hash value.
	//
	//int						GetHash(int theTableSize);
	//int						GetHashI(int theTableSize);

	//static int				GetHash(char *pString, int theTableSize);
	//static int				GetHashI(char *pString, int theTableSize);

	//static int				GetHash(char *pString, int theCount, int theTableSize);
	//static int				GetHashI(char *pString, int theCount, int theTableSize);


	unsigned int					    GetHash();
	unsigned int					    GetHashI();

	static unsigned int				    GetHash(char *pString);
	static unsigned int				    GetHashI(char *pString);

	//
	//Sets the case of all letters.
	//
	void							    Uppercase();
	void							    Lowercase();


	void							    CapitolizeFirstLetter(bool pForceLower);

	//
	//Get a copy of the FString with a certain case.
	//
	FString							    ToUpper(){FString aResult = *this;aResult.Uppercase();return aResult;}
	FString							    ToLower(){FString aResult = *this;aResult.Lowercase();return aResult;}

	void							    Encrypt(char *theKey);
	void							    Encrypt(const char *theKey){Encrypt((char*)theKey);}
	virtual void					    Encrypt(FString &theKey){Encrypt(theKey.mData);}

	void							    Decrypt(char *theKey);
	void							    Decrypt(const char *theKey){Decrypt((char*)theKey);}
	virtual void					    Decrypt(FString &theKey){Decrypt(theKey.mData);}

	int                                 Compare(FString &pString);
	int                                 CompareI(FString &pString);

    inline int                          Compare(char *pString){FString aString(pString);return Compare(aString);}
	inline int                          CompareI(char *pString){FString aString(pString);return CompareI(aString);}

	inline int                          Compare(const char *pString){FString aString(pString);return Compare(aString);}
	inline int                          CompareI(const char *pString){FString aString(pString);return CompareI(aString);}
    
    
	bool                                StartsWith(char *pString);
	inline bool                         StartsWith(FString &pString){return StartsWith(pString.mData);}
	
	bool                                StartsWithI(char *pString);
	inline bool                         StartsWithI(FString &pString){return StartsWithI(pString.mData);}
    
    
    bool                                EndsWith(char *pString);
	inline bool                         EndsWith(FString &pString){return EndsWith(pString.mData);}
	
	bool                                EndsWithI(char *pString);
	inline bool                         EndsWithI(FString &pString){return EndsWithI(pString.mData);}
    
    
    inline char                         *c() { if (mData == 0) { *this = ""; } return mData; }
    
    

    inline bool                     operator ==(FString pString){return (CompareI(pString) == 0);}
	inline bool						operator ==(const char *pString){return (CompareI(pString) == 0);}
	inline bool						operator ==(char *pString){return (CompareI(pString) == 0);}
    
    void                            operator = (char*pString){ Set((const char *)pString); }
	void                            operator = (const char *pString) { Set(pString); }
	void                            operator = (const FString pString) { Set((const char *)(pString.mData)); }
    
	inline void                     operator += (FString pString){Append(pString);}
	inline void                     operator += (char*pString){Append(pString);}
	inline void                     operator += (const char*pString){Append(pString);}
	void                            operator += (char pChar){Append(pChar);}

    
	FString                         operator + (FString pString);
	FString                         operator + (const char *pString);
	FString                         operator + (char *pString);

	FString                         operator + (char pChar);
    
    
protected:
    
    //void                            BaseInitialize();
    
    
};

//inline void		operator--(FString &pString, int theDummy){pString.Truncate(pString.mLength-1);}

//inline FString	operator+(FString &pString1, FString &pString2){ return FString(pString1.c()) + pString2; }
inline FString	operator+(char * theChar, FString &pString){ return FString(theChar) + pString; }
inline FString	operator+(const char * theChar, FString &pString){return FString(theChar) + pString;}
//inline FString	operator+(int theInt, FString &pString){return FString(theInt) + pString;}
//inline FString	operator+(bool theBool, FString &pString){return FString(theBool) + pString;}
//inline FString	operator+(float pFloat, FString &pString){return FString(pFloat) + pString;}
//inline FString	operator+(char theChar, FString &pString){return FString(theChar) + pString;}

//inline bool		operator==(char *theChar, FString pString){return pString == theChar;}

#endif

