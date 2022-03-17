set(COMPONENT_SRCS
   cmd_system.c
   cmd_wifi.c
   config.c
   node_main.cpp
   memfault_platform_device_info.c
   pressure/pressure.cpp
   imu/imu.cpp
   ota_update/ota_update.cpp
   actuators/actuators.cpp
)

set(COMPONENT_ADD_INCLUDEDIRS .)

set(COMPONENT_REQUIRES esp_https_ota app_update)

register_component()
