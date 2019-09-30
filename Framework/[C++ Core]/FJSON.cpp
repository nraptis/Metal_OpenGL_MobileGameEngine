//
//  FJSON.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FJSON.hpp"
#include "FFile.hpp"


FJSONNode::FJSONNode() {
    //mKey = NULL;
    mValue = NULL;
    
    mList = NULL;
    mListCount = 0;
    mListSize = 0;
    
    mInfo = NULL;
    
    mNodeType = JSON_NODE_TYPE_DATA;
    mDataType = JSON_DATA_TYPE_FLAG;
}

FJSONNode::~FJSONNode() {
    
    if (mValue != NULL) {
        delete [] mValue;
        mValue = NULL;
    }
    
    if (mList != NULL) {
        for (int i=0;i<mListCount;i++) {
            delete mList[i];
        }
        delete [] mList;
        mList = NULL;
    }
    
    if (mInfo != NULL) {
        FStringMapNode *aNode = mInfo->mListHead;
        while (aNode != NULL) {
            FJSONNode *aJSONNode = ((FJSONNode *)aNode->mObject);
            delete aJSONNode;
            aNode = aNode->mListNext;
        }
        delete mInfo;
        mInfo = NULL;
    }
}

void FJSONNode::AddDictionary(const char *pKey, FJSONNode *pNode) {
    if (mInfo == NULL) {
        mInfo = new FStringMap();
    }
    mNodeType = JSON_NODE_TYPE_DICTIONARY;
    mInfo->Add(pKey, pNode);
}

void FJSONNode::AddDictionaryInt(const char *pKey, int pValue) {
    FString aString;
    aString.ParseInt(pValue);
    FJSONNode *aValueNode = new FJSONNode();
    aValueNode->mDataType = JSON_DATA_TYPE_NUMBER;
    aValueNode->mValue = aString.GetCharArray();
    AddDictionary(pKey, aValueNode);
}

void FJSONNode::AddDictionaryBool(const char *pKey, bool pValue) {
    FString aString;
    aString.ParseBool(pValue);
    FJSONNode *aValueNode = new FJSONNode();
    aValueNode->mDataType = JSON_DATA_TYPE_FLAG;
    aValueNode->mValue = aString.GetCharArray();
    AddDictionary(pKey, aValueNode);
}

void FJSONNode::AddDictionaryFloat(const char *pKey, float pValue) {
    FString aString;
    aString.ParseFloat(pValue);
    FJSONNode *aValueNode = new FJSONNode();
    aValueNode->mDataType = JSON_DATA_TYPE_NUMBER;
    aValueNode->mValue = aString.GetCharArray();
    AddDictionary(pKey, aValueNode);
}

void FJSONNode::AddDictionaryString(const char *pKey, const char *pValue) {
    FString aString = pValue;
    FJSONNode *aValueNode = new FJSONNode();
    aValueNode->mDataType = JSON_DATA_TYPE_STRING;
    aValueNode->mValue = aString.GetCharArray();
    AddDictionary(pKey, aValueNode);
}

void FJSONNode::AddArray(FJSONNode *pNode) {
    if (mList == NULL) {
        mListSize = 1;
        mList = new FJSONNode*[mListSize];
    }
    if (mListCount >= mListSize) {
        mListSize = (mListCount + mListCount / 2 + 1);
        FJSONNode **aNewList = new FJSONNode*[mListSize];
        for (int i=0;i<mListCount;i++) {
            aNewList[i] = mList[i];
        }
        delete [] mList;
        mList = aNewList;
    }
    mNodeType = JSON_NODE_TYPE_ARRAY;
    mList[mListCount++] = pNode;
}

FJSONNode *FJSONNode::GetArray(const char *pKey) {
    if (mInfo != NULL) {
        FJSONNode *aNode = (FJSONNode *)mInfo->Get(pKey);
        if (aNode != NULL && aNode->mNodeType == JSON_NODE_TYPE_ARRAY) {
            return aNode;
        }
    }
    return NULL;
}

FJSONNode *FJSONNode::GetDictionary(const char *pKey) {
    if (mInfo != NULL) {
        FJSONNode *aNode = (FJSONNode *)mInfo->Get(pKey);
        if (aNode != NULL && aNode->mNodeType == JSON_NODE_TYPE_DICTIONARY) {
            return aNode;
        }
    }
    return NULL;
}

