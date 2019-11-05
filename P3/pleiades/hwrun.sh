#!/bin/sh

set -e

if [ -z "$1" ]
then
	mpicc -o main ./main.c
else
	mpicc -o $1 ./$1.c
fi

mpirun -np 8 ./main 15 37 24 9241 20000
