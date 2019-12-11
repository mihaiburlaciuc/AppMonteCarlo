build: integral_openmp pi_openmp

integral_openmp: integral_openmp.cpp
	g++ -fopenmp -Wall integral_openmp.cpp -o integral_openmp
pi_openmp: pi_openmp.cpp
	g++ -fopenmp -Wall pi_openmp.cpp -o pi_openmp

clean:
	rm -f integral_openmp pi_openmp
