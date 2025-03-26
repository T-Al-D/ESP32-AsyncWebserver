#include "Displaymanager.h"
#include <Wire.h>

// from main.cpp
extern String output;

// create a display object (I2C-adress here is an example: 0x3C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void initDisplay()
{
    // Initialize I2C (SDA = 1st num, SCL = 2nd num)
    Wire.begin(OLED_SDA, OLED_SCL);

    // init the display :  0x3C is the I2C-Adress of the display
    if (!display.begin(SSD1306_SWITCHCAPVCC, BOARD_ADRESS)) {
        Serial.println(F("OLED-Display could not be initialized"));
        while (1) { };
    } else {
        // show text on display
        Serial.println("OLED Initialized Successfully");
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print(F("Initialization....."));
        display.display();

        // Small delay for display initialization
        delay(500);
    }
}

// Update the display
void showOutput(String output)
{
    display.clearDisplay(); // Clear display before new drawing
    display.setCursor(0, 0); // Set the cursor position
    display.print(output); // Print the count to the display
    display.display(); // Refresh the display
}