#ifndef LIAISONTTN_H
#define LIAISONTTN_H

#include <Arduino.h>
#include <MKRWAN.h>

class liaisonTTN{
    private:
      bool accuser_reception;
      String appEUI;
      String appKEY;
      LoRaModem modem;
    public:
        liaisonTTN(String eui, String key);
        void initialiser();
        void sendData(String data);
        bool get_accuser_reception();
};
#endif