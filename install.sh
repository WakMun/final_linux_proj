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


echo -e "${BOLD}${GREEN}Installing LED_1sec_1sec.sh${NC}"
mkdir -p ${INSTALL_PATH}/blinker
cp -v ./task2/LED_1sec_1sec.sh ${INSTALL_PATH}/blinker/LED_1sec_1sec.sh
echo "Installed: ${INSTALL_PATH}/blinker/LED_1sec_1sec.sh" | systemd-cat -t install.sh -p info

