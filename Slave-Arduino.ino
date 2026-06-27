#include <SPI.h>

// Arduino Uno SPI slave: receives a newline-terminated message from the
// ESP32 master and prints it to the Serial Monitor.
//
// An AVR has no clock of its own in slave mode, so it must service each
// incoming byte from the SPI Transfer Complete interrupt (SPI_STC_vect) —
// polling digitalRead(SS) + SPI.transfer() (a *master* call) drops bytes.

#define SS_PIN 10          // Uno hardware SS; must stay INPUT for slave mode
#define BUF_SIZE 64

volatile char    receivedData[BUF_SIZE];
volatile uint8_t idx = 0;
volatile bool    messageReady = false;

void setup() {
  Serial.begin(115200);

  pinMode(SS_PIN, INPUT);   // SS as input keeps the SPI hardware in slave mode
  pinMode(MISO, OUTPUT);    // MISO is the only line a slave drives

  SPCR |= _BV(SPE);         // Enable SPI in slave mode (MSTR stays clear)
  SPCR |= _BV(SPIE);        // Enable the SPI Transfer Complete interrupt
}

// Fires once per byte clocked in by the master.
ISR(SPI_STC_vect) {
  char c = SPDR;            // read the just-received byte

  if (messageReady) return; // hold the last message until loop() consumes it

  if (c == '\n') {          // end of message
    receivedData[idx] = '\0';
    messageReady = true;
    idx = 0;
  } else if (idx < BUF_SIZE - 1) {
    receivedData[idx++] = c;
  }
  // else: buffer full without a newline — drop extra bytes instead of
  // overflowing, and wait for the terminating '\n' to reset.
}

void loop() {
  if (messageReady) {
    Serial.print("Received: ");
    Serial.println((const char *)receivedData);
    messageReady = false;   // re-arm for the next message
  }
}
