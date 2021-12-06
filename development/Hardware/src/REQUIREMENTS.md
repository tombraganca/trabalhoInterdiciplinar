# REQUISITOS

### Instalar Bibliotecas pelo Arduino IDE
`Ferramenta> Gerenciar Bibliotecas...> Procurar e Instalar`

- > ArduinoJson | v6+
- > AsyncTelegram2 | 2.0.4
- > AsyncTimer | 2.1.2

### VScode Setup
- > Instalar Extensão [Arduino](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)


### Configuração Arduino no VScode
- > Criar Arquivo .vscode/arduino.json
```
{
    "board": "esp32:esp32:esp32wrover",
    "configuration": "PartitionScheme=huge_app,FlashMode=qio,FlashFreq=40,UploadSpeed=115200,DebugLevel=none",
    "sketch": "telebot.ino",
    "port": "/dev/ttyACM0"
}
```
### Váriaveis de Ambiente
- renomear arquivo env.exemplo.h para env.h
- preencher informações do Wifi/Telegram


### Execução 
- > Selecionar arquivo Telebot.ino
- > fazer o Upload
