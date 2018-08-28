/*
 *  Testing  the Universal bi-directional LCD level converter adapter for connectors Aux-3+ and Aux4+
 * 
 *  Tests are: 
 *    - all output (default, or set by Y-min or Y-max
 *        You can use a LED (or multimeter) to see the outputs blink
 *    - all input (set by X-min or X-max)
 *       If you poull-down a pin (on the 5V side), then that pin ID will be shown  
 *       in the serial monitor. 
 *       It will also cause D13 LED (yellow on the RAMPS 1.7) to blink.
 *    
 */

// Aux-3 pins
#define SCK_PIN            76
#define MISO_PIN           74
#define D53_PIN            53
#define MOSI_PIN           75
#define D49_PIN            49

// Aux-4 pins
#define SDA20_PIN          20
#define SCL21_PIN          21
#define S1_TXO_16_PIN      16
#define S1_RXI_17_PIN      17
#define D23_PIN            23
#define D25_PIN            25
#define D27_PIN            27
#define D29_PIN            29
#define D31_PIN            31
#define D33_PIN            33
#define D35_PIN            35
#define D37_PIN            37
#define D39_PIN            39
#define D41_PIN            41
#define D43_PIN            43
#define D45_PIN            45
#define D47_PIN            47
#define D32_PIN            32


// End-stop pins
#define X_MIN_PIN           3
#define X_MAX_PIN           2
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19
#define Z_PROBE_PIN        64

//variables for aux-ports testing
int aux_test_type = 0;    // 0 = output, 1 = input
int aux_out_state = LOW;
bool do_blink = false;    // only write things to Serial port once in a while (like twice a second)

const int blink_pin = 13;       // the pin number that the debug LED is connected to




// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200); // Initialize the serial
  Serial.println( F("Hello World!") );

  pinMode(blink_pin, OUTPUT);

  // initialize end-stop pins 
  pinMode(X_MIN_PIN, INPUT_PULLUP);  
  pinMode(X_MAX_PIN, INPUT_PULLUP);  
  pinMode(Y_MIN_PIN, INPUT_PULLUP);  
  pinMode(Y_MAX_PIN, INPUT_PULLUP);  
  pinMode(Z_MIN_PIN, INPUT_PULLUP);  
  pinMode(Z_MAX_PIN, INPUT_PULLUP);  
  pinMode(Z_PROBE_PIN, INPUT_PULLUP); 

  // initialize Aux3+ and Aux4+ pins
  Set_Aux_as_output(); 
}



// the loop function runs over and over again forever
void loop() {
  Endstops();
  aux_ports();
}

void aux_ports(){
  static unsigned long aux_millis = 0;
  static unsigned long aux_interval = 500;
  if ( millis() - aux_millis >  aux_interval )  { // if its time to blink the output
    do_blink = true;
    
    //ready to wait for next show
    aux_millis = millis();
  }else{
    do_blink = false;
  }
    
  if( (aux_test_type == 0) && do_blink) {    // 0 = output, 1 = input
    
    //toggle all aux-pins twice a second 
    if(aux_out_state == LOW) {
      //now set them HIGH
      set_all_aux_HIGH();
      aux_out_state = HIGH;
    }else{ //aux_out_state == HIGH
      //now set them LOW
      set_all_aux_LOW();
      aux_out_state = LOW;
    }
    do_blink = false;
      
  }else if(aux_test_type == 1) {
    //read all aux pins
    read_all_aux_pins();
  }
} //aux_ports()

void Set_Aux_as_output() {
  //Aux-3
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MISO_PIN, OUTPUT);
  pinMode(D53_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(D49_PIN, OUTPUT);
  //Aux-4+
  pinMode(SDA20_PIN, OUTPUT);
  pinMode(SCL21_PIN, OUTPUT);
  pinMode(S1_TXO_16_PIN, OUTPUT);
  pinMode(S1_RXI_17_PIN, OUTPUT);
  pinMode(D23_PIN, OUTPUT);
  pinMode(D25_PIN, OUTPUT);
  pinMode(D27_PIN, OUTPUT);
  pinMode(D29_PIN, OUTPUT);
  pinMode(D31_PIN, OUTPUT);
  pinMode(D33_PIN, OUTPUT);
  pinMode(D35_PIN, OUTPUT);
  pinMode(D37_PIN, OUTPUT);
  pinMode(D39_PIN, OUTPUT);
  pinMode(D41_PIN, OUTPUT);
  pinMode(D43_PIN, OUTPUT);
  pinMode(D45_PIN, OUTPUT);
  pinMode(D47_PIN, OUTPUT);
  pinMode(D32_PIN, OUTPUT);
  Serial.println( F("Output mode is active") );
}

