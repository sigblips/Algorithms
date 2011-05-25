#ifndef SQ_SIGNALS_H
#define SQ_SIGNALS_H

#include <stdio.h>

int sq_gen_sine(FILE* outstream,
                unsigned int nsamples,
                unsigned int length,
                unsigned int sin_arr_length,
                float wavelength,
                float SNR );

#endif
