#include "geofence.h"
#include <math.h>

// Coordenadas de la zona segura
#define SAFE_ZONE_LAT 40.416775
#define SAFE_ZONE_LON -3.703790
#define SAFE_ZONE_RADIUS 0.005 // ~500m

// Coordenadas del área "casa"
#define HOME_LAT 40.416775 // Cambia estas coordenadas a tu ubicación
#define HOME_LON -3.703790
#define HOME_RADIUS 0.005 // ~500 metros

bool isAtHome(float lat, float lon) {
  float distance = sqrt(pow(lat - HOME_LAT, 2) + pow(lon - HOME_LON, 2));
  return distance <= HOME_RADIUS;
}


bool isOutsideSafeZone(float lat, float lon) {
  float distance = sqrt(pow(lat - SAFE_ZONE_LAT, 2) + pow(lon - SAFE_ZONE_LON, 2));
  return distance > SAFE_ZONE_RADIUS;
}
