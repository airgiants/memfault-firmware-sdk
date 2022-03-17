
#include "can.h"
#include <ArduinoUAVCAN.h>
#include <ACAN_ESP32.h>


using namespace uavcan::node;
ArduinoUAVCAN uc(12, transmitCanFrame);


Heartbeat_1_0<> hb;

CANMessage can_frame;
bool transmitCanFrame(CanardFrame const & frame)
{

    uint8_t myBuffer[8];
    memcpy(myBuffer, reinterpret_cast<uint8_t const *>(frame.payload), MIN(static_cast<uint8_t const>(frame.payload_size), 8)); 

     for (uint8_t i=0 ; i<8 ; i++) {
        can_frame.data[i] = myBuffer[i];
     }
  
    can_frame.len = static_cast<uint8_t const>(frame.payload_size);
    can_frame.rtr = false; //dataframe
    can_frame.ext = true;
    can_frame.id = CAN_EFF_BITMASK | frame.extended_can_id;
                     
  return ACAN_ESP32::can.tryToSend(can_frame);
}



void can_setup(){






  /* Attach interrupt handler to register MCP2515 signaled by taking INT low */
  //pinMode(MKRCAN_MCP2515_INT_PIN, INPUT_PULLUP);
 // attachInterrupt(digitalPinToInterrupt(MKRCAN_MCP2515_INT_PIN), onExternalEvent, FALLING);

  Serial.println ("Configure ESP32 CAN") ;
  ACAN_ESP32_Settings settings (DESIRED_BIT_RATE) ;
  settings.mRequestedCANMode = ACAN_ESP32_Settings::NormalMode ;  // Select loopback mode
 const uint32_t errorCode = ACAN_ESP32::can.begin (settings) ;
  if (errorCode == 0) {
    Serial.print ("Bit Rate prescaler: ") ;
    Serial.println (settings.mBitRatePrescaler) ;
    Serial.print ("Time Segment 1:     ") ;
    Serial.println (settings.mTimeSegment1) ;
    Serial.print ("Time Segment 2:     ") ;
    Serial.println (settings.mTimeSegment2) ;
    Serial.print ("RJW:                ") ;
    Serial.println (settings.mRJW) ;
    Serial.print ("Triple Sampling:    ") ;
    Serial.println (settings.mTripleSampling ? "yes" : "no") ;
    Serial.print ("Actual bit rate:    ") ;
    Serial.print (settings.actualBitRate ()) ;
    Serial.println (" bit/s") ;
    Serial.print ("Exact bit rate ?    ") ;
    Serial.println (settings.exactBitRate () ? "yes" : "no") ;
    Serial.print ("Sample point:       ") ;
    Serial.print (settings.samplePointFromBitStart ()) ;
    Serial.println ("%") ;
    Serial.println ("Configuration OK!");
  }else {
    Serial.print ("Configuration error 0x") ;
    Serial.println (errorCode, HEX) ;
  }



  /* Configure initial heartbeat */
  hb.data.uptime = 0;
  hb = Heartbeat_1_0<>::Health::NOMINAL;
  hb = Heartbeat_1_0<>::Mode::INITIALIZATION;
  hb.data.vendor_specific_status_code = 0;

}


void heartbeat_loop(){

      /* Update the heartbeat object */
  hb.data.uptime = millis() / 1000;
  hb = Heartbeat_1_0<>::Mode::OPERATIONAL;

  /* Publish the heartbeat once/second */
  static unsigned long prev = 0;
  unsigned long const now = millis();
  if(now - prev > 1000) {
    uc.publish(hb);
    prev = now;
  }

  /* Transmit all enqeued CAN frames */
  while(uc.transmitCanFrame()) { }



}