#include "board.h"
#include "Arduino.h"



Board::Board(){

//LEDS
    pinMode(LED_HEART, OUTPUT);
    pinMode(LED_S1,OUTPUT);
    pinMode(PWR_STATUS,INPUT);

    _heartbeat_frequency = 500;
    _last_heartbeat = millis();
    _id = 55;
    _pwr_good = false;
    disable_power();
}


void Board::update(){
  if (millis() - _last_heartbeat >= _heartbeat_frequency) {
    _last_heartbeat += _heartbeat_frequency;
    digitalWrite(LED_HEART, !digitalRead(LED_HEART));
  }
  _pwr_good = digitalRead(PWR_STATUS);
  digitalWrite(LED_S1, _pwr_good);

}
void Board::set_hb_freq(int freq){
    _heartbeat_frequency = freq;
}

int Board::get_id(){
  return _id;
}

bool Board::set_id(int id){
  if(id < 128){
      _id = id;
    return true;
  }
  else return false;
}

void Board::enable_power(){
    pinMode(PWR_EN, OUTPUT); //"turn on servo Power"
    digitalWrite(PWR_EN, PWR_EN_DIR);
}

void Board::disable_power(){
    pinMode(PWR_EN, OUTPUT); //"turn on servo Power"
    digitalWrite(PWR_EN, !PWR_EN_DIR);
}

bool Board::power_good(){
  return _pwr_good;
}