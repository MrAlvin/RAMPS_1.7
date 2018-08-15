// Code for testing stepper boards on RAMPS 1.7
// MrAlvin 2018
// Inspired by code found here: https://alexkenis.wordpress.com/2018/08/03/source-code-for-arduino-beginner-stepper-motor-control-video/

// For 4988 style stepper boards. 
// Stepper: 1.8 degree - with 1/4 microstepping


#define STEPPER X  //options are X, Y, Z, E0, E1

#ifdef STEPPER == X
  #define enaPin    55
  #define stepPin   56
  #define directPin 57
#elif STEPPER == Y
  #define enaPin    58
  #define stepPin   62
  #define directPin 63
#elif STEPPER == Z
  #define enaPin    67
  #define stepPin   68
  #define directPin 69
#elif STEPPER == E0
  #define enaPin    30
  #define stepPin   34
  #define directPin 36
#elif STEPPER == E1
  #define enaPin    22
  #define stepPin   24
  #define directPin 26
#endif

 
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
