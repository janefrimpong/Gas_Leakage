#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Define the pin connections
const int mq2Pin = A0; // Analog input pin connected to MQ-2 sensor
const int buzzerPin = 8; // Digital output pin connected to the buzzer

// Define the threshold value for gas detection
const int thresholdValue = 500; // You may need to adjust this value based on your sensor and environment

// Initialize the LCD with the I2C address
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the address if necessary

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set the buzzer pin and LCD as outputs
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight(); // Turn on the backlight
  
  // Display initial message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Gas Detector");
  lcd.setCursor(0, 1);
  lcd.print("Ready");
}

void loop() {
  // Read the analog value from the MQ-2 sensor
  int sensorValue = analogRead(mq2Pin);

  // Print the sensor value for debugging
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // Check if the sensor value exceeds the threshold
  if (sensorValue > thresholdValue) {
    // If gas is detected, turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Gas Detected! Buzzer On");
    
    // Display message on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Gas Detected!");
    lcd.setCursor(0, 1);
    lcd.print("Ventilate area");
  } else {
    // Otherwise, turn off the buzzer
    digitalWrite(buzzerPin, LOW);
    
    // Clear the LCD
    lcd.clear();
    
    // Display default message
    lcd.setCursor(0, 0);
    lcd.print("Gas Detector");
    lcd.setCursor(0, 1);
    lcd.print("Ready");
  }

  // Add a delay before the next reading
  delay(1000);
}
