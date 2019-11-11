#!/bin/sh

gcc -o main -fopenmp main.c -lm


if [ -z "$2" ]
then
	sbatch -N1 ./main 1024 4
else
	sbatch -N1 ./main $1 $2
fi