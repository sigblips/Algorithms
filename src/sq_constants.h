#ifndef SQ_CONSTANTS_H
#define SQ_CONSTANTS_H

#include <inttypes.h>

//Error codes
#define err_arg_bounds -1
#define err_stream_open -2
#define err_stream_close -3
#define err_stream_read -4
#define err_stream_write -5

// Some constants
#define MAX_SMPLS_LEN 134217728
#define TOTAL_BYTES_TRIGGER_VAL 1000000000
#define SMPLS_PER_READ 1000000

// Array indices
#define REAL 0
#define IMAG 1
            
#endif