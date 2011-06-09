#ifndef __x86_64__
#   define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sq_dsp.h"
#include "sq_utils.h"

unsigned int wndw_len = 0;

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "l:")) != -1)
    {
        switch (opt)
        {
            case 'l':
                sscanf(optarg, "%u", &wndw_len);
                break;
        }
    }
    
    int status = sq_window(stdin, stdout, wndw_len);
    
    if(status < 0)
    {
        fprintf(stderr, "%s encountered a fatal error.", argv[0]);
        sq_error_handle(status);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}


