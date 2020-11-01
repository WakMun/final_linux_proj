/**
 * @file main_app.cpp
 * @brief starting point of the application.
 * @version 0.1
 * @date 2020-11-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

//#include "GpioPin.h"
#include "US_snsr.h"
#include "pdc.h"
#include "UI.h"
#include <chrono>
#include <thread>
#include <iostream>
using namespace std::chrono_literals;
int main()
{

    // gpioPin LED(23, gpioPin::Direction::Out);

    // for (int i = 0; i < 4; i++)
    // {
    //     
    //     LED.WriteVal(true);
    //     std::this_thread::sleep_for(500ms);
    //     LED.WriteVal(false);
    //     std::this_thread::sleep_for(500ms);
    // }

    US_snsr myus_snsr(18, 24);
    Pdc my_pdc;
    Ui my_ui;
    int dist;

    while (true)
    {
        //std::cout << "distance: " << myus_snsr.get_dist_cm() << std::endl;
        dist = myus_snsr.get_dist_cm();
        my_ui.print_dist_level(dist, my_pdc.get_warning_level(dist));
        std::this_thread::sleep_for(500ms);
    }

    return 0;

}
