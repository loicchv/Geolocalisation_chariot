#ifndef MODULEGPS_H
#define MODULEGPS_H

#include <Arduino.h>
#include <HardwareSerial.h>

class moduleGPS {
    private:
        HardwareSerial* gpsSerial; 
        int pinRX;
        int pinTX;
        String donnees[3];
        

    public:
        moduleGPS(HardwareSerial* portSerie, int rx, int tx);
        
        void initialiser();
        void lireTrameGPGGA();
        String get_longitude();
        String get_latitude();
        String get_heure();
};

#endif