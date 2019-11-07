if [ -z "$7" ]
then
	sbatch -N4 ./hwrun.sh 16 150 74 49 4999 1024
else
	sbatch -N$1 ./hwrun.sh $2 $3 $4 $5 $6 $7
fi