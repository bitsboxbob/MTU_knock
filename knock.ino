/*
Toggle a LED with a tap on a piezo transducer
*/
//Define ports for the led and piezo transducer
const int piezo A2;
const int LED A5;

int knockValue = 0; //stores the value read from the piezo input
int threshold = 50;  //the value above which the knockValue must reach
bool ledOn = 0; //led status flag

void readKnock();

void setup() 
{
  Serial.begin(9600);     //  opens serial port, sets data rate to 9600 bps
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);
  delay(2000);
  digitalWrite(LED,LOW);
  delay(500);
}

void loop() 
{
  readKnock();
  //Serial.print("KnockValue= ");
  //Serial.println(knockValue);

  if (ledOn)
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
}

void readKnock()
{
  knockValue = analogRead(piezo);
  if (knockValue >= threshold)
  {
    ledOn = !ledOn;
    delay(500);
  }
  
}
