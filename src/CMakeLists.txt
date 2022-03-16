set(COMPONENT_SRCS
   cmd_system.c
   cmd_wifi.c
   config.c
   console_example_main.cpp
   memfault_platform_device_info.c
   pressure/pressure.cpp
   imu/imu.cpp
)

set(COMPONENT_ADD_INCLUDEDIRS .)

set(COMPONENT_REQUIRES esp_https_ota app_update)

register_component()
