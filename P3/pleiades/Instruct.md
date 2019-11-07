#Running on Pleiades cluster

Since the cluster uses SLURM workload manager we can't run like we would on local and just execute the shell script. Instead the cluster will use the sbatch command in the form 

sbatch -N<number of nodes> hwrun.sh <Number of Processors> <Seed> <A value> <B value> <Large Prime Number> <number of outputs (n)>

to execute. 

The above will run based on the input you provide to it.

There is also an execute.sh script included. This will run a predefined set of values if executed with no input. If input is included it will be input as such:

./execute.sh <number of nodes> <Number of Processors> <Seed> <A value> <B value> <Large Prime Number> <number of outputs (n)>

Anything not in this format will default to the standard execution and not run your customized inputs. 