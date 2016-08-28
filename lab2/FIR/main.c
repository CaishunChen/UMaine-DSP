/*!
 * @file
 * 
 * @brief The purpose of this program is to test the functions of ece486_fir.c.
 * 
 * @author ECE486 Lab Group 10
 * @author Chris Eustis
 * @author Josh Scripture
 * @author Nabil Chowdhoury
 * 
 * @date Feb 19, 2016
 * 
 * This file tests the FIR filter, which calculates the discrete-time
 * convolution of a given input signal, x, with a given impulse
 * response, h.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "ece486_fir.h"

int main(void)
{
	FIR_T *filt = (FIR_T *)malloc(sizeof(FIR_T *));

	int i;

	// Sample size
	int m = 50;
	// Blocksize
	int blocksize = 100;

	// impulse response
	float *h = (float *)malloc(blocksize*sizeof(float));

	// Allocate memory for inputs x[i] and outputs y[i] of length "blocksize"
	float *x = (float *)malloc(blocksize*sizeof(float));
	float *y = (float *)calloc((2*blocksize), sizeof(float));

	// Number of elements in input signal x[n]
	int n = sizeof(x);

	// impulse response vector h of length m
	for (i = 0; i < blocksize; i++) {
		h[i] = 1;
		x[i] = i;
	}

	filt = init_fir(h, m, blocksize);

	calc_fir(filt, x, y);
	
	printf("\ny[n]=[");
	for (i = 0; i < (n+m-1); i++) {
		printf("%lf ", y[i]);
	}
	printf("]\n\n");

	calc_fir(filt, x, y);
	
	printf("\ny[n]=[");
	for (i = 0; i < (n+m-1); i++) {
		printf("%lf ", y[i]);
	}
	printf("]\n\n");

	free(h);
	free(x);
	free(y);
	destroy_fir(filt);
}