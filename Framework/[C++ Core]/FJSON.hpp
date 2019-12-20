//
//  FJSON.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FJSON_hpp
#define FJSON_hpp

#include "core_includes.h"
#include "FString.hpp"
#include "FList.hpp"
#include "FHashMap.hpp"
#include "FString.hpp"

#define EnumJSONArray(_json_node, _subjson_node_name)for(FJSONNode **_enum_start=(FJSONNode**)_json_node->mList,**_enum_end=((_json_node->mListCount > 0)?((FJSONNode**)(&(_json_node->mList[_json_node->mListCount]))) : ((FJSONNode**)0)),*_subjson_node_name=((_json_node->mListCount > 0)?(*_enum_start):((FJSONNode*)0));_subjson_node_name!=((FJSONNode*)0);_subjson_node_name=(++_enum_start<_enum_end)?*_enum_start:NULL)

#define JSON_NODE_TYPE_DATA 0
#define JSON_NODE_TYPE_DICTIONARY 1
#define JSON_NODE_TYPE_ARRAY 2

#define JSON_DATA_TYPE_STRING 0
#define JSON_DATA_TYPE_NUMBER 1
#define JSON_DATA_TYPE_FLAG 2

class FJSONNode {
public:
    FJSONNode();
    ~FJSONNode();
    
    void                        AddDictionary(const char *pKey, FJSONNode *pNode);
    
    void                        AddDictionaryInt(const char *pKey, int pValue);
    void                        AddDictionaryBool(const char *pKey, bool pValue);
    void                        AddDictionaryFloat(const char *pKey, float pValue);
    void                        AddDictionaryString(const char *pKey, const char *pValue);
    
    FJSONNode                   *GetArray(const char *pKey);
    FJSONNode                   *GetDictionary(const char *pKey);
    FJSONNode                   *GetData(const char *pKey);
    
    
    int                         GetInt(const char *pKey, int pDefaultValue);
    bool                        GetBool(const char *pKey, bool pDefaultValue);
    float                       GetFloat(const char *pKey, float pDefaultValue);
    FString                     GetString(const char *pKey, FString pDefaultValue);
    
    int                         IntValue(int pDefaultValue);
    bool                        BoolValue(bool pDefaultValue);
    float                       FloatValue(float pDefaultValue);
    FString                     StringValue(FString pDefaultValue);
    
    
    void                        ArrayAddInt(int pValue);
    void                        ArrayAddFloat(float pValue);
    void                        ArrayAddBool(bool pValue);
    void                        ArrayAddString(FString pValue);
    
    
    
    
    void                        AddArray(FJSONNode *pNode);
    
    
    //const char                  *mKey;
    const char                  *mValue;
    int                         mDataType;
    
    FJSONNode                   **mList;
    int                         mListCount;
    int                         mListSize;
    
    FStringMap                  *mInfo;
    
    int                         mNodeType;
};

class FJSON {
public:
    FJSON();
    ~FJSON();
    
    void                        Clear();
    
    void                        Save(const char *pFile);
    inline void                 Save(FString pString) { Save((const char *)pString.c()); }
    
    void                        Load(const char *pFile);
    inline void                 Load(FString pString) { Load((const char *)pString.c()); }
    
    void                        Parse(const char *pData, int pLength);
    
    void                        Print();
    FString                     GetPrettyPrint();
    
    FJSONNode                   *mRoot;
    
private:
    
    void                        OutputChunk(FJSONNode *pNode, FJSONNode *pParent, int pDepth, bool pTabbed, FString *pOutput);
    
    
    inline bool                 IsWhiteSpace(char pChar) { return pChar <= 32; }
    inline bool                 IsNumber(char pChar) {
        if (pChar >= '0' && pChar <= '9') { return true; }
        if (pChar == '-') { return true; }
        if (pChar == '+') { return true; }
        if (pChar == '.') { return true; }
        return false;
    }
    
    inline bool                 IsAlphabetic(char pChar) {
        if (pChar >= 'a' && pChar <= 'z') { return true; }
        if (pChar >= 'A' && pChar <= 'Z') { return true; }
        return false;
    }
    
    inline char                 *EndOfQuote(char *pChar) {
        ++pChar;
        while (*pChar != 0) {
            if (*pChar == '\"') {
                return pChar;
            } else if (*pChar == '\\') {
                pChar++;
                if (*pChar == 'b' ||
                    *pChar == 'f' ||
                    *pChar == 'n' ||
                    *pChar == 'r' ||
                    *pChar == 't' ||
                    *pChar == '\"' ||
                    *pChar == '\\') {
                    pChar++;
                } else {
                    Log("Illegal character following \\\n\n\n");
                    return 0;
                }
            } else {
                ++pChar;
            }
        }
        return NULL;
    }
    
    inline char                 *GetQuotedString(char *pStart, char *pEnd) {
        int aLength = (int)(pEnd - pStart);
        char *aResult = new char[aLength + 2];
        char *aPaste = aResult;
        char *aCopy = pStart + 1;
        while (aCopy < pEnd) {
            if (*aCopy == '\\') {
                ++aCopy;
                if (*aCopy == 'b') {
                    *aPaste++ = '\b';
                    aCopy++;
                } else if (*aCopy == 'f') {
                    *aPaste++ = '\f';
                    aCopy++;
                } else if (*aCopy == 'n') {
                    *aPaste++ = '\n';
                    aCopy++;
                } else if (*aCopy == 'r') {
                    *aPaste++ = '\r';
                    aCopy++;
                } else if (*aCopy == 't') {
                    *aPaste++ = '\t';
                    aCopy++;
                } else if (*aCopy == '\"') {
                    *aPaste++ = '\"';
                    aCopy++;
                } else if (*aCopy == '\\') {
                    *aPaste++ = '\\';
                    aCopy++;
                }
            } else {
                *aPaste++ = *aCopy++;
            }
        }
        *aPaste = 0;
        return aResult;
    }
    
    inline char                 *EndOfNumber(char *pChar) {
        ++pChar;
        while (IsNumber(*pChar)) {
            ++pChar;
        }
        --pChar;
        return pChar;
    }
    
    inline char                 *GetNumber(char *pStart, char *pEnd) {
        int aLength = (int)(pEnd - pStart);
        char *aResult = new char[aLength + 2];
        char *aPaste = aResult;
        char *aCopy = pStart;
        while (aCopy <= pEnd) {
            *aPaste++ = *aCopy++;
        }
        *aPaste = 0;

        return aResult;
    }
    
    inline char                 *EndOfAlphabetic(char *pChar) {
        //Assumption *pChar = NUM
        ++pChar;
        while (IsAlphabetic(*pChar)) {
            ++pChar;
        }
        --pChar;
        return pChar;
    }
    
    inline char                 *GetAlphabetic(char *pStart, char *pEnd) {
        int aLength = (int)(pEnd - pStart);
        char *aResult = new char[aLength + 2];
        char *aPaste = aResult;
        char *aCopy = pStart;
        while (aCopy <= pEnd) {
            *aPaste++ = *aCopy++;
        }
        *aPaste = 0;
        //*aPaste = 0;
        
        return aResult;
    }
    
    //Assume that we pass in character AFTER the "{"
    //with the parent node as last item on pStack
    char                        *ParseHelperDictionary(char *pData, FList *pStack, bool *pSuccess);
    
    //Assume that we pass in character AFTER the "["
    //with the parent node as last item on pStack
    char                        *ParseHelperArray(char *pData, FList *pStack, bool *pSuccess);
};



#endif /* FJSON_hpp */
