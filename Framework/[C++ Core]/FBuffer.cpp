//
//  FBuffer.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/16/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FBuffer.hpp"
#include "os_core_graphics.h"
#include "core_includes.h"
#include "FBufferCache.hpp"

FBuffer::FBuffer(int pLength, int pType) {
    mLength = pLength;
    mType = pType;
    mBindIndex = -1;
    Realize();
    gBufferCache.RegisterBuffer(this);
}

FBuffer::~FBuffer() {
    gBufferCache.UnregisterBuffer(this);
}

void FBuffer::Realize() {
    if ((mBindIndex == -1) && (mLength > 0)) {
        if (mType == BUFFER_TYPE_ARRAY) {
            mBindIndex = Graphics::BufferArrayGenerate(mLength);
        }
        if (mType == BUFFER_TYPE_ELEMENT) {
            mBindIndex = Graphics::BufferElementGenerate(mLength);
        }
    }
}

void FBuffer::Unload() {
    if (mBindIndex != -1) {
        if (mType == BUFFER_TYPE_ARRAY) {
            Graphics::BufferArrayDelete(mBindIndex);
        }
        if (mType == BUFFER_TYPE_ELEMENT) {
            Graphics::BufferElementDelete(mBindIndex);
        }
    }
    mBindIndex = -1;
}
