/**
 * @file UI.cpp
 * @brief implementation for Ui class
 * @version 0.1
 * @date 2020-11-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "UI.h"

Ui::Ui()
{
    display_texts.insert({Pdc::warn_lvl::OK,      "-----OK----"});
    display_texts.insert({Pdc::warn_lvl::WARNING, "--WARNING--"});
    display_texts.insert({Pdc::warn_lvl::STOP,    "----STOP---"});
}

int Ui::print_dist_level(int dist, Pdc::warn_lvl wrn_lvl)
{
    std::cout << display_texts[wrn_lvl] << " Distance: " << dist << " cm"<< std::endl;
    return 0;
}