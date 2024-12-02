#include "storage.h"
#include <vector>

// Vector para almacenar ubicaciones en memoria
std::vector<FirebaseJson> storedLocations;

// Almacena una ubicación en memoria
void storeLocation(float lat, float lon, String timestamp) {
  FirebaseJson location;
  location.set("latitud", lat);
  location.set("longitud", lon);
  location.set("timestamp", timestamp);
  storedLocations.push_back(location);
}

// Obtiene todas las ubicaciones almacenadas
std::vector<FirebaseJson> getStoredLocations() {
  return storedLocations;
}

// Limpia las ubicaciones almacenadas
void clearStoredLocations() {
  storedLocations.clear();
}