FJSONNode *FJSONNode::GetData(const char *pKey) {
    if (mInfo != NULL) {
        FJSONNode *aNode = (FJSONNode *)mInfo->Get(pKey);
        if (aNode != NULL && aNode->mNodeType == JSON_NODE_TYPE_DATA) {
            return aNode;
        }
    }
    return NULL;
}

int FJSONNode::GetInt(const char *pKey, int pDefaultValue) {
    FJSONNode *aNode = GetData(pKey);
    if (aNode != NULL) { return aNode->IntValue(pDefaultValue); }
    return pDefaultValue;
}

bool FJSONNode::GetBool(const char *pKey, bool pDefaultValue) {
    FJSONNode *aNode = GetData(pKey);
    if (aNode != NULL) { return aNode->BoolValue(pDefaultValue); }
    return pDefaultValue;
}

float FJSONNode::GetFloat(const char *pKey, float pDefaultValue) {
    FJSONNode *aNode = GetData(pKey);
    if (aNode != NULL) { return aNode->FloatValue(pDefaultValue); }
    return pDefaultValue;
}

FString FJSONNode::GetString(const char *pKey, FString pDefaultValue) {
    FJSONNode *aNode = GetData(pKey);
    if (aNode != NULL) { return aNode->StringValue(pDefaultValue); }
    return pDefaultValue;
}

int FJSONNode::IntValue(int pDefaultValue) {
    if (mNodeType == JSON_NODE_TYPE_DATA && mValue != NULL) {
        return FString(mValue).ToInt();
    }
    return pDefaultValue;
}

bool FJSONNode::BoolValue(bool pDefaultValue) {
    if (mNodeType == JSON_NODE_TYPE_DATA && mValue != NULL) {
        return FString(mValue).ToBool();
    }
    return pDefaultValue;
}

float FJSONNode::FloatValue(float pDefaultValue) {
    
    if (mNodeType == JSON_NODE_TYPE_DATA && mValue != NULL) {
        return FString(mValue).ToFloat();
    }
    return pDefaultValue;
}

FString FJSONNode::StringValue(FString pDefaultValue) {
    if (mNodeType == JSON_NODE_TYPE_DATA && mValue != NULL) {
        return FString(mValue);
    }
    return pDefaultValue;
}

FJSON::FJSON() {
    mRoot = NULL;
}

FJSON::~FJSON() {
    Clear();
}

void FJSON::Clear() {
    if (mRoot != NULL) {
        delete mRoot;
        mRoot = NULL;
    }
}

void FJSON::Load(const char *pFile) {
    FFile aFile;
    aFile.Load(pFile);
    
    if (aFile.mLength <= 0) {
        bool aBlock = false;
        while (aBlock == false) {
            aBlock = true;
            FString aFileName = FString(pFile);
            aFileName.RemoveExtension();
            aFile.Load(aFileName + FString(".json"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".JSON"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".jsn"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".JSN"));
            if (aFile.mLength > 0) { break; }
            aFileName.RemovePath();
            aFile.Load(aFileName + FString(".json"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".JSON"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".jsn"));
            if (aFile.mLength > 0) { break; }
            aFile.Load(aFileName + FString(".JSN"));
        }
    }
    Parse((const char *)aFile.mData, aFile.mLength);
}

void FJSON::Save(const char *pFile) {
    FString aExport = GetPrettyPrint();
    if (aExport.mLength <= 1) { aExport = "{}"; }
    FFile aFile;
    aFile.Write(aExport.mData, aExport.mLength);
    aFile.Save(pFile);
}

