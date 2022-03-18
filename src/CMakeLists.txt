set(COMPONENT_SRCS
   config.c
   node_main.cpp
   memfault_platform_device_info.c
   util/constrain.cpp
   pressure/pressure.cpp
   imu/imu.cpp
   ota_update/ota_update.cpp
   actuator/actuator.cpp
   actuators/actuators.cpp
   board/board.cpp
   config/config.cpp
   can/can.cpp
   mqtt/mqtt.cpp
   bellow/bellow.cpp
)

set(COMPONENT_ADD_INCLUDEDIRS .)

set(COMPONENT_REQUIRES esp_https_ota app_update)

register_component()
