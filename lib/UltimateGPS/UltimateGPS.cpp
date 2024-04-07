#include "UltimateGPS.h"

#include <unity.h>

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
 * @brief Applies the checksum xor 8 algorithm to a string.
 *
 * @details The checksum is calculated by summing the result of applying xor 8
 * to each character between the first instance of '$' and the first instance of
 * '*' after the first instance of '$'.
 *
 * @param[in] string is the complete string to calculate the checksum of.
 *
 * @return the calculated xor checksum as a hexidecimal.
 */
uint8_t vcss::UltimateGPS::calculateXorChecksum (const char *string)
{
    uint8_t calculatedChecksum = 0;

    // calculate checksum
    uint8_t i = 0;
    while (string[i] != '\0')
    {
        calculatedChecksum ^= string[i];
        i++;
    }

    return calculatedChecksum;
}

/**
 * @brief Checks if a string has a valid xor checksum
 *
 * @details The checksum is calculated by summing the result of applying xor to
 * each character between the first instance of '$' and the first instance of
 * '*' after the first instance of '$'.
 *
 * @param[in] string is the complete string to check the checksum of.
 *
 * @return whether the checksum *checks* out ;)
 */
bool vcss::UltimateGPS::hasValidXorChecksum (const char *string)
{
    if (string == NULL || strlen (string) > 128 || strlen (string) < 2)
    {
        return false;
    }

    const char CHECKSUM_START_CHAR = '$';
    const char CHECKSUM_END_CHAR   = '*';

    uint8_t i, startCharIndex, endCharIndex = 0;

    // search for index with start char of checksum
    while (string[i] != CHECKSUM_START_CHAR)
    {
        if (string[i] == '\0')
        {
            return false;
        }
        i++;
    }

    // record index and move right one
    startCharIndex = i++;

    // continue and search for the index with end char of checksum
    while (string[i] != CHECKSUM_END_CHAR)
    {
        if (string[i] == '\0')
        {
            return false;
        }
        i++;
    }

    // record index and move right one
    endCharIndex = i++;

    // get the expected checksum result
    uint16_t expectedChecksum = 0;
    while (string[i] != '\r')
    {
        if (string[i] == '\0')
        {
            return false;
        }

        char hexChar = string[i];

        // convert from hexidecimal to digit and add it to expectedChecksum
        uint8_t hexOnesDigit;
        if (hexChar >= '0' && hexChar <= '9')
        {
            hexOnesDigit = (uint8_t) hexChar - '0';
        }
        else if (hexChar >= 'A' && hexChar <= 'F')
        {
            hexOnesDigit = (uint8_t) hexChar - 'A' + 10;
        }

        // shift bits to make space for the right most hex digit, then add it
        expectedChecksum = expectedChecksum << 4 | hexOnesDigit;

        i++;
    }

    // construct string to checksum
    uint8_t checksumStringLength = endCharIndex - startCharIndex - 1;
    char checksumString[checksumStringLength + 1];

    for (uint8_t j = 0; j < checksumStringLength; j++)
    {
        // add one to string index to skip '$'
        checksumString[j] = string[startCharIndex + 1 + j];
    }

    // terminate string with null
    checksumString[checksumStringLength] = '\0';

    return (expectedChecksum == calculateXorChecksum (checksumString));
}
