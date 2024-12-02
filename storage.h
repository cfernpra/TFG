#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <FirebaseJson.h>

// Estructura para guardar ubicaciones
struct Location {
  float lat;
  float lon;
  String timestamp;
};

// Funciones para almacenamiento
void storeLocation(float lat, float lon, String timestamp);
std::vector<FirebaseJson> getStoredLocations();
void clearStoredLocations();

#endif
