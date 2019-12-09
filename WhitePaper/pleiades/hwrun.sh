#! /bin/sh


g++ -std=c++11 -o main -fopenmp test.cpp -lm


if [ -z "$3" ]
then
	./main 1024 4
else
	./main $1 $2 $3 $4
fi