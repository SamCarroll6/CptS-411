#!/bin/sh

gcc -o main -fopenmp main.c -lm

sbatch -N1 ./hwrun.sh 1000000 1
sleep 2
sbatch -N1 ./hwrun.sh 2000000 2
sleep 2
sbatch -N1 ./hwrun.sh 4000000 4
sleep 2
sbatch -N1 ./hwrun.sh 8000000 8
sleep 2
sbatch -N1 ./hwrun.sh 16000000 16
sleep 2
sbatch -N1 ./hwrun.sh 32000000 32
sleep 2
sbatch -N1 ./hwrun.sh 64000000 64

