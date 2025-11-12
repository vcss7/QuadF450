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
     * @brief Contstructor for Logger class; pass in any interfaces here.
     */
    Logger (HardwareSerial *uart);

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
     * @brief UART interface to write to.
     */
    HardwareSerial *_uart = NULL;
};

}  // namespace Q4
