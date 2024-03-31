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

 
int sensorPin = A0;                                                                                                                                       
float volt;
float ntu;
 
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

//tubidity sensor

    volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(sensorPin)/1023)*5*2.41;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2); 
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
    }
 
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

delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(0, 1);
  lcd.print(cel);

  lcd.print(" C/ ");
  lcd.print(fahr);
  lcd.print("F");

  lcd.print("F");
  delay(2000);
  if(ntu>=1200&&ntu<=1800){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tubidity: ");
    lcd.print("Fair");
 
    lcd.setCursor(0,1);
    lcd.print(ntu);
    lcd.print(" NTU");
    delay(2000);
    }
   else if(ntu>1801){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tubidity: ");
    lcd.print("Muddy");
 
    lcd.setCursor(0,1);
    lcd.print(ntu);
    lcd.print(" NTU");
    delay(2000);
    }
     
     else{
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tubidity: ");
    lcd.print("CLear");
 
    lcd.setCursor(0,1);
    lcd.print(ntu);
    lcd.print(" NTU");
    delay(2000);
    }
   
    
  
          //buzzer at this distance
      
if(lowDist<40&&lowDist>=1){

  digitalWrite(buzzer,HIGH);
 
}
else{
  digitalWrite(buzzer,LOW);
}



}


}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
