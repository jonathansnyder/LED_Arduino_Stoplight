
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

}

if(request.indexof("/Yellow")){


}

if(request.indexof("/Red")){

}

if(request.indexof("/Auto")){

}