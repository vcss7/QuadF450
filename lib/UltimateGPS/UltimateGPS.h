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

const uint8_t TEENSY_HARDWARE_SERIAL_1_RX = 0;
const uint8_t TEENSY_HARDWARE_SERIAL_1_TX = 1;

class UltimateGPS
{
private:
    typedef enum AckCmdResponse
    {
        ERROR       = -1,  // Catch all error
        INVALID     = 0,   // Invalid command
        UNSUPPORTED = 1,   // Unsupported command
        FAILED      = 2,   // Valid command, but execution failed
        SUCCESS     = 3    // Valid command, and execution success
    } AwkCmdResponse;

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
    int8_t checkPkmtAwk (const char *command);
    bool setGpsBaudRate (const uint32_t baudRate);
    void setNmeaOutput ();
    uint8_t calculateXorChecksum (const char *string);
    bool hasValidXorChecksum (const char *string);
};

#endif
