#include "UltimateGPS.h"

vcss::UltimateGPS::UltimateGPS ()
{
}

vcss::UltimateGPS::UltimateGPS (HardwareSerial hardwareSerial)
{
    this->gpsSerial = &hardwareSerial;
}

// class functions
void vcss::UltimateGPS::setHardwareSerial (HardwareSerial hardwareSerial)
{
    this->gpsSerial = &hardwareSerial;
}
