#ifndef actuator_h
#define actuator_h
#include <ESP32Servo.h>





class Actuator
{
  public:
    Actuator( );
    Actuator(int pin );
    Actuator(int pin, int min_val, int max_val);
    void set_pin(int pin);
    int get();
    bool update();
    void set(int val);
    void setScaled(float val);

    void max(int max_val);
    void min(int min_val);
    
  private:
    int _pos;
    int _min, _max;
    int _pin;
};
#endif
