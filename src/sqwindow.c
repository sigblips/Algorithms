#ifndef __x86_64__
#   define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#define MAX_WNDW_LEN 134217728

unsigned int wndw_len = 0;

float *wndw_bfr;
float *in_bfr;
float *out_bfr;

void mylog(char *msg);

int main(int argc, char **argv)
{

    int opt;

    unsigned int wndwi, bfri;

    while ((opt = getopt(argc, argv, "l:")) != -1)
    {
        switch (opt)
        {
            case 'l':
                sscanf(optarg, "%u", &wndw_len);
                break;
        }
    }

    if (!((wndw_len >= 2) && (wndw_len <= MAX_WNDW_LEN)))
    {
        printf("sqwndw -l window-size\n");
        exit(EXIT_FAILURE);
    }

    wndw_bfr = malloc(wndw_len * 4);
    in_bfr = malloc(wndw_len * 4 * 2);
    out_bfr = malloc(wndw_len * 4 * 2);

    for (wndwi = 0; wndwi < wndw_len; wndwi++)
    {
        wndw_bfr[wndwi] =
            cos(((((float)wndwi) - ((wndw_len - 1.0) / 2.0)) / ((wndw_len - 1.0) / 2.0)) * (M_PI / 2.0));
    }

    fread(&in_bfr[(wndw_len/2)*2], 8, wndw_len / 2, stdin);
    memcpy(&in_bfr[0], &in_bfr[(wndw_len/2)*2], (wndw_len / 2)*4*2);

    while (fread(&in_bfr[(wndw_len/2)*2], 8, wndw_len / 2, stdin) == (wndw_len / 2))
    {
        for (bfri = 0; bfri < wndw_len; bfri++)
        {
            out_bfr[(bfri<<1)+0] = in_bfr[(bfri<<1)+0] * wndw_bfr[bfri];
            out_bfr[(bfri<<1)+1] = in_bfr[(bfri<<1)+1] * wndw_bfr[bfri];
        }
        fwrite(out_bfr, 8, wndw_len, stdout);
        memcpy(&in_bfr[0], &in_bfr[(wndw_len/2)*2], (wndw_len / 2)*4*2);
    }

    free(wndw_bfr);
    free(in_bfr);
    free(out_bfr);

    exit(EXIT_SUCCESS);
}


