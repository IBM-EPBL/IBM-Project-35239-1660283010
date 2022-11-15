#include <WiFi.h>
#include <PubSubClient.h>
#include<Servo.h>

void callback(char* subscribetopic, byte* payload, unsigned int payloadLength); 

//-------credentials of IBM Accounts------

#define ORG "woaev0"//IBM ORGANITION ID
#define DEVICE_TYPE "abcde"//Device type mentioned in ibm watson IOT Platform
#define DEVICE_ID "112345"//Device ID mentioned in ibm watson IOT Platform
#define TOKEN "1a2b3c4d" 
String data3;
float d,d1,w;

Servo Myservo;
int pos;

#define trigpin    18
#define echopin    5

#define trigpin1 25
#define echopin1 33


char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char publishTopic[] = "iot-2/evt/Data/fmt/json";
char subscribetopic[] = "iot-2/cmd/display/fmt/String";
char authMethod[] = "use-token-auth";// authentication method
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;//client id


//-----------------------------------------
WiFiClient wifiClient; // creating the instance for wificlient
PubSubClient client(server, 1883, callback ,wifiClient); 


void setup()// configureing the ESP32 
{
  Serial.begin(115200);
  Serial.println();

   pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  Myservo.attach(26);
  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);

  wificonnect();
  mqttconnect();
}

void loop()// Recursive Function
{

   digitalWrite(trigpin1,LOW);
  digitalWrite(trigpin1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin1,LOW);
  float duration=pulseIn(echopin1,HIGH);
  d1=(duration/(58*4));
  if(d1<20){
    Myservo.write(180);
    delay(15);
    Serial.println("Putin waste here");
  }
  else{ 
    Myservo.write(0);
  }


  digitalWrite(trigpin,LOW);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
 float dura=pulseIn(echopin,HIGH);
  d=(dura/(58*4));

w=random(5,100);
String s="Kinathukadavu,Coimbatore";
String status="";
  Serial.print("WasteLevel:");
  Serial.println(d);
  Serial.print("WasteWeight:");
  Serial.println(w);
  Serial.println("Location:");
  Serial.println(s);

  PublishData(d, w);
  delay(1000);
  if (!client.loop()) {
    mqttconnect();
  }
}



/*.....................................retrieving to Cloud...............................*/

void PublishData(float dis, float wei) {
  mqttconnect();//function call for connecting to ibm
  /*
     creating the String in in form JSon to update the data to ibm cloud
  */
  String status="";

  String payload = "{\"DustbinContent\":";
  payload += dis;
  payload += "," "\"WateWeight\":";
  payload += wei;
  payload += "," "\"Location\":";
  payload += "\"Kinathukadavu,Coimbatore\"";
  payload += "}";

  
  Serial.print("Sending payload: ");
  Serial.println(payload);

  
  if (client.publish(publishTopic, (char*) payload.c_str())) {
    Serial.println("Publish ok");// if it sucessfully upload data on the cloud then it will print publish ok in Serial monitor or else it will print publish failed
  } else {
    Serial.println("Publish failed");
  }
  
}


void mqttconnect() {
  if (!client.connected()) {
    Serial.print("Reconnecting client to ");
    Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
      
     initManagedDevice();
     Serial.println();
  }
}
void wificonnect() //function defination for wificonnect
{
  Serial.println();
  Serial.print("Connecting to ");

  WiFi.begin("Wokwi-GUEST", "", 6);//passing the wifi credentials to establish the connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void initManagedDevice() {
  if (client.subscribe(subscribetopic)) {
    Serial.println((subscribetopic));
    Serial.println("subscribe to cmd OK");
  } else {
    Serial.println("subscribe to cmd FAILED");
  }
}

void callback(char* subscribetopic, byte* payload, unsigned int payloadLength) 
{
  
  Serial.print("callback invoked for topic: ");
  Serial.println(subscribetopic);
  for (int i = 0; i < payloadLength; i++) {
    //Serial.print((char)payload[i]);
    data3 += (char)payload[i];
  } 
  Serial.println("data: "+ data3); 
  if(data3=="lighton")
  {
Serial.println(data3);
  }

data3="";  
}
