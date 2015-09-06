#include<SoftwareSerial.h>

SoftwareSerial RFID(8,9); /* set up a software serial port with D8 as Rx and D9 as Tx */

int switch1State; // used to store the state of Switch 1
int switch2State; // used to store the state of Switch 2
int Relay1=0; // used to store the state of Relay 1
int Relay2=0; // used to store the state of Relay 2

void LED1On(){ // switch LED1 On
 digitalWrite(13,LOW);
}

void LED1Off(){ // switch LED1 Off
 digitalWrite(13,HIGH); 
}

void LED2On(){  // switch LED2 On
 digitalWrite(12,LOW);
}

void LED2Off(){ // switch LED2 Off
 digitalWrite(12,HIGH);
}

void BuzzerOff(){ // switch Buzzer Off
digitalWrite(5,LOW);
}

void BuzzerOn(){  // switch Buzzer On
 digitalWrite(5,HIGH); 
}

void Relay1Off(){ // switch Relay1 Off
 Relay1 =0;
 digitalWrite(7,LOW);
}

void Relay1On(){ //  switch Relay1 On
 Relay1=1;
 digitalWrite(7,HIGH);
}

void Relay2Off(){ // switch Relay2 Off
 Relay2 =0;
 digitalWrite(4,LOW);
}

void Relay2On(){ //  switch Relay2 On
 Relay2=1;
 digitalWrite(4,HIGH);
}


void setup(){
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(5,OUTPUT);
pinMode(7,OUTPUT);
pinMode(4,OUTPUT);

LED1Off();
LED2Off();
BuzzerOff();
Relay1Off();
Relay2Off();

Serial.begin(9600);
RFID.begin(9600);
}


void loop(){
 char c;
switch1State = digitalRead(2); // read switch 1 state
switch2State = digitalRead(3); // read switch 2 state

if(RFID.available()) // check if card is detected
{  
  BuzzerOn();
  LED1On();
  LED2On();
  c=RFID.read();
  Serial.println(c);
  delay(50);
}
else
{
  BuzzerOff();
  LED1Off();
  LED2Off();
}

if(switch1State==LOW)
{
  if(Relay1==0)
  Relay1On();
  else
  Relay1Off();
  delay(1000);
}

if(switch2State==LOW)
{
  if(Relay2==0)
  Relay2On();
  else
  Relay2Off();
  delay(1000);
}


}
