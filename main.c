#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "delvs.h"

int main(int argc, char *argv[]) {
  if(argc > 1) {
    FILE *fp;
    long size;

    fp = fopen(argv[1], "r");

    if(fp == NULL) {
      printf("File: \"%s\" not found\n", argv[1]);
      return 1;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    char *temp = (char*) malloc (100);

    char *file = (char*) malloc (size);

    file[0] = '\0';

    while (fgets(temp, 100, fp) != NULL) strcat(file, temp);

    free(temp);
    fclose(fp);

    struct Data g;

    g.code = file;
    g.bit = 7;
    g.pointer = &g.vars[15000];

    lexer(&g);
  }
  else {
    printf("Usage: %s <filename>\n", argv[0]);
  }
  return 0;
}
