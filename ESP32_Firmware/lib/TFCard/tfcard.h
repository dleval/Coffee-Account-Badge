/**
 * @file tfcard.h
 * @author David Leval
 * @brief TF Card module
 * @version 0.1
 * @date 2023-08-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include "FS.h"
#include "SD.h"

#ifndef __TFCARD_H
#define __TFCARD_H

#define DEBUG_TFCARD    1

class TFCARD
{
private:
    /* data */
public:
    TFCARD(/* args */);
    ~TFCARD();
    void begin(void);
    void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
    void createDir(fs::FS &fs, const char *path);
    void removeDir(fs::FS &fs, const char *path);
    void readFile(fs::FS &fs, const char *path);
    void writeFile(fs::FS &fs, const char *path, const char *message);
    void appendFile(fs::FS &fs, const char *path, const char *message);
    void renameFile(fs::FS &fs, const char *path1, const char *path2);
    void deleteFile(fs::FS &fs, const char *path);
};

extern TFCARD tfcard;

#endif //__TFCARD_H
