/*
   Funktion:        LEDs sollen im Laufmuster aufleuchten
   Programierer:    Eric Junker
   letzte Änderung: 03.11.2020
   Version:         1.5
   Hardware:        Pin 2-5 rote LEDs im Laufmuster
                    Pin 6-9 grüne LEDs im Laufmzuster
*/
#include <OneButton.h>
unsigned long letzteZeit = 0;
unsigned long warteZeit = 150;
byte zaehler = 0;
byte led[8] = {2, 3, 4, 5, 6, 7, 8, 9};

OneButton taster(10, true);
bool merkerPower = false;

void setup()
{

  for (byte i = 0; i < 8; i++)
  {
    pinMode(led[i], OUTPUT);                        //Pinbelegung 2-9 Output
  }
  taster.attachClick(Taster_Funktion);
  Serial.begin(9600);
}

void loop()
{
  taster.tick();
  delay(10);
  Serial.println(merkerPower);
  unsigned long aktuelleZeit = millis();              //aktuelle Zeit setzten
  if  (merkerPower == true)
  {

    if ((aktuelleZeit - letzteZeit) > warteZeit)      //Zeitabfrage warte Zeit zwischen den durchgängen
    {
      
      {
        digitalWrite( led[zaehler], LOW);               //vorherriger Pin wird ausgeschaltet
        zaehler ++;
        if (zaehler == 8)                               //nach 7 wechseln ist der durchgang vorbei und wird neu gestartet
        {
          zaehler = 0;
        }
        digitalWrite( led[zaehler], HIGH);              //nächster Pin wird eingeschaltet
        letzteZeit = aktuelleZeit;                      //Zeit wird neu gesetzt
      }                                                 
    }

  }
  else                                                //Taster aus LEDs aus
  {
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(led[i], LOW);
      zaehler = 7;
    }
  }
}


void Taster_Funktion()                                //merker wird Invertiert
{
  merkerPower = !merkerPower;
}
