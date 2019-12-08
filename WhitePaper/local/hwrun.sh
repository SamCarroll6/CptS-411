#!/bin/sh

g++-9 -o main -fopenmp main.cpp


if [ -z "$2" ]
then
	./main 1024 4
else
	./main $1 $2
fi