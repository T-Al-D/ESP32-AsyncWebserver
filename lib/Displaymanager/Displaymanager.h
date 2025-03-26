// pre processing directive
#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

// variables (for Displaymanager only)
const short SCREEN_WIDTH = 128;
const short SCREEN_HEIGHT = 64;
const short OLED_SDA = 17;
const short OLED_SCL = 18;
const short OLED_RST = 21;
const short BOARD_ADRESS = 0x3C;

// methods
void initDisplay();
void showOutput(String output);

#endif
