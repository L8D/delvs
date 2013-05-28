#include <stdio.h>

void lexer(const char *source, short int *p) {
  for (const char *c = source; *c; c++) {
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
        while(*p) {
          lexer(c, p);
        }
        break;

      case ']':
        return;

      default:
        // everything else is comments
        break;
    }
  }
}
