#include <stdlib.h>

#include "sq_constants.h"
#include "sq_dsp.h"
#include "sq_utils.h"

int sq_power(FILE* instream, FILE* outstream, unsigned int nsamples)
{
    float *smpls_bfr;
    unsigned int smpli;
    
    if ((nsamples < 2) || (nsamples >= MAX_SMPLS_LEN))
        return err_arg_bounds;
    
    smpls_bfr = malloc(nsamples * sizeof(float) * 2);
    
    while (fread(smpls_bfr, 8, nsamples, instream) == nsamples)
    {
        for (smpli = 0; smpli < nsamples ; smpli++)
        {
            smpls_bfr[(smpli<<1)+0] =
            (smpls_bfr[(smpli<<1)+0] * smpls_bfr[(smpli<<1)+0]) +
            (smpls_bfr[(smpli<<1)+1] * smpls_bfr[(smpli<<1)+1]);
            smpls_bfr[(smpli<<1)+1] = 0.0;
        }

        fwrite(smpls_bfr, 8, nsamples, outstream);
    }

    free(smpls_bfr);
    
    return 0;
}
