#include <DHT.h>

#define DHTPIN 2       // DHT11 data pin connected to digital pin 2
#define DHTTYPE DHT11  // DHT 11 
#define BUZZER_PIN 8   // Buzzer connected to digital pin 8
#define RED_PIN 11      // Red LED pin
#define GREEN_PIN 10   // Green LED pin

DHT dht(DHTPIN, DHTTYPE);

// Upper thresholds
float upperTemperatureThreshold = 32.0; // Set your upper temperature threshold
float upperHumidityThreshold = 75.0;    // Set your upper humidity threshold

// Lower thresholds
float lowerTemperatureThreshold = 10.0; // Set your lower temperature threshold
float lowerHumidityThreshold = 30.0;    // Set your lower humidity threshold

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  digitalWrite(GREEN_PIN, HIGH);  // Start with green LED on
  digitalWrite(RED_PIN, LOW);     // Red LED off
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");

  if (h > upperHumidityThreshold || t > upperTemperatureThreshold || h < lowerHumidityThreshold || t < lowerTemperatureThreshold) {
    // Alert condition
    digitalWrite(RED_PIN, HIGH);   // Turn red LED on
    digitalWrite(GREEN_PIN, LOW);  // Turn green LED off
    tone(BUZZER_PIN, 1000);        // Sound the buzzer
    delay(500);                    // Wait for 500 ms
    noTone(BUZZER_PIN);            // Stop the buzzer
    delay(500);                    // Wait for 500 ms
  } else {
    // Normal condition
    digitalWrite(RED_PIN, LOW);    // Turn red LED off
    digitalWrite(GREEN_PIN, HIGH); // Turn green LED on
    noTone(BUZZER_PIN);            // Ensure buzzer is off
  }

  delay(2000); // Wait 2 seconds before the next loop
}
