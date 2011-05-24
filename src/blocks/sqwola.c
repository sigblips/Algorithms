#ifndef __x86_64__
    #define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "sq_dsp.h"
#include "sq_utils.h"

//          1         2         3         4         5         6         7
// 123456789012345678901234567890123456789012345678901234567890123456789012 
char *usage_text[] = {
    "                                                                        ",
    "NAME                                                                    ",
    "  sqwola - performs weight-overlap-add window on data in front of       ",
    "           FFT (sqfftw) to improve channel response characteristics     ",
    "SYNOPSIS                                                                ",
    "  sqwola [OPTIONS]                                                      ",
    "DESCRIPTION                                                             ",
    "  -l  pos. integer (required), samples length of subsequent FFT         ",
    "  -f  pos. odd integer (required), number of folds                      ",
    "  -o  pos. integer (required), overlap percentage: 0, 25, or 50         ",
    "  -w  flag, dump window coefficients to stdout and then exit            ",
    "                                                                        "
};

unsigned int fftlen;
unsigned int folds;
unsigned int overlap; 
unsigned char is_window_dump = 0;

int main(int argc, char *argv[]) {
    unsigned int wndwi, readi, smpli, ffti;
    
    unsigned int readlen;
    
    unsigned char argflags = 0;
    int opt;
    
    while ((opt = getopt(argc, argv, "l:f:o:w")) != -1) {
        switch (opt) {
            case 'l':
                sscanf(optarg, "%u", &fftlen);
                argflags |= 0x01;
                break;
            case 'f':
                sscanf(optarg, "%u", &folds);
                argflags |= 0x02;
                break;
            case 'o':
                sscanf(optarg, "%u", &overlap);
                argflags |= 0x04;
                break;
            case 'w':
                is_window_dump = 1;
                break;
        }
    }
    if (!(argflags == 0x07)) {
        print_usage(usage_text);
        exit(EXIT_FAILURE);
    }
    
    int status = sq_wola(stdin, stdout, fftlen, folds, overlap, is_window_dump);
    
    if(status < 0)
    {
        print_usage(usage_text);
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}
    
    