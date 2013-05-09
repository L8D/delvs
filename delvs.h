#include <stdio.h>

void lexer(const char *code, size_t len, struct *data) {
  int n[30000];
  int *c;
  c = &n[0];
  char doBreak = 0;
  for (const char *p = code ; doBreak || p != code + len ; ++p)
    switch (*p) {
      case '>':
        ++c;
        break;

      case '<':
        --c;
        break;

      case '+':
        ++*c;
        break;

      case '-':
        --*c;
        break;

      case '.':
        putchar(*c);
        break;

      case ',':
        *c = getchar();
        break;

      case '[':
        break;

      case ']':
        break;

      case '=':
        if(!*c) doBreak = 1;
        break;

      default:
        // everything else is comments
        break;
    }
};
