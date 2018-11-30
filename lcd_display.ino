#include<LiquidCrystal.h>

const int AOUTpin=0;
const int DOUTpin=7;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int value;
float x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(AOUTpin,INPUT);
  pinMode(DOUTpin,INPUT);
  lcd.begin(16,2);
  lcd.print("Alcohol Level");

}

void detected()
{
  Serial.println("Above the value");
  lcd.print(" Drunk");
}

void loop() {
  // put your main code here, to run repeatedly:
  value=analogRead(AOUTpin);
  x=((value*0.21)/1023);
  
  Serial.println("Alcohol Level");
  Serial.println(value);
  Serial.println(x);
  lcd.setCursor(0,1);
  lcd.print(value);
  lcd.print("mg/L");
  delay(5000);
  if(x>0.06)
  {
  Serial.println("Above the value");
  lcd.print(" Drunk");
  delay(5000);
  }
  else
  {
    lcd.print(" Sober");
  }
}
