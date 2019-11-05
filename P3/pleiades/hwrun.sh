#!/bin/sh

set -e

if [ -z "$1" ]
then
	mpicc -o main ~/School/CptS411/CptS-411/P3/local/main.c
else
	mpicc -o $1 ./$1.c
fi

mpirun -np 8 ~/School/CptS411/CptS-411/P3/local/main 15 37 24 9241 20000
