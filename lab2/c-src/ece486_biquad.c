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
	BIQUAD_T *filt = (BIQUAD_T *)malloc(sizeof(BIQUAD_T));

	filt->biquad_coefs = biquad_coefs;

	filt->v1_prev = 0.0;
	filt->v2_prev = 0.0;

	filt->g = g;
	filt->sections = sections;
	filt->blocksize = blocksize;

	return filt;
}

void calc_biquad(BIQUAD_T *s, float *x, float *y)
{
	int i, j;
	float v1, v2;
	float b0, b1, b2, a1, a2;

	for(i = 0; i < s->sections; i++) {
		for (j = 0; j < s->blocksize; j++) {
			//!< Point to coefficients needed for current calculation
			b0 = s->biquad_coefs[5*i+0];
			b1 = s->biquad_coefs[5*i+1];
			b2 = s->biquad_coefs[5*i+2];
			a1 = s->biquad_coefs[5*i+3];
			a2 = s->biquad_coefs[5*i+4];

			//!< Perform difference equation calculations
			y[j] = s->v1_prev + b0 * x[j];
			v1 = s->v2_prev - a1 * y[j] + b1 * x[j];
			v2 = b2 * x[j] - a2 * y[j];

			//!< Save off values needed for next calculation
			s->v1_prev = v1;
			s->v2_prev = v2;
		}
		/*
		 * For each section, output values become input values
		 */
		for (j = 0; j < s->blocksize; j++) {
			x[j] = y[j];
		}
	}
	for (i = 0; i < s->blocksize; i++) {
		y[i] *= s->g;
	}
}

void destroy_biquad(BIQUAD_T *s)
{
	if (s)
		free(s);
}