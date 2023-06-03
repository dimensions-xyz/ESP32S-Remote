#include <WiFi.h>

const char* ssid = "¯_(ツ)_/¯";
const char* password = "¯_(ツ)_/¯";
const int ledPin = 2;  // GPIO

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  connectToWiFi();
}

void loop() {
  checkWifi();

  delay(1000);
}

void connectToWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print("Connecting to WİFİ network...\n");
      delay(1000);
    }
    digitalWrite(ledPin, HIGH);
    Serial.println("Connected to WiFi successfully!");
  }
}

void checkWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledPin, LOW);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi disconnected! Reconnecting...");
      delay(1000);
    }
    digitalWrite(ledPin, HIGH);
    Serial.println("Reconnected to WiFi!");
  }
}