#!/bin/sh

g++-9 -o main -fopenmp main.cpp


if [ -z "$2" ]
then
	./main 1000 4 2
else
	./main $1 $2
fi