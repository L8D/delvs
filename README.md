Delvs
=====

Delvs(Pronounced Del-vis) is my own personal variation of brainfuck, the interpreter is written in C.

Additions
---------
- `:` casts the current value to a string and prints it.
- `;` grabs value from user input and casts to cell value.
- `#` reads following cells as null-terminating string for filename, then if current cell is != 1, open file for reading, or if 1, open file writing.
- `\`` read next char from file, apply to current cell.
- `!` write char from current cell to file.
