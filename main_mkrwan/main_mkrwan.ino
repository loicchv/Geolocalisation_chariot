#include "liaisonESP32.h"
#include "liaisonTTN.h"

liaisonESP32 ESP32;

String appEui = "0000000000000000";
String appKey = "970846FE1C620DC02012E94D6EFF8B48";
liaisonTTN TTN(appEui, appKey);



String firstData(String data){
    String trame;
    int index = data.indexOf(';');
    if(data.indexOf('{')==0){
        return trame += data.substring(0, index) + "}";
    }
    if(index == -1){
        trame += "{" + data;        
        return trame;
    }
    return trame += "{" + data.substring(0, index) + "}";
}

String deleteData(String data, String dataDelete){
    if(data == dataDelete){return "";}
    if(data.indexOf('{')==0){
        return data.substring(dataDelete.length()+1);
    }
    return data.substring(dataDelete.length()-1);
}

void setup(){
    delay(5000);
    Serial.begin(115200);
    Serial.println("ESP32 Init");
    ESP32.initialiser();
    Serial.println("TTN Init");
    TTN.initialiser();
}

void loop(){
    String trameFormatee;
    do{
        trameFormatee = ESP32.readData();
    }while(trameFormatee == "");
        
    do{
        String data = firstData(trameFormatee);
        Serial.println("Beacon en cours d'envoi : " + data);
        do {
            TTN.sendData(data);
            delay(5000);
        } while(TTN.get_accuser_reception() != true);
        trameFormatee = deleteData(trameFormatee, data);
    }while(trameFormatee != "");

    delay(1000);
}
