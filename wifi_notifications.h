
#ifndef WIFI_NOTIFICATIONS_H
#define WIFI_NOTIFICATIONS_H

void setupWiFi(const char* ssid, const char* password);
void sendAlert(float lat, float lon);

#endif
