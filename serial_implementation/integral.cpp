#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

// #define MAX 2000000000
#define MAX 200000000

unsigned int count;
long double total, inBox;
int x_min, x_max, y_min, y_max;

//The function that the integral should be calculated for
long double f (long double x){
  return exp(2 * sin(x) * sin(x));
}

//function that calculates the integral
long double integral (long double (*f)(long double), long double xmin, long double xmax, long double ymin, long double ymax) {
	for (count = 0; count < MAX; count++){
		long double u1 = (long double)rand()/(long double)RAND_MAX;
		long double u2 = (long double)rand()/(long double)RAND_MAX;

		long double xcoord = ((xmax - xmin)*u1) + xmin;
		long double ycoord = ((ymax - ymin)*u2) + ymin;
		long double val = f(xcoord);

		total++;

		if (val > ycoord){
			inBox++;
		}
	}

	long double density = inBox / total;

	return (xmax - xmin) * (ymax - ymin) * density;
}


int main(){
	clock_t start, end;
	double cpu_time_used;
	long double result;
	x_min = -2;
	x_max = 2;
	y_min = 0;
	y_max = 4;

	start = clock();
	result = integral(f, x_min, x_max, y_min, y_max);
	end = clock();

	std::cout << "RESULT: " << result << "\n";
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	std::cout << "Time used: " << cpu_time_used << "\n";

	return 0;
}
