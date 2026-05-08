#include <Arduino.h>
#include <vector>
using namespace std;
#include "beaconPublication.h"
#include "moduleGPS.h"
#include "liaisonMKRWAN.h"

int dureeScan = 5;
int nbScansParHeure = 3600/dureeScan;
vector<Beacon> listeBeacons5SEC;
vector<Beacon> listeBeacons1H;
moduleGPS monGPS(&Serial2, 27, 26);
BeaconPublication* beaconPub;
liaisonMKRWAN mkrwan(16,17);

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

vector<Beacon> integrerNouveaux(vector<Beacon> listeEnvoi, vector<Beacon> listeNouveaux){
  for(int i = 0; i < listeNouveaux.size(); i++) {
    Beacon newBeacon = listeNouveaux[i];
    bool estPresent = false;
    int iPresent = 0; 

    for(int j = 0; j < listeEnvoi.size(); j++) {
        Beacon beaconEnvoi = listeEnvoi1H[j];

        if(newBeacon.get_manufactureId() == beaconEnvoi.get_manufactureId() && newBeacon.get_major() == beaconEnvoi.get_major() && newBeacon.get_minor() == beaconEnvoi.get_minor()) { 
            estPresent = true;
            iPresent = j;
            break;
        }
    }
    if(estPresent) {
      if (newBeacon.get_rssi() > listeEnvoi[iPresent].get_rssi()){listeEnvoi[iPresent] = newBeacon;}
    } else {    
        listeEnvoi.push_back(newBeacon); 
    }
  }
  return listeEnvoi;
}

vector<Beacon> supprimerIncomplet(vector<Beacon> liste){
  for(int i = 0; i < liste.size();){
    Beacon beacon = liste[i];
    if(beacon.get_major()==0 || beacon.get_minor()==0 || beacon.get_longitude()==0 || beacon.get_latitude()==0 || beacon.get_heure() == ":"){liste.erase(liste.begin()+i);}
    else {i++;}
  }
  return liste;
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

  for(int k = 0; k < nbScansParHeure; k++){
    //Scan des beacons
    beaconPub->start(dureeScan);
    listeBeacons5SEC = beaconPub->get_vectorBeacon();
    //Dédoublonnage des beacons
    listeBeacons1H = integrerNouveaux(listeBeacons1H, listeBeacons5SEC);
  }

  //Supprimer les beacons incomplets
  listeBeacons1H = supprimerIncomplet(listeBeacons1H);

  //Mettre la liste des beacons sour le format d'une trame
  String trameFormatee = formatTrame(listeBeacons1H); 
  //Envoie de la trame vers la carte mkrwan
  if(trameFormatee!="{}"){
    mkrwan.sendData(trameFormatee);
    Serial.print("Envoi effectuer :");
    Serial.println(trameFormatee);
  } 

  beaconPub->clear();
  
  delay(2000);
}
