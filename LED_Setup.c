#include <ESP8266WiFi.h>
const char* ssid = ;
const char* password = ;

int green = D5;
int yellow = D6;
int red = D7;

long lastMillis = 0;
long greenAndRedTimer = 3000;
long yellowTimer = 1000;
//autostate green = 1, yellow = 2, red = 3
int autostate = 0;

pinMode(green, OUTPUT);
pinMode(yellow, OUTPUT);
pinMode(red, OUTPUT);


WiFiServer server(80);

//setup
Serial.begin(115200);
delay(10);

WiFi.begin(ssid, password);

while(WiFi.status() != WL_CONNECTED){
    delay(450);
}
Serial.println("WiFi Connected");

//start server
server.begin();
Serial.print(WiFi.localIP());

