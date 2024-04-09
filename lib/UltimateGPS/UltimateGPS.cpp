#include "UltimateGPS.h"

/**
 * @brief Contrcutor to initialize the "device" without any connections.
 */
UltimateGPS::UltimateGPS ()
{
}

/**
 * @brief Constructor to initialize the "device" with a hardware serial
 * connection.
 *
 * @param[in] hardwareSerial is the HardwareSerial the device is connected to.
 */
UltimateGPS::UltimateGPS (HardwareSerial hardwareSerial)
{
    this->gpsSerial = &hardwareSerial;
}

/**
 * @brief Sets the HardwareSerial to use.
 *
 * @param[in] hardwareSerial is the HardwareSerial the device is connected to.
 */
void UltimateGPS::setHardwareSerial (HardwareSerial hardwareSerial)
{
    this->gpsSerial = &hardwareSerial;
}

/**
 * @brief Sets rxPin.
 *
 * @param[in] rxPin is the uint8_t to set the rxPin to.
 */
void UltimateGPS::setRxPin (const uint8_t rxPin)
{
    this->rxPin = rxPin;
}

/**
 * @brief Sets txPin.
 *
 * @param[in] txPin is the uint8_t to set the txPin to.
 */
void UltimateGPS::setTxPin (const uint8_t txPin)
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
bool UltimateGPS::isRxHigh ()
{
    return digitalRead (this->rxPin);
}

/**
 * @brief Checks the serial port for a valid PKMT command response.
 *
 * @param[in] command is the command string response from the gps device.
 *
 * @return The response we interpret from the string
 */
int8_t UltimateGPS::checkPkmtAwk (const char *command)
{
    if (command == NULL)
    {
        return AwkCmdResponse::ERROR;
    }

    int8_t cmdResponse;

    size_t strLength = strlen (command);
    for (size_t i = 0; i < strLength; i++)
    {
        if (command[i] != '\0')
        {
            return AwkCmdResponse::INVALID;
        }
        else if (command[i] == '*')
        {
            // the character before '*' is the command response
            break;
        }

        cmdResponse = command[i];
    }

    switch (cmdResponse)
    {
        case AwkCmdResponse::INVALID:
            cmdResponse = AwkCmdResponse::INVALID;
            break;
        case AwkCmdResponse::UNSUPPORTED:
            cmdResponse = AwkCmdResponse::UNSUPPORTED;
            break;
        case AwkCmdResponse::FAILED:
            cmdResponse = AwkCmdResponse::FAILED;
            break;
        case AwkCmdResponse::SUCCESS:
            cmdResponse = AwkCmdResponse::SUCCESS;
            break;
        default:
            cmdResponse = -1;
    }

    return cmdResponse;
}

/**
 * @brief Sets the NMEA output frequency of the data fields.
 *
 * @details See page 12 of the PMTK_A11 document in doc/GPS/ under Packet Type:
 * 314 PMTK_API_SET_NMEA_OUTPUT for more information.
 */
void UltimateGPS::setNmeaOutput ()
{
    const char *nmeaSetting
        = "$PMTK314,1,1,1,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0*2C\r\n";
    gpsSerial->print (nmeaSetting);
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
uint8_t UltimateGPS::calculateXorChecksum (const char *string)
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
bool UltimateGPS::hasValidXorChecksum (const char *string)
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
