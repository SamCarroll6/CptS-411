#! /bin/sh

sbatch -N1 ./hwrun.sh 1024 1
sleep 2
sbatch -N1 ./hwrun.sh 2048 2
sleep 2
sbatch -N1 ./hwrun.sh 4096 4
sleep 2
sbatch -N1 ./hwrun.sh 8192 8
sleep 2
sbatch -N1 ./hwrun.sh 16384 16
sleep 2
sbatch -N1 ./hwrun.sh 32768 32
sleep 2
sbatch -N1 ./hwrun.sh 65536 64