void Set_Aux_as_intput() {
  //Aux-3
  pinMode(SCK_PIN, INPUT_PULLUP);
  pinMode(MISO_PIN, INPUT_PULLUP);
  pinMode(D53_PIN, INPUT_PULLUP);
  pinMode(MOSI_PIN, INPUT_PULLUP);
  pinMode(D49_PIN, INPUT_PULLUP);
  //Aux-4+
  pinMode(SDA20_PIN, INPUT_PULLUP);
  pinMode(SCL21_PIN, INPUT_PULLUP);
  pinMode(S1_TXO_16_PIN, INPUT_PULLUP);
  pinMode(S1_RXI_17_PIN, INPUT_PULLUP);
  pinMode(D23_PIN, INPUT_PULLUP);
  pinMode(D25_PIN, INPUT_PULLUP);
  pinMode(D27_PIN, INPUT_PULLUP);
  pinMode(D29_PIN, INPUT_PULLUP);
  pinMode(D31_PIN, INPUT_PULLUP);
  pinMode(D33_PIN, INPUT_PULLUP);
  pinMode(D35_PIN, INPUT_PULLUP);
  pinMode(D37_PIN, INPUT_PULLUP);
  pinMode(D39_PIN, INPUT_PULLUP);
  pinMode(D41_PIN, INPUT_PULLUP);
  pinMode(D43_PIN, INPUT_PULLUP);
  pinMode(D45_PIN, INPUT_PULLUP);
  pinMode(D47_PIN, INPUT_PULLUP);
  pinMode(D32_PIN, INPUT_PULLUP);
  Serial.println( F("Input mode is active") );
}

void set_all_aux_HIGH() {
  //Aux-3
  digitalWrite(SCK_PIN, HIGH);
  digitalWrite(MISO_PIN, HIGH);
  digitalWrite(D53_PIN, HIGH);
  digitalWrite(MOSI_PIN, HIGH);
  digitalWrite(D49_PIN, HIGH);
  //Aux-4+
  digitalWrite(SDA20_PIN, HIGH);
  digitalWrite(SCL21_PIN, HIGH);
  digitalWrite(S1_TXO_16_PIN, HIGH);
  digitalWrite(S1_RXI_17_PIN, HIGH);
  digitalWrite(D23_PIN, HIGH);
  digitalWrite(D25_PIN, HIGH);
  digitalWrite(D27_PIN, HIGH);
  digitalWrite(D29_PIN, HIGH);
  digitalWrite(D31_PIN, HIGH);
  digitalWrite(D33_PIN, HIGH);
  digitalWrite(D35_PIN, HIGH);
  digitalWrite(D37_PIN, HIGH);
  digitalWrite(D39_PIN, HIGH);
  digitalWrite(D41_PIN, HIGH);
  digitalWrite(D43_PIN, HIGH);
  digitalWrite(D45_PIN, HIGH);
  digitalWrite(D47_PIN, HIGH);
  digitalWrite(D32_PIN, HIGH);
}

void set_all_aux_LOW() {
  //Aux-3
  digitalWrite(SCK_PIN, LOW);
  digitalWrite(MISO_PIN, LOW);
  digitalWrite(D53_PIN, LOW);
  digitalWrite(MOSI_PIN, LOW);
  digitalWrite(D49_PIN, LOW);
  //Aux-4+
  digitalWrite(SDA20_PIN, LOW);
  digitalWrite(SCL21_PIN, LOW);
  digitalWrite(S1_TXO_16_PIN, LOW);
  digitalWrite(S1_RXI_17_PIN, LOW);
  digitalWrite(D23_PIN, LOW);
  digitalWrite(D25_PIN, LOW);
  digitalWrite(D27_PIN, LOW);
  digitalWrite(D29_PIN, LOW);
  digitalWrite(D31_PIN, LOW);
  digitalWrite(D33_PIN, LOW);
  digitalWrite(D35_PIN, LOW);
  digitalWrite(D37_PIN, LOW);
  digitalWrite(D39_PIN, LOW);
  digitalWrite(D41_PIN, LOW);
  digitalWrite(D43_PIN, LOW);
  digitalWrite(D45_PIN, LOW);
  digitalWrite(D47_PIN, LOW);
  digitalWrite(D32_PIN, LOW);
}


