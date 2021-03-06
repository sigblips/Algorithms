#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "sq_imaging.h"
#include "sq_constants.h"

int sq_alloc_img(float* img_buf, int rows, int cols)
{
    img_buf = malloc(sizeof(float) * rows * cols);
    if(img_buf == NULL)
        return ERR_MALLOC;
}

int sq_no_scale(float* img_buf, int rows, int cols)
{

}

int sq_linear_scale(float* img_buf, int rows, int cols)
{
    unsigned int imgi;

    float imgvalf;

    float min = img_buf[0];
    float max = img_buf[0];

    for (imgi = 0; imgi < (rows * cols); imgi++)
    {
        if (img_buf[imgi] < min) min = img_buf[imgi];
        if (img_buf[imgi] > max) max = img_buf[imgi];
    }

    for (imgi = 0; imgi < (rows * cols); imgi++)
    {
        imgvalf = img_buf[imgi];
        imgvalf -= min;
        imgvalf *= ((float) MAX_PIXEL_VAL) / (max - min);
        img_buf[imgi] = imgvalf;
    }
}

int sq_power_scale(float* img_buf, int rows, int cols)
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

    for (imgi = 0; imgi < (rows * cols); imgi++)
    {
        imgvalf = img_buf[imgi];
        imgvalf -= min;
        imgvalf *= ((float) MAX_PIXEL_VAL) / (max - min);
        img_buf[imgi] = imgvalf;
    }
}

int sq_read_img(FILE* instream, float* img_buf, int rows, int cols)
{
    unsigned int rowi;

    if (!((rows > 0) && (cols > 0)))
        return ERR_ARG_BOUNDS;

    for (rowi = 0; rowi < rows; rowi++)
    {
        if (!(fread(&img_buf[rowi*cols], sizeof(float), cols, instream) == cols))
        {
            rows = rowi;
            break;
        }
    }

    if (!(rows > 0))
    {
        free(img_buf);
        return ERR_STREAM_READ;
    }
}

int sq_write_pnm(FILE* outstream, float* img_buf, int rows, int cols)
{
    unsigned int imgi;
    float imgvalf;
    unsigned char imgvalb;

    fprintf(outstream, "P5\n");
    fprintf(outstream, "%u %u\n", cols, rows);
    fprintf(outstream, "%u\n", MAX_PIXEL_VAL);

    for (imgi = 0; imgi < (rows * cols); imgi++)
    {
        imgvalf = img_buf[imgi];
        
        if (imgvalf < 0.0)
            imgvalf = 0.0;
        if (imgvalf > (float) MAX_PIXEL_VAL) 
            imgvalf = (float) MAX_PIXEL_VAL;
        
        imgvalb = (unsigned char) imgvalf;
        fwrite(&imgvalb, 1, 1, outstream);
    }
}
