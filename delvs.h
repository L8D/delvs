#include <stdio.h>

const char *lexer(const char *c, char *p, FILE *f) {
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
        printf("start stack\n");
        while(*p) {
          c = cc; // restore char position to start of loop
          c = lexer(c + 1, p, f);
        }
        break;

      case ']':
        printf("%hhd", *p);
        return c;

      case ':':
        printf("%hhd", *p);
        break;

      case ';':
        scanf("%hhd", p);
        break;

      case '#':
        f = fopen(p + 1, "rw");
        break;

      case '`':
        *p = fgetc(f);
        break;

      case '!':
        fputc(*p, f);
        break;

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
 * char data[30000];
 * char *p = &data[0];
 * lexer(&code, p);
 */
