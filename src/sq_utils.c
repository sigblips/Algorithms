#include "sq_constants.h"
#include "sq_utils.h"

void print_usage(char** usage_text)
{
    unsigned int i;
    
    for (i = 0; i < (sizeof(usage_text) / sizeof(char)); i++)
        fprintf(stderr, "%s\n", usage_text[i]);
}

int sq_read_array(float inarray[], FILE* outstream, int ncolumns)
{
    if (ncolumns <= 0)
        return err_arg_bounds;
    
    unsigned int coli;
    unsigned long length = sizeof(inarray)/sizeof(float);
    
    for(coli = 0; coli < length; ++coli)
    {
        fprintf(outstream, " %e", inarray[coli]);
        
        if (coli % ncolumns == 0)
            fprintf(outstream, "\n");
    }
    
    return coli;
}

int sq_read_stream(FILE* instream, FILE* outstream, int ncolumns)
{
    if (ncolumns <= 0)
        return err_arg_bounds;
    
    unsigned long coli = 0;
    
    float val;
    while (fread(&val, sizeof(float), 1, instream) == 1)
    {
        fprintf(outstream, " %e", val);
        coli++;
        
        if (coli % ncolumns == 0)
            fprintf(outstream, "\n");
    }
    
    return coli;
}
