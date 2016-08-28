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

#include "ece486_fir.h"

int main(void)
{
            int i;
            char lcd_str[8];

            FIR_T *filt = (FIR_T *)malloc(sizeof(FIR_T *));

            // Sample size
            int m = 50;
            // Blocksize
            int blocksize;
 
            float *x;
            float *y;
            float *h;

            //!< Determine blocksize
            blocksize = getblocksize();

            // impulse response
            h = (float *)calloc(m, sizeof(float));

            // Allocate memory for inputs x[i] and outputs y[i] of length "blocksize"
            x = (float *)malloc(blocksize*sizeof(float));
            y = (float *)calloc((blocksize), sizeof(float));
        
            //! Set values for biquad coefficients and input x[n]

            // impulse response vector h of length m
            h[0] = 0.001472;
	h[1] = -0.007812;
	h[2] = -0.007515;
	h[3] = -0.009645;
	h[4] = -0.012021;
	h[5] = -0.013997;
	h[6] = -0.015146;
	h[7] = -0.015070;
	h[8] = -0.013414;
	h[9] = -0.009897;
	h[10] = -0.004354;
	h[11] = 0.003233;
	h[12] = 0.012718;
	h[13] = 0.023784;
	h[14] = 0.035954;
	h[15] = 0.048616;
	h[16] = 0.061065;
	h[17] = 0.072564;
	h[18] = 0.082396;
	h[19] = 0.089932;
	h[20] = 0.094661;
	h[21] = 0.096272;
	h[22] = 0.094661;
	h[23] = 0.089932;
	h[24] = 0.082396;
	h[25] = 0.072564;
	h[26] = 0.061065;
	h[27] = 0.048616;
	h[28] = 0.035954;
	h[29] = 0.023784;
	h[30] = 0.012718;
	h[31] = 0.003233;
	h[32] = -0.004354;
	h[33] = -0.009897;
	h[34] = -0.013414;
	h[35] = -0.015070;
	h[36] = -0.015146;
	h[37] = -0.013997;
	h[38] = -0.012021;
	h[39] = -0.009645;
	h[40] = -0.007515;
	h[41] = -0.007812;
	h[42] = 0.001472;

            // if (h==NULL  || x==NULL || y == NULL) {
            //            flagerror(MEMORY_ALLOCATION_ERROR);
            //            while(1);
            // }

            /*
             * Set up ADCs, DACs, GPIO, Clocks, DMAs, and Timer
             */
            initialize(FS_50K, MONO_IN, MONO_OUT);

            filt = init_fir(h, m, blocksize);

            sprintf(lcd_str, "FIR");
            BSP_LCD_GLASS_DisplayString( (uint8_t *)lcd_str);            

            while(1){	
                       getblock(x);                   //!< Get input sample on ADC (Pin: PA1)
                       DIGITAL_IO_SET();          //!< Measure execution time of calculation (Pin: PD0)
                       calc_fir(filt, x, y);
                       DIGITAL_IO_RESET();      //!< Done measuring execution time
                       putblock(y);                   //!< Output on DAC (Pin: PA5)
            }
}