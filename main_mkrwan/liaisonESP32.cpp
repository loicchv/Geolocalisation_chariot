#include "liaisonESP32.h"

liaisonESP32::liaisonESP32(){

}

void liaisonESP32::initialiser(){
    Serial1.begin(9600);
}

String liaisonESP32::readData(){
    String msg = Serial1.readStringUntil('\n');
    msg.trim();
    return msg;    
}