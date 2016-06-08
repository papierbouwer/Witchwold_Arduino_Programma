#include "RGB_Led.h"

// Stelt de RGB_Led in die op pinRed, pinYellow en pinBlue is aangesloten.
RGB_led::RGB_led(int pinRed, int pinYellow, int pinBlue)
{
  // Stelt de variabelen van het object in.
	outputPinRed = pinRed;
	outputPinBlue = pinBlue;
	outputPinYellow = pinYellow;

  // Stelt de pinmodes voor de pins in op output.
	pinMode(outputPinRed, OUTPUT);
	pinMode(outputPinBlue, OUTPUT);
	pinMode(outputPinYellow, OUTPUT);

  // Zet de led uit.
  setColor(OUTPUT_COLOR_NON);
}

// Stelt de RGB_Led in op een bepaalde kleur
void RGB_led::setColor(int red, int yellow, int blue)
{
  // Controleert of de inputs een geldige waarde hebben.
	if (0 < red < 1024 && 0 < yellow < 1024 && 0 < blue < 1024)
	{
    // Schrijft de RGB-waarden naar de ledpins.
		analogWrite(outputPinRed, red);
		analogWrite(outputPinBlue, blue);
		analogWrite(outputPinYellow, yellow);
	}
}
