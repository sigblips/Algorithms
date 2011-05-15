#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <fftw3.h>

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

    while (fread(smpls_bfr, sizeof(float) * 2, nsamples, instream) == nsamples)
    {
        for (smpli = 0; smpli < nsamples ; smpli++)
        {
            smpls_bfr[(smpli<<1)+0] =
                (smpls_bfr[(smpli<<1)+0] * smpls_bfr[(smpli<<1)+0]) +
                (smpls_bfr[(smpli<<1)+1] * smpls_bfr[(smpli<<1)+1]);
            smpls_bfr[(smpli<<1)+1] = 0.0;
        }

        fwrite(smpls_bfr, sizeof(float) * 2, nsamples, outstream);
    }

    free(smpls_bfr);

    return 0;
}

int sq_sum(FILE* instream, FILE* outstream, unsigned int nsamples)
{

    if (!((nsamples >= 2) && (nsamples <= MAX_SMPLS_LEN)))
        return err_arg_bounds;

    float *smpls_bfr;
    float *sum_bfr;

    smpls_bfr = malloc(nsamples * 4 * 2);
    sum_bfr = malloc(nsamples * 4 * 2);

    unsigned int smpli;

    for (smpli = 0; smpli < nsamples; smpli++)
    {
        sum_bfr[(smpli<<1)+0] = 0.0;
        sum_bfr[(smpli<<1)+1] = 0.0;
    }

    while (fread(smpls_bfr, 8, nsamples, instream) == nsamples)
    {
        for (smpli = 0; smpli < nsamples; smpli++)
        {
            sum_bfr[(smpli<<1)+0] += (smpls_bfr[(smpli<<1)+0] / (float) nsamples);
            sum_bfr[(smpli<<1)+1] += (smpls_bfr[(smpli<<1)+1] / (float) nsamples);
        }
    }

    fwrite(sum_bfr, 8, nsamples, outstream);

    free(sum_bfr);
    free(smpls_bfr);

    return 0;
}

int sq_window(FILE* instream, FILE* outstream, unsigned int wndw_len)
{
    float *wndw_bfr;
    float *in_bfr;
    float *out_bfr;

    if (!((wndw_len >= 2) && (wndw_len <= MAX_WNDW_LEN)))
        return err_arg_bounds;

    wndw_bfr = malloc(wndw_len * 4);
    in_bfr = malloc(wndw_len * 4 * 2);
    out_bfr = malloc(wndw_len * 4 * 2);

    unsigned int wndwi, bfri;

    for (wndwi = 0; wndwi < wndw_len; wndwi++)
    {
        wndw_bfr[wndwi] =
            cos(((((float)wndwi) - ((wndw_len - 1.0) / 2.0)) / ((wndw_len - 1.0) / 2.0)) * (M_PI / 2.0));
    }

    fread(&in_bfr[(wndw_len/2)*2], 8, wndw_len / 2, instream);
    memcpy(&in_bfr[0], &in_bfr[(wndw_len/2)*2], (wndw_len / 2)*4*2);

    while (fread(&in_bfr[(wndw_len/2)*2], 8, wndw_len / 2, instream) == (wndw_len / 2))
    {
        for (bfri = 0; bfri < wndw_len; bfri++)
        {
            out_bfr[(bfri<<1)+0] = in_bfr[(bfri<<1)+0] * wndw_bfr[bfri];
            out_bfr[(bfri<<1)+1] = in_bfr[(bfri<<1)+1] * wndw_bfr[bfri];
        }
        fwrite(out_bfr, 8, wndw_len, outstream);
        memcpy(&in_bfr[0], &in_bfr[(wndw_len/2)*2], (wndw_len / 2)*4*2);
    }

    free(wndw_bfr);
    free(in_bfr);
    free(out_bfr);

    return 0;
}

int sq_component(FILE* instream, FILE* outstream, unsigned int nsamples, int component)
{
    if (nsamples <= 0)
        return err_arg_bounds;
    if ((component != 0) && (component != 1))
        return err_arg_bounds;

    int i;
    cmplx *sbfr;
    float *rbfr;

    sbfr = malloc(nsamples * sizeof(cmplx));
    rbfr = malloc(nsamples * sizeof(float));

    while (fread(sbfr, sizeof(cmplx), nsamples, instream) == nsamples)
    {
        for (i = 0; i < nsamples; i++)
            rbfr[i] = sbfr[i][component];
        fwrite(rbfr, sizeof(float), nsamples, outstream);
    }

    free(rbfr);
    free(sbfr);

    return 0;
}

