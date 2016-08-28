/*!
 * @file ece486_nco.c
 * 
 * @brief Subroutines to implement numerically controlled oscillators.
 * Multiple subroutine calls are used to create sample sequences
 * for sinusoidal functions with programmable frequency and phase.
 *                            y(n) = cos(2 PI f0 n + theta)
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ece486_nco.h"

float cos_table[N];

void generate_cos_lut(void)
{
        int i;
        for (i = 0; i < N; i++) {
                  cos_table[i] = (cos(2 * PI * (i / (float)N)));
                  // printf("cos_table[%d]: %f\n", i, cos_table[i]);
        }
}


NCO_T *init_nco(float f0, float theta)
{
        NCO_T *s;
        s = (NCO_T *)malloc(sizeof(s));

        // Generate cosine lookup table
        generate_cos_lut();

        s->f0 = f0;
        s->value = cos_table[0];
        s->prev = 0;

        s->phi_delay = 0;
        s->last_index = 0;

        // Sample rate
        s->Fs = 50000;

        );

        return s;
}

void nco_get_samples(NCO_T *s, float *y, int n_samples)
{
	int i;
	float *phi;

	phi = calloc(n_samples, sizeof(float));

	if (s->phi_delay != 0)
		phi[0] = s->phi_delay;
	else
		phi[0] = s->theta;

	s->phi_delay = phi[0];
	y[0] = cos_table[(int)phi[0]];

	printf("\ny = [");
	printf("%f, ", y[0]);

	float f_i = s->f0 / s->Fs;
        
	for(i = 1; i < n_samples; i++) {
		phi[i] = s->phi_delay + 2 * PI * f_i;
		if (ceil(phi[i]) > N) {
			phi[i] = 0;
		}
		y[i] = cos_table[(int)phi[i]];
		s->phi_delay = phi[i];
		printf("%f, ", y[i]);
	}

	s->phi_delay += 2 * PI * f_i;

	printf("];\n");

	free(phi);
}

void nco_set_frequency(NCO_T *s, float f_new)
{
        s->f0 = f_new;
}

void nco_set_phase(NCO_T *s, float theta)
{
        s->theta = theta *  (N / (2 * PI));
}

void destroy_nco(NCO_T *s)
{
        if (s)
                free(s);
}