#!/bin/bash


###################################
# Intializers / Definitions
###################################
# Common path for all GPIO access
BASE_GPIO_PATH=/sys/class/gpio

# Assign a name to GPIO pin number
RED=23

# Assign names to states
ON="1"
OFF="0"


###################################
# Utility Functions
###################################
# Utility function to export a pin if not already exported
exportPin()
{
    if [ ! -e /sys/class/gpio/gpio$1 ]; then
        echo $1 > /sys/class/gpio/export
    fi
}

# Utility function to export a pin if not already exported
unexportPin()
{
    if [ ! -e /sys/class/gpio/gpio$1 ]; then
        echo $1 > /sys/class/gpio/unexport
    fi
}

# Utility function to set a pin as an output
setOutput()
{
    echo "out" > /sys/class/gpio/gpio$1/direction
}

# Utility function to change state of a light
setLightState()
{
    echo $2 > /sys/class/gpio/gpio$1/value
}



###################################
# Ctrl-C handler for clean shutdown
###################################
shutdown()
{
    setLightState $RED $OFF
    unexportPin $RED
    exit 0
}

###################################
## Main()
###################################

trap shutdown SIGINT
trap shutdown SIGTERM

# Export pins so that we can use them
exportPin $RED

# Set pins as outputs
setOutput $RED

#Calculate the sleep time based on cmd line args
#SLEEP_SEC=`echo 3k $1 2000 /p | dc`
SLEEP_SEC=1

# Loop forever until user presses Ctrl-C
for i in 1 2
do
    # Red
    setLightState $RED $ON
    sleep $SLEEP_SEC
    setLightState $RED $OFF
    sleep $SLEEP_SEC
    
done

shutdown
