/**
 * @file I2CDevice.hpp
 * @author Victor Solis
 * @date 2025-10-10
 * @version 1.0.0
 * @brief class defintion of the I2C protocol peripheral devices
 *
 * Classes can be derived from this class to interface with peripheral devices
 * and guarantee thread safety in real time devices.
 */

#pragma once

#include "../peripherals/Peripheral.hpp"
#include <Wire.h>

namespace Q4
{

/**
 * @brief Adaptor for TwoWire object to add support for multi-task I2C
 * communication.
 */
class I2CDevice : public Peripheral
{
public:
    /**
     * @struct I2CConfig
     * @brief Configuration parameters for I2C communication.
     */
    struct I2CConfig
    {
        uint32_t frequency;
        uint8_t address;
        uint8_t sdaPin;
        uint8_t sclPin;
        uint16_t timeoutMs;
    };

    /**
     * @brief Initializes and sets I2C configurations to communicate with
     * a device.
     * @return ReturnCode exit status
     */
    ReturnCode open ();

    /**
     * @brief Deinitializes and closes communication with a device.
     * @return ReturnCode
     */
    ReturnCode close ();

    /**
     * @brief Used to read from an I2C device.
     * @param buffer The buffer to write the bytes read.
     * @param length The number of bytes to read
     * @return ReturnCode exit status
     */
    ReturnCode read (uint8_t* buffer, size_t length);

    /**
     * @brief Used to read from an I2C device.
     * @param buffer The buffer to write the bytes read.
     * @param length The number of bytes to read
     * @return ReturnCode exit status
     */
    ReturnCode write (const uint8_t* buffer, size_t length);

protected:
    /**
     * @brief Default constructor to invoke the derived class's constructor.
     */
    I2CDevice() = default;

    /**
     * @brief Pointer to the TwoWire instance for I2C communication.
     */
    TwoWire* _wire;

    /**
     * @brief Configuration parameters for I2C communication.
     */
    I2CConfig _config;

private:
    /**
     * @brief Delete copy constructor
     * @note MISRA C++ 2008 Rule 12-8-1: A copy constructor shall only
     * initialize its base classes and the non-static members of the class of
     * which it is a member.
     */
    I2CDevice(const I2CDevice&) = delete;

    /**
     * @brief Delete copy assignment operator
     * @note MISRA C++ 2008 Rule 12-8-2: The copy assignment operator shall be
     * declared protected or private in an abstract class.
     */
    I2CDevice& operator=(const I2CDevice&) = delete;
};

}

