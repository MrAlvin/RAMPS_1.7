// Code for Keyes 4988 board and 1.8 degree stepper with 1/4 microstepping driver

// Original code found here: https://alexkenis.wordpress.com/2018/08/03/source-code-for-arduino-beginner-stepper-motor-control-video/

#define enaPin 2
#define stepPin 3
#define directPin 4
 
// put your setup code here, to run once:
void setup() {
  pinMode(enaPin,OUTPUT); // enable pin
  pinMode(stepPin,OUTPUT); // step pin
  pinMode(directPin,OUTPUT); // direct pin
  digitalWrite(directPin,HIGH); //fixed rotation direction
 
  delay(100);
}
 
// put your main code here, to run repeatedly:
void loop() {
  digitalWrite(enaPin,LOW); //enable pin pulled low
  while(1) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(2); // not really needed because overhead is ~4us
    digitalWrite(stepPin,LOW);
    delayMicroseconds(200); // slightly over 400rpm
  }
}
