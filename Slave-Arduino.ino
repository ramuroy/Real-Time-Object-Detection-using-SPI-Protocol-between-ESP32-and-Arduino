#include <SPI.h>

#define SS_PIN 10  

volatile boolean received = false;
char receivedData[50];  
int index = 0;

void setup() {
  Serial.begin(115200);  
  pinMode(SS_PIN, INPUT);  
  pinMode(MISO, OUTPUT);  

  SPCR |= _BV(SPE);  // Enable SPI in Slave Mode
}

void loop() {
  if (digitalRead(SS_PIN) == LOW) {  
    char c = SPI.transfer(0x00);  
    if (c == '\n') {
      received = true;
    } else {
      receivedData[index++] = c;
      receivedData[index] = '\0';
    }
  }

  if (received) {
    Serial.print("Received: ");
    Serial.println(receivedData);
    received = false;
    index = 0;
  }
}