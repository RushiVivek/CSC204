# !/bin/bash
echo -n "Enter the number: "
read N
fl=0

for (( i=2 ; i<$N ; i++ ));
do
    C=`expr $N % $i`
    if [ $C -eq 0 ]
    then
        fl=1
        break
    fi
done

if [ $fl -ne 1 ]
then
    echo "Number is a Prime."
else
    echo "Number is not a Prime."
fi
