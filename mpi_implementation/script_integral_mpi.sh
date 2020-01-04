#!/bin/bash
mpirun -np 2 ./integral_mpi
mpirun -np 4 ./integral_mpi
mpirun -np 8 ./integral_mpi