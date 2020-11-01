/**
 * @file US_snsr.cpp
 * @brief Implementation of Ui class
 * @version 0.1
 * @date 2020-11-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#include "US_snsr.h"
#include "GpioPin.h"
#include <chrono>
#include <thread>

US_snsr::US_snsr(int trigPin, int echoPin)
{
    TrigPin = std::make_unique<GpioPin>(trigPin, GpioPin::Direction::Out);
    EchoPin = std::make_unique<GpioPin>(echoPin, GpioPin::Direction::In);
    TrigPin->WriteVal(false);
}

using namespace std::chrono_literals;
using namespace std::chrono;

int US_snsr::get_dist_cm()
{

    typedef high_resolution_clock Time;
    typedef milliseconds ms;
    typedef duration<float> d_sec;

    TrigPin->WriteVal(true);
    std::this_thread::sleep_for(10us);
    TrigPin->WriteVal(false);

    
    auto t0 = Time::now();
    ms wait_ms = duration_cast<ms>(t0 - t0);

    //Wait for the echo pin to go high (maximum 20ms)
    while (false == EchoPin->ReadVal() && wait_ms.count() < 20)
    {

        wait_ms = duration_cast<ms>(Time::now() - t0);
    }

    if (wait_ms.count() >= 20)
        return -1;

    auto start_pulse = Time::now();

    t0 = Time::now();
    wait_ms = duration_cast<ms>(t0 - t0);

    //Wait for the echo pin to go low (maximum 20ms)
    while (true == EchoPin->ReadVal() && wait_ms.count() < 20)
    {
        wait_ms = duration_cast<ms>(Time::now() - t0);
    }

    auto end_pulse = Time::now();

    if (wait_ms.count() >= 20)
        return -1;

    d_sec pulse_length = end_pulse - start_pulse;

    // get centimeters from duration on basis of speed of sound
    double cms = (pulse_length.count() * 34300) / 2;

    if (cms < 2 || cms > 300)
        cms = -1;

    return (int)cms;
}
