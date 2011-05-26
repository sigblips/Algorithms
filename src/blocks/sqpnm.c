#ifndef __x86_64__
    #define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sq_utils.h"
#include "sq_imaging.h"

//          1         2         3         4         5         6         7
// 123456789012345678901234567890123456789012345678901234567890123456789012
char *usage_text[] =
{
    "                                                                        ",
    "NAME                                                                    ",
    "  sqpnm - reads series of float values in raster-scan order (top-left to",
    "          bottom-right), scales the values, and then outputs the values ",
    "          in 8-bit grayscale (PGM) image format.  Default scale         ",
    "          algorithm is linear.  Smallest value scaled to 0.  Largest    ",
    "          value scaled to 255.                                          ",
    "SYNOPSIS                                                                ",
    "  sqpnm [OPTIONS] ...                                                   ",
    "DESCRIPTION                                                             ",
    "  -r  pos. integer (required), image rows                               ",
    "  -c  pos. integer (required), image columns                            ",
    "  -p  flag, scale appropriate for power values which have an exponential",
    "      distribution in the right tail.  (m - s) scaled to 0.  (m + 3s)   ",
    "      scaled to 255. Values outside of range are clipped.               ",
    "  -x  flag, power values not scaled                                     ",
    "                                                                        "
};

float *imgbfr;
unsigned int rows = 0;
unsigned int cols = 0;

void (*scale_fnctn)(float* img_buf, int rows, int cols);

int main(int argc, char *argv[])
{
    int opt;

    scale_fnctn = sq_linear_scale;

    while ((opt = getopt(argc, argv, "r:c:px")) != -1)
    {
        switch (opt)
        {
            case 'r':
                sscanf(optarg, "%u", &rows);
                break;
            case 'c':
                sscanf(optarg, "%u", &cols);
                break;
            case 'p':
                scale_fnctn = sq_power_scale;
                break;
            case 'x':
                scale_fnctn = sq_no_scale;
                break;
        }
    }

    imgbfr = malloc(sizeof(float) * rows * cols);
    
    int read_status = sq_read_img(stdin, imgbfr, rows, cols);
    
    if(read_status < 0)
    {
        fprintf(stderr, "Read error, bad rows/cols count");
        free(imgbfr);
        exit(EXIT_FAILURE);
    }

    scale_fnctn(imgbfr, rows, cols);
    sq_write_pnm(stdout, imgbfr, rows, cols);

    free(imgbfr);

    exit(EXIT_SUCCESS);
}
