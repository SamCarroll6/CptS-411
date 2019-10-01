#!/bin/sh

set -e

if [ -z "$1" ]
then
	mpicc -o main ~/CptS-411/P2/pleiades/main.c
else
	mpicc -o $1 ~/CptS-411/P2/pleiades/$1.c
fi


if [ -z "$4" ]
then
	if [ -z "$3" ]
	then
		if [ -z "$2" ]
		then
			if [ -z "$1" ]
			then
				mpirun -np 2 ~/CptS-411/P2/pleiades/main 8 0
				rm main
			else
				mpirun -np 2 ./$1 8 0 
				rm $1
			fi
		else
			mpirun -np $2 ./$1 8 0
			rm $1
		fi
	else
		if [ -z "$2" ]
		then
			if [ -z "$1" ]
			then
				mpirun -np 2 ~/CptS-411/P2/pleiades/main $3 0 
				rm main
			else
				mpirun -np 2 ./$1 $3 0 
				rm $1
			fi
		else
			mpirun -np $2 ./$1 $3 0
			rm $1
		fi
	fi
else
	if [ -z "$3" ]
	then
		if [ -z "$2" ]
		then
			if [ -z "$1" ]
			then
				mpirun -np 2 ~/CptS-411/P2/pleiades/main 8 $4
				rm main
			else
				mpirun -np 2 ./$1 8 $4
				rm $1
			fi
		else
			mpirun -np $2 ./$1 8 $4
			rm $1
		fi
	else
		if [ -z "$2" ]
		then
			if [ -z "$1" ]
			then
				mpirun -np 2 ~/CptS-411/P2/pleiades/main $3 $4
				rm main
			else
				mpirun -np 2 ./$1 $3 $4
				rm $1
			fi
		else
			mpirun -np $2 ./$1 $3 $4
			rm $1
		fi
	fi
fi
