#Running on Pleiades cluster

Since the cluster uses SLURM workload manager we can't run like we would on local and just execute the shell script. Instead the cluster will use the sbatch command in the form 

sbatch -N<number of nodes> hwrun.sh fulltest <number of processors> <size of array> <flag {0 = SUM, 1 = MAX}>

to execute. 

The above will run simply the standard main option. 

I wrote test cases as well which are stored in accompanying directories CorrectnessTest and PerformanceCompare: 

The CorrectnessTest directory contains a script CT.sh which runs a prewritten set of tests in order to test the correctness of the program. This script takes no additional input, all that needs to be done is execute it on the pleiades cluster. 

./CT.sh 

The PerformanceCompare directory has a script PC.sh, similar to CT.sh it also runs a predetermined set of tests. This one however does require input. For performance testing I split my main function into 3 separate functions myreducetime.c, mpireducetime.c, bustime.c. Each function grabs the average of 10 run times for the function that corresponds with its name (my reduce = myreducetime.c, mpi_allreduce = mpireducetime.c, naivereduce = bustime.c). I separated the functions because I wanted each to have it's own function focusing on it's time to process in order to avoid the program running multiple processes which end at different times and potentially impacting the results. This script call will take 3 user inputs in order to run properly.

./PC.sh <number of nodes> <function name> <number of processors>

All other information is preset in the tests. 