#Running on Pleiades cluster

Since the cluster uses SLURM workload manager we can't run like we would on local and just execute the shell script. Instead the cluster will use the sbatch command in the form 

sbatch -N<number of nodes> hwrun.sh fulltest <number of processors>

to execute. 

In this case number of processors is an optional addition. Technically fulltest is not required either but if you don't include it the general run script I wrote will look for a file 'main' which in this directory does not exist.
