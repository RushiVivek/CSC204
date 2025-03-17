# !/bin/bash
echo -n "Enter the number of numbers to be printed: "
read N
A=0
B=1
if [ $N -ge 1 ]
then
    echo -n "0 "
fi
if [ $N -ge 2 ]
then
    echo -n "1 "
fi

if [ $N -gt 2 ]
then
    for (( i=2 ; i<$N ; i++ ));
    do
        C=`expr $A + $B`
        echo -n "$C "
        A=$B
        B=$C
    done
fi
echo "."
