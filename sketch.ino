#include "DHT.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// SCL and SDA pins should be: D1 and D2 (NodeMCU)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int BUTTONPIN = 13;
 
#define DHT_PIN 12
#define DHT_TYPE DHT22

DHT dht = DHT(DHT_PIN, DHT_TYPE);

bool isDown = false;
void setup() {
    Serial.begin(115200);
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay(); 
    pinMode(BUTTONPIN, INPUT_PULLUP);
    dht.begin();
}

void loop() {
  
    isDown = true;
    
    float temperature = dht.readTemperature(),
          humidity = dht.readHumidity();

    display.setFont(&FreeSans9pt7b);
    display.clearDisplay();
    display.drawLine(64, 0, 64, 64, WHITE);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 30);
    display.println(String(temperature));
    display.setCursor(20, 55);
    display.println("C");
    
    display.setCursor(76, 30);
    display.println(String(humidity));
    display.setCursor(91, 55);
    display.println("%");
    display.display();

    Serial.print(String(temperature) + "°C | " + String(humidity) + "% \n");
    delay(100);
}
