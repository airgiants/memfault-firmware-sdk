#ifndef actuators_h
#define actuators_h
#include <ESP32Servo.h>
#include "actuator/actuator.h"



class Actuators{

public:
	Actuators();
	void begin();
	void update();
	Actuator inflate;
	Actuator deflate;

private:



};


#endif
