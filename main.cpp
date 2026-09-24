#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 9
#define OLED_CS 10
#define OLED_RST 8

Adafruit_SSD1306 display(
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	OLED_MOSI,
	OLED_CLK,
	OLED_DC,
	OLED_RST,
	OLED_CS
);

Adafruit_BMP280 bme;
float temperature;
float altitude;
float pressure;

unsigned long currentTime;



void setup(){
  Serial.begin(9600);
  Serial.println("Program Started");
  Wire.begin();
  Serial.println("I2C Started");

  if(bme.begin(0x76))
  {
	  Serial.println("BME280 Found at 0x76");
  } else if(bme.begin(0x77)){
    Serial.println("BME280 Found at 0x77");
  }
  else {
    Serial.println("BME220 Not Found");
  }

  display.begin(
    SSD1306_SWITCHCAPVCC
  );

// Clear Display
display.clearDisplay();
// Set Text Size
display.setTextSize(1);
// Set Text Color
display.setTextColor(SSD1306_WHITE);
// Update Display
display.display();
}

void loop(){
  // measuring the temperature with BMP sensor
  temperature = bme.readTemperature();
  Serial.print("Temperature:");
  Serial.print(temperature);
  Serial.println(" C");
  delay(1000);

 // measuring the altitude with BMP Sensor
  altitude = bme.readAltitude(1013.25);
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  pressure = bme.readPressure();
  Serial.print("Pressure: ");
  Serial.print(pressure/100);
  Serial.println(" hPa");

  // Clear the display
  display.clearDisplay();

  // Read the temperature from the BME280 sensor
  bme.readTemperature();
  // Read the humidity from the BME280 sensor
  bme.readAltitude();
  // Read the atmospheric pressure from the BME280 sensor
  bme.readPressure();
  // Clear the OLED display
  display.clearDisplay();
  // Move the cursor to the top of the display
  display.setCursor(0,0);
  // Display the label "Temp: "
  display.print("Temp: ");
  // Display the temperature value
  display.print(temperature);
  // Display the temperature unit
  display.println(" C");
  // Display the label "Alt: "
  display.print("Alt: ");
  // Display the alt value
  display.print(altitude);
  //Display the alt unit
  display.println(" m");
  // Display the label "Pres: "
  display.print("Pres: ");
  // Display the pressure value
  display.print(pressure);
  // Display the pressure unit
  display.println(" hPa");
  // Update the OLED display
  display.display();
  // Wait one second
  delay(1000);

  //calculate time
  currentTime = millis()/1000;
  Serial.println(currentTime);
}
