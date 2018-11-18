

#include <SPI.h>
#include "SSD1306.h"

#define SDA_PIN 5
#define SCL_PIN 4

SSD1306  display(0x3c, SDA_PIN, SCL_PIN);

const int csPin = 15;
int A0_input = 0;



void setup() {
    SPI.begin();
    SPI.setBitOrder(MSBFIRST); // From Data Sheet
    SPI.setDataMode(SPI_MODE1);
    pinMode(csPin,OUTPUT);
    Serial.begin(115200);
    display.init();
    display.flipScreenVertically();
    display.clear();
    display.setFont(ArialMT_Plain_10);
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

void oled_display() {
    display.drawString(0, 0, "A0 in:");
    display.drawString(10, 13, "Value:");
    display.drawString(42, 13, String(analogRead(A0)));
    display.drawString(21, 25, "Bin:"); 
    display.drawString(42, 25, String(analogRead(A0),BIN));
    display.drawString(18, 37, "Hex:"); 
    display.drawString(42, 37, String(analogRead(A0),HEX));
    display.drawString(20, 49, "Oct:"); 
    display.drawString(42, 49, String(analogRead(A0),OCT));
    }

void loop() {
    A0_input = map(analogRead(A0), 0, 1023, 0, 1023);
    delay(50);
    digitalPotWrite(0,A0_input);
    Serial.print("A0: - Analog read:");
    Serial.print(analogRead(A0));
    Serial.print("\t");
    Serial.print("Bin:");
    Serial.print(analogRead(A0),BIN);
    Serial.print("\t");
    Serial.print("\t");
    Serial.print("Hex:");
    Serial.print(analogRead(A0),HEX);
    Serial.print("\t");
    Serial.print("Oct:");
    Serial.print(analogRead(A0),OCT);
    Serial.print("\t");
    Serial.print("Dec:");
    Serial.println(analogRead(A0),DEC);   
    display.clear();
    oled_display();
    display.display();
    delay(50);
    }

