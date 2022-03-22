#include "Arduino.h"
#include <Adafruit_INA219.h>
#include "board.h"




Board::Board(){

//LEDS
_init = false;
    pinMode(LED_HEART, OUTPUT);
    pinMode(LED_S1,OUTPUT);
    pinMode(PWR_STATUS,INPUT);
    pinMode(PIN_SENSE_VIN,INPUT);

    _heartbeat_frequency = 500;
    _last_heartbeat = millis();
    _id = 55;
    _pwr_good = false;
    _out_voltage = 0;
    _out_power = 0;
    _out_current = 0;
    disable_power();
    
}


void Board::update(){
  if(!_init){
    current_sensor.begin();
    _init = true;
  }
  if (millis() - _last_heartbeat >= _heartbeat_frequency) {
    _last_heartbeat += _heartbeat_frequency;
    digitalWrite(LED_HEART, !digitalRead(LED_HEART));
  }
  _pwr_good = digitalRead(PWR_STATUS);
  digitalWrite(LED_S1, _pwr_good);
  _out_voltage = current_sensor.getBusVoltage_V();
  _out_current = current_sensor.getCurrent_mA()/1000;
  _out_power = current_sensor.getPower_mW()/1000;

  _input_voltage = _adc_to_V(analogRead(PIN_SENSE_VIN));


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

float Board::output_voltage(){
  return _out_voltage;
}

float Board::output_current(){
  return _out_current;
}

float Board::output_power(){
  return _out_power;
}

float Board::input_voltage(){
  return _input_voltage;
}

float Board::_adc_to_V(int raw){
  return raw/10.0;
}