//https://www.youtube.com/watch?v=vfBCvpeaAJk&list=PLUWZpHJMEu-Dv5Va5AmPeZH-E8-v9038u&index=137
//https://www.viralsciencecreativity.com/post/arduino-humidity-monitor-oled
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "DHT.h"

#define OLED_RESET -1
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);

char str[10];

void setup() {
  Serial.begin(9600);
  //initialize with the I2C addr 0x3C (128x64)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
  Serial.println("DHT11 test!");

  dht.begin();
  
  display.setTextColor(WHITE);
  display.setTextSize(2);
  displayStr(35, 10, "VIRAL");
  displayStr(25, 30, "SCIENCE");
  display.display();
}

void loop() {
  delay(1000);
  
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");

  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hic);
  Serial.println(" *F");

  // picture loop
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  displayStr( 0, 0, "Humidity:");
  displayStr( 80, 0, dtostrf(h, 5, 2, str));
  displayStr( 120, 0, "%");

  displayStr( 0, 14, "Temperature:");
  displayStr( 80, 14, dtostrf(t, 5, 2, str));
  displayStr( 120, 14, "C");

  displayStr( 80, 28, dtostrf(f, 5, 2, str));
  displayStr( 120, 28, "F");

  displayStr( 0, 42, "Heat index:");
  displayStr( 80, 42, dtostrf(hic, 5, 2, str));
  displayStr( 120, 42, "C");

  displayStr( 80, 56, dtostrf(hif, 5, 2, str));
  displayStr( 120, 56, "F");
  display.display();
}

void displayStr(int x, int y, char string[]) {
  display.setCursor(x, y); //oled display
  display.println(string);
}
