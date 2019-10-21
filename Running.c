
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
    autocycle = 0;
    greenled();
}

if(request.indexof("/Yellow") != -1){
    autocycle = 0;
    yellowled();
}

if(request.indexof("/Red") != -1){
    autocycle = 0;
    redled();
}

if(request.indexof("/Off") != -1){
    autocycle = 0;
    offled();
}

if(request.indexof("/Auto") != -1){
    autocycle();
}
if(autocycle == 1){
    if(autostate == 1){
        if(currenttime - lastMillis > greenAndRedTimer){
            yellowled();
            autostate = 2;
            }
        }
    if(autostate == 2){
        if(currenttime - lastMillis > yellowTimer){
            redled();
            autostate = 3;
        }
    }
    if(autostate == 3)
        if(currenttime - lastMillis > greenAndRedTimer){
            greenled();
            autostate = 1;
        }
}
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
    unsigned long currenttime = millis();
    
    greenled();
    
}