#! /bin/sh

sbatch -N1 ./hwrun.sh 65536 1
sleep 2
sbatch -N1 ./hwrun.sh 131072 2
sleep 2
sbatch -N1 ./hwrun.sh 262144 4
sleep 2
sbatch -N1 ./hwrun.sh 524288 8
sleep 2
sbatch -N1 ./hwrun.sh 1048576 16
sleep 2
sbatch -N1 ./hwrun.sh 2097152 32
sleep 2
sbatch -N1 ./hwrun.sh 4194304 64
sleep 2