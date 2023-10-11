/*
Run a UK traffic light sequence in response to push button press.
*/

//Port definitions
const int redLight = 19; //Port A5 red led
const int yellowLight = 18; //Port A4 yellow led
const int greenLight = 17; //Port A3 green led
const int button = 3; //Sw1

void setup() {
//i/o port directions
pinMode (button, INPUT_PULLUP);
pinMode (redLight, OUTPUT);
pinMode (yellowLight, OUTPUT);
pinMode (greenLight, OUTPUT);

}

void loop() {

  digitalWrite(redLight,HIGH);

  while (digitalRead(button) == HIGH){}  //Wait here for a button push

  digitalWrite(yellowLight, HIGH); //Traffic light sequence
  delay(2000);
  digitalWrite(redLight,LOW);
  digitalWrite(yellowLight,LOW);
  digitalWrite(greenLight, HIGH);
  delay(5000);
  digitalWrite(greenLight, LOW);
  digitalWrite(yellowLight, HIGH);
  delay(2000);
  digitalWrite(yellowLight, LOW);

}
