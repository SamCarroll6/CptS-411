#! /bin/sh

sbatch -N1 ./hwrun.sh 1 1
sleep 2
sbatch -N1 ./hwrun.sh 2 2
sleep 2
sbatch -N1 ./hwrun.sh 4 4
sleep 2
sbatch -N1 ./hwrun.sh 8 8
sleep 2
sbatch -N1 ./hwrun.sh 16 16
sleep 2
sbatch -N1 ./hwrun.sh 32 32
sleep 2
sbatch -N1 ./hwrun.sh 64 64
sleep 2


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
sleep 2

sbatch -N1 ./hwrun.sh 4 1
sleep 2
sbatch -N1 ./hwrun.sh 8 2
sleep 2
sbatch -N1 ./hwrun.sh 16 4
sleep 2
sbatch -N1 ./hwrun.sh 32 8
sleep 2
sbatch -N1 ./hwrun.sh 64 16
sleep 2
sbatch -N1 ./hwrun.sh 128 32
sleep 2
sbatch -N1 ./hwrun.sh 256 64
sleep 2

sbatch -N1 ./hwrun.sh 8 1
sleep 2
sbatch -N1 ./hwrun.sh 16 2
sleep 2
sbatch -N1 ./hwrun.sh 32 4
sleep 2
sbatch -N1 ./hwrun.sh 64 8
sleep 2
sbatch -N1 ./hwrun.sh 128 16
sleep 2
sbatch -N1 ./hwrun.sh 256 32
sleep 2
sbatch -N1 ./hwrun.sh 512 64
sleep 2