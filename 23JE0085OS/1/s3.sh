# !/bin/bash
echo -n "Enter the number: "
read NUM
M=`expr $NUM % 2`
if [ $M == 0 ]
then
    echo "Number is Even"
else
    echo "Number is Odd"
fi
