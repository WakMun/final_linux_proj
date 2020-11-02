#!/bin/bash

# install location
INSTALL_PATH=/opt/pdc

#set -o xtrace
RED='\033[31m'
GREEN='\033[92m'
BOLD='\033[1m'
NC='\033[0m' # No Color

echo -e "${BOLD}Running Install Script${NC}"


echo "Install Script Started." | systemd-cat -t install.sh -p info
#journalctl -t install.sh

# check if we are running with root permissions.
if [ "$EUID" -ne 0 ]; then
    echo -e "${RED}${BOLD}Must be run as root${NC}"
    echo "Must be run as root" | systemd-cat -t install.sh -p err
    exit 1
fi

if [ $SUDO_USER ]; then
    real_user=$SUDO_USER
else
    real_user=$(whoami)
fi

#sudo -u $real_user whoami

echo -e "${BOLD}${GREEN}Installing LED_1sec_1sec.sh (Task2)${NC}"
mkdir -p ${INSTALL_PATH}/blinker
cp -v ./task2/LED_1sec_1sec.sh ${INSTALL_PATH}/blinker/LED_1sec_1sec.sh
echo "Installed: ${INSTALL_PATH}/blinker/LED_1sec_1sec.sh" | systemd-cat -t install.sh -p info
echo



echo -e "${BOLD}${GREEN}Installing PDC App (Task3)${NC}"
if [ ! -e ./task3/build/pdc_app ]; then
    echo -e "./task3/build/main_app does not exist."
    echo -e "Trying to compile ..."
    pushd task3 > /dev/null
    sudo -u $real_user make all
    if [ $? -ne 0 ]; then
        popd > /dev/null
        echo -e "${BOLD}${RED}compilation failed. Please resolve the issue and then retry. ${NC}"
        exit 1
    fi
    popd > /dev/null
    echo -e "${BOLD}${GREEN}Success!${NC}"
fi
mkdir -p ${INSTALL_PATH}/pdc
cp -v ./task3/build/pdc_app ${INSTALL_PATH}/pdc/pdc_app
echo


echo -e "${BOLD}${GREEN}Installing PDC Service (Task4)${NC}"
cp -v ./task4/pdc.service /etc/systemd/system/pdc.service
systemctl daemon-reload
systemctl enable --now pdc.service
#journalctl -u pdc.service
echo

echo -e "${BOLD}${GREEN}Installing logger Service (Task5)${NC}"
mkdir -p -p ${INSTALL_PATH}/logger
cp -v ./task5/mem_cpu_logger.sh ${INSTALL_PATH}/logger/
chmod +x ${INSTALL_PATH}/logger/mem_cpu_logger.sh
cp -v ./task5/mem_cpu_logger.service /etc/systemd/system/
cp -v ./task5/mem_cpu_logger.timer /etc/systemd/system/
systemctl daemon-reload
systemctl enable --now mem_cpu_logger.timer
#journalctl -u mem_cpu_logger.sh -f
echo

echo -e "${BOLD}${GREEN}Installing Pdc Kernel Module (Task6)${NC}"
mkdir -p  /lib/modules/$(uname -r)/kernel/drivers/pdc
cp -v ./task6/pdcKern.ko /lib/modules/$(uname -r)/kernel/drivers/pdc/
echo "kernel/pdc/pdcKern.ko:" >> /lib/modules/$(uname -r)/modules.dep
depmod
echo "pdcKern" >> /etc/modules-load.d/modules.conf
