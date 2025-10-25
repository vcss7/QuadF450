/**
 * @file I2CDevice.cpp
 * @author Victor Solis
 * @date 2025-10-14
 * @version 1.0.0
 * @brief I2CDevice class implementation
 */

#include "I2CDevice.hpp"

using namespace Q4;

I2CDevice::I2CDevice (TwoWire* wire, uint32_t freq, uint8_t addr,
                      uint8_t sdaPin, uint8_t sclPin, uint16_t timeoutMs)
{
    _wire      = wire;
    _freq      = freq;
    _addr      = addr;
    _sdaPin    = sdaPin;
    _sclPin    = sclPin;
    _timeoutMs = timeoutMs;
    _mutex     = xSemaphoreCreateBinary ();
}

I2CDevice::ReturnCode I2CDevice::open ()
{
    Q4::I2CDevice::ReturnCode result = Q4::I2CDevice::ReturnCode::Unknown;

    return result;
}

I2CDevice::ReturnCode I2CDevice::close ()
{
    I2CDevice::ReturnCode result = I2CDevice::ReturnCode::Unknown;

    return result;
}

I2CDevice::ReturnCode I2CDevice::read (uint8_t* buffer, size_t length)
{
    I2CDevice::ReturnCode result = I2CDevice::ReturnCode::Unknown;

    return result;
}

I2CDevice::ReturnCode I2CDevice::write (const uint8_t* buffer, size_t length)
{
    I2CDevice::ReturnCode result = I2CDevice::ReturnCode::Unknown;

    return result;
}
