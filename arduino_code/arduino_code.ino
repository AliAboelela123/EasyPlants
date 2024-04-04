#include <Arduino.h>
#include <Ethernet.h>
#include <PubSubClient.h>

byte mac[] = {}; // Ethernet MAC address
IPAddress ip(192, 168, 1, 100); // Arduino's IP address
const char* awsEndpoint = "YOUR_AWS_IOT_ENDPOINT";
const char* clientId = "YOUR_CLIENT_ID";
const char* awsTopic = "YOUR_MQTT_TOPIC";

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

void setup() {
  Serial.begin(115200);
  Ethernet.begin(mac, ip);
  delay(1000); // Allow time for Ethernet to initialize
  mqttClient.setServer(awsEndpoint, 8883); // MQTT over TLS
  mqttClient.setCallback(callback);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
  // Read sensor data
  int sensorValue = analogRead(A1);
  // Publish sensor data to MQTT topic
  mqttClient.publish(awsTopic, String(sensorValue).c_str());
  delay(5000); // Publish every 5 seconds
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(clientId)) {
      Serial.println("connected");
      mqttClient.subscribe(awsTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle MQTT message received (optional)
}
