
#define SENSOR_INTERVAL 2000
#include "env.h"

#include <AsyncTimer.h>
#include "./Wifi/WifiService.h"
#include <WiFiClientSecure.h>
WiFiClientSecure client;
#include <AsyncTelegram2.h>
AsyncTelegram2 instance(client);

#include "./Camera/CameraService.h"
#include "./Telegram/TelegramService.h"
#include "./Sensores/ChamaService.h"
#include "./Sensores/GasService.h"

WifiService wifi;
TelegramService telegram;
CameraService camera;
AsyncTimer t;
ChamaService sensorChama;
GasService sensorGas;

int CHAMA_PIN = 2;
int GAS_PIN = 14;

void setup()
{

  Serial.begin(115200);
  Serial.println();

  pinMode(CHAMA_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);

  wifi.startConnection();

  telegram.start();

  camera.init_camera();

  Serial.println("Sensor Started...");
  t.setup();
  sensorsRead();
}

void sensorsRead()
{

  t.setInterval([]()
  {

    if (sensorChama.warning(CHAMA_PIN))
    {
      sensorChama.print();
      instance.sendTo(userid, "ALERTA!!! TA PEGANDO FOGO BICHO.");
      camera.sendPicture(userid, instance);
    }
    if (sensorGas.warning(GAS_PIN))
    { 
      sensorGas.print();
      instance.sendTo(userid, "ALERTA!!! AOOOOOOOO GAS.");
      camera.sendPicture(userid, instance);
    }

    telegram.getClientMessages(camera);
  },
  SENSOR_INTERVAL);
}

void loop()
{
  t.handle();
}
