#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEEddystoneTLM.h>
#include <BLEBeacon.h>
#include <vector>
using namespace std;
#include "beacon.h"


#ifndef BEACONPUBLICATION_H
#define BEACONPUBLICATION_H

class moduleGPS;

class BeaconPublication : public BLEAdvertisedDeviceCallbacks {
  private:
    BLEScan *pBLEScan;
    BLEDevice* pBLEDevice; 
    vector<Beacon> vectorBeacon;   
    moduleGPS* monGPS;   
 
  public:
    BeaconPublication(moduleGPS* gps);
    void onResult(BLEAdvertisedDevice advertisedDevice);
    void init();
    void start(int dureeScan);
    void clear();
    vector<Beacon> get_vectorBeacon(); 
};

#endif