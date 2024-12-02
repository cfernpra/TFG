#include "gps.h"
#include "geofence.h"
#include "firebase.h"
#include "config.h"


void setup() {
  Serial.begin(115200);

  // Conectar al Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a Wi-Fi...");
  }
  Serial.println("Conexión Wi-Fi establecida");

  // Inicializar módulos
  setupGPS();       // GPS
  setupFirebase();  // Firestore
}

void loop() {
  // Actualizar coordenadas GPS
  updateGPS();
  float lat = getLatitude();
  float lon = getLongitude();

  // Verificar si el usuario está fuera de la zona segura
  if (isOutsideSafeZone(lat, lon)) {
    Serial.println("¡Fuera de la zona segura!");

    // Crear timestamp
    String timestamp = String(millis() / 1000);

    // Enviar ubicación con referencia al usuario
    sendLocationWithReference("/users/usuario1", lat, lon, timestamp);

    // Enviar alerta con referencia a la ubicación y al usuario
    sendAlertWithReference("/users/usuario1", "/locations/location1", "Out of safe zone", timestamp);
  } else {
    Serial.println("Dentro de la zona segura.");
  }

  // Guardar datos si no está en casa
  if (!isAtHome(lat, lon)) {
    String timestamp = String(millis() / 1000);
    storeLocation(lat, lon, timestamp);  // Almacena datos localmente
    Serial.println("Ubicación almacenada.");
  } else {
    // Si está en casa, conectar a Wi-Fi y enviar datos acumulados
    if (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a Wi-Fi...");
      }
      Serial.println("Conectado a Wi-Fi");
    }

    // Enviar datos acumulados al regresar a casa
    enviarDatosAlRegresar();
  }

  // Leer datos de una ubicación específica con referencias
  getLocationWithReference("location1");

  delay(30000); // Esperar 30 segundos antes de la próxima actualización
}

