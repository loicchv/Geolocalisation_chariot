#include "moduleGPS.h"

moduleGPS::moduleGPS(HardwareSerial* portSerie, int rx, int tx) {
    gpsSerial = portSerie; 
    pinRX = rx;
    pinTX = tx;
}

void moduleGPS::initialiser() {
    gpsSerial->begin(9600, SERIAL_8N1, pinRX, pinTX);
}

void moduleGPS::lireTrameGPGGA() {    
    // donnees[0] = ""; 
    // donnees[1] = ""; 
    // donnees[2] = "";

    while (gpsSerial->available() > 0) {
        String trame = gpsSerial->readStringUntil('\n'); 

        if (trame.startsWith("$GPGGA")) {
            int v1 = trame.indexOf(','); // position 1er ","
            int v2 = trame.indexOf(',', v1 + 1); //position 2eme ","
            int v3 = trame.indexOf(',', v2 + 1); //...
            int v4 = trame.indexOf(',', v3 + 1);
            int v5 = trame.indexOf(',', v4 + 1);
            int v6 = trame.indexOf(',', v5 + 1);

            if (v6 > 0) {
                donnees[0] = trame.substring(v1 + 1, v2); //date 
                
                String Latitude = trame.substring(v2 + 1, v3); 
                String dirLatitude = trame.substring(v3 + 1, v4); 
                String Longitude = trame.substring(v4 + 1, v5);
                String dirLongitude = trame.substring(v5 + 1, v6);
                
                if (Latitude.length() >= 4) {
                    double latDeg = Latitude.substring(0, 2).toDouble();       
                    double latMin = Latitude.substring(2).toDouble();          
                    double latDec = latDeg + (latMin / 60.0);
                    if (dirLatitude == "S"){
                        latDec = latDec * -1.0;
                    }               
                    donnees[2] = String(latDec, 6); 
                }

                if (Longitude.length() >= 5) {
                    double lonDeg = Longitude.substring(0, 3).toDouble();       
                    double lonMin = Longitude.substring(3).toDouble();          
                    double lonDec = lonDeg + (lonMin / 60.0);                
                    if (dirLongitude == "W"){
                        lonDec = lonDec * -1.0;              
                    }
                    donnees[1] = String(lonDec, 6); 
                }
            }
        }
    }
}

String moduleGPS::get_heure(){
    String heureBrute = donnees[0];
    String heures = heureBrute.substring(0, 2); 
    String minutes = heureBrute.substring(2, 4);  
    return heures + ":" + minutes;  
}

String moduleGPS::get_longitude(){
    int positionPoint = donnees[1].indexOf('.');
    return donnees[1].substring(positionPoint + 1);
}

String moduleGPS::get_latitude(){
    int positionPoint = donnees[2].indexOf('.');
    return donnees[2].substring(positionPoint + 1);
}








