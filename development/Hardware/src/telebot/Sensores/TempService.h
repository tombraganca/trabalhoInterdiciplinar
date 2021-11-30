#ifndef TEMPERATURE_SERVICE_H
#define TEMPERATURE_SERVICE_H

#include "DHT.h"
#include <AsyncTelegram2.h>

DHT dht(DHTPIN, DHTTYPE);

class TempService
{
private:
    int TEMP_PIN;
    float umidade = -1.0;
    float temp = -1.0;

public:
    void init()
    {
        dht.begin();
        Serial.println("Sensor DHT11 iniciado.");
    }

    void read()
    {
        umidade = dht.readHumidity();
        temp = dht.readTemperature();
    }

    bool sendLecture(TBMessage &msg, AsyncTelegram2 telegram)
    {

        Serial.println("Leitura de temperatura iniciada.");

        read();
        char welcome_msg[64];
        if (isnan(temp) || isnan(umidade))
        {

            telegram.sendMessage(msg, "Falha na leitura DHT11.");
            Serial.println("Falha na leitura sensor DHT11.");
            return false;
        }
        else
        {
            char welcome_msg[64];
            snprintf(welcome_msg, 64, "Umidade: %0.2f %t \n Temperatura: %0.2f *C", umidade, temp);
            telegram.sendMessage(msg, welcome_msg);
        }
        return true;
    }
};
#endif // !TEMPERATURE_SERVICE_H