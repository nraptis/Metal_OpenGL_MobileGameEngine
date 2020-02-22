//
//  core_os.m
//  CoreDemo
//
//  Created by Nick Raptis on 9/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//


#include "os_core_outlets.h"
#include "core_includes.h"
#include "FList.hpp"
#include "FString.hpp"

#include <sys/time.h>
#include <sys/stat.h>
#include <time.h>
#include <chrono>

#include <fcntl.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <dirent.h>

#include <pthread.h>
#include <sys/utsname.h>

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


using namespace std;

#define JAVA_OUTLET_CLASS "com/froggy/game/JavaOutlets"

jobject _objJNIHelper = 0;
jclass _clsJNIHelper = 0;
static bool gJNIDetached = false;
jclass gOutletClass = NULL;



char mPrintBuffer[2048];

void Log(const char *pText, ...) {
    if ((pText != 0) && (_objJNIHelper != 0)) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        if (aEnv != NULL) {
            va_list argptr;
            va_start(argptr, pText);
            vsprintf(mPrintBuffer, pText, argptr);
            va_end(argptr);

            jstring aName = aEnv->NewStringUTF(mPrintBuffer);
            jmethodID aMethodID = aEnv->GetMethodID(_clsJNIHelper, "JavaLog", "(Ljava/lang/String;)V");
            if (aMethodID) {
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aName);
            }
            aEnv->DeleteLocalRef(aName);
        }
        if (aDetach) {
            //gJVM->DetachCurrentThread();
        }
    }
}

void os_initialize_outlets() {
    if (gJVM) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        if (aEnv) {
            if (_clsJNIHelper == 0) {
                jclass cls = os_getClassID(aEnv);
                _clsJNIHelper = (jclass) aEnv->NewGlobalRef(cls);
                jmethodID constructor = aEnv->GetMethodID(_clsJNIHelper, "<init>", "()V");
                _objJNIHelper = aEnv->NewObject(_clsJNIHelper, constructor);
                _objJNIHelper = aEnv->NewGlobalRef(_objJNIHelper);
            }
        }
    }
}


JNIEnv *os_getJNIEnv(bool *pRequiresDetach) {
    JNIEnv *aENV = 0;
    *pRequiresDetach = false;
    if (gJVM != 0) {
        jint ret = gJVM->GetEnv((void**)&aENV, JNI_VERSION_1_6);
        switch (ret) {
            case JNI_OK :
                return aENV;
                gJNIDetached = false;

            case JNI_EDETACHED :
                //LOGI("STATS: JNI_JNI_EDETACHED...\n");

                // Thread not attached
                
                // TODO : If calling AttachCurrentThread() on a native thread
                // must call DetachCurrentThread() in future.
                // see: http://developer.android.com/guide/practices/design/jni.html

                *pRequiresDetach = true;

                if (gJVM->AttachCurrentThread(&aENV, NULL) < 0) {
                    Log("Failed to get the environment using AttachCurrentThread()\n");
                    return 0;
                } else {
                    return aENV;
                }
            case JNI_EVERSION :
                // Cannot recover from this error
                LOGI("JNI interface version 1.4 not supported\n");
            default :
                LOGI("Failed to get the environment using GetEnv()\n");
                return 0;
        }
    }
    return aENV;
}

jclass os_getClassID(JNIEnv *pEnv) {

    if (gOutletClass != NULL) {
        return gOutletClass;
    }

    jclass aClass = pEnv->FindClass(JAVA_OUTLET_CLASS);

    if (!aClass) {
        Log("Failed to find class of %s", JAVA_OUTLET_CLASS);
    }

    if (pEnv->ExceptionCheck()) {
        LOGI("NO CLASS FOUND...?\n");
        return NULL;
    }

    gOutletClass  = (jclass)(pEnv->NewGlobalRef(aClass));

    return aClass;
}

void os_detach_thread(void (*pFunction)(void *pArg), void* pArg) {
    printf("Detaching Threat [%X]\n", pArg);
    pthread_t aThread;
    pthread_attr_t aAttr;
    pthread_attr_init(&aAttr);
    pthread_attr_setdetachstate(&aAttr, PTHREAD_CREATE_DETACHED);
    pthread_create(&aThread,&aAttr, (void*(*)(void*))pFunction, pArg);
}

void os_sleep(int pTime) {
    usleep(pTime * 1000);
}

bool os_updates_in_background() {
    return true;
}

bool os_draws_in_background() {
    return true;
}

