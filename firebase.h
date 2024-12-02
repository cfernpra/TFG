#ifndef FIREBASE_H
#define FIREBASE_H

#include <FirebaseESP32.h>

// Funciones para inicializar y gestionar Firestore
void setupFirebase();
void enviarUbicacion(String usuarioID, float lat, float lon);
void obtenerUbicacion(String usuarioID);

// Nuevas funciones para manejar referencias
void sendLocationWithReference(String userPath, float lat, float lon, String timestamp);
void sendAlertWithReference(String userPath, String locationPath, String message, String timestamp);
void getLocationWithReference(String locationID);

#endif
