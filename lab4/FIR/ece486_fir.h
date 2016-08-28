/*!
 * @file
 * 
 * @brief This file contains the definititions of the functions 
 * for implementation of discrete-time convolution.
 * 
 * @author ECE486 Lab Group 10
 * @author Chris Eustis
 * @author Josh Scripture
 * @author Nabil Chowdhoury
 * 
 * @date April 8, 2016
 * 
 * This structure of which holds the data for calculating the convolution
 * is defined, along with the functions to calculate the convolution. The
 * final function definition is used to free any previously allocated
 * memory used during the calculations.
 * 
 */

#ifndef ECE486_FIR_H
#define ECE486_FIR_H

/*!
 * @brief A structure typedef for storing data in which to calculate
 * the discrete-time convolution of a signal.
 * 
 * The structure holds the inpulse function data used for the convolution,
 * as well as the number of coefficients (sample size) and the output
 * data calculated by doing the convolution.
 * 
 */
typedef struct {
	float *h;		//! Impulse function
	int length;		//! Sample size
	int num_samples;	//! Number of samples in history
	float *prev;		//! Previous values for rolling calculation
	int blocksize;		//! Maintain blocksize for looping
} FIR_T;

/*!
 * @brief Initialize and reserve memory of data struture
 * 
 * Allocates memory for the necessary data that is stored in the structure
 * for use when calculating discrete-time convolution.
 * 
 * @param[in]	 	*fir_coefs	The impulse response coefficients.
 * @param[in]		n_coef	 	The number of samples to average over.
 * @param[in]     	blocksize	The width of samples being given.
 * @param[out]	FIR_T *filt	Pointer to an initialized struct.

 * @returns	 On return, all elements of the structure are allocated in
 *		 memory, with the output data being initialized to zero.
 *
 */
FIR_T *init_fir(float *fir_coefs, int n_coef, int blocksize);

/*!
 * @brief Calculate discrete-time convolution
 * 
 * Takes a pointer to an initialized struct and calculates the
 * discrete-time convolution of input signal x.
 *  
 * @param[in]	 	*s 	Structure holding data for calculations.
 * @param[in]		*x 	Input signal data values.
 * @param[in]		*y 	Output signal data values.
 *
 */
void calc_fir(FIR_T *s, float *x, float *y);

/*!
 * @brief Free any reserved memory used to calculate the discrete-time convolution.
 * 
 * Takes the structure used to calculate the discrete-time convolution and
 * frees and reserved memory used.
 *
 * @param[in] 		*s 	Structure holding data for calculations.
 *
 */
void destroy_fir(FIR_T *s);

#endif