#ifndef ALERT_SERVICE_H
#define ALERT_SERVICE_H

class AlertService
{
private:
    bool active = false;
    int ALERT_PIN;

public:
    void init(int pin)
    {
        ALERT_PIN = pin;
        pinMode (ALERT_PIN, OUTPUT);
    }

    void execute()
    {
        if (active)
        {
            digitalWrite (ALERT_PIN, LOW);
            active = false;
        }
        else
        {
            digitalWrite(ALERT_PIN, HIGH);
            active = true;
        }
    }

    void print()
    {
        Serial.print("Alerta Sonoro: ");
        Serial.print(active ? "Ativo" : "Desativo");
        Serial.println("");
    }
};
#endif // !ALERT_SERVICE_H