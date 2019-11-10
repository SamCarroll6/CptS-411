#!/bin/sh

gcc -o main -fopenmp main.c

sbatch -N1 ./main 1000000 1
sleep 2
sbatch -N1 ./main 2000000 2
sleep 2
sbatch -N1 ./main 4000000 4
sleep 2
sbatch -N1 ./main 8000000 8
sleep 2
sbatch -N1 ./main 16000000 16
sleep 2
sbatch -N1 ./main 32000000 32
sleep 2
sbatch -N1 ./main 64000000 64

