/*
Test out the low cost ultrasound sensor
*/
const int trigPin = 12;
const int echoPin = 11;
 
void setup() 
{
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board
  
  pinMode(trigPin, OUTPUT);            //Setup ultrasound pins
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);                  // initialize serial communication:
}
 
void loop()
{
  long duration, cm;
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.println();
  delay(100);
}
 
 
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
} 
