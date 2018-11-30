import time
import urllib as url
import serial

ArduinoSerial=serial.Serial("/dev/ttyACM0",19200) //Port where Arduino is connected and the baud rate
time.sleep(2)

while True:
  s=ArduinoSerial.readline()
  print s
  temp=url.urlopen("https://api.thingspeak.com/update?api_key=AITK0MCOYQB0UXD2&field1="+str(s))
  time.sleep(15)
