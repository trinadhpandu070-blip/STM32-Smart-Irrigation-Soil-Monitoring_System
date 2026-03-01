#include <LiquidCrystal.h>
const int rs =PC14, en =PC15, d4 =PA0, d5 =PA1, d6 =PA2, d7 =PA3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int mot=PB7;
int cnt=0;
int x=0;
int pos = 0;  
int t,h;
int md=0;
int ms=PA5;
int ldr=PA6;
#include "DHT.h"
#define DHTPIN PB8
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
lcd.begin (16,2);
lcd.setCursor(4,0);
lcd.print("WELCOME");
lcd.setCursor(0,1);
lcd.print("SMART AGRICULTURE:");
delay(2000);
lcd.clear();

Serial.begin(9600);
dht.begin();
pinMode(ms,INPUT);
pinMode(ldr,INPUT);
pinMode(mot,OUTPUT);


 
}
void loop() {
  cnt++;
int h = dht.readHumidity();
int t = dht.readTemperature();
int mval=1023-analogRead(ms)/4;
int lval=1023-analogRead(ldr)/4;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("T:");
lcd.setCursor(2,0);
lcd.print(t);
lcd.setCursor(5,0);
lcd.print("H:");
lcd.setCursor(7,0);
lcd.print(h);
lcd.setCursor(0,1);
lcd.print("M:");
lcd.setCursor(2,1);
lcd.print(mval);
lcd.setCursor(7,1);
lcd.print("L:");
lcd.setCursor(10,1);
lcd.print(lval);
delay(1000);
if (Serial.available()){
  int x=Serial.read();
  if (x=='1'){
    lcd.setCursor(11,0);
    lcd.print("AUTO");
    md=0;
  }
   if (x=='2'){
      lcd.setCursor(11,0);
    lcd.print("MANU");
     digitalWrite(mot,0);
    md=1;
  }
   if (x=='3'){
    digitalWrite(mot,1);
    
  }
  if (x=='4'){
    digitalWrite(mot,0);
    
  }
}
if (md==0){
  
if( mval>400)
{
   digitalWrite(mot,0);
  
 
  }
else
{
  digitalWrite(mot,1);
 
}
}

Serial.println("temp:"+String(t)+" hum:"+String(h) + " lig:"+String(lval)+" mos:"+String(mval));
delay(1000);
}