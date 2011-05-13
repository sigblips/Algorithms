#ifndef __x86_64__
#define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include "sq_constants.h"

uint64_t total_bytes_next_trigger = TOTAL_BYTES_TRIGGER_VAL;

signed char smpls_in[SMPLS_PER_READ][2];

float smpls_out[SMPLS_PER_READ][2];

uint64_t total_bytes = 0;

void mylog(char *msg);

int main(int argc, char **argv)
{
    char msg[99];

    unsigned int smpli;

    while (fread(smpls_in, 2, SMPLS_PER_READ, stdin) == SMPLS_PER_READ)
    {
        for (smpli = 0; smpli < SMPLS_PER_READ; smpli++)
        {
            smpls_out[smpli][REAL] = (float) smpls_in[smpli][REAL];
            smpls_out[smpli][IMAG] = -(float) smpls_in[smpli][IMAG];
        }
        fwrite(smpls_out, 8, SMPLS_PER_READ, stdout);
        total_bytes += (SMPLS_PER_READ * 2);
        if (total_bytes >= total_bytes_next_trigger)
        {
            total_bytes_next_trigger += TOTAL_BYTES_TRIGGER_VAL;
            sprintf(msg, "total bytes processed %lu", total_bytes);
            //      mylog(msg);
        }
    }

    sprintf(msg, "total bytes processed %lu", total_bytes);
    //  mylog(msg);

    exit(EXIT_SUCCESS);
}
