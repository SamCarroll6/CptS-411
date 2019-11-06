sbatch -N1 ./hwrun.sh 2 150 74 49 4999 1048576
sleep 2
sbatch -N2 ./hwrun.sh 4 150 74 49 4999 1048576
sleep 2
sbatch -N4 ./hwrun.sh 8 150 74 49 4999 1048576
sleep 2
sbatch -N4 ./hwrun.sh 16 150 74 49 4999 1048576
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 1048576
sleep 2
sbatch -N8 ./hwrun.sh 64 150 74 49 4999 1048576