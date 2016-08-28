/*!
 * @file
 * 
 * @brief The purpose of this program is to perform multiple stages of transposed Direct Form II 
 * convolutions on a given input to simulate the function of an IIR filter.
 * 
 * @author ECE486 Lab Group 10
 * @author Chris Eustis
 * @author Josh Scripture
 * @author Nabil Chowdhoury
 * 
 * @date Feb 19, 2016
 * 
 * init_biquad() allocates memory to the output array and coefficient array.
 * calc_biquad() performs the Transposed Direct Form II calculations on the input x[] and intermediate
 * values v[] in order to produce an output y[].
 * destroy_biquad() frees the previously allocated memory.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ece486_biquad.h"

BIQUAD_T *init_biquad(int sections, float g, float *biquad_coefs, int blocksize)
{
	int i;
	BIQUAD_T *filt;

	filt = (BIQUAD_T *)calloc(1, sizeof(BIQUAD_T));
	// if (filt == NULL)
		// return null;

	// Save off coefficient values
	filt->biquad_coefs = biquad_coefs;

	// Intermediate values (z-delays)
	filt->z_delay = (float**)malloc(sections*sizeof(float*));

	// Allocate inner arrays for history
	for(i = 0; i < sections; i++) {
		filt->z_delay[i] = (float*)calloc(2, sizeof(float));
	}

	// Filter gain, number of second order systems, and number of samples
	filt->g = g;
	filt->sections = sections;
	filt->blocksize = blocksize;

	return filt;
}

void calc_biquad(BIQUAD_T *s, float *x, float *y)
{
	int i, j;
	float b0, b1, b2, a1, a2;
	float temp;

	j = 0;

	// Iterate over each section
	for(i = 0; i < s->sections; i++) {
		// Calculate gain
		if (s > 0)
			temp = y[j];
		else
			temp = x[j] * s->g;

		/* Iterate over each value in block */
		for (j = 0; j < s->blocksize; j++) {
			/* Get coefficients for this section */
			b0 = s->biquad_coefs[5 * i + 0];
			b1 = s->biquad_coefs[5 * i + 1];
			b2 = s->biquad_coefs[5 * i + 2];
			a1 = s->biquad_coefs[5 * i + 3];
			a2 = s->biquad_coefs[5 * i + 4];

			/* Intermediate value with gain added */
			temp = x[j] * s->g + (-a1 * (s->z_delay[i][0])) + (-a2 * (s->z_delay[i][1]));

			/* Calculate output value */
			y[j] = temp * b0 + (b1 * s->z_delay[i][0]) + (b2 * s->z_delay[i][1]);

			/* Shift delay values */
			s->z_delay[i][1] = s->z_delay[i][0];
			s->z_delay[i][0] = temp;
		}
	}
}

void destroy_biquad(BIQUAD_T *s)
{
	if (s)
		free(s->z_delay);
		free(s);
}