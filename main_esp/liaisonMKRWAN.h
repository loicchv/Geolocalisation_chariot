#include <HardwareSerial.h>
#include <Arduino.h>

#ifndef LIAISONMKRWAN_H
#define LIAISONMKRWAN_H

class liaisonMKRWAN{
    private:
    int pinRX;
    int pinTX;

    public:
    liaisonMKRWAN(int rx, int tx);
    void initialiser();
    void sendData(String data);
};

#endif
