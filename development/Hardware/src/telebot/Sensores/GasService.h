#ifndef GAS_SERVICE_H
#define GAS_SERVICE_H

class GasService
{
private:
    int _GAS_READ = -1;

public:
    bool warning(int GAS_PIN)
    {
        _GAS_READ = digitalRead(GAS_PIN);
        return _GAS_READ == 0;
    }

    void print()
    {
        Serial.print("Leitura gas: ");
        Serial.print(_GAS_READ == 0 ? "TRUE" : "FALSE");
        Serial.println("");
    }
};
#endif // !GAS_SERVICE_H