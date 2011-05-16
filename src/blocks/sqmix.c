#ifndef __x86_64__
    #define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "sq_constants.h"
#include "sq_dsp.h"

unsigned int data_len = 1000000;
float channel = 0.0;
float rad_per_sample = 0.0;
const float TWO_PI = 2.0 * M_PI;

int main(int argc, char **argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "l:r:c:")) != -1)
    {
        switch (opt)
        {
            case 'l':
                sscanf(optarg, "%u", &data_len);
                break;
            case 'r':
                sscanf(optarg, "%f", &rad_per_sample);
                break;
            case 'c':
                sscanf(optarg, "%f", &channel);
                rad_per_sample = TWO_PI * (channel / (float) SQ_STAGE1_FFT_LEN);  
                break;
        }
    }
    
    int status = sq_mix(stdin, stdout, data_len, rad_per_sample);
    
    if(status < 0)
    {
        fprintf(stderr, "sqmix: bad args.");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}
