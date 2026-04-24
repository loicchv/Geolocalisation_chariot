#ifndef BEACON_H
#define BEACON_H

#include <Arduino.h>

class Beacon{
    private:
      int manufactureId;
      int major;
      int minor;
      int rssi;
      int longitude;
      int latitude;
      String heure;

    public:
      Beacon(int mId, int maj, int min, int rss, float lat, float longi, String heur);
      int get_manufactureId();
      int get_major();
      int get_minor();
      int get_rssi();
      int get_longitude();
      int get_latitude();
      String get_heure();
};

#endif 
