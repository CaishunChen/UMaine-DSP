/*!
 * @file
 * 
 * @brief This file contains the definititions of the functions for calculating
 * the running average of an input signal.
 * 
 * @author ECE486 Lab Group 10
 * @author Chris Eustis
 * @author Josh Scripture
 * @author Nabil Chowdhoury
 * 
 * @date Feb 5, 2016
 * 
 * The structure of which holds the data necessary to perfom the running 
 * average calculations is defined, along with the functions to initialize
 * the structure, calculate the running average, and free and reserved
 * memory when complete.
 * 
 */

#ifndef ECE486_RUNNING_MEAN_H
#define ECE486_RUNNING_MEAN_H

/*!
 * @brief A structure typedef for storing data in which to calculate the running
 * average of an input signal
 * 
 * The structure holds data of the last input samples of blocksize to use to
 * maintain a running average. The structure also contains the number of samples
 * to average over and the blocksize to know how many samples have been given.
 * 
 */
struct mean_value {
 	double *lastM;		//!< Last M samples of input
 	double *block;		//!< 
 	double *y;		//!< Output of running average
	int blocksize;		//!< Blocksize of input signal samples
	int M;			//!< Sample size
	int j;			//!< 

};

void print_output(struct mean_value);
struct mean_value init_struct(struct mean_value, int, int);
struct mean_value calc_running_mean(struct mean_value, double *);
void terminate(struct mean_value);

#endif