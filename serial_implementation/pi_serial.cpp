#include <bits/stdc++.h>
#include <limits.h>
#include <sys/time.h>

#define INTERVAL 2000000000
using namespace std;

double calculate_pi() {
	unsigned long long  i;
	double  rand_x, rand_y, origin_dist, pi;
	unsigned long long circle_points = 0, square_points = 0;

	srand(time(NULL));
	for (i = 0; i < INTERVAL; i++) {
		rand_x = double(rand() % (INTERVAL + 1)) / INTERVAL;
		rand_y = double(rand() % (INTERVAL + 1)) / INTERVAL;

		origin_dist = rand_x * rand_x + rand_y * rand_y;

		if (origin_dist <= 1)
			circle_points++;

		square_points++;

		pi = double(4 * circle_points) / square_points;
	}

	return pi;
}

int main()
{
	double pi;
	struct timeval  start, stop;
  	gettimeofday(&start, NULL);

	pi = calculate_pi();	
	cout << "Final Estimation of Pi = " << pi << endl;
	gettimeofday(&stop, NULL);
  	printf ("Pi serial has a duration of %lf seconds\n",
          (double) (start.tv_usec - stop.tv_usec) / 1000000 +
          (double) (stop.tv_sec - start.tv_sec));
	return 0;
}
