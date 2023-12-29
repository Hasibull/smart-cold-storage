#include <MQ2.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "dht.h"
#define dht_apin 2
 
dht DHT;

// Necessary variables
const int Analog_Input = A0;
int lpg, co, smoke;
//----------------------------------------

// Instantiating the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
//----------------------------------------

// Instantiating MQ2
MQ2 mq2(Analog_Input);
//----------------------------------------

void setup() {
  
  // initialize the LCD and Serial monitor
  lcd.begin();
  Serial.begin(9600);
  
  // Turn on the LCD blacklight
  lcd.backlight();
  mq2.begin();
}


void loop() {

  // Reading from MQ2
  lpg = mq2.readLPG();

  // Reading from MQ135
  int airQuality = analogRead(A3);
  
  // Instantiating DHT11
  DHT.read11(dht_apin);

  // Printing on LCD
  lcd.setCursor(0,0);
  lcd.print("Hu:");
  lcd.print(DHT.humidity);
  lcd.print(" T:");
  lcd.print(DHT.temperature);
  lcd.setCursor(0,1);
  lcd.print("CO2:");
  lcd.print(airQuality);
  //----------------------------------------


  // Sending data to NodeMcu
  
  Serial.print(DHT.temperature);
  Serial.print("T");
  Serial.print(DHT.humidity);
  Serial.print("H");
  Serial.print(lpg);
  Serial.print("L");
  Serial.print(airQuality);
  Serial.print("C");
  
  delay(3000);
  
}
