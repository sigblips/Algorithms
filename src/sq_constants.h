#ifndef SQ_CONSTANTS_H
#define SQ_CONSTANTS_H

#include <inttypes.h>
#include <math.h>

// Error codes
#define err_arg_bounds -1
#define err_stream_open -2
#define err_stream_close -3
#define err_stream_read -4
#define err_stream_write -5
#define err_malloc -6

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