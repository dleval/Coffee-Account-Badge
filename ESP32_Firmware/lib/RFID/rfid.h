/**
 * @file rfid.h
 * @author david Leval
 * @brief rfid module
 * @version 0.1
 * @date 2023-08-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>

#ifndef __RFID_H
#define __RFID_H

#define DEBUG_RFID    1

class RFID
{
private:
    
public:
    RFID(/* args */);
    ~RFID();
    void begin(void);
    bool check_badge(void);
    uint8_t uid_data[10];
};

extern RFID rfid;

#endif //__RFID_H
