#ifndef actuator_h
#define actuator_h
#include <ESP32Servo.h>





class Actuator
{
  public:
    Actuator();
    Actuator(int pin );
    Actuator(int pin, int min_val, int max_val);
    void set_servo(int pin);
    int get();
    bool update();
    void set(int val);
    void setScaled(float val);

    int max(int max_val);
    int min(int min_val);
    int max();
    int min();
    
  private:
    int _pos;
    int _min, _max;
    int _pin;
};
#endif
