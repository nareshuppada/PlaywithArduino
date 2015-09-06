#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("A");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("A");
  Serial.println("STARTED");
  mySerial.println("AT");
}

void loop() // run over and over
{
  
  ;
}
