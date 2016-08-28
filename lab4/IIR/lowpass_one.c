/*
 * This program takes the biquad calculation functions and uses
 * data from a function generator, executes the calculation, and
 * outputs the result in the DAC.
 * 
 * An input waveform is copied to the output DAC.
 *
 */
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ece486_biquad.h"

int main(void)
{
            char lcd_str[8];

            BIQUAD_T *filt = (BIQUAD_T *)malloc(sizeof(BIQUAD_T *));

            //! Declare number of NUM_STAGES, scale factor G, and blocksize
            int NUM_STAGES = 5;
            int blocksize;
 
            float *x;
            float *y;
            float *biquad_coefs;

	/* Blocksize */
	blocksize = getblocksize();

	/* Input x, Output y, Coefficients pCoeffs */
            x = (float *)calloc(blocksize, sizeof(float));
            y = (float *)calloc(blocksize, sizeof(float));
            biquad_coefs = (float *)calloc(NUM_STAGES*5, sizeof(float));

	float g = 0.000024;
	biquad_coefs[0] = 1.000000;
	biquad_coefs[1] = -1.790000;
	biquad_coefs[2] = 1.000000;
	biquad_coefs[3] = -1.863335;
	biquad_coefs[4] = 0.970807;
	biquad_coefs[5] = 1.000000;
	biquad_coefs[6] = -1.715704;
	biquad_coefs[7] = 1.000000;
	biquad_coefs[8] = -1.863743;
	biquad_coefs[9] = 0.942534;
	biquad_coefs[10] = 1.000000;
	biquad_coefs[11] = -1.449767;
	biquad_coefs[12] = 1.000000;
	biquad_coefs[13] = -1.867948;
	biquad_coefs[14] = 0.907822;
	biquad_coefs[15] = 1.000000;
	biquad_coefs[16] = 0.193940;
	biquad_coefs[17] = 1.000000;
	biquad_coefs[18] = -1.872091;
	biquad_coefs[19] = 0.880842;
	biquad_coefs[20] = 1.000000;
	biquad_coefs[21] = -1.813523;
	biquad_coefs[22] = 1.000000;
	biquad_coefs[23] = -1.869482;
	biquad_coefs[24] = 0.991253;

            /*
             * Set up ADCs, DACs, GPIO, Clocks, DMAs, and Timer
             */
            initialize(FS_50K, MONO_IN, MONO_OUT);

            filt = init_biquad(NUM_STAGES, g, biquad_coefs, blocksize);

            sprintf(lcd_str, "IIR");
            BSP_LCD_GLASS_DisplayString( (uint8_t *)lcd_str);            

            while(1){	
                       getblock(x);                   //!< Get input sample on ADC (Pin: PA1)
                       DIGITAL_IO_SET();          //!< Measure execution time of calculation (Pin: PD0)
                       calc_biquad(filt, x, y);
                       DIGITAL_IO_RESET();      //!< Done measuring execution time
                       putblock(y);                   //!< Output on DAC (Pin: PA5)
            }

            free(x);
            free(y);
            free(biquad_coefs);
            free(filt);
}