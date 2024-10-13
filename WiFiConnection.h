#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <WiFi.h>

class WiFiConnection {
public:
    WiFiConnection(const char* ssid, const char* password)
        : ssid(ssid), password(password) {}

    void connect() {
        Serial.print("Connecting to WiFi ");
        Serial.println(ssid);
        
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nConnected to WiFi");
    }

private:
    const char* ssid;
    const char* password;
};

#endif // WIFI_CONNECTION_H
