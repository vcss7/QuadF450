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

/**
 * @brief Applies the xor checksum algorithm to a string.
 *
 * @details The checksum is calculated by summing the result of applying xor to
 * each character between the first instance of '$' and the first instance of
 * '*' after the first instance of '$'.
 *
 * @param[in] string is the complete string to calculate the checksum of.
 *
 * @return the calculated xor checksum.
 */
uint8_t vcss::UltimateGPS::calculateXorChecksum (const char *string)
{
    const char CHECKSUM_START_CHAR = '$';
    const char CHECKSUM_END_CHAR   = '*';

    uint8_t i = 0;

    // search for index with start char of checksum
    while (string[i] != CHECKSUM_START_CHAR)
    {
        i++;
    }

    // calculate checksum
    uint8_t calculatedXorChecksum = 0;
    while (string[i] != CHECKSUM_END_CHAR)
    {
        // return false if string ends before calculation is done
        if (string[i] == '\0')
            return false;

        calculatedXorChecksum ^= string[i];
        i++;
    }

    return calculatedXorChecksum;
}

/**
 * @brief Applies the xor checksum algorithm to a string.
 *
 * @details The checksum is calculated by summing the result of applying xor to
 * each character between the first instance of '$' and the first instance of
 * '*' after the first instance of '$'.
 *
 * @param[in] string is the complete string to check the checksum of.
 * @param[in] checksum is the expected value of the xor checksum algorithm.
 *
 * @return whether the checksum *checks* out ;)
 */
bool vcss::UltimateGPS::hasValidChecksum (const char *string,
                                          const uint8_t checksum)
{
    if (strlen (string) > 128)
    {
        return false;
    }

    // todo: get the checksum from the string

    return (calculateXorChecksum (string) == checksum);
}
