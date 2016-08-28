/*!
 * @file ece486_nco.h
 * 
 * @brief Subroutines to implement numerically controlled oscillators.
 * Multiple subroutine calls are used to create sample sequences
 * for sinusoidal functions with programmable frequency and phase.
 *                            y(n) = cos(2 pi f0 n + theta)
 * 
 * @author ECE486 Lab Group 10
 * @author Chris Eustis
 * @author Josh Scripture
 * @author Nabil Chowdhoury
 * 
 * @date April 8, 2016
 * 
 * 
 */

#ifndef ECE486_NCO
#define ECE486_NCO

#define N 512
#define PI 3.14159265358979323846

/*!
 * @brief A structure typedef for storing data which is used in the "ece486_nco.c" file
 * for producing NCO output sample values.
 * 
 * The structure holds the discrete-time frequency and the phase of the output sample
 * sequence in cycles/sample and radians, respectively.
 * 
 */
typedef struct {
        float f0;         //!< Discrete-time frequency for the output sample sequence (cycles/sample)
        float theta;    //!< Phase of the output sample sequence (radians)
        float value;
        int prev;
        float phi_delay;
        float f_i;
        int Fs;
        int last_index;
} NCO_T;
        
/*!
 * @brief Initialize and reserve memory of data struture
 * 
 * Allocates memory for the necessary data that is stored in the structure
 * for use when producing the NCO output sequence.
 * 
 * @param[in]  f0                  Initial NCO discrete-time frequency for the output sample sequence (cycles/sample)
 * @param[in]   theta            Initial phase of the output sample sequence (radians)

 * @returns  On return, a pointer to a NCO_T data type structure.
 *  
 */
NCO_T *init_nco(float f0, float theta);
        
/*!
 * @brief Calculates the next n_samples values of the NCO output sequency
 * 
 * Definitiion 
 *
 * @param[in]   s                  Pointer to initialized NCO_T structure
 * @param[in]   y                  Caller-supplied array, replaced by NCO output samples
 * @param[in]   n_samples   Number of NCO output samples to generate

 * @returns  On return, y[i] (for i = 0, 1, ..., n_samples-1) contains the next
 * n_samples values of the NCO output sequence. Subsequent calls to 
 * nco_get_samples() continues to return NCO output samples with no
 * phase discontinuities from one call to the next.
 *  
 */
void nco_get_samples(NCO_T *s, float *y, int n_samples);

/*!
 * @brief Set new frequency for NCO values
 * 
 * Modifies the NCO_T structure to operate at an updated frequency.
 * 
 * @param[in]   s           Pointer to NCO_T
 * @param[in]   f_new    New NCO frequency (cycles/sample)

 * @returns  On return, the NCO_T structure, s, is modified where subsequent calls
 * to nco_get_samples() will operate at frequency f_new (no loss of phase continuity)
 *  
 */
void nco_set_frequency(NCO_T *s, float f_new);

/*!
 * @brief Set phase shift for NCO values
 * 
 * Modifies the NCO_T structure to operate with an updated phase shift.
 * 
 * @param[in]   s           Pointer to NCO_T
 * @param[in]   theta     Phase shift (radians)

 * @returns  On return, the NCO_T structure, s, is modified where subsquent calls
 * to nco_get_samples() will operate with the phase shift given by theta (in radians).
 *  
 */
void nco_set_phase(NCO_T *s, float theta);

/*!
 * @brief Free any allocated memory
 * 
 * Releases any allocated memory required within the NCO_T s structure.
 * 
 * @param[in]   s           Pointer to NCO_T
 *  
 */
void destroy_nco(NCO_T *s);

#endif
