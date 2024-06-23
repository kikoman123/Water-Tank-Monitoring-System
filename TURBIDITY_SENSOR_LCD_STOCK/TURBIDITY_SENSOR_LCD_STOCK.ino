#include <Wire.h> 
#include <LiquidCrystal_I2C.h>    //https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define buzzer 7
int sensorPin = A0;                                                                                                                                       
float volt;
float ntu;
 
void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
}
 
void loop()
{
    
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
    if(ntu>=1400&&ntu<=1800){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tubidity: ");
    lcd.print("Fair");
 
    lcd.setCursor(0,1);
    lcd.print(ntu);
    lcd.print(" NTU");
    delay(1000);
    }
   else if(ntu>1801){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tubidity: ");
    lcd.print("Muddy");
 
    lcd.setCursor(0,1);
    lcd.print(ntu);
    lcd.print(" NTU");
    delay(1000);
    }
     
     else{
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tubidity: ");
    lcd.print("Great");
 
    lcd.setCursor(0,1);
    lcd.print(ntu);
    lcd.print(" NTU");
    delay(1000);
    }
   if(ntu>1800){ 
  for(int j=0; j<=2;j++){

    tone(buzzer, 1000);
    delay(200);
    noTone(buzzer);
    delay(100);

  }
};
    }
    

 
float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}