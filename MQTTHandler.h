#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <PubSubClient.h>

class MQTTHandler {
public:
    MQTTHandler(const char* server, int port, const char* topic) 
        : mqttServer(server), mqttPort(port), actuadorTopic(topic), mqttClient(wifiClient) {
        mqttClient.setServer(mqttServer, mqttPort);
    }

    void connect() {
        if (!mqttClient.connected()) {
            Serial.print("Conectando al broker MQTT...");
            String clientId = "ESP32Client_" + String(millis());
            if (mqttClient.connect(clientId.c_str())) {
                Serial.println("Conectado");
                mqttClient.subscribe(actuadorTopic);
            } else {
                Serial.print("Falló, rc=");
                Serial.print(mqttClient.state());
                Serial.println(" Intentando de nuevo en 5 segundos");
            }
        }
    }

    void loop() {
        mqttClient.loop();
    }

    bool isConnected() {
        return mqttClient.connected();
    }

    void setCallback(MQTT_CALLBACK_SIGNATURE) {
        mqttClient.setCallback(callback);
    }

    void publish(const char* topic, const char* payload) {
        mqttClient.publish(topic, payload);
    }

private:
    const char* mqttServer;
    int mqttPort;
    const char* actuadorTopic;
    WiFiClient wifiClient;
    PubSubClient mqttClient;
};

#endif // MQTTHANDLER_H
