/*
This program will allow you to change the ID of a smart motor if 
you know the ID of the motor
*/

#include "Herkulex.h"
int n=0xfe; //motor ID - verify your ID !!!! 0xfe is all motors, ie broadcast
/*
0xfd or 253 is the default
0xfe or 254 is broadcast, ie all motors
*/

int oldID,newID;
int mystep=0;
 
void setup() 
{
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board
  
  Herkulex.beginSerial2(115200); //open serial port 2 to talk to the motors
  Herkulex.reboot(n);            //reboot first motor
  delay(500);
  Herkulex.initialize();         //initialize motors
  delay(200); 
  Serial.begin(9600);
  Serial.println("Enter current ID(default is 253): >");
}

int readline(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\n': // Ignore new-lines
        break;
      case '\r': // Return on CR
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len-1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  // No end of line has been found, so return -1.
  return -1;
}
 
void loop()
{
   static char buffer1[80];
   static char buffer2[80];
     
 if(mystep==0)
 {
  if(readline(Serial.read(), buffer1, 80)>0)
  {
    mystep++;
    Serial.println("Enter new ID: >");
  }
 }
 
  if(mystep==1)
  {  
    if(readline(Serial.read(), buffer2, 80)>0)
    {
      mystep++;
    }
  }
  
   if(mystep==2)
   {
     oldID=atoi(buffer1);
     newID=atoi(buffer2);
     
     Herkulex.set_ID(oldID,newID);  
     
     Serial.print("ID changed from ");  
     Serial.print(oldID);
     Serial.print(" to ");
     Serial.println(newID);
     mystep++;
   }   
}



