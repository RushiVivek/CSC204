# !/bin/bash

echo -n "Enter number 1: "
read A
echo -n "Enter number 2: "
read B
C=`expr $A + $B`
echo "Sum is: $C"