void FJSON::Parse(const char *pData, int pLength) {
    
    Clear();
    if (pData == NULL || pLength <= 2) { return; }
    
    char *aData = new char[pLength + 1];
    for (int i=0;i<pLength;i++) {
        aData[i] = pData[i];
    }
    aData[pLength] = 0;
    
    FList aStack;
    bool aDictionary = false;
    
    char *aPtr = aData;
    while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
    
    if (*aPtr == '{') {
        ++aPtr;
        aDictionary = true;
    } else if (*aPtr == '[') {
        ++aPtr;
        aDictionary = false;
    } else {
        goto JSON_PARSE_ERROR;
    }
    
    mRoot = new FJSONNode();
    aStack.Add(mRoot);
    
    if (aDictionary) {
        bool aSuccess = true;
        mRoot->mNodeType = JSON_NODE_TYPE_DICTIONARY;
        ParseHelperDictionary(aPtr, &aStack, &aSuccess);
        if (aSuccess == false) {
            goto JSON_PARSE_ERROR;
        }
    } else {
        bool aSuccess = true;
        mRoot->mNodeType = JSON_NODE_TYPE_ARRAY;
        ParseHelperArray(aPtr, &aStack, &aSuccess);
        if (aSuccess == false) {
            goto JSON_PARSE_ERROR;
        }
    }
    
    delete [] aData;
    return;
    
JSON_PARSE_ERROR:
    
    delete [] aData;
    delete mRoot;
    mRoot = NULL;
}


//Assume that we pass in character AFTER the "{"
//with the parent node as last item on pStack
char *FJSON::ParseHelperDictionary(char *pData, FList *pStack, bool *pSuccess) {
    FJSONNode *aParent = (FJSONNode *)pStack->Last();
    if (aParent == NULL) {
        *pSuccess = false;
        return NULL;
    }
    
    int aElementIndex = 0;
    char *aPtr = pData;
    while (*aPtr) {
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        if (aElementIndex > 0) {
            if (*aPtr == ',') {
                aPtr += 1;
            } else if (*aPtr == '}') {
                aPtr += 1;
                goto ParseHelperDictionary_COMPLETE;
            } else {
                *pSuccess = false;
                return NULL;
            }
        } else {
            if (*aPtr == '}') {
                ++aPtr;
                goto ParseHelperDictionary_COMPLETE;
            }
        }
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        if (*aPtr != '\"') {
            *pSuccess = false;
            return NULL;
        }
        
        char *aEOQ = EndOfQuote(aPtr);
        if (aEOQ == NULL) {
            *pSuccess = false;
            return NULL;
        }
        
        char *aKey = GetQuotedString(aPtr, aEOQ);
        aPtr = aEOQ + 1;
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        
        if (*aPtr != ':') {
            *pSuccess = false;
            delete aKey;
            return NULL;
        }
        ++aPtr;
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        if (*aPtr == '{') {
            ++aPtr;
            
            FJSONNode *aNode = new FJSONNode();
            //aNode->mKey = aKey;
            aNode->mNodeType = JSON_NODE_TYPE_DICTIONARY;
            aParent->AddDictionary(aKey, aNode);
            delete aKey;
            pStack->Add(aNode);
            aPtr = ParseHelperDictionary(aPtr, pStack, pSuccess);
            if (*pSuccess == false) {
                return NULL;
            }
            
            pStack->PopLast();
            
        } else if (*aPtr == '[') {
            ++aPtr;
            FJSONNode *aNode = new FJSONNode();
            //aNode->mKey = aKey;
            aNode->mNodeType = JSON_NODE_TYPE_ARRAY;
            aParent->AddDictionary(aKey, aNode);
            delete aKey;
            pStack->Add(aNode);
            aPtr = ParseHelperArray(aPtr, pStack, pSuccess);
            if (*pSuccess == false) {
                return NULL;
            }
            
            pStack->PopLast();
        } else if (*aPtr == '\"') {
            aEOQ = EndOfQuote(aPtr);
            if (aEOQ == NULL) {
                *pSuccess = false;
                delete aKey;
                return NULL;
            }
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mDataType = JSON_DATA_TYPE_STRING;
            aValueNode->mValue = GetQuotedString(aPtr, aEOQ);
            aParent->AddDictionary(aKey, aValueNode);
            delete aKey;
            aPtr = aEOQ;
            ++aPtr;
        } else if (IsNumber(*aPtr)) {
            char *aEON = EndOfNumber(aPtr);
            if (aEON == NULL) {
                *pSuccess = false;
                delete aKey;
                return NULL;
            }
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mDataType = JSON_DATA_TYPE_NUMBER;
            aValueNode->mValue = GetNumber(aPtr, aEON);
            aParent->AddDictionary(aKey, aValueNode);
            
            delete aKey;
            aPtr = aEON;
            ++aPtr;
        } else if (IsAlphabetic(*aPtr)) {
            char *aEOA = EndOfAlphabetic(aPtr);
            if (aEOA == NULL) {
                *pSuccess = false;
                delete aKey;
                return NULL;
            }
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mDataType = JSON_DATA_TYPE_FLAG;
            aValueNode->mValue = GetNumber(aPtr, aEOA);
            aParent->AddDictionary(aKey, aValueNode);
            delete aKey;
            aPtr = aEOA;
            ++aPtr;
        } else {
            *pSuccess = false;
            delete aKey;
            return NULL;
        }
        ++aElementIndex;
    }
ParseHelperDictionary_COMPLETE:
    return aPtr;
}

