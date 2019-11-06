#!/bin/sh

set -e


mpicc -o main ./Stime.c

if [ -z "$1" ]
then
	mpirun -np 16 ./main 15 37 24 9241 20000
else
	mpirun -np $1 ./main $2 $3 $4 $5 $6
fi
