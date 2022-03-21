
#include "actuator/actuator.h"
#include "board/board.h"
#include "actuators.h"



//see above for servo pins PIN_SERVOx

#include <ESP32Servo.h>

extern Board board;

Actuators::Actuators(){
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
    //inflate Actuator 
}

void Actuators::begin(){
	pinMode(PIN_DXL_DIR, OUTPUT); //set buffer to "out"
    digitalWrite(PIN_DXL_DIR,PIN_DXL_OUTPUT);

    board.enable_power();

    inflate.set(0);
    inflate.set_servo(PIN_SERVO0);
    deflate.set(180);
    deflate.set_servo(PIN_SERVO1);
}

void Actuators::update(){
    const int period = 125;
    static unsigned long prev = 0;
    unsigned long const now = millis();
    if(now - prev > period) {
        inflate.update();
        deflate.update();
        prev = now;
    }

}
