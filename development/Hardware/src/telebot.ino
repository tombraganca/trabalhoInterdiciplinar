
#include "env.h"

#include "./Wifi/WifiService.h"
#include <WiFiClientSecure.h>
WiFiClientSecure client;
#include <AsyncTelegram2.h>
AsyncTelegram2 instance(client);

#include "./Camera/CameraService.h"
#include "./Telegram/TelegramService.h"

WifiService wifi;
TelegramService telegram;
CameraService camera;

void setup() {  

  Serial.begin(115200);
  Serial.println();

  wifi.startConnection();

  telegram.start();

  camera.init_camera();
}

void loop() {
  telegram.getClientMessages(camera);
}
