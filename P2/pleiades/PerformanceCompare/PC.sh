#!/bin/sh

sbatch -N$1 ./hwrun.sh main $2 1000 1

sbatch -N$1 ./hwrun.sh main $2 2000 1

sbatch -N$1 ./hwrun.sh main $2 4000 1

sbatch -N$1 ./hwrun.sh main $2 8000 1

sbatch -N$1 ./hwrun.sh main $2 16000 1

sbatch -N$1 ./hwrun.sh main $2 32000 1

sbatch -N$1 ./hwrun.sh main $2 64000 1

sbatch -N$1 ./hwrun.sh main $2 640000 1