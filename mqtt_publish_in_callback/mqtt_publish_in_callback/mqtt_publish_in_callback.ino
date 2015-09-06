/*
 Publishing in the callback 
 
  - connects to UBINTEL MQTT server
  - subscribes to the channel "Heat"
  - when a message is received, republishes it to "led"
  

  
*/

#include <SPI.h>
#include <Ethernet.h>
#include <LibUbintel.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
byte ip[]     = { 192, 168, 1, 125 };

// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

EthernetClient ethClient;
char device_id[] = "53d7edbf10ec01351d11ef0f";
char secret[] = "3f1c3b18-748e-400c-b6c1-a4992ec1d2ca";
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
  client.publish("Heat", "25"); 
  Serial.println("published");
  // Free the memory
  free(p);
}

void setup()
{
  Serial.begin(19200); 
  Serial.println("Connecting.....");
  Ethernet.begin(mac, ip);
  int i = client.connect();
  Serial.println(i);
  if (i) {
    Serial.println("Connected");
    client.publish("Heat","30");
    Serial.println("Published");
    client.subscribe("led",callback);
}
}

void loop()
{
  client.loop();
}

