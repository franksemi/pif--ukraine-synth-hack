
#include <SPI.h>

const int csPin = 10;
int mapped_A0_input;
int number = 0; // can be used in switch case of final code

void setup() {

  SPI.begin();
  SPI.setBitOrder(MSBFIRST); // From Data Sheet
  pinMode(csPin,OUTPUT);
  digitalWrite(csPin, HIGH);
  Serial.begin(9600);
  Serial.println(number); // start somewhere
}

void loop() {
    mapped_A0_input = map(analogRead(A0), 0, 1023, 0, 1023);
    if (number != mapped_A0_input)
    if (number < mapped_A0_input) number ++;
    else number --;
    delay(100);
    digitalPotWrite(0,mapped_A0_input);
    Serial.println(number);
    delay(100);
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



