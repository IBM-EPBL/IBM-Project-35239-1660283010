#include<Servo.h>
int dist = 0;
int gassensor = 0;
long readUltrasonicDistance(int triggerPin, int echoPin)
{
 pinMode(triggerPin, OUTPUT); 
 digitalWrite(triggerPin, LOW);
 delayMicroseconds(2);
 digitalWrite(triggerPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(triggerPin, LOW);
 pinMode(echoPin, INPUT);
 return pulseIn(echoPin, HIGH);
}
Servo mainServo;
void setup()
{
 mainServo.attach(8, 500, 2500);
 pinMode(13,OUTPUT);
 pinMode(4,INPUT);
 pinMode(12,OUTPUT);
 pinMode(A0, INPUT);
 pinMode(12, OUTPUT);
 Serial.begin(9600);
}
void loop()
{
 dist = 0.01723 * readUltrasonicDistance(7, 7);
 if (dist <= 100) {
 mainServo.write(90);
 delay(1000); 
 } else {
 mainServo.write(0);
 delay(1000); 
 }
 if (digitalRead(4) == 1) {
 digitalWrite(13, HIGH);
 //delay(1000); 
 } else {
 digitalWrite(13, LOW);
 //delay(1000); 
 }
 gassensor = analogRead(A0);
 if (gassensor >= 250) {
 tone(12, 523, 1000); 
 delay(10);
 }
}
