
#define SENSOR_INTERVAL 2000
#define ALERT_INTERVAL 1000
#define DHTPIN 15
#define DHTTYPE DHT11


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
#include "./Sensores/AlertService.h"
#include "./Sensores/TempService.h"

int CHAMA_PIN = 2;
int GAS_PIN = 14;
int BUZZER_PIN = 12;

WifiService wifi;
TelegramService telegram;
CameraService camera;
AsyncTimer t;
ChamaService sensorChama;
GasService sensorGas;
AlertService alertBuzzer;
TempService temp;

void setup()
{

  Serial.begin(115200);
  Serial.println();

  pinMode(CHAMA_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);
  temp.init();

  wifi.startConnection();

  telegram.start();

  camera.init_camera();

  alertBuzzer.init(BUZZER_PIN);

  Serial.println("Sensor Started...");
  t.setup();

  sensorsRead();
  alertStart();
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

                  temp.read();
                  temp.print();

                  telegram.getClientMessages(camera);
                },
                SENSOR_INTERVAL);
}

void alertStart()
{
  t.setInterval([]()
                { alertBuzzer.execute(); },
                ALERT_INTERVAL);
}

void loop()
{
  t.handle();
}
