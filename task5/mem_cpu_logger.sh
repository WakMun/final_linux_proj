#!/bin/bash

#this script creates a tmpfs and mounts it, if already mounted, appends a log entry


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

if [ ! -e /tmp/sensor_logs/distance_log ]; then
    echo "not found"
    mkdir -p /tmp/sensor_logs
    mount -t tmpfs -o size=20m tmpfs /tmp/sensor_logs
    touch /tmp/sensor_logs/distance_log
    #stat /tmp/sensor_logs/distance_log
fi

MEM_USAGE=$(awk '/^Mem/ {print $3}' <(free -m))
CPU_USAGE=$(awk '{u=$2+$4; t=$2+$4+$5; if (NR==1){u1=u; t1=t;} else print ($2+$4-u1) * 100 / (t-t1) " %"; }' \
<(grep 'cpu ' /proc/stat) <(sleep 1;grep 'cpu ' /proc/stat))
CURR_TIME=$(date +%X)
NEW_LOG="${CURR_TIME}  Mem Usage: ${MEM_USAGE} MB, CPU Usage: ${CPU_USAGE}"

echo ${NEW_LOG} >> /tmp/sensor_logs/distance_log
#echo ${NEW_LOG} | systemd-cat -t Mem_CPU_logger -p info
echo ${NEW_LOG}