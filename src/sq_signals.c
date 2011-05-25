#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "sq_utils.h"
#include "sq_constants.h"
#include "sq_signals.h"

int sq_gen_sine(FILE* outstream, unsigned int nsamples, unsigned int length, unsigned int sin_arr_length, float wavelength, float SNR)
{
    if((nsamples <= 0) || (nsamples > MAX_SMPLS_LEN))
        return err_arg_bounds;
    
    unsigned int i;
    unsigned int smpli;
    unsigned int index;
    
    // generate LUT's for sine and cosine
    float* Sin = malloc(sin_arr_length * sizeof(float));
    float* Cos = malloc(sin_arr_length * sizeof(float));
    float* smpls_out = malloc(nsamples* 2 * sizeof(float));
    
    for (index = 0; index < sin_arr_length; ++index)
    {
        Sin[index] = (float)sin(index * 2 * PI / sin_arr_length);
        Cos[index] = (float)cos(index * 2 * PI / sin_arr_length);
    }    
    
    for (i = 0; i < length; ++i)
    {
        for (smpli = 0; smpli < nsamples; smpli++)
        {
            index = (int) ((float)(i*nsamples + smpli) / wavelength);
            index = index%sin_arr_length;
            smpls_out[smpli<<1 + REAL] = Sin[index] * SNR + sq_randgaus();
            smpls_out[smpli<<1 + IMAG] = Cos[index] * SNR + sq_randgaus();
            //printf("%f\n", smpls_out[smpli<<1 + REAL]);
        }
        fwrite(smpls_out, 8, nsamples, stdout);
    }
    
    free(Sin);
    free(Cos);
    free(smpls_out);
    
    return 0;
}
