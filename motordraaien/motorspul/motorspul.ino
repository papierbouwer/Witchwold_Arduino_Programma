//Include de library voor de stappenmotor e het schrijven naar het EEPROM
#include <Stepper.h>
#include <EEPROM.h>

//Defineer het aantal stappen per rotatie
#define STAPPEN_PER_ROTATIE 2048

//Defineer de aansluitingen voor de stappenmotor
#define STAPPENMOTOR_PIN_IN_1 9
#define STAPPENMOTOR_PIN_IN_2 10
#define STAPPENMOTOR_PIN_IN_3 11
#define STAPPENMOTOR_PIN_IN_4 12

//Defineer de startstap voor de stappenmotor
#define START_STEP 0

//Defineer de stopposities
#define STOP_POSTITIE_WERELDBOL_1 0
#define STOP_POSTITIE_WERELDBOL_2 512
#define STOP_POSTITIE_WERELDBOL_3 1024
#define STOP_POSTITIE_WERELDBOL_4 1536

//Defineer de in en outputs voor de leds.
#define LED_OUT_1 4
#define LED_OUT_2 5
#define LED_OUT_3 6
#define LED_OUT_4 7
#define LED_IN_1  2
#define LED_IN_2  3

//Defineer het adres waar de positie van de wereldbol wordt opgeslagen
#define EEPROM_ADDRES_WERELDBOL_POSITIE 0

//Maak een object Stepper aan voor de stappenmotor van de wereldbol.
Stepper wereldbolStappenmotor
(
  STAPPEN_PER_ROTATIE, 
  STAPPENMOTOR_PIN_IN_1, 
  STAPPENMOTOR_PIN_IN_2,
  STAPPENMOTOR_PIN_IN_3, 
  STAPPENMOTOR_PIN_IN_4
);

int wereldbolPositie;

void setup() {
  Serial.begin(9600);
  //Stel de snelheid van de stappenmotor in
  wereldbolStappenmotor.setSpeed(10);

  wereldbolPositie = EEPROM.read(EEPROM_ADDRES_WERELDBOL_POSITIE);
  if(wereldbolPositie != START_STEP)
    wereldbolStappenmotor.step(STAPPEN_PER_ROTATIE - wereldbolPositie);

  //Stel de pinmodes in voor de leds in de houder van de wereldbol.
  pinMode(LED_IN_1, OUTPUT);
  pinMode(LED_IN_2, OUTPUT);
  pinMode(LED_OUT_1, OUTPUT);
  pinMode(LED_OUT_2, OUTPUT);
  pinMode(LED_OUT_3, OUTPUT);
  pinMode(LED_OUT_4, OUTPUT);

  digitalWrite(LED_IN_1, HIGH);
  digitalWrite(LED_IN_2, HIGH);
  
  Serial.println("Alles ingesteld");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  draaiWereldbol(wereldbolStappenmotor, 700);
  digitalWrite(LED_IN_1, LOW);
  digitalWrite(LED_OUT_1, HIGH);
  digitalWrite(LED_IN_1, HIGH);
  digitalWrite(LED_IN_2, LOW);
  digitalWrite(LED_OUT_1, HIGH);
  delay(500);
  digitalWrite(LED_IN_2, HIGH);
  
  delay(500);
  draaiWereldbol(wereldbolStappenmotor, 70);
  delay(500);
}

void draaiWereldbol(Stepper& wereldbol, int stapAankomst)
{
  int positieWereldbol = map(EEPROM.read(EEPROM_ADDRES_WERELDBOL_POSITIE), 0, 255, 0, STAPPEN_PER_ROTATIE - 1);
  if(stapAankomst >= STAPPEN_PER_ROTATIE)
  {
    stapAankomst = positieWereldbol;
  }
  while(positieWereldbol != stapAankomst)
  {
    positieWereldbol++;
    if(positieWereldbol >= STAPPEN_PER_ROTATIE)
    {
      positieWereldbol = 0;
    }
    wereldbol.step(1);
    EEPROM.write(EEPROM_ADDRES_WERELDBOL_POSITIE, map(positieWereldbol, 0, STAPPEN_PER_ROTATIE - 1, 0, 255));
  }
}
