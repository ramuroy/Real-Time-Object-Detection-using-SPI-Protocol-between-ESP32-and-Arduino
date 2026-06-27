#include <SPI.h>

// ESP32 SPI master: on each new IR detection, send one timestamped message
// to the Arduino slave over SPI.

// Define custom pins
#define SS_PIN 5             // Chip Select pin for SPI
#define IR_SENSOR_PIN 35     // IR sensor pin
#define MOSI_PIN 33          // SPI MOSI pin
#define MISO_PIN 25          // SPI MISO pin
#define SCK_PIN 26           // SPI Clock pin
#define LED_PIN 27           // LED to indicate object detection

// An AVR slave reliably receives well below F_CPU/4 (4 MHz on a 16 MHz Uno);
// 1 MHz, MSB-first, mode 0 leaves comfortable margin for the slave's ISR.
static const SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE0);

int lastIrState = HIGH;      // IR idle reads HIGH; an object pulls it LOW

void setup() {
  Serial.begin(115200);

  // Initialize SPI communication
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);

  pinMode(SS_PIN, OUTPUT);       // Set SS as output
  pinMode(IR_SENSOR_PIN, INPUT); // IR sensor as input
  pinMode(LED_PIN, OUTPUT);      // LED as output

  digitalWrite(SS_PIN, HIGH);    // Disable slave initially
  digitalWrite(LED_PIN, LOW);    // Turn off LED at start
}

// Send a newline-terminated message to the slave inside one SPI transaction.
void sendMessage(const char *msg) {
  SPI.beginTransaction(spiSettings);
  digitalWrite(SS_PIN, LOW);     // select the slave
  for (const char *p = msg; *p != '\0'; ++p) {
    SPI.transfer(*p);
  }
  SPI.transfer('\n');            // end-of-message marker
  digitalWrite(SS_PIN, HIGH);    // deselect the slave
  SPI.endTransaction();
}

void loop() {
  int irState = digitalRead(IR_SENSOR_PIN);

  // Edge-trigger: act only on the HIGH->LOW transition (object newly
  // detected) so one detection sends exactly one message, instead of
  // re-sending ~10x/second while the object sits in front of the sensor.
  if (irState == LOW && lastIrState == HIGH) {
    digitalWrite(LED_PIN, HIGH);

    char msg[48];
    snprintf(msg, sizeof(msg), "Object Detected at %lu sec", millis() / 1000);
    sendMessage(msg);

    Serial.print("Sent: ");
    Serial.println(msg);
  } else if (irState == HIGH) {
    digitalWrite(LED_PIN, LOW);  // turn LED off once the object is gone
  }

  lastIrState = irState;
  delay(50);  // simple debounce / poll interval
}
