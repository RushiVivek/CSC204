# !/bin/bash
echo -n "Enter temperature in Celsius: "
read TEMP

TEMPF=$(( ( $TEMP * 9 / 5 ) + 32 ))
echo "Temperature in Fahrenheit is $TEMPF"
