CXXFLAGS=-std=c++0x -Os -fno-rtti
all: interpreter compiler

interpreter: interpreter.cc brainfuck.h

compiler: compiler.cc brainfuck.h

