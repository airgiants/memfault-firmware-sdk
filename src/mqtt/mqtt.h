#ifndef mqtt_h
#define mqtt_h

#include <AsyncMqttClient.h>

//const char* broker = "mqtt.airgiants.co.uk";
#define MQTT_HOST "mqtt.airgiants.co.uk"
#define MQTT_PORT 44920


void connectToMqtt();


void setup_mqtt();

#endif