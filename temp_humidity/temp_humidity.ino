#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPIN 2
#define DHTTYPE DHT22       // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT sensor for normal 16mhz Arduino
#define BUTTONPIN 7

// Set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int button, delays;
float hum, temp;

void setup() {
    lcd.begin();
    lcd.backlight();
    dht.begin();
    pinMode(BUTTONPIN, INPUT);

    delays = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura & ");
    lcd.setCursor(0, 1);
    lcd.print("Vlaga - v0.1");

    Serial.begin(9600);
}

void loop() {
    button = digitalRead(BUTTONPIN);

    if (button == LOW) {
        lcd.backlight();
    } else {
        lcd.noBacklight();
    }

    if(delays > 30){
        delays = 0;
        // Read data and store it to variables hum and temp
        hum = dht.readHumidity();
        temp = dht.readTemperature();

        /*/ Print temp and humidity values to serial monitor
        Serial.print("Humidity: ");
        Serial.print(hum);
        Serial.print(" %, Temp: ");
        Serial.print(temp);
        Serial.println(" Celsius");
        */

        lcd.clear();
        lcd.print("Temp:         C ");
        lcd.setCursor(7, 0);
        lcd.print(temp);
        lcd.setCursor(0, 1);
        lcd.print("Vlaga:        % ");
        lcd.setCursor(7, 1);
        lcd.print(hum);
    }
    delay(100);
    delays++;
}
