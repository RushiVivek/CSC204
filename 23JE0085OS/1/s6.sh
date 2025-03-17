# !bin/bash
echo -n "Enter birth year: "
read Y
YEAR=`date +'%Y'`
if [ $Y -gt $YEAR ]
then
    echo "Invalid Year"
else
    AGE=`expr $YEAR - $Y`
    echo "Age is $AGE"
fi
