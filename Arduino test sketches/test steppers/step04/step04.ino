// Code for testing stepper boards on RAMPS 1.7
// MrAlvin 2018

/*  Same as step03, but without any delay() statements
 *  so this code can be run at the same time as all 
 *  the other other sections of the board are being tested
 */

// For 4988 style stepper boards. 

//#define REV_B
#define REV_C

#define enaPinX    55
#define stepPinX   56
#define directPinX 57

#ifdef REV_B
  #define enaPinY    58
  #define stepPinY   62
  #define directPinY 63
#else
  #define enaPinY    58
  #define stepPinY   46
  #define directPinY 42
#endif

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
    
  digitalWrite(enaPinX,LOW);  //enable pin pulled low
  digitalWrite(enaPinY,LOW);  //enable pin pulled low
  digitalWrite(enaPinZ,LOW);  //enable pin pulled low
  digitalWrite(enaPinE0,LOW); //enable pin pulled low
  digitalWrite(enaPinE1,LOW); //enable pin pulled low

  digitalWrite(directPinX,HIGH);  //set rotation direction
  digitalWrite(directPinY,HIGH);  //set rotation direction
  digitalWrite(directPinZ,HIGH);  //set rotation direction
  digitalWrite(directPinE0,HIGH); //set rotation direction
  digitalWrite(directPinE1,HIGH); //set rotation direction
  
  delay(100);
}
 
// put your main code here, to run repeatedly:
void loop() {
  SetDirection();
  OneStepAllPins();
}


void SetDirection(){
  static unsigned long direction_millis = 0;
  static unsigned long direction_interval = 1000;  // move one directon for 1000 milli seconds = 1 second
  static boolean step_direction = true;
  if ( millis() - direction_millis >  direction_interval )  {
    if(step_direction) {
      digitalWrite(directPinX,HIGH);  //set rotation direction
      digitalWrite(directPinY,HIGH);  //set rotation direction
      digitalWrite(directPinZ,HIGH);  //set rotation direction
      digitalWrite(directPinE0,HIGH); //set rotation direction
      digitalWrite(directPinE1,HIGH); //set rotation direction
      step_direction = !step_direction; // ready to reverse direction
    }else{
      digitalWrite(directPinX,LOW);  //set rotation direction
      digitalWrite(directPinY,LOW);  //set rotation direction
      digitalWrite(directPinZ,LOW);  //set rotation direction
      digitalWrite(directPinE0,LOW); //set rotation direction
      digitalWrite(directPinE1,LOW); //set rotation direction
      step_direction = !step_direction; // ready to reverse direction
    } // if step_direction
    direction_millis = millis();
  } // if millis
} // StepAllPins


void OneStepAllPins() {
  static int idxS = 0;
  static unsigned long pause_micros = 0;
  static unsigned long pause_interval = 0;
  switch(idxS) {
    case 0:
      digitalWrite(stepPinX,HIGH);
      digitalWrite(stepPinY,HIGH);
      digitalWrite(stepPinZ,HIGH);
      digitalWrite(stepPinE0,HIGH);
      digitalWrite(stepPinE1,HIGH);
      pause_micros = micros();
      pause_interval = 20; // pause 20 micro seconds in next step
      idxS++;
      break;
    case 1:
      if ( micros() - pause_micros >  pause_interval )  { //pause min. 4 micro seconds, however not really needed because program overhead is already >4uS
        idxS++;
      }
      break;
    case 2:
      digitalWrite(stepPinX,LOW);
      digitalWrite(stepPinY,LOW);
      digitalWrite(stepPinZ,LOW);
      digitalWrite(stepPinE0,LOW);
      digitalWrite(stepPinE1,LOW);
      pause_micros = micros();
      pause_interval = 1000; // 1000 for no micro step
      idxS++;
    case 3:
     if ( micros() - pause_micros >  pause_interval )  { //pause min. 4 micro seconds, however not really needed because program overhead is already >4uS
        idxS = 0;
      }
      break;
      default:
        idxS = 0;
      break;
  } //switch
} // OneStepAllPins()
  
