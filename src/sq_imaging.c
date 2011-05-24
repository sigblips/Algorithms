#include <math.h>
#include <stdio.h>

#include "sq_imaging.h"

void sq_linear_scale(float* img_buf, int rows, int cols)
{
    unsigned int imgi;
    
    float imgvalf;
    
    float min = img_buf[0];
    float max = img_buf[0];
    
    for (imgi = 0; imgi < (rows * cols); imgi++) {
        if (img_buf[imgi] < min) min = img_buf[imgi];
        if (img_buf[imgi] > max) max = img_buf[imgi];
    }
    
    for (imgi = 0; imgi < (rows * cols); imgi++) {
        imgvalf = img_buf[imgi];
        imgvalf -= min;
        imgvalf *= ((float) MAX_PIXEL_VAL) / (max - min); 
        img_buf[imgi] = imgvalf;
    }
}

void sq_power_scale(float* img_buf, int rows, int cols)
{
    unsigned int imgi;    
    float imgvalf;

    float mean, stddev;
    float min, max;
    
    min = img_buf[0];
    
    for (imgi = 0; imgi < (rows * cols); imgi++)
        if (img_buf[imgi] < min) min = img_buf[imgi];
        if (min < 0.0)
            for (imgi = 0; imgi < (rows * cols); imgi++)
                img_buf[imgi] -= min;
            
            mean = 0.0;
        for (imgi = 0; imgi < (rows * cols); imgi++)
            mean += sqrt(img_buf[imgi]);
        mean /= (rows * cols);
    
    stddev = 0.0;
    for (imgi = 0; imgi < (rows * cols); imgi++)
        stddev += (sqrt(img_buf[imgi]) - mean) * (sqrt(img_buf[imgi]) - mean);
    stddev = sqrt(stddev / (rows * cols));
    
    min = mean - stddev;
    if (min < 0.0) min = 0.0;
    min = min * min;
    max = mean + (2.3 * stddev);
    max = max * max;
    
    for (imgi = 0; imgi < (rows * cols); imgi++) {
        imgvalf = img_buf[imgi];
        imgvalf -= min;
        imgvalf *= ((float) MAX_PIXEL_VAL) / (max - min); 
        img_buf[imgi] = imgvalf;
    }
}

void sq_write_pnm(FILE* outstream, float* img_buf, int rows, int cols)
{
    unsigned int imgi;
    float imgvalf;
    unsigned char imgvalb;
    
    fprintf(stderr, "P5\n");
    fprintf(stderr, "%u %u\n", cols, rows);
    fprintf(stderr, "%u\n", MAX_PIXEL_VAL); 
    
    for (imgi = 0; imgi < (rows * cols); imgi++) {
        imgvalf = img_buf[imgi];
        if (imgvalf < 0.0) imgvalf = 0.0;
        if (imgvalf > (float) MAX_PIXEL_VAL) imgvalf = (float) MAX_PIXEL_VAL;
        imgvalb = (unsigned char) imgvalf;
        fwrite(&imgvalb, 1, 1, outstream);
    }
}