/**
 * @file UI.h
 * @brief Header for Ui class
 * @version 0.1
 * @date 2020-11-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __UI_H__
#define __UI_H__

#include <iostream>
#include <map>
#include <string>
#include "pdc.h"

/**
 * @brief A simple calss to implement user interface.
 * 
 */
class Ui
{
    std::map<Pdc::warn_lvl, std::string> display_texts;

public:
    Ui();

    /**
     * @brief Print distance and the label for the corresponding zone.
     * 
     * @param distance 
     * @return int 
     */
    int print_dist_level(int distance, Pdc::warn_lvl);
};

#endif //__UI_H__