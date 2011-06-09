#ifndef __x86_64__
#define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include "sq_dsp.h"
#include "sq_utils.h"

unsigned int smpls_len = 1000000;
float real_delta = 0.0;
float imag_delta = 0.0;

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "r:i:l:")) != -1)
    {
        switch (opt)
        {
            case 'r':
                sscanf(optarg, "%f", &real_delta);
                break;
            case 'i':
                sscanf(optarg, "%f", &imag_delta);
                break;
            case 'l':
                sscanf(optarg, "%u", &smpls_len);
                break;
        }
    }

    int status = sq_offset(stdin, stdout, smpls_len, real_delta, imag_delta);
    
    if(status < 0)
    {
        fprintf(stderr, "%s encountered a fatal error.", argv[0]);
        sq_error_handle(status);
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}
