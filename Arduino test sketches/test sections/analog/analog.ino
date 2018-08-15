/* This sketch will read three analog pins and display their values on the serial port
 *  
 *  MrAlvin 2018
 * 
 */


//***** Analog Read and Serial Out example, but without the use of delay() *****
const int analogInPin_1 = A5;  // Analog input pin that the potentiometer is attached to
const int analogInPin_2 = A6;  // Analog input pin that the potentiometer is attached to
const int analogInPin_3 = A7;  // Analog input pin that the potentiometer is attached to

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  Serial.println( F("Hello World!") );
}

void loop() {
  // put your main code here, to run repeatedly:
  AnalogRead_and_SerialOut_example();
}


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
