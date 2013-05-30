#include <stdio.h>

const char *lexer(const char *c, short int *p) {
  const char *cc = c;
  while(*c) {
    switch (*c++) {
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
        *p = getchar();
        break;

      case '[':
        cc = c;
        while(*p) {
          c = cc; // restore char position to start of loop
          c = lexer(c + 1, p);
        }
        break;

      case ']':
        return c;

      default:
        // everything else is comments
        break;
    }
  }
  return c;
}
/*
 * Usage:
 * const char *code = ",[.,]";
 * short int data[30000];
 * short int *p = &data[0];
 * lexer(&code, p);
 */
