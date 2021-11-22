#ifndef CHAMA_SERVICE_H
#define CHAMA_SERVICE_H

class ChamaService
{
private:
    int _CHAMA_READ = -1;

public:
    bool warning(int CHAMA_PIN)
    {
        _CHAMA_READ = digitalRead(CHAMA_PIN);
        return _CHAMA_READ == 0;
    }

    void print()
    {
        Serial.print("Leitura chama: ");
        Serial.print(_CHAMA_READ == 0 ? "TRUE" : "FALSE");
        Serial.println("");
    }
};

#endif // !CHAMA_SERVICE_H
