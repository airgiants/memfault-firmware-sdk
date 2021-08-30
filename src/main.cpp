#include <Arduino.h>

#include "memfault/components.h"

void setup() {
  // put your setup code here, to run once:
  memfault_platform_boot();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void app_main() {
  memfault_platform_boot();
}