void read_all_aux_pins(){
  int count = 0; 
  int in_pin = 0; 
   //Aux-3
  in_pin = digitalRead(SCK_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("SCK_PIN, ") );
    count++;
  }
  
  in_pin = digitalRead(MISO_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("MISO_PIN, ") );
    count++;
  }
  
  in_pin = digitalRead(D53_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D53_PIN, ") );
    count++;
  }
  
  in_pin = digitalRead(MOSI_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("MOSI_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D49_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D49_PIN, ") );
    count++;
  }
  
  //Aux-4+
  in_pin = digitalRead(SDA20_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("SDA20_PIN, ") );
    count++;
  }

  in_pin = digitalRead(SCL21_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("SCL21_PIN, ") );
    count++;
  }
  
  in_pin = digitalRead(S1_TXO_16_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("S1_TXO_16_PIN, ") );
    count++;
  }
  
  in_pin = digitalRead(S1_RXI_17_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("S1_RXI_17_PIN, ") );
    count++;
  }
  
  in_pin = digitalRead(D23_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D23_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D25_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D25_PIN, ") );
    count++;
  }
  
  in_pin = digitalRead(D27_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D27_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D29_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D29_PIN, ") );
    count++;
  }
  
  in_pin = digitalRead(D31_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D31_PIN, ") );
    count++;
  }
  
  in_pin = digitalRead(D33_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D33_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D35_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D35_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D37_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D37_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D39_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D39_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D41_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D41_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D43_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D43_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D45_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D45_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D47_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D47_PIN, ") );
    count++;
  }

  in_pin = digitalRead(D32_PIN);
  if(in_pin == LOW) {
    if (do_blink) Serial.print( F("D32_PIN, ") );
    count++;
  }  

  //if (do_blink) Serial.print( F("Count: ") ); Serial.println(count);
  if(count) digitalWrite(blink_pin, HIGH);  else digitalWrite(blink_pin, LOW);
  count = 0;
  
}


void Endstops() { 
  static unsigned long endstop_millis = 0;
  static unsigned long endstop_interval = 500;
  if ( millis() - endstop_millis >  endstop_interval )  { // if its time to show status
    Serial.println( F("Endstops") );
    EndstopsHL();  //show logic level
    Endstops10();  //show on/off style
    Serial.println();

    //update screen with AUX  mode
    if(aux_test_type == 0) Serial.println( F("Output mode is active") );
    else if (aux_test_type == 1) Serial.println( F("Input mode is active") );
    Serial.println();

    //ready to wait for next show
    endstop_millis = millis();
  }
}


void Set_test_type_0(){        //output mode
  if( !(aux_test_type == 0) ) { 
    aux_test_type = 0; 
    Set_Aux_as_output();
  }
}

void Set_test_type_1(){        //input mode
  if( !(aux_test_type == 1) ) { 
    aux_test_type = 1; 
    Set_Aux_as_intput();
  }
}


void EndstopsHL() {     
  if( digitalRead(X_MIN_PIN) ) Serial.print("H"); else { Serial.print("L"); Set_test_type_0(); }
  if( digitalRead(X_MAX_PIN) ) Serial.print("H"); else { Serial.print("L"); Set_test_type_0(); }
  Serial.print(" ");
  if( digitalRead(Y_MIN_PIN) ) Serial.print("H"); else { Serial.print("L"); Set_test_type_1(); }
  if( digitalRead(Y_MAX_PIN) ) Serial.print("H"); else { Serial.print("L"); Set_test_type_1(); }
  Serial.print(" ");
  if( digitalRead(Z_MIN_PIN) ) Serial.print("H"); else Serial.print("L");
  if( digitalRead(Z_MAX_PIN) ) Serial.print("H"); else Serial.print("L");
  Serial.print("-");
  if( digitalRead(Z_PROBE_PIN) ) Serial.println("H"); else Serial.println("L");
}

void Endstops10() {     
  if( digitalRead(X_MIN_PIN) ) Serial.print("0"); else { Serial.print("1"); Set_test_type_0(); }
  if( digitalRead(X_MAX_PIN) ) Serial.print("0"); else { Serial.print("1"); Set_test_type_0(); }
  Serial.print(" ");
  if( digitalRead(Y_MIN_PIN) ) Serial.print("0"); else { Serial.print("1");  Set_test_type_1(); }
  if( digitalRead(Y_MAX_PIN) ) Serial.print("0"); else { Serial.print("1");  Set_test_type_1(); }
  Serial.print(" ");
  if( digitalRead(Z_MIN_PIN) ) Serial.print("0"); else Serial.print("1");
  if( digitalRead(Z_MAX_PIN) ) Serial.print("0"); else Serial.print("1");
  Serial.print("-");
  if( digitalRead(Z_PROBE_PIN) ) Serial.println("0"); else Serial.println("1");
}


