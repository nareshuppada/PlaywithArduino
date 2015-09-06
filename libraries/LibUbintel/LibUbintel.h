/*
 UbMqtt.h - A simple interface to ubintel mqtt gateway.
 This utility uses PubSubClient in the background.
 Author : Naresh Uppada
 email : naresh.uppada@ubintel.com
*/

#ifndef LibUbintel_h
#define LibUbintel_h

#include <PubSubClient.h>

typedef struct {
	char* device_id;
	char* secret;
}UB_Device_t;

typedef struct {
	char ch_id[2];
	char ch_name[25];
	char ch_value[5];
}UB_Device_Channel_t;


typedef struct {
	char topic[100];
}UB_mqtt_topic_t;

typedef struct{
	char message[100];
	char topic[50];
	char qos[5];
}UB_mqtt_message_t;



class LibUbintel {


private:
	PubSubClient mqttClient;
	UB_Device_t device_details;

public:
LibUbintel(Client& client,char* device_id,char* secret);
   boolean connect();
   void disconnect();
   boolean publish(char *channel_name, char *payload);
   boolean subscribe(char *topic,void(*)(char*,uint8_t*,unsigned int));
   boolean loop();
   boolean connected();
};




#endif
