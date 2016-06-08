// Defineer de ledpins voor de output van de meerkleurenled, deze moeten allemaal op een PWM-poort worden aangesloten.
#define LEDPIN_RED 3
#define LEDPIN_BLUE 5
#define LEDPIN_YELLOW 6

// Defineer de outputpins voor de diverse effecten.
#define OUTPUT_SNOW 8
#define OUTPUT_RAIN 7
#define OUTPUT_HEAT 4

// Defineer de verschillende kleuren voor de verschillende soorten weer.
#define OUTPUT_COLOR_NON  0, 0, 0 
#define OUTPUT_COLOR_SNOW 0, 0, 0
#define OUTPUT_COLOR_RAIN 0, 0, 0
#define OUTPUT_COLOR_HEAT 0, 0, 0

// Defineer de pin voor de startknop
#define INPUT_STARTPIN 2

// Defineer tijden voor hoe lang bepaalde opdrachten duren in miliseconden.
#define TIMESPAN_TURNING  500
#define TIMESPAN_POINTING 500
#define TIMESPAN_WEATHER  500
#define TIMESPAN_WAITING  500

// Defineer een enum voor de state-machine.
enum State { stopped, started, turning, pointing, weather, cleanup };

// Defineer een enum voor het opslaan van het soort weer.
enum Climate { snow, rain, heat, null };

// Maak een integers aan die de tijd bijhouden.
int currentTime = 0;
int nextTime = 0;

// Maak een State aan voor de state-machine
State state;
  
// Maak een Climate aan voor het opslaan van het klimaat voor het aansturen van het weer.
Climate climate;

// Invoegen "RGB_Led.h" voor de Class RGB_Led.
#include "RGB_Led.h"

// Deze code wordt alleen direct na het opstarten gedraaid.
void setup() 
{
	// Het instellen van de outputs voor de effecten.
	pinMode(OUTPUT_SNOW, OUTPUT);
	pinMode(OUTPUT_RAIN, OUTPUT);
	pinMode(OUTPUT_HEAT, OUTPUT);
	pinMode(INPUT_STARTPIN, INPUT);
	
	// Maak een RGB_Led-object aan voor het aansturen van de led.
	RGB_led colorLed = RGB_led(LEDPIN_RED, LEDPIN_YELLOW, LEDPIN_BLUE);
	
	// Maak een State aan voor de state-machine
	state = stopped;
	
	// Maak een Climate aan voor het opslaan van het klimaat voor het aansturen van het weer.
	climate = null;
}

// Deze code wordt continu uitgevoerd.
void loop() 
{
	// 
	currentTime = millis();
	switch (state)
	{
		case stopped:
			if(digitalRead(INPUT_STARTPIN))
				state = started;
			break;
			
		case started:
			randomSeed(micros());
			char randomClimate = random(1, 4);
			switch(randomClimate)
			{
				case 1:
					climate = snow;
					break;
				case 2:
					climate = rain;
					break;
				case 3:
					climate = heat;
					break;
				default:
					climate = null;
					break;
			}
			nextTime = currentTime + TIMESPAN_TURNING;
			state = turning;
            break;
			
		case turning:
			if(currentTime < nextTime)
				setTurning();
			else
			{
				nextTime = currentTime + TIMESPAN_POINTING;
				state = pointing;
			}
			break;
			
		case pointing:
			if(currentTime < nextTime)
				setPointing(climate);
			else
			{
				nextTime = currentTime + TIMESPAN_WEATHER;
				state = weather;
			}
			break;
			
		case weather:
			if(currentTime < nextTime)
				setWeather(climate);
			else
			{
				nextTime = currentTime + TIMESPAN_WAITING;
				state = cleanup;
			}
			break;
			
		case cleanup:
			climate = null;
			setWeather(climate);
			if( currentTime > nextTime)
				state = stopped;
			break;
	}
}

void setTurning()
{
  
}

void setPointing(Climate climate)
{
  
}

void setWeather(Climate climate)
{
  
}



