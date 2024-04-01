/**
 * @file UltimateGPS.h
 *
 * @brief A lightweight library to get basic gps information from the Ultimate
 * GPS breakout module manufactured by Adafruit.
 */

// The GPS modules uses NMEA
// todo: what kind of NMEA message does the Ultimate GPS use?

#ifndef ULTIMATE_GPS_H
#define ULTIMATE_GPS_H

#include <Arduino.h>

namespace vcss
{

class UltimateGPS
{
private:
    HardwareSerial *gpsSerial;

public:
    // constructors
    UltimateGPS ();
    UltimateGPS (HardwareSerial hardwareSerial);  // Using HardwareSerial

    // class functions
    void setHardwareSerial (HardwareSerial hardwareSerial);
};

}  // namespace vcss

#endif
