#ifndef GPS_H
#define GPS_H

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// Declaración de funciones y variables
void setupGPS();
void updateGPS();
float getLatitude();
float getLongitude();

#endif
