# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME node-app)
set(CMAKE_PROJECT_NAME ${PROJECT_NAME})
set(MEMFAULT_PLATFORM_PORT_COMPONENTS src)
# set(MEMFAULT_ESP_HTTP_CLIENT_ENABLE 0)

get_filename_component(memfault_firmare_sdk_dir src/memfault/memfault-firmware-sdk ABSOLUTE)
include(${memfault_firmare_sdk_dir}/ports/esp_idf/memfault.cmake)

# NOTE: This include also applies global compiler options, make sure
# this happens first before defining other targets!
# The esp-idf project() macro creates a project_name.elf target:
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(${PROJECT_NAME})
