# Sprint 3 - Edge Computing

## Sobre o Projeto
Este projeto é baseado no desenvolvimento de uma aplicação IoT utilizando ESP32. A aplicação é capaz de medir a distância usando um sensor ultrassônico e controlar LEDs com base na distância medida. 

## Arquitetura

A arquitetura proposta para a solução IoT é composta pelos seguintes componentes:

- **Dispositivos IoT**: ESP32, que mede a distância com um sensor HC-SR04 e controla os LEDs.
- **Broker MQTT**: Utiliza o Mosquitto como broker para gerenciar a comunicação entre os dispositivos.
- **Dashboard**: Um dashboard desenvolvido no Node-RED para visualização dos dados.

## Bibliotecas Necessárias

- **WiFi.h**: Gerencia a coneção WI-FI.
- **PubSubClient**: Implementa o protocolo MQTT para envio e recebimento de informações.

## Requisitos

- **Hardware**:
  - ESP32
  - Sensor Ultrassônico (HC-SR04)
  - 4 LEDs
  - Resistores (se necessário)

- **Software**:
  - Arduino IDE
  - Broker MQTT  
  - Node-RED

## Instruções de Uso

Pode ser utilizado em um simulador, como o wokwi ou em uma placa ESP32 real.

Para visualizar o projeto feito no simulador, aperte [aqui](https://wokwi.com/projects/410501970995056641).

## Vídeo Explicativo 

Aperte [aqui](https://www.youtube.com/watch?v=r8OXlSqdqfM) para acessar vídeo explicativo sobre esse projeto.

## Integrantes 

- Arnaldo Filho -    RM 555780
- Diego Cabral -     RM 557817
- Debora Ivanowski - RM 555694