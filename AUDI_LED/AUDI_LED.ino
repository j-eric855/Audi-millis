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
unsigned long warteZeit = 100;
byte led[8] = {2, 3, 4, 5, 6, 7, 8, 9};
byte ledZustand[6][8] = {
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
};
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
  unsigned long zeitJetzt = millis();
  taster.tick();
  delay(10);
  Serial.println(merkerPower);
  if  (merkerPower == true)
  {

    for (byte i = 0; i < 6; i++)                  //Zeilen
    {
      if (zeitJetzt - zeitVorher > warteZeit)    //Verzögerung von warteZeit
      {

        for (byte j = 0; j < 8; j++)              //Spalten
        {
          digitalWrite(led[j], ledZustand[i][j]);


        }
        zeitJetzt = zeitVorher;
      }

    }
  }


}

void Taster_Funktion()
{
  merkerPower = !merkerPower;
}
