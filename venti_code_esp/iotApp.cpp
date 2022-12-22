#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <aREST.h>
const char* ssid = "admin";
const char* password = "12345678";
// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.145.223";
// Initializes the espClient
WiFiClient espClient;
PubSubClient client(espClient);
// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
 
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
 
  Serial.println();
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
   
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
      client.subscribe("esp82664");
     // client.subscribe("esp8266/5");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(15000);
    }
  }
}
void iotparameters() {
  float ipPressure = 100;
  float opPressure = 200;
  float ipBPM = 300;
  float ipTidalVol = 12.2;
  float opTidalVol = 13.3;
  float motorVolt = 14.4;
  float motorCurr = 15.5;
  float motorSpeedinrpm = 16.6;
  float motorStep = 85;
  float motorAccel =25;
  float ambuCompressionin_percentage = 75;
  float flowrate = 25;
  float compTime = 20;
  float decomTime = 25;
    // Check if any reads failed and exit early (to try again).
    //if (isnan(ipPressure) || isnan(opPressure) || isnan(ipBPM) || isnan(ipTidalVol) || isnan(opTidalVol) || isnan(motorVolt) || isnan(motorCurr) || isnan(motorSpeedinrpm) || isnan(motorStep) || isnan(motorAccel) || isnan(ambuCompressionin_percentage) || isnan(flowrate) || isnan(compTime) || isnan(decomTime) ) {
     // Serial.println("Failed to read from sensor!");
     // return;
    //}
    static char InputPressure[7];
    dtostrf(ipPressure, 6, 2, InputPressure);
   
    static char OutputPressure[7];
    dtostrf(opPressure, 6, 2, OutputPressure);
    static char InputBPM[7];
    dtostrf(ipBPM, 6, 2, InputBPM);
    static char InputTidalVol[7];
    dtostrf(ipTidalVol, 6, 2, InputTidalVol);
    static char OutputTidalVol[7];
    dtostrf(opTidalVol, 6, 2, OutputTidalVol);
    static char MotorVoltage[7];
    dtostrf(motorVolt, 6, 2, MotorVoltage);
    static char MotorCurrent[7];
    dtostrf(motorCurr, 6, 2, MotorCurrent);
    static char MotorSpeedinrpm[7];
    dtostrf(motorSpeedinrpm, 6, 2, MotorSpeedinrpm);
    static char MotorStep[7];
    dtostrf(motorStep, 6, 2, MotorStep);
    static char MotorAccel[7];
    dtostrf(motorAccel, 6, 2, MotorAccel);
    static char AmbuCompressionin_percentage[7];
    dtostrf(ambuCompressionin_percentage, 6, 2, AmbuCompressionin_percentage);
    static char Flowrate[7];
    dtostrf(flowrate, 6, 2, Flowrate);
    static char CompressionTime[7];
    dtostrf(compTime, 6, 2, CompressionTime);
    static char DecompressionTime[7];
    dtostrf(compTime, 6, 2, DecompressionTime);  
    // Publishes  values
    client.publish("/esp82664/ipPressure", InputPressure);
    client.publish("/esp82664/opPressure", OutputPressure);
    client.publish("/esp82664/ipBPM", InputBPM);
    client.publish("/esp82664/ipTidalVol", InputTidalVol);
    client.publish("/esp82664/opTidalVol", OutputTidalVol );
    client.publish("/esp82664/motorVolt", MotorVoltage);
    client.publish("/esp82664/motorCurr", MotorCurrent);
    client.publish("/esp82664/motorSpeedinrpm", MotorSpeedinrpm);
    client.publish("/esp82664/motorStep", MotorStep);
    client.publish("/esp82664/motorAccel", MotorAccel);
    client.publish("/esp82664/ambuCompressionin_percentage", AmbuCompressionin_percentage);
    client.publish("/esp82664/flowrate", Flowrate);
    client.publish("/esp82664/compTime", CompressionTime);
    client.publish("/esp82664/decomTime", DecompressionTime );
   
    Serial.print("InputPressure(cmH2o): ");
    Serial.print(ipPressure);
    Serial.print("\nOutputPressure(CmH2o): ");
    Serial.print(opPressure);
    Serial.print("\nInputBPM(number):  ");
    Serial.print(ipBPM);
    Serial.print("\nInputTidalVol(ml):  ");
    Serial.print(ipTidalVol);
    Serial.print("\nOutputTidalVol(ml):  ");
    Serial.print(opTidalVol);
    Serial.print("\nMotorVoltage(volts):  ");
    Serial.print(motorVolt);
    Serial.print("\nMotorCurrent(Amps):  ");
    Serial.print(motorCurr);
    Serial.print("\nMotorSpeedinrpm:  ");
    Serial.print(motorSpeedinrpm);
    Serial.print("\nMotorStep(Number):  ");
    Serial.print(motorStep);
    Serial.print("\nMotorAccel:  ");
    Serial.print(motorAccel);
    Serial.print("\nAmbuCompressionin_percentage:  ");
    Serial.print(ambuCompressionin_percentage);
    Serial.print("\nFlowrate(ml/sec):  ");
    Serial.print(flowrate);
    Serial.print("\nCompressionTime(msec):  ");
    Serial.print(compTime);
    Serial.print("\nDecompressionTime(msec):  ");
    Serial.print(decomTime);
}
// void setup() 
// {
//   Serial.begin(115200);
//   setup_wifi();
//   client.setServer(mqtt_server, 1883);
//   client.setCallback(callback);
// }
// void loop() {
//   if (!client.connected()) {
//     reconnect();
//   }
//   if(!client.loop())
//     client.connect("ESP8266Client");
   
//   now = millis();
//     if (now - lastMeasure > 10000) {
//     lastMeasure = now;
//     iotparameters();
//     }
// }