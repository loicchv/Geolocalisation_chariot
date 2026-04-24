#include "beacon.h"

Beacon::Beacon(int mId, int maj, int min, int rss, int lat, int longi, String heur){
    manufactureId = mId;
    major = maj;
    minor = min;
    rssi = rss;
    latitude = lat;
    longitude = longi;
    heure = heur;
}

int Beacon::get_manufactureId(){
    return manufactureId;
}

int Beacon::get_major(){
    return major;
}

int Beacon::get_minor(){
    return minor;
}

int Beacon::get_rssi(){
    return rssi;
}

int Beacon::get_longitude(){
    return longitude;
}

int Beacon::get_latitude(){
    return latitude;
}

String Beacon::get_heure(){
    return heure;
}
