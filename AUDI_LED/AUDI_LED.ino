/*
   Funktion:        LEDs sollen im Laufmuster aufleuchten
   Programierer:    Eric Junker
   letzte Änderung: 22.09.2020
   Version:         1.0
   Hardware:        Pin 2-5 rote LEDs im Laufmuster
                    Pin 6-9 grüne LEDs im Laufmzuster
*/
#include <OneButton.h>
unsigned long letzteZeit = 0;
unsigned long warteZeit = 90;
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
  unsigned long aktuelleZeit = millis();
  if  (merkerPower == true)
  {

    if ((aktuelleZeit - letzteZeit) > warteZeit)
    {
      digitalWrite( led[zaehler], LOW);
      zaehler ++;
      if (zaehler == 8)
      {
        zaehler = 0;
      }
      digitalWrite( led[zaehler], HIGH);
      letzteZeit = aktuelleZeit;
    }

  }
  else
  {
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(led[i], LOW);
    }
  }
}


void Taster_Funktion()
{
  merkerPower = !merkerPower;
}
