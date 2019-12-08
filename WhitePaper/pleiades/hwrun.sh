#! /bin/sh


g++ -std=c++11 -o main -fopenmp main.c -lm


if [ -z "$2" ]
then
	./main 1024 4
else
	./main $1 $2
fi