int os_getAssetScale() {

    Log("os_getAssetScale!!!???\n");

    int aResult = 0;

    jmethodID aMethodID = 0;
    if (gJVM != 0) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        if (aEnv != 0) {
            jclass aClass = os_getClassID(aEnv);
            if (aClass != 0) {
                aMethodID = aEnv->GetMethodID(aClass, "getAssetScale", "()I");
                if (aMethodID) {
                    aResult = aEnv->CallIntMethod(_objJNIHelper, aMethodID);
                }
            }
        }
        if (aDetach) {
            //gJVM->DetachCurrentThread();
        }
    }
    return aResult;

    /*

    jmethodID aMethodID = 0;
    if (gJVM != 0) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        if (aEnv != 0) {
            jclass aClass = os_getClassID(aEnv);
            if (aClass != 0) {
                aMethodID = aEnv->GetMethodID(aClass, "getAssetScale", "()I");
                if (aMethodID) {
                    aResult = aEnv->CallIntMethod(_objJNIHelper, aMethodID);
                }
            }
        }
        if (aDetach) {
            //gJVM->DetachCurrentThread();
        }
    }
    */
    return aResult;
}

void os_commitRender() {
    jmethodID aMethodID = 0;
    if (gJVM != 0) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        if (aEnv != 0) {
            jclass aClass = os_getClassID(aEnv);
            if (aClass != 0) {
                aMethodID = aEnv->GetMethodID(aClass, "commitRender", "()V");
                if (aMethodID) {
                    aEnv->CallVoidMethod(_objJNIHelper, aMethodID);
                }
            }
        }
        if (aDetach) {
            //gJVM->DetachCurrentThread();
        }
    }
}
//
////

int os_create_thread_lock() {
    int aResult = -1;
    jmethodID aMethodID = 0;
    if (gJVM != 0) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        if (aEnv != 0) {
            jclass aClass = os_getClassID(aEnv);
            if (aClass != 0) {
                aMethodID = aEnv->GetMethodID(aClass, "createThreadLock", "()I");
                if (aMethodID) {
                    aResult = aEnv->CallIntMethod(_objJNIHelper, aMethodID);
                }
            }
        }
        if (aDetach) {
            //gJVM->DetachCurrentThread();
        }
    }
    return aResult;
}

bool os_thread_lock_exists(int pLockIndex) {
    bool aResult = false;
    if (pLockIndex >= 0) {

        jmethodID aMethodID = 0;
        if (gJVM != 0) {
            bool aDetach = false;
            JNIEnv *aEnv = os_getJNIEnv(&aDetach);
            if (aEnv != 0) {
                jclass aClass = os_getClassID(aEnv);
                if (aClass != 0) {
                    aMethodID = aEnv->GetMethodID(aClass, "doesThreadLockExist", "(I)Z");
                    if (aMethodID) {
                        aResult = aEnv->CallBooleanMethod(_objJNIHelper, aMethodID, pLockIndex);
                        //Log("Does Lock [%d] Exist? [%d]!!!\n\n", pLockIndex, aResult);
                    }
                }
            }
            if (aDetach) {
                //gJVM->DetachCurrentThread();
            }
        }
        return true;
    }
    return false;
}

void os_delete_thread_lock(int pLockIndex) {
    if (pLockIndex >= 0) {
        jmethodID aMethodID = 0;
        if (gJVM != 0) {
            bool aDetach = false;
            JNIEnv *aEnv = os_getJNIEnv(&aDetach);
            if (aEnv != 0) {
                jclass aClass = os_getClassID(aEnv);
                if (aClass != 0) {
                    aMethodID = aEnv->GetMethodID(aClass, "deleteThreadLock", "(I)V");
                    if (aMethodID) {
                        aEnv->CallVoidMethod(_objJNIHelper, aMethodID, pLockIndex);
                    }
                }
            }
        }
    }
}

void os_delete_all_thread_locks() {
        jmethodID aMethodID = 0;
        if (gJVM != 0) {
            bool aDetach = false;
            JNIEnv *aEnv = os_getJNIEnv(&aDetach);
            if (aEnv != 0) {
                jclass aClass = os_getClassID(aEnv);
                if (aClass != 0) {
                    aMethodID = aEnv->GetMethodID(aClass, "deleteAllThreadLocks", "()V");
                    if (aMethodID) {
                        aEnv->CallVoidMethod(_objJNIHelper, aMethodID);
                    }
                }
            }
        }
}

