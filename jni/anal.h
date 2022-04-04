#ifndef ANAL_H
#define ANAL_H

#include <android/log.h>

#define  LOG_TAG    "ANAL2.0b"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define DEPTH_TEXTURE
#define FINAL
#define SYNC_PLAYER
//#define DISKWRITE
//#define DISKWRITE_START 6000
//#define DISKWRITE_END 6999
//#define DISKWRITE_FPS 30.0


typedef struct {
  unsigned char *data;
  unsigned int size;
} Assetloader;

Assetloader loadasset(char *filename);

#endif