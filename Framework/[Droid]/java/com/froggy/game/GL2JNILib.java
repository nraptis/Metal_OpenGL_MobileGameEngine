/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.froggy.game;

// Wrapper for native library

public class GL2JNILib {

     static {
         System.loadLibrary("gl2jni");
     }

    public static native void NativeAppShellPreinitialize();
    public static native void NativeAppShellSetAudioBufferAttributes(int pSampleRate, int pBufferSize);

    public static native void NativeAppShellInitialize(int pWidth, int pHeight);

    public static native void NativeAppShellDetachRunLoop();
    public static native void NativeAppShellGraphicsReady();

    public static native void NativeAppShellFrame();
    public static native void NativeAppShellSetSize(int pWidth, int pHeight);
    public static native void NativeAppShellSetDirectoryBundle(String pPath);
    public static native void NativeAppShellSetDirectoryDocuments(String pPath);

    public static native void NativeAppShellTouchBegin(float pX, float pY, int pData, int pCount);
    public static native void NativeAppShellTouchMove(float pX, float pY, int pData, int pCount);
    public static native void NativeAppShellTouchRelease(float pX, float pY, int pData, int pCount);
    public static native void NativeAppShellTouchCancel(float pX, float pY, int pData, int pCount);
    public static native void NativeAppShellTouchFlush();
    public static native void NativeAppShellExit();
    public static native void NativeAppShellPause();
    public static native void NativeAppShellResume();

    public static native void NativeAppShellMemoryWarning(boolean pSevre);

    public static native void NativeAppShellPurchaseSuccessful(char [] pName);
    public static native void NativeAppShellPurchaseFailed(char [] pName);
    public static native void NativeAppShellPurchaseCanceled(char [] pName);

    public static native void NativeAppShellAdBannerSetHeight(char [] pName);
    public static native void NativeAppShellAdBannerLoadFailed();
    public static native void NativeAppShellAdBannerLoadSuccessful();

    public static native void NativeAppShellKeyPress(int pKey);

}
