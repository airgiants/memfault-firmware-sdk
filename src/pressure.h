#ifndef pressure_h
#define pressure_h




class Pressure
{
  public:
    Pressure();
    void begin();
    bool update();
    float get_temperature();
    float get_pressure();
    bool is_connected();

  private:
    float press;
    float temp;

   
};
#endif