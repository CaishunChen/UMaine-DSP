/*!
 * @file
 * 
 * @brief The purpose of this program is to calculate the running average 
 * of an input signal. 
 * 
 * @author ECE486 Lab Group 10
 * @author Chris Eustis
 * @author Josh Scripture
 * @author Nabil Chowdhoury
 * 
 * @date Feb 5, 2016
 * 
 * The first function is used to initialize a structure
 * of which holds the data for calculating the running average of an input signal.
 * 
 * The second function calculates the running mean using the data of stored
 * in the structure and the latest blocksize of samples from the input signal.
 *
 * The final function is used to release any reserved memory that has been
 * used by the functions to calculate the running average.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "running_mean.h"

/*!
 * @brief Initialize and reserve memory of data struture
 * 
 * Allocates memory for the necessary data that is stored in the structure
 * for use when calculating the running average. Data in any ararys are 
 * initialized to zeros.
 * 
 * @param[in,out] 	s 		Structure holding data for calculations.
 * @param[in]		blocksize 	The width of samples being given.
 * @param[in]     	M 		The number of samples to average over.
 * 
 * @returns	 On return, all elements of the structure are initialized to zeros
 * 		 and have been allocated in memory.  
 */
struct mean_value init_struct(struct mean_value s, int blocksize, int M) {
	int i;

	/*! Allocate space for output y - set to zeros */
	s.y = (double *)calloc(blocksize, sizeof(double));

	/*! Allocate space for lastM  - set to zeros */
	s.lastM = (double *)calloc(M, sizeof(double));

	/*! Allocate space for block  - set to zeros */
	s.block = (double *)calloc(blocksize, sizeof(double));

	s.j = 0;
	s.blocksize = blocksize;
	s.M = M;
	return s;
}

/*!
 * @brief Calculate running average of input signal
 * 
 * Takes a new input signal of blocksize samples and averages them over 
 * the number of samples.
 *  
 * @param[in,out] 	s 	Structure holding data for calculations.
 * @param[in]		x 	Input signal data values.
 * 
 * @returns	 On return, the structure output signal has been adjusted to contain
 *		 the most recent running average of samples from the given
 *		 input signal of blocksize.
 */
struct mean_value calc_running_mean(struct mean_value s, double *x)
{
	double q;
	int i;

	/*! Fill block */
	for (i = 0; i < s.blocksize; i++) {
		s.block[i] = x[s.j+i];
	}

	/*! Bring block into summing array and re-evaluate average */
	for (i = 0; i < s.blocksize; i++) {
		q = s.lastM[((i + s.j)  % s.M)];
		s.lastM[((i + s.j) % s.M)] = s.block[i];
		if (i == 0)
			s.y[i] = s.y[s.blocksize-1] + s.block[i] / s.M - q/s.M;
		else
			s.y[i] = s.y[i-1] + s.block[i] / s.M - q/s.M;
	}
	s.j += s.blocksize;
	return s;
}

/*!
 * @brief This function prints out the output value y of the structure
 * to show the resulting average of the input signal.
 *
 * @param[in] 		s 	Structure holding data for calculations.
 *
 */
void print_output(struct mean_value s) {
	int i;
	for (i = 0; i < s.blocksize; i++) {
		printf("s.y[%d]: %f\n", i, s.y[i]);
	}
}

/*!
 * @brief Free any reserved memory used to calculate running average
 * 
 * Takes the structure used to calculate the running average and frees andy
 * of the reserved memory when finished.
 *
 * @param[in] 		s 	Structure holding data for calculations.
 *
 */
void terminate(struct mean_value s)
{	
	free(s.y);
	free(s.lastM);
	free(s.block);
}