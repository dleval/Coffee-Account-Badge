/**
 * @file tfcard.cpp
 * @author David Leval
 * @version 0.1
 * @date 2023-08-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "M5Atom.h"
#include <SPI.h>
#include "tfcard.h"

#if DEBUG_TFCARD == 1
  #define DEBUG_PRINTLN(x)              Serial.println (x)
  #define DEBUG_PRINT(x)                Serial.print (x)
  #define DEBUG_PRINTF(x, args...)      Serial.printf (x, ## args)
  #define DEBUG_WRITE(x)                Serial.write(x)
#else
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTF(x, args...)
  #define DEBUG_WRITE(x)
#endif


TFCARD::TFCARD(/* args */)
{
}

TFCARD::~TFCARD()
{
}

void TFCARD::begin(void)
{
    SPI.begin(23, 33, 19, -1);

    if (!SD.begin(22, SPI, 10000000)) {
        DEBUG_PRINTLN("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE) {
        DEBUG_PRINTLN("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC) {
        DEBUG_PRINTLN("MMC");
    } else if (cardType == CARD_SD) {
        DEBUG_PRINTLN("SDSC");
    } else if (cardType == CARD_SDHC) {
        DEBUG_PRINTLN("SDHC");
    } else {
        DEBUG_PRINTLN("UNKNOWN");
    }
}

void TFCARD::listDir(fs::FS &fs, const char *dirname, uint8_t levels) 
{
    DEBUG_PRINTF("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root) {
        DEBUG_PRINTLN("Failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        DEBUG_PRINTLN("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            DEBUG_PRINT("  DIR : ");
            DEBUG_PRINTLN(file.name());
            if (levels) {
                listDir(fs, file.name(), levels - 1);
            }
        } else {
            DEBUG_PRINT("  FILE: ");
            DEBUG_PRINT(file.name());
            DEBUG_PRINT("  SIZE: ");
            DEBUG_PRINTLN(file.size());
        }
        file = root.openNextFile();
    }
}

void TFCARD::createDir(fs::FS &fs, const char *path) 
{
    DEBUG_PRINTF("Creating Dir: %s\n", path);
    if (fs.mkdir(path)) {
        DEBUG_PRINTLN("Dir created");
    } else {
        DEBUG_PRINTLN("mkdir failed");
    }
}

void TFCARD::removeDir(fs::FS &fs, const char *path) 
{
    DEBUG_PRINTF("Removing Dir: %s\n", path);
    if (fs.rmdir(path)) {
        DEBUG_PRINTLN("Dir removed");
    } else {
        DEBUG_PRINTLN("rmdir failed");
    }
}

void TFCARD::readFile(fs::FS &fs, const char *path) 
{
    DEBUG_PRINTF("Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file) {
        DEBUG_PRINTLN("Failed to open file for reading");
        return;
    }

    DEBUG_PRINT("Read from file: ");
    while (file.available()) {
        DEBUG_WRITE(file.read());
    }
    file.close();
}

void TFCARD::writeFile(fs::FS &fs, const char *path, const char *message) 
{
    DEBUG_PRINTF("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file) {
        DEBUG_PRINTLN("Failed to open file for writing");
        return;
    }
    if (file.print(message)) {
        DEBUG_PRINTLN("File written");
    } else {
        DEBUG_PRINTLN("Write failed");
    }
    file.close();
}

void TFCARD::appendFile(fs::FS &fs, const char *path, const char *message) 
{
    DEBUG_PRINTF("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if (!file) {
        DEBUG_PRINTLN("Failed to open file for appending");
        return;
    }
    if (file.print(message)) {
        DEBUG_PRINTLN("Message appended");
    } else {
        DEBUG_PRINTLN("Append failed");
    }
    file.close();
}

void TFCARD::renameFile(fs::FS &fs, const char *path1, const char *path2) 
{
    DEBUG_PRINTF("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        DEBUG_PRINTLN("File renamed");
    } else {
        DEBUG_PRINTLN("Rename failed");
    }
}

void TFCARD::deleteFile(fs::FS &fs, const char *path) 
{
    DEBUG_PRINTF("Deleting file: %s\n", path);
    if (fs.remove(path)) {
        DEBUG_PRINTLN("File deleted");
    } else {
        DEBUG_PRINTLN("Delete failed");
    }
}

TFCARD tfcard;
