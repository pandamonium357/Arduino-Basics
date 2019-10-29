/* DHT11 Interfacing by Flying Saucer
Huge thanks to  for the dht11 library to brainybits, please download and add the library to the code


 */



#include <dht.h>  // https://www.brainy-bits.com/wp-content/uploads/2017/12/DHT_Library.zip
#include <LiquidCrystal.h>

dht DHT; //object created

#define DHT11_PIN A1 //Analog Pin set to read DHT11 data



const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){

  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("TEMP & HUMIDITY");
  lcd.setCursor(0,2);
  lcd.print("SENSOR");
   delay(1000);
  
Serial.begin(9600);
Serial.println("Welcome to the Temperature and Humidty Sensor");
 
}

void loop(){


  
DHT.read11(DHT11_PIN);

//Serial monitor code included for testing, please remove it if you don't need it
Serial.println(" Humidity " );

Serial.println(DHT.humidity, 1);

Serial.println(" Temparature ");

Serial.println(DHT.temperature, 1);

Serial.println(""); 

lcd.clear();
  
    lcd.setCursor(0,0);
    lcd.print("TEMP: ");
    lcd.setCursor(6,0);
    lcd.print(DHT.temperature);
    lcd.setCursor(11,0);
    lcd.print((char)223);
    lcd.setCursor(12,0);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("HUMID: ");
    lcd.setCursor(6,1);
    lcd.print(DHT.humidity);
    lcd.setCursor(11,1);
    lcd.print("%");



  delay(1000);
}
