#include <stdio.h>
#include <stdbool.h>

void lexer(const char *source, short int *p) {
  for (const char *c = source; *c != NULL; c++) {
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
        break;

      default:
        // everything else is comments
        break;
    }
  }
}
