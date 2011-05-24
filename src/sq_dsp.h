#ifndef SQ_DSP_H
#define SQ_DSP_H

#include <stdio.h>

/**
 * Takes 2-channel (quadrature) 8-bit data from the input stream,
 * and writes samples in the form of floats to the output stream,
 * in chunks of a given number of samples.
 * @param instream Input stream with 2-channel 8-bit data.
 * @param outstream Output stream of floats
 * @param nsamples Number of samples to process at a time
 * @return Code; negative if error.
 */
int sq_sample(FILE* instream, FILE* outstream, unsigned int nsamples);

/**
 * Takes a stream of floats (alternating real, imaginary) as input signal
 * and writes the instantaneous power samples to the output stream.
 * @param instream Input stream of float data
 * @param outstream Output stream of float data
 * @param nsamples Number of samples to process at a time
 * @return Code; negative if error.
 */
int sq_power(FILE* instream, FILE* outstream, unsigned int nsamples);

int sq_sum(FILE* instream, FILE* outstream, unsigned int nsamples);

int sq_window(FILE* instream, FILE* outstream, unsigned int window_length);

/**
 * Takes a stream of sample floats as input signal and returns the 
 * real or imaginary component of that signal.
 * @param instream Input stream of float data
 * @param outstream Output stream of float data
 * @param nsamples Number of samples to process at a time
 * @param component The REAL (0) or IMAGINARY (1) component
 */
int sq_component(FILE* instream, FILE* outstream, unsigned int nsamples, int component);

/**
 * Takes a stream of sample floats as input signal and returns the 
 * real component of that signal.
 * @param instream Input stream of float data
 * @param outstream Output stream of float data
 * @param nsamples Number of samples to process at a time
 */
int sq_real(FILE* instream, FILE* outstream, unsigned int nsamples);

/**
 * Takes a stream of sample floats as input signal and returns the 
 * imaginary component of that signal.
 * @param instream Input stream of float data
 * @param outstream Output stream of float data
 * @param nsamples Number of samples to process at a time
 */
int sq_imag(FILE* instream, FILE* outstream, unsigned int nsamples);

/**
 * Computes the Fast Fourier Transform (FFT) of the sequence of floats in the
 * input stream and returns the sequence of floats of it's frequency domain
 * representation.
 * @param instream Input stream of float data in the time domain
 * @param outstream Output stream of float data in the frequency domain
 * @param fft_len The length of the FFT
 */
int sq_fft(FILE* instream, FILE* outstream, 
           unsigned int fft_len, 
           unsigned char is_inverted, 
           unsigned char is_measured );

/**
 * Takes a signal and adds a complex DC offset to it.
 * @param instream Input stream of float data
 * @param outstream Output stream of float data
 * @param real_delta The real part of the DC offset
 * @param imag_delta The imaginary part of the DC offset
 */
int sq_offset(FILE* instream, FILE* outstream, 
              unsigned int nsamples, 
              float real_delta, 
              float imag_delta );

/**
 * Computes the complex conjugate of a signal.
 * @param instream Input stream of float data
 * @param outstream Output stream of float data which contains the conjugate samples
 * @param nsamples Number of samples to process at a time
 */
int sq_conjugate(FILE* instream, FILE* outstream, unsigned int nsamples);

/**
 * Multiplies a signal by a constant R*exp(j*Theta), where R is the scaling factor
 * and Theta is the phase.
 * @param instream Input stream of float data
 * @param outstream Output stream of float data which contains the conjugate samples
 * @param nsamples Number of samples to process at a time
 * @param scale_factor The scaling factor R
 * @param radians The phase Theta
 */
int sq_scaleandrotate(FILE* instream, FILE* outstream, 
                      unsigned int nsamples,
                      float scale_factor,
                      float radians );

/**
 * Scales the input signal by a given factor.
 * @param instream Input stream of float data
 * @param outstream Output stream of scaled float data
 * @param nsamples Number of samples to process at a time
 * @param scale_factor The scaling factor R
 */
int sq_scale(FILE* instream, FILE* outstream, unsigned int nsamples, float scale_factor);

/**
 * Adds a constant value to the instantaneous phase of each sample in the signal.
 * @param instream Input stream of float data
 * @param outstream Output stream of float data
 * @param nsamples Number of samples to process at a time
 * @param radians The value to be added to the instantaneous phase
 */
int sq_rotate(FILE* instream, FILE* outstream, unsigned int nsamples, float radians);

int sq_mix(FILE* instream, FILE* outstream, unsigned int nsamples, float radians);

int sq_zoom(FILE* instream, FILE* outstream, unsigned int zoom_length);

void init_window(float* wndwbfr, unsigned int wndwlen, unsigned int folds);
int sq_wola(FILE* instream, FILE* outstream,
            unsigned int fftlen,
            unsigned int folds,
            unsigned int overlap,
            unsigned char is_window_dump);

#endif