#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// LCD setup (I2C address 0x27 is common; use 0x3F if it doesn’t work)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT22 setup
#define DHTPIN 2          // DHT22 data pin connected to D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Buzzer pin
#define BUZZER 7          // Buzzer connected to D7

void setup() {
  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Initialize DHT22
  dht.begin();

  // Initialize buzzer pin
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW); // Ensure buzzer is OFF initially

  // Display static label
  lcd.setCursor(0, 0);
  lcd.print("Temp:     C");
  lcd.setCursor(0, 1);
  lcd.print("Humid:    %");
}

void loop() {
  // Read temperature and humidity
  float temp = dht.readTemperature();     // in Celsius
  float humid = dht.readHumidity();       // in percentage

  // Check for failed reads
  if (isnan(temp) || isnan(humid)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor error");
    delay(2000);
    return;
  }

  // Update LCD display
  lcd.setCursor(6, 0);
  lcd.print("     ");         // Clear previous value
  lcd.setCursor(6, 0);
  lcd.print(temp, 1);         // One decimal place

  lcd.setCursor(7, 1);
  lcd.print("     ");
  lcd.setCursor(7, 1);
  lcd.print(humid, 1);

  // Buzzer logic
  if (temp > 120.0) {
    digitalWrite(BUZZER, HIGH);  // Turn on buzzer
  } else {
    digitalWrite(BUZZER, LOW);   // Turn off buzzer
  }

  delay(1000);  // Delay 1 second
}
