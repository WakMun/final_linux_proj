/**
 * @file pdc.h
 * @brief definition of pdc class. 
 * @version 0.1
 * @date 2020-11-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __PDC_H__
#define __PDC_H__

/**
 * @brief Pdc class: This is responsible for interperating ultrasonic sensor readings 
 * 
 */
class Pdc
{
public:

    /**
     * @brief Three warning levels are defined.
     * 
     */
    enum class warn_lvl
    {
        OK,         // for distances moe than 100
        WARNING,    // for distances more than 30 cm but less than 100 cm
        STOP        // for distance less than 30 cm
    };

    /**
     * @brief Convert the sensor reading to a corresponding warning level.
     * 
     * @param distance 
     * @return warn_lvl 
     */
    warn_lvl get_warning_level(int distance);
};

#endif //__PDC_H__