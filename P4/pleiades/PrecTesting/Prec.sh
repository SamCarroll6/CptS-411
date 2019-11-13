#! /bin/sh

sbatch -N1 ./hwrun.sh 4194304 1
sleep 2
sbatch -N1 ./hwrun.sh 8388608 2
sleep 2
sbatch -N1 ./hwrun.sh 16777216 4
sleep 2
sbatch -N1 ./hwrun.sh 33554432 8
sleep 2
sbatch -N1 ./hwrun.sh 67108864 16
sleep 2
sbatch -N1 ./hwrun.sh 134217728 32
sleep 2
sbatch -N1 ./hwrun.sh 268435456 64
sleep 2