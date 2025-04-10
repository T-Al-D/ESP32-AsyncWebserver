# ESP32-AsyncWebserver

A modified **Asyc Webserver** on ESP32 for my final Project.
Access Point (Standalone) is used.
It has all functions from base-branch. Further functions:

- 8 actuators are controlled by 5 sensors
- "timemeasure" in StatusControl.cpp
- website representing the (current) state of the actuators

Tools that I used for the project:

- [ESP Tool](https://espressif.github.io/esptool-js/)
- [Platform.IO for VSCODE](https://platformio.org/install/ide?install=vscode)
- [Driver for the USB-URAT connection](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
- [Documentation of the board](https://resource.heltec.cn/download/WiFi_Kit_32_V3)
- [Building a HTML Webpage](https://www.w3schools.com/html/tryit.asp?filename=tryhtml_default)

Chip where this Programm was developed/tested:

- Chip is ESP32-S3 (QFN56) (revision v0.2)
- Features: Wi-Fi,BLE, Embedded Flash 8MB (GD)
- Crystal is 40MHz

Other Info:

- platform.ini contains a [common](https://github.com/T-Al-D/ESP32-AsyncWebserver/blob/main/platformio.ini) environment which all other environments can use (with variables!)
- If the **native** environment is unsed for testing, please install gcc and g++, and put them in the systemvariables!
- The partitions on the board can be changed in [huge_app.csv](https://github.com/T-Al-D/ESP32-AsyncWebserver/blob/main/data/partitions/huge_app.csv).
- If you wnat to connect to the asyncWebserber via mobile, you have to turn off your mobile data and turn on your WiFi!
- Test for native can be written, if needed but IoT exclusive libraries (example: "Aduino.h") can´t be tested on native!

Usage of space in kilobyte (during compile -> duration 33s):

- RAM : 44,5
- Flash : 793,1