int sq_real(FILE* instream, FILE* outstream, unsigned int nsamples)
{
    return sq_component(instream, outstream, nsamples, REAL);
}

int sq_imag(FILE* instream, FILE* outstream, unsigned int nsamples)
{
    return sq_component(instream, outstream, nsamples, IMAG);
}

int sq_fft(FILE* instream, FILE* outstream, unsigned int fft_len, unsigned char is_inverted, unsigned char is_measured)
{
    if (fft_len <= 0)
        return err_arg_bounds;

    fftwf_complex *fft_bfr;
    fftwf_plan plan;

    int i;

    fft_bfr = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * fft_len);
    plan = fftwf_plan_dft_1d(fft_len, fft_bfr, fft_bfr,
                             FFTW_FORWARD, (is_measured ? FFTW_MEASURE : FFTW_ESTIMATE));

    while (fread(fft_bfr, sizeof(fftwf_complex), fft_len, instream) == fft_len)
    {
        if (is_inverted)
            for (i = 0; i < fft_len; i++)
                fft_bfr[i][1] = -fft_bfr[i][1];  // conjugate
        fftwf_execute(plan);
        //  write negative channels first ...
        fwrite(&fft_bfr[fft_len/2], sizeof(fftwf_complex), fft_len / 2, outstream);
        //  ... then positive channels
        fwrite(&fft_bfr[0], sizeof(fftwf_complex), fft_len / 2, outstream);
    }

    fftwf_destroy_plan(plan);
    fftwf_free(fft_bfr);

    return 0;
}

int sq_offset(FILE* instream, FILE* outstream, unsigned int nsamples, float real_delta, float imag_delta)
{
    if (nsamples <= 0)
        return err_arg_bounds;

    unsigned int smpli;
    float *smpls_bfr;

    smpls_bfr = malloc(nsamples * 4 * 2);

    while (fread(smpls_bfr, 8, nsamples, instream) == nsamples)
    {
        for (smpli = 0; smpli < nsamples; smpli++)
        {
            smpls_bfr[(smpli<<1)+0] += real_delta;
            smpls_bfr[(smpli<<1)+1] += imag_delta;
        }

        fwrite(smpls_bfr, 8, nsamples, outstream);
    }

    free(smpls_bfr);

    return 0;
}

int sq_conjugate(FILE* instream, FILE* outstream, unsigned int nsamples)
{
    if (!((nsamples >= 2) && (nsamples <= MAX_SMPLS_LEN)))
        return err_arg_bounds;

    float *data_bfr;
    unsigned int datai;

    data_bfr = malloc(nsamples * sizeof(float) * 2);

    while (fread(data_bfr, 8, nsamples, instream) == nsamples)
    {
        for (datai = 0; datai < nsamples; datai += 1)
            data_bfr[(datai<<1)+1] *= -1.0;

        fwrite(data_bfr, sizeof(float) * 2, nsamples, outstream);
    }

    free(data_bfr);

    return 0;
}

int sq_scaleandrotate(FILE* instream, FILE* outstream, unsigned int nsamples, float scale_factor, float radians)
{
    if (nsamples <= 0)
        return err_arg_bounds;
    
    unsigned int smpli;
    float *smpls_bfr;
    
    smpls_bfr = malloc(nsamples * 4 * 2);
    
    float re, im;
    while (fread(smpls_bfr, 8, nsamples, instream) == nsamples)
    {
        for (smpli = 0; smpli < nsamples; smpli++)
        {
            re = smpls_bfr[(smpli<<1)+0];
            im = smpls_bfr[(smpli<<1)+1];
            smpls_bfr[(smpli<<1)+0] = scale_factor * (re*cos(radians) - im*sin(radians));
            smpls_bfr[(smpli<<1)+1] = scale_factor * (im*cos(radians) + re*sin(radians));
        }
        
        fwrite(smpls_bfr, 8, nsamples, outstream);
    }
    
    free(smpls_bfr);
    
    return 0;
}
