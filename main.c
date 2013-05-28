#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "delvs.h"

bool fileExists(const char *filename) {
  FILE *file;
  if ((file = fopen(filename, "r")) == NULL) {
    return false;
  } else {
    fclose(file);
    return true;
  }
}

int main(int argc, char *argv[]) {
  if(argc > 1) {
    if(fileExists(argv[1])) {
      FILE *fp;
      long size;

      fp = fopen(argv[1], "r");

      fseek(fp, 0, SEEK_END);
      size = ftell(fp);
      rewind(fp);

      char *temp = (char*) malloc (100);

      char *file = (char*) malloc (size);

      file[0] = '\0';

      while (fgets(temp, 100, fp) != NULL) strcat(file, temp);

      free(temp);
      fclose(fp);

      const char *code = file;
      code = malloc(sizeof(*file));
      short int data[30000];
      short int *p = &data[15000];

      lexer(code, p);
    }
    else {
      printf("File not found!");
    }
  }

  const char *code = "+++++ +++++ [>+++++ +++++<-]> ++++ . + .";
  short int data[30000];
  short int *p = &data[15000];
  lexer(code, p);

  return 0;
}
