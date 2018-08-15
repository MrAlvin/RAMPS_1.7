/*
  Blink

  Turns a LED on for one second, then off for one second, repeatedly.
  MrAlvin (2018)


*/

//***** Blink n-times and optionally then blink m-times
byte _blinks = 3;
byte _blink_minor = 0;

int blinkN_pin = 13;    //the pin number that the LED is connected to
int blinkN_on_delay = 100;    //change this value to adjust the number of MilliSeconds the LED is ON
int blinkN_off_delay = 100;   //change this value to adjust the number of MilliSeconds the LED is OFF
int blinkN_long_off_delay = 400;

 
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 (Built-in LED) 
  pinMode(13, OUTPUT);

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

  Serial.begin(19200); // Initialize the serial
  Serial.println( F("Hello World!") );
  Serial.print( F("blinking pin ") );
  Serial.println(blinkN_pin );
}

// the loop function runs over and over again forever
void loop() {
  //Blink(13);
  //Blink(8);
  //Blink(9);
  //Blink(10);
  //Blink(11);
  //Blink(12);
  blinkN(); //blinks a mosfet three times, then moves to the next mosfet

}

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


//*****************************************************//
//****                                             ****//
//****       Blink and stuff                       ****//
//****                                             ****//
//*****************************************************//

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
        idx = 0; 
        break;
    }
    Serial.print( F("blinking pin ") );
    Serial.println(blinkN_pin );
     
  }
}
