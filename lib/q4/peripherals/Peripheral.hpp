/**
 * @file Peripheral.hpp
 * @brief Abstract interface for peripheral device operations.
 * @author Victor Solis
 * @date 2025-10-09
 * @version 1.0.0
 */

#pragma once

namespace Q4
{

class Peripheral
{
public:
    virtual void open ()  = 0;
    virtual void close () = 0;
    virtual void read ()  = 0;
    virtual void write () = 0;

    virtual ~Peripheral () = default;
};

}  // namespace Q4
