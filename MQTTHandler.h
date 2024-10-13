#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <PubSubClient.h>

class MQTTHandler {
public:
    MQTTHandler(const char* server, int port, const char* sensorTopic, const char* actuadorTopic, int pwmPin)
        : sensorTopic(sensorTopic), actuadorTopic(actuadorTopic), pwmPin(pwmPin), mqttClient(wifiClient) {
        mqttClient.setServer(server, port);
    }

    void setup(void (*callback)(char*, byte*, unsigned int)) {
        mqttClient.setCallback(callback);
        connect();
    }

    void loop() {
        if (!mqttClient.connected()) {
            connect();
        } else {
            mqttClient.loop();
        }
    }

    void sendTemperature(float temperatureC) {
        String tempString = String(temperatureC);
        mqttClient.publish(sensorTopic, tempString.c_str());
        Serial.print("Temperature sent: ");
        Serial.println(tempString + " °C");
    }

    void handleMessage(char* topic, byte* message, unsigned int length) {
        String messageString;
        for (int i = 0; i < length; i++) {
            messageString += (char)message[i];
        }

        Serial.print("Message received on topic [");
        Serial.print(topic);
        Serial.print("]: ");
        Serial.println(messageString);

        if (String(topic) == actuadorTopic) {
            int sliderValue = messageString.toInt();
            int pwmValue = (sliderValue == 0) ? 0 : map(sliderValue, 10, 100, 60, 255);
            analogWrite(pwmPin, pwmValue); // Use the stored pwmPin here
            Serial.print("Motor speed set to: ");
            Serial.println(pwmValue);
        }
    }

private:
    void connect() {
        if (!mqttClient.connected()) {
            Serial.print("Connecting to MQTT broker...");
            String clientId = "ESP32Client_" + String(millis());
            if (mqttClient.connect(clientId.c_str())) {
                Serial.println("Connected");
                mqttClient.subscribe(actuadorTopic);
            } else {
                Serial.print("Failed, rc=");
                Serial.print(mqttClient.state());
                Serial.println(" Trying again in 5 seconds");
            }
        }
    }

    const char* sensorTopic;
    const char* actuadorTopic;
    int pwmPin; // Store pwmPin here
    WiFiClient wifiClient;
    PubSubClient mqttClient;
};

#endif // MQTT_HANDLER_H
