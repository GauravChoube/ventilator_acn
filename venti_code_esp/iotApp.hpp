

// typedef enum
// {
//   MQTT_CONNECTED,
//   MQTT_DISCONNECTED

// }iotappreturnvalue;

void  setup_wifi();
int   sendIOTParameter(char *buffer);
int   mqttConnect();
int   keepAlive();
int isConnectedToWifi();


void  callback(String topic, byte* message, unsigned int length);

void reconnect();

void iotparameters();