/**
 * @file GpioPin.cpp
 * @brief implementation of GPIOPin class.
 * @version 0.1
 * @date 2020-11-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

// adopted from https://github.com/perimeno/LIO

#include "GpioPin.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

GpioPin::GpioPin(uint32_t pinNo, GpioPin::Direction dir) : _pinNo(pinNo), basePath("/sys/class/gpio"), pinBasePath("")
{
    std::stringstream ss;
    ss << basePath << "/gpio" << _pinNo << "/";
    pinBasePath = ss.str();

    std::ofstream exp(basePath + "/export");
    if (!exp.good())
    {
        std::cerr << "unable to open IO port - " << pinNo << std::endl;
        throw std::runtime_error("output open error");
    }
    exp << std::to_string(_pinNo) << std::flush;
    exp.close();
    waitForPermission();

    GpioPin::SetDirection(dir);
}

GpioPin::~GpioPin()
{
    std::ofstream unExp(basePath + "/unexport");
    unExp << std::to_string(_pinNo);
}

void GpioPin::SetDirection(GpioPin::Direction dir)
{
    std::ofstream direction(pinBasePath + "direction");
    if (!direction.good())
    {
        throw std::runtime_error("Unable to open direction");
    }
    switch (dir)
    {
    case Direction::In:
        direction << "in";
        break;
    case Direction::Out:
        direction << "out";
        break;
    case Direction::High:
        direction << "high";
        break;
    case Direction::Low:
        direction << "low";
        break;
    }
}

void GpioPin::SetActiveLow(bool isActiveLow)
{
    std::ofstream activeLow(pinBasePath + "active_low");
    if (!activeLow.good())
    {
        std::cerr << "Unable to open active_low file - " << _pinNo << std::endl;
        throw std::runtime_error("Unable to open active_low");
    }
    activeLow << (isActiveLow ? "1" : "0");
}

bool GpioPin::ReadVal()
{
    std::ifstream value(pinBasePath + "value");
    if (!value.good())
    {
        std::cerr << "Unable to open value for read - " << _pinNo;
        throw std::runtime_error("Unable to open value for read");
    }
    bool ret;
    value >> ret;
    return ret;
}

void GpioPin::WriteVal(bool val)
{
    std::ofstream value(pinBasePath + "value");
    if (!value.good())
    {
        std::cerr << "Unable to open value for write - " << _pinNo << std::endl;
        throw std::runtime_error("Unable to open value for write");
    }
    value << val;
}

uint32_t GpioPin::GetPinNo()
{
    return _pinNo;
}

std::string GpioPin::GetPinBasePath()
{
    return pinBasePath;
}

void GpioPin::waitForPermission()
{
    for (int i = 0; i < 10 && !isPermissionOk(); ++i)
    { //hack to wait until permissions are set correctly on subdescriptors during gdb debug
        //std::cout << "wait for permission on " << pinBasePath << std::endl;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
    }
}

bool GpioPin::isPermissionOk()
{
    struct stat st;
    bool ret = false;
    if (stat(pinBasePath.c_str(), &st) == 0)
    {
        mode_t perm = st.st_mode;

        ret = (perm & (S_IRGRP | S_IWGRP | S_IXGRP)) == (S_IRGRP | S_IWGRP | S_IXGRP);
    }
    else
    {
        std::cerr << "unable to read file permission" << std::endl;
    }
    return ret;
}
