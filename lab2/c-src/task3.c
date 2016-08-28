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
            int i;
            char lcd_str[8];

            BIQUAD_T *filt = (BIQUAD_T *)malloc(sizeof(BIQUAD_T *));

            //! Declare number of sections, scale factor G, and blocksize
            int sections = 2;
            float g = 1;
            int blocksize;
 
            float *x;
            float *y;
            float *biquad_coefs;

            //!< Determine blocksize
            blocksize = getblocksize();

            x = (float *)malloc(sections*blocksize*sizeof(float));
            y = (float *)calloc(sections*blocksize, sizeof(float));
            biquad_coefs = (float *)calloc(sections*blocksize, sizeof(float));

            //! Set values for biquad coefficients and input x[n]
            for (i = 0; i < sizeof(biquad_coefs); i++) {
                       biquad_coefs[i] = 1;
            }
            // biquad_coefs[0] = 1;
            // biquad_coefs[1] = 0;
            // biquad_coefs[2] = 0;
            // biquad_coefs[3] = -1;
            // biquad_coefs[4] = 0;


            if (biquad_coefs==NULL  || x==NULL || y == NULL) {
                       flagerror(MEMORY_ALLOCATION_ERROR);
                       while(1);
            }

            /*
             * Set up ADCs, DACs, GPIO, Clocks, DMAs, and Timer
             */
            initialize(FS_50K, MONO_IN, MONO_OUT);

            filt = init_biquad(sections, g, biquad_coefs, blocksize);

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