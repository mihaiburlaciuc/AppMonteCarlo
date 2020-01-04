lsbuild: integral_openmp pi_openmp integral_serial

integral_serial: integral.cpp
	g++  -o integral_serial integral.cpp  -Wall
integral_openmp: integral_openmp.c
	gcc -o integral_openmp integral_openmp.c -fopenmp -lm -Wall
pi_openmp: pi_openmp.cpp
	g++ -fopenmp -Wall pi_openmp.cpp -o pi_openmp

clean:
	rm -f integral_openmp pi_openmp integral_serial
