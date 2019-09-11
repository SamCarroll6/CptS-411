#Running on Pleiades cluster

Since the cluster uses SLURM workload manager we can't run like we would on local and just execute the shell script. Instead is has to use the sbatch command in the form sbatch -N<number of nodes> hwrun.sh to execute. 
