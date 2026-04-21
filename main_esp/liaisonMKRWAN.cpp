#include "liaisonMKRWAN.h"

liaisonMKRWAN::liaisonMKRWAN(int rx, int tx){
    pinRX = rx;
    pinTX = tx;    
}

void liaisonMKRWAN::initialiser(){
    Serial1.begin(9600, SERIAL_8N1, pinRX, pinTX);
    
}

void liaisonMKRWAN::sendData(String data){
    Serial1.println(data);
}
