#! /bin/sh

sbatch -N1 ./hwrun.sh 10000000 1
sleep 2
sbatch -N1 ./hwrun.sh 20000000 2
sleep 2
sbatch -N1 ./hwrun.sh 40000000 4
sleep 2
sbatch -N1 ./hwrun.sh 80000000 8
sleep 2
sbatch -N1 ./hwrun.sh 160000000 16
sleep 2
sbatch -N1 ./hwrun.sh 320000000 32
sleep 2
sbatch -N1 ./hwrun.sh 640000000 64

