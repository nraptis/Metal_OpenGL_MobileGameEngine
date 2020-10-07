#ifndef APP_OUTLETS_H
#define APP_OUTLETS_H

#include "FString.hpp"
#include "FList.hpp"

#define Log printf

void os_initialize_outlets();

int os_getAssetScale();

void os_sleep(int pTime);

unsigned int os_system_time();

void os_detach_thread(void (*pFunction)(void *pArg), void *pArg);

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


void os_load_image_to_buffer(char *pFile, unsigned int *pData);
unsigned int *os_load_image(char *pFile, int &pWidth, int &pHeight);

bool os_createDirectory(const char *pDirectory);
//FString os_getTestDirectory();
void os_getTestDirectory(FString *pString);

void os_getFilesInDirectory(const char *pFilePath, FList *pList);
void os_getFilesInDirectoryRecursive(const char *pFilePath, FList *pList);

void os_getAllResources(const char *pFilePath, FList *pList);

void os_cloudPost(const char *pRecordName, const char *pIdentifier, const char *pFieldName, FString pData);
void os_cloudRead(const char *pRecordName, const char *pIdentifier, const char *pFieldName);


#endif // JNIAPI_H
