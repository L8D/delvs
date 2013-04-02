Delvs
=====

Delvs(Pronounced Del-vis) is my own personal variation of brainfuck, which adds the '=' character which breaks a loop if the current cell/pointer is 0. 
And eventually a few other things, like implementing BF++'s file writing stuff.

The '=' can be used for primitive 'if'-like statements. For example, to run code if a pointer equals a specific number, you can do:
`+[- > +++ > ++ < [ --- >-= < ] >= code for if cell 2 is 3 goes here ]`
