#include <bits/stdc++.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

#define INTERVAL 2000000000
using namespace std;

int NUM_THREADS;
int partial_inBoxes[10000];

double calculate_pi() {
	unsigned long long  i;
	double  rand_x, rand_y, origin_dist, pi;
	unsigned long long circle_points = 0;

	//srand(time(NULL));
	omp_set_num_threads(NUM_THREADS);

	unsigned seed;
	#pragma omp parallel private(seed, rand_x, rand_y, circle_points) shared(pi)
	{
		seed = time(NULL);
		#pragma omp for schedule(static)
		for (i = 0; i < INTERVAL; i++) {
			rand_x = double(rand_r(&seed) % (INTERVAL + 1)) / INTERVAL;
			rand_y = double(rand_r(&seed) % (INTERVAL + 1)) / INTERVAL;

			origin_dist = rand_x * rand_x + rand_y * rand_y;

			if (origin_dist <= 1)
				circle_points++;
		}
	int tid = omp_get_thread_num();
    partial_inBoxes[tid] = circle_points;
	}
	unsigned long long total_circle_points = 0;
	for(int i =0 ; i < omp_get_max_threads(); ++i)
    	total_circle_points += partial_inBoxes[i];
    pi = double(4 * total_circle_points) / (double)INTERVAL;

	return pi;
}

int main(int argc, char *argv[]) {
	NUM_THREADS = atoi(argv[1]);
	double pi;
	struct timeval  start, stop;
  	gettimeofday(&start, NULL);

	pi = calculate_pi();

	printf("RESULT: %lf \n", pi);
  	gettimeofday(&stop, NULL);
  	printf ("Integral OPENMP with %d threads has a duration of %lf seconds\n",
          atoi(argv[1]),
          (double) (start.tv_usec - stop.tv_usec) / 1000000 +
          (double) (stop.tv_sec - start.tv_sec));

	return 0;
}
