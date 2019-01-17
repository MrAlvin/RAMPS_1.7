/*
 * This sketch will test several elements on the RAMPS 1.7 board
 *       Use the Arduino Monitor (or any serial terminal program) to see results and readouts.
 *       
 * The following sections on the RAMPS 1.7 board is being tested:
 *  - EEPROM   
 *       is read and written to once, during setup()
 *  - Mosfets   
 *       one mosfet is blinked three times, then the next mosfet is being blinked three times
 *       continues rotation of which mosfet to blink while the sketch is running
 *  - Temperature pins  
 *       are read, and raw value is displayed.
 *       Connect any resistor between each of the two pins, 
 *       to change the number being displayed
 *  - End-stops
 *       reads and shows the status of all end-stops
 *  - Z-probe
 *       reads and shows the status of the Z-probe at the end of the End-stop status line
 *  - Stepper drivers X, Y, Z, E0, E1
 *       All steppers are moved for 1 second in one direction, then direction is changed,
 *       and this continues, while the sketch is running
 */

//***** For End-stops
#define X_MIN_PIN           3
#define X_MAX_PIN           2
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19
#define Z_PROBE_PIN        64

const int DebugLed_pin = 13; 
bool PauseEndStopBlink = false;

//***** For Blink n-times of mosfets
byte _blinks = 3;
byte _blink_minor = 0;

int blinkN_pin = 13;    //the pin number that the LED is connected to
int blinkN_on_delay = 100;    //change this value to adjust the number of MilliSeconds the LED is ON
int blinkN_off_delay = 100;   //change this value to adjust the number of MilliSeconds the LED is OFF
int blinkN_long_off_delay = 400;


//***** For EEPROM
#include <Wire.h>     // for I2C
 
#define eeprom_address 0x50    // device address 
byte d = 0;
byte b = 0;
int  i = 0;


//***** Analog Read and Serial Out example, but without the use of delay() *****
const int analogInPin_1 = A5;  // Analog input pin that the potentiometer is attached to
const int analogInPin_2 = A6;  // Analog input pin that the potentiometer is attached to
const int analogInPin_3 = A7;  // Analog input pin that the potentiometer is attached to


//***** For 5 Stepper drivers on RAMPS 1.7
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


//*****************************************************//
//****                                             ****//
//****                 SETUP                       ****//
//****                                             ****//
//*****************************************************//

void setup()
{
  // initialize end-stop pins 
  pinMode(X_MIN_PIN, INPUT_PULLUP);  
  pinMode(X_MAX_PIN, INPUT_PULLUP);  
  pinMode(Y_MIN_PIN, INPUT_PULLUP);  
  pinMode(Y_MAX_PIN, INPUT_PULLUP);  
  pinMode(Z_MIN_PIN, INPUT_PULLUP);  
  pinMode(Z_MAX_PIN, INPUT_PULLUP);  
  pinMode(Z_PROBE_PIN, INPUT_PULLUP);

  // initialize digital pin 13 (Built-in LED) 
  pinMode(DebugLed_pin, OUTPUT);

  // initialize mosfet pins 
  pinMode(8, OUTPUT);  //fan2 
  digitalWrite(8, LOW);
  pinMode(9, OUTPUT);  //heat-bed
  digitalWrite(9, LOW);
  pinMode(10, OUTPUT); //fan1
  digitalWrite(10, LOW);
  pinMode(11, OUTPUT); //hot-end
  digitalWrite(11, LOW);
  pinMode(12, OUTPUT); //pwr-on or fan3
  digitalWrite(12, LOW);

  
  Serial.begin(115200); // Initialize the serial
  Serial.println( F("Hello World!") );

  test_i2c_eeprom();
  
  Serial.print( F("blinking pin ") );
  Serial.println(blinkN_pin );
  Serial.println( F("Showing analog"));

  // Initialize stepper driver pins
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

  //set enable pins to: Enable
  digitalWrite(enaPinX,LOW);  //enable pin pulled low
  digitalWrite(enaPinY,LOW);  //enable pin pulled low
  digitalWrite(enaPinZ,LOW);  //enable pin pulled low
  digitalWrite(enaPinE0,LOW); //enable pin pulled low
  digitalWrite(enaPinE1,LOW); //enable pin pulled low

  //set direction pins 
  digitalWrite(directPinX,HIGH);  //set rotation direction
  digitalWrite(directPinY,HIGH);  //set rotation direction
  digitalWrite(directPinZ,HIGH);  //set rotation direction
  digitalWrite(directPinE0,HIGH); //set rotation direction
  digitalWrite(directPinE1,HIGH); //set rotation direction
}

//*****************************************************//
//****                                             ****//
//****      eeprom stuff                           ****//
//****                                             ****//
//*****************************************************//

