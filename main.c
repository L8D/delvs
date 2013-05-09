#include "delvs.h"
#include <stdio.h>
#include <stdbool.h>

bool fileExists(const char *filename) {
  FILE *file;
  if((file = fopen(filename, "r"))) {
    fclose(file);
    return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  if(argc > 1) {
    if(fileExists(argv[1])) {
      printf("File found");
      // stuff here
      FILE *sourceCodeFile = fopen(argv[1], 'r');

    }
    else {
      printf("File not found");
      return 404;
    }
  }
  return 0;
}
