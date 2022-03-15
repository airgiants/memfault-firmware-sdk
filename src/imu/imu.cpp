#include "imu.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);


Imu::Imu(){
    connected = false;
}
bool Imu::begin(){
    connected = bno.begin();
    bno.setExtCrystalUse(true);
    return connected;
}


float Imu::get_angle(){



  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  /* Display the floating point data */
//   Serial.print("X: ");
//   Serial.print(euler.x());
//   Serial.print(" Y: ");
//  Serial.print(euler.y());
//  Serial.print(" Z: ");
//  Serial.print(euler.z());
//  Serial.print("\t\t");
    return euler.x();

  /*
  // Quaternion data
  imu::Quaternion quat = bno.getQuat();
  Serial.print("qW: ");
  Serial.print(quat.w(), 4);
  Serial.print(" qX: ");
  Serial.print(quat.x(), 4);
  Serial.print(" qY: ");
  Serial.print(quat.y(), 4);
  Serial.print(" qZ: ");
  Serial.print(quat.z(), 4);
  Serial.print("\t\t");
  */

  /* Display calibration status for each sensor. */
//   uint8_t system, gyro, accel, mag = 0;
//   bno.getCalibration(&system, &gyro, &accel, &mag);
//   Serial.print("CALIBRATION: Sys=");
//   Serial.print(system, DEC);
//   Serial.print(" Gyro=");
//   Serial.print(gyro, DEC);
//   Serial.print(" Accel=");
//   Serial.print(accel, DEC);
//   Serial.print(" Mag=");
//   Serial.println(mag, DEC);



// int8_t temp = bno.getTemp();
//   Serial.print("Current Temperature: ");
//   Serial.print(temp);
//   Serial.println(" C");
//   Serial.println("");

 

}
bool Imu::is_connected(){
    return connected;
}
