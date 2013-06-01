Delvs
=====

Delvs(Pronounced Del-vis) is my own personal variation of brainfuck, the interpreter is written in C.

Additions
---------
- `:` casts the current value to a string and prints it. Code: `printf("%hhd", *p);`
- `;` grabs value from user input and casts to cell value. Code: `scanf("%hhd", p);`
- `#` reads following cells as null-terminating string for filename, then if current cell is != 1, open file for reading, or if 1, open file writing. Code: `f = fopen(p + 1, p == 1 ? "w" : "r");`
- `\`` read next char from file, apply to current cell. (`EOF` becomes `0`) Code: `*p = fgetc(f);`
- `!` write char from current cell to file. Code: `fputc(*p, f);`
