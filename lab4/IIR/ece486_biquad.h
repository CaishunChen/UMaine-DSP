/*!
 * @file
 * 
 * @brief This file contains the declarations of the functions 
 * for implementation of the biqaud filter calculations.
 * 
 * @author ECE486 Lab Group 10
 * @author Chris Eustis
 * @author Josh Scripture
 * @author Nabil Chowdhoury
 * 
 * @date Feb 19, 2016
 * 
 * 
 */

#ifndef ECE486_IIR_H
#define ECE486_IIR_H


/*!
 * @brief A structure typedef for storing data which is used in the "ece486_biquad.c" file
 * for the transposed Direct Form II calculation.
 * 
 * The structure holds the output array pointer, the coefficient array pointer, the number of 
 * sections and elements in each block, and the system scale factor. Additionally, the 
 * previous values used in calculation are maintaned to perform further calculations.
 * 
 */
typedef struct {
	int sections;		//!< Number of sections
	float g;			//!< Scale factor
	float *biquad_coefs;	//!< System coefficients
	int blocksize;		//!< Blocksize
	float *v1;		//!< Interim value for calculations
	float *v2;		//!< Interim value for calculations
	float v1_prev;		//!< Previous output values
	float v2_prev;		//!< Previous input values
	float **z_delay;

} BIQUAD_T;

/*!
 * @brief Initialize and reserve memory of data struture
 * 
 * Allocates memory for the necessary data that is stored in the structure
 * for use when calculating discrete-time convolution.
 * 
 * @param[in]	 	sections		The number of second order systems
 * @param[in]		g	 		The scaling factor of the overall system
 * @param[in]     	*biquad_coefs		The coefficients for each system
 * @param[in]		blocksize		The number of samples being given

 * @returns	 On return, all elements of the structure are initialized to zero and memory is
 * 		 allocated
 * 	
 */
BIQUAD_T *init_biquad(int sections, float g, float *biquad_coefs, int blocksize);

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
void calc_biquad(BIQUAD_T *s, float *x, float *y);

/*!
 * @brief Free any reserved memory used to calculate the discrete-time convolution.
 * 
 * Takes the structure used to calculate the discrete-time convolution and
 * frees and reserved memory used.
 *
 * @param[in] 		*s 	Structure holding data for calculations.
 *
 */
void destroy_biquad(BIQUAD_T *s);

 #endif