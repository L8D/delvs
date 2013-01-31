CXXFLAGS=-std=c++0x -Os -fno-rtti
all: test interpreter compiler

test: test.cc brainfuck.h

interpreter: interpreter.cc brainfuck.h

compiler: compiler.cc brainfuck.h

