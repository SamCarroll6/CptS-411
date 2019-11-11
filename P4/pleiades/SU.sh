#! /bin/sh


if [ -z "$2" ]
then
    ./hwrun.sh 1000000 1
    sleep 2
    ./hwrun.sh 1000000 2
    sleep 2
    ./hwrun.sh 1000000 4
    sleep 2
    ./hwrun.sh 1000000 8
    sleep 2
else
    ./hwrun.sh $1 1
    sleep 2
    ./hwrun.sh $1 2
    sleep 2
    ./hwrun.sh $1 4
    sleep 2
    ./hwrun.sh $1 8
fi