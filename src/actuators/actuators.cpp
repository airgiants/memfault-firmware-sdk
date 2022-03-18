
#include "actuator/actuator.h"
#include "config/config.h"
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

    inflate.set_servo(PIN_SERVO0);
    deflate.set_servo(PIN_SERVO1);

    

}

void Actuators::update(){
    const int period = 50;
    static unsigned long prev = 0;
    unsigned long const now = millis();
    if(now - prev > period) {

        inflate.update();
        deflate.update();
        
        prev = now;
    }


}
// void setupServo() {
// 	// Allow allocation of all timers
// 	ESP32PWM::allocateTimer(0);
// 	ESP32PWM::allocateTimer(1);
// 	ESP32PWM::allocateTimer(2);
// 	ESP32PWM::allocateTimer(3);

// 	//set output puffer to output

    
// 	inflateServo.setPeriodHertz(50);    // standard 50 hz servo
// 	deflateServo.setPeriodHertz(50);    // standard 50 hz servo
// 	inflateServo.attach(PIN_SERVO2, 1100, 2000); // attaches the servo on pin 18 to the servo object
// 	deflateServo.attach(PIN_SERVO1, 1100, 2000); // attaches the servo on pin 18 to the servo object
// 	// using default min/max of 1000us and 2000us
// 	// different servos may require different min/max settings
// 	// for an accurate 0 to 180 sweep
//     inflateServo.write(180.0);
//     deflateServo.write(0.0);
// }