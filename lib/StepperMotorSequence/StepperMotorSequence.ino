/*
This sample code is for testing the 4 stepper motors
Each motor will iturn rotate forward then backward
*/
int M1dirpin   = 39;
int M1steppin  = 38;

int M2dirpin   = 41;
int M2steppin  = 40;

int M3dirpin = 45;
int M3steppin = 44;

int M4dirpin = 43;
int M4steppin = 42;

void setup()
{
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board
  
  //Setup step and direction pins for output
  pinMode(M1dirpin,OUTPUT);
  pinMode(M1steppin,OUTPUT);
  
  pinMode(M2dirpin,OUTPUT);
  pinMode(M2steppin,OUTPUT);
  
  pinMode(M3dirpin,OUTPUT);
  pinMode(M3steppin,OUTPUT);
  
  pinMode(M4dirpin,OUTPUT);
  pinMode(M4steppin,OUTPUT);
}
void loop()
{
  int j;

  //Set direction for all channels
  digitalWrite(M1dirpin,LOW);    
  digitalWrite(M2dirpin,LOW);
  digitalWrite(M3dirpin,LOW);
  digitalWrite(M4dirpin,LOW);
  
  //Channel 1
  for(j=0;j<=1000;j++)          //Move 1000 steps
  {
    digitalWrite(M1steppin,LOW);
    delayMicroseconds(2);
    digitalWrite(M1steppin,HIGH);
    delay(1);
  }
  digitalWrite(M1dirpin,HIGH);  //Change direction
  
  for(j=0;j<=1000;j++)          //Move another 1000 steps
  {
    digitalWrite(M1steppin,LOW);
    delayMicroseconds(2);
    digitalWrite(M1steppin,HIGH);
    delay(1);
  }
  
  //Channel 2
  for(j=0;j<=1000;j++)
  {
    digitalWrite(M2steppin,LOW);
    delayMicroseconds(2);
    digitalWrite(M2steppin,HIGH);
    delay(1);
  }
  digitalWrite(M2dirpin,HIGH);
  for(j=0;j<=1000;j++)
  {
    digitalWrite(M2steppin,LOW);
    delayMicroseconds(2);
    digitalWrite(M2steppin,HIGH);
    delay(1);
  }
  
  //Channel 3
  for(j=0;j<=1000;j++)
  {
    digitalWrite(M3steppin,LOW);
    delayMicroseconds(2);
    digitalWrite(M3steppin,HIGH);
    delay(1);
  }
  digitalWrite(M3dirpin,HIGH);
  for(j=0;j<=1000;j++)
  {
    digitalWrite(M3steppin,LOW);
    delayMicroseconds(2);
    digitalWrite(M3steppin,HIGH);
    delay(1);
  }
  
  //Channel 4
  for(j=0;j<=1000;j++)
  {
    digitalWrite(M4steppin,LOW);
    delayMicroseconds(2);
    digitalWrite(M4steppin,HIGH);
    delay(1);
  }
  digitalWrite(M4dirpin,HIGH);
  for(j=0;j<=1000;j++)
  {
    digitalWrite(M4steppin,LOW);
    delayMicroseconds(2);
    digitalWrite(M4steppin,HIGH);
    delay(1);
  }
}
