
WiFiClient client = server.available();
if (!client){
    return;
}

while(!client.available()){
    delay(1);
}

String request = client.readStringUntil('\r');
client.flush();

if(request.indexof("/Green")){
    greenled();
}

if(request.indexof("/Yellow")){
    yellowled();
}

if(request.indexof("/Red")){
    redled();
}

if(request.indexof("/Auto")){

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

}