#ifndef __x86_64__
    # define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <math.h>

#include "sq_signals.h"
#include "sq_utils.h"

unsigned int nsamples = 1000000;
unsigned int length = 16777216;
unsigned int sine_array_length = 128;
float wavelength = 2.4f;
float SNR = 0.01;

int main(int argc, char *argv[])
{
    int opt;
    
    while ((opt = getopt(argc, argv, "l:s:a:w:n")) != -1)
    {
        switch (opt)
        {
            case 'l':
                sscanf(optarg, "%u", &nsamples);
                break;
            case 's':
                sscanf(optarg, "%u", &length);
                break;
            case 'a':
                sscanf(optarg, "%u", &sine_array_length);
                break;
            case 'w':
                sscanf(optarg, "%f", &wavelength);
                break;
            case 'n':
                sscanf(optarg, "%f", &SNR);
                break;
        }
    }
    
    int status = sq_gen_sine(stdout, nsamples, length, sine_array_length, wavelength, SNR);
    
    if(status < 0)
    {
        fprintf(stderr, "%s encountered a fatal error.", argv[0]);
        sq_error_handle(status);
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}