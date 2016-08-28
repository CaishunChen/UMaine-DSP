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
            int NUM_STAGES = 4;
	float g = 1.633862e-02;
            int blocksize;
 
            float *x;
            float *y;
            float *biquad_coefs;

	/* Blocksize */
	blocksize = getblocksize();

	/* Input x, Output y, Coefficients pCoeffs */
            x = (float *)malloc(blocksize*sizeof(float));
            y = (float *)calloc(blocksize, sizeof(float));
            biquad_coefs = (float *)calloc(NUM_STAGES*5, sizeof(float));

	biquad_coefs = (float *)calloc(NUM_STAGES*5, sizeof(float));
	biquad_coefs[0] = 1.0000000000*g;
	biquad_coefs[1] = 1.0580134541*g;
	biquad_coefs[2] = 0.8100000000*g;
	biquad_coefs[3] = 0.0590522271;
	biquad_coefs[4] = 0.8836000000;
	biquad_coefs[5] = 1.0000000000;
	biquad_coefs[6] = -1.6180339887;
	biquad_coefs[7] = 1.0000000000;
	biquad_coefs[8] = -1.1522652609;
	biquad_coefs[9] = 0.8836000000;
	biquad_coefs[10] = 1.0000000000;
	biquad_coefs[11] = -1.8830919023;
	biquad_coefs[12] = 0.9801000000;
	biquad_coefs[13] = -0.9499209086;
	biquad_coefs[14] = 0.7140250000;
	biquad_coefs[15] = 1.0000000000;
	biquad_coefs[16] = 1.4256104387;
	biquad_coefs[17] = 0.6400000000;
	biquad_coefs[18] = -0.0923020637;
	biquad_coefs[19] = 0.5402250000;

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
}