void os_lock_thread(int pLockIndex) {
    if (pLockIndex >= 0) {
        jmethodID aMethodID = 0;
        if (gJVM != 0) {
            bool aDetach = false;
            JNIEnv *aEnv = os_getJNIEnv(&aDetach);
            if (aEnv != 0) {
                jclass aClass = os_getClassID(aEnv);
                if (aClass != 0) {
                    aMethodID = aEnv->GetMethodID(aClass, "lockThread", "(I)V");
                    if (aMethodID) {
                        aEnv->CallVoidMethod(_objJNIHelper, aMethodID, pLockIndex);
                    }
                }
            }
        }
    }
}

void os_unlock_thread(int pLockIndex) {
    if (pLockIndex >= 0) {
        jmethodID aMethodID = 0;
        if (gJVM != 0) {
            bool aDetach = false;
            JNIEnv *aEnv = os_getJNIEnv(&aDetach);
            if (aEnv != 0) {
                jclass aClass = os_getClassID(aEnv);
                if (aClass != 0) {
                    aMethodID = aEnv->GetMethodID(aClass, "unlockThread", "(I)V");
                    if (aMethodID) {
                        aEnv->CallVoidMethod(_objJNIHelper, aMethodID, pLockIndex);
                    }
                }
            }
        }
    }
}


bool os_fileExists(const char *pFilePath) {
    bool aReturn = false;
    jmethodID aMethodID = 0;
    if ((gJVM != 0) && (pFilePath != 0)) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        if (aEnv != 0) {
            jclass aClass = os_getClassID(aEnv);
            if (aClass != 0) {
                aMethodID = aEnv->GetMethodID(aClass, "fileExists", "(Ljava/lang/String;)Z");
                if (aMethodID) {
                    jstring aPath = aEnv->NewStringUTF(pFilePath);
                    aReturn = aEnv->CallBooleanMethod(_objJNIHelper, aMethodID, aPath);
                    aEnv->DeleteLocalRef(aPath);
                }
            }
        }
    }

    return aReturn;
}

bool os_fileExists(FString pFilePath) {
    return os_fileExists((const char *)(pFilePath.c()));
}

bool os_is_portrait() {
#ifdef ORIENTATION_LANDSCAPE
    return false;
#else
    return true;
#endif
    
}

//#define NANOS_IN_SECOND 1000000000
unsigned int os_system_time() {
    unsigned long aMili =
            chrono::system_clock::now().time_since_epoch() /
            chrono::milliseconds(1);
    return (unsigned int)aMili;

    //    struct timespec res;
    //    clock_gettime(CLOCK_MONOTONIC, &res);
    //    return (res.tv_sec * NANOS_IN_SECOND) + res.tv_nsec;

}

unsigned char *os_read_file(const char *pFileName, unsigned int &pLength) {
    pLength = 0;
    unsigned char *aData = 0;
    jmethodID aMethodID = 0;
    if((gJVM != 0) && (pFileName != 0)) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        jclass aClass = os_getClassID(aEnv);
        if ((aEnv != 0) && (aClass != 0)) {
            aMethodID = aEnv->GetMethodID(aClass, "readFileLength", "(Ljava/lang/String;)I");
            if(aMethodID) {
                jstring aFileName = aEnv->NewStringUTF(pFileName);
                pLength = aEnv->CallIntMethod(_objJNIHelper, aMethodID, aFileName);
                if (pLength > 0) {
                    aMethodID = aEnv->GetMethodID(aClass, "readFileData", "(Ljava/lang/String;[B)V");
                    if (aMethodID) {
                        jbyteArray aArray = aEnv->NewByteArray(pLength + 1);
                        aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aFileName, aArray);
                        jbyte *aByte = aEnv->GetByteArrayElements(aArray, 0);
                        aData = new unsigned char [pLength];
                        memcpy(aData, aByte, pLength);
                        aEnv->ReleaseByteArrayElements(aArray, aByte, 0);
                        aEnv->DeleteLocalRef(aArray);
                    } else {
                        pLength = 0;
                    }
                } else {
                    pLength = 0;
                }
                aEnv->DeleteLocalRef(aFileName);
            }
        }
    }
    return aData;
}

