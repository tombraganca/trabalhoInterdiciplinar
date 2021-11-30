#ifndef TEMPERATURE_SERVICE_H
#define TEMPERATURE_SERVICE_H

#include "DHT.h"


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
    }

    void read()
    {
        umidade = dht.readHumidity();
        temp = dht.readTemperature();

    }

    void print()
    {
        if (isnan(temp) || isnan(umidade))
        {
            Serial.println("Falha na leitura DHT11");
        }
        else
        {
            Serial.print("Umidade: ");
            Serial.print(umidade);
            Serial.print(" %t");
            Serial.print("Temperatura: ");
            Serial.print(temp);
            Serial.println(" *C");
        }
    }
};
#endif // !TEMPERATURE_SERVICE_H