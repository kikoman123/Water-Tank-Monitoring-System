#define TRIG 11 //Module pins
#define ECHO 12
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
#define buzzer 7

DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

 
void setup() {
  //buzzer
  pinMode(buzzer, OUTPUT);
  //temp
  sensors.begin();
// LCD code
  lcd.begin();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
//Ultrasonic sensor
Serial.begin(9600); // Serial monitoring
pinMode(TRIG, OUTPUT); // Initializing Trigger Output and Echo Input
pinMode(ECHO, INPUT_PULLUP);
}
 float cel=sensors.getTempCByIndex(0);
float fahr= (sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0;




void loop() {
 

  sensors.requestTemperatures();

digitalWrite(TRIG, LOW); // Set the trigger pin to low for 2uS
delayMicroseconds(2);
 
digitalWrite(TRIG, HIGH); // Send a 10uS high to trigger ranging
delayMicroseconds(20);
 
digitalWrite(TRIG, LOW); // Send pin low again
int distance = pulseIn(ECHO, HIGH,26000); // Read in times pulse
 
distance= distance/58; //Convert the pulse duration to distance
//You can add other math functions to calibrate it well
int lowDist= distance;                    ///Distance
if(distance>=18){
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("Distance: ");
lcd.setCursor(0, 1);
lcd.print(distance);
lcd.print(" cm");

delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(0, 1);
  lcd.print(cel);

  lcd.print(" C/ ");
  lcd.print(fahr);
  lcd.print("F");

  lcd.print("F");
  delay(1000);
  
          //buzzer at this distance
      
if(lowDist<40&&lowDist>=1){

  digitalWrite(buzzer,HIGH);
 
}
else{
  digitalWrite(buzzer,LOW);
}



}


}
