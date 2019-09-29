#!/bin/sh

set -e

if [ -z "$1" ]
then
	mpicc -o main ~/School/CptS411/CptS-411/P2/local/main.c
else
	mpicc -o $1 ./$1.c
fi

if [ -z "$3"]
then
	if [ -z "$2" ]
	then
		if [ -z "$1" ]
		then
			mpirun -np 2 ~/School/CptS411/CptS-411/P2/local/main 8
			rm main
		else
			mpirun -np 2 ./$1 8
			rm $1
		fi
	else
		mpirun -np $2 ./$1 8
		rm $1
	fi
else
	if [ -z "$2" ]
	then
		if [ -z "$1" ]
		then
			mpirun -np 2 ~/School/CptS411/CptS-411/P2/local/main $3
			rm main
		else
			mpirun -np 2 ./$1 $3
			rm $1
		fi
	else
		mpirun -np $2 ./$1 $3
		rm $1
	fi
fi


