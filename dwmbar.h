#include <pthread.h>

void updateMemo(void* ptr);
void updateBL(void* ptr);
void updateVol(void* ptr);
void updateTime(void* ptr);
void update(void* ptr);
void flush(char** status);
void run(pthread_t* threadPtr, void (*func)(void* ptr), char** status);
