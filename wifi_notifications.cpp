#include "wifi_notifications.h"
#include <WiFi.h>
#include <HTTPClient.h>

// Configurar Wi-Fi
void setupWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");
}

// Enviar alerta
void sendAlert(float lat, float lon) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://tu-servidor.com/api/alerta");
    http.addHeader("Content-Type", "application/json");
    String payload = "{\"latitude\":" + String(lat, 6) + ",\"longitude\":" + String(lon, 6) + "}";
    int httpResponseCode = http.POST(payload);
    Serial.println("Alerta enviada. Código: " + String(httpResponseCode));
    http.end();
  }
}
