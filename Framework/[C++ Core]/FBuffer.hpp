//
//  FBuffer.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/16/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FBuffer_hpp
#define FBuffer_hpp



#define BUFFER_TYPE_ARRAY 0
#define BUFFER_TYPE_ELEMENT 1

class FBuffer {
public:
    FBuffer(int pLength, int pType);
    virtual ~FBuffer();
    
    void                                    Realize();
    void                                    Unload();
    
    int                                     mBindIndex;
    
    int                                     mLength;
    int                                     mType;
};

#endif
