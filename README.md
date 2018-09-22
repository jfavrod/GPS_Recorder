GPS Recorder
============
Firmware for the Arduino Uno to read GPS data from the Ublox NEO 6M GPS
module and record it to an SD Card (formatted to the FAT filing system).

Records latitude, longitude, and timestamp (in universal coordinated
time, UTC) in CSV format to a file named `DATA.CSV`.


Dependencies
------------
* SoftwareSerial - https://www.arduino.cc/en/Tutorial/SoftwareSerial
* TinyGPS - https://github.com/mikalhart/TinyGPS


Usage
-----
Clone this repo, then using the Arduino IDE make sure SoftwareSerial
is available in your programming environment. If it's not add the
library to the IDE. Then add TinyGPS by downloading the library from
the link above, then including the library in the Arduino IDE.

To include the TinyGPS library, from the top bar menu on the IDE go to
<b>Sketch > Include Library > Add .ZIP Library...</b> and select on the
TinyGPS repository.

Once the IDE has the dependencies, simply open the code from
`GPS_Recorder.ino` in the IDE and upload it to a connected Uno.


### Chip Select
The chip select for the SD card shild used in the code is pin 10. If
the chip select differs on your device, edit the following line.

```
if (!SD.begin(10)) {
```

And use your chip select instead of `(10)`.


### Coms
SoftwareSerial is configured to receive on digital pin 2 and transmit
on digital pin 3. If your GPS module is not connected to the Uno with
receive on digital pin 2 and transmit on digital pin 3 edit the
following line of the code.

```
SoftwareSerial mySerial(3,4);
```

Instead of `(3,4)`, in the first position set the value of your receive
pin +1 and in the second position set the value of your transmit pin +1.

For more information see my [blog post](https://jasonfavrod.com/recording-and-replaying-gps-data).
