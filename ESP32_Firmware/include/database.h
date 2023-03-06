/**
 * @file database.h
 * @author David Leval
 * @brief 
 * @version 0.1
 * @date 2023-03-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _DATABASE_H
#define _DATABASE_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "SPIFFS.h"

class database
{
private:
    /* data */
public:
    database(/* args */);
    ~database();
    void read_json_file(fs::FS &fs, const char * path);
};


extern database db;



#endif //_DATABASE_H
