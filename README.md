# Final Project Linux Lab
This repository contains the final deliverable for Linux lab. A commit is added for every completed subtask. Also, where applicable, the deliverables for subtasks are found in respectively named subfolders.

## Task 1
* This repository is setup.

### Task 1A
* This readme is added.
* Install scripts is added.


## Task2 + 2A
* task2/LED_1sec_1sec.sh is added
* Install script is updated
    * Must be run as root
    * Installation path: /opt/pdc/blinker/LED_1sec_1sec.sh


## Task 3 + 3A
* task3 added which contains:
    * Architectural Documentation: ./html/index.html 
    * Makefile added for buliding 
* Install.sh updated to install pdc_app
    * location: /opt/pdc/pdc/pdc_app


## Task 4
* task4 added which contains:
    * service unit: pdc.service 
* install.sh updated to install and run the service at start up

## Task 5 + 5A
* task5 added which contains
    * mem_cpu_logger.timer
    * mem_cpu_logger.service
    * mem_cpu_logger.sh
* install.sh updated to install and enable timer/service unit 

## Task 6
* task6 folder added which contains
    * compiled kernel module: pdcKern.ko
    * Makefile for kernel module
    * source: pdcKern.c 
* install.sh updated to install pdcKern.ko so that it is active on boot