//Assume that we pass in character AFTER the "["
//with the parent node as last item on pStack
char *FJSON::ParseHelperArray(char *pData, FList *pStack, bool *pSuccess) {
    FJSONNode *aParent = (FJSONNode *)pStack->Last();
    if (aParent == NULL) {
        *pSuccess = false;
        return NULL;
    }
    int aElementIndex = 0;
    char *aPtr = pData;
    while (*aPtr) {
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        if (aElementIndex > 0) {
            if (*aPtr == ',') {
                aPtr += 1;
            } else if (*aPtr == ']') {
                aPtr += 1;
                goto ParseHelperArray_COMPLETE;
            } else {
                *pSuccess = false;
                return NULL;
            }
        } else {
            if (*aPtr == ']') {
                ++aPtr;
                goto ParseHelperArray_COMPLETE;
            }
        }
        while ((*aPtr != 0) && IsWhiteSpace(*aPtr)) { aPtr++; }
        if (*aPtr == '{') {
            ++aPtr;
            FJSONNode *aNode = new FJSONNode();
            aNode->mNodeType = JSON_NODE_TYPE_DICTIONARY;
            aParent->AddArray(aNode);
            pStack->Add(aNode);
            aPtr = ParseHelperDictionary(aPtr, pStack, pSuccess);
            if (*pSuccess == false) {
                return NULL;
            }
            pStack->PopLast();
        } else if (*aPtr == '[') {
            ++aPtr;
            FJSONNode *aNode = new FJSONNode();
            aNode->mNodeType = JSON_NODE_TYPE_ARRAY;
            aParent->AddArray(aNode);
            pStack->Add(aNode);
            aPtr = ParseHelperArray(aPtr, pStack, pSuccess);
            if (*pSuccess == false) {
                return NULL;
            }
            pStack->PopLast();
        } else if (*aPtr == '\"') {
            char *aEOQ = EndOfQuote(aPtr);
            if (aEOQ == NULL) {
                *pSuccess = false;
                return NULL;
            }
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mDataType = JSON_DATA_TYPE_STRING;
            aValueNode->mValue = GetQuotedString(aPtr, aEOQ);
            aParent->AddArray(aValueNode);
            aPtr = aEOQ;
            ++aPtr;
        } else if (IsNumber(*aPtr)) {
            char *aEON = EndOfNumber(aPtr);
            if (aEON == NULL) {
                *pSuccess = false;
                return NULL;
            }
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mDataType = JSON_DATA_TYPE_NUMBER;
            aValueNode->mValue = GetNumber(aPtr, aEON);
            aParent->AddArray(aValueNode);
            aPtr = aEON;
            ++aPtr;
        } else if (IsAlphabetic(*aPtr)) {
            char *aEOA = EndOfAlphabetic(aPtr);
            if (aEOA == NULL) {
                *pSuccess = false;
                return NULL;
            }
            FJSONNode *aValueNode = new FJSONNode();
            aValueNode->mDataType = JSON_DATA_TYPE_FLAG;
            aValueNode->mValue = GetAlphabetic(aPtr, aEOA);
            aParent->AddArray(aValueNode);
            aPtr = aEOA;
            ++aPtr;
        } else {
            *pSuccess = false;
            return NULL;
        }
        ++aElementIndex;
    }
ParseHelperArray_COMPLETE:
    return aPtr;
}


void FJSON::Print() {
    Log("__JSON_BEGIN:\n");
    FString aString = GetPrettyPrint();
    Log("\n%s\n", aString.c());
    Log("__JSON_END:\n");
}

FString FJSON::GetPrettyPrint() {
    if (mRoot == NULL) {
        FString aResult = "";
        return aResult;
    }
    FString aResult;
    OutputChunk(mRoot, NULL, 0, false, &aResult);
    return aResult;
}