void test_i2c_eeprom(){
  Serial.println( F("Testing EEPROM") );
  Wire.begin();

  //check to see if this eeprom test has been done before
  d = readData(i+1);
  if (d > 0) b = d;
 
  //write data out
  Serial.println("Writing data.");
  for ( i = 0; i < 10; i++ )
  {
    writeData(i,i+b);
  }
  Serial.println("Complete");
  //read data back
  Serial.println("Reading data.");
  for ( i = 0; i < 10; i++ )
  {
    Serial.print(i);
    Serial.print(" : ");
    d = readData(i);
    Serial.println(d, DEC);
  }
  Serial.println( F("EEPROM Done"));
  Serial.println();
}
 
// writes a byte of data in i2c memory location eaddress
void writeData(unsigned int eaddress, byte data) 
{
  Wire.beginTransmission(eeprom_address);
  // set the pointer position
  Wire.write((int)(eaddress >> 8));
  Wire.write((int)(eaddress & 0xFF));
  Wire.write(data);
  Wire.endTransmission();
  delay(10);
}
 
// reads a byte of data from i2c memory location eaddress
byte readData(unsigned int eaddress) 
{
  byte result;
  Wire.beginTransmission(eeprom_address);
  // set the pointer position
  Wire.write((int)(eaddress >> 8));
  Wire.write((int)(eaddress & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(eeprom_address,1); // get the byte of data
  result = Wire.read();
  return result;
}


//*****************************************************//
//****                                             ****//
//****      MAIN LOOP                              ****//
//****                                             ****//
//*****************************************************//

void loop(){
  AnalogRead_and_SerialOut_example();  // reads and displays an analog value
  Endstops(); //reads and shows endstop pin status
  blinkN(); //blinks a mosfet three times, then moves to the next mosfet
  SetDirection(); // switches direction of steppers every 1 second
  OneStepAllPins(); //moves the steppers
}


//*****************************************************//
//****                                             ****//
//****      Analog Temperature pins                ****//
//****                                             ****//
//*****************************************************//

void AnalogRead_and_SerialOut_example() {
  static unsigned long analog_delay = 500;      // milli seconds to wait between analog readings
  static unsigned long analog_millis = 0;
  static int sensorValue_1 = 0;        // value read from the pot
  static int sensorValue_2 = 0;        // value read from the pot
  static int sensorValue_3 = 0;        // value read from the pot
  
  //static int outputValue = 0;        // value output to the PWM (analog out)

  if (millis() - analog_millis > analog_delay )  // if its time to make a new reading
  { 
    // read the analog in value:
    sensorValue_1 = analogRead(analogInPin_1);  
    sensorValue_2 = analogRead(analogInPin_2);
    sensorValue_3 = analogRead(analogInPin_3); 
             
    // map it to the range of the analog out:
    //outputValue = map(sensorValue, 0, 1023, 0, 255);  
    // change the analog out value:
    //analogWrite(analogOutPin, outputValue);           
  
    // print the results to the serial monitor:
    Serial.print( F("sensor1 = ") );                       
    Serial.println(sensorValue_1);   
    Serial.print( F("sensor2 = ") );                       
    Serial.println(sensorValue_2); 
    Serial.print( F("sensor3 = ") );                       
    Serial.println(sensorValue_3);
    Serial.println();    
    //Serial.print( F("\t output = ") );      
    //Serial.println(outputValue);   

    //ready to wait for next read and show
    analog_millis = millis();
  }
}

//*****************************************************//
//****                                             ****//
//****       Endstops and Z-probe                  ****//
//****                                             ****//
//*****************************************************//

void Endstops() { 
  static unsigned long endstop_millis = 0;
  static unsigned long endstop_interval = 500;
  if ( millis() - endstop_millis >  endstop_interval )  { // if its time to show status
    Serial.println( F("Endstops") );
    ShowEndstopsHL();  //show logic level
    ShowEndstops10();  //show on/off style
    Serial.println();

    //ready to wait for next show
    endstop_millis = millis();
  }
  EndstopsDebugLED();
}

void EndstopsDebugLED() {     
  bool EndsDebugLedOn = 0;
  if( !digitalRead(X_MIN_PIN) ) EndsDebugLedOn = 1;
  if( !digitalRead(X_MAX_PIN) ) EndsDebugLedOn = 1;
  if( !digitalRead(Y_MIN_PIN) ) EndsDebugLedOn = 1;
  if( !digitalRead(Y_MAX_PIN) ) EndsDebugLedOn = 1;
  if( !digitalRead(Z_MIN_PIN) ) EndsDebugLedOn = 1;
  if( !digitalRead(Z_MAX_PIN) ) EndsDebugLedOn = 1;
  if( !digitalRead(Z_PROBE_PIN) ) EndsDebugLedOn = 1;

  if( !PauseEndStopBlink ) {
    if( (EndsDebugLedOn == 1)  ) { //endstop LED indication is paused during the three blinks of DebugLED
      digitalWrite(DebugLed_pin, HIGH);   // set the LED on
    }else{
      digitalWrite(DebugLed_pin, LOW);   // set the LED ooff
    }
  }
}

void ShowEndstopsHL() {     
  if( digitalRead(X_MIN_PIN) ) Serial.print("H"); else Serial.print("L");
  if( digitalRead(X_MAX_PIN) ) Serial.print("H"); else Serial.print("L");
  Serial.print(" ");
  if( digitalRead(Y_MIN_PIN) ) Serial.print("H"); else Serial.print("L");
  if( digitalRead(Y_MAX_PIN) ) Serial.print("H"); else Serial.print("L");
  Serial.print(" ");
  if( digitalRead(Z_MIN_PIN) ) Serial.print("H"); else Serial.print("L");
  if( digitalRead(Z_MAX_PIN) ) Serial.print("H"); else Serial.print("L");
  Serial.print("-");
  if( digitalRead(Z_PROBE_PIN) ) Serial.println("H"); else Serial.println("L");
}

void ShowEndstops10() {     
  if( digitalRead(X_MIN_PIN) ) Serial.print("0"); else Serial.print("1");
  if( digitalRead(X_MAX_PIN) ) Serial.print("0"); else Serial.print("1");
  Serial.print(" ");
  if( digitalRead(Y_MIN_PIN) ) Serial.print("0"); else Serial.print("1");
  if( digitalRead(Y_MAX_PIN) ) Serial.print("0"); else Serial.print("1");
  Serial.print(" ");
  if( digitalRead(Z_MIN_PIN) ) Serial.print("0"); else Serial.print("1");
  if( digitalRead(Z_MAX_PIN) ) Serial.print("0"); else Serial.print("1");
  Serial.print("-");
  if( digitalRead(Z_PROBE_PIN) ) Serial.println("0"); else Serial.println("1");
}

//*****************************************************//
//****                                             ****//
//****       Blink and stuff                       ****//
//****                                             ****//
//*****************************************************//


void Blink(int blink_pin) 
{ 
  static unsigned long blink_millis = 0;
  static unsigned long blink_interval = 0;
  static boolean do_on = true;
  static int on_delay = 100;    //change this value to adjust the number of MilliSeconds the LED is ON
  static int off_delay = 100;   //change this value to adjust the number of MilliSeconds the LED is OFF
  
  if ( millis() - blink_millis >  blink_interval )  { // if its time to change the blink
    if (do_on) { //use a flag to determine wether to turn on or off the Blink LED
      digitalWrite(blink_pin, HIGH);   // set the LED on, if okay to use power for it
      blink_millis = millis();
      blink_interval = on_delay; // wait for a second
      do_on = false;
    }else{
      digitalWrite(blink_pin, LOW);    // set the LED off
      // set the time to do next blink 
      blink_millis = millis();
      blink_interval = off_delay;  // wait for a second
      do_on = true;
    } 
  }
}


void blinkN(byte bl){
  _blinks = bl;
}

void blinkN(byte major, byte minor){
  _blinks = major;
  _blink_minor = minor; 
}


void blinkN() {
  static unsigned long blinkN_millis = 0;
  static unsigned long blinkN_interval = 0;
  static boolean do_N_on = true;
  static int idx = 0;
  if(_blinks > 0) { // still do a blink session 
    if ( millis() - blinkN_millis >  blinkN_interval )  { // 
      if(do_N_on) { //use a flag to determine wether to turn on or off the Blink LED
        digitalWrite(blinkN_pin, HIGH);   // set the LED on, if okay to use power for it
        blinkN_millis = millis();
        blinkN_interval = blinkN_on_delay; // wait for a second
        do_N_on = false;
      }else{
        digitalWrite(blinkN_pin, LOW);    // set the LED off
        // set the time to do next blink 
        blinkN_millis = millis();
        blinkN_interval = blinkN_off_delay;  // wait for a second
        do_N_on = true;
        _blinks--;
        if(_blinks == 0) {
          blinkN_interval = blinkN_long_off_delay; // a longer pause is necessary before doing next blink session
          //next blink session will be; 
          if (_blink_minor) {
            _blinks = _blink_minor;
            _blink_minor = 0; 
          }
        }
      } 
    }
  }else{ // no more blink sessions
    // do next blink  
    switch (idx){
      case 0:
        blinkN_pin = 9; 
        _blinks = 3;
        PauseEndStopBlink = false;
        idx++; 
        break;
       case 1:
        blinkN_pin = 10;
        _blinks = 3;
        idx++; 
        break;
       case 2:
        blinkN_pin = 11;
        _blinks = 3; 
        idx++; 
        break;
       case 3:
        blinkN_pin = 8;
        _blinks = 3;
        idx++; 
        break;
       case 4:
        blinkN_pin = 12;
        _blinks = 3;
        idx++; 
        break;
       case 5:
        blinkN_pin = 13;
        _blinks = 3;
        PauseEndStopBlink = true;
        idx = 0; 
        break;
    }
    Serial.print( F("blinking pin ") );
    Serial.println(blinkN_pin );
     
  }
}

//*****************************************************//
//****                                             ****//
//****       Stepper driver stuff                  ****//
//****                                             ****//
//*****************************************************//

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
} // OneStepAllPins
