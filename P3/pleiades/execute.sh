if [ -z "$1" ]
then
    sbatch -N1 ./hwrun.sh 2
    sbatch -N2 ./hwrun.sh 4
    sbatch -N4 ./hwrun.sh 8
    sbatch -N4 ./hwrun.sh 16
    sbatch -N8 ./hwrun.sh 32
    sbatch -N8 ./hwrun.sh 64
else
    sbatch -N1 ./hwrun.sh 2 150 74 49 49999 1024
    sbatch -N2 ./hwrun.sh 4 150 74 49 49999 1024
    sbatch -N4 ./hwrun.sh 8 150 74 49 49999 1024
    sbatch -N4 ./hwrun.sh 16 150 74 49 49999 1024
    sbatch -N8 ./hwrun.sh 32 150 74 49 49999 1024
    sbatch -N8 ./hwrun.sh 64 150 74 49 49999 1024
fi