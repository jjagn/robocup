/*
Test out the limit switches on the IO extension board
*/
int PinLimit01 = 30;
int PinLimit02 = 31;
int PinLimit03 = 32;
int PinLimit04 = 33;

int PinLimit05 = 34;
int PinLimit06 = 35;
int PinLimit07 = 36;
int PinLimit08 = 37;

void setup()
{
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board
 
  pinMode(PinLimit01,INPUT);  //Define all the pins as inputs
  pinMode(PinLimit02,INPUT);
  pinMode(PinLimit03,INPUT);
  pinMode(PinLimit04,INPUT);
  
  pinMode(PinLimit05,INPUT);
  pinMode(PinLimit06,INPUT);
  pinMode(PinLimit07,INPUT);
  pinMode(PinLimit08,INPUT);
  
  Serial.begin(9600);        //Set up serial communications
}

void loop()
{
  int Limit01,Limit02,Limit03,Limit04,Limit05,Limit06,Limit07,Limit08;
  
  //Read all limit switches
  Limit01=digitalRead(PinLimit01);
  Limit02=digitalRead(PinLimit02);
  Limit03=digitalRead(PinLimit03);
  Limit04=digitalRead(PinLimit04);
  
  Limit05=digitalRead(PinLimit05);
  Limit06=digitalRead(PinLimit06);
  Limit07=digitalRead(PinLimit07);
  Limit08=digitalRead(PinLimit08);
  
  //Print result to serial port
  Serial.print(Limit01);
  Serial.print(" ");
  Serial.print(Limit02);
  Serial.print(" ");
  Serial.print(Limit03);
  Serial.print(" ");
  Serial.print(Limit04);
  Serial.print(" ");
  Serial.print(Limit05);
  Serial.print(" ");
  Serial.print(Limit06);
  Serial.print(" ");
  Serial.print(Limit07);
  Serial.print(" ");
  Serial.print(Limit08);
  Serial.println("");
}
