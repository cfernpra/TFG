#include "gps.h"

// Configuración del GPS
#define RXPin 16
#define TXPin 17
SoftwareSerial mySerial(RXPin, TXPin);
Adafruit_GPS GPS(&mySerial);

// Variables globales para ubicación
float latitude = 0.0;
float longitude = 0.0;

void setupGPS() {
  mySerial.begin(9600);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
}

void updateGPS() {
  GPS.read();
  if (GPS.newNMEAreceived()) {
    GPS.parse(GPS.lastNMEA());
    latitude = GPS.latitudeDegrees;
    longitude = GPS.longitudeDegrees;
  }
}

float getLatitude() {
  return latitude;
}

float getLongitude() {
  return longitude;
}
