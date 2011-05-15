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
 * Takes a stream of floats (alternating real, imaginary) as input signal
 * and writes the instantaneous power samples to the output stream.
 * @param instream Input stream of float data
 * @param outstream Output stream of float data
 * @return Code; negative if error.
 */
int sq_power(FILE* instream, FILE* outstream, unsigned int nsamples);

int sq_sum(FILE* instream, FILE* outstream, unsigned int nsamples);

int sq_window(FILE* instream, FILE* outstream, unsigned int window_length);

int sq_component(FILE* instream, FILE* outstream, unsigned int nsamples, int component);
int sq_real(FILE* instream, FILE* outstream, unsigned int nsamples);
int sq_imag(FILE* instream, FILE* outstream, unsigned int nsamples);

int sq_fft(FILE* instream, FILE* outstream, 
           unsigned int fft_len, 
           unsigned char is_inverted, 
           unsigned char is_measured );

int sq_offset(FILE* instream, FILE* outstream, 
              unsigned int nsamples, 
              float real_delta, 
              float imag_delta );

int sq_conjugate(FILE* instream, FILE* outstream, unsigned int nsamples);

int sq_scaleandrotate(FILE* instream, FILE* outstream, 
                      unsigned int nsamples,
                      float scale_factor,
                      float radians );

int sq_scale(FILE* instream, FILE* outstream, unsigned int nsamples, float scale_factor);
int sq_rotate(FILE* instream, FILE* outstream, unsigned int nsamples, float radians);

#endif