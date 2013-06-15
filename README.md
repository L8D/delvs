Delvs
=====

Delvs(Pronounced Del-vis) is my own personal variation of brainfuck, the interpreter is written in C.
File reading was inspired by brainfuck++, and the bit fiddling was inspired by boolfuck(DuckDuckGo them if you have to, I'm not putting links there right now)

Additions
---------
- `:` casts the current value to a string and prints it. Code: `printf("%hhd", *p);`
- `;` grabs value from user input and casts to cell value. Code: `scanf("%hhd", p);`
- `#` reads following cells as null-terminating string for filename, then if current cell is != 1, open file for reading, or if 1, open file writing. Code: `f = fopen(p + 1, p == 1 ? "w" : "r");`
- `` ` `` read next char from file, apply to current cell. (`EOF` becomes `0`) Code: `*p = fgetc(f);`
- `!` write char from current cell to file. Code: `fputc(*p, f);`
- `"` increment current bit position by 1. (psuedo)Code: `b++;`
- `'` flip bit at current bit position, then incrment current bit position by 1. Code: `*p ^= (1 << b)`
- `/[...]` ignore EVERYTHING between the two brackets. Remember the beginned needs to be `/[`

Example
-------
Turn your code that looks like this:

    +++++ +++++ [
      > +++++ ++
      > +++++ +++++
      > +++
      >+
      <<<< -
    ]
    > ++ . H
    > + . e
    +++++ ++ . . ll
    +++ . o
    > ++ .
    << +++++ +++++ +++++ . W
    > . +++ . or
    ------ . -------- . ld
    > + . !
    > .

Into this:

    01001000 H
    "'""'""".>
    01100101 e
    "''""'"'.>
    01101100 l
    "''"''"".>
    01101100 l
    "''"''"".>
    01101111 o
    "''"''''.>
    00100000
    ""'""""".>
    01010111 W
    "'"'"'''.>
    01101111 o
    "''"''''.>
    01110010 r
    "'''""'".>
    01101100 l
    "''"''"".>
    01100100 d
    "''""'"".>
    00100001 !
    ""'""""'.>
    00001010 \n
    """"'"'".>
