/**
 * @file Peripheral.hpp
 * @brief Abstract interface for peripheral device operations.
 * @author Victor Solis
 * @date 2025-10-09
 * @version 1.1.0
 */

#pragma once

#include <cstddef>
#include <cstdint>

namespace Q4
{

/**
 * @brief An interface of peripheral devices.
 * @details Derive from this class a common interface that can be used for
 * interfacing with peripheral devices.
 */
class Peripheral
{
public:
    /**
     * @brief An enumeration type for function return codes.
     * @note MISRA C++ 2023 Rule 10-2-1: An enumeration shall be defined with
     * an explicit underlying type.
     */
    enum class ReturnCode : uint8_t
    {
        Success = 0,
        Error   = 1,
        Timeout = 2,
    };

    /**
     * @brief Used for preparing and intializing a port to a peripheral device.
     * @return ReturnCode
     */
    virtual ReturnCode open () = 0;

    /**
     * @brief Used for closing and deinitializing a port to a peripheral device.
     * @return ReturnCode
     */
    virtual ReturnCode close () = 0;

    /**
     * @brief Used to read from a peripheral device.
     * @param buffer The buffer to write the bytes read.
     * @param length The number of bytes to read.
     * @return ReturnCode
     */
    virtual ReturnCode read (uint8_t* buffer, size_t length) = 0;

    /**
     * @brief Used to write to a peripheral device.
     * @param buffer The buffer to write to the device.
     * @param length The number of bytes to write.
     * @return ReturnCode
     */
    virtual ReturnCode write (const uint8_t* buffer, size_t length) = 0;

    /**
     * @brief Defualt contructor to invoke the derived class's destructor.
     */
    virtual ~Peripheral () = default;

protected:
    /**
     * @brief Defualt contructor to invoke the derived class's constructor.
     */
    Peripheral () = default;

private:
    /**
     * @brief Delete copy constructor
     * @note MISRA C++ 2008 Rule 12-8-1: A copy constructor shall only
     * initialize its base classes and the non-static members of the class of
     * which it is a member.
     */
    Peripheral (const Peripheral&) = delete;

    /**
     * @brief Delete copy assignment operator
     * @note MISRA C++ 2008 Rule 12-8-2: The copy assignment operator shall be
     * declared protected or private in an abstract class.
     */
    Peripheral& operator= (const Peripheral&) = delete;
};

}  // namespace Q4
