build: integral pi_parallel

integral: integral.cpp
	g++ -Wall integral.cpp -o integral -lpthread

pi_parallel: pi_parallel.cpp
	g++ -Wall pi_parallel.cpp -o pi_parallel -lpthread

clean:
	rm -f integral pi_parallel
