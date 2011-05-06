#ifndef __x86_64__
#define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//          1         2         3         4         5         6         7
// 123456789012345678901234567890123456789012345678901234567890123456789012 
char *usage_text[] = {
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

void stdout_usage();

int main(int argc, char *argv[]) {
  int coli;
  float val;

  int opt;

  while ((opt = getopt(argc, argv, "c:")) != -1) {
    switch (opt) {
      case 'c':
        sscanf(optarg, "%u", &cols);
        break;
    }
  }

  if (!(cols > 0)) {
    stdout_usage();
    exit(EXIT_FAILURE);
  }

  coli = 0;
  while (fread(&val, sizeof(float), 1, stdin) == 1) {
    printf(" %e", val);
    coli++;
    if (!(coli < cols)) {
      printf("\n");
      coli = 0;
    }
  }

  exit(EXIT_SUCCESS);
}

void stdout_usage() {
  unsigned int i;

  for (i = 0; i < (sizeof(usage_text)/sizeof(char *)); i++)
    fprintf(stderr, "%s\n", usage_text[i]); 
}
