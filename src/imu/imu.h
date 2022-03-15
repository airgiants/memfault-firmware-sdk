#ifndef imu_h
#define imu_h


class Imu
{
    public:
        Imu();
        bool begin();
        float get_angle();
        bool is_connected();
    private:
        bool connected; 


};

#endif
