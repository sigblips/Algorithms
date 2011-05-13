#ifndef SQ_DSP_H
#define SQ_DSP_H

#include <stdio.h>

/**
 * Takes 2-channel (quadrature) 8-bit data from the input stream,
 * and writes samples in the form of floats to the output stream,
 * in chunks of a given number of samples.
 * @param instream Input stream with 2-channel 8-bit data.
 * @param outstream Output stream of floats
 * @return Code; negative if error.
 */
int sq_sample(FILE* instream, FILE* outstream);

/**
 * 
 */
int sq_power(FILE* instream, FILE* outstream, unsigned int nsamples);

#endif