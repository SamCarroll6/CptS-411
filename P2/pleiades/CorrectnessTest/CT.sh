#!/bin/sh

sbatch -N1 ./hwrun.sh main 1 1000 1
sleep 1
sbatch -N2 ./hwrun.sh main 2 2000 1
sleep 1
sbatch -N2 ./hwrun.sh main 4 4000 1
sleep 1
sbatch -N4 ./hwrun.sh main 8 8000 1
sleep 1
sbatch -N8 ./hwrun.sh main 16 16000 1
sleep 1
sbatch -N8 ./hwrun.sh main 32 32000 1
sleep 1
sbatch -N8 ./hwrun.sh main 64 64000 1
sleep 1
sbatch -N8 ./hwrun.sh main 64 640000 1