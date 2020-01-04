#!/bin/bash
make
./integral_serial
./integral_openmp 2
./integral_openmp 4
./integral_openmp 8
make clean