#include <ESP8266WiFi.h>

const char* ssid = "Bob";
const char* password = "darktremors";

int green = D5;
int yellow = D6;
int red = D7;

WiFiServer server(80);
//IPAddress ip(192, 168, 1, 4); //Static
//IPAddress gateway(192, 168, 1, 104);

unsigned long lastMillis;
unsigned long greenAndRedTimer = 5000;
unsigned long yellowTimer = 3000;
unsigned long currenttime = 0;
//autostate green = 1, yellow = 2, red = 3
int autostate = 0;
bool automode = false;
void setup() {
  // put your setup code here, to run once:
  // Sever code is from the tutorial found here: http://www.esp8266learning.com/wemos-webserver-example.php

pinMode(green, OUTPUT);
pinMode(yellow, OUTPUT);
pinMode(red, OUTPUT);

//setup
Serial.begin(115200);
// Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());
  lastMillis = millis(); 
}

void loop() {
  // put your main code here, to run repeatedly:

WiFiClient client = server.available();



String request = client.readStringUntil('\r');
client.flush();

//Serial.println("start of if block");
//turns on green led
if(request.indexOf("/Green") != -1){
    autostate = 0;
    automode = false;
    greenled();
}
//turns led yellow
if(request.indexOf("/Yellow") != -1){
    autostate = 0;
    automode = false;
    yellowled();
}
//turns on led exits cycle
if(request.indexOf("/Red") != -1){
    autostate = 0;
    automode = false;
    redled();
}
//turns off leds exits cycle
if(request.indexOf("/Off") != -1){
    autostate = 0;
    automode = false;
    offled();
}
//starts the autocycle of stoplight
if(request.indexOf("/Auto") != -1){
    autocycle();
    //Serial.println("in the auto button zone");
}
currenttime = millis();
//Serial.println();
//Serial.println("automode value");
//Serial.print(automode);
//Serial.println();
if(automode){
  //debuging serial var print
Serial.println("automode on");
    if(autostate == 1){
      //debuging serial print
      Serial.println("auto1");
        if(currenttime - lastMillis >= greenAndRedTimer){
            yellowled();
            autostate = 2;
            lastMillis = currenttime;
            }
        }
    if(autostate == 2){
      //debuging serial print
      Serial.println("auto2");
      //Serial.print("current");
      //Serial.print(currenttime);
      //Serial.println();
      //Serial.println("last");
      //Serial.print(lastMillis);
      currenttime = millis();
        if(currenttime - lastMillis >= yellowTimer){
            redled();
            autostate = 3;
            lastMillis = currenttime;
        }
    }
    if(autostate == 3){
      //debuging serial print
      Serial.println("auto3");
      currenttime = millis();
        if(currenttime - lastMillis >= greenAndRedTimer){
            greenled();
            autostate = 1;
            lastMillis = currenttime;
        }
}
}
//this is the HTML webpage to request the light state
client.println("<!DOCTYPE html>");
client.println("");
client.println("<head>");
client.println("<title>Stoplight</title>");
client.println("</head>");
client.println("<style>");
client.println(".ledbuttonRed {");
client.println("background-color: #ba1313;");
client.println("border: none;");
client.println("text-align: center;");
client.println("font-size: 20px;");
client.println("cursor: pointer;");
client.println("text-decoration: none;");
client.println("padding: 30px 30px;");
client.println("color: black;");
client.println("display: inline-block");
client.println("}");
client.println(".ledbuttonYellow {");
client.println("background-color: yellow;");
client.println("border: none;");
client.println("text-align: center;");
client.println("font-size: 20px;");
client.println("cursor: pointer;");
client.println("text-decoration: none;");
client.println("padding: 30px 30px;");
client.println("color: black;");
client.println("display: inline-block");
client.println("}");
client.println(".ledbuttonGreen {");
client.println("background-color: green;");
client.println("border: none;");
client.println("text-align: center;");
client.println("font-size: 20px;");
client.println("cursor: pointer;");
client.println("text-decoration: none;");
client.println("padding: 30px 30px;");
client.println("color: black;");
client.println("display: inline-block");
client.println("}");
client.println(".ledbuttonOff {");
client.println("background-color: lightgray;");
client.println("border: none;");
client.println("text-align: center;");
client.println("font-size: 20px;");
client.println("cursor: pointer;");
client.println("text-decoration: none;");
client.println("padding: 30px 30px;");
client.println("color: black;");
client.println("display: inline-block");
client.println("}");
client.println(".ledbutton {");
client.println("background-color: burlywood;");
client.println("border: none;");
client.println("text-align: center;");
client.println("font-size: 20px;");
client.println("cursor: pointer;");
client.println("text-decoration: none;");
client.println("padding: 30px 30px;");
client.println("color: black;");
client.println("display: inline-block;");
client.println("}");
client.println("div {");
client.println("display: flex;");
client.println("align-items: center;");
client.println("justify-content: center;");
client.println("}");
client.println("p {");
client.println("display: flex;");
client.println("align-items: center;");
client.println("justify-content: center;");
client.println("}");
client.println("</style>");
client.println("<link rel=\"stylesheet\" href=\"../static/stoplight.css\">");
client.println("<body>");
client.println("    <p>Select the button for the chosen light. The Stoplight Cycle button will run 3 cycles of the stoplight.</p>");
client.println("    <div>");
client.println("    ");
client.println("    <a href=\"/Red\" class=\"ledbuttonRed\">Red Light</a>");
client.println("");
client.println("    <a href=\"/Yellow\" class=\"ledbuttonYellow\">Yellow Light</a>");
client.println("");
client.println("    <a href=\"/Green\" class=\"ledbuttonGreen\">Green Light</a>");
client.println("");
client.println("    <a href=\"/Off\" class=\"ledbuttonOff\">Off</a>");
client.println("");
client.println("    <a href=\"/Auto\" class=\"ledbutton\">Stoplight Cycle</a>");
client.println("    </div>");
client.println("");
client.println("");
client.println("</body>");
client.println("");
client.println("</html>");
}
//changes led to green
void greenled(){
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
}
//changes led to red
void redled(){
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
}
//changes led to yellow
void yellowled(){
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
}
//turns off the led
void offled(){
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
}
//starts the autocycling of the stoplight
void autocycle(){
    Serial.println("autocycle function");
    greenled();
    autostate = 1;
    automode = true;
    
}