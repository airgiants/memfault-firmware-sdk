#include "actuator.h"
#include "config/config.h"
#include "util/constrain.h"
#include <ESP32Servo.h>


Servo serv;

Actuator::Actuator(){
	_pin = 0;
	_min = 0;
	_max = 180;
}
Actuator::Actuator(int pin){
	_pin = pin;
	_min = 0;
	_max = 180;
}

Actuator::Actuator(int pin, int min_val, int max_val){
	_min = min_val;
	_max = max_val;
	_pin = pin;
}
    
void Actuator::set_servo(int pin){
	_pin = pin;
	serv.setPeriodHertz(50);
	serv.attach(pin);
}

int Actuator::min(int min_val){
	_min = min_val;
return _min;
}

int  Actuator::max(int max_val){
	_max = max_val;
	return _max;
}

int Actuator::min(){
	return _min; 

}

int Actuator::max(){
	return _max; 
}

void Actuator::set(int val){

	_pos = constrain(val, _min, _max);
}
int Actuator::get(){
	return _pos;
}
void Actuator::setScaled(float val){
	_pos = fmapConstrained(val,0.0,1.0,_min, _max);
}

bool Actuator::update(){
	serv.write(_pos);
	return true;
}


// void Actuator::begin(){

    
// }

