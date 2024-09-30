# Projeto de Monitoramento de Temperatura e Umidade com ESP32 e MQTT

Este projeto visa monitorar em tempo real a temperatura e a umidade de ambientes utilizando um ESP32 conectado a um sensor DHT22. Os dados coletados são enviados para um broker MQTT via Wi-Fi, permitindo que outras aplicações acessem essas informações de maneira contínua e automatizada. Esta solução pode ser aplicada em diversos cenários, incluindo a Fórmula E, para monitoramento de condições ambientais críticas.

## Arquitetura Proposta

A solução proposta envolve três componentes principais:
- **IoT Devices**: O ESP32 atua como controlador principal, conectado ao sensor de temperatura e umidade DHT22. Ele se conecta à rede Wi-Fi e publica os dados no broker MQTT.
- **Backend**: O servidor MQTT recebe os dados publicados pelo ESP32 e pode encaminhá-los para uma aplicação web ou sistemas de monitoramento em tempo real.
- **Frontend**: Uma interface web ou sistema de visualização recebe e exibe os dados em gráficos ou dashboards. Pode ser integrado a ferramentas de análise pós-corrida.

### Diagrama de Arquitetura
```
[Sensor DHT22] --> [ESP32] --(Wi-Fi)--> [Broker MQTT] --> [Dashboard/Frontend]
```

## Recursos Necessários

### IoT (Dispositivos)
- **ESP32**: Microcontrolador com Wi-Fi integrado para coleta e envio de dados.
- **DHT22**: Sensor responsável pela medição de temperatura e umidade.
- **Bibliotecas**:
  - `WiFi.h`: Conexão à rede Wi-Fi.
  - `PubSubClient.h`: Implementação do protocolo MQTT.
  - `DHT.h`: Interação com o sensor DHT22.

### Backend (Servidor)
- **Broker MQTT**: Servidor para recebimento e roteamento dos dados. Pode ser implementado com soluções como Mosquitto MQTT.
- **Servidor Web (Opcional)**: Para armazenar os dados em um banco de dados ou fazer análises mais detalhadas.

### Frontend (Interface de Visualização)
- **Interface Web**: Sistema de visualização para exibir as leituras de temperatura e umidade em gráficos. Pode ser integrado com bibliotecas como Chart.js ou D3.js.

## Instruções de Uso

1. **Configurar o Ambiente IoT**:
   - Conecte o ESP32 ao sensor DHT22 conforme o diagrama de pinos.
   - Configure as credenciais da rede Wi-Fi e do broker MQTT no código.

2. **Carregar o Código no ESP32**:
   - Utilize o Arduino IDE para programar o ESP32. Certifique-se de que as bibliotecas `WiFi.h`, `PubSubClient.h` e `DHT.h` estejam instaladas.

3. **Monitorar a Conexão Wi-Fi**:
   - A função `setup_wifi()` garante que o ESP32 se conecte ao Wi-Fi. Caso a conexão falhe, o dispositivo tenta reconectar automaticamente.

4. **Publicar Dados no MQTT**:
   - A função `handleTemperatureAndHumidity()` lê os dados do sensor e publica no broker MQTT a cada 2 segundos.

5. **Configurar o Broker MQTT**:
   - Instale o Mosquitto MQTT ou use um broker público (ex: HiveMQ) para receber os dados do ESP32.
   - Configure o servidor para receber dados do ESP32 em um tópico específico.

## Requisitos e Dependências

- **Hardware**:
  - ESP32
  - Sensor DHT22
  - Conexão Wi-Fi

- **Software**:
  - Arduino IDE
  - Mosquitto MQTT ou qualquer outro broker MQTT
  - Bibliotecas: `WiFi.h`, `PubSubClient.h`, `DHT.h`

## Possíveis Aplicações na Fórmula E

1. **Monitoramento Ambiental em Boxes**:
   O projeto pode ser utilizado para monitorar a temperatura e umidade em áreas críticas, como nos boxes, ajudando as equipes a otimizar o gerenciamento térmico e a segurança dos equipamentos.

2. **Coleta de Dados para Análises Pós-Corrida**:
   Os dados podem ser armazenados e analisados posteriormente para entender o impacto das condições ambientais no desempenho do carro elétrico e da bateria.

3. **Melhoria na Performance de Pit Stops**:
   Monitorar as condições ambientais durante os pit stops pode ajudar na previsão do melhor momento para realizar manutenções ou trocas de pneus, aumentando a eficiência.

## Considerações Finais

Este projeto oferece uma solução simples e eficiente para monitorar variáveis ambientais em tempo real, com potencial aplicação em diversos setores, incluindo o automobilismo de alta performance como a Fórmula E. A integração com sistemas IoT e protocolos como MQTT garante escalabilidade e automação para diferentes tipos de uso.
