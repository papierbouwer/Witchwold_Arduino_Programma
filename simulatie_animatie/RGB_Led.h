#ifndef RGB_LED

#ifndef OUTPUT_COLOR_NON
#define OUTPUT_COLOR_NON 0, 0, 0
#endif

#define RGB_LED

#include "arduino.h"

class RGB_led
{
	int outputPinRed,
		outputPinBlue,
		outputPinYellow;

public:
	RGB_led(int pinRed, int pinYellow, int pinBlue);
	//~RGB_led();
  void setColor(int red, int yellow, int blue);
private:

};

#endif
