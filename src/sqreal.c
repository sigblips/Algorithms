#ifndef __x86_64__
#   define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//          1         2         3         4         5         6         7
// 123456789012345678901234567890123456789012345678901234567890123456789012
char *usage_text[] =
{
    "                                                                        ",
    "NAME                                                                    ",
    "  sqreal - inputs time-series of complex (real,imag) float coefficient  ",
    "           pairs.  Outputs only the real coefficients and discards the  ",
    "           imaginary coefficients: (r1,i1)(r2,i2)... --> r1, r2, ...    ",
    "SYNOPSIS                                                                ",
    "  sqreal [OPTIONS] ...                                                  ",
    "DESCRIPTION                                                             ",
    "  -l  pos. integer (required),  length of sample buffer (number of      ",
    "      real,imag coefficient pairs input with a block read at a time and ",
    "      number of real coefficients output with a block write at a time)  ",
    "                                                                        "
};

unsigned int sblen = 0;

typedef float cmplx[2];

cmplx *sbfr;
float *rbfr;

void stdout_usage();

int main(int argc, char *argv[])
{
    int i;

    int opt;

    while ((opt = getopt(argc, argv, "l:")) != -1)
    {
        switch (opt)
        {
            case 'l':
                sscanf(optarg, "%u", &sblen);
                break;
        }
    }

    if (!(sblen > 0))
    {
        stdout_usage();
        exit(EXIT_FAILURE);
    }

    sbfr = malloc(sblen * sizeof(cmplx));
    rbfr = malloc(sblen * sizeof(float));

    while (fread(sbfr, sizeof(cmplx), sblen, stdin) == sblen)
    {
        for (i = 0; i < sblen; i++)
            rbfr[i] = sbfr[i][0];
        fwrite(rbfr, sizeof(float), sblen, stdout);
    }

    free(rbfr);
    free(sbfr);

    exit(EXIT_SUCCESS);
}

void stdout_usage()
{
    unsigned int i;

    for (i = 0; i < (sizeof(usage_text) / sizeof(char *)); i++)
        fprintf(stderr, "%s\n", usage_text[i]);
}

