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


int sq_sample(FILE* instream, FILE* outstream, unsigned int nsamples)
{
    if ((nsamples <= 0) || (nsamples > MAX_SMPLS_LEN))
        return err_arg_bounds;
    
    uint64_t total_bytes_next_trigger = TOTAL_BYTES_TRIGGER_VAL;
    signed char *smpls_in;
    float *smpls_out;
    uint64_t total_bytes = 0;
    
    unsigned int smpli;
    
    smpls_in = malloc(nsamples * sizeof(char) * 2);
    if(smpls_in == NULL)
        return err_malloc;
    smpls_out = malloc(nsamples * sizeof(float) * 2);
    if(smpls_out == NULL)
        return err_malloc;
    
    while (fread(smpls_in, 2, nsamples, instream) == nsamples)
    {
        for (smpli = 0; smpli < nsamples; smpli++)
        {
            smpls_out[(smpli<<1) + REAL] = (float) smpls_in[(smpli<<1) + REAL];
            smpls_out[(smpli<<1) + IMAG] = -(float) smpls_in[(smpli<<1) + IMAG];
        }
        fwrite(smpls_out, 8, nsamples, outstream);
        total_bytes += (nsamples * 2);
        if (total_bytes >= total_bytes_next_trigger)
        {
            total_bytes_next_trigger += TOTAL_BYTES_TRIGGER_VAL;
            //sprintf(msg, "total bytes processed %lu", total_bytes);
            //      mylog(msg);
        }
    }
    
    free(smpls_in);
    free(smpls_out);
    
    return 0;
}

float sq_randgaus()
{
    float rand1 = ((float)rand() / RAND_MAX);
    float rand2 = ((float)rand() / RAND_MAX);
    return (float)sqrt(-2 * log(rand1)) * sin(2 * PI * rand2); 
}

void sq_error_print(char* message)
{
    fprintf(stderr, "%s", message);
}

void sq_error_handle(int errcode)
{
    switch(errcode)
    {
        case -1: sq_error_print("Argument(s) out-of-bounds."); break;
        case -2: sq_error_print("Could not open stream."); break;
        case -3: sq_error_print("Could not close stream."); break;
        case -4: sq_error_print("Could not read from stream."); break;
        case -5: sq_error_print("Could not write to stream."); break;
        case -6: sq_error_print("Could not allocate memory."); break;
        default:
            if(errcode < 0)
                sq_error_print("Unhandled error.");
    }
    
    sq_error_print("\n");
}
