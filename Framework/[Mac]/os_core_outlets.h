#ifndef APP_OUTLETS_MAX_H
#define APP_OUTLETS_MAX_H

#define Log printf

class FList;
class FString;

void os_initialize_outlets();

//Returns 0 if the device asset scale is not known.
//Otherwise returns the device asset scale...
int os_getAssetScale();

void os_detach_thread(void (*pFunction)(void *pArg), void *pArg);

bool os_fileExists(const char *pFilePath);

void os_sleep(int pTime);

unsigned int os_system_time();

bool os_updates_in_background();
bool os_draws_in_background();

int os_create_thread_lock();
bool os_thread_lock_exists(int pLockIndex);
void os_delete_thread_lock(int pLockIndex);
void os_delete_all_thread_locks();

void os_lock_thread(int pLockIndex);
void os_unlock_thread(int pLockIndex);

//void os_execute_on_main_thread(void (*pFunc)());

void os_message_box(const char *pTitle, const char *pBody);

unsigned char *os_read_file(const char *pFileName, unsigned int &pLength);
bool os_write_file(const char *pFileName, unsigned char *pData, unsigned int pLength);

void os_load_image_to_buffer(char *pFile, unsigned int *pData);
unsigned int *os_load_image(char *pFile, int &pWidth, int &pHeight);

bool os_createDirectory(const char *pDirectory);
void os_getFilesInDirectory(const char *pFilePath, FList *pList);
void os_getFilesInDirectoryRecursive(const char *pFilePath, FList *pList);

void os_getAllResources(const char *pFilePath, FList *pList);

void os_exportPNGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight);
void os_exportJPEGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight, float pQuality);
void os_exportToPhotoLibrary(unsigned int *pData, int pWidth, int pHeight);


#endif
