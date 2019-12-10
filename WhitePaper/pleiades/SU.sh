#! /bin/sh


if [ -z "$1" ]
then
    sbatch -N1 ./hwrun.sh 1000 0 8
    sleep 2
    sbatch -N1 ./hwrun.sh 1000 10 8
    sleep 2
    sbatch -N1 ./hwrun.sh 1000 50 8
    sleep 2
    sbatch -N1 ./hwrun.sh 1000 90 8
    sleep 2
else
    sbatch -N1 ./hwrun.sh $1 1
    sleep 2
    sbatch -N1 ./hwrun.sh $1 2
    sleep 2
    sbatch -N1 ./hwrun.sh $1 4
    sleep 2
    sbatch -N1 ./hwrun.sh $1 8
fi