bool os_write_file(const char *pFileName, unsigned char *pData, unsigned int pLength) {
    bool aReturn = false;
    jmethodID aMethodID = 0;

    if ((gJVM != 0) && (pFileName != 0) && (pLength > 0)) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        jclass aClass = os_getClassID(aEnv);

        if ((aEnv != 0) && (aClass != 0)) {
            aMethodID = aEnv->GetMethodID(aClass, "writeFileData", "(Ljava/lang/String;[BI)Z");
            if (aMethodID) {
                jbyteArray aArray = aEnv->NewByteArray(pLength + 1);
                jbyte *aByte = aEnv->GetByteArrayElements(aArray, 0);

                memcpy(aByte, pData, pLength);

                jstring aPath = aEnv->NewStringUTF(pFileName);
                aReturn = aEnv->CallBooleanMethod(_objJNIHelper, aMethodID, aPath, aArray, pLength);
                aEnv->DeleteLocalRef(aPath);

                if ((aReturn == false) && (gDirDocuments.mLength > 0)) {
                    FString aDocPath = gDirDocuments + pFileName;
                    aPath = aEnv->NewStringUTF(aDocPath.c());
                    aReturn = aEnv->CallBooleanMethod(_objJNIHelper, aMethodID, aPath, aArray, pLength);
                    aEnv->DeleteLocalRef(aPath);
                }
                aEnv->ReleaseByteArrayElements(aArray, aByte, 0);
                aEnv->DeleteLocalRef(aArray);
            }
        }
    }
    return aReturn;
}

FString os_getBundleDirectory()
{
    FString aPath;
    aPath += "/";
    
    Log("Bundle: [%s]\n", aPath.c());
    
    return aPath;
}

FString os_getDocumentsDirectory() {
    FString aPath;
    aPath += "/";
    
    Log("Documents: [%s]\n", aPath.c());
    
    return aPath;
}

void os_load_image_to_buffer(char *pFile, unsigned int *pData)
{
    jmethodID aMethodID;
    bool aDetach = false;
    JNIEnv *aEnv = os_getJNIEnv(&aDetach);

    if (aEnv) {
        jstring aJavaFileName = aEnv->NewStringUTF(pFile);
        aMethodID = aEnv->GetMethodID(_clsJNIHelper, "loadBitmap", "(Ljava/lang/String;)Landroid/graphics/Bitmap;");

        jobject aBitmap = aEnv->CallObjectMethod(_objJNIHelper, aMethodID, aJavaFileName);
        aEnv->DeleteLocalRef(aJavaFileName);

        if (aBitmap) {
            aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapWidth", "(Landroid/graphics/Bitmap;)I");
            int aWidth = aEnv->CallIntMethod(_objJNIHelper, aMethodID, aBitmap);

            aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapHeight", "(Landroid/graphics/Bitmap;)I");
            int aHeight = aEnv->CallIntMethod(_objJNIHelper, aMethodID, aBitmap);

            if ((aWidth > 0) && (aHeight > 0)) {
                int aArea = aWidth * aHeight;

                jintArray aArray = aEnv->NewIntArray(aArea);

                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapPixels", "(Landroid/graphics/Bitmap;[I)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap, aArray);

                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "closeBitmap", "(Landroid/graphics/Bitmap;)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap);

                //aData = new unsigned int[aArea];
                jint *aPixels = aEnv->GetIntArrayElements(aArray, 0);

                unsigned char *aPixelBytesOriginal = (unsigned char *)aPixels;
                unsigned char *aDataBytesOriginal = (unsigned char *)pData;

                unsigned char *aPixelBytes = aPixelBytesOriginal;
                unsigned char *aDataBytes = aDataBytesOriginal;

                int aByteLength = aArea * 4;

                unsigned char *aPixelShelf = &(aPixelBytesOriginal[aByteLength]);

                aPixelBytes = &(aPixelBytesOriginal[2]);
                aDataBytes = &(aDataBytesOriginal[0]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[1]);
                aDataBytes = &(aDataBytesOriginal[1]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[0]);
                aDataBytes = &(aDataBytesOriginal[2]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[3]);
                aDataBytes = &(aDataBytesOriginal[3]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aEnv->ReleaseIntArrayElements(aArray, aPixels, 0);
                aEnv->DeleteLocalRef(aArray);
            }
            else
            {
                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "closeBitmap", "(Landroid/graphics/Bitmap;)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap);
            }
        }
        if (aDetach) {
            //gJVM->DetachCurrentThread();
        }
    }
}

unsigned int *os_load_image(char *pFile,int &pWidth, int &pHeight) {
    pWidth = 0;
    pHeight = 0;


    unsigned int *aData = 0;

    jmethodID aMethodID;
    bool aDetach = false;
    JNIEnv *aEnv = os_getJNIEnv(&aDetach);

    if(aEnv)
    {
        jstring aJavaFileName = aEnv->NewStringUTF(pFile);
        aMethodID = aEnv->GetMethodID(_clsJNIHelper, "loadBitmap", "(Ljava/lang/String;)Landroid/graphics/Bitmap;");

        jobject aBitmap = aEnv->CallObjectMethod(_objJNIHelper, aMethodID, aJavaFileName);
        aEnv->DeleteLocalRef(aJavaFileName);

        if (aBitmap) {

            aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapWidth", "(Landroid/graphics/Bitmap;)I");
            pWidth = aEnv->CallIntMethod(_objJNIHelper, aMethodID, aBitmap);

            aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapHeight", "(Landroid/graphics/Bitmap;)I");
            pHeight = aEnv->CallIntMethod(_objJNIHelper, aMethodID, aBitmap);

            if ((pWidth > 0) && (pHeight > 0)) {
                int aArea = pWidth * pHeight;

                jintArray aArray = aEnv->NewIntArray(aArea);

                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "getBitmapPixels", "(Landroid/graphics/Bitmap;[I)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap, aArray);

                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "closeBitmap", "(Landroid/graphics/Bitmap;)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap);

                aData = new unsigned int[aArea];
                jint *aPixels = aEnv->GetIntArrayElements(aArray, 0);

                unsigned char *aPixelBytesOriginal = (unsigned char *)aPixels;
                unsigned char *aDataBytesOriginal = (unsigned char *)aData;

                unsigned char *aPixelBytes = aPixelBytesOriginal;
                unsigned char *aDataBytes = aDataBytesOriginal;

                int aByteLength = aArea * 4;

                unsigned char *aPixelShelf = &(aPixelBytesOriginal[aByteLength]);

                aPixelBytes = &(aPixelBytesOriginal[2]);
                aDataBytes = &(aDataBytesOriginal[0]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[1]);
                aDataBytes = &(aDataBytesOriginal[1]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[0]);
                aDataBytes = &(aDataBytesOriginal[2]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aPixelBytes = &(aPixelBytesOriginal[3]);
                aDataBytes = &(aDataBytesOriginal[3]);
                while(aPixelBytes < aPixelShelf)
                {
                    *aDataBytes = *aPixelBytes;
                    aPixelBytes += 4;
                    aDataBytes += 4;
                }

                aEnv->ReleaseIntArrayElements(aArray, aPixels, 0);
                aEnv->DeleteLocalRef(aArray);
            }
            else
            {
                aMethodID = aEnv->GetMethodID(_clsJNIHelper, "closeBitmap", "(Landroid/graphics/Bitmap;)V");
                aEnv->CallVoidMethod(_objJNIHelper, aMethodID, aBitmap);

                pWidth = 0;
                pHeight = 0;
            }
        }
    }
    if (aDetach) {
        //gJVM->DetachCurrentThread();
    }
    return aData;
}

void os_exportPNGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight) {
    
}

void os_exportJPEGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight, float pQuality) {
    
}

