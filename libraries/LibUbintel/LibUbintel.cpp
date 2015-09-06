/*
 UbMqtt.h - A simple interface to ubintel mqtt gateway.
 This utility uses PubSubClient in the background.
 Author : Naresh Uppada
 email : naresh.uppada@ubintel.com
*/

#include<libubintel.h>
   char UB_DOMAIN[] = "api.ubintel.com";
   int UB_PORT = 1883;
   LibUbintel::LibUbintel(Client& client,char* device_id, char* secret):mqttClient(UB_DOMAIN,UB_PORT,NULL,client){

	  // this->mqttClient = NULL;
	   //PubSubClient psclient("",1883,callback,client);
	   this->device_details.device_id = device_id;
	   this->device_details.secret = secret;
   }
   boolean LibUbintel::connect(){
	   return this->mqttClient.connect(this->device_details.device_id,this->device_details.device_id,this->device_details.secret);

   }
   void LibUbintel::disconnect(){
	   this->mqttClient.disconnect();
   }
   boolean LibUbintel::publish(char *channel_name, char *payload){
	   UB_mqtt_topic_t mqtt_publish_topic;
	   strcpy(mqtt_publish_topic.topic,"device/");
	   strcat(mqtt_publish_topic.topic,this->device_details.device_id);
	   strcat(mqtt_publish_topic.topic,"/");
	   strcat(mqtt_publish_topic.topic,channel_name);

	   return this->mqttClient.publish(mqtt_publish_topic.topic,payload);
   }
   boolean LibUbintel::subscribe(char *topic, void (*callback)(char *topic,uint8_t *payload,unsigned int len)){
	   this->mqttClient.callback = callback;
	   return this->mqttClient.subscribe(topic);
   }

   boolean LibUbintel::loop(){
	   return this->mqttClient.loop();

   }
   boolean LibUbintel::connected(){
	   return this->mqttClient.connected();

   }
