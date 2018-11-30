#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
#include<TinyGPS.h>

const int AOUTpin=0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //rs=0 implies it will take instruction, 1 implies it will take data
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial sim(9,10); //9-RX pin of Arduino, 10- TX pin of Arduino
TinyGPS gps;

int value; //Variable to store data from the sensor
int c=1;
float x; //Actual value of alcohol in mg/L

void setup() {
 
  Serial.begin(19200); //19200 baud rate 
  sim.begin(19200);
  pinMode(AOUTpin,INPUT);
  
  lcd.begin(16,2);
  lcd.print("Alcohol Level:");
  delay(100);
  
}

void sendMessage()
  {
    float flat,flon; //variable for latitude and  longitude data
    unsigned long age; //time from the last fix was obtained in miliseconds
    gps.f_get_position(&flat,&flon,&age); //library function to get location
    sim.println("AT+CMGF=1"); //AT command to set it in text message sending mode
    delay(1000);
    sim.println("AT+CMGS=\"+918280079489\"\r");
    delay(1000);
    //sim.print("Name- Ajay, Veh No- OD07869, Alcohol level-");
    sim.print(x);
    sim.print("mg/l");
    sim.print("   http://maps.google.com/maps?q=loc:");
    sim.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    sim.print(",");
    sim.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(1000);
    sim.println((char)26);
    delay(1000);
}


void loop() {
  // Code to run repeatedly:
  value=analogRead(AOUTpin);
  x=((value*0.21)/1023);
  Serial.println(x);
  lcd.setCursor(0,1);
  lcd.print(x);
  lcd.print("mg/L");
  delay(3000);
  if(x>0.06)
  {
    lcd.print(" Drunk");
       if(c!=0)
         {
            c=0;
            sendMessage();
            delay(5000);
          }
  }
  else
  {
      lcd.print(" Sober");
  }
  
}
