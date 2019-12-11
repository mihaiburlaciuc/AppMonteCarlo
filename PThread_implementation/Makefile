build: integral pi_parallel

integral: integral.cpp
	g++ -Wall integral.cpp -o integral -lpthread

pi_parallel: pi_parallel.cpp
	g++ pi_parallel.cpp -lpthread -o pi_parallel

clean:
	rm -f integral pi_parallel
