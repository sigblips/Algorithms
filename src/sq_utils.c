#include "sq_constants.h"
#include "sq_utils.h"

void print_usage(char** usage_text)
{
    unsigned int i;
    
    for (i = 0; i < (sizeof(usage_text) / sizeof(char)); i++)
        fprintf(stderr, "%s\n", usage_text[i]);
}
