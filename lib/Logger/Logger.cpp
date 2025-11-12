/**
 * @file I2CDevice.cpp
 * @author Victor Solis
 * @date 2025-1l-11
 * @version 1.0.0
 * @brief Logger class implementation
 */

#include "Logger.hpp"

using namespace Q4;

Logger::Logger (HardwareSerial *uart)
{
    _uart = uart;
}

size_t Logger::write (uint8_t b)
{
    return 0;
}
size_t Logger::write (const uint8_t *buffer, size_t size)
{
    return 0;
}

int Logger::availableForWrite (void)
{
    return 0;
}
void flush ()
{
    return;
}
