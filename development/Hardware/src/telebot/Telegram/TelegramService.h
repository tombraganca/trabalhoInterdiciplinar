#ifndef TELEGRAM_SERVICE_H
#define TELEGRAM_SERVICE_H

// Timezone definition to get properly time from NTP server
#define MYTZ "CET-1CEST,M3.5.0,M10.5.0/3"

class TelegramService
{
public:



    void start()
    {
        configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");

        client.setCACert(telegram_cert);

        instance.setUpdateTime(SENSOR_INTERVAL);
        instance.setTelegramToken(token);
        Serial.print("\nTestando conexao Telegram... ");
        instance.begin() ? Serial.println("OK") : Serial.println("NOK");

        char welcome_msg[67];
        snprintf(welcome_msg, 67, "BOT @%s online.\nTente com comando /foto ou /Temperatura.", instance.getBotName());
        instance.sendTo(userid, welcome_msg);
        started = true;
    };

    void getClientMessages(CameraService camera, TempService temp)
    {

        if(!started) {
            Serial.println("Erro, Eh necessario iniciar a classe antes. TelegramService.Start()");
            return;
        }

        TBMessage msg;

        if (instance.getNewMessage(msg))
        {
            Serial.print("Nova menssagem do chat_id: ");
            Serial.println(msg.sender.id);
            MessageType msgType = msg.messageType;

            if (msgType == MessageText)
            {

                if (msg.text.equalsIgnoreCase("/foto"))
                {
                    Serial.println("\nEnviando a foto da Camera");
                    if (camera.sendPicture(msg, instance))
                        Serial.println("Foto Enviada com Sucesso");
                    else
                        instance.sendMessage(msg, "Erro, falha no envio.");
                }else if (msg.text.equalsIgnoreCase("/temperatura"))
                {
                    Serial.println("\nEnviado Leitura");
                    if (temp.sendLecture(msg, instance))
                        Serial.println("Leitura Enviada com Sucesso");
                    else
                        instance.sendMessage(msg, "Erro, falha no envio.");
                }
                else
                {
                    Serial.print("\nMensagem Recebida: ");
                    Serial.println(msg.text);
                    String replyStr = "Mensagem Recebida:\n";
                    replyStr += msg.text;
                    replyStr += "\nTente o Comando /foto\n e /temperatura para leitura de umidade e temperatura";
                    instance.sendMessage(msg, replyStr);
                }
            }
        }
    }

private:
    bool started = false;
};

#endif //TELEGRAM_SERVICE_H
