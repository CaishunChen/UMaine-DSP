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
	BIQUAD_T *filt = (BIQUAD_T *)malloc(sizeof(BIQUAD_T));

	int i;

	//! Declare number of sections, scale factor G, and blocksize
	int sections = 1;
	float g = 1.;
	int blocksize = 10;
	float *x;
	float *y;
	float *biquad_coefs;

	/***************/
	/* Test Case 1 */
	/***************/

	/*
	  This test creates an accumulator, where each output value is incremented by 2.
	*/

	//! Allocate memory for inputs x[i] and outputs y[i] of length "blocksize"
	x = (float *)malloc(blocksize*sizeof(float));
	y = (float *)calloc(blocksize, sizeof(float));

	//! Allocate memory for biquad coefficients
	biquad_coefs = (float *)calloc(sections*5, sizeof(float));


	//! Set values for biquad coefficients and input x[n]
	for (i = 0; i < sections*5; i++) {
		biquad_coefs[i] = 1.;
	}
	for (i = 0; i < blocksize; i++) {
		x[i] = 1.;
	}
	biquad_coefs[0] = 1.;
	biquad_coefs[1] = 0.;
	biquad_coefs[2] = 0.;
	biquad_coefs[3] = -1.;
	biquad_coefs[4] = 0.;

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

	/***************/
	/* Test Case 2 */
	/***************/

	/*
	  This test has an impuse as the input and should produce all ones on the output.
	*/
	// x = (float *)malloc(blocksize*sizeof(float));
	// y = (float *)calloc(blocksize, sizeof(float));

	// //! Allocate memory for biquad coefficients
	// biquad_coefs = (float *)calloc(sections*5, sizeof(float));


	// //! Set values for biquad coefficients and input x[n]
	// for (i = 0; i < sections*5; i++) {
	// 	biquad_coefs[i] = 0;
	// 	x[i] = 1;
	// }
	// biquad_coefs[0] = 1;

	// filt = init_biquad(sections, g, biquad_coefs, blocksize);

	// calc_biquad(filt, x, y);

	// printf("TEST CASE 2\n");
	// printf("y=[");
	// for (i = 0; i < blocksize; i++) {
	// 	printf("%lf ", y[i]);
	// }
	// printf("]\n\n");

	// calc_biquad(filt, x, y);
	// printf("y=[");
	// for (i = 0; i < blocksize; i++) {
	// 	printf("%lf ", y[i]);
	// }
	// printf("]\n\n");

	// free(biquad_coefs);
	// free(x);
	// free(y);
	// destroy_biquad(filt);

	/***************/
	 // Test Case 3 
	/***************/

	/*
	  This test produces a sin(n*pi/4).
	*/
	// x = (float *)malloc(blocksize*sizeof(float));
	// y = (float *)calloc(blocksize, sizeof(float));

	// //! Allocate memory for biquad coefficients
	// biquad_coefs = (float *)calloc(sections*5, sizeof(float));

	// //! Set values for biquad coefficients and input x[n]
	// for (i = 0; i < sections*5; i++) {
	// 	biquad_coefs[i] = 0;
	// 	x[i] = 0;
	// }
	// x[0] = 1;

	// biquad_coefs[0] = 0;
	// biquad_coefs[1] = sqrt(2)/2;
	// biquad_coefs[2] = 0;
	// biquad_coefs[3] = -sqrt(2);
	// biquad_coefs[4] = 1;

	// filt = init_biquad(sections, g, biquad_coefs, blocksize);

	// calc_biquad(filt, x, y);

	// printf("TEST CASE 3\n");
	// printf("y=[");
	// for (i = 0; i < blocksize; i++) {
	// 	printf("%lf ", y[i]);
	// }
	// printf("]\n\n");
	
	// calc_biquad(filt, x, y);
	// printf("y=[");
	// for (i = 0; i < blocksize; i++) {
	// 	printf("%lf ", y[i]);
	// }
	// printf("]\n\n");

	// free(biquad_coefs);
	// free(x);
	// free(y);
	// destroy_biquad(filt);

	return 1;
}