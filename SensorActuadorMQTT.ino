#include "WiFiConnection.h"
#include "MQTTHandler.h"
#include "MotorController.h"
#include "TemperatureSensor.h"

// Instantiate objects
WiFiConnection wifiConnection("PRULAND", "Huminta24");
MQTTHandler mqttHandler("broker.hivemq.com", 1883, "ucb/cba/Iot/grupo14/sensor", "ucb/cba/Iot/grupo14/actuador", 4);
MotorController motorController(4, 2, 0, 15);
TemperatureSensor temperatureSensor(35);

unsigned long previousMillisTemp = 0;
const long intervalTemp = 5000;  // Send temperature every 5 seconds

void setup() {
  Serial.begin(115200);
  motorController.setup();
  wifiConnection.connect();
  mqttHandler.setup(mqttCallback);
}

void loop() {
  mqttHandler.loop();
  
  unsigned long currentMillisTemp = millis();
  if (currentMillisTemp - previousMillisTemp >= intervalTemp) {
    previousMillisTemp = currentMillisTemp;
    float temperatureC = temperatureSensor.read();
    mqttHandler.sendTemperature(temperatureC);
  }
}

void mqttCallback(char* topic, byte* message, unsigned int length) {
  mqttHandler.handleMessage(topic, message, length);
}
