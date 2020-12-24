# DSTIKEos

## Overview
DSTIKEos is an effort to establish a baseline framework for the DSTIKE wristband V2 onwards.

DSTIKEos provides configuration, state, display, and wifi with an events based programming approach.

The intention for this framework is to boot the watch, load configuration, connect to wifi and then loop through configured event handlers.

#### Future features
* Modular, plugin-like structure so that watch owners can download include/exclude modules that they require.
* Fallback to AP mode if all configured wifi connections fail to connect.
* Web based config interface
* Onscreen menu for various features and functions and to access menu items configured by modules.
* Include the orignal DSTIKE code for wifi deauther features (as a module).

## Build

Platform.io is configured and can be run e.g.
```shell
$ pio run -t upload && pio device monitor -p /dev/ttyUSB0 -f esp8266_exception_decoder
```

You'll notice that `Configuration.h` contains a wifi connection array this can be defined in the `PLATFORMIO_BUILD_FLAGS` environment variable e.g.
```shell
$ PLATFORMIO_BUILD_FLAGS="'-DWIFI_SSID=\"my-ssid\"' '-DWIFI_PASS=\"my-password\"'" \
pio run -t upload && pio device monitor -p /dev/ttyUSB0 -f esp8266_exception_decoder
```

## Issues
Please raise an issue for any problems you spot.