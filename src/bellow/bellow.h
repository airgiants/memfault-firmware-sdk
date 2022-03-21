#ifndef bellow_h
#define bellow_h
#include "actuators/actuators.h"

class Bellow
{
  public:
    Bellow();
    void begin();
    void set_drive(float drive);
    float get_drive();
    void fill();
    void empty();
    void set_pressure(float target);
    float get_pressure();
    void update(int period);


    
  private:
    float _drive;
    float _atmospheric_pressure, _max_pressure, _target_pressure;
    float _pressure, _pressure_error, _absoute_error;
    int _update_period;
};
#endif