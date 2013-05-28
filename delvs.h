#include <stdio.h>

void lexer(const char *c, short int *p) {
  for (; *c; c++) {
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
        while(*p) lexer(c, p);
        break;

      case ']':
        return;

      case EOF:
        return;

      default:
        // everything else is comments
        break;
    }
  }
}
/*
 * Usage:
 * const char *code = ",[.,]";
 * short int data[30000];
 * short int *p = &data[0];
 * lexer(code, p);
 */
