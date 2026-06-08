#include <WiFi.h>
#include <MQTT.h>

const char ssid[] = "Tes";
const char pass[] = "12345678";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("dari_elsa", "kelompok4mikrokontroller", "84wmjt1a5zRurEuh")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);
}

void setup() {
  Serial.begin(115200);

  // start wifi and mqtt
  WiFi.begin(ssid, pass);
  client.begin("kelompok4mikrokontroller.cloud.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("/hello", "world");
  }
}