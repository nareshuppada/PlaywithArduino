/*
 Publishing in the callback 
 
  - connects to UBINTEL MQTT server
  - subscribes to the channel "heat"
  - when a message is received, republishes it to "led"
  
  This example shows how to publish messages within the
  callback function. The callback function header needs to
  be declared before the PubSubClient constructor and the 
  actual callback defined afterwards.
  This ensures the client reference in the callback function
  is valid.
  
*/

#include <SPI.h>
#include <Ethernet.h>
#include <LibUbintel.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include "SWTFT.h" // Hardware-specific library


// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
byte ip[]     = { 54, 77, 15, 84 }; //[54.77.15.84
SWTFT tft;
int col=0;
// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

EthernetClient ethClient;
char device_id[25] = "";
char secret[25] = "";
LibUbintel client(ethClient,device_id,secret);

// Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  // In order to republish this payload, a copy must be made
  // as the orignal payload buffer will be overwritten whilst
  // constructing the PUBLISH packet.
  
  // Allocate the correct amount of memory for the payload copy
  byte* p = (byte*)malloc(length);
  // Copy the payload to the new buffer
  memcpy(p,payload,length);
  client.publish("led", "25"); 
  Serial.println("published");
  // Free the memory
  free(p);
}

void setup()
{
  Serial.begin(19200); 
   tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.fillScreen(BLACK);  //LCD BACKGROUND COLOR
  tft.setCursor(0, 30);
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  Serial.println("Connecting.....");
   tft.println("  Connecting to Ubintel..... ");
   
  
   
  Ethernet.begin(mac, ip);
  if (client.connect()) {
    tft.println("Connected");
    Serial.println("Connected");
    client.publish("heat","30");
    client.subscribe("led",callback);
}
}

void loop()
{
  client.loop();
}

