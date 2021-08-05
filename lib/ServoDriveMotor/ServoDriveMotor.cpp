/*
Useing port S1 and channels S1 and S2 to drive the two motors on the robot.
The motors must be connected through the Sabertooth driver.
The sabertooth must be in mode Microcontroller pulses, independent linear control mode.
1000us to 2000us control the speed and direction. 1500us is stop.
Any speed outside this range will be ignored.
*/
#include <Servo.h>
#include <Arduino.h>

Servo myservoA;      // create servo object to control a servo
Servo myservoB;      // create servo object to control a servo



void setup()
{ 
    pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
    digitalWrite(49, 1);                 //Enable IO power on main CPU board
    
    myservoA.attach(3);  // attaches the servo pin 3 to the servo object
    myservoB.attach(2);  // attaches the servo pin 2 to the servo object
    Serial.begin(9600);
}

void loop() 
{ 
    Serial.println("stop");
    myservoA.writeMicroseconds(1500);      //Stop 
    myservoB.writeMicroseconds(1500);      // 
    delay(1500);   
                                           //
    Serial.println("fwd slow");
    myservoA.writeMicroseconds(1800);      //Forward Slow  
    myservoB.writeMicroseconds(1800);      // 
    delay(1500);                           // 

    Serial.println("fwd fast");
    myservoA.writeMicroseconds(2000);      //Forward Fast   
    myservoB.writeMicroseconds(2000);      //  
    delay(1500);                           // 

    Serial.println("fwd slow");
    myservoA.writeMicroseconds(1800);      //Forward Slow  
    myservoB.writeMicroseconds(1800);      // 
    delay(1500);                           // 

    Serial.println("stop");
    myservoA.writeMicroseconds(1500);      //Stop 
    myservoB.writeMicroseconds(1500);      //  
    delay(1500);                           // 

    Serial.println("bwd slow");
    myservoA.writeMicroseconds(1200);      //Backward Slow  
    myservoB.writeMicroseconds(1200);      // 
    delay(1500);                           // 

    Serial.println("bwd fast");
    myservoA.writeMicroseconds(1000);      //Backward Fast 
    myservoB.writeMicroseconds(1000);      // 
    
    delay(1500);                           //

    Serial.println("bwd slow");
    myservoA.writeMicroseconds(1200);      //Backward Slow   
    myservoB.writeMicroseconds(1200);      //  
    delay(1500);                           // 

    Serial.println("stop");
    myservoA.writeMicroseconds(1500);      //Stop  
    myservoB.writeMicroseconds(1500);      //  
    delay(1500);                           // 
  
} 



