#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPIN 2
#define DHTTYPE DHT22       // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT sensor for normal 16mhz Arduino
#define BUTTONPIN 7
#define NUMDELAYS 30        // 30 delays x 100 ms = 3 seconds, because the DHT22
                            // updates only every ~2 seconds
#define DELAYTIME 100       // 100 ms for delay
// Relay
#define IN4 12

// Set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int button, delays, relayState;
float hum, temp;

void setup() {
    lcd.begin();
    lcd.backlight();
    dht.begin();

    // Pushbutton
    pinMode(BUTTONPIN, INPUT);

    // Relay
    pinMode(IN4, OUTPUT);
    digitalWrite(IN4, LOW);

    delays = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature & ");
    lcd.setCursor(0, 1);
    lcd.print("Humidity - v0.2");

    Serial.begin(9600);
}

void loop() {
    button = digitalRead(BUTTONPIN);

    if (button == LOW) {
        lcd.backlight();
    } else {
        lcd.noBacklight();
    }

    if(delays >= NUMDELAYS){
        delays = 0;
        // Read data and store it to variables hum and temp
        hum = dht.readHumidity();
        temp = dht.readTemperature();

        lcd.clear();
        lcd.print("Temp:         C ");
        lcd.setCursor(7, 0);
        lcd.print(temp);
        lcd.setCursor(0, 1);
        lcd.print("Vlaga:        % ");
        lcd.setCursor(7, 1);
        lcd.print(hum);

        relayState = digitalRead(IN4);

        if( (hum > 70.0 || hum < 30.0 ) && (relayState == LOW) ) {
            digitalWrite(IN4, HIGH);
        } else if ( (hum <= 70.0 && hum >= 30.0 ) && (relayState == HIGH) ) {
            digitalWrite(IN4, LOW);
        }
    }
    delay(DELAYTIME);
    if(delays < NUMDELAYS){
        delays++;
    }
}
