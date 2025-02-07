#include <Wire.h>
#define SENSOR_PIN A2
#define SAMPLES 200          // Increase sample size
#define CALIBRATION_FACTOR 1.293
#define VREF 5.0             // Set correct reference voltage

void setup() {
  Serial.begin(115200);
}

float getRMSVoltage() {
  float sum = 0;

  for (int i = 0; i < SAMPLES; i++) {
    int rawValue = analogRead(SENSOR_PIN);
    float voltage = (rawValue * VREF) / 1023.0; // Convert ADC to voltage
    sum += voltage * voltage;  // Square values for RMS
    delayMicroseconds(500);    // Short delay to capture AC waveform properly
  }

  float rmsVoltage = sqrt(sum / SAMPLES);  // Compute RMS
  return rmsVoltage * CALIBRATION_FACTOR;  // Apply calibration factor
}

void loop() {
  float voltage = getRMSVoltage();
  Serial.print("Voltage: ");
  if(voltage>2.5){
  Serial.println(voltage*65.79);
  }
  else
   Serial.println(voltage);
  delay(500);  // Slow down readings for better observation
}
