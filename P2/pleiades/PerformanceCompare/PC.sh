#!/bin/sh

sbatch -N$1 ./hwrun.sh $2 $3 1000 1
sleep 1
sbatch -N$1 ./hwrun.sh $2 $3 2000 1
sleep 1
sbatch -N$1 ./hwrun.sh $2 $3 4000 1
sleep 1
sbatch -N$1 ./hwrun.sh $2 $3 8000 1
sleep 1
sbatch -N$1 ./hwrun.sh $2 $3 16000 1
sleep 1
sbatch -N$1 ./hwrun.sh $2 $3 32000 1
sleep 1
sbatch -N$1 ./hwrun.sh $2 $3 64000 1
sleep 1
sbatch -N$1 ./hwrun.sh $2 $3 640000 1