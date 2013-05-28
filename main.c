#include "delvs.h"
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  char *code = "+++++ +++++ [>+++++ +++++<-]> ++++ . + .";
  short int data[30000];
  short int *p = &data[15000];
  lexer(code, p);

  return 0;
}
