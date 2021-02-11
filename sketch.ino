#include "DHT.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int BUTTONPIN = 13;

#define DHT_PIN 12
#define DHT_TYPE DHT22

DHT dht = DHT(DHT_PIN, DHT_TYPE);

bool isDown = false;

void setup() {
    
    Serial.begin(9600);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay(); 
    
    Serial.print("hello");
    pinMode(BUTTONPIN, INPUT_PULLUP);
    dht.begin();
}

void loop() {
    int buttonState = digitalRead(BUTTONPIN);
    
    if (buttonState == HIGH && isDown == false) {
        isDown = true;

        float temperature = dht.readTemperature(),
              humidity = dht.readHumidity();

        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        display.println("TEMPERATURE: " + String(temperature));
        display.setCursor(0, 30);
        display.println("HUMIDITY: " + String(humidity) + " %");
        display.display();

        Serial.print(String(temperature) + "°C | " + String(humidity) + "% \n");
    }
    else if (buttonState == LOW && isDown == true){
        isDown = false;
    }
}
