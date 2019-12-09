#!/bin/sh

g++-9 -o main -fopenmp test.cpp


if [ -z "$2" ]
then
	./main 1000 20 2 ../Paths/web-Google_sorted.txt tab
else
	./main $1 $2
fi