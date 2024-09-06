# Projeto: Sistema de Detecção de Movimento com Arduino e MQTT

Este projeto consiste em um sistema de detecção de movimento utilizando um **Arduino Uno**, um **Ethernet Shield** e um **sensor de movimento SR501**. Os dados capturados pelo sensor são enviados para um servidor **MQTT**. Para receber as notificações, um aplicativo Android foi desenvolvido para alertar sobre possíveis invasões, exibindo a data e a hora da detecção.

## Tecnologias Utilizadas
- **Arduino Uno**: Microcontrolador utilizado para controlar o sensor de movimento.
- **Ethernet Shield**: Permite a comunicação com a rede via cabo Ethernet.
- **Sensor de Movimento SR501**: Detecta a presença de objetos em movimento.
- **MQTT**: Protocolo de comunicação utilizado para enviar os dados do Arduino para o servidor.
- **Servidor MQTT**: Utilizei tanto um servidor MQTT próprio quanto uma máquina virtual fornecida pelo **CEFET-RJ** para hospedar o broker.
- **Android**: O aplicativo foi desenvolvido em **Java** e exibe as notificações quando o sensor detecta movimento.

## Funcionalidades
1. **Detecção de Movimento**: O sensor SR501 é responsável por detectar qualquer presença no ambiente.
2. **Envio de Dados via MQTT**: Sempre que o sensor detecta movimento, o Arduino envia uma mensagem via protocolo MQTT para o servidor.
3. **Notificações no Aplicativo Android**: O aplicativo Android, conectado ao servidor MQTT, recebe as mensagens e exibe uma notificação com a data e hora da detecção, alertando sobre a presença de um possível invasor.

## Configuração do Ambiente

### Arduino
1. **Hardware**:
   - Arduino Uno
   - Ethernet Shield
   - Sensor de Movimento SR501
   - Cabos de conexão

2. **Software**:
   - **IDE Arduino** para programar o Arduino.
   - Código implementado para detectar movimento e enviar mensagens via MQTT.

### MQTT
- Um servidor MQTT foi configurado em uma máquina virtual fornecida pelo CEFET-RJ e, em paralelo, utilizei um broker MQTT próprio.

### Aplicativo Android
- Aplicativo construído em **Java** que se conecta ao servidor MQTT para receber e exibir notificações em tempo real.

## Instalação e Execução

### Arduino
1. Baixe e instale a **IDE Arduino** [aqui](https://www.arduino.cc/en/software).
2. Faça o upload do código para o Arduino.
3. Conecte o Arduino à rede via cabo Ethernet.

### Servidor MQTT
1. Instale e configure um broker MQTT. Eu utilizei o **Mosquitto**, disponível [aqui](https://mosquitto.org/download/).
2. Configure o broker na máquina virtual fornecida pelo **CEFET-RJ** ou utilize seu próprio servidor.

### Aplicativo Android
1. Baixe o APK ou compile o código fonte em **Android Studio**.
2. Conecte o aplicativo ao servidor MQTT para começar a receber notificações.

## Como Funciona
1. Quando o sensor SR501 detecta movimento, o Arduino envia uma mensagem via MQTT para o servidor.
2. O servidor MQTT transmite a mensagem para o aplicativo Android.
3. O aplicativo exibe uma notificação no dispositivo móvel com informações sobre o evento, como a data e a hora.

## Contribuições
Este projeto é aberto a contribuições. Sinta-se à vontade para sugerir melhorias.

