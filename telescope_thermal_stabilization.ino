//**************************************************************//
//  Name    : TELESCOPE THERMAL STABILIZATION
//  Author  : Mik™ <miksoft.pro> <miksoft.tm@gmail.com>
//  Version : 1.0.1 (24 Jan 2018)
//  Notes   : Telescope Thermal Stabilization Controller
//**************************************************************//

// LCD SCREEN TEMPLATE:
// ------------------
// |M:+22.4C° D:2.8 |
// |O:+19.6C° F:100%|
// ------------------
//  ^0        ^10  ^15

// Connecting Libraries
#include <OneWire.h>            // DS18B20 temperature sensor
#include <DallasTemperature.h>  // DS18B20 temperature sensor
#include <LiquidCrystal.h>      // 16x2 LCD

// --- /CONFIGURATION/ ---
#define DEBUG      // Debug mode (messages are displayed in a serial port)
#define PIN_TEMP 2 // PIN of temperature sensor
#define PIN_FAN  9 // PIN PWM for fan control
// --- /CONFIGURATION/ ---

OneWire oneWire(PIN_TEMP);
DallasTemperature sensors(&oneWire);

// Инициализируем объект-экран, передаём использованные
// для подключения контакты на Arduino в порядке:
// RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

float temp1, temp2, delta;

uint8_t degree[8] = {
  B01100,
  B10010,
  B10010,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000
};

// SETUP
void setup() {
  lcd.createChar(1, degree);

  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("TELESCOPE THERMAL STABILIZATION");
  #endif

  // DS18B20 library start
  sensors.begin();

  // LCD start
  lcd.begin(16, 2);
  lcd.print("   TERMO STAB   ");
  lcd.setCursor(0, 1);
  lcd.print("     V 1.0      ");

  delay(2000);

  display_clear();
} // void setup()

// Gets the temperature from the sensors
void get_temperature() {
  #ifdef DEBUG
    Serial.println("Requesting temperatures...");
  #endif
  sensors.requestTemperatures();
  #ifdef DEBUG
    Serial.println("DONE");
  #endif

  temp1 = sensors.getTempCByIndex(0);
  temp2 = sensors.getTempCByIndex(1);
  delta = abs(temp1 - temp2);
} // void get_temperature()

// Clears the display
void display_clear() {
  lcd.setCursor(0, 0);
  lcd.print("               ");
  lcd.setCursor(0, 1);
  lcd.print("               ");
} // void display_clear()

// MAIN LOOP
void loop() {
  get_temperature();

  // TEMP 1
  lcd.setCursor(0, 0);
  lcd.print("M");
  if (temp1 > 0) {
     lcd.print("+");
  }
  lcd.print(temp1, 1);
  lcd.print("\1  ");

  // TEMP 2
  lcd.setCursor(0, 1);
  lcd.print("M");
  if (temp2 > 0) {
     lcd.print("+");
  }
  lcd.print(temp2, 1);
  lcd.print("\1  ");

  // Delta
  lcd.setCursor(10, 0);
  lcd.print("D:");
  lcd.print(delta, 1);
  lcd.print("  ");

  // Calc fan speed
  float fratio;
  int fspeed;

  fratio = constrain(delta, 0, 5);
  fratio = map(fratio, 0, 5, 0, 255);
  fspeed = map(fratio, 0, 255, 0, 100);

  // Fan speed
  lcd.setCursor(10, 1);
  lcd.print("F:");
  lcd.print(fspeed);
  lcd.print("  ");

  analogWrite(PIN_FAN, fratio);

  #ifdef DEBUG
    Serial.print("Mirror temperature: ");
    Serial.print(temp1);
    Serial.println("C°");
    Serial.print("Outside temperature: ");
    Serial.print(temp2);
    Serial.println("C°");
    Serial.print("Temperature difference (ABS): ");
    Serial.print(delta);
    Serial.println("C°");
    Serial.print("Fan speed (%): ");
    Serial.println(fspeed);
    Serial.print("PWM signal: ");
    Serial.println(fratio);
    Serial.println(" ");
  #endif

  delay(1000);
}
