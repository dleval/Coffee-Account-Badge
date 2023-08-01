#include <Arduino.h>
#include "M5Atom.h"
#include "tfcard.h"
#include "rfid.h"
#include "web_server.h"

void setup()
{
    M5.begin(true, false, true);

    delay(2000);

    Serial.println("\n\r Coffee Badge Reader");

    tfcard.begin();

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    tfcard.listDir(SD, "/", 0);
    tfcard.readFile(SD, "/test.txt");

    rfid.begin();

    web_server.begin();
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (rfid.check_badge())
    {
        Serial.print(" UID readed: ");
        for(uint8_t i = 0; i < 10; i++)
        {
            Serial.printf(" 0x%02X", rfid.uid_data[i]);
        }
        Serial.println("");
    }
    delay(200);
}
