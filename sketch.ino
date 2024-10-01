#include <WiFi.h>           
#include <PubSubClient.h>   

#define TRIGGER_PIN 2
#define ECHO_PIN 15
#define LED_1 25
#define LED_2 26
#define LED_3 32
#define LED_4 33

#define MQTT_SERVER "test.mosquitto.org" 

const char* ssid = "Wokwi-GUEST";
const char* password = "";         

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
String led_status;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected to MQTT");
      client.publish("iot/sensor/status", "Device connected");
      client.subscribe("iot/sensor/control"); 
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  Serial.begin(115200);   
  setup_wifi();           

  client.setServer(MQTT_SERVER, 1883); 
}

void loop() {
  if (!client.connected()) {
    reconnect();  
  }
  client.loop();  

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  float duracao = pulseIn(ECHO_PIN, HIGH);
  float distancia = duracao / 58.772;
  Serial.println("Distância em cm: " + String(distancia));

  if (distancia >= 40 && distancia < 80) {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    led_status = "LED1 aceso";
  } else if (distancia >= 80 && distancia < 120) {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    led_status = "LED2 aceso";
  } else if (distancia >= 120 && distancia < 160) {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, LOW);
    led_status = "LED3 aceso";
  } else if (distancia >= 160) {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, HIGH);
    led_status = "LED4 aceso";
  } else {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    led_status = "Nenhum LED aceso";
  }

  client.publish("iot/sensor/distance", String(distancia).c_str());
  client.publish("iot/sensor/ledstatus", led_status.c_str());

  delay(1000);
}