build: integral_pthread pi_pthread

integral_pthread: integral_pthread.cpp
	g++ -Wall integral_pthread.cpp -o integral_pthread -lpthread

pi_pthread: pi_pthread.cpp
	g++ pi_pthread.cpp -lpthread -o pi_pthread

clean:
	rm -f integral_pthread pi_pthread
