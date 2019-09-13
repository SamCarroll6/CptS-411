#Running on Pleiades cluster

When running locally make sure you mpich installed and working on your local machine. from there the call is fairly simple:

hwrun.sh fulltest <number of processors>

to execute. 

In this case number of processors is an optional addition. Technically fulltest is not required either but if you don't include it the general run script I wrote will look for a file 'main' which in this directory is just the basic send receive implementation that we started with. Nonblocking.c and blocking.c can also be run but the best file in this folder is fulltest.c. 
