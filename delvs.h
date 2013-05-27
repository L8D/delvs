#include <stdio.h>
#include <stdbool.h>

void lexer(const char *source, short int *p) {
  bool endLoop;
  for (const char *c = source; endLoop || *c == EOF; c++) {
    switch (*c) {
      case '>':
        ++p;
        break;

      case '<':
        --p;
        break;

      case '+':
        ++*p;
        break;

      case '-':
        --*p;
        break;

      case '.':
        putchar(*p);
        break;

      case ',':
        *p += getchar();
        break;

      case '[':
        break;

      case ']':
        if(!*p) endLoop = true;
        break;

      default:
        // everything else is comments
        break;
    }
  }
}
