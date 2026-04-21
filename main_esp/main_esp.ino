#include <Arduino.h>
#include <vector>
using namespace std;
#include "beaconPublication.h"
#include "moduleGPS.h"
#include "liaisonMKRWAN.h"

int dureeScan = 5;
vector<Beacon> listeBeacons5SEC;
vector<Beacon> listeBeacons1H;
moduleGPS monGPS(&Serial2, 27, 26);
BeaconPublication* beaconPub;
liaisonMKRWAN mkrwan(16,17)

String formatTrame(vector<Beacon> liste){
  String trame = "";
  trame+= "{";
  for(int i = 0; i < liste.size(); i++){
    Beacon beacon = liste[i];
    trame += "\"" + String(beacon.get_major()) + "\", ";
    trame += "\"" + String(beacon.get_minor()) + "\", ";
    trame += "\"" + String(beacon.get_rssi()) + "\", ";
    trame += "\"" + String(beacon.get_longitude()) + "\", ";
    trame += "\"" + String(beacon.get_latitude()) + "\", ";
    trame += "\"" + String(beacon.get_heure()) + "\"";
    if(i != liste.size()-1){trame += "\;";}
  }
  trame += "}";
  return trame;
}

void setup() {
  Serial.begin(115200);
  beaconPub = new BeaconPublication(&monGPS);
  beaconPub->init();
  monGPS.initialiser();
  mkrwan.initialiser();
}

void loop() {
  monGPS.lireTrameGPGGA();

  // beaconPub->set_longitude(monGPS.get_longitude().toFloat());
  // beaconPub->set_latitude(monGPS.get_latitude().toFloat());
  // beaconPub->start(dureeScan);
  // listeBeacons = beaconPub->get_vectorBeacon();

  for(int k = 0; k < 5; k++){
    //Scan des beacons
    beaconPub->start(dureeScan);
    listeBeacons5SEC = beaconPub->get_vectorBeacon();


    //Dédoublonnage des beacons
  for(int i = 0; i < listeBeacons5SEC.size(); i++) {
      Beacon beacon5s = listeBeacons5SEC[i];
      bool estPresent = false;
      int iPresent = 0; 

      for(int j = 0; j < listeBeacons1H.size(); j++) {
          Beacon beacon1h = listeBeacons1H[j];

          if(beacon5s.get_manufactureId() == beacon1h.get_manufactureId() && beacon5s.get_major() == beacon1h.get_major() && beacon5s.get_minor() == beacon1h.get_minor()) { 
              estPresent = true;
              iPresent = j;
              break;
          }
      }
      if(estPresent) {
        if (beacon5s.get_rssi() > listeBeacons1H[iPresent].get_rssi()){
          listeBeacons1H[iPresent] = beacon5s;
        }

      } else {    
          listeBeacons1H.push_back(beacon5s); 
      }
    }
  }

  //Supprimer les beacons incomplets
  for(int i = 0; i < listeBeacons1H.size();){
    Beacon beacon = listeBeacons1H[i];
    if(beacon.get_major()==0 || beacon.get_minor()==0 || beacon.get_longitude()==0 || beacon.get_latitude()==0 || beacon.get_heure() == ":"){listeBeacons1H.erase(listeBeacons1H.begin()+i);}
    else {i++;}
  }

  //Mettre la liste des beacons sour le format d'une trame
  String trameFormater = formatTrame(listeBeacons1H); 
  //Envoie de la trame vers la carte mkrwan
  mkrwan.sendData(trameFormater);

  beaconPub->clear();
  
  delay(2000);
}
