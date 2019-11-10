#!/bin/sh

gcc -o main -fopenmp main.c -lm


if [ -z "$2" ]
then
    sbatch -N1 ./main 1000000 1
    sleep 2
    sbatch -N1 ./main 1000000 2
    sleep 2
    sbatch -N1 ./main 1000000 4
    sleep 2
    sbatch -N1 ./main 1000000 8
    sleep 2
else
    sbatch -N1 ./main $1 1
    sleep 2
    sbatch -N1 ./main $1 2
    sleep 2
    sbatch -N1 ./main $1 4
    sleep 2
    sbatch -N1 ./main $1 8
fi