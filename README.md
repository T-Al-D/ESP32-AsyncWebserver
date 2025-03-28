# ESP32-AsyncWebserver

A small project for an **Asyc Webserver** on ESP32: Access Point (Standalone) is used.
Functions:

- 2 Buttons on a dynamic Website to control
- Website refreshes, if state changes
- one small input element for textinput
- photo-resistor is being read for button1 and button2

Tools for the project:

- [ESP Tool](https://espressif.github.io/esptool-js/)
- [Platform.IO for VSCODE](https://platformio.org/install/ide?install=vscode)
- [Driver for the USB-URAT connection](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
- [Documentation of the board](<https://resource.heltec.cn/download/WiFi_Kit_32_V3/HTIT-WiFi%20kit32_V3(Rev1.1).pdf>)

Chip where this Programm was developed/tested:

- Chip is ESP32-S3 (QFN56) (revision v0.2)
- Features: Wi-Fi,BLE,Embedded Flash 8MB (GD)
- Crystal is 40MHz

Other Info:

- platform.ini contains a [common](https://github.com/T-Al-D/ESP32-AsyncWebserver/blob/main/platformio.ini) enviorement which all other environments can use (with variables!)
- If the **native** environment is unsed for testing, please install gcc and g++, and put them in the systemvariables!
- the partitions on the board can be changed in [huge_app.csv](https://github.com/T-Al-D/ESP32-AsyncWebserver/blob/main/data/partitions/huge_app.csv)

Usage of space in kilobyte (during compile):

- RAM : 44,5
- Flash : 787,9
