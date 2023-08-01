/**
 * @file web_server.h
 * @author David Leval
 * @brief Web server
 * @version 0.1
 * @date 2023-08-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Arduino.h>

#ifndef __WEB_SERVER_H
#define __WEB_SERVER_H

#define DEBUG_WEB_SERVER 1

class WEB_SERVER
{
private:
    /* data */
public:
    WEB_SERVER(/* args */);
    ~WEB_SERVER();
    void begin(void);
};

extern WEB_SERVER web_server;

#endif //__WEB_SERVER_H
