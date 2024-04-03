#include "UltimateGPS.h"

/**
 * @brief Contrcutor to initialize the "device" without any connections.
 */
vcss::UltimateGPS::UltimateGPS ()
{
}

/**
 * @brief Constructor to initialize the "device" with a hardware serial
 * connection.
 *
 * @param hardwareSerial is the HardwareSerial the device is connected to.
 */
vcss::UltimateGPS::UltimateGPS (HardwareSerial hardwareSerial)
{
    this->gpsSerial = &hardwareSerial;
}

/**
 * @brief Sets the HardwareSerial to use.
 *
 * @param hardwareSerial is the HardwareSerial the device is connected to.
 */
void vcss::UltimateGPS::setHardwareSerial (HardwareSerial hardwareSerial)
{
    this->gpsSerial = &hardwareSerial;
}

/**
 * @brief Sets rxPin.
 *
 * @param rxPin is the uint8_t to set the rxPin to.
 */
void vcss::UltimateGPS::setRxPin (const uint8_t rxPin)
{
    this->rxPin = rxPin;
}

/**
 * @brief Sets txPin.
 *
 * @param txPin is the uint8_t to set the txPin to.
 */
void vcss::UltimateGPS::setTxPin (const uint8_t txPin)
{
    this->txPin = txPin;
}

/**
 * @brief Checks if the rxPin is high.
 *
 * @details UART devices keep the transmitting line on high when idle. Returning
 * true means *something* is keeping the line high.. maybe a UART device?
 * 
 * @return If rx line is high.
 */
bool vcss::UltimateGPS::isRxHigh ()
{
    return digitalRead (this->rxPin);
}
