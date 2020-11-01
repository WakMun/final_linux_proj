/**
 * @file documentation.cpp
 * @brief File added to generate doxygen documentation 
 * @version 0.1
 * @date 2020-11-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */


/*! \mainpage Archtecture Description
 *
 * \section overview_sec Overview
 *
 * "Task 3" consists of a simple park distance control application (pdc). The main 
 * task is to measure the distance to the nearest obstacle in front of the ultra 
 * sonic sensor then classify it into three zones and show it on the user display (terminal).
 * The hardware to be used for this task is raspberry pi 4, where an ultrasonic sensor is
 * mounted on GPIO extension interface. 
 * 
 * \section Architecture
 * On basis of given requirements, application consists of following main components  (in order of
 * top-down design)
 *  - UI: This component presents the output to user in human readable form. It is implemented in 
 * class Ui.
 *  - PDC: This component implements simple functionality of classifying the distance into zones.
 * It is implemented in class Pdc.
 *  - Ultra Sonic Sensor: This component interfaces with ultrasonic sensor ie conducts the timing 
 * measurements to calculate the distance. This is implemented in class US_snsr.
 *  - GPIO Pin Interace: This components provides abstraction to provide an easy interface to
 * control gpio pins on raspberry pi using the sysfs interface. This component is the bottom
 * of design heirarchy. This is implemented in GpioPin.
 * 
 * The details of these components will be documented in the source code. 
 *
 * \section install_sec Installation
 * 
 * If the make is succesful, the following main binary is generated in the following 
 * relative path: ./build/pdc_app
 *
 * \section Expected Output
 * 
 * Expectation is that a simple text output is produced in terminal where the
 * progam is run. It should produce two pieces of information: 
 *  -# Distance to the obstacle present in front of UltraSonic Sensor 
 *  -# A zone. This is derived from the above distance
 *
 */