void os_exportToPhotoLibrary(unsigned int *pData, int pWidth, int pHeight) {
    
}


bool os_createDirectory(const char *pDirectory)
{
    bool aReturn = false;
    
    
    return aReturn;
}


void os_getTestDirectory(FString *pString) {
    if (pString) {
        pString->Set("/Users/nraptis/Desktop/Exports/");
    }
}

void os_getFilesInDirectory(const char *pFilePath, FList *pList) {
    
}

void os_getFilesInDirectoryRecursive(const char *pFilePath, FList *pList) {
    if(pList)
    {
    DIR *dp;
    
    struct dirent *ep;
    
    dp = opendir ("./");
    char sf[1024];
    
    if(dp != NULL)
    {
        ep = readdir(dp);
        if(ep)
        {
            //aLoops1++;
            //Log("LOOPS1 = %d\n", aLoops1);
            
            //{
                
                char *n;
                DIR *dirp;
                struct dirent *direntp;
                
                dirp = opendir(pFilePath);
                
                if(dirp != NULL)
                {
                    //aLoops2 = 0;
                    for(;;)
                    {
                        //aLoops2++;
                        //Log("\tLOOPS2 = %d\n", aLoops2);
                        direntp = readdir( dirp );
                        
                        if(direntp == NULL)
                        {
                            break;
                        }
                        
                        n=direntp->d_name;
                        if (strcmp(n,".")!=0 && strcmp(n,"..")!=0)
                        {
                            strcpy(sf, pFilePath);
                            strcat(sf,n);
                            
                            FString *aString = new FString(sf);
                            
                            Log("FileDir = [%s]\n", aString->c());
                            
                            pList->Add(aString);
                            
                            //remove(sf);
                        }
                        
                        
                    }
                    closedir( dirp );
                    
                }
            }
            
            //puts (ep->d_name);
        //}
        
        //(void)closedir(dp);
    }
    }
}

void os_getAllResources(const char *pFilePath, FList *pList)
{
    
}
