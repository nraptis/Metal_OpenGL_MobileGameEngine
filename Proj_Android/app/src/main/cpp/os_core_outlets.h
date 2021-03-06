//
// Copyright 2011 Tero Saarni
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

//Is "output" even the right word for this? It's the thing that talks TO the OS,
//It will eventually be responsible for loading images, sounds, and saving files...

#ifndef APP_OUTLETS_H
#define APP_OUTLETS_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <jni.h>

class FList;
class FString;

void Log(const char *pText, ...);

void os_initialize_outlets();

int os_getAssetScale();

void os_commitRender();

void os_sleep(int pTime);

unsigned int os_system_time();

void os_execute_on_main_thread(void (*pFunc)());

void os_detach_thread(void (*theFunction)(void *theArg), void* theArg);

bool os_updates_in_background();
bool os_draws_in_background();

int os_create_thread_lock();
bool os_thread_lock_exists(int pLockIndex);
void os_delete_thread_lock(int pLockIndex);
void os_delete_all_thread_locks();
void os_lock_thread(int pLockIndex);
void os_unlock_thread(int pLockIndex);

bool os_fileExists(const char *pFilePath);
bool os_fileExists(FString pFilePath);

unsigned char *os_read_file(const char *pFileName, unsigned int &pLength);
bool os_write_file(const char *pFileName, unsigned char *pData, unsigned int pLength);

void os_load_image_to_buffer(char *pFile, unsigned int *pData);
unsigned int *os_load_image(char *pFile, int &pWidth, int &pHeight);

void os_exportPNGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight);
void os_exportJPEGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight, float pQuality);
void os_exportToPhotoLibrary(unsigned int *pData, int pWidth, int pHeight);


bool os_createDirectory(const char *pDirectory);
//FString os_getTestDirectory();
void os_getTestDirectory(FString *pString);

void os_getFilesInDirectory(const char *pFilePath, FList *pList);
void os_getFilesInDirectoryRecursive(const char *pFilePath, FList *pList);

void os_getAllResources(const char *pFilePath, FList *pList);



JNIEnv *os_getJNIEnv(bool *pRequiresDetach);
jclass os_getClassID(JNIEnv *pEnv);
jmethodID os_getMethodInfo(const char *methodName, const char *paramCode);


void os_test_jre();
void os_test_click(float pX, float pY);
int os_test_load(const char *pChar);



#endif // JNIAPI_H
