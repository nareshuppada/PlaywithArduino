#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

//Sensor Types

int temperature_sensor=1,pir_sensor=2,humidity_sensor=3,ldr_sensor=4,pulse_sensor=5,proximity_sensor=6;

char currWord[20]; // Stores current word recieved.

char stype[20];
char sid[10];
char iport[10];
char oport[10];
char inData[20];

void setup(){
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
 // lcd.print("Hello, Naresh!");
  lcd.print("Temperature :");
  Serial.begin(9600);
  //handshake
 while(1){
    delay(500);
    Serial.write("power up");
    if(Comp("<<>>")==0){
    Serial.write("<<>>");
    break;
    }
 
 
 }
}

char * floatToString(char * outstr, double val, byte precision, byte widthp){
  char temp[16];
  byte i;

  // compute the rounding factor and fractional multiplier
  double roundingFactor = 0.5;
  unsigned long mult = 1;
  for (i = 0; i < precision; i++)
  {
    roundingFactor /= 10.0;
    mult *= 10;
  }
  
  temp[0]='\0';
  outstr[0]='\0';

  if(val < 0.0){
    strcpy(outstr,"-\0");
    val = -val;
  }

  val += roundingFactor;

  strcat(outstr, itoa(int(val),temp,10));  //prints the int part
  if( precision > 0) {
    strcat(outstr, ".\0"); // print the decimal point
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
      mult *=10;

    if(val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;

    while(frac1 /= 10)
      padding--;

    while(padding--)
      strcat(outstr,"0\0");

    strcat(outstr,itoa(frac,temp,10));
  }

  // generate space padding 
  if ((widthp != 0)&&(widthp >= strlen(outstr))){
    byte J=0;
    J = widthp - strlen(outstr);
    
    for (i=0; i< J; i++) {
      temp[i] = ' ';
    }

    temp[i++] = '\0';
    strcat(temp,outstr);
    strcpy(outstr,temp);
  }
  
  return outstr;
}

//function to compare Serial data with Strings.
char Comp(char* This){
  int index=0;
  char inChar;
 // >>:stype:1#sid:5#iport:1#oport:0#<<
  char inData[20]={'\0'};
 while(Serial.available() > 0) // Don't read unless
   // there you know there is data
 {
   if(index < 20) // One less than the size of the array
   {
     inChar = Serial.read(); // Read a character
   //  Serial.write(inChar);
     inData[index] = inChar; // Store it
     index++; // Increment where to write next
     inData[index] = '\0'; // Null terminate the string
   }
 }
 Serial.write(inData);
 if(strcmp(inData,This)  == 0){
   for(int i=0;i<19;i++){
     inData[i]=0;
   }
   index=0;
   
   return(0);        

 }
 else{
   return(1);


 }
}



 char* readTemperature(int inputPin){
    char data[20];
    //pinMode(inputPin, INPUT);     // declare sensor as input
    double temp = analogRead(1);
    floatToString(data, temp*0.49 , 2, 0);
  lcd.setCursor(0, 1);
  lcd.print(data);
    //Serial.write(temp);
   //lcd.print(data);
    return data;
  }
  
 char* readPIR(int inputPin){
    char data[20];
    pinMode(inputPin, INPUT);     // declare sensor as input
    
     sprintf(data, "%.4g", digitalRead(inputPin));
  return data;
 
  }
  
 int readHumidity(int inputPin){
    pinMode(inputPin, INPUT);     // declare sensor as input
    int voltage = analogRead(inputPin)*0.49;
    return voltage;  
  }
 
 float readLightSensor(int inputPin){
    pinMode(inputPin, INPUT);     // declare sensor as input
    int voltage = analogRead(inputPin)*0.49;
    return voltage;  
  }
  
  float readProximitySensor(int inputAnalogPin,int echoDigitalPin){
     pinMode(inputAnalogPin, INPUT);     // declare sensor as input
     pinMode(echoDigitalPin, OUTPUT);     // declare pin as output
    
  }
  
  

  
void recieveWord(char d){
  int inChar;
  int index=0;
  strcpy(currWord,"");
while(Serial.available() > 0) // Don't read unless
   // there you know there is data
 {
   if(index < 20) // One less than the size of the array
   {
     inChar = Serial.read(); // Read a character
     if(inChar==d) break;
     currWord[index] = inChar; // Store it
     index++; // Increment where to write next
     currWord[index] = '\0'; // Null terminate the string
   }
 }
 Serial.write(currWord);
}

void parseNpopulate(){
  delay(100);
  recieveWord(':');
  
  if(strcmp(currWord,"stype")==0){
   recieveWord('#');
   strcpy(stype,currWord);
  }
  recieveWord(':');
  if(strcmp(currWord,"sid")==0){
   recieveWord('#');
   strcpy(sid,currWord);
  }
  
  recieveWord(':');
  if(strcmp(currWord,"iport")==0){
   recieveWord('#');
   strcpy(iport,currWord);
  }
  
  recieveWord(':');
  if(strcmp(currWord,"oport")==0){
   recieveWord('#');
   strcpy(oport,currWord);
  }
  
  if(Comp("<<")==0){
  return;
  }
 
}
  


void loop(){
  //check if ready to recieve
  strcpy(stype,"0");
  strcpy(sid,"0");
  strcpy(iport,"100");
  strcpy(oport,"100");
  while(1){
    delay(200);
   // Serial.write("waiting");
  if(Comp(">>")==0){
    Serial.write("<<");
    break;
  }
  }
  
  while(1){
     delay(200);
    //  Serial.write("reading");
     recieveWord(':');
  if(strcmp(currWord,">>")==0){
    Serial.write("begin Parsing"); //remove
   parseNpopulate();
   
  if(strcmp(stype,"1")==0){ 
        Serial.write("reading temperature port");
        Serial.print(atoi(iport));
        Serial.write(strcat(strcat(">>",readTemperature(atoi(iport))),"<<"));
        break;
      }
     else if (strcmp(stype,"2")==0){
        Serial.write(strcat(strcat(">>",readPIR(atoi(iport))),"<<"));
        break;
     }
     else if (strcmp(stype,"3")==0){
        Serial.write(">><<");
     }
     else if (strcmp(stype,"4")==0){
        Serial.write(">><<");
     }
     else if (strcmp(stype,"5")==0){
        Serial.write(">><<");
     }
    
   
  }
  
  }
 
}
