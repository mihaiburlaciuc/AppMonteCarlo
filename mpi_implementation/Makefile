build: pi_mpi integral_mpi

pi_mpi: pi_mpi.c
	mpicc pi_mpi.c -o pi_mpi

integral_mpi: integral_mpi.c
	mpicc integral_mpi.c -o integral_mpi -lm

clean:
	rm -f pi_mpi integral_mpi
