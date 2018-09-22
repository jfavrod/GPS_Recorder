/**
 * @author Jason Favrod <mail@jasonfavrod.com>
 * @version 1.0.0
 */
 
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

SoftwareSerial mySerial(3,4);
TinyGPS gps;
File myFile;
void gpsdump(TinyGPS &gps);


void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);

  while (!Serial) {
    ;
  }

  Serial.print("initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while(1);
  }

  Serial.println("initialization done.\n");

  delay(1000);
  Serial.println("uBlox Neo 6M");
  Serial.print("TinyGPS library v. ");
  Serial.println(TinyGPS::library_version());
  Serial.print("loaded size: "); 
  Serial.println(sizeof(TinyGPS));
  Serial.println();
}


void loop()
{
  bool newdata = false;
  unsigned long start = millis();

  while (millis() - start < 5000) 
  {
    if (mySerial.available()) 
    {
      char c = mySerial.read();

      if (gps.encode(c)) 
        newdata = true;
    }
  }

  if (newdata)
    gpsdump(gps);
  else
    Serial.println("No Data");
}

void gpsdump(TinyGPS &gps)
{
  float lat, lon;
  unsigned long age, date, time, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  String record = "";

  gps.f_get_position(&lat, &lon, &age);
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);

  record = String(record + String(lat, 6));
  record = String(record + ",");
  
  record = String(record + String(lon, 6));
  record = String(record + ",");

  record = String(record + year);
  record = String(record + "-");

  if (month < 10) record = String(record + "0");
  record = String(record + static_cast<int>(month));
  record = String(record + "-");

  if (day < 10) record = String(record + "0");
  record = String(record + static_cast<int>(day));
  record = String(record + "T");
  
  if (hour < 10) record = String(record + "0");
  record = String(record + static_cast<int>(hour));
  record = String(record + ":");
  
  if (minute < 10) record = String(record + "0");
  record = String(record + static_cast<int>(minute));
  record = String(record + ":");
  
  if (second < 10) record = String(record + "0");
  record = String(record + static_cast<int>(second));
  record = (record + "Z");

  Serial.println(record);
  myFile = SD.open("data.csv", FILE_WRITE);
  
  if (myFile) {
    myFile.println(record);
    myFile.close();
  }
  else
    Serial.println(" error opening data file!");
}
