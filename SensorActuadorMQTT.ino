#include "WiFiConnection.h"
#include "MQTTHandler.h"
#include "MotorController.h"
#include "TemperatureSensor.h"

// Instanciar las clases con los parámetros necesarios
WiFiConnection wifi("PRULAND", "Huminta24");
MQTTHandler mqtt("broker.hivemq.com", 1883, "ucb/cba/Iot/grupo14/actuador");
MotorController motor(4, 2, 0, 15);
TemperatureSensor tempSensor(35);

// Variables para controlar el intervalo de envío de temperatura
unsigned long previousMillisTemp = 0;
const long intervalTemp = 5000;

void setup() {
    Serial.begin(115200);
    wifi.connect();
    mqtt.setCallback(mqttCallback);
    mqtt.connect();
}

void loop() {
    // Verificar y reconectar si es necesario
    if (!mqtt.isConnected()) {
        mqtt.connect();
    } else {
        mqtt.loop();
    }

    // Enviar la temperatura cada cierto intervalo
    unsigned long currentMillisTemp = millis();
    if (currentMillisTemp - previousMillisTemp >= intervalTemp) {
        previousMillisTemp = currentMillisTemp;
        float temperature = tempSensor.readTemperature();
        sendTemperature(temperature);
    }
}

void sendTemperature(float temperature) {
    String tempString = String(temperature);
    mqtt.publish("ucb/cba/Iot/grupo14/sensor", tempString.c_str());
    Serial.print("Temperatura enviada: ");
    Serial.println(tempString + " °C");
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    int sliderValue = message.toInt();
    int pwmValue = (sliderValue == 0) ? 0 : map(sliderValue, 10, 100, 60, 255);
    motor.setSpeed(pwmValue);
    Serial.print("Velocidad del motor ajustada a: ");
    Serial.println(pwmValue);
}
