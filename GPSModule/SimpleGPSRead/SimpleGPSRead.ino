#include <SoftwareSerial.h>

SoftwareSerial GpsMod = SoftwareSerial(2,3);

void setup()
{
GpsMod.begin(9600);
Serial.begin(9600);
}

 void loop()
{
  char a = GpsMod.read();
 //if(a=='$')
 //Serial.println();
  //else
Serial.print(char(a));
}
