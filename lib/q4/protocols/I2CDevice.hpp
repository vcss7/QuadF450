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

#include <q4/peripheral/Peripheral.hpp>

namespace Q4
{

class I2CDevice : public Peripheral
{
    public:
        virtual void open ()  = 0;
        virtual void close () = 0;
        virtual void read ()  = 0;
        virtual void write () = 0;

    private:
};

}

