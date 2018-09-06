/*
  Listfiles

 This example shows how print out the filenames in a
 directory on a SD card

 The circuit:
 * SD card attached to SPI bus as follows:
 *          Uno        Mega          DUE          ICSP 
 ** MOSI - pin 11  -  pin  51  -   icsp 4 (D75) -   4
 ** MISO - pin 12  -  pin  50  -   icsp 1 (D74) -   1
 ** CLK  - pin 13  -  pin  52  -   icsp 3 (D76) -   3 
 ** CS   - pin 10  -  pin  53  -   pin 53 (52?)  
 * 
 * ICSP: 
 * 1 - MISO      ++   +Vcc - 2
 * 3 - CLK(SCK)  ++   MOSI - 4
 * 5 - Reset     ++   GND  - 6    
 * 

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 2 Feb 2014
 by Scott Fitzgerald
 modified for RAMPS 1.7 on 1 sept 2018
 by MrAlvin 
 

 This example code is in the public domain.
 This code uses hardware SPI.

 */
#include <SPI.h>
#include <SD.h>

File root;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");
}

void loop() {
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}



