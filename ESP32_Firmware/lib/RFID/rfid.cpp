/**
 * @file rfid.cpp
 * @author David Leval
 * @version 0.1
 * @date 2023-08-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "rfid.h"
#include <Wire.h>
#include "MFRC522_I2C.h"

#if DEBUG_RFID == 1
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTF(x, args...) Serial.printf(x, ##args)
#define DEBUG_WRITE(x) Serial.write(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#define DEBUG_PRINTF(x, args...)
#define DEBUG_WRITE(x)
#endif

MFRC522 mfrc522(0x28);

RFID::RFID(/* args */)
{
}

RFID::~RFID()
{
}

void RFID::begin(void)
{
    DEBUG_PRINTLN("Init MFRC522 module");
    Wire.begin(26, 32, 100000UL);
    mfrc522.PCD_Init();
}

bool RFID::check_badge(void)
{
    uint8_t i;

    if (mfrc522.PICC_IsNewCardPresent())
    {
        if(mfrc522.PICC_ReadCardSerial())
        {
            for (i = 0; i < sizeof(uid_data); i++)
            {
                uid_data[i] = 0;
            }

            for (i = 0; i < mfrc522.uid.size; i++)
            {
                DEBUG_PRINT(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                DEBUG_PRINTF("0x%02X", mfrc522.uid.uidByte[i]);
                uid_data[i] = mfrc522.uid.uidByte[i];
            }
            DEBUG_PRINTLN("");

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

RFID rfid;