void FJSON::OutputChunk(FJSONNode *pNode, FJSONNode *pParent, int pDepth, bool pTabbed, FString *pOutput) {
    if (pNode == NULL) { return; }
    if (pTabbed == false) {
        for (int i=0;i<pDepth;i++) {
            pOutput->Append("\t");
        }
    }
    if (pNode->mNodeType == JSON_NODE_TYPE_DICTIONARY) {
        pOutput->Append("{");
        if (pNode->mInfo != NULL) {
            FStringMapNode *aMapNode = pNode->mInfo->mListHead;
            pOutput->Append("\n");
            while (aMapNode != NULL) {
                for (int i=0;i<=pDepth;i++) {
                    pOutput->Append("\t");
                }
                FJSONNode *aNode = (FJSONNode *)aMapNode->mObject;
                pOutput->Append("\"");
                pOutput->Append(aMapNode->mKey);
                pOutput->Append("\"");
                pOutput->Append(": ");
                if (aNode->mNodeType == JSON_NODE_TYPE_DATA) {
                    if (aNode->mDataType == JSON_DATA_TYPE_STRING) {
                        pOutput->Append("\"");
                        pOutput->Append(aNode->mValue);
                        pOutput->Append("\"");
                    } else {
                        if (aNode->mValue && *(aNode->mValue)) {
                            pOutput->Append(aNode->mValue);
                        } else {
                            pOutput->Append("0");
                        }
                    }
                } else {
                    OutputChunk(aNode, pNode, pDepth + 1, true, pOutput);
                }
                if (aMapNode->mListNext) {
                    pOutput->Append(",\r\n");
                } else {
                    pOutput->Append("\r\n");
                }
                aMapNode = aMapNode->mListNext;
            }
            for (int i=0;i<pDepth;i++) {
                pOutput->Append("\t");
            }
            pOutput->Append("}");
        } else {
            pOutput->Append("}");
        }
    } else if (pNode->mNodeType == JSON_NODE_TYPE_ARRAY) {
        pOutput->Append("[");
        int aCount = pNode->mListCount;
        if (aCount > 0 && pNode->mList != NULL) {
            bool aMixedTypeChildren = false;
            for (int i=0;i<aCount;i++) {
                FJSONNode *aNode = pNode->mList[i];
                if (aNode->mNodeType == JSON_NODE_TYPE_ARRAY ||
                    aNode->mNodeType == JSON_NODE_TYPE_DICTIONARY) {
                    aMixedTypeChildren = true;
                }
            }
            if (aMixedTypeChildren == false) {
                for (int i=0;i<aCount;i++) {
                    FJSONNode *aNode = pNode->mList[i];
                    if (aNode->mDataType == JSON_DATA_TYPE_STRING) {
                        pOutput->Append("\"");
                        pOutput->Append(aNode->mValue);
                        pOutput->Append("\"");
                    } else {
                        pOutput->Append(aNode->mValue);
                    }
                    if (i < (aCount - 1)) {
                        pOutput->Append(", ");
                    }
                }
                pOutput->Append("]");
            } else {
                pOutput->Append("\n");
                for (int i=0;i<aCount;i++) {
                    FJSONNode *aNode = pNode->mList[i];
                    for (int i=0;i<=pDepth;i++) {
                        pOutput->Append("\t");
                    }
                    if (aNode->mNodeType == JSON_NODE_TYPE_DATA) {
                        if (aNode->mDataType == JSON_DATA_TYPE_STRING) {
                            pOutput->Append("\"");
                            pOutput->Append(aNode->mValue);
                            pOutput->Append("\"");
                        } else {
                            pOutput->Append(aNode->mValue);
                        }
                    } else {
                        OutputChunk(aNode, pNode, pDepth + 1, true, pOutput);
                    }
                    if (i < (aCount - 1)) {
                        pOutput->Append(",\r\n");
                    } else {
                        pOutput->Append("\r\n");
                    }
                }
                for (int i=0;i<pDepth;i++) {
                    pOutput->Append("\t");
                }
                pOutput->Append("]");
            }
        } else {
            pOutput->Append("]");
        }
    } else {
        pOutput->Append("0");
    }
}

