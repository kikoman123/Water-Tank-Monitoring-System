#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);
// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  
// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
void setup(void)
{
  
  Serial.begin(9600);
  sensors.begin();  
  lcd.begin();
  lcd.backlight();
}
void loop(void)
{ 
  sensors.requestTemperatures(); 
  lcd.setCursor(0,0);
  lcd.print("TEMP: ");
  lcd.print(sensors.getTempCByIndex(0));

  lcd.print(" C");
  delay(1000);
  lcd.clear();
}