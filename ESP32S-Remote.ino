#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "¯_(ツ)_/¯";
const char* password = "¯_(ツ)_/¯";
const int ledPin = 2;  // GPIO

bool led1Status = LOW;

WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  connectToWiFi();
  setupServer();
}

void loop() {
  checkWifi();
  server.handleClient();
  changeLedStatus();

  delay(1000);
}

void changeLedStatus() {
  if (led1Status) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void connectToWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connecting to WİFİ network...");
      delay(1000);
    }
    Serial.println("Connected to WiFi successfully!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    blinkLed1();
  }
}

void checkWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi disconnected! Reconnecting...");
      delay(1000);
    }
    Serial.println("Reconnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    blinkLed1();
  }
}

void blinkLed1(){
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
}

void setupServer() {
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.onNotFound(handle_NotFound);

  server.begin();
}

void handle_OnConnect() {
  led1Status = LOW;
  server.send(200, "text/html", sendHTML(led1Status));
}

void handle_led1on() {
  led1Status = HIGH;
  Serial.println("Led Status: ON");
  server.send(200, "text/html", sendHTML(true));
}

void handle_led1off() {
  led1Status = LOW;
  Serial.println("Led Status: OFF");
  server.send(200, "text/html", sendHTML(false));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Error 404 Not Found.");
}

String sendHTML(bool led1Status) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>NodeMCU-32S</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c ;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #0095c7;}\n";
  ptr += ".button-on:active {background-color: #16a085;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body bgcolor= BlanchedAlmond style=color:white>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>NodeMCU-32S Home Controller</h1>\n";

  if (led1Status) {
    ptr += "<p>LED1 STATUS: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
    ptr += "<br/><br/><img src= 'https://i.kym-cdn.com/photos/images/original/001/917/246/304.png' Z\" width=\"800\" height=\"600\" alt=\"logo\\\">\n";
  } else {
    ptr += "<p>LED1 STATUS: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
    ptr += "<br/><br/><img src= 'https://i.kym-cdn.com/entries/icons/mobile/000/018/433/wojak.jpg' Z\" width=\"800\" height=\"600\" alt=\"logo\\\">\n";
  }

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
