#define TRIG 11 //Module pins
#define ECHO 12
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

 
void setup() {
// LCD code
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
//Ultrasonic sensor
Serial.begin(9600); // Serial monitoring
pinMode(TRIG, OUTPUT); // Initializing Trigger Output and Echo Input
pinMode(ECHO, INPUT_PULLUP);
}
 
void loop() {
 
digitalWrite(TRIG, LOW); // Set the trigger pin to low for 2uS
delayMicroseconds(2);
 
digitalWrite(TRIG, HIGH); // Send a 10uS high to trigger ranging
delayMicroseconds(20);
 
digitalWrite(TRIG, LOW); // Send pin low again
int distance = pulseIn(ECHO, HIGH,26000); // Read in times pulse
 
distance= distance/58; //Convert the pulse duration to distance
//You can add other math functions to calibrate it well
if(distance>=18){
lcd.setCursor(0,0);
lcd.print("Distance: ");
lcd.print(distance);
lcd.print(" cm");
delay(1000);
lcd.clear();

}




}
