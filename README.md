# Trabalho Interdiciplinar
## INTEGRAÇÃO DE UM BOT DO TELEGRAM COM ESP32 <br> PARA MONITORAMENTO DE DADOS DE RISCO DE SEGURANÇA

## 1. INTRODUÇÃO E OBJETIVO
> Os sistemas embarcados estão por toda parte: nos veículos, nos eletrodomésticos,
nos sistemas de monitoramento do clima em espaços urbanos, no agronegócio e
assim por diante. No entanto, um dos usos mais importantes dos sistemas
embarcados é com relação à segurança.
A razão para isso é simples: desde que utilizem sensores adequados para o que se
deseja monitorar e tenham os recursos para trabalhar (energia, conectividade, etc.),
os sistemas embarcados são como guardiões que trabalham 24 horas por dia, 7 dias
por semana, e quem eles raramente errarão em seu papel.
Assim, os sistemas embarcados são especialmente úteis em sistemas de segurança
críticos, como monitoramento e alarmes de incêndio, por exemplo.
Portanto, este trabalho tem por objetivo o desenvolvimento de um software em
hardware que será integrado a um bot a ser desenvolvido no telegram para
monitoramento de condições de risco de incêndio.
Assim, de qualquer lugar do mundo, você poderá saber sobre qualquer situação
perigosa em relação aos gases inflamáveis, o que pode ser muito útil para
monitoramento remoto e ação rápida em caso de incêndio.

## 2. FUNCIONALIDADES

> O projeto como um todo se dividirá na construção do bot responsável por receber e
manter o usuário informado sobre possíveis riscos e na programação do hardware
(ESP32) para captação dos sinais do ambiente.
Para o monitoramento de riscos de incêndio irá-se utilizar o sensor MQ-2 que
consegue detectar gases inflamáveis e fumaça. Para estabelecer a comunicação
entre o o ESP32 e o Telegram será utilizado uma biblioteca especial que permite o
envio de parâmetros de forma bidirecional entre o hardware e o BOT.
Com o intuito de melhor entender o processo de comunicação entre hardware e
software e a fim de tentar construir um processo que, não somente monitora, mas
também controla, poderá ser construído uma funcionalidade que diz respeito a dar
ordens ao BOT para controle de atuadores conectados ao hardware.
Posto tudo isso, caso o sistema identifique algum risco o BOT poderá acionar as
autoridades de segurança do estado como, por exemplo, o corpo de bombeiros e,
além disso, poderá notificar a vizinhança de possível risco de incêndio ao redor.Por
fim, com perspectivas futuras de evolução do projeto, pensa-se na integração de
outros sensores ao projeto que teriam também um propósito de segurança e
poderiam fazer com que o BOT notificasse a autoridade pública competente a
aquele risco.

## 3. RECURSOS
### 3.1. HARDWARE
> - Esp32
> - Sensor de detecção de fumaça e gases inflamáveis (MQ-2)
### 3.2. SOFTWARE
> - Eclipse IDE for C/C++ Developers
> - NodeJS API integração Telegram

## Gerência de Projeto
* para mais detalhes [clique aqui](docs/gerenciaprojeto.md)
> - Termo de Abertura do Projeto (TAP)
> - Declaração de Escopo e EAP
> - Matriz RACI
> - Cronograma
> - Plano de Qualidade
> - Plano de Comunicação
> - Planejamento de Riscos

## Desenvolvimento

### Organização dos Arquivos
```

├── README.md (Arquivo de introdução)
├── docs/ (Documentos do Projeto)
├── development/ (Base de code)
│   ├── Hardware/ (Projeto do ESP32)
│   ├── Integration/ (Middleware de integração com Telegram)
└── Fim

```
# Participantes
> - Fernando [Github](https://github.com/feeluiz)
> -
> -
> -
