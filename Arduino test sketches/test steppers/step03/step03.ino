// Code for testing stepper boards on RAMPS 1.7
// MrAlvin 2018
// Inspired by code found here: https://alexkenis.wordpress.com/2018/08/03/source-code-for-arduino-beginner-stepper-motor-control-video/

// For 4988 style stepper boards. 

#define enaPinX    55
#define stepPinX   56
#define directPinX 57

#define enaPinY    58
#define stepPinY   62
#define directPinY 63

#define enaPinZ    67
#define stepPinZ   68
#define directPinZ 69

#define enaPinE0    30
#define stepPinE0   34
#define directPinE0 36

#define enaPinE1    22    
#define stepPinE1   24
#define directPinE1 26
 
// put your setup code here, to run once:
void setup() {
  pinMode(enaPinX,OUTPUT);  // enable pin
  pinMode(enaPinY,OUTPUT);  // enable pin
  pinMode(enaPinZ,OUTPUT);  // enable pin
  pinMode(enaPinE0,OUTPUT); // enable pin
  pinMode(enaPinE1,OUTPUT); // enable pin
  
  pinMode(stepPinX,OUTPUT);  // step pin
  pinMode(stepPinY,OUTPUT);  // step pin
  pinMode(stepPinZ,OUTPUT);  // step pin
  pinMode(stepPinE0,OUTPUT); // step pin
  pinMode(stepPinE1,OUTPUT); // step pin
    
  pinMode(directPinX,OUTPUT);  // direct pin
  pinMode(directPinY,OUTPUT);  // direct pin
  pinMode(directPinZ,OUTPUT);  // direct pin
  pinMode(directPinE0,OUTPUT); // direct pin
  pinMode(directPinE1,OUTPUT); // direct pin
    
  digitalWrite(directPinX,HIGH);  //set rotation direction
  digitalWrite(directPinY,HIGH);  //set rotation direction
  digitalWrite(directPinZ,HIGH);  //set rotation direction
  digitalWrite(directPinE0,HIGH); //set rotation direction
  digitalWrite(directPinE1,HIGH); //set rotation direction

  delay(100);
}
 
// put your main code here, to run repeatedly:
void loop() {
  digitalWrite(enaPinX,LOW);  //enable pin pulled low
  digitalWrite(enaPinY,LOW);  //enable pin pulled low
  digitalWrite(enaPinZ,LOW);  //enable pin pulled low
  digitalWrite(enaPinE0,LOW); //enable pin pulled low
  digitalWrite(enaPinE1,LOW); //enable pin pulled low
  
  while(1) {
    digitalWrite(stepPinX,HIGH);
    digitalWrite(stepPinY,HIGH);
    digitalWrite(stepPinZ,HIGH);
    digitalWrite(stepPinE0,HIGH);
    digitalWrite(stepPinE1,HIGH);
        
    delayMicroseconds(20); // not really needed because overhead is ~4us per digitalWrite()
    
    digitalWrite(stepPinX,LOW);
    digitalWrite(stepPinY,LOW);
    digitalWrite(stepPinZ,LOW);
    digitalWrite(stepPinE0,LOW);
    digitalWrite(stepPinE1,LOW);
        
    delayMicroseconds(1000); // 1000 for no micro step
    
  }
}
