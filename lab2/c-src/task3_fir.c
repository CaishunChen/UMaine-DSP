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
            h = (float *)malloc(m*sizeof(float));

            // Allocate memory for inputs x[i] and outputs y[i] of length "blocksize"
            x = (float *)malloc(blocksize*sizeof(float));
            y = (float *)calloc((2*blocksize), sizeof(float));
        
            //! Set values for biquad coefficients and input x[n]

            // impulse response vector h of length m
            for (i = 0; i < sizeof(h); i++) {
                h[i] = 1;
            }

            if (h==NULL  || x==NULL || y == NULL) {
                       flagerror(MEMORY_ALLOCATION_ERROR);
                       while(1);
            }

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
                       putblock(filt->y);                   //!< Output on DAC (Pin: PA5)
            }
}