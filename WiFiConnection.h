#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H

#include <WiFi.h>

class WiFiConnection {
public:
    WiFiConnection(const char* ssid, const char* password) 
        : ssid(ssid), password(password), previousMillisReconnect(0) {}

    void connect() {
        Serial.print("Conectando a WiFi ");
        Serial.println(ssid);
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillisReconnect >= reconnectInterval) {
                previousMillisReconnect = currentMillis;
                Serial.print(".");
            }
        }
        Serial.println("\nConectado a WiFi");
    }

    bool isConnected() {
        return WiFi.status() == WL_CONNECTED;
    }

private:
    const char* ssid;
    const char* password;
    unsigned long previousMillisReconnect;
    const long reconnectInterval = 500;
};

#endif // WIFICONNECTION_H
