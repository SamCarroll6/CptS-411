#!/bin/sh

gcc-9 -o main -fopenmp main.c


if [ -z "$2" ]
then
	sbatch -N1 ./main 1024 4
else
	sbatch -N1 ./main $1 $2
fi