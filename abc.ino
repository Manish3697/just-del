#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define SDA_PIN 21
#define SCL_PIN 22
#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;

uint32_t tsLastReport = 0;

// Callback when beat detected
void onBeatDetected() {
  Serial.println("Beat Detected!");
}

void setup() {
  Serial.begin(115200);

  // Start I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println("Initializing MAX30100...");

  if (!pox.begin()) {
    Serial.println("❌ Sensor FAILED");
    while (1);
  } else {
    Serial.println("✅ Sensor SUCCESS");
  }

  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  pox.update();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("❤️ Heart Rate: ");
    Serial.print(pox.getHeartRate());
    Serial.print(" BPM | SpO2: ");
    Serial.print(pox.getSpO2());
    Serial.println(" %");

    tsLastReport = millis();
  }
}