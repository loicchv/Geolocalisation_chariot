#include "liaisonTTN.h"


liaisonTTN::liaisonTTN(String eui, String key){
  appEUI = eui;
  appKEY = key;  
  accuser_reception = false;
}

void liaisonTTN::initialiser(){
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };


  int connected = modem.joinOTAA(appEUI, appKEY);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }

  // Set poll interval to 60 secs.
  modem.minPollInterval(60);
  // NOTE: independent of this setting, the modem will
  // not allow sending more than one message every 2 minutes,
  // this is enforced by firmware and can not be changed.
}

void liaisonTTN::sendData(String data){
  int err = 0;
  accuser_reception = false;
  modem.beginPacket();
  modem.print(data);
  
  err = modem.endPacket(true);

  // Si err > 0, l'envoi est validé et l'accusé a été reçu
  if (err > 0) {
    accuser_reception = true;
  } else {
    accuser_reception = false;
    Serial.println("Nononono");
  }
}

bool liaisonTTN::get_accuser_reception(){
  return accuser_reception;
}