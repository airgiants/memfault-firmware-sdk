#ifndef config_h
#define config_h



//User led's 

#define LED_HEART 18
#define LED_S1 19


//I2C bus pins

#define I2C_SDA 21
#define I2C_SCL 22

//Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);
// Both jumpers closed


// USE if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {


//POWER

#define PWR_EN 25
#define PWR_EN_DIR HIGH
#define PWR_STATUS 23


//TX/RX on SERVO 0 
#define PIN_DXL_TX 16
#define PIN_DXL_RX 17
//Direction switch for DYNAMIXEL 
#define PIN_DXL_DIR 33
#define PIN_DXL_OUTPUT HIGH


//SERVO PINS
#define PIN_SERVO0 16
#define PIN_SERVO1 26
#define PIN_SERVO2 27
#define PIN_SERVO3 32


//ANALOG SENSING INPut
#define PIN_SENSE_VOUT 2
#define PIN_SENSE_VIN 15


#endif


