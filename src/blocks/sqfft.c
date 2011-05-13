#ifndef __x86_64__
#   define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include <fftw3.h>

#include "sq_dsp.h"
#include "sq_utils.h"

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

int main(int argc, char *argv[])
{
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
    
    int status = sq_fft(stdin, stdout, fft_len, is_inverted, is_measured);
    
    if(status < 0)
    {
        print_usage(usage_text);
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}