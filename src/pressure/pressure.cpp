#include "pressure.h"
#include <icp101xx.h>

ICP101xx pressure_sensor;



Pressure::Pressure(){
    temp = 99;
    press = 300000;
}
    
void Pressure::begin(){
    pressure_sensor.begin();
    pressure_sensor.measure(pressure_sensor.VERY_ACCURATE);
    temp = pressure_sensor.getTemperatureC();
    press = pressure_sensor.getPressurePa();
}

bool Pressure::update(){
    if (pressure_sensor.dataReady()) {
        temp = pressure_sensor.getTemperatureC();
        press = pressure_sensor.getPressurePa();
        pressure_sensor.measureStart(pressure_sensor.VERY_ACCURATE);
    }
    return 0;//is_connected();
} 

bool Pressure::is_connected(){
    return  pressure_sensor.isConnected();
}
float Pressure::get_pressure(){
    return press;
}
float Pressure::get_temperature(){
    return temp;
}