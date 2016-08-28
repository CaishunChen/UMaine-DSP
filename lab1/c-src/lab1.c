/*!
 * @file
 * 
 * @brief The purpose of this program is to test the functions of running_mean.c.
 * 
 * @author ECE486 Lab Group 10
 * @author Chris Eustis
 * @author Josh Scripture
 * @author Nabil Chowdhoury
 * 
 * @date Feb 5, 2016
 * 
 * This file sets the sample size and blocksize of a desired signal.
 * An input signal x(n) is described as 'double x[]' to represent the data
 * points of the signal. A structure is initializated to provide the 
 * necessary data to continously calculate the running average of
 * the input signal.
 * 
 */

#include <stdio.h>
#include <math.h>
#include "running_mean.h"


 int main(void)
{
	/*! Initialize the data structure */
	struct mean_value s;

	int samples;
	int blocksize;
	double x[1000];
	int i;

	/*! TEST CASE 1 */

	puts("Beginning Test Case #1");
	/*! Define blocksize and samples to average over */
	samples = 10;
	blocksize = 4;

	/*! Create structure */
	s = init_struct(s, blocksize, samples);
	
	/*! Input signal data as a sine wave */
	for (i = 0; i < 1000; i++) {
		x[i] = sin(i+1)+1;
	}
	
	/*! Calculate the running average */
	s = calc_running_mean(s, x);
	print_output(s);
	s = calc_running_mean(s, x);
	print_output(s);
	s = calc_running_mean(s, x);
	print_output(s);
	s = calc_running_mean(s, x);
	print_output(s);

	/*! Deallocate any reserved memory */
	terminate(s);
	puts("Ending Test Case #1\n");


	/*! TEST CASE 2 */

	puts("Beginning Test Case #2");
	/*! Define blocksize and samples to average over */
	samples = 10;
	blocksize = 4;
	
	/*! Create structure */
	s = init_struct(s, blocksize, samples);
	
	/*! Input signal data as a sine wave */
	for (i = 0; i < 1000; i++) {
		x[i] = 1;
	}
	
	/*! Calculate the running average */
	s = calc_running_mean(s, x);
	print_output(s);
	s = calc_running_mean(s, x);
	print_output(s);
	s = calc_running_mean(s, x);
	print_output(s);
	s = calc_running_mean(s, x);
	print_output(s);

	/*! Deallocate any reserved memory */
	terminate(s);
	puts("Ending Test Case #2\n");


	/*! TEST CASE 3 */

	puts("Beginning Test Case #3");
	/*! Define blocksize and samples to average over */
	samples = 2;
	blocksize = 2;
	
	/*! Create structure */
	s = init_struct(s, blocksize, samples);
	
	/*! Input signal data as a sine wave */
	for (i = 0; i < 1000; i++) {
		x[i] = 1;
	}
	
	/*! Calculate the running average */
	s = calc_running_mean(s, x);
	print_output(s);
	s = calc_running_mean(s, x);
	print_output(s);

	/*! Deallocate any reserved memory */
	terminate(s);
	puts("Ending Test Case #3\n");

	return 1;
}