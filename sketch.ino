#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Configurações da rede Wi-Fi (dados do primeiro código)
const char* wifi_ssid = "FIAP-IBM";
const char* wifi_password = "Challenge@24!";

// Configurações do MQTT (dados do primeiro código)
const char* mqtt_server = "18.223.238.211";
const int mqtt_port = 1883;
const char* mqtt_id = "fiware_001";
const char* mqtt_topic_publish_temp = "/TEF/lamp001/temperature";  // Tópico para publicar temperatura
const char* mqtt_topic_publish_hum = "/TEF/lamp001/humidity";      // Tópico para publicar umidade

// Configurações do DHT22
#define DHTPIN 4  // Pino de dados do DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Inicialização de Wi-Fi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Função para conectar ao Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// Função para reconectar ao MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect(mqtt_id)) {
      Serial.println("Conectado ao broker MQTT");
      // Não é necessário se inscrever em tópicos, pois não estamos recebendo comandos
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

// Função para ler temperatura e umidade e publicar no MQTT
void handleTemperatureAndHumidity() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Falha na leitura do sensor DHT!");
    return;
  }

  char tempString[8];
  dtostrf(t, 1, 2, tempString);
  char humString[8];
  dtostrf(h, 1, 2, humString);

  Serial.print("Temperatura: ");
  Serial.print(tempString);
  Serial.print(" °C, Umidade: ");
  Serial.print(humString);
  Serial.println(" %");

  client.publish(mqtt_topic_publish_temp, tempString);  // Publica temperatura
  client.publish(mqtt_topic_publish_hum, humString);    // Publica umidade
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  // Não é necessário definir um callback MQTT, pois não estamos recebendo mensagens
}

void loop() {
  // Verifica se o cliente MQTT está conectado
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Publica os dados de temperatura e umidade
  handleTemperatureAndHumidity();

  delay(2000);  // Aguarda 2 segundos entre as leituras
}
