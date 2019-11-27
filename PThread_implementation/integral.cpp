#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAX 2000000000

typedef struct {
	int id;
	unsigned int count_max;
	int x_min;
	int x_max;
	int y_min;
	int y_max;
} thread_info;

float thread_inBox[500];

// Functia pentru care se calculeaza integrala
float f (float x){
	return exp(2 * sin(x) * sin(x));
}

void* thread_function(void *var)
{
	thread_info info = *(thread_info *) var;
	unsigned int count;
	float inBox = 0;

	for (count = 0; count < info.count_max; count++){
		float u1 = (float)rand()/(float)RAND_MAX;
		float u2 = (float)rand()/(float)RAND_MAX;

		float xcoord = ((info.x_max - info.x_min) * u1) + info.x_min;
		float ycoord = ((info.y_max - info.y_min) * u2) + info.y_min;
		float val = f(xcoord);

		if (val > ycoord){
			inBox++;
		}
	}

	thread_inBox[info.id] = inBox;

	return 0;
}

int main(int argc, char **argv) {
	float result;
	int x_min = -1000;
	int x_max = 1000;
	int y_min = 0;
	int y_max = 40000;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s num_threads\n", argv[0]);
		return -1;
	}

	int num_threads = atoi(argv[1]);
	int step = MAX / num_threads;
	int i;

	pthread_t tid[num_threads];
	thread_info thread_info[num_threads];

	// Punem valori in structurile pentru thread-uri
	for (i = 0; i < num_threads; i++)
	{
		thread_info[i].id = i;
		thread_info[i].count_max = step;
		thread_info[i].x_min = x_min;
		thread_info[i].x_max = x_max;
		thread_info[i].y_min = y_min;
		thread_info[i].y_max = y_max;
	}

	for (i = 0; i < num_threads; i++)
	{
		pthread_create(&(tid[i]), NULL, thread_function, &(thread_info[i]));
	}

	for (i = 0; i < num_threads; i++)
	{
		pthread_join(tid[i], NULL);
	}

	int inBox_sum = 0;
	for (i = 0; i < num_threads; i++) {
		inBox_sum += thread_inBox[i];
	}

	float density = inBox_sum / MAX;

	result = (x_max - x_min) * (y_max - y_min) * density;

	std::cout<< "RESULT: " << result << "\n";

	return 0;
}
