#include <stdio.h>

struct data {
  const char *code;
  char vars[30000];
  char *pointer;
  FILE *file;
};

void lexer(struct data *g) {
#define c g->code
#define p g->pointer
#define f g->file
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
          lexer(g);
        }
        break;

      case ']':
        return;

      case ':':
        printf("%hhd", *p);
        break;

      case ';':
        scanf("%hhd", p);
        break;

      case '#':
        // open in read mode unless the cell is 1
        f = fopen(p + 1, *p == 1 ? "w" : "r");
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
}
/*
 * Usage:
 *  struct g g;
 *  g.code = file;
 *  g.pointer = &g.data[15000];
 *  g.file = NULL;
 *  lexer(&g);
 */
