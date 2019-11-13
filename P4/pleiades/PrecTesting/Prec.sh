#! /bin/sh

sbatch -N1 ./hwrun.sh 16 1
sleep 2
sbatch -N1 ./hwrun.sh 32 2
sleep 2
sbatch -N1 ./hwrun.sh 64 4
sleep 2
sbatch -N1 ./hwrun.sh 128 8
sleep 2
sbatch -N1 ./hwrun.sh 256 16
sleep 2
sbatch -N1 ./hwrun.sh 512 32
sleep 2
sbatch -N1 ./hwrun.sh 1024 64

