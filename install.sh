#!/bin/bash

#set -o xtrace
RED='\033[31m'
GREEN='\033[92m'
BOLD='\033[1m'
NC='\033[0m' # No Color

echo 
echo -e "${BOLD}${GREEN}Running Install Script${NC}"
echo 

echo "Install Script Started." | systemd-cat -t install.sh -p info
#journalctl -t install.sh