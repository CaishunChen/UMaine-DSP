/*!
 * @file
 * 
 * @brief The purpose of this program is to calculate the
 * discrete-time convolution of a signal.
 * 
 * @author ECE486 Lab Group 10
 * @author Chris Eustis
 * @author Josh Scripture
 * @author Nabil Chowdhoury
 * 
 * @date April 8, 2016
 * 
 * Initializations are done in the init_fir function, where
 * the necessary memory is allocated for the data held
 * within the struct.
 *
 * The calculation of the convolution is done in the
 * calc_fir function, where an input signal is given,
 * and the convolution is calculated using data
 * that is contained within the struct.
 *
 * The final function, destroy_fir, is used to free
 * any previously allocated memory used by the program.
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ece486_fir.h"

FIR_T *init_fir(float *fir_coefs, int n_coef, int blocksize)
{
	int i; 
	int num_samples;
	int blocks;

	FIR_T *filt;

	filt = malloc(sizeof(FIR_T));

	/* Calculate # blocks for history */
	blocks = (int)(n_coef / blocksize);
	if (blocks <= blocksize)
		blocks += 1;

	/* Calculate number of samples */
	num_samples = blocksize * blocks;

	// Allocate for impulse response and set to given coefficients
	filt->h = (float *)malloc(n_coef * sizeof(float));
	for (i = 0; i < n_coef; i++) {
		filt->h[i] = fir_coefs[i];
	}

	/*
	* filt->prev: stores new data in conjuction with previous data
	* determined by # blocks; used to compute discrete-time
	* convolution of signal
	*/
	filt->prev = malloc(num_samples * sizeof(float));

	/* Set all values of filt->prev to 0.0 */
	for(i = 0; i < num_samples; i++) {
		filt->prev[i] = 0.0f;
	}

	/* Save size of impulse response coefficients */
	filt->length = n_coef;
	/* Save blocksize */
	filt->blocksize = blocksize;
	/* Save number of samples */
	filt->num_samples = num_samples;

	return filt;
}

void calc_fir(FIR_T *s, float *x, float *y)
{
	int i, j;
	float temp;
	float conv_sum;

	/* Shift history by 'blocksize' for new data coming in */
	for(i = s->num_samples-1; i >= s->blocksize; i--) {
		s->prev[i] = s->prev[i - s->blocksize];
	}

	/* Copy new data into history array */
	for (i = 0; i < s->blocksize; i++) {
		s->prev[i] = x[i];
	}

	/* Iterate through new input data */
	for (i = 0; i < s->blocksize; i++) {
		/* Initialize sum */
		conv_sum = 0.;
		for (j = i; j < i+s->length; j++) {
			temp = s->prev[i];
			temp *= s->h[j-i];
			conv_sum += temp;
		}
		/* Store convolution sum into output */
		y[i] = conv_sum;
	}
}

void destroy_fir(FIR_T *s)
{
	if (s)
		free(s->h);
		free(s->prev);
		free(s);
}