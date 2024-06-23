#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float Celsius = 0;
float Fahrenheit = 0;

void setup() {
  sensors.begin();
  lcd.begin();
  lcd.print("Room Temperature");
}

void loop() {
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);

  lcd.setCursor(0, 0);
  lcd.print(Celsius);
  lcd.print(" Celsius  ");
  lcd.setCursor(0, 1);
  lcd.print(Fahrenheit);
  lcd.println(" Fahrenheit ");

  delay(1000);

}
