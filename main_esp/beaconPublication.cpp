#include "beaconPublication.h"
#include "moduleGPS.h"

BeaconPublication::BeaconPublication(moduleGPS* gps){
    monGPS = gps;
}

void BeaconPublication::onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.haveManufacturerData() == true) {
        String strManufacturerData = advertisedDevice.getManufacturerData();
        uint8_t cManufacturerData[255];
        size_t dataLength = strManufacturerData.length();

        if (dataLength == 25) {
            memcpy(cManufacturerData, strManufacturerData.c_str(), dataLength);

            if (cManufacturerData[0] == 0x4C && cManufacturerData[1] == 0x00) {
                BLEBeacon oBeacon = BLEBeacon();
                oBeacon.setData(strManufacturerData);
                int manuFactureID = oBeacon.getManufacturerId();
                int major = ENDIAN_CHANGE_U16(oBeacon.getMajor());
                int minor = ENDIAN_CHANGE_U16(oBeacon.getMinor()); 
                int rssi = advertisedDevice.getRSSI();

                int latitude = monGPS->get_latitude();
                int longitude = monGPS->get_longitude();
                String heure = monGPS->get_heure();

                Beacon newBeacon(manuFactureID, major, minor, rssi, latitude, longitude, heure);
                vectorBeacon.push_back(newBeacon);
            }
        } 
    }
}

void BeaconPublication::init(){
    pBLEDevice = new BLEDevice();
    pBLEDevice->init("");
    pBLEScan = pBLEDevice->getScan(); 
    pBLEScan->setAdvertisedDeviceCallbacks(this);
    pBLEScan->setActiveScan(true);  
    pBLEScan->setInterval(100);
}

void BeaconPublication::start(int dureeScan){
    vectorBeacon.clear();
    vectorBeacon.shrink_to_fit();
    pBLEScan->start(dureeScan, false);
}

void BeaconPublication::clear(){
    pBLEScan->clearResults();
}

vector<Beacon> BeaconPublication::get_vectorBeacon(){
    return vectorBeacon;
}
