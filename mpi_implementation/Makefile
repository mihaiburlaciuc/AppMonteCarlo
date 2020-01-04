<<<<<<< HEAD
build:
	g++ -o integral_serial integral.cpp -Wall
	mpicc pi_mpi.c -o pi_mpi 
	mpicxx -o integral_mpi integral_mpi.c -Wall
clean:
	rm pi_mpi
	rm integral_mpi
	rm integral_serial
=======
build: pi_mpi integral_mpi

pi_mpi: pi_mpi.c
	mpicc pi_mpi.c -o pi_mpi

integral_mpi: integral_mpi.c
	mpicc integral_mpi.c -o integral_mpi -lm

clean:
	rm -f pi_mpi integral_mpi
>>>>>>> c6d906fd7d318d66684c2228f1be0c8604411e44
