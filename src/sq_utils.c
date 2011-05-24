#include <time.h>
#include <stdlib.h>
#include <sys/types.h>

#include "sq_constants.h"
#include "sq_utils.h"

void print_usage(char** usage_text)
{
    unsigned int i;

    for (i = 0; i < (sizeof(usage_text) / sizeof(char)); i++)
        fprintf(stderr, "%s\n", usage_text[i]);
}

void write_log(char* message, FILE* outstream)
{
    struct timeval tv;
    time_t current_seconds;
    struct tm bdt;

    gettimeofday(&tv, NULL);
    current_seconds = tv.tv_sec;
    gmtime_r(&current_seconds, &bdt);

    fprintf(outstream, "%04u-%02u-%02uT%02u:%02u:%02u.%03luZ | %s\n",
            (bdt.tm_year + 1900), (bdt.tm_mon + 1), bdt.tm_mday,
            bdt.tm_hour, bdt.tm_min, bdt.tm_sec,
            (tv.tv_usec / 1000), message);
}

void alloc_char_2d(signed char ** array, uint nrows, unsigned int ncolumns)
{
    array = calloc(nrows, sizeof(signed char *));
    if (array == NULL)
    {
        fprintf(stderr, "out of memory\n");
        return;
    }
    int i;
    for (i = 0; i < nrows; i++)
    {
        array[i] = calloc(ncolumns, sizeof(signed char));
        if (array[i] == NULL)
        {
            fprintf(stderr, "out of memory\n");
            return;
        }
    }
}

void alloc_float_2d(float** array, uint nrows, unsigned int ncolumns)
{
    array = (float **) malloc(nrows * sizeof(float *));
    if (array == NULL)
    {
        fprintf(stderr, "out of memory\n");
        return;
    }
    int i;
    for (i = 0; i < nrows; i++)
    {
        array[i] = (float *) malloc(ncolumns * sizeof(float));
        if (array[i] == NULL)
        {
            fprintf(stderr, "out of memory\n");
            return;
        }
    }
}


int sq_read_array(float inarray[], FILE* outstream, int ncolumns)
{
    if (ncolumns <= 0)
        return err_arg_bounds;

    unsigned int coli;
    unsigned long length = sizeof(inarray) / sizeof(float);

    for (coli = 0; coli < length; ++coli)
    {
        fprintf(outstream, " %e", inarray[coli]);

        if (coli % ncolumns == 0)
            fprintf(outstream, "\n");
    }

    return coli;
}

int sq_read_stream(FILE* instream, FILE* outstream, int ncolumns)
{
    if (ncolumns <= 0)
        return err_arg_bounds;

    unsigned long coli = 0;
    float val;

    while (fread(&val, sizeof(float), 1, instream) == 1)
    {
        fprintf(outstream, " %e", val);
        coli++;

        if (coli % ncolumns == 0)
            fprintf(outstream, "\n");
    }

    return coli;
}

