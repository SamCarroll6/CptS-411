#sbatch -N8 ./hwrun.sh 32 150 74 49 4999 1048576
#sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 32
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 64
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 128
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 256
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 512
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 1024
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 2048
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 4096
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 8192
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 16384
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 32768
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 65536
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 131072
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 262144
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 524288
sleep 2
sbatch -N8 ./hwrun.sh 32 150 74 49 4999 1048576
# sleep 2
