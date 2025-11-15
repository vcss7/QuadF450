/**
 * @file I2CDevice.cpp
 * @author Victor Solis
 * @date 2025-1l-11
 * @version 1.0.0
 * @brief Logger class implementation
 */

#include "Logger.hpp"

using namespace Q4;

Logger::Logger (usb_serial_class *usb_serial, usb_serial_baud_t baud)
{
    if (usb_serial != NULL)
    {
        _usb_serial = usb_serial;
        _usb_serial->begin (baud);
    }
}

size_t Logger::write (uint8_t b)
{
    size_t count = 0;

    if (_usb_serial != NULL)
    {
        count += _usb_serial->write (b);
    }

    return count;
}
size_t Logger::write (const uint8_t *buffer, size_t size)
{
    size_t count = 0;

    if (_usb_serial != NULL)
    {
        count += _usb_serial->write (buffer, size);
    }

    return count;
}

int Logger::availableForWrite (void)
{
    size_t numOpenedInterfaces = 0;

    if (_usb_serial != NULL)
    {
        numOpenedInterfaces += 1;
    }

    return numOpenedInterfaces;
}
void Logger::flush ()
{
    if (_usb_serial != NULL)
    {
        _usb_serial->flush ();
    }

    return;
}
