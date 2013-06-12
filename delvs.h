#include <stdio.h>
#define c g->code
#define p g->pointer
#define f g->file

struct Data {
  const char *code;
  char vars[30000];
  char *pointer;
  FILE *file;
};

void dlexer(struct Data *g) {
  while(*c) if(*c++ == ']')
    return;
}

void lexer(struct Data *g) {
  const char *cc = c;
  while(*c)
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
        if(!*p) dlexer(g);
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
        if((*p = fgetc(f)) == EOF) *p = 0;
        break;

      case '!':
        fputc(*p, f);
        break;

      default:
        // everything else is comments
        break;
    }
}
/*
 * Usage:
 *  struct Data g;
 *  g.code = file;
 *  g.pointer = &g.data[15000];
 *  lexer(&g);
 */
