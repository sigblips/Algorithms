#ifndef __x86_64__
#define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#define MAX_SMPLS_LEN 134217728

unsigned int smpls_len = 100000;

float *smpls_bfr;

void mylog(char *msg);

int main(int argc, char **argv) {

  int opt;

  unsigned int smpli;

  while ((opt = getopt(argc, argv, "l:")) != -1) {
    switch (opt) {
      case 'l':
        sscanf(optarg, "%u", &smpls_len);
        break;
    }
  }

  if (!((smpls_len >= 2) && (smpls_len <= MAX_SMPLS_LEN))) {
    printf("sqpwr [-l samples-block-size]\n");
    exit(EXIT_FAILURE);
  }

  smpls_bfr = malloc(smpls_len * 4 * 2);

  while (fread(smpls_bfr, 8, smpls_len, stdin) == smpls_len) {
    for (smpli = 0; smpli < smpls_len; smpli++) {
      smpls_bfr[(smpli<<1)+0] =
        (smpls_bfr[(smpli<<1)+0] * smpls_bfr[(smpli<<1)+0]) +
        (smpls_bfr[(smpli<<1)+1] * smpls_bfr[(smpli<<1)+1]);
      smpls_bfr[(smpli<<1)+1] = 0.0;
    }
    fwrite(smpls_bfr, 8, smpls_len, stdout);
  }

  free(smpls_bfr);

  exit(EXIT_SUCCESS);
}
