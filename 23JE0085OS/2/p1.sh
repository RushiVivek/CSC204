# !/bin/bash
echo -n "Enter 1st number: "
read A
echo -n "Enter 2nd number: "
read B
echo -n "Enter 3rd number: "
read C

if [ $B -lt $C ]
then
    B=$C
fi

if [ $A -lt $B ]
then
    A=$B
fi

echo "The largest of the three numbers is: $A"
