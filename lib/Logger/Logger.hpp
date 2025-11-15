/**
 * @file Logger.hpp
 * @author Victor Solis
 * @date 2025-11-11
 * @version 1.0.0
 * @brief class defintion of the logging system with different outputs
 *
 * This logging system outputs log messages to different streams
 */

#pragma once

#include <Arduino.h>

namespace Q4
{

/**
 * @brief Class for logging messages
 */
class Logger : public Print
{
public:
    /**
     * @brief An alias to describe the usb serial baud rate
     */
    typedef int32_t usb_serial_baud_t;

    /**
     * @brief Contstructor for Logger class; pass in any interfaces here.
     */
    Logger (usb_serial_class *usb_serial, usb_serial_baud_t baud);

    /**
     * @brief The base write function.
     * @param b The byte to write to all interfaces.
     * @return The amount of bytes written.
     */
    size_t write (uint8_t b);

    /**
     * @brief The base write function.
     * @param buffer The buffer to write to all interfaces.
     * @param size The size of buffer.
     * @return The amount of bytes written.
     */
    size_t write (const uint8_t *buffer, size_t size);

    /**
     * @brief Checks to see how many interfaces are available to write.
     */
    int availableForWrite (void);

    /**
     * @brief Flushes the interface streams.
     */
    void flush ();

protected:
    /**
     * @brief Default constructor.
     */
    Logger () = default;

private:
    /*
     * @brief USB serial interface to write to.
     */
    usb_serial_class *_usb_serial = NULL;
};

}  // namespace Q4
