#include<LiquidCrystal.h>
#include<SoftwareSerial.h>

int c=0;
const int AOUTpin=0;
const int DOUTpin=7;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial sim(9,10);

int value;
float x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  sim.begin(19200);
  pinMode(AOUTpin,INPUT);
  pinMode(DOUTpin,INPUT);
  lcd.begin(16,2);
  lcd.print("Alcohol Level");
  delay(100);

}

void sendMessage()
  {
    Serial.println("sending");
    sim.println("AT+CMGF=1");
    delay(1000);
    sim.println("AT+CMGS=\"+919938734697\"\r");
    delay(1000);
    sim.println("The driver is drunk");
    delay(1000);
    sim.println((char)26);
    delay(1000);
   sim.println("AT+SAPBR=3,1,"Contype","GPRS"");
//    delay(1000);
//    sim.println("AT+SAPBR=3,1,APN,bsnlnet");
//    delay(1000);
//    sim.println("AT+SAPBR =1,1");
//    delay(1000);
//    sim.println("AT+SAPBR =2,1");
//    delay(1000);
//    sim.println("AT+CIPGSMLOC=1,1");
//    delay(1000);
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
  lcd.print(x);
  lcd.print("mg/L");
  delay(5000);
  if(x>0.06)
  {
  if(Serial.read()=='a')
  {
    sendMessage();
  }
  Serial.println("Above the value");
  lcd.print(" Drunk");
  delay(5000);
  }
  else
  {
    Serial.println("Sober");
    lcd.print(" Sober");
  }
}
