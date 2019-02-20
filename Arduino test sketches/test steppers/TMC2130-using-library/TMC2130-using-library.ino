/**
 * This sketch will (with default settings) test stepper Y on a RAMPS 1.7 board, 
 * by turning the stepper in alternating directions.
 *
 * You need the latest TMC2130 library from: https://github.com/teemuatlut/TMC2130Stepper
 * 
 * This sketch by MrAlvin, Jan 2019
 * Original sketch and library by Teemu Mäntykallio 
 *
 * 
 * 
 * Change the TEST_STEPPER value, to test the X,Y,Z,E0,E1 drivers the RAMPS 1.7 board
 */

#define TEST_STEPPER  2  // values can be 1 to 5 where: 1 => X, 2 => Y, 3 => Z, 4 => E0, 5 => E1
//#define REV_B
#define REV_C

/** 
 *  You need the latest TMC2130 library from: https://github.com/teemuatlut/TMC2130Stepper
 *  
 ***  Library Installation Guide ***
 *  
 *  Option A) 
 *       Use the Arduino IDE library manager (Sketch -> Include library -> Manage libraries...)
 *       Search for TMC2130Stepper 
 *       and then install.
 *       
 *  Option B)
 *       Download the zip file from Github ( https://github.com/teemuatlut/TMC2130Stepper )
 *       and extract it to: <arduino folder>/libraries
 *       and restart the IDE.
 *       
 *  Option C)
 *       goto to you arduino/libraries folder 
 *       and in command line: git clone https://github.com/teemuatlut/TMC2130Stepper.git
 */

#if TEST_STEPPER == 2  // Y
  #ifdef REV_B
    //         Ramps17-Y  // examples
    #define EN_PIN    58  // 38  // Nano v3:	16 Mega:	38	//enable (CFG6)
    #define DIR_PIN   63  // 55  //			19			55	//direction
    #define STEP_PIN  62  // 54  //			18			54	//step
    #define CS_PIN    42  // 40  //			17			64	//chip select
  #else
    #define EN_PIN    58  
    #define DIR_PIN   42  
    #define STEP_PIN  46  
    #define CS_PIN    63 
  #endif 
  char Step = 'Y';
#elif TEST_STEPPER == 1  // X
  #ifdef REV_B
    #define EN_PIN    55  
    #define DIR_PIN   57  
    #define STEP_PIN  56  
    #define CS_PIN    46  
  #else
    #define EN_PIN    55  
    #define DIR_PIN   57  
    #define STEP_PIN  56  
    #define CS_PIN    62
  #endif
  char Step = 'X';
#elif TEST_STEPPER == 3  // Z
  #ifdef REV_B
    #define EN_PIN    67  
    #define DIR_PIN   69  
    #define STEP_PIN  68  
    #define CS_PIN    48
  #else
    #define EN_PIN    67  
    #define DIR_PIN   69  
    #define STEP_PIN  68  
    #define CS_PIN    66
  #endif
  char Step = 'Z';
#elif TEST_STEPPER == 4  // E0
  #ifdef REV_B
    #define EN_PIN    30  
    #define DIR_PIN   36  
    #define STEP_PIN  34  
    #define CS_PIN    38
  #else
    #define EN_PIN    30  
    #define DIR_PIN   36  
    #define STEP_PIN  34  
    #define CS_PIN    64
  #endif
  char Step = '0';
#elif TEST_STEPPER == 5  // E1 
  #ifdef REV_B
    #define EN_PIN    22  
    #define DIR_PIN   26  
    #define STEP_PIN  24  
    #define CS_PIN     6
  #else
    #define EN_PIN    22  
    #define DIR_PIN   26  
    #define STEP_PIN  24  
    #define CS_PIN     6
  #endif
  char Step = '1';
#endif



bool dir = true;

#include <TMC2130Stepper.h>
TMC2130Stepper driver = TMC2130Stepper(EN_PIN, DIR_PIN, STEP_PIN, CS_PIN);

void setup() {
	Serial.begin(115200);
	while(!Serial);
	Serial.println("Start...");
  Serial.print("Testing driver: ");
  Serial.println(TEST_STEPPER);
  
	SPI.begin();
	pinMode(MISO, INPUT_PULLUP);
	driver.begin(); 			// Initiate pins and registeries
	driver.rms_current(300); 	// Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
	driver.stealthChop(1); 	// Enable extremely quiet stepping
	
	digitalWrite(EN_PIN, LOW);
}

void loop() {
	digitalWrite(STEP_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(STEP_PIN, LOW);
	delayMicroseconds(10);
	uint32_t ms = millis();
	static uint32_t last_time = 0;
	if ((ms - last_time) > 2000) {
		if (dir) {
			Serial.println("Dir -> 0");
			driver.shaft_dir(0);
		} else {
			Serial.println("Dir -> 1");
			driver.shaft_dir(1);
		}
		dir = !dir;
		last_time = ms;
	}
}
