
// long lastMillis = 0;
// long greenAndRedTimer = 3000;
// long yellowTimer = 1000;


WiFiClient client = server.available();
if (!client){
    return;
}

while(!client.available()){
    delay(1);
}

String request = client.readStringUntil('\r');
client.flush();

if(request.indexof("/Green") != -1){
    autostate = 0;
    automode = false;
    greenled();
}

if(request.indexof("/Yellow") != -1){
    autostate = 0;
    automode = false;
    yellowled();
}

if(request.indexof("/Red") != -1){
    autostate = 0;
    automode = false;
    redled();
}

if(request.indexof("/Off") != -1){
    autostate = 0;
    automode = false;
    offled();
}

if(request.indexof("/Auto") != -1){
    autocycle();
}
currenttime = millis();
if(automode){
    if(autostate == 1){
        if(currenttime - lastMillis > greenAndRedTimer){
            yellowled();
            autostate = 2;
            lastMillis = currenttime;
            }
        }
    if(autostate == 2){
        if(currenttime - lastMillis > yellowTimer){
            redled();
            autostate = 3;
            lastMillis = currenttime;
        }
    }
    if(autostate == 3)
        if(currenttime - lastMillis > greenAndRedTimer){
            greenled();
            autostate = 1;
            lastMillis = currenttime;
        }
}

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
client.println("    <a href=\"/none\" class=\"ledbuttonOff\">Off</a>");
client.println("");
client.println("    <a href=\"/auto\" class=\"ledbutton\">Stoplight Cycle</a>");
client.println("    </div>");
client.println("");
client.println("");
client.println("</body>");
client.println("");
client.println("</html>");

void greenled(){
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
}

void redled(){
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
}

void yellowled(){
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
}

void offled(){
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
}

void autocycle(){
    autostate = 1;
    greenled();
    automode = true;
    
}