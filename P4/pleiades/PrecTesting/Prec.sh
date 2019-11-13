#! /bin/sh

sbatch -N1 ./hwrun.sh 2 1
sleep 2
sbatch -N1 ./hwrun.sh 4 2
sleep 2
sbatch -N1 ./hwrun.sh 8 4
sleep 2
sbatch -N1 ./hwrun.sh 16 8
sleep 2
sbatch -N1 ./hwrun.sh 32 16
sleep 2
sbatch -N1 ./hwrun.sh 64 32
sleep 2
sbatch -N1 ./hwrun.sh 128 64

