
// template


#include <SPI.h> 

const int csPin = 10;

void setup() {

 SPI.begin();
 SPI.setBitOrder(MSBFIRST); //We know this from the Data Sheet

 pinMode(csPin,OUTPUT);
 digitalWrite(csPin, HIGH);
}

void loop() {
 for(int i=0; i<1023; i++) { 
  digitalPotWrite(0,i);
  delay(10);
 } 
}

void digitalPotWrite(int address, int value) {
 digitalWrite(csPin, LOW); //select slave
 byte command = 0xB0; //0xB0 = 10110000 
 command += address; 
 SPI.transfer(command); 
 byte byte1 = (value >> 8);
 byte byte0 = (value & 0xFF); //0xFF = B11111111
 SPI.transfer(byte1);
 SPI.transfer(byte0);
 digitalWrite(csPin, HIGH); //de-select slave
}
