#!/bin/sh

set -e


mpicc -o main ./main.c

if [ -z "$1" ]
then
	mpirun -np 16 ./main 15 37 24 9241 20000
else
	mpirun -np $1 ./main 15 37 24 9241 20000
fi

if [ -z "$2" ]
then
	mpirun -np 16 ./main 15 37 24 9241 20000
else
	mpirun -np $1 ./main $2 37 24 9241 20000
fi

if [ -z "$3" ]
then
	mpirun -np 16 ./main 15 37 24 9241 20000
else
	mpirun -np $1 ./main $2 $3 24 9241 20000
fi

if [ -z "$4" ]
then
	mpirun -np 16 ./main 15 37 24 9241 20000
else
	mpirun -np $1 ./main $2 $3 $4 9241 20000
fi

if [ -z "$5" ]
then
	mpirun -np 16 ./main 15 37 24 9241 20000
else
	mpirun -np $1 ./main $2 $3 $4 $5 20000
fi

if [ -z "$5" ]
then
	mpirun -np 16 ./main 15 37 24 9241 20000
else
	mpirun -np $1 ./main $2 $3 $4 $5 $6
fi


