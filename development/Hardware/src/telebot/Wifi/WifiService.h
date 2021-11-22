#ifndef WIFI_SERVICE_H
#define WIFI_SERVICE_H


#include <WiFi.h>


class WifiService
{
public:

    void startConnection()
    {
        WiFi.begin(ssid, pass);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println(WiFi.localIP());
    }

private:
};

#endif //WIFI_SERVICE_H
