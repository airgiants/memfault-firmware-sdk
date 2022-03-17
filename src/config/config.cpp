#include "config.h"
#include "Arduino.h"



Board::Board(){

//LEDS
    pinMode(LED_HEART, OUTPUT);
    pinMode(LED_S1,OUTPUT);
    _heartbeat_frequency = 500;
    _last_heartbeat = millis();
}


void Board::update(){
 //   if(_last_heartbeat == 0) _last_heartbeat = millis();
    if (millis() - _last_heartbeat >= _heartbeat_frequency) {
    _last_heartbeat += _heartbeat_frequency;
    digitalWrite(LED_HEART, !digitalRead(LED_HEART));
  }

}
void Board::set_hb_freq(int freq){
    _heartbeat_frequency = freq;
}