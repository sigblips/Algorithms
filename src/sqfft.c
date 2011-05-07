#ifndef __x86_64__
#   define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include <fftw3.h>

//          1         2         3         4         5         6         7
// 123456789012345678901234567890123456789012345678901234567890123456789012
char *usage_text[] =
{
    "                                                                        ",
    "NAME                                                                    ",
    "  sqfftw - computes forward FFT.  Input is time-series of float values: ",
    "           (real)(imag)(real)(imag)...  Output is float values          ",
    "           arranged: (most neg. real)(most neg. imag) ... (DC real)     ",
    "           (DC imag) ... (most pos. real)(most pos. imag)               ",
    "SYNOPSIS                                                                ",
    "  sqfftw [OPTIONS] ...                                                  ",
    "DESCRIPTION                                                             ",
    "  -l  integer length of transform                                       ",
    "  -i  invert spectrum neg. <--> pos.                                    ",
    "  -m  measure plan instead of estimate.  This will cause an initial     ",
    "      delay but should result in an optimized transform.                ",
    "                                                                        "
};

unsigned char is_inverted = 0;
unsigned char is_measured = 0;

unsigned int fft_len = 0;

fftwf_complex *fft_bfr;
fftwf_plan plan;

void stdout_usage();

int main(int argc, char *argv[])
{
    int i;

    int opt;

    while ((opt = getopt(argc, argv, "l:im")) != -1)
    {
        switch (opt)
        {
            case 'l':
                sscanf(optarg, "%u", &fft_len);
                break;
            case 'i':
                is_inverted = 1;
                break;
            case 'm':
                is_measured = 1;
                break;
        }
    }

    if (!(fft_len > 0))
    {
        stdout_usage();
        exit(EXIT_FAILURE);
    }

    fft_bfr = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * fft_len);
    plan = fftwf_plan_dft_1d(fft_len, fft_bfr, fft_bfr,
                             FFTW_FORWARD, (is_measured ? FFTW_MEASURE : FFTW_ESTIMATE));

    while (fread(fft_bfr, sizeof(fftwf_complex), fft_len, stdin) == fft_len)
    {
        if (is_inverted)
            for (i = 0; i < fft_len; i++)
                fft_bfr[i][1] = -fft_bfr[i][1];  // conjugate
        fftwf_execute(plan);
//  write negative channels first ...
        fwrite(&fft_bfr[fft_len/2], sizeof(fftwf_complex), fft_len / 2, stdout);
//  ... then positive channels
        fwrite(&fft_bfr[0], sizeof(fftwf_complex), fft_len / 2, stdout);
    }

    fftwf_destroy_plan(plan);
    fftwf_free(fft_bfr);

    exit(EXIT_SUCCESS);
}

void stdout_usage()
{
    unsigned int i;

    for (i = 0; i < (sizeof(usage_text) / sizeof(char *)); i++)
        printf("%s\n", usage_text[i]);
}
