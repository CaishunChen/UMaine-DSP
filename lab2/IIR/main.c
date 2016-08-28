/*!
 * @file
 * 
 * @brief The purpose of this program is to test the functions of ece486_biquad.c.
 * 
 * @author ECE486 Lab Group 10
 * @author Chris Eustis
 * @author Josh Scripture
 * @author Nabil Chowdhoury
 * 
 * @date Feb 19, 2016
 * 
 * This file tests the IIR filter which is an implementation of
 * cascaded second-order systems.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ece486_biquad.h"

int main(void)
{
	int i;
	BIQUAD_T *filt;

	filt = (BIQUAD_T *)malloc(sizeof(BIQUAD_T));

	int blocksize = 100;
	float *x;
	float *y;
	float *biquad_coefs;
	int sections = 4;
	float g = 1.633862e-02;

	//! Allocate memory for inputs x[i] and outputs y[i] of length "blocksize"
	x = (float *)malloc(blocksize*sizeof(float));
	y = (float *)calloc(blocksize, sizeof(float));

	//! Allocate memory for biquad coefficients
	biquad_coefs = (float *)calloc(sections*5, sizeof(float));
	biquad_coefs[0] = 1.0000000000;
	biquad_coefs[1] = 1.0580134541;
	biquad_coefs[2] = 0.8100000000;
	biquad_coefs[3] = 1.0000000000;
	biquad_coefs[4] = 0.0590522271;
	biquad_coefs[5] = 0.8836000000;
	biquad_coefs[6] = 1.0000000000;
	biquad_coefs[7] = -1.6180339887;
	biquad_coefs[8] = 1.0000000000;
	biquad_coefs[9] = 1.0000000000;
	biquad_coefs[10] = -1.1522652609;
	biquad_coefs[11] = 0.8836000000;
	biquad_coefs[12] = 1.0000000000;
	biquad_coefs[13] = -1.8830919023;
	biquad_coefs[14] = 0.9801000000;
	biquad_coefs[15] = 1.0000000000;
	biquad_coefs[16] = -0.9499209086;
	biquad_coefs[17] = 0.7140250000;
	biquad_coefs[18] = 1.0000000000;
	biquad_coefs[19] = 1.4256104387;
	biquad_coefs[20] = 0.6400000000;
	biquad_coefs[21] = 1.0000000000;
	biquad_coefs[22] = -0.0923020637;
	biquad_coefs[23] = 0.5402250000;

	for (i = 0; i < blocksize; i++) {
		x[i] = 1.;
	}

	filt = init_biquad(sections, g, biquad_coefs, blocksize);

	calc_biquad(filt, x, y);

	printf("\nTEST CASE 1\n");
	printf("y=[");
	for (i = 0; i < blocksize; i++) {
		printf("%lf ", y[i]);
	}
	printf("]\n\n");

	calc_biquad(filt, x, y);
	printf("y=[");
	for (i = 0; i < blocksize; i++) {
		printf("%lf ", y[i]);
	}
	printf("]\n\n");

	free(biquad_coefs);
	free(x);
	free(y);
	destroy_biquad(filt);

	return 1;
}