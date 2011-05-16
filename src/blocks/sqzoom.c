#ifndef __x86_64__
#define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include "sq_dsp.h"

unsigned int zoom_len = 0;

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "l:")) != -1)
    {
        switch (opt)
        {
            case 'l':
                sscanf(optarg, "%u", &zoom_len);
                break;
        }
    }

    int status = sq_zoom(stdin, stdout, zoom_len);
    
    if (status < 0)
    {
        printf("sqzoom -l samples-block-size\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
