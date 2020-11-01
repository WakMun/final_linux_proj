/**
 * @file pdc.cpp
 * @brief implementation of pdc class
 * @version 0.1
 * @date 2020-11-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "pdc.h"

Pdc::warn_lvl Pdc::get_warning_level(int dist)
{
    if (dist >= 100)
        return warn_lvl::OK;
    else if (dist >= 30)
        return warn_lvl::WARNING;
    else
        return warn_lvl::STOP;
}