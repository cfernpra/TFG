#include "gps.h"
#include "geofence.h"
#include "firebase.h"
#include "config.h"
#include "esp_sleep.h"

void setup() {
  Serial.begin(115200);

  // Conectar al Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Wi-Fi connected.");

  // Inicializar módulos
  setupGPS();       // GPS initialization
  setupFirebase();  // Firestore initialization
}

void loop() {
  // Actualizar coordenadas GPS
  updateGPS();
  float lat = getLatitude();
  float lon = getLongitude();

  // Verificar si el usuario está fuera de la zona segura
  if (isOutsideSafeZone(lat, lon)) {
    Serial.println("Out of the safe zone!");

    // Crear timestamp
    String timestamp = String(millis() / 1000);

    // Enviar ubicación con referencia al usuario
    sendLocationWithReference("/users/usuario1", lat, lon, timestamp);

    // Enviar alerta con referencia a la ubicación y al usuario
    sendAlertWithReference("/users/usuario1", "/locations/location1", "Out of safe zone", timestamp);
  } else {
    Serial.println("Inside the safe zone.");
  }

  // Guardar datos si no está en casa
  if (!isAtHome(lat, lon)) {
    String timestamp = String(millis() / 1000);
    storeLocation(lat, lon, timestamp);  // Store data locally
    Serial.println("Location stored locally.");
  } else {
    // Si está en casa, conectar a Wi-Fi y enviar datos acumulados
    reconnectWiFiIfNeeded();

    // Enviar datos acumulados al regresar a casa
    enviarDatosAlRegresar();
  }

  // Leer datos de una ubicación específica con referencias
  getLocationWithReference("location1");

  // Reducir consumo energético si es posible
  enterDeepSleep();
}

void reconnectWiFiIfNeeded() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconnecting to Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to Wi-Fi...");
    }
    Serial.println("Wi-Fi reconnected.");
  }
}

void enterDeepSleep() {
  Serial.println("Entering deep sleep mode...");
  esp_sleep_enable_timer_wakeup(60000000); // Wake up every 60 seconds
  esp_deep_sleep_start();
}
