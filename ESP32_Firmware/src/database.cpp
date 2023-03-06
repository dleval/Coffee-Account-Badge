/**
 * @file database.cpp
 * @author David Leval
 * @brief 
 * @version 0.1
 * @date 2023-03-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "database.h"
#include <ArduinoJson.h>

StaticJsonDocument<8192> json_db;

database db;

database::database(/* args */)
{
}

database::~database()
{
}

void database::read_json_file(fs::FS &fs, const char * path)
{
   Serial.printf("Reading file: %s\r\n", path);

   File file = fs.open(path);
   if(!file || file.isDirectory()){
       Serial.println("− failed to open file for reading");
       return;
   }

  //  Serial.println("− read from file:");
  //  while(file.available()){
  //     Serial.write(file.read());
  //  }

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(json_db, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));
 
  serializeJsonPretty(json_db, Serial);
  Serial.println(json_db.size());
  JsonArray repos = json_db["db"];
  for (JsonObject repo : repos) {
    const char* name = repo["Name"];
    Serial.println(name);
  }



  file.close();
}

