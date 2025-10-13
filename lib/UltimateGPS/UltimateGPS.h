/**
 * @file UltimateGPS.h
 *
 * @brief A lightweight library to get basic gps information from the Ultimate
 * GPS breakout module manufactured by Adafruit.
 *
 * MTK3339-based module specs:
 * Satellites: 22 tracking, 66 searching
 * Patch Antenna Size: 15mm x 15mm x 4mm
 * Update rate: 1 to 10 Hz
 * Position Accuracy: 1.8 meters
 * Velocity Accuracy: 0.1 meters/s
 * Warm/cold start: 34 seconds
 * Acquisition sensitivity: -145 dBm
 * Tracking sensitivity: -165 dBm
 * Maximum Velocity: 515m/s
 * Vin range: 3.0-5.5VDC
 * MTK3339 Operating current: 25mA tracking, 20 mA current draw during
 * navigation
 * Output: NMEA 0183, 9600 baud default
 * DGPS/WAAS/EGNOS supported
 * FCC E911 compliance and AGPS support (Offline mode : EPO valid up to 14 days)
 * Up to 210 PRN channels
 * Jammer detection and reduction
 * Multi-path detection and compensation
 */

// The GPS modules uses NMEA
// todo: what kind of NMEA message does the Ultimate GPS use?

#ifndef ULTIMATE_GPS_H
#define ULTIMATE_GPS_H

#include <Arduino.h>

namespace vcss
{

const uint8_t TEENSY_HARDWARE_SERIAL_1_RX = 0;
const uint8_t TEENSY_HARDWARE_SERIAL_1_TX = 1;

enum AckCmdResponse
{
    INVALID     = 0,
    UNSUPPORTED = 1,
    FAILED      = 2,
    SUCCESS     = 3
};

class UltimateGPS
{
private:
    HardwareSerial *gpsSerial = &SERIAL_PORT_HARDWARE;
    uint8_t rxPin             = TEENSY_HARDWARE_SERIAL_1_RX;
    uint8_t txPin             = TEENSY_HARDWARE_SERIAL_1_TX;

public:
    // constructors
    UltimateGPS ();
    UltimateGPS (HardwareSerial hardwareSerial);  // Using HardwareSerial

    // class functions
    void setHardwareSerial (HardwareSerial hardwareSerial);
    void setRxPin (const uint8_t rxPin);
    void setTxPin (const uint8_t txPin);
    bool isRxHigh ();

    // pmkt functions
    bool setGpsBaudRate (const uint32_t baudRate);
    uint8_t checkGpsAck (const uint32_t cmd, const uint32_t);
    void setNmeaOutput ();
    uint8_t calculateXorChecksum (const char *string);
    bool hasValidChecksum (const char *string, const uint8_t checksum);
};

}  // namespace vcss

#endif
