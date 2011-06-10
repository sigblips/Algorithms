#ifndef SQ_CONSTANTS_H
#define SQ_CONSTANTS_H

#include <inttypes.h>
#include <math.h>

// Error codes
#define ERR_ARG_BOUNDS -1
#define ERR_STREAM_OPEN -2
#define ERR_STREAM_CLOSE -3
#define ERR_STREAM_READ -4
#define ERR_STREAM_WRITE -5
#define ERR_MALLOC -6

// Some constants
#define MAX_SMPLS_LEN 134217728
#define TOTAL_BYTES_TRIGGER_VAL 1000000000
#define SMPLS_PER_READ 1000000
#define MAX_WNDW_LEN 134217728
#define SQ_STAGE1_FFT_LEN 4096
#define MAX_ZOOM_LEN 134217728
#define ZOOM_OUTPUT_BFR_LEN 1024

// Math constants
#define PI 3.1415926535897932384626433832795

// Array indices
#define REAL 0
#define IMAG 1

typedef float cmplx[2];
            
#endif