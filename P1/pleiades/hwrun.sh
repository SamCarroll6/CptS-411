#!/bin/sh

set -e

if [ -z "$1" ]
then
	mpicc -o main ~/CptS-411/P1/pleiades/main.c
else
	mpicc -o $1 ~/CptS-411/P1/pleiades/$1.c
fi

if [ -z "$2"]
then
	if [ -z "$1" ]
	then
		mpirun -np 2 ~/CptS-411/P1/pleiades/main
		rm main
	else
		mpirun -np 2 ~/CptS-411/P1/pleiades/$1
		rm $1
	fi
else
	mpirun -np $2 ~/CptS-411/P1/pleiades/$1
	rm $1
fi

