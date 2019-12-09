#! /bin/sh


if [ -z "$1" ]
then
    sbatch -N1 ./hwrun.sh 10000 10 1 ../Paths/web-Google_sorted.txt
    sleep 2
    sbatch -N1 ./hwrun.sh 10000 10 2 ../Paths/web-Google_sorted.txt
    sleep 2
    sbatch -N1 ./hwrun.sh 10000 10 4 ../Paths/web-Google_sorted.txt
    sleep 2
    sbatch -N1 ./hwrun.sh 10000 10 8 ../Paths/web-Google_sorted.txt
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