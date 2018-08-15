/*
 

*/

#define X_MIN_PIN           3
#define X_MAX_PIN           2
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19
#define Z_PROBE_PIN        64
 
// the setup function runs once when you press reset or power the board
void setup() {

// initialize end-stop pins 
  pinMode(X_MIN_PIN, INPUT_PULLUP);  
  pinMode(X_MAX_PIN, INPUT_PULLUP);  
  pinMode(Y_MIN_PIN, INPUT_PULLUP);  
  pinMode(Y_MAX_PIN, INPUT_PULLUP);  
  pinMode(Z_MIN_PIN, INPUT_PULLUP);  
  pinMode(Z_MAX_PIN, INPUT_PULLUP);  
  pinMode(Z_PROBE_PIN, INPUT_PULLUP); 

  Serial.begin(19200); // Initialize the serial
  Serial.println( F("Hello World!") );

}

// the loop function runs over and over again forever
void loop() {
  Endstops();
}

void Endstops() { 
  static unsigned long endstop_millis = 0;
  static unsigned long endstop_interval = 500;
  if ( millis() - endstop_millis >  endstop_interval )  { // if its time to show status
    Serial.println( F("Endstops") );
    EndstopsHL();  //show logic level
    Endstops10();  //show on/off style
    Serial.println();

    //ready to wait for next show
    endstop_millis = millis();
  }
}


void EndstopsHL() {     
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

void Endstops10() {     
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


