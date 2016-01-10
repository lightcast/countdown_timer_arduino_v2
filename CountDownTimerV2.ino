// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
 
#include <Wire.h>
#include "RTClib.h"

 
// Use the softwareserial library to create a new "soft" serial port
// for the display. This prevents display corruption when uploading code.
#include <SoftwareSerial.h>

RTC_DS1307 RTC;

int days = 0;
int hours = 0; // start hours
int minutes = 0; //start min
int seconds = 0; //start seconds
long currentTime = 0; 
long goalTime = 0; //1455446006; 
long oneYear = 3075840; //number of seconds from 1/9/16 -> 12/31/16
char colon = ':';
boolean  exitLoop = false;
// Attach the serial display's RX line to digital pin 2
SoftwareSerial mySerial(3,2); // pin 2 = TX, pin 3 = RX (unused)
 
void setup () {
    //Serial.begin(57600);
     pinMode(A2, OUTPUT); digitalWrite(A2, LOW);
     pinMode(A3, OUTPUT); digitalWrite(A3, HIGH);
    
    Wire.begin();
    RTC.begin();
    if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));
    }
   


  DateTime now = RTC.now();
  currentTime = now.unixtime();
  goalTime = currentTime + oneYear;
  
  Serial.begin(9600);
  mySerial.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);

  mySerial.write("                "); // clear display
  mySerial.write("                ");

  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
 
  mySerial.write("Year CountUp    ");
  delay(150);  //wait a bit
}
 
void loop () {
  DateTime now = RTC.now();
    days = now.day();
    hours = now.hour();
    minutes = now.minute();
    seconds = now.second();
    
    if(goalTime > now.unixtime()){
      String strDays = (days < 10) ? "0" + String(days, DEC) : String(days, DEC);
      String strHours = (hours < 10) ? "0" + String(hours, DEC) : String(hours, DEC); 
      String strMinutes = (minutes < 10) ? "0" + String(minutes, DEC) : String(minutes, DEC);
      String strSeconds = (seconds < 10) ? "0" + String(seconds, DEC) : String(seconds, DEC);
      //Serial.print(strSeconds);
      String results = String(strDays + colon + strHours + colon + strMinutes + colon + strSeconds);
      //Serial.println(results);
      mySerial.write(254); // move cursor to beginning of first line
      mySerial.write(128);
     
      mySerial.write("Year Count Up   ");
      mySerial.print(results);
    delay(1000);
  }
  else
  {
      mySerial.write(254); // move cursor to beginning of first line
      mySerial.write(128);
      mySerial.write("                "); // clear display
      mySerial.write("                ");
      mySerial.write("Tawain CountDown");
      mySerial.write("Done!!!");
      while(1); // wait forever
  
  }    
}
