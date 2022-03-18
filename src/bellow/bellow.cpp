
#include "actuators/actuators.h"
#include "pressure/pressure.h"
#include "util/constrain.h"

#include "config.h"
#include "Arduino.h"
#include "bellow.h"


extern Actuators actuators;
extern Pressure psensor; 

Bellow::Bellow(){

}

void Bellow::begin(){
    psensor.begin();
    actuators.begin();
    _update_period = 100; //100 ms

}


void Bellow::set_drive(float drive){

    drive = fconstrain( drive, -1.0, 1.0 );

    //driveServoAngle(inflateServo, 1.0);
    // driveServoAngle(deflateServo, 1.0);
    //return;
    
    if( drive > 0.0 ) //increase pressure
    {
        actuators.inflate.setScaled(drive);
        actuators.deflate.setScaled(0);
  
        //if( traceBellows ){Serial.print(n); Serial.print(" inflate "); Serial.print(drive);Serial.print(" deflate "); Serial.println(0);}
    }
    else // decrease pressure
    {
        actuators.inflate.setScaled(0);
        actuators.deflate.setScaled(drive);

        //if( traceBellows ){Serial.print(n); Serial.print(" inflate "); Serial.print(0);Serial.print(" deflate "); Serial.println(-drive);}
    }
}

void Bellow::fill(){
    set_drive(1.0);
}
void Bellow::empty(){
    set_drive(-1.0);
}

  




void Bellow::set_pressure(float target){


}

float Bellow::get_pressure(){
    return psensor.get_pressure();
}

void Bellow::update(int period){
    _update_period = period;

    float pressure = get_pressure() - _atmospheric_pressure;

    static unsigned long prev = 0;
    unsigned long const now = millis();
    if(now - prev > _update_period) {
        
        if (get_pressure() > _max_pressure )
        {
           _max_pressure = get_pressure();
        }

        if(get_pressure() < _atmospheric_pressure && get_pressure() > 0){
            _atmospheric_pressure = get_pressure();
        }

        _pressure_error = _target_pressure - pressure;


          _target_pressure = 0.9 * _target_pressure + 0.1 * pressure;
  
  float baseline_pressure = _max_pressure - _atmospheric_pressure;
  _absoute_error = (_target_pressure - pressure)/baseline_pressure;
        
        

        
        prev = now;
    }

}