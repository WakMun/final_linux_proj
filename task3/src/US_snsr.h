/**
 * @file US_snsr.h
 * @brief Header for Ui class
 * @version 0.1
 * @date 2020-11-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __US_SNSR_H__
#define __US_SNSR_H__

#include "GpioPin.h"

/**
 * @brief Ultrasonic Sensor interface. This class implements the low level functions 
 * to convert the timing measurements from echos to distance measurements.
 */
class US_snsr
{
    //pointer to store the gpio pin for triggereing the ultrasonic sensor.
    std::unique_ptr<GpioPin> TrigPin;

    //pointer to store the gpio pin for getting the echo duration from ultrasonic sensor.
    std::unique_ptr<GpioPin> EchoPin;

public:
    US_snsr() = delete;
    
    /**
     * @brief Construct a new interface for ultrasonic sensor
     * 
     * @param trigPin : Pin No as integer 
     * @param echoPin : Pin No as integer
     */
    US_snsr(int trigPin, int echoPin);


    /**
     * @brief Get the dist in centimeters from the obstacle in front of ultrasonic sensor.
     * 
     * @return int : centimeters
     */
    int get_dist_cm();
};

#endif //__US_SNSR_H__
