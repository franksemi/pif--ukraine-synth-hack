

#include <SPI.h>
#include "SSD1306.h"

#define SDA_PIN 5
#define SCL_PIN 4

SSD1306  display(0x3c, SDA_PIN, SCL_PIN);


const int csPin = 10;
int mapped_A0_input;
int number = 0; // can be used in switch case of final code


void setup() {
    SPI.begin();
    SPI.setBitOrder(MSBFIRST); // From Data Sheet
    pinMode(csPin,OUTPUT);
    digitalWrite(csPin, HIGH);
    Serial.begin(115200);
    Serial.println(number); // start somewhere
    display.init();
    display.flipScreenVertically();
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.display();
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


void oled_writenumbers() {
    display.drawString(0, 18, "A0 in:");
    display.drawString(66, 18, String(analogRead(A0)));
    }


void loop() {
    mapped_A0_input = map(analogRead(A0), 0, 1023, 0, 1023);
    if (number != mapped_A0_input)
    if (number < mapped_A0_input) number ++;
    else number --;
    delay(50);
    digitalPotWrite(0,mapped_A0_input);
    Serial.println(number);
    display.clear();
    oled_writenumbers();
    display.display();
    delay(50);
    }
