# Sample platformio + espressif32-arduino memfault project

_NOTE: currently this example project is for reference only and does not build!_

## Changes to default project

This project was based on this example:

https://github.com/platformio/platform-espressif32/tree/develop/examples/espidf-arduino-wifiscan

The memfault tree was added with a git submodule:

```bash
❯ git submodule add https://github.com/memfault/memfault-firmware-sdk.git src/memfault/memfault-firmware-sdk
```

The `CMakeLists.txt` and `src/` files were copied over from the memfault example:

```bash
❯ cp -r src/memfault/memfault-firmware-sdk/examples/esp32/apps/memfault_demo_app/* ./
```
