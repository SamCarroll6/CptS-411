#! /bin/sh


gcc -o main -fopenmp main.c -lm


if [ -z "$2" ]
then
	./main 1024 4
else
	./main $1 $2
fi