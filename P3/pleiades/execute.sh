#if [ -z "$1" ]
#then
#    sbatch -N1 ./hwrun.sh 2 | sort -V
#    sbatch -N2 ./hwrun.sh 4 | sort -V
#    sbatch -N4 ./hwrun.sh 8 | sort -V
#    sbatch -N4 ./hwrun.sh 16 | sort -V
#    sbatch -N8 ./hwrun.sh 32 | sort -V
#    sbatch -N8 ./hwrun.sh 64 | sort -V
# else
#     sbatch -N1 ./hwrun.sh 2 150 74 49 49999 1024 | sort -V
#     sbatch -N2 ./hwrun.sh 4 150 74 49 49999 1024 | sort -V
#     sbatch -N4 ./hwrun.sh 8 150 74 49 49999 1024 | sort -V
#     sbatch -N4 ./hwrun.sh 16 150 74 49 49999 1024 | sort -V
#     sbatch -N8 ./hwrun.sh 32 150 74 49 49999 1024 | sort -V
#     sbatch -N8 ./hwrun.sh 64 150 74 49 49999 1024 | sort -V
# fi

# p seed A B Prime n

if [ -z "$7" ]
then
	sbatch -N4 ./hwrun.sh 16 150 74 49 4999 1024
else
	sbatch -N$1 ./hwrun.sh $2 $3 $4 $5 $6 $7
fi

# elif [ -z "$6" ]
# then
# 	sbatch -N4 ./hwrun.sh 16 150 74 49 49999 1024 | sort -V
# else
# 	sbatch -N$1 ./hwrun.sh $2 $3 $4 $5 $6 1024 | sort -V
# fi

# elif [ -z "$5" ]
# then
# 	sbatch -N4 ./hwrun.sh 16 150 74 49 49999 1024 | sort -V
# else
# 	sbatch -N$1 ./hwrun.sh $2 $3 $4 $5 49999 1024 | sort -V
# fi

# elif [ -z "$4" ]
# then
# 	sbatch -N4 ./hwrun.sh 16 150 74 49 49999 1024 | sort -V
# else
# 	sbatch -N$1 ./hwrun.sh $2 $3 $4 49 49999 1024 | sort -V
# fi

# elif [ -z "$3" ]
# then
# 	sbatch -N4 ./hwrun.sh 16 150 74 49 49999 1024 | sort -V
# else
# 	sbatch -N$1 ./hwrun.sh $2 $3 74 49 49999 1024 | sort -V
# fi

# elif [ -z "$2" ]
# then
# 	sbatch -N4 ./hwrun.sh 16 150 74 49 49999 1024 | sort -V
# else
# 	sbatch -N$1 ./hwrun.sh $2 150 74 49 49999 1024 | sort -V
# fi

# elif [ -z "$1" ]
# then
# 	sbatch -N4 ./hwrun.sh 16 150 74 49 49999 1024 | sort -V
# else
# 	sbatch -N$1 ./hwrun.sh 16 150 74 49 49999 1024 | sort -V
# fi







