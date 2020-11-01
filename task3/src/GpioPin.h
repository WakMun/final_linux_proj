/**
 * @file GpioPin.h
 * @brief definition of GPIOPin class for interfacing with pins directly.
 * @version 0.1
 * @date 2020-11-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// adopted from https://github.com/perimeno/LIO

#ifndef __GPIOPIN_H__
#define __GPIOPIN_H__

#include <string>
#include <fstream>
#include <memory>

/**
 * @brief Low level abstraction class to directly manipulate GPIO
 * on pin level using sysfs
 * 
 */
class GpioPin
{
private:

    uint32_t _pinNo;
    std::string const basePath;
    std::string pinBasePath;
    bool isPermissionOk();
    void waitForPermission();

public:

    enum class Direction
    {
        In,
        Out,
        High,
        Low
    };
    /**
     * @brief Set the Direction of a pin.
     * It can have four possible values as per enum Direction.
     * 
     * @param dir 
     */
    void SetDirection(Direction dir);

    void SetActiveLow(bool isActiveLow);
    
    /**
     * @brief Construct a new Gpio Pin object
     * 
     * @param pinNo : Pin number
     * @param dir : enum Direction
     */
    GpioPin(uint32_t pinNo, Direction dir);
    ~GpioPin();

    /**
     * @brief Read value from a pin that was initialized as input.
     * 
     * @return true 
     * @return false 
     */
    bool ReadVal();

    /**
     * @brief Write a bit value to a pin which was initialized as output. 
     * 
     * @param val : boolean
     */
    void WriteVal(bool val);

    /**
     * @brief Get the Pin Base Path
     * 
     * @return std::string 
     */
    std::string GetPinBasePath();

    /**
     * @brief Get the Pin No 
     * 
     * @return uint32_t 
     */
    uint32_t GetPinNo();
};

#endif // __GPIOPIN_H__
