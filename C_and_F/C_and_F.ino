#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
LiquidCrystal_I2C lcd(0x27, 16, 2);
DallasTemperature sensors(&oneWire);

void setup() {
  sensors.begin();
  Serial.begin(9600);
     lcd.init();
  lcd.backlight();

}




void loop() {
  
sensors.requestTemperatures(); 

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(0, 1);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.setCursor(7, 1);
  lcd.print("C");
  lcd.setCursor(9, 1);
  lcd.print( (sensors.getTempCByIndex(0)*9.0 )/5.0 + 32.0 );
  lcd.setCursor(16, 1);
  lcd.print("F");
  delay(1000);

}
