/******************************************************************************
 * Copyright 2018 Google
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#if defined(ARDUINO_SAMD_MKR1000) or defined(ESP32)
#define _SKIP_ESP8266_
#endif

#if defined(ESP8266)
#define _ESP8266_MQTT_
#endif

#ifdef _SKIP_ESP8266_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WifiClientSecure.h>

void setup(){
  Serial.begin(115200);
}

void loop(){
  Serial.println("Hello World");
}

#endif

#ifdef _ESP8266_MQTT_
#include <CloudIoTCore.h>
#include "esp8266_mqtt.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

char buffer[100];
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupCloudIoT(); // Creates globals for MQTT
  pinMode(LED_BUILTIN, OUTPUT);
}

static unsigned long lastMillis = 0;
void loop()
{
  if (!mqtt->loop())
  {
    mqtt->mqttConnect();
  }

  delay(10); // <- fixes some issues with WiFi stability

  // TODO: Replace with your code here
  if (millis() - lastMillis > 60000)
  {
    lastMillis = millis();
    float tes = 1.0;
//    StaticJsonDocument<100> doc; 
//    doc["tes"] = tes;
//    serializeJson(doc, buffer);
    publishTelemetry(getDefaultSensor());
  }
}
#endif
