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

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
byte ip[]     = { 172, 16, 0, 100 };

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
  Serial.println("Connecting.....");
  Ethernet.begin(mac, ip);
  if (client.connect()) {
    Serial.println("Connected");
    client.publish("heat","30");
    client.subscribe("led",callback);
}
}

void loop()
{
  client.loop();
}

