/*
   Funktion:        LEDs sollen im Laufmuster aufleuchten
   Programierer:    Eric Junker
   letzte Änderung: 22.09.2020
   Version:         1.0
   Hardware:        Pin 2-5 rote LEDs im Laufmuster
                    Pin 6-9 grüne LEDs im Laufmzuster
*/
#include <OneButton.h>
unsigned long zeitVorher = 0;
unsigned long warteZeit = 1000;
byte zaehler = 0;
byte led[8] = {2, 3, 4, 5, 6, 7, 8, 9};

OneButton taster(10, true);
bool merkerPower = false;

void setup()
{
  /******Pinbelegung********/
  for (byte i = 0; i < 8; i++)
  {
    pinMode(led[i], OUTPUT);
  }
  taster.attachClick(Taster_Funktion);
  Serial.begin(9600);
}

void loop()
{
  
  taster.tick();
  delay(10);
  Serial.println(merkerPower);
  if  (merkerPower == true)
  {
    unsigned long zeitJetzt = millis();
    if ((zeitJetzt - zeitVorher) > warteZeit)
    {
      digitalWrite( led[zaehler], LOW);
      digitalWrite( led[zaehler +1], HIGH);
      zaehler ++;
    }
    
    if (zaehler == 8)
    {
      zaehler = 0;
    }
    zeitVorher = zeitJetzt;
  }



}

void Taster_Funktion()
{
  merkerPower = !merkerPower;
}
