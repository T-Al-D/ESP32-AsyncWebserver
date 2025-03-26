#ifndef HTML_SEND_H
#define HTML_SEND_H
#include <Arduino.h>

// methods
// the method "DesignButtons" should not be accessed anywhere else!
String SendHTML(bool led1stat, bool led2stat, String otherInfo);

#endif