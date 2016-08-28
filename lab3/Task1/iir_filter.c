#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "arm_math.h"
#include "ece486.h"
#include <stdlib.h>
#include <stdint.h>

/* Number of second-order systems */
#define NUM_STAGES		4

int main(void)
{
	arm_biquad_cascade_df2T_instance_f32 S;
	uint32_t blocksize;
	float32_t *biquad_coefs;
	float32_t *x;
	float32_t *y;
	float32_t iir_state_buff[2*NUM_STAGES];
	float g = 1.633862e-02;

	/* Blocksize */
	blocksize = getblocksize();

	/* Input x, Output y, Coefficients pCoeffs */
	x = malloc(blocksize*sizeof(float32_t));
	y = malloc(blocksize*sizeof(float32_t));
	biquad_coefs = malloc(5*NUM_STAGES*sizeof(float32_t));

	biquad_coefs = (float *)calloc(NUM_STAGES*5, sizeof(float));
	biquad_coefs[0] = 1.0000000000*g;
	biquad_coefs[1] = 1.0580134541*g;
	biquad_coefs[2] = 0.8100000000*g;
	// biquad_coefs[3] = 1.0000000000;
	biquad_coefs[3] = 0.0590522271;
	biquad_coefs[4] = 0.8836000000;
	biquad_coefs[5] = 1.0000000000;
	biquad_coefs[6] = -1.6180339887;
	biquad_coefs[7] = 1.0000000000;
	// biquad_coefs[9] = 1.0000000000;
	biquad_coefs[8] = -1.1522652609;
	biquad_coefs[9] = 0.8836000000;
	biquad_coefs[10] = 1.0000000000;
	biquad_coefs[11] = -1.8830919023;
	biquad_coefs[12] = 0.9801000000;
	// biquad_coefs[15] = 1.0000000000;
	biquad_coefs[13] = -0.9499209086;
	biquad_coefs[14] = 0.7140250000;
	biquad_coefs[15] = 1.0000000000;
	biquad_coefs[16] = 1.4256104387;
	biquad_coefs[17] = 0.6400000000;
	// biquad_coefs[21] = 1.0000000000;
	biquad_coefs[18] = -0.0923020637;
	biquad_coefs[19] = 0.5402250000;
	// biquad_coefs[24] = 1.0000000000;

	/* Initiallize the board */
            initialize(FS_50K, MONO_IN, MONO_OUT);

            /* Initialize the filter struct */
	arm_biquad_cascade_df2T_init_f32(&S, NUM_STAGES, biquad_coefs, iir_state_buff);

	while(1) {
		getblock(x);						//!< Get input sample block from ADC
                       DIGITAL_IO_SET();					//!< Measure execution time of calculation (Pin: PD0)
		arm_biquad_cascade_df2T_f32(&S, x, y, blocksize);	//!<Filter Calculation
                       DIGITAL_IO_RESET();					//!< Done measuring execution time
                       putblock(y);						//!< Output on DAC (Pin: PA5)
	}

	free(x);
	free(y);
	free(biquad_coefs);

	return 0;
}