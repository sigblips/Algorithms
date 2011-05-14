#ifndef __x86_64__
    #define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sq_dsp.h"

unsigned int data_len = 1000000;

int main(int argc, char **argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "l:")) != -1)
    {
        switch (opt)
        {
            case 'l':
                sscanf(optarg, "%u", &data_len);
                break;
        }
    }
    
    int status = sq_conjugate(stdin, stdout, data_len);
    
    if(status < 0)
    {
        fprintf(stderr, "sqconjugate: bad args.");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}
