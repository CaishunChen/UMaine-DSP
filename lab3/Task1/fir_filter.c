#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "arm_math.h"
#include "ece486.h"
#include <stdlib.h>
#include <stdint.h>

/* Number of coefficients */
#define NUM_COEFFS		20

/*
*  FIR Coefficients (in reverse order) - Not really sure what these numbers mean/are and should probably use some we know the meaning to
*/
const float32_t fir_coeffs[NUM_COEFFS] = {
	1359, -3920, -8614, -12543, -15212, -16532, -15850, -13755, -10278, -5769, -680, 4477, 9185, 12970, 15451, 16380, 15644, 13374, 9740, 5128
};

int main(void)
{
	arm_fir_instance_f32 S;
	float32_t *x;
	float32_t *y;

	/* Blocksize */
	uint32_t blocksize = getblocksize();

	/* State Buffer */ 
	float32_t firStateF32[blocksize + NUM_COEFFS - 1];

	/* Input x and Output y */
	x = malloc(blocksize * sizeof(float32_t));
	y = malloc(blocksize * sizeof(float32_t));

	/* Initiallize the board */
            initialize(FS_50K, MONO_IN, MONO_OUT);

            /* Initialize the filter struct */
	arm_fir_init_f32(&S, NUM_COEFFS, (float32_t *)&fir_coeffs[0], &firStateF32[0], blocksize);

	while(1) {
		getblock(x);				//!< Get input sample block from ADC
                       DIGITAL_IO_SET();          		//!< Measure execution time of calculation (Pin: PD0)
		arm_fir_f32(&S, x, y, blocksize);	//!< Filter calculation
                       DIGITAL_IO_RESET();      		//!< Done measuring execution time
                       putblock(y);                   		//!< Output on DAC (Pin: PA5)
	}

	free(x);
	free(y);

	return 0;
}