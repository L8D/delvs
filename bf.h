#include <stdio.h>
#define c g->code
#define p g->pointer
#define f g->file

struct Data {
  const char *code;
  char vars[30000];
  char *pointer;
};

void dummyLexer(struct Data *g) { while(*c) if(*c++ == ']') return; }

void lexer(struct Data *g) {
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
        if(!*p) dummyLexer(g);
        while(*p) {
          c = cc; // restore char position to start of loop
          lexer(g);
        }
        break;

      case ']':
        return;

      default:
        // everything else is comments
        break;
    }
  }
  return;
}
/*
 * Usage:
 *  struct Data g;
 *  g.code = file;
 *  g.pointer = &g.data[15000];
 *  lexer(&g);
 */
