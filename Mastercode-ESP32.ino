#include <SPI.h>

// Define custom pins
#define SS_PIN 5            // Chip Select Pin for SPI
#define IR_SENSOR_PIN 35     // IR Sensor Pin
#define MOSI_PIN 33          // SPI MOSI pin
#define MISO_PIN 25          // SPI MISO pin
#define SCK_PIN 26           // SPI Clock pin
#define LED_PIN 27            // LED Pin to indicate object detection

void setup() {
  Serial.begin(115200);
  
  // Initialize SPI communication
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);
  
  pinMode(SS_PIN, OUTPUT);      // Set SS as output
  pinMode(IR_SENSOR_PIN, INPUT); // IR sensor as input
  pinMode(LED_PIN, OUTPUT);      // LED as output
  
  digitalWrite(SS_PIN, HIGH);   // Disable slave initially
  digitalWrite(LED_PIN, LOW);   // Turn off LED at start
}

void loop() {
  int irState = digitalRead(IR_SENSOR_PIN);  // Read IR sensor state

  if (irState == LOW) {  // Object detected
    digitalWrite(LED_PIN, HIGH);  // Turn LED ON

    unsigned long timestamp = millis() / 1000;  // Convert milliseconds to seconds
    String data = "Object Detected at " + String(timestamp) + " sec";

    // Start SPI communication
    digitalWrite(SS_PIN, LOW);  // Enable SPI communication
    for (int i = 0; i < data.length(); i++) {
      SPI.transfer(data[i]);  // Send each character
    }
    SPI.transfer('\n');  // End of message
    digitalWrite(SS_PIN, HIGH);  // Disable SPI communication

    // Show message in Serial Monitor
    Serial.println("Sent: " + data);
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn LED OFF if no object
  }

  delay(100);  // Small delay before checking again
}