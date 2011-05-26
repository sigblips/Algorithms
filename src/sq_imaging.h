#ifndef SQ_IMAGING_H
#define SQ_IMAGING_H

#define MAX_PIXEL_VAL 255

#include <stdio.h>

void sq_linear_scale(float* img_buf, int rows, int cols);
void sq_power_scale(float* img_buf, int rows, int cols);
void sq_no_scale(float* img_buf, int rows, int cols);
int sq_read_img(FILE* instream, float* img_buf, int rows, int cols);
void sq_write_pnm(FILE* outstream, float* img_buf, int rows, int cols);

#endif