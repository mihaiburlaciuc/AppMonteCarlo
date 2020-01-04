#!/bin/bash
mpirun -np 2 ./pi_mpi
mpirun -np 4 ./pi_mpi
mpirun -np 8 ./pi_mpi