#include <bits/stdc++.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

#define INTERVAL 1000
#define NUM_THREADS 8
using namespace std;

double calculate_pi() {
	unsigned long long  i;
	double  rand_x, rand_y, origin_dist, pi;
	unsigned long long circle_points = 0, square_points = 0;

	srand(time(NULL));
	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel private(rand_x, rand_y, circle_points, square_points) shared(pi)
	{
		#pragma omp for schedule(static)
		for (i = 0; i < UINT_MAX; i++) {
			rand_x = double(rand() % (INTERVAL + 1)) / INTERVAL;
			rand_y = double(rand() % (INTERVAL + 1)) / INTERVAL;

			origin_dist = rand_x * rand_x + rand_y * rand_y;

			if (origin_dist <= 1)
				circle_points++;

			square_points++;

			pi = double(4 * circle_points) / square_points;
		}
	}

	return pi;
}

int main()
{
	double pi;
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	pi = calculate_pi();
	end = clock();

	cout << "Final Estimation of Pi = " << pi << endl;
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	cout << "Time used: " << cpu_time_used << "\n";

	return 0;
}
