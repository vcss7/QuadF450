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

#include "Peripheral.hpp"

#include <FreeRTOS.h>
#include <Wire.h>
#include <semphr.h>

namespace Q4
{

/**
 * @brief Adaptor for TwoWire object to add support for multi-task I2C
 * communication.
 */
class I2CDevice : public Peripheral
{
public:
    /*
     * @brief Construct the I2CDevice object with desired initializations
     */
    I2CDevice (TwoWire* wire, SemaphoreHandle_t* mutex, uint32_t freq,
               uint8_t addr, uint8_t sdaPin, uint8_t sclPin,
               uint16_t timeoutMs);

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
    I2CDevice () = default;

    /**
     * @brief Pointer to the TwoWire instance for I2C communication.
     */
    TwoWire* _wire;

    /**
     * @brief A mutex task handle for managing access to the TwoWire resource.
     */
    SemaphoreHandle_t* _mutex = NULL;

private:
    /**
     * @brief Delete copy constructor
     * @note MISRA C++ 2008 Rule 12-8-1: A copy constructor shall only
     * initialize its base classes and the non-static members of the class of
     * which it is a member.
     */
    I2CDevice (const I2CDevice&) = delete;

    /**
     * @brief Delete copy assignment operator
     * @note MISRA C++ 2008 Rule 12-8-2: The copy assignment operator shall be
     * declared protected or private in an abstract class.
     */
    I2CDevice& operator= (const I2CDevice&) = delete;

    /*
     * @brief The frequncy of the clock pin for the I2C bus
     */
    uint32_t _freq;

    /*
     * @beief The I2C address of the I2C device
     */
    uint8_t _addr;

    /*
     * @brief The I2C data pin
     */
    uint8_t _sdaPin;

    /*
     * @brief The I2C clock pin
     */
    uint8_t _sclPin;

    /*
     * @brief The maximum amount of milliseconds to wait for communication for
     * this device.
     */
    uint16_t _timeoutMs;
};

}  // namespace Q4
