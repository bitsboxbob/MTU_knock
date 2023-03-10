/*
Make sounds with a murata piezo transducer on port A2. Resonant freq. 4kHz.
*/

#define piezo A2



void setup() 
{
  pinMode(piezo, OUTPUT);
}

void loop() {
  tone(piezo, 4000, 500);
  delay(2000);
}
