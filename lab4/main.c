#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ece486_nco.h"

int main(void)
{
	NCO_T *s = malloc(sizeof(NCO_T));

	int n_samples = 100;
	int f0 = 1200;
	float theta = 0;
	// nco_set_phase(s, theta);

	float *y = calloc(n_samples, sizeof(float));

	s = init_nco(f0, theta);

	nco_get_samples(s, y, n_samples);
	nco_set_frequency(s, 2200);
	// nco_set_phase(s, PI/2);
	nco_get_samples(s, y, n_samples);

	free(y);

	destroy_nco(s);

	return 0;
}
