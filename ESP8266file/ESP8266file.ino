#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
const char* ssid = "Som's OnePlus 9R";   // Your Network SSID
const char* password = "ssoomm12345";       // Your Network Password
float val;
float readD1;
int Pin_D0= 0;
int pin = A0; //LM53 Pin Connected at A0 Pin
WiFiClient client;
unsigned long myChannelNumber = 1773726; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "Q36HC0TPRJAGAT7E"; //Your Write API Key
void setup()
{
  Serial.begin(9600);
  delay(10);
  // Connect to WiFi network
  pinMode(pin, INPUT);
  pinMode(Pin_D0,OUTPUT);
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}
float analogRead1(){
  digitalWrite(Pin_D0, HIGH);
  return analogRead(0);
}
void loop() 
{
  readD1 = analogRead1();
  Serial.println(readD1);
  float percentage = map(readD1, 781, 790, 100, 0);
  Serial.print("Moisture: ");
  Serial.print(percentage);
  Serial.println("%");
  val = analogRead(pin) * (9.0 /1023.0);
  Serial.print("pH: ");
  Serial.println(val);
  delay(100);
  ThingSpeak.writeField(myChannelNumber, 1,percentage, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 2, val, myWriteAPIKey); //Update in ThingSpeak
}
