#ifndef can_h
#define can_h



#include <ArduinoUAVCAN.h>
#define MIN(a,b) (((a)<(b))?(a):(b))

static const uint32_t DESIRED_BIT_RATE = 1000UL * 1000UL ; // 1 Mb/s
static uint32_t constexpr CAN_EFF_BITMASK   = 0x80000000;

bool transmitCanFrame(CanardFrame const & frame);
void can_setup();
void heartbeat_loop();


#endif