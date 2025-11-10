/**
 * @file I2CDevice.cpp
 * @author Victor Solis
 * @date 2025-10-14
 * @version 1.0.0
 * @brief I2CDevice class implementation
 */

#include "I2CDevice.hpp"

using namespace Q4;

I2CDevice::I2CDevice (TwoWire* wire, SemaphoreHandle_t* mutex, uint32_t freq,
                      uint8_t addr, uint8_t sdaPin, uint8_t sclPin,
                      uint16_t timeoutMs)
{
    _wire      = wire;
    _freq      = freq;
    _addr      = addr;
    _sdaPin    = sdaPin;
    _sclPin    = sclPin;
    _timeoutMs = timeoutMs;
	_mutex     = mutex;
}

I2CDevice::ReturnCode I2CDevice::open ()
{
	if (*_mutex == NULL)
	{
		abort ();
	}
	
	if (xSemaphoreTake (*_mutex, (TickType_t) 10) == pdFALSE)
	{
		return Q4::I2CDevice::ReturnCode::Timeout;
	}

	// configure i2c bus
	_wire->end ();
	_wire->setClock (_freq);
	_wire->setSDA (_sdaPin);
	_wire->setSCL (_sclPin);
	_wire->begin ();

	xSemaphoreGive (*_mutex);

    return Q4::I2CDevice::ReturnCode::Success;
}

I2CDevice::ReturnCode I2CDevice::close ()
{
	if (*_mutex == NULL)
	{
		abort ();
	}

	if (xSemaphoreTake (*_mutex, (TickType_t) 10) == pdFALSE)
	{
		return Q4::I2CDevice::ReturnCode::Timeout;
	}

	xSemaphoreGive (*_mutex);

    return Q4::I2CDevice::ReturnCode::Success;
}

I2CDevice::ReturnCode I2CDevice::read (uint8_t* buffer, size_t length)
{
	if (*_mutex == NULL)
	{
		abort ();
	}

	if (buffer == NULL || length == 0)
	{
		return Q4::I2CDevice::ReturnCode::Error;
	}

	if (xSemaphoreTake (*_mutex, (TickType_t) 10) == pdFALSE)
	{
		return Q4::I2CDevice::ReturnCode::Timeout;
	}

	xSemaphoreGive (*_mutex);

    return Q4::I2CDevice::ReturnCode::Success;
}

I2CDevice::ReturnCode I2CDevice::write (const uint8_t* buffer, size_t length)
{
	if (*_mutex == NULL)
	{
		abort ();
	}

	if (buffer == NULL || length == 0)
	{
		return Q4::I2CDevice::ReturnCode::Error;
	}

	if (xSemaphoreTake (*_mutex, (TickType_t) 10) == pdFALSE)
	{
		return Q4::I2CDevice::ReturnCode::Timeout;
	}

	xSemaphoreGive (*_mutex);

    return Q4::I2CDevice::ReturnCode::Success;
}
