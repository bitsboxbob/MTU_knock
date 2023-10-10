/* Read the temperature from a 10k thermistor and display the result on a 2-digit
7-segment display.
5V---Thermistor----10k----Gnd
                |
                A1
Arranged as above.
*/

//Global variable definitions
float therm_voltage = 0.0;
float temperature = 0.0;
int displayNum = 0;
unsigned long lastTime = 0;
unsigned long currentTime = 0;

// LED segment codes {a,b,c,d,e,f,g}
int digitBits[11][8] =
{
  {1,1,1,1,1,1,0,0}, //0
  {0,1,1,0,0,0,0,0}, //1
	{1,1,0,1,1,0,1,0}, //2
	{1,1,1,1,0,0,1,0}, //3
	{0,1,1,0,0,1,1,0}, //4
	{1,0,1,1,0,1,1,0}, //5
	{1,0,1,1,1,1,1,0}, //6
	{1,1,1,0,0,0,0,0}, //7
	{1,1,1,1,1,1,1,0}, //8
	{1,1,1,1,0,1,1,0}, //9
  {0,0,0,0,0,0,0,0}, //blank (10)
};

//Pin definitions
const int segA = 4, segB = 5, segC = 6, segD = 7, segE = 8, segF = 9, segG = 10, dp = 11; //seg pin assignments
const int comD1 13; //common pins for each digit
const int comD2 12;
const int thermistor A1;

//Array definitions
int segPin[8] = {segA, segB, segC, segD, segE, segF, segG, dp}; //segment pin array so they can be referenced 0-8
int comPin[2] = {comD1, comD2}; // commons pin array.
int display[2] = {0, 0}; //the 2 x 7-segment displays and the data on them.

//Flags
bool dpFlag = 0;  //indicates if the 7-seg display should show a decimal point

//Function prototypes
void displayUpdate(int);
void readThermistor();

//***********************************************************************************
void setup() 
{
  Serial.begin(9600);     //  opens serial port, sets data rate to 9600 bps

  //io pin directions
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(dp, OUTPUT);
  pinMode(comD1, OUTPUT);
  pinMode(comD2, OUTPUT);

  readThermistor(); // initial temperature measurement
}

//***********************************************************************************
void loop() 
{
  currentTime = millis();
  if ((currentTime - lastTime) > 2000)
    {
      readThermistor();
    }
  displayUpdate(displayNum);

}

//***********************************************************************************
void displayUpdate(int NumToDisplay)
{
  byte i = 0;
  byte digitToDisplay = 0;
    display[1] = 0; //takes care of the leading zero when NumToDisplay <10
    while (NumToDisplay > 0)  //split the number into individual digits
    {
      int mod = NumToDisplay % 10;
      display[i] = mod;
      NumToDisplay = NumToDisplay/10;
      i++;
    }

  //Put the digits on the display.
  //Set the digit commons to off
  for (byte i=0; i<2; i++)
  {
    digitalWrite(comPin[i], LOW);
  }
    for (byte digit = 0; digit < 2; digit++)//For each digit
    {
      digitToDisplay = display[digit];
      for (byte i=0; i<8; i++) //set up the segment pattern on the appropriate pins.
      {
        digitalWrite(segPin[i], digitBits[digitToDisplay][i]);
        //If displaying a time, need to make dp active on digit 1
      }
        if (dpFlag && digit==1)
        {
          digitalWrite(segPin[7],HIGH);
        }
      
      //Then select the digit's common pin
        digitalWrite(comPin[digit], HIGH);
        delay(5); //light long enough for pov
        digitalWrite(comPin[digit], LOW);
    }
  //Take down the decimal point flag
  dpFlag = 0;
}

void readThermistor()
{
  int analog_value = analogRead(thermistor);
      therm_voltage = (analog_value * 5.0) / 1024.0; 
        Serial.print("v= ");
        Serial.println(therm_voltage);
      temperature = 17.6*(therm_voltage-1.1); //using Philips 10k thermistor
        Serial.print("T= ");
        Serial.println(temperature);
  displayNum = temperature + 0.5; //round the temperature and convert to integer for display
  lastTime = millis();
}
