
#define SENSOR_INTERVAL 2000
#define ALERT_INTERVAL 500
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
#include "./Sensores/TempService.h"
#include "./Telegram/TelegramService.h"
#include "./Sensores/ChamaService.h"
#include "./Sensores/GasService.h"
#include "./Sensores/AlertService.h"

int CHAMA_PIN = 2;
int GAS_PIN = 14;
int BUZZER_PIN = 12;
bool ALERT = false;

WifiService wifi;
TempService temp;
TelegramService telegram;
CameraService camera;
AsyncTimer t;
ChamaService sensorChama;
GasService sensorGas;
AlertService alertBuzzer;

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
                  bool isChama = sensorChama.warning(CHAMA_PIN);
                  bool isGas = sensorGas.warning(GAS_PIN);
                  if (isChama)
                  {
                    sensorChama.print();
                    ALERT = true;
                    instance.sendTo(userid, "ALERTA!!! TA PEGANDO FOGO BICHO.");
                    camera.sendPicture(userid, instance);
                  }
                  
                  if (isGas)
                  {
                    sensorGas.print();
                    ALERT = true;
                    instance.sendTo(userid, "ALERTA!!! AOOOOOOOO GAS.");
                    camera.sendPicture(userid, instance);
                  }

          
                  if(!isGas && !isChama)
                  {
                    ALERT = false;
                  }

                  telegram.getClientMessages(camera, temp);
                },
                SENSOR_INTERVAL);
}

void alertStart()
{
  t.setInterval([]()
                {
                  if (ALERT)
                  {
                    alertBuzzer.execute();
                  }
                  else
                  {
                    alertBuzzer.stop();
                  }
                },
                ALERT_INTERVAL);
}

void loop()
{
  t.handle();
}
