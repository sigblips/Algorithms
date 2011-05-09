#ifndef __x86_64__
#   define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sq_utils.h"

//          1         2         3         4         5         6         7
// 123456789012345678901234567890123456789012345678901234567890123456789012
char *usage_text[] =
{
    "                                                                        ",
    "NAME                                                                    ",
    "  sqread - inputs float values and then prints the float values         ",
    "           as text values arranged in columns                           ",
    "SYNOPSIS                                                                ",
    "  sqread [OPTIONS] ...                                                  ",
    "DESCRIPTION                                                             ",
    "  -c  pos. integer (required),  columns                                 ",
    "                                                                        "
};

unsigned int cols = 0;

int main(int argc, char *argv[])
{
    int coli;
    float val;

    int opt;

    while ((opt = getopt(argc, argv, "c:")) != -1)
    {
        switch (opt)
        {
            case 'c':
                sscanf(optarg, "%u", &cols);
                break;
        }
    }

    if (!(cols > 0))
    {
        print_usage(usage_text);
        exit(EXIT_FAILURE);
    }

    coli = 0;
    while (fread(&val, sizeof(float), 1, stdin) == 1)
    {
        printf(" %e", val);
        coli++;
        if (!(coli < cols))
        {
            printf("\n");
            coli = 0;
        }
    }

    exit(EXIT_SUCCESS);
}


