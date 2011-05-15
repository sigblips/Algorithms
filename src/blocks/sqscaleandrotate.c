#ifndef __x86_64__
    #define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sq_dsp.h"

unsigned int data_len = 1000000;
float R = 1;
float theta = 0;

int main(int argc, char **argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "r:t:l:")) != -1)
    {
        switch (opt)
        {
            case 'l':
                sscanf(optarg, "%u", &data_len);
                break;
            case 'r':
                sscanf(optarg, "%f", &R);
                break;
            case 't':
                sscanf(optarg, "%f", &theta);
                break;
        }
    }
    
    int status = sq_scaleandrotate(stdin, stdout, data_len, R, theta);
    
    if(status < 0)
    {
        fprintf(stderr, "sqscaleandrotate: bad args.");